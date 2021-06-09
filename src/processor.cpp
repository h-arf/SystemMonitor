#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    //from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    std::vector<unsigned long long> r=LinuxParser::CpuUtilization();
    unsigned long long user{r[0]},nice{r[1]},system{r[2]},idle{r[3]},iowait{r[4]},irq{r[5]},softirq{r[6]},steal{r[7]},guest{r[8]},guest_nice{r[9]};
    unsigned long long intusertime = usertime - guest;                             # As you see here, it subtracts guest from user time
    unsigned long long intnicetime = nicetime - guestnice;                         # and guest_nice from nice time
// Fields existing on kernels >= 2.6
// (and RHEL's patched kernel 2.4...)
    unsigned long long int idlealltime = idletime + ioWait;  # ioWait is added in the idleTime
    unsigned long long int systemalltime = systemtime + irq + softIrq;
    unsigned long long int virtalltime = guest + guestnice;
    unsigned long long int totaltime = usertime + nicetime + systemalltime + idlealltime + steal + virtalltime;
    PrevIdle = previdle + previowait
    Idle = idle + iowait

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    NonIdle = user + nice + system + irq + softirq + steal

    PrevTotal = PrevIdle + PrevNonIdle
    Total = Idle + NonIdle

    totald = Total - PrevTotal
    idled = Idle - PrevIdle

    CPU_Percentage = (totald - idled)/totald;
    return CPU_Percentage;
}