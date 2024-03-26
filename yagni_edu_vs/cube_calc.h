#ifndef _CUBE_CALC_H_
#define _CUBE_CALC_H_

#include "gen.h"

class CubeCalc
{
public:
    CubeCalc();
    ~CubeCalc();
    int run();

private:
    float side;
    float calculation(float s);
};

#endif
