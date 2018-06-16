
#include "log.hpp"
#include <iostream>
//#include <time.h>

const tm log::currentDateTime(){
    string date;
    std::time_t t = std::time(0);   
    std::tm* now = std::localtime(&t);
   
    return *now;
}

void log::write(string who, string action){
    tm date;
    date = currentDateTime();
    ofstream ofile;
    ofile.open("register.log", ios::app);
    ofile << decor('-', 11) << '\n';
    ofile << who << " \n";
    ofile << action << " \n";
    ofile << (date.tm_year + 1900) << '-'
    << (date.tm_mon + 1) << '-'
    <<  date.tm_mday << " "
    <<  date.tm_hour << ':'
    <<  date.tm_min << ':'
    << date.tm_sec << "\n";
    ofile.close();
}

string log::decor(char ch, int q){
    string line;
    for(int i=0; i <= q; i++){
        line += ch;
    }
    line += " || ";
    
    for(int i=0; i <= q; i++){
        line += ch;
    }
    return line;
}
