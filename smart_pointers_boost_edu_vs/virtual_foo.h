#ifndef _VIRTUAL_FOO_H_
#define _VIRTUAL_FOO_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class ClassA
{
public:
    ClassA() 
    {
        data = 10;
    }

    virtual void set()
    {
        std::cout << "ClassA is increasing" << std::endl;
        data++;
    }

    int get()
    {
        set();
        return data;
    }

protected:
    int data;
};

class ClassB : public ClassA
{
public:
    void set()
    {
        std::cout << "ClassB is decreasing" << std::endl;
        data--;
    }
};


class A 
{
public:
    virtual void Foo (int n = 10) 
    {
        cout << "A::Foo, n = " << n << endl;
    }
};

class B : public A 
{
public:
    virtual void Foo (int n = 20) 
    {
        cout << "B::Foo, n = " << n << endl;
    }
};

#endif
