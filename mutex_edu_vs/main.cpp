#include "gen.h"
#include "TimerClass.h"

/* Mutex
* https://www.youtube.com/watch?v=FaF2dADZ-Y0&list=PLQOaTSbfxUtAc_RpyDiWCHq0YTzLtVSD0&index=16
*
*/

std::mutex mtx;

void Function()
{
    TimerClass timer_;
    for (size_t i = 0; i <10; i++)
    {
        std::cout << "Hello - " << i << "\n";
    }
}

void MyPrint(char toPrintP)
{
    mtx.lock();
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t i = 0; i < 10; i++)
        {
            std::cout << toPrintP;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        std::cout << std::endl;
    }
    mtx.unlock();
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
        * sleep for 1 sec. and output time diff
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
    // std::auto_ptr <App> my_stack(new App());
    TimerClass timer_;
    try
    { 
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << "\n";

        // my_stack->Run();
        //MyPrint('*');
        //MyPrint('#');

        thread t1(MyPrint, '*');
        thread t2(MyPrint, '#');

        t1.join();
        t2.join();

        long b1 = std::clock();
        std::cout << "Time END: " << b1 << "\n\n";
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
    //system("PAUSE");
    
    return 1;
}
