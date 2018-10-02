
#include "ElectricOven.h"

ElectricOven::ElectricOven()
{
    // gCounter = 0;
    mColor = "Red";
    gCounter++;
    setId(gCounter);
    // std::cout << "id: " << getId() << std::endl;
    std::cout << "ElectricOven object id: " << getId() << " created. Color: " << mColor << std::endl;
    
    // std::cout << "gCounter: " << getCount() << std::endl;
}

ElectricOven::~ElectricOven()
{    
    std::cout << "ElectricOven id: " << getId() << " destroyed." << std::endl;
}

std::string ElectricOven::getColor()
{
    std::cout << "call getColor() for ElectricOven object: " << getId() << std::endl;
    return mColor;
}

void ElectricOven::start()
{
    std::cout << "ElectricOven started" << std::endl;
}

void ElectricOven::stop()
{
    std::cout << "ElectricOven stopped" << std::endl;
}

bool ElectricOven::canBake()
{
    if (!isCurrency)
    {
        std::cout << "ElectricOven can NOT bake!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "ElectricOven can bake!" << std::endl;
        return true;
    }
}

