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

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';
    const int START = 4096;

    int z;
    for (z = START; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/* unsigned 8 bits  */  
typedef unsigned char      IntU8;       

/**
Container for 16 chip data bytes.
*/
typedef IntU8 EntropyChipDataArray[16];

/** 16 chip data bytes */
EntropyChipDataArray aChipDataM;

#define    ELEMENTS(tab)    (sizeof(tab) /  sizeof(tab[0]))

enum { INVALID_CHIP_DATA_BYTE = 0xcc };

EntropyChipDataArray& getChipData()
{
    for (size_t i = 0; i < ELEMENTS(aChipDataM); ++i)
    {
      aChipDataM[i] = static_cast<IntU8>(INVALID_CHIP_DATA_BYTE);
    }   
    
    return aChipDataM;
}

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();
    for (int i=0; i<=15;i++)
    {
        printf ("%d - %d\n", i, getChipData()[i]);
        printf ("%s\n", byte_to_binary(getChipData()[i]) );
    }

    bool a = true;
    printf ("a = %d\n", a);


    return 1;
}
