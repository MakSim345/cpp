#ifndef _PLANE_H_
#define _PLANE_H_

#include "gen.h"

class Plane
{
public:
    virtual ~Plane(){}

    virtual void start()=0;
    virtual void stop()=0;
    virtual bool canFly()=0;

private:
    int _plane_type;
};


class CropperPlane : public Plane
{
public:
    CropperPlane();
    ~CropperPlane();

    bool canFly();
    void start();
    void stop();

private:
    std::string mFuel; //
    std::string mColor;
    bool isFuel;
    //...
};

class AirForcePlane: public Plane
{
public:
    AirForcePlane();

    virtual ~AirForcePlane();

    virtual void start();
    virtual void stop();
    virtual bool canFly();

private:
    int _gas_level;
    std::string mColor;
    //...
};
#endif
