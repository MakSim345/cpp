#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <ctime>

using namespace std;

// inline float cube(const float s) {return s*s*s;}

class ExampleApp
{
public:
    int Run()
    {
        std::cout << "Hello cruel world!\n";
        return 0;
    }
    ~ExampleApp()
    {
        std::cout << "Good bye!\n";
    }

};

class CubeCalc
{
public:
    CubeCalc()
    {
        std::cout << "Hello! I will calculate a cube for you!\n";
    }
    ~CubeCalc()
    {
        std::cout << "Good bye!\n";
    }

    int run()
    {
        std::cout << "Enter cube dimention: ";
        std::cin >> cubeSideP;

        long a = std::clock();

        std::cout << "Cube with side " << cubeSideP << " is equal to " << calcCube(cubeSideP) << "\n";

        std::cout << "Time Start: " << a << "\n";

        for (int i = 0; i < 1000000; i++)
        {
            // std::cout << i << "\n";
            calcCube(i);
            lastParamCtr = i;
        }

        std::cout << "Cube with side " << lastParamCtr << " is equal to " << calcCube(lastParamCtr) << "\n";

        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        return 1;
    }

private:
    float cubeSideP;
    long lastParamCtr;

    float calcCube(float sideP)
    {
        return sideP * sideP * sideP;
    }

};

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    std::unique_ptr <CubeCalc> cube_calc(new CubeCalc());
    cube_calc->run();
    return 1;
}
