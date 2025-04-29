#ifndef _RABBIT_H_
#define _RABBIT_H_

#include "gen.h"
#include "animal.h"
#include "winner.h"

class SuperRabbit : public Animal
{
public:
    SuperRabbit(std::string _myName, Winner *_win);
   ~SuperRabbit();
    int move(const int newRndValP);

private:

};

#endif
