#include "cube_calc.h"

using namespace std;

CubeCalc::CubeCalc()
{
    std::cout << "Hello! I will calculate a cube for you!\n";
}

CubeCalc::~CubeCalc()
{
    std::cout << "Good bye!\n";
}
    
int CubeCalc::run()
{
    std::cout << "Enter cube dimention: ";
    std::cin >> side;
    cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";
    return 1;
}

float CubeCalc::calculation(float s)
{
    return s*s*s;
}

