#ifndef _POLAR_BEAR_ADAPTER_H_
#define _POLAR_BEAR_ADAPTER_H_

#include "gen.h"
#include "cat_if.h"
#include "polar_bear.h"

class PolarBearAdapter : public iHomeCat
{
public:
    PolarBearAdapter(PolarBear &polarBear)
    : _polarBear(polarBear)
    {
    }

    virtual ~PolarBearAdapter() {}

    virtual std::string Name() const
    {
        return _polarBear.Species();
    }

    virtual void Meow() const
    {
        _polarBear.Roar();
    }

    virtual void Scratch() const
    {
        _polarBear.Claw();
    }

private:
    PolarBear &_polarBear;
};

#endif