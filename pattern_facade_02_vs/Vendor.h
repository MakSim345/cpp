#pragma once

class Vendor
{
public:
    void submitRequestToVendor()
    {
        _state = 0;
    }
    bool checkStatus()
    {
#ifdef DEBUG
        std::cout<<"Vendor: Current State: "<<_stateToStrVendor[_state]<< std::endl;
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
        Received, VerifyInventory, GetItemFromWareHouse, PackItem, ContactCourier, Complete
    };
    int _state;

};

