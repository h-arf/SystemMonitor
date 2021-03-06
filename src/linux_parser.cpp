#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  int MemTotal,MemFree;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string line;
  string key;
  string value;
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          MemTotal=std::stoi(value);
        }
        else if (key=="MemFree:"){
          MemFree=std::stoi(value);
        }
        
      }
    }
  return (float)(MemTotal-MemFree)/MemTotal;
}

//  Read and return the system uptime
long LinuxParser::UpTime()
{
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  long a,b;
  stream>>a>>b;
  return a-b;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
//long LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<unsigned long> LinuxParser::CpuUtilization()
{
  vector<unsigned long> r;
  std::ifstream stream(kProcDirectory + kStatFilename);
  std::string temp;
  stream>>temp;
  for (int i=0;i<10;i++){
    stream>>temp;
    r.push_back(std::stoll(temp));
  }
  return r;
}

//  Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line;
  string key;
  string value;
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          #ifdef DEBUG_PRINT
          std::cerr<<key<<"="<<value<<std::endl<<line<<std::endl;
          #endif
          return std::stoi(value);
        }
      }
    }
  return -1;
}

//  Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line;
  string key;
  string value;
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          #ifdef DEBUG_PRINT
          std::cerr<<key<<"="<<value<<std::endl<<line<<std::endl;
          #endif
          return std::stoi(value);
        }
      }
    }
  return -1;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string t{};
  return stream>>t?t:"";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line;
  string key;
  int value;
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "VmSize:") {
          linestream>>value;
          return to_string((int)value/1024);
        }
      }
    }
  return "";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
int LinuxParser::Uid(int pid)
{
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line;
  string key;
  string value;
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return std::stoi(value);
        }
      }
    }
  return -1;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid){
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  int n=1;
  string t;
  while (n<23){
    stream>>t;
    if (n==22){
      if (t.size()<1)
        return -1;
      return stol(t)-UpTime();
    }
    n++;
  }
  return -1;
}

std::vector<std::string> const LinuxParser::CpuUtilization(int pid)
{
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  vector<string> r{};
  int n=1;
  string t;
  while (n<23){
    stream>>t;
    if ((n>=14&&n<18)||n==22){
      r.push_back(t);
    }
    n++;
  }
  return r;
}