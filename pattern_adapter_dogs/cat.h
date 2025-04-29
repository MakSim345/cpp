#ifndef _CATS_H_
#define _CATS_H_

#include "gen.h"

// Class to be adapted:
class Cat
{
public:
    Cat()  {}
    virtual ~Cat() {}

    virtual void Meow() const
    {
        std::cout << "Meow-Meow\n";
    }
/*
    virtual void  Scratch() const
    {
        std::cout << "Scratch!!!\n";
    }
*/
};

#endif
