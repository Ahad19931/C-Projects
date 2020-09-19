#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hours, mins, secs;
    std::string str;
    secs=seconds%60;
    mins =(seconds/60)%60;
    hours =(seconds/60)/60;
    return std::string(hours<10 ? "0":"") + std::to_string(hours) + ":"
           + std::string(mins<10 ? "0":"") + std::to_string(mins) + ":"
           + std::string(secs<10 ? "0":"") + std::to_string(secs);
}