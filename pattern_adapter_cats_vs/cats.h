#ifndef _CATS_H_
#define _CATS_H_

#include "gen.h"
#include "cat_if.h"


class PedigreedCat: public iHomeCat
{
public:
    PedigreedCat()  {}
    virtual ~PedigreedCat() {}

    virtual void Meow() const
    {
        std::cout << "Myp-Myp\n";
    }        

    virtual void  Scratch() const
    {
        std::cout << "No Scratch\n";
    } 

};

class StreetCat: public iHomeCat
{
public:
    StreetCat()  {}
    virtual ~StreetCat() {}

    virtual void Meow() const
    {
        std::cout << "Xppp-Xppp\n";
    }        

    virtual void  Scratch() const
    {
        std::cout << "Scratch!!!\n";
    } 

};

#endif
