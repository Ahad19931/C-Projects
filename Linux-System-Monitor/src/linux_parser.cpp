#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
    std::ifstream stream(kProcDirectory+kMeminfoFilename);
    std::string line, key;
    float MemTotal, MemFree, MemU;
    int value;
    if(stream.is_open()){
      for(size_t i{0};i<2;++i){
        std::getline(stream,line);
        std::replace(line.begin(),line.end(),':',' ');
        std::istringstream ss(line);
        ss >> key >> value;
        if(key=="MemTotal"){MemTotal=value;}
        else
          MemFree=value;  
      }
      MemU=(MemTotal-MemFree)/MemTotal;
    }
    return MemU; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  long uptime, idletime;
  if(stream.is_open()){
    stream >> uptime >> idletime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
float LinuxParser::CpuUtilization(int pid) { 
    std::string p=std::to_string(pid);
	std::ifstream stream(kProcDirectory+p+kStatFilename);
  	std::string line;
  	std::vector<std::string> utilization_values;
  	float utime, stime, cutime, cstime, start_time, hertz, total_time, seconds, cpu_usage;
  	int count{22};
  	if(stream.is_open()){
        for(int i{0};i<count;i++){
          stream>>line;
      	  utilization_values.push_back(line);
        }
      	utime = stof(utilization_values.at(13));
  		stime = stof(utilization_values.at(14));
  		cutime = stof(utilization_values.at(15));
  		cstime = stof(utilization_values.at(16));
  		start_time = stof(utilization_values.at(21));
 		  hertz = sysconf(_SC_CLK_TCK);
  		total_time = utime + stime + cutime + cstime;
  		seconds = LinuxParser::UpTime() - (start_time / hertz);
  		cpu_usage = ((total_time / hertz) / seconds);
  		return cpu_usage;
    }    	
	return 0.0; 
}

int LinuxParser::TotalProcesses() { 
    std::ifstream stream(kProcDirectory+kStatFilename);
    std::string line, key;
    int value;
    if(stream.is_open()){
      while(std::getline(stream,line)){
        std::istringstream ss(line);
        ss >> key >> value;
        if(key=="processes")
          return value;
      }
    }
    return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
    std::ifstream stream(kProcDirectory+kStatFilename);
    std::string line, key;
    int value;
    if(stream.is_open()){
      while(std::getline(stream,line)){
        std::istringstream ss(line);
        ss >> key >> value;
        if(key=="procs_running")
          return value;
      }
    }
    return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  	std::string p=std::to_string(pid);
	  std::ifstream stream(kProcDirectory+p+kCmdlineFilename);
  	std::string command, line;
  	if(stream.is_open()){
      std::getline(stream,line);
  	  std::replace(line.begin(),line.end(),':',' ');
   	  std::istringstream ss(line);
      ss>>command;
      return command;
    }
    return string();
}
// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
	std::string p=std::to_string(pid);
	std::ifstream stream(kProcDirectory+p+kStatusFilename);
  	std::string line,ram_string,ram_mb,val;
  	long int ram_value;
  	if(stream.is_open()){
      while(std::getline(stream,line)){
        std::replace(line.begin(),line.end(),':',' ');
      	std::istringstream ss(line);
        ss>>ram_string>>val;
        if(ram_string=="VmSize"){
          ram_value=std::stol(val)/1000;
          return ram_mb=std::to_string(ram_value);
        }
      }
    }
   return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {     
    std::string p=std::to_string(pid);
	std::ifstream stream(kProcDirectory+p+kStatusFilename);
  	std::string line,uid_string;
  	std::string uid_num;
  	if(stream.is_open()){
      while(std::getline(stream,line)){
        std::replace(line.begin(),line.end(),':',' ');
      	std::istringstream ss(line);
        ss>>uid_string>>uid_num;
        if(uid_string=="Uid")
          return uid_num;
      }
    }
  	return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
	std::ifstream stream(kPasswordPath);
  	std::string line,user,x;
    std::string uid_num{Uid(pid)};
  	std::string uid;
  	if(stream.is_open()){
      while(std::getline(stream,line)){
        std::replace(line.begin(),line.end(),':',' ');
      	std::istringstream ss(line);
        ss>>user>>x>>uid;
        if(uid==uid_num)
          return user;
      }
    }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  	std::string p=std::to_string(pid);
	std::ifstream stream(kProcDirectory+p+kStatFilename);
  	std::string line;
    long int value;
  	int count{22};
  	if(stream.is_open()){
        for(int i{0};i<count;i++)
        	stream>>line;
      	value=UpTime() - std::stol(line)/sysconf(_SC_CLK_TCK);
      	return value;
    }   
  	return 0; 
 }