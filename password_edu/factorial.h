#ifndef _FACTORIAL_H_
#define _FACTORIAL_H_

#include "gen.h"

class Factorial
{
public:
    Factorial();
    ~Factorial();
    
    void run();
    
private:
    vector<string> letters;
    int genRnd(int max);
};

#endif

