
#ifndef log_hpp
#define log_hpp

#include <stdio.h>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include "user.hpp"
using namespace std;

class log
{
private:
    time_t time;
    string decor(char, int);
public:
    log()
    {std::time_t time = std::time(NULL);}
    
    const tm currentDateTime();
    void write(string, string);
};

#endif /* log_hpp */
