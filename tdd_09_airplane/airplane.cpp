#include "airplane.h"

bool Airplane::canFly()
{

    std::cout << "Airplane can fly\n";
    return true;
}

Airplane::Airplane()
{
    std::cout << "class Airplane created\n";
}

/*
Airplane::~Airplane()
{
    std::cout << "class Airplane destroyed\n";
}

void start()
{
    std::cout << "class Airplane START\n";
}

void stop()
{
    std::cout << "class Airplane STOP\n";
}

*/
