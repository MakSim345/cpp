#pragma once
#include <vector>
#include "Room.h"

/*
 *
 * Product
 *
 * */

class Maze 
{
    public:
        Maze();

        void AddRoom(Room*);
        Room* RoomNo(int) const;
        void PrintId();

    private:
        int id;
        // here go data structures to hold list of rooms
        std::vector<Room*> _rooms;
};
