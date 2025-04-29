#include "rabbit.h"

//SuperRabbit functions:

SuperRabbit::SuperRabbit(std::string _myName, Winner *_win)
    :Animal( _myName, _win)
{

}

int SuperRabbit::move(const int newRndValP)
{
    switch (newRndValP)
    {
    case 1: case 2:
        setPos(0); // sleep
        break;
    case 3: case 4:
        setPos(9); // long jump
        break;
    case 5: case 6: case 7:
        setPos(1); // short jump
        break;
    case 8:
        setPos(-12); // long slippery
        break;
    case 9: case 10:
        setPos(-2); // short slippery
        break;
    default:
        break;
    }
    return getPosition();
}

SuperRabbit::~SuperRabbit()
{

}
