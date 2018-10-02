#pragma once

#include "gen.h"
using namespace std;

#define _ARRAY_INT vector <int>

/* GetRandom returns a random integer between min and max. */
#define GetRandom( min, max ) ((rand() % (int)(((max) + 1) - (min))) + (min))

class CRandomNumbers
{
public:

    static int getRandomNumber(int iMin, int iMax);
    static _ARRAY_INT getRandomNumbers(int iMin, int iMax, int iSize, bool bUniqueOnlyFlag);

protected:

private:
    static void initialize();

};

