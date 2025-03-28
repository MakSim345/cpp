/*
*/

// #include <stdio>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "person.h"

//#include "I2cDrvIf.hpp"
//#include "I2cIf.hpp"

using namespace std;

static std::atomic<int> av;
static int gv;


int main()
{
    /*
    for (auto i = 0; i < 10; i++)
    {
        cout << "GetRandom: " << GetRandom(9999) << endl;
    }
    */
    testPersonMobile();
    // system("PAUSE");
    return 0;
}
