#ifndef _V_CLASS_H_
#define _V_CLASS_H_
//============================================================
//
//
//============================================================
//
// File:           vClass.h
// Project:        SW
//
// Author:         YS /
//
//============================================================
// Description:
//============================================================
#include "gen.h" 

class SummatorIf
{
public:
    virtual ~SummatorIf() {}

    virtual int getA() = 0;
    virtual int sum1() = 0;
    virtual int sum2() = 0;
};

//============================================================
class SummatorImpl : public SummatorIf
{
    int a;
    static int b;

public:
    SummatorImpl() { a = 0; }
    ~SummatorImpl() { a = 0; }
    
    int getA() { return a; }
    int getB() { return b; }

    int sum1() { return a+b; }
    int sum2() { return getA() + getB(); }
};

#endif 
