#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    //from the link provided to roseta code
    std::vector<unsigned long> r=LinuxParser::CpuUtilization();
    unsigned long tt=std::accumulate(r.begin(), r.end(), 0ll);
    unsigned long idle=r[3];
    unsigned long i_d=idle-prev_idle;
    unsigned long t_d=tt-prev_total;
    prev_idle=idle;
    prev_total=tt;
    return (1.0-(float)i_d/t_d);
}