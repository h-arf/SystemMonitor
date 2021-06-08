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
    double m,h;
    h=s/3600;
    m=(h-(long)h)*60;
    s=(m-(long)m)*60;
    string r;
#ifdef DEBUG_PRINT
    std::cerr<<h<<":"<<m<<":"<<s<<std::endl;
#endif
    return to_string((long)h)+":"+to_string((long)m)+":"+to_string(s);
}