#include "example.h"

int MAC (int addOneP, int addTwoP, int& rSumP)
{
    rSumP += addOneP * addTwoP;
    return rSumP;
}

int Square (int x)
{
    // return x*2;
    return x*x;
}
