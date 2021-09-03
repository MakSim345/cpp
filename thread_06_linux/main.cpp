#include <iostream>
#include <stdint.h>
#include "utils.h"
#include <condition_variable>
#include <thread>
#include <chrono>
#include <sstream>

using namespace std;

/*
 *
 * 2018-FEB. A multi thread example with an error.
 * It is using C++ 14.
 *
*/

struct My_Semaphore_Class
{
    std::mutex mutex_m;
    std::condition_variable condition_variable_m;
    int counter_m;
    typedef std::unique_lock<std::mutex> My_LOCK_Type;

    My_Semaphore_Class() : counter_m{} {}

    void acquire()
    {
        My_LOCK_Type l(mutex_m);
        ++counter_m;
    }

    void release()
    {
        {
            My_LOCK_Type l(mutex_m);
            if (counter_m > 0)
            {
                --counter_m;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
        condition_variable_m.notify_all();
    }

    void wait()
    {
        My_LOCK_Type l(mutex_m);
        condition_variable_m.wait(l, [&]{return counter_m == 0; });
    }
};

void forwardToAnotherThread()
{
    std::thread* treadM{nullptr};
    {
        My_Semaphore_Class MySemaforeM;
        MySemaforeM.acquire();
        treadM = new std::thread([&]{MySemaforeM.release();});
        MySemaforeM.wait();
    }
    treadM->join();
    delete treadM;
}

int main()
{
    std::thread* thread_array[800];
    for (auto& p: thread_array)
    {
        p = new std::thread(&forwardToAnotherThread);
    }

    for (auto& p: thread_array)
    {
        p->join();
        delete p;
    }

    return 0;
}
