#pragma once
#include "Maze.h"
#include "Room.h"
#include "Door.h"
#include "Wall.h"
#include "MazeFactory.h"

/* *
 * 
 * Creator and default ConcreteProduct
 *
 * */

class MazeGame {
public:

    Maze* CreateMaze(MazeFactory& factory);

    //factory methods:

    virtual Maze* MakeMaze() const {
        return new Maze;
    }
    virtual Room* MakeRoom(int n) const {
        return new Room(n);
    }
    virtual Wall* MakeWall() const {
        return new Wall;
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const {
        return new Door(r1, r2);
    }
};
