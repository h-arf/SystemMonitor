#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    //from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    std::vector<unsigned long long> r=LinuxParser::CpuUtilization();
    unsigned long long tt{(r[0])+(r[1])+(r[2])+(r[3])+(r[4])+(r[5])+(r[6])+(r[7])+(r[8])+(r[9])};
    unsigned long long idle=r[3];
    unsigned long long i_d=idle-prev_idle;
    unsigned long long t_d=tt-prev_total;
    prev_idle=idle;
    prev_total=tt;
    return 1.0-t_d/(long double)i_d;
}