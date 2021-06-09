#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    //from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    std::vector<unsigned long long> r=LinuxParser::CpuUtilization();
    unsigned long long tt=std::accumulate(r.begin(), r.end(), 0ll);
    long double idle=r[3];
    unsigned long long i_d=idle-prev_idle;
    unsigned long long t_d=tt-prev_total;
    prev_idle=idle;
    prev_total=tt;
    return (float)(1.0-t_d/i_d);
}