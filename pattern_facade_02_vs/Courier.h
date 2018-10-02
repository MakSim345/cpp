#ifndef courier_h__
#define courier_h__

#include "gen.h"

class Courier
{
public:
    void submitRequestToCourier()
    {
        _state = 0;
    }

    bool checkStatus()
    {
#ifdef DEBUG
        std::cout<<"Courier: Current State: "<<_stateToStrCourier[_state]<< std::endl;
#endif
        mySleep(500); /* Do some useful work here */
 
        _state++;
        if (_state == Complete)
            return 1;
        return 0;
    }
private:
    enum States
    {
        Received, VerifyReachbility, AssignPerson, DispatchPackage, GetDeliveryConfirmation, Complete
    };

    int _state;
};

#endif // 
