#pragma once

#include "gen.h"

class Entity
{
public:
    Entity() : sNameM("Unknown") {};
    Entity(const String& nameP) : sNameM(nameP) {};

    // ~Entity();
    const String& GetName() const { return sNameM; }

private:
    String sNameM;
};


int GetRandom(int maxP)
{
    static bool isFirstTime = true;
    if (isFirstTime)
    {
        srand(time(NULL));
        isFirstTime = false;
    }
    auto retVal = rand() % maxP;
    return retVal;
}

void hello()
{
    std::cout <<  "Hello world, I'm a thread!" << std::endl;
}
