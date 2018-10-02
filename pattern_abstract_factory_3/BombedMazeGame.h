#pragma once
#include "MazeGame.h"
#include "RoomWithABomb.h"
#include "BombedWall.h"

/*
 *
 * ConcreteCreator
 *
 */

class BombedMazeGame : public MazeGame {
public:
    BombedMazeGame();
    
    virtual Room* MakeRoom(int n) const 
        { return new RoomWithABomb(n); }
    virtual Wall* MakeWall() const
        { return new BombedWall; }
};
