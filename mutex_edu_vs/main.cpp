#include "gen.h"
#include "TimerClass.h"

// Note: remove this mutex and see the rubbish output
#define USE_MUTEX_FOR_PRINT

#ifdef USE_MUTEX_FOR_PRINT
    std::mutex globalMutexForPrint;
#endif // USE_MUTEX_FOR_PRINT

void Function()
{
    // TimerClass timer_;
    for (size_t i = 0; i <10; i++)
    {
        std::cout << "Hello - " << i << "\n";
    }
}

void printFunctionForThread(char toPrintP)
{
#ifdef USE_MUTEX_FOR_PRINT
    globalMutexForPrint.lock();
#endif // USE_MUTEX_FOR_PRINT
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t i = 0; i < 10; i++)
        {
            std::cout << toPrintP;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        std::cout << std::endl;
    }
#ifdef USE_MUTEX_FOR_PRINT
    globalMutexForPrint.unlock();
#endif // USE_MUTEX_FOR_PRINT
}

int main()
{
    // std::auto_ptr <App> my_stack(new App());
    App* my_stack = new App();
    my_stack->Run();

    // TimerClass timer_;
    try
    {
        // long a1 = std::clock();
        auto startTimeStamp = std::chrono::high_resolution_clock::now();
        // std::cout << "Time Start: " << a1 << "\n";
        //printFunctionForThread('*');
        //printFunctionForThread('#');

        thread threadToRun_01(printFunctionForThread, '*');
        thread threadToRun_02(printFunctionForThread, '#');

        threadToRun_01.join();
        threadToRun_02.join();

        // long b1 = std::clock();
        auto currentTimeStamp = std::chrono::high_resolution_clock::now();
        // std::cout << "Time END: " << b1 << "\n\n";
        std::chrono::duration<float> duration = currentTimeStamp - startTimeStamp;
        std::cout << "Application took " << duration.count() << " seconds to run." << std::endl;
        // std::cout << "Open file Time TOTAL: " << (b1-a1)/1000.0 << " sec.\n";

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
    system("PAUSE");

    return 1;
}
