#ifndef _THERMO_H_
#define _THERMO_H_

#include "gen.h"

class Thermo
{
public:
    Thermo(){ cout << "Thermo created" << endl;}
   ~Thermo(){ cout << "Thermo complete" << endl;}

    void WarmUp(int _dergrees)
    { 
        cout << "WarmUp: water to "<< _dergrees << " dergrees." << endl;
        _m_dergrees = _dergrees;
    }
        
private:    
    int _m_dergrees;
};

#endif
