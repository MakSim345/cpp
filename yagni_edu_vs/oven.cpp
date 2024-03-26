#include "oven.h"

electricOven::electricOven()
{
    std::cout << "ElectricOven object created" << std::endl;
}

electricOven::~electricOven()
{
    std::cout << "ElectricOven destroyed" << std::endl;
}

void electricOven::start()
{
    std::cout << "ElectricOven started" << std::endl;
}

void electricOven::stop()
{
    std::cout << "ElectricOven stopped" << std::endl;
}

bool electricOven::canBake()
{
    if (!isCurrency)
    {
        std::cout << "ElectricOven can NOT bake: no electricity" << std::endl;
        return false;
    }
    else
    {
        std::cout << "ElectricOven can bake!" << std::endl;
        return true;
    }
}

gasOven::gasOven()
    :_gas_level(10)
{
    // _gas_level = -10
    std::cout << "GasOven object created" << std::endl;
    std::cout << "_gas_level:" << _gas_level <<std::endl;
}

gasOven::~gasOven()
{
    std::cout << "GasOven destroyed" << std::endl;

}

void gasOven::start()
{
    std::cout << "GasOven started" << std::endl;
}

void gasOven::stop()
{
    std::cout << "GasOven stopped" << std::endl;
}

bool gasOven::canBake()
{
    if (_gas_level <= 0)
    {
        std::cout << "GasOven can NOT bake!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "GasOven can bake!" << std::endl;
        return true;
    }
}
