#include <iostream>
#include "utils.h"
#include <ctime>
#include <cstdio>
// #include <chrono>

using namespace std;

class Foo
{
    public:
    Foo() { std::cout << "Foo's constructor" << std::endl; }
};
class Bar : public Foo
{
    public:
    Bar() { std::cout << "Bar's constructor" << std::endl; }
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
    std::cout << "END:" << std::clock() << " \n";
    
    return 0;
}


