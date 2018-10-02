#include <iostream>
#include "gen.h"

class Engine
{

public:
    void start (void) 
    {
        cout << "Engine starts! "<< "\n";
    }

};

class Headlights
{

public:
    void turn_on (void) 
    {
        cout << "Headlights turn ON!"<< "\n";
    }

};

// This is a facade:
class Auto
{
private:
    Engine myEngine;
    Headlights myHeadlights;

public:
    void turn_ignition_key()
    {
        myHeadlights.turn_on();
        myEngine.start();
    }

};