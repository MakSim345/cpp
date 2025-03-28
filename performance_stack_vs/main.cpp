#include "gen.h"
#include "utils.h"

class Foo
{
    public:
    Foo()
        { std::cout << "Foo's constructor" << std::endl; }
};

class Bar : public Foo
{
    public:
    Bar()
        { std::cout << "Bar's constructor" << std::endl; }
};

namespace MyNamespace
{
    class Empty { }; // even empty classes take up 1 byte of space, minimum

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
        MyNamespace::Empty e;
    }
    std::clock_t duration = std::clock() - start;
    std::cout << "stack allocation took " << duration << " clock ticks\n";
    start = std::clock();

    for (int i = 0; i < 100000; ++i)
    {
        MyNamespace::Empty* e = new MyNamespace::Empty;
        delete e;
    };

    duration = std::clock() - start;

    std::cout << "heap allocation took " << duration << " clock ticks\n";
    std::cout << "END:" << std::clock() << " \n";

    return 1;
}

int main()
{
    auto cycle_counter = 1000000000;
    std::clock_t start = std::clock();
    std::cout << "Application start. Time :" << start << " \n";
    std::cout << "Will count " << cycle_counter << " allocations from stack\n";

    // auto begin = std::chrono::system_clock::now();

    for (int i = 0; i < cycle_counter; ++i)
        MyNamespace::on_stack();
    // auto end = std::chrono::system_clock::now();
    // std::printf("on_stack took %f seconds\n", std::chrono::duration<double>(end - begin).count());

    std::clock_t duration = std::clock() - start;
    std::cout << "- stack allocation took " << duration << " clock ticks\n";

    std::cout << "Next - start heap allocation for " << cycle_counter << ". Please wait...\n";
    start = std::clock();

    //begin = std::chrono::system_clock::now();
    for (int i = 0; i < cycle_counter; ++i)
        MyNamespace::on_heap();
    //end = std::chrono::system_clock::now();
    //std::printf("on_heap took %f seconds\n", std::chrono::duration<double>(end - begin).count());
    duration = std::clock() - start;
    std::cout << "- heap allocation took " << duration << " clock ticks\n";
    std::cout << "END:" << std::clock() << " \n";

    return 0;
}


