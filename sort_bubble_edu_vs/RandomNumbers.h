//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#ifndef _RANDOM_NUMBERS_H_
#define _RANDOM_NUMBERS_H_

#include "gen.h"

// #define _ARRAY_OF_INT vector <int>

class RandomNumbers
{
public:
    static int getRandomNumber(int iMin, int iMax);
    // static _ARRAY_OF_INT getRandomNumbers(int iMin, int iMax, int iSize, bool bUniqueOnlyFlag);
    static vector <int> getRandomNumbers(int iMin, int iMax, int iSize, bool bUniqueOnlyFlag);

private:
    static void initialize();
};

#endif
