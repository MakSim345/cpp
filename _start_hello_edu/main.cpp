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
        std::cin >> side;
        
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
/*
        for (int i = 0; i < 1000000; i++)
        {
            long _number = my_rnd->getRandomNumber(100, 10000000);
            int _lenght_name =  my_rnd->getRandomNumber(3, 7);
            std::string _name = my_name->genPass(_lenght_name);

            pb->add_data_to_file(_name, _number);
        }
  */      

        cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";    
        return 1;
    }

private:
    float side; 

    float calculation(float s)
    {
        return s*s*s;
    }

};

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    cube_calc->run();    
    return 1;
}
