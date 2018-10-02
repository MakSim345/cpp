#ifndef _TODO_H_
#define _TODO_H_

#include "gen.h"

class ToDo
{
public:
    ToDo();
    ~ToDo();
    int run();

private:
    float side;
    float calculation(float s);
};

#endif

