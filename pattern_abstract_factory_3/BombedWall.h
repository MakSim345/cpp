#pragma once
#include "Wall.h"

class BombedWall : public Wall {
    public:
        BombedWall();

        virtual void Enter() { }
};

