#ifndef _PLANE_H_
#define _PLANE_H_

#include "gen.h"

class Plane
{
public:
    virtual ~Plane() = default;

    virtual void start()=0;
    virtual void stop()=0;
    virtual bool canFly()=0;

private:
    int planeTypeM;
};


class CropperPlane : public Plane
{
public:
    explicit CropperPlane();
    ~CropperPlane() override;

    bool canFly() override;
    void start() override;
    void stop() override;

private:
    std::string mFuel;
    std::string mColor;
    bool isFuelM;
};

class AirForcePlane: public Plane
{
public:
    explicit AirForcePlane();
    ~AirForcePlane() override;

    void start() override;
    void stop() override;
    bool canFly() override;

private:
    int gasLevelM;
    std::string colorM;
};
#endif
