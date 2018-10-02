#ifndef orderingteam_h__
#define orderingteam_h__

#include "gen.h"

class OrderingTeam
{
public:
    void submitRequestToOrderTeam()
    {
        _state = 0;
    }
    bool checkStatus()
    {
#ifdef DEBUG
        std::cout<<"OrderingTeam: Current State: "<<_stateToStrOrderTeam[_state]<< std::endl;
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
        Received, VerifyPayment, ContactVendor, Complete
    };
    int _state;
};

#endif //orderingteam_h__