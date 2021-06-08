#include <string>

#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long s) {
    long m,h;
    m=s/60;
    s=s%60;
    h=m/60;
    m=m%60;
    h=h%24;
    string r;
    return to_string(h)+":"+to_string(m)+":"+to_string(s);
}