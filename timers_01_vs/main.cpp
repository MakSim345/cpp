#include "gen.h"
#include "timer.h"

/* Timing by Cherno
* https://www.youtube.com/watch?v=oEx5vGNFrLk
*
*/
void Function()
{
    // TimerClass timerM;
    CTimer timerM;
    unsigned long ctrTimerStart = timerM.Get1msTimeMS();
    unsigned long ctrDiff = 0;

    for (size_t i = 0; i <5; i++)
    {
        // std::cout << "Hello - " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << i << " -ms     :" << timerM.GetElapsedTimeMs() << std::endl;
        std::cout << i << " -mks    :" << timerM.GetElapsedTimeMks() << std::endl;
        std::cout << i << " -get1Ms :" << timerM.Get1msTimeMS() << std::endl;
        //ctrDiff = timerM.Get1msTimeMS() - ctrTimerStart;
        printf("1 ms (unsigned long): %lu \n", timerM.Get1msTimeMS());
        // ctrTimerStart = timerM.Get1msTimeMS();
    }
}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \n";
        cout << '\n';

        return 0;
    }

    void sleep_and_count()
    {
        /*
        * sleep for 1 sec. and output time difference
        */
        auto startTime = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(1s);
        auto endTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = endTime - startTime;
        std::cout << duration.count() << " sec." << std::endl;
    }

    App()
    {
        init_random_gen();
    }

    void init_random_gen()
    {
        srand((unsigned)time(0));
        rand();
        return;
    }

    int get_rnd_number(int iMin=0, int iMax=101)
    {
        int _tmp_rand_value = 0;
        int _retValue = 0;

        _tmp_rand_value = rand();
        _retValue = ( iMin + int( (iMax - iMin + 1) * _tmp_rand_value /(RAND_MAX + 1.0) ) );
        return _retValue;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    CTimer cTimerCtr;
    std::unique_ptr <App> my_stack(new App());
    try
    {
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << " : " << cTimerCtr.GetElapsedTimeMs() <<"\n";

        my_stack->Run();

        Function();

        my_stack->sleep_and_count();

        long b1 = std::clock();
        std::cout << "Time END: " << b1 << " : " << cTimerCtr.GetElapsedTimeMs() <<"\n\n";
        std::cout << "Open file Time TOTAL: " << (b1-a1)/1000.0 << " sec.\n";

    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }
    */

    //std::cout << "\nPress any key to exit...\n";
    // system("PAUSE");

    return 1;
}
