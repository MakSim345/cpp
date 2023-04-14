#pragma once

#include "gen.h"
using namespace std;

#define _ARRAY_INT vector <int>

class CRandomNumbers
{
public:

    static int getRandomNumber(int iMin, int iMax);
    static _ARRAY_INT getRandomNumbers(int iMin, int iMax, int iSize, bool bUniqueOnlyFlag);

protected:

private:
    static void initialize();

};

