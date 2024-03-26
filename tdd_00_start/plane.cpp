#include "plane.h"

CropperPlane::CropperPlane()
{
    std::cout << "CropperPlane object created" << std::endl;
}

CropperPlane::~CropperPlane()
{
    std::cout << "CropperPlane destroyed" << std::endl;
}

void CropperPlane::start()
{
    std::cout << "CropperPlane started engine." << std::endl;
}

void CropperPlane::stop()
{
    std::cout << "CropperPlane stopped engine." << std::endl;
}

bool CropperPlane::canFly()
{
    if (!isFuel)
    {
        std::cout << "CropperPlane can NOT fly!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "CropperPlane can fly!" << std::endl;
        return true;
    }
}

AirForcePlane::AirForcePlane()
{
    _gas_level = -10;
    std::cout << "AirForcePlane object created" << std::endl;
    std::cout << "_gas_level:" << _gas_level <<std::endl;
}

AirForcePlane::~AirForcePlane()
{
    std::cout << "AirForcePlane destroyed" << std::endl;

}

void AirForcePlane::start()
{
    std::cout << "AirForcePlane started" << std::endl;
}

void AirForcePlane::stop()
{
    std::cout << "AirForcePlane stopped" << std::endl;
}

bool AirForcePlane::canFly()
{
    if (_gas_level <= 0)
    {
        std::cout << "AirForcePlane can NOT fly!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "AirForcePlane can fly!" << std::endl;
        return true;
    }
}
