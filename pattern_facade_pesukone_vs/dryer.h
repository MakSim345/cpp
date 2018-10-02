#ifndef _DRYER_H_
#define _DRYER_H_

#include "gen.h"

class Dryer
{
public:
    Dryer() { cout << "Dryer created" << endl;}
   ~Dryer() { cout << "Dryer complete" << endl;}

    void Dry(int _seconds, int _intencity)
    { 
        cout << "Dryer: " << _seconds  << " seconds with intencity " << _intencity << endl;
    }

private:    
    int _m_seconds;
    int _m_intencity;
};

#endif
