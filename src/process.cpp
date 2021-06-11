#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include "process.h"
#include "linux_parser.h"
#include <sys/types.h>
#include <pwd.h>
using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
    pid_=pid;
}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }
bool cmp(const Process &a, const Process &b){
    return a.CpuUtilization()>b.CpuUtilization();
}
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{
    long Hertz=sysconf(_SC_CLK_TCK);
    vector<string> vs=LinuxParser::CpuUtilization(pid_);
    unsigned long utime=std::stoul(vs[0]), stime=std::stoul(vs[1]);
    //long cutime=std::stol(vs[2]),cstime=std::stol(vs[3]);
    unsigned long long starttime=std::stoull(vs[4]);
    //std::cerr<<utime<<" "<<stime<<" "<<cutime<<" "<<cstime<<" "<<starttime<<" "<<LinuxParser::UpTime()<<" "<<Hertz<<std::endl;
    unsigned long long total_time = utime + stime;// + cutime + cstime;
    float seconds = LinuxParser::UpTime() - (float)(starttime / Hertz);
    return (float)(((total_time ) / seconds)/100);
}

// TODO: Return the command that generated this process
string Process::Command()
{
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User()
{
    int uid=LinuxParser::Uid(pid_);
    struct passwd *pws;
    if((pws = getpwuid(uid))<0){
        return to_string(uid);
    }
    return pws->pw_name;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const { return CpuUtilization()<a.CpuUtilization(); }