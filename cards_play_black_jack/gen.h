#ifndef GEN_H
#define GEN_H
/*********************************************************************
  gen.h
**********************************************************************/
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <algorithm> // for 'shuffle'

// #include "time.h"
#include "utils.h"

using namespace std;

enum Rank {
    ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Suit{
    HEARTS, DIAMONDS, CLUBS, SPADES
};


#endif //GEN_H
