#include <iostream>
#include "utils.h"

#define ASSERT_Y(condition, message) {     \
    if ( !(condition) ){                   \
        std::cout << "ASSERT FAILED:";     \
        exit (EXIT_FAILURE);               \
    }                                      \
    else                                   \
        std::cout << "ASSERT PASSED!:";    \
}

        //std::cout << "ASSERT FAILED:" <<   \
        //#condition << message << std:endl; \

int main()
{
    int a = 11;
    std::cout << a << std::endl;
    ASSERT_Y ((a > 10), "error!!");
    print_message();
    return 0;
}

