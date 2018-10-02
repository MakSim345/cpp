#pragma once

#include "gen.h"

class classAbstractBase 
{ // Abstract class
public:
    classAbstractBase ( void ) { std::cout << "Init: object of the classAbstractBase.\n"; }

    virtual void Abstr ( void ) = 0; // Pure virtual function
    void         fun   ( void ) { std::cout << "No realization will inherit!\n"; }

    ~classAbstractBase () { std::cout << "classAbstractBase call destructor.\n"; }
};

class classDerivedAbstract : public classAbstractBase 
{
public:
    classDerivedAbstract ( void ) { std::cout << "Init object of the classDerivedAbstract!\n"; }

    void Abstr ( void ){ std::cout << " call function classDerivedAbstract.Abstr();\n"; } //function implementation
    void fun   ( void ){ std::cout << " call function classDerivedAbstract.fun()\n"; }

    //~CB () {} // Неверно для абстр. кл. ~CB(){ ~CA(); } 
    ~classDerivedAbstract () { std::cout << "classDerivedAbstract call destructor.\n"; }
};

class baseClassA
{
public:
    baseClassA() 
    {
        data = 10;
    }

    virtual void set()
    {
        std::cout << "baseClassA is increasing" << std::endl;
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

class derivedClassB : public baseClassA
{
public:
    void set()
    {
        std::cout << "derivedClassB is decreasing" << std::endl;
        data--;
    }
};


class baseClassFoo 
{
public:
    virtual void Foo (int n = 10) 
    {
        cout << "baseClassFoo::Foo, n = " << n << endl;
    }
};

class derivedClassFoo : public baseClassFoo 
{
public:
    virtual void Foo (int n = 20) 
    {
        cout << "derivedClassFoo::Foo, n = " << n << endl;
    }
};

