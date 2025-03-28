#pragma once
#include "gen.h"


class FlyBehaviorIf
{
public:
    virtual void fly() = 0;
};

class FlyCanDo: public FlyBehaviorIf
{
public:
    void fly() { cout << "Flying hight!" << endl; }
};

class FlyNoWay: public FlyBehaviorIf
{
public:
    void fly() { cout << "I can not fly!" << endl; }
};

