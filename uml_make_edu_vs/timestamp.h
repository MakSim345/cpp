#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include "gen.h"
#include <iomanip>
#include <ctime>

class timestamp
{
public:
    timestamp()
    {
        time_t t = time(0);   // get time now
        now = localtime( & t );
        cout << (now->tm_year + 0) << endl;
        //print_time();
        //now->tm_year = 900;
        print_time();
    }
        
    void print_time()
    {
        cout << (now->tm_year + 1900) << '-' 
            << (now->tm_mon + 1) << '-'
            << now->tm_mday << ' '
            << now->tm_hour << ':'
            << now->tm_min << ':'
            << now->tm_sec 
            << endl;

    }
private:
    struct tm * now;
    //...
};

#endif
