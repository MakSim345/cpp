#include "gen.h"

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


int main()
{
    try
    {
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << "\n";


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

    //std::cout << "\nPress ENTER to exit...\n";
    //cin.get();

    // this PAUSE will give a info text - press any key to continue, etc.
    system("PAUSE");

    // this pause is silent. You have to know to press any key.
    // system("pause>0");

    return 1;
}
