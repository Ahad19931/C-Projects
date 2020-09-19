#include "processor.h"
#include <sstream>
#include <fstream>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
    std::string line, first_string;
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    if(stream.is_open()){
        std::getline(stream,line);
        std::istringstream ss(line);
        ss >> first_string >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        float PrevIdle = previdle + previowait;
        float Idle = idle + iowait;
        float PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
        float NonIdle = user + nice + system + irq + softirq + steal;
        float PrevTotal = PrevIdle + PrevNonIdle;
        float Total = Idle + NonIdle;
        float totald = Total - PrevTotal;
        float idled = Idle - PrevIdle;
        float output = (totald - idled) / totald;

        previdle = idle;
        previowait = iowait;
        prevuser = user;
        prevnice = nice;
        prevsystem = system;
        previrq = irq;
        prevsoftirq = softirq;
        prevsteal = steal;    

        return output;      
    }  
    return 0.0;
}