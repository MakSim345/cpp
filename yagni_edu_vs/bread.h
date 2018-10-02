#ifndef _BREAD_H_
#define _BREAD_H_

#include "gen.h"
#include "oven.h"
#include "error_message.h"

class Bread
{
public:
    Bread();
    ~Bread();

private:
    float weight;
};

class BreadMaker
{
public:

    Bread* doBakeBread(ovenIf &oven);    

    int run() {return _number;}

private:
    int _number;
};

#endif
