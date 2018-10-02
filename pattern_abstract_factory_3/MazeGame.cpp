#include "MazeGame.h"
#include "MazeFactory.h"

Maze* MazeGame::CreateMaze(MazeFactory& aMazeFactory) {
    Maze* aMaze = aMazeFactory.MakeMaze();

    Room* r1 = aMazeFactory.MakeRoom(1);
    Room* r2 = aMazeFactory.MakeRoom(2);
    Door* aDoor = aMazeFactory.MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(NORTH, aMazeFactory.MakeWall());
    r1->SetSide(EAST,  aDoor);
    r1->SetSide(SOUTH, aMazeFactory.MakeWall());
    r1->SetSide(WEST,  aMazeFactory.MakeWall());

    r2->SetSide(NORTH, aMazeFactory.MakeWall());
    r2->SetSide(EAST,  aMazeFactory.MakeWall());
    r2->SetSide(SOUTH, aMazeFactory.MakeWall());
    r2->SetSide(WEST,  aDoor);

    return aMaze;
}
