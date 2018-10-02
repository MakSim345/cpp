#ifndef _ROOM_H_
#define _ROOM_H_

#include "gen.h"

class room
{
public:

    room(int n);
    room();

    ~room()
    {
        _number = 0;
    }

    void setNumber(int newNumber)
    {
        _number = newNumber;
    }

    int getNumber()
    {
        return this->_number;
    }

    int _number;
};


#endif
