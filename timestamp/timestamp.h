#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include "gen.h"
// put_time example
#include <iostream>     // std::cout
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
// #include <chrono>       // std::chrono::system_clock


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

/*-----------------------------------------------------------------------
Returns Time/Date String
-----------------------------------------------------------------------*/
std::string PrintTime(void)
{
    //char ReturnTime[100];
    //struct date d;
    //struct time t;

    //getdate(&d);
    //gettime(&t);

    /*
    sprintf(ReturnTime,"%02d/%02d/%02d %02d:%02d:%02d",
           d.da_day,d.da_mon,d.da_year,
           t.ti_hour,t.ti_min,t.ti_sec);  // timestamp
    */

    // return ReturnTime;

    std::string ReturnTime;
    std::time_t t = std::time(NULL);
    std::tm tm_info = *std::localtime(&t);
    // std::cout.imbue(std::locale("ru_RU.utf8"));
    std::put_time(&tm_info, "%c %Z");    
    //cout << "PrintTime: " << t << "\n";
    //cout << "PrintTime: " << asctime(&tm_info) << "\n";

    // return ReturnTime;
    return asctime(&tm_info);
}

#endif
