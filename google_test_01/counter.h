#pragma once

#include "gen.h"

class Counter
{
public:
    Counter();    	
    ~Counter();
    int Increment();
    int Decrement();
    // print the current counter value to STDOUT
    void PrintMe() const;
    
private:    
    int counterM;
};



