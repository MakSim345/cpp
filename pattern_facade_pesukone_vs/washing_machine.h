#ifndef _WASHING_MACHINE_H_
#define _WASHING_MACHINE_H_

#include "gen.h"
#include "water_management.h"
#include "dryer.h"
#include "engine.h"
#include "thermo.h"


class WashingMashine
{
public:
    WashingMashine() 
    { 
        cout << "WashingMashine created" << endl;
        water = new WaterManagement();        
        thermo = new Thermo();
        engine = new Engine();
        dryer = new Dryer();
    }
   
   ~WashingMashine() 
    { 
    cout << "Dryer complete" << endl;
    }
    
    void wash_cotton()
    {
        // cotton
        water->FillWater(10);
        thermo->WarmUp(70);
        engine->Rotate();
        engine->Rotate();
        engine->Rotate();
        engine->Stop();
        water->EmptyWater();
        dryer->Dry(30, 1000);
        water->FillWater(15);
        thermo->WarmUp(50);
        engine->Rotate();
        engine->Rotate();
        engine->Rotate();
        engine->Stop();
        water->EmptyWater();
        dryer->Dry(60, 1501);
    }

    void start_machine()
    { 
        cout << "WashingMashine: start " << endl;
        this->wash_cotton();
        cout << "WashingMashine: stop " << endl;        
    }
    
private:    
    WaterManagement *water;
    Thermo *thermo;
    Engine *engine;
    Dryer *dryer;
};

#endif
