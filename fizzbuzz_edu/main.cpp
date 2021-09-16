#include "gen.h"
#include "utils.h"
#include "fizz_buzz.h"

void simple_fuzz_buzz(int maxP)
/*
* tooks 3.33 seconds for 10000 numbers
*/
{
    int i = 1;

    while(i <= maxP)
    {
        printf("%d", i);
        if(i%3 == 0) printf(" - fizz");
        if(i%5 == 0) printf(" - buzz");
        printf("\n");
        i++;
    }
}


int main()
{
    const int max_fuzz_buzz = 10000;
    std::clock_t start = std::clock();
    std::cout << "START:" << start << " \n";
//=============================================================
    std::auto_ptr <fizz_buzz> fzbz(new fizz_buzz());
    try
    {
        fzbz->Run_Default();
        // simple_fuzz_buzz(max_fuzz_buzz);
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
//=============================================================
    std::clock_t duration = std::clock() - start;
    std::cout << "operation took " << duration << " clock ticks\n";

    // use seconds instead:
    std::cout << "Execution time: " << duration/double(CLOCKS_PER_SEC) << " seconds\n";

    std::cout << "END:" << std::clock() << " \n";

    return 1;
}

