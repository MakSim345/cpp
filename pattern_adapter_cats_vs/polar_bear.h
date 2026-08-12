#ifndef _POLAR_BEAR_H_
#define _POLAR_BEAR_H_

#include "gen.h"

class PolarBear
{
public:
    PolarBear()
    : _species("Ursus maritimus arcticus")
    {
    }

    virtual ~PolarBear() {}

    virtual void Roar() const
    {
        std::cout << "Deep Arctic roar!\n";
    }

    virtual void Claw() const
    {
        std::cout << "Massive arctic claw swipe!\n";
    }

    virtual bool hasNightVision() const
    {
        return true;
    }

    virtual std::string Species() const
    {
        return _species;
    }

private:
    std::string _species;
};

#endif