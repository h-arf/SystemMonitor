#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
    pid_=pid;
}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization(){
    long Hertz=sysconf(_SC_CLK_TCK);
    vector<string> vs=LinuxParser::CpuUtilization(Pid());
    unsigned long utime,stime;
    long cutime,cstime;
    unsigned long long starttime;
    unsigned long long total_time = utime + stime + cutime + cstime;
    long seconds = LinuxParser::UpTime() - (starttime / Hertz);
    return (float)((total_time / Hertz) / seconds);
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }