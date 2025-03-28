#include "gen.h"
#include "sleep_impl.h"

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