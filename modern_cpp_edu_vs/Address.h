#pragma once
#include "gen.h"

class Address 
{
public:
    Address() {}

    Address(const string& aStreet, const string& aCity) :
        street(aStreet),
        city(aCity) 

        {
            // implementatation here...
        }

    ~Address()
    {
        cout << "Destructing Address object" << endl;
    }

    void const printData()
    {
        cout << street << " " << city << endl;
    }

private:
    string street;
    string city;
};