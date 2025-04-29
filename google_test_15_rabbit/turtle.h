#ifndef _TURTLE_H_
#define _TURTLE_H_

#include "gen.h"
#include "winner.h"
#include "animal.h"

class SuperTurtle : public Animal
{
public:
    SuperTurtle(std::string _myName, Winner *_win);
   ~SuperTurtle();

    int move(const int newRndValP);

private:

};

#endif
