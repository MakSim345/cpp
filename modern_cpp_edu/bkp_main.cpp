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

inline float cube(const float s) {return s*s*s;}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world!\n";
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
//    std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
//    cube_calc->run();    
    return 1;
}
