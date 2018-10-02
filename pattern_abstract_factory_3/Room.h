#pragma once
#include "gen.h"
#include "MapSite.h"

class Room : public MapSite {
    public:
        Room(int);

        MapSite* GetSide(Direction) const;
        void SetSide(Direction, MapSite*);

        virtual void Enter() { }

    protected:
        MapSite* _sides[4];
        int _roomNumber;
};
