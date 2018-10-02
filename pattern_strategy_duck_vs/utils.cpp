#include "utils.h"

void print_message()
{
    std::cout << "This is a native C++ program." << std::endl;
}

void printHex(int a)
{
    std::cout << std::hex << "0x" << a << "\n";
}

void printHex(std::string a)
{
    unsigned int k;
    for (int i = 0; i<a.size(); i++)
    {
        k = (unsigned int)a[i];
        std::cout << " 0x" << std::hex << std::uppercase  << k;        
        // cout << hex << k;
    }
    std::cout << "\n";
}

/*==============================================================================
  Function   : dispBitsToArr()
  Purpose    : print bits to a given array
  Params     : value to print, char array
  Return     : none
  ==============================================================================*/
void dispBitsToArr(unsigned Val, char* _array)
{
    unsigned BIT = 7;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
    int nPrintRes = 1;

    //if (nPrintRes)
    //   fprintf (fi, "Val = %d(0x%X)\n", Val, Val);

    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? '1' : '0' ;
        _array[c-1] = nBin;
        Val <<= 1;

        if ((c%9 == 0) && nPrintRes)
        {
            _array[c-1] = ' ';
        }
    }

    /* usage:
    char _array_bit[9] = {'0','0','0','0','0','0','0','0','\0'};
    dispBitsToArr(RCON, _array_bit);        
    printf("_array_bit after: \n");
    for (int i=0; i<16; i++)
    {
        // printf ("[%d] = 0x%X\n", i, _array_bit[i]);
        printf ("%c", _array_bit[i]);
    }
    */
}
