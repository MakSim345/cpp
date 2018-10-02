#include "cube_calc.h"

using namespace std;
/*----------------------------------------------------------------*/
CubeCalc::CubeCalc()
{
    std::cout << "Hello! I will calculate a cube for you!\n";
    /*  const byte DIGITS[10][8] = {
    //A  B  C  D  E  F  G  H
    { 1, 1, 1, 1, 1, 1, 0, 0 }, // 0 - 252
    { 0, 1, 1, 0, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1, 0 }, // 2
    { 1, 1, 1, 1, 0, 0, 1, 0 }, // 3 
    { 0, 1, 1, 0, 0, 1, 1, 0 }, // 4
    { 1, 0, 1, 1, 0, 1, 1, 0 }, // 5
    { 1, 0, 1, 1, 1, 1, 1, 0 }, // 6
    { 1, 1, 1, 0, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
    { 1, 1, 1, 1, 0, 1, 1, 0 }  // 9
    };
    */
    unsigned _my_val = 252;
    
    int* bin_led = getBin(_my_val);
    
    std::cout <<"\nResult: \n";
    for (int i = 0; i<10; i++)
    {        
        std::cout << i << " - " << bin_led[i] << "\n";
        
        for (int j=0; j<7; j++)
        {
            DIGITS[i][j] = bin_led[i];
        }
    }

    printDigits();
}

void CubeCalc::printDigits()
{
    std::cout <<"\n printDigits Result: \n";
    for (int i = 0; i<10; i++)
    {        
        std::cout << i << " - ";
        for (int j=0; j<7; j++)
        {
            std::cout << " " << DIGITS[i][j];
        }
        std::cout << "\n";
    }
}

int* CubeCalc::getBin(unsigned Val)
{
    unsigned BIT = 7;
    //unsigned BIT = 15;
    //unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
    int*  ret_val;
    //if (nPrintRes)
    printf ("Val = %d(0x%X)\n", Val, Val);
 
    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
     
        //if (nPrintRes)
        printf ("%d", nBin);
        ret_val[c-1] = nBin;

        Val<<=1;
     
        //if ((c%8 == 0) && nPrintRes)
        //    printf (" ");       
    }
    return ret_val;
    //if (nPrintRes)
    //    printf ("\n");
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

