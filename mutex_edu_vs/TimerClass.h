#pragma once
/*********************************************************************
  
**********************************************************************/
#include "gen.h" 

class TimerClass
{
public:
    TimerClass();
    ~TimerClass();

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
    std::chrono::duration<float> duration;
};