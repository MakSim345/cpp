#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Maze::Maze() 
{
    id = rand() % 100 + 1;
    srand(id);
}

void Maze::AddRoom(Room* room) 
{
    _rooms.push_back(room);
}

void Maze::PrintId() 
{
    std::cout << "This maze is maze " << id << "\n";
}
