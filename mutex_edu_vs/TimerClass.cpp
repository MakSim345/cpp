#include "gen.h"
#include "TimerClass.h"

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


App::App()
{
    init_random_gen();
}

int App::Run()
{
    std::cout << "Hello cruel world! \n";
    cout << '\n';
    return 0;
}

void App::sleep_and_count()
{
    /*sleep for 1 sec and output the time difference */

    auto startTime = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = endTime - startTime;
    std::cout << duration.count() << " sec." << std::endl;
}

void App::init_random_gen()
{
    srand((unsigned)time(0));
    rand();
    return;
}

int App::get_rnd_number(int iMin, int iMax)
{
    int _tmp_rand_value = 0;
    int _retValue = 0;

    _tmp_rand_value = rand();
    _retValue = (iMin + int((iMax - iMin + 1) * _tmp_rand_value / (RAND_MAX + 1.0)));
    return _retValue;
}

App::~App()
{
    std::cout << "\nGood bye!\n";
}
