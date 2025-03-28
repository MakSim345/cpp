#ifndef _WATER_MANAGEMENT_H_
#define _WATER_MANAGEMENT_H_

#include "gen.h"

class WaterManagement
{

public:
    WaterManagement() { cout << "WaterManagement created" << endl;}
   ~WaterManagement() { cout << "WaterManagement complete" << endl;}

    void FillWater(int _liters)
    {
        cout << "WaterManagement: Fill tank with "<< _liters  << " liters of water." << endl;
        _m_liters = _liters;
    }

    void EmptyWater()
    {
        cout << "WaterManagement: Empty water tank" << endl;
    }

private:
    int _m_liters;

};

#endif
