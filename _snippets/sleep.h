#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <conio.h> // for kbhit()
#else
#include <unistd.h>
#endif

#include <thread>

void multiPlatformSleep(unsigned int milliseconds);
void Sleep_(unsigned int milliseconds);



/*------------------------Implementation-------------------*/
void multiPlatformSleep(unsigned int milliseconds)
{
#ifdef _WIN32
    // Windows Sleep function takes milliseconds
    Sleep(milliseconds);
#else
    // Unix-based systems use usleep, which takes microseconds
    usleep(milliseconds * 1000);
#endif
}

void Sleep_(unsigned int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
