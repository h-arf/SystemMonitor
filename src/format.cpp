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
#define SEC_IN_MIN 60
#define MIN_IN_HR 60
#define SEC_IN_HR (SEC_IN_MIN * MIN_IN_HR)
string Format::ElapsedTime(long seconds) {
    long hours, minutes;
    hours = seconds/SEC_IN_HR;
    seconds = seconds%SEC_IN_HR;
    minutes = seconds/SEC_IN_MIN;
    seconds = seconds%SEC_IN_MIN;
    string secs=std::to_string(seconds);
    secs.insert(0, 2 - secs.length(), '0');
    return (std::to_string(hours) + ":" + std::to_string(minutes) + ":" + secs);
}