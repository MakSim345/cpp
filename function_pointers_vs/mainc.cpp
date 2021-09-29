#include "gen.h"
#include "utils.h"

/*
* Function pointers in C++
* By
* CHERNO: https://www.youtube.com/watch?v=p4sDgQ-jao4
*/


void HelloWorld()
{
    std::cout << "Hello world!" << std::endl;
}

void HelloWorldParam(int paramP)
{
    std::cout << "Hello world! Value:" << paramP << std::endl;
}

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int nTdiff = 100; // 1000 is one second

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");

    // std::cout << "enter somethig:\n";
    // std::cin.get();

    printf ("1. Time: %ld\n", Get1msTimeMS());
    msTimer t;
    volatile unsigned long my_num = 0;

    for (int i = 0; i < 5000000; i++)
    {
        // my_num++;
    }
    std::cout << "Elapsed time: " << t.elapsedMs() << " millisec" << endl;
    printf ("2. Time: %ld\n", Get1msTimeMS());

    // Note: NO parentheses in this function call.
    // We taking a memory address instead. (like: "&HelloWorld")
    // There is implicit conversion, so & is not necessary.
    auto function = HelloWorld;

    // the auto is actually this type:
    void(*cherno)();

    cherno = HelloWorld;
    cherno();

    function();

    typedef void(*HelloWorldFunction)();
    HelloWorldFunction function2 = HelloWorld;
    function2();

    // Use parameters in a function:
    typedef void(*HelloWorldParamFunction)(int);
    HelloWorldParamFunction function3 = HelloWorldParam;
    function3(34);

    // Use vectors:

    // std::vector<int> values = {1,5,4,2,3}; - this does not work in VS2010 
    std::vector<int> values;
    values.push_back(1);
    values.push_back(5);
    values.push_back(4);
    values.push_back(2);
    values.push_back(3);


    printf ("Application complete.\n");

    system ("PAUSE"); // wait for press any key in VS mode

    return 0;
//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);

    // and this is complicated one-thread way:
    if ((( Get1msTimeMS() - LastTimeInMS) > nTdiff - 1) || (LastTimeInMS > Get1msTimeMS() ))
    {
        nResult = produceRND();
        printf ("Time: %ld. Random: %d\n",Get1msTimeMS(), nResult);
        std::cout << "Elapsed time:" << t.elapsedMs() << endl;

        Sleep(1);

        LastTimeInMS = Get1msTimeMS();
    }

    // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true; // END mark
    }
} while (!RValue);

printf ("Application complete.\n");

system ("PAUSE"); // wait for press any key in VS mode

return 0;

}



