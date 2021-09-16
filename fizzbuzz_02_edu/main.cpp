#include "gen.h"

int main(int argc, char** argv)
{
    int i = 1;
    const int max_fizz_buzz = 10000;

    std::clock_t start = std::clock();
    std::cout << "START:" << start << " \n";
//=============================================================
    while(i <= max_fizz_buzz)
    {
        printf("%d", i);
        if(i%3 == 0) printf(" - fizz");
        if(i%5 == 0) printf(" - buzz");
        printf("\n");
        i++;
    }
//=============================================================
    std::clock_t duration = std::clock() - start;
    std::cout << "operation took " << duration << " clock ticks\n";

    // use seconds instead:
    std::cout << "Execution time: " << duration/double(CLOCKS_PER_SEC) << " seconds\n";

    std::cout << "END:" << std::clock() << " \n";
    return 0;
}
