#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "gen.h"

class Engine
{
public:
    Engine(){ cout << "Engine created" << endl;}
   ~Engine(){ cout << "Engine complete" << endl;}

    void Rotate()
    { 
        cout << "Engine: start rotation" << endl;
    }

    void Stop()
    { 
        cout << "Engine: stop rotation" << endl;
    }
    
private:    
    int _m_liters;
};

#endif
