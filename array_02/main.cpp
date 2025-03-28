#include "gen.h"
#include "utils.h"

long g_lTimeTick = 0;

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeInMS = 0;
    int RValue = false;
    int nResult = 0;
    int DelayInMiliseconds = 1000; // 1000 is one second
    CTimer mTimer;

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");

    printf("1. Time: %ld\n", mTimer.Get1msTimeMS());

    {
        // Entity02 e; // Stack allocated variable.
        // Entity02* e = new Entity02(); // Heap allocated variable!
    }

    // int* a = CreateArray();
    // printf("a = %d\n", a[9]);

    int example[5];
    int* another = new int[5]; // need a delete [] !

    for (int i = 0; i < 5; i++)
    {
        example[i] = 2;
        another[i] = 3;
    }
    // testPlayer(newPlayer);

    //printf ("Application complete.\n");
    //system ("PAUSE"); // wait for press any key in VS mode
    //return 0;

//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);

    // and this is complicated one-thread way:
    if (((mTimer.Get1msTimeMS() - LastTimeInMS) > DelayInMiliseconds - 1) || (LastTimeInMS > mTimer.Get1msTimeMS() ))
    {
        // nResult = produceRND();
        nResult = getRandomNumber();
        printf ("Time in ms: %ld.\n", mTimer.Get1msTimeMS());
        printf ("Random: %d\n", nResult);
        std::cout << "Elapsed time:" << mTimer.GetElapsedTimeMs() << endl;

#ifdef WIN32_APP
    Sleep(1000); // Sleep for 1000 milliseconds
#else
    sleep(1); // Sleep for 1 second
#endif

        LastTimeInMS = mTimer.Get1msTimeMS();
    }

    // control of endless loop (may be also in monitor.cpp)
    //if (_kbhit())  // has anything been pressed from keyboard ?
    // {
    //     RValue = true; // END mark
    // }
} while (!RValue);

printf ("Application complete.\n");
system ("PAUSE"); // wait for press any key in VS mode
return 0;

}
