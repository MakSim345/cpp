#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

#include "gen.h"

class random_generator
{
public:
 
    random_generator() { srand(time(NULL));}
    // ~random_generator();   
    int get_tick() {return 1 + rand() % 10;}

private:
    
};

#endif

