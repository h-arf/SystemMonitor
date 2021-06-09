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
    std::vector<unsigned long> r=LinuxParser::CpuUtilization();
    unsigned long tt=std::accumulate(r.begin(), r.end(), 0ll);
    unsigned long idle=r[3];
    std::cerr<<tt<<" "<<idle<<" "<<r[3]<<std::endl;
    unsigned long i_d=idle-prev_idle;
    unsigned long t_d=tt-prev_total;
    std::cerr<<t_d<<" "<<i_d<<std::endl;
    prev_idle=idle;
    prev_total=tt;
    std::cerr<<(float)(1.0-(float)(t_d/i_d))<<std::endl;
    return (1.0-(float)t_d/i_d);
}