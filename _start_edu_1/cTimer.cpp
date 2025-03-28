#include "gen.h"
#include "cTimer.h"

/*
TimerClass::TimerClass()
{
    startTime = std::chrono::high_resolution_clock::now();
}

TimerClass::~TimerClass()
{
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    float ms = duration.count() * 1000.0f;
    std::cout << "Destructor: Timer took " << ms << " ms. \n";
}

*/

/*
 * CTimer Class
 */

CTimer::CTimer() :
    isTimerStarted(false),
    ctrTimer1MsStartM(0),
    ctrTimer1MsDiffM(0)
{
    this->Start();
}

long CTimer::Get1msSinceEpoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

long CTimer::Get1msTimeMS()
{
    // get 1 ms time since the class created.
    // use milliseconds since Epoch to count.
    ctrTimer1MsDiffM = Get1msSinceEpoch() - ctrTimer1MsStartM;
    return ctrTimer1MsDiffM;
}

void CTimer::Start()
{
    startTimeM = std::chrono::high_resolution_clock::now();
    ctrTimer1MsStartM=this->Get1msSinceEpoch();
    isTimerStarted = true;
}

unsigned int CTimer::GetElapsedTimeMs() const
{
    // Returns the elapsed time in number of milliseconds
    //if (!isTimerStarted)
    //{
    //    return 0;
    //}
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (endTime - startTimeM).count();
}

uint64_t CTimer::GetElapsedTimeMks() const
{
    // Returns the elapsed time in number of milcroseconds
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>
        (endTime - startTimeM).count();
}
