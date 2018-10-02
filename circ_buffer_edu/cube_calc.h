#ifndef _CUBE_CALC_H_
#define _CUBE_CALC_H_

#include "gen.h"

class CubeCalc
{
public:
    CubeCalc();
    ~CubeCalc();    
    int run();
    int* getBin(unsigned Val);
    void printDigits();

private:
    float side; 
    float calculation(float s);
    int myints[7]; //= {32, 71, 12, 45, 26, 80, 53, 33};
    int DIGITS[10][8];
};

#endif
