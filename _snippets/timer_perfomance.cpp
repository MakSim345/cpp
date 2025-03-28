#include <iostream>
#include "utils.h"
#include <ctime>
#include <cstdio>
// #include <chrono>

using namespace std;

class TimerClass
{
public:
    TimerClass()
    {
        startTime = std::chrono::high_resolution_clock::now();
    }
   ~TimerClass()
    {
        endTime = std::chrono::high_resolution_clock::now();
        duration = endTime - startTime;
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << " ms. \n";
    }


private:
    std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
    std::chrono::duration<float> duration;
};

namespace
{
    class empty { }; // even empty classes take up 1 byte of space, minimum

    void on_stack()
    {
        int i;
    }

    void on_heap()
    {
        int* i = new int;
        delete i;
    }
}

int test_one()
{
    std::clock_t start = std::clock();
    std::cout << "START:" << start << " \n";
    for (int i = 0; i < 100000; ++i)
    {
        empty e;
    }
    std::clock_t duration = std::clock() - start;
    std::cout << "stack allocation took " << duration << " clock ticks\n";
    start = std::clock();

    for (int i = 0; i < 100000; ++i)
    {
        empty* e = new empty;
        delete e;
    };

    duration = std::clock() - start;

    std::cout << "heap allocation took " << duration << " clock ticks\n";
    std::cout << "END:" << std::clock() << " \n";

    return 1;
}

int main()
{
    std::clock_t start = std::clock();
    std::cout << "START:" << start << " \n";
    //auto begin = std::chrono::system_clock::now();
    for (int i = 0; i < 1000000000; ++i)
        on_stack();
    //auto end = std::chrono::system_clock::now();
    //std::printf("on_stack took %f seconds\n", std::chrono::duration<double>(end - begin).count());

    std::clock_t duration = std::clock() - start;
    std::cout << "stack allocation took " << duration << " clock ticks\n";

    start = std::clock();

    //begin = std::chrono::system_clock::now();
    for (int i = 0; i < 1000000000; ++i)
        on_heap();
    //end = std::chrono::system_clock::now();
    //std::printf("on_heap took %f seconds\n", std::chrono::duration<double>(end - begin).count());
    duration = std::clock() - start;
    std::cout << "heap allocation took " << duration << " clock ticks\n";

    // use seconds instead:
    std::cout << "Execution time " << " took " << duration/double(CLOCKS_PER_SEC) << " seconds\n";

    std::cout << "END:" << std::clock() << " \n";

    return 0;
}

#include <iostream>
#include <chrono>

int main()
{
    // Start measuring total application runtime
    auto totalStart = std::chrono::high_resolution_clock::now();

    // Example: Loop with iterations
    int numIterations = 10; // Number of iterations in the loop

    for (int i = 0; i < numIterations; ++i)
    {
        // Start measuring time for this iteration
        auto iterationStart = std::chrono::high_resolution_clock::now();

        // Simulate some work (e.g., computation or I/O)
        // Replace this with your actual logic
        std::cout << "Processing iteration " << i + 1 << "..." << std::endl;
        for (int j = 0; j < 1000000; ++j)
        {
            volatile int x = j * j; // Dummy computation to simulate work
        }

        // End measuring time for this iteration
        auto iterationEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> iterationDuration = iterationEnd - iterationStart;

        // Output the time taken for this iteration
        std::cout << "Iteration " << i + 1 << " took " << iterationDuration.count() << " ms" << std::endl;
    }

    // End measuring total application runtime
    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> totalDuration = totalEnd - totalStart;

    // Output the total runtime of the application
    std::cout << "Total application runtime: " << totalDuration.count() << " ms" << std::endl;

    return 0;
}
