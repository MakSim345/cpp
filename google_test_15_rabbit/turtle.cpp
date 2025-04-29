#include "turtle.h"

//--------
//SuperTurtle functions:

SuperTurtle::SuperTurtle(std::string _myName, Winner *_win)
    :Animal( _myName, _win)
{

}

int SuperTurtle::move(const int newRndValP)
{
    switch (newRndValP)
    {
     case 1: case 2: case 3: case 4: case 5:
        setPos(3); // quick moving
        break;
     case 6: case 7:
        setPos(-6); // slippery
        break;
    case 8: case 9: case 10:
        setPos(1); // moving
        break;
    default:
        break;
    }

    return getPosition();
}

SuperTurtle::~SuperTurtle()
{

}