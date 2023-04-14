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

class App
{
public:
    App();
    ~App();

    int Run();

    void sleep_and_count();    
    void init_random_gen();    
    int get_rnd_number(int iMin = 0, int iMax = 101);
};
