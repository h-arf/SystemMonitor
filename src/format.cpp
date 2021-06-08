#include <string>
#include <iostream>//should wrap
#include "format.h"
#define DEBUG_PRINT
using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long s) {
#ifdef DEBUG_PRINT
    std::cerr<<"star s is: "<<s<<std::endl;
#endif
    long m,h;
    m=s/60;
    s=s%60;
    h=m/60;
    m=m%60;
    h=h%24;
    string r;
#ifdef DEBUG_PRINT
    std::cerr<<h<<":"<<m<<":"<<s<<std::endl;
#endif
    return to_string(h)+":"+to_string(m)+":"+to_string(s);
}