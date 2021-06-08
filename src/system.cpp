#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
//TODO
Processor& System::Cpu(){
    return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
    if (processes_.size()<1){
        //TODO: processes_=LinuxParser::Pids();
    }
    return processes_;
}


std::string System::Kernel()
{
    if (kernel_.size()<1){
        kernel_=LinuxParser::Kernel();
    }
    return kernel_;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization()
{ 
    return LinuxParser::MemoryUtilization();
}


std::string System::OperatingSystem()
{
    if (os_.size()<1){
        os_=LinuxParser::OperatingSystem();
    }
    return os_;
}


int System::RunningProcesses()
{
    return LinuxParser::RunningProcesses();
}


int System::TotalProcesses()
{
    return LinuxParser::TotalProcesses();
}


long int System::UpTime(){
    return LinuxParser::UpTime();
}