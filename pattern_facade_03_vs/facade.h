#ifndef _FACADE_H_
#define _FACADE_H_

#include "gen.h"

class A
{
public:
    void fun(){ cout << "class A complete" << endl;}
};
 
class B
{
public:
    void fun(){ cout << "class B complete" << endl;}
};


class MyFacade
{
public:
    MyFacade();
    ~MyFacade();    
    int run();
    
private:    
    A a;
    B b;    
};

#endif
