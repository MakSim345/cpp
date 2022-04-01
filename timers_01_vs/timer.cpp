#include "gen.h"
#include "timer.h"

TimerClass::TimerClass()
{
    startTime = std::chrono::high_resolution_clock::now();
}

TimerClass::~TimerClass()
{
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    float ms = duration.count() * 1000.0f;
    std::cout << "Timer took " << ms << " ms. \n";
}
