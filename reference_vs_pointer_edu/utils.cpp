#include "utils.h"

// global variables for LED dispaly:
// array of numbers:       0     1     2      3     4     5    6      7    8     9
// int seven_led_array[20] ={0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};
int seven_led_array[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void print_message()
{
    std::cout << "This is a native C++ program." << std::endl;
}

void set_number_int(int _LED_BLOCK, int _to_write)
{
    printf("\n--------------------------\n");
    printf("set_number_int. incoming number is: %d, 0x%X, ", _to_write, _to_write);     
    
    char _array_bit[16] = {'0'};
    dispBitsToArr((unsigned int)_to_write, _array_bit);    
    for (int i=0; i<16; i++)
    {
        // printf ("[%d] = 0x%X\n", i, _array_bit[i]);
        printf ("%c", _array_bit[i]);
    }

    int firstDigit = (_to_write - _to_write % 10)/10; // To use decilitres as input
    int secondDigit = _to_write % 10; // To fix rounding    
    
    printf("\n");
    printf("first  - %d 0x%X\n", firstDigit, firstDigit); 
    printf("second - %d 0x%X\n", secondDigit, firstDigit); 
    
    // perform range check for _LED_BLOCK: up to 3.
    if (_LED_BLOCK >= MAX_LED_BLOCK)
        _LED_BLOCK = MAX_LED_BLOCK;
    
    // if no-decode mode set for all segments:
    firstDigit = seven_led_array[firstDigit];
    secondDigit = seven_led_array[secondDigit];

    int leftLED = (_LED_BLOCK * 2) - 1;
    int rightLED = _LED_BLOCK * 2;

    // if number has more than 2 digit indicate 'FL' instead:    
    if (_to_write > 99)
    {
        //set_alpha(leftLED, CHAR_F_DEC_NO);
        //set_alpha(rightLED, CHAR_L_DEC_NO);
        set_alpha(leftLED, 'F');
        set_alpha(rightLED, 'L');
    }
    else if (_to_write < 0)
    {
        set_alpha(leftLED, '-');
        set_alpha(rightLED, '-');
    }
    else
    {
        printf("\nfirst - 0x%X\n", firstDigit); 
        printf("second- 0x%X\n", secondDigit); 
        //    printf ("Val = %d(0x%X)\n", Val, Val);
        set_digit_int(leftLED, firstDigit);
        set_digit_int(rightLED, secondDigit);
    }
}

void set_alpha(int _LED_DIGIT, int _char_to_write)
{
    // std::cout << "sa1. set_alpha:" << _char_to_write <<  std::endl;
    // printf("set_alpha. digit %d: -%d- \n", _LED_DIGIT, _char_to_write);
    // printf("set_alpha. digit %d: -0x%X- \n", _LED_DIGIT, _char_to_write);
    printf("[%c] ", _char_to_write);
}

void set_digit_int(int _LED_DIGIT, int _to_write)
{
   // std::cout << "sd1. set_digit_int" << _to_write << std::endl;
   // printf("set_digit_int. digit %n: -%n- \n", _LED_DIGIT, _to_write); 
   // printf("set_digit_int. digit %d: -0x%X- \n", _LED_DIGIT, _to_write); 
   // printf("-0x%X- ",  _to_write); 
   //printf("set_digit_int: %d\n", _LED_DIGIT); 
   //printf("set_digit_int: 0x%X\n", _to_write); 
   printf("[%X] ",  _to_write); 
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
