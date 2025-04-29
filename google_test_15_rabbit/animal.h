#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include "gen.h"
#include "winner.h"

class Animal
{
public:
    Animal(std::string _myName, Winner *_win);
    virtual ~Animal() = default;

    char getChar() {return firstCharNameM;}
    int getPosition() {return nPositionM;}
    void setPos(int nPos);
    virtual int move(int newRndValP) = 0;

private:
    char firstCharNameM;
    int nPositionM;
    std::string strNameM;
    Winner *winner;
};

#endif
