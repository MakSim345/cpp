#pragma once
#include "Room.h"
#include "gen.h"

class RoomWithABomb : public Room {
    public:
        RoomWithABomb(int);

        virtual void Enter() { }
};
