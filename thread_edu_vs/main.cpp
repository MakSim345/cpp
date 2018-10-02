#include "gen.h"
#include "printHex.h"
#include "timer_util.h"
#include "trash.h"
#include "my_templates.h"

// #include <thread> since C++11

void doSomeWork( void )
{
    std::cout << "hello from thread..." << std::endl;
    return;
}

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    CTimer *_time = new CTimer();
    printf ("main start on time: %ld. \n", _time->GetElapsedTimeMs());
    
//*************MAIN LOOP*****************//
    cout << "\n$ > Press Any Key to exit." << std::endl;
    do
    {
        //This is simple Windows way:
        Sleep(55);

        nResult = produceRND();
        printf ("1-Time: %ld. RND: %d\n", _time->GetElapsedTimeMs(), nResult);

       //nResult = produceRND();
        //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;
            if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
            {
                RValue = true; // END mark
            }
            if (NewChar == 'd')  // pressed
            {
                if (1 == CaptureModeHex)
                    CaptureModeHex = 1;
                else
                    CaptureModeHex = 0;
            }
        }
    } while (!RValue);
    printf ("Application complete.\n");
    return 0;
}


