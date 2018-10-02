#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>

#define MAX_LED_BLOCK 6

#define CHAR_F_DEC_NO 0xFF
#define CHAR_L_DEC_NO 0xCC

void print_message();
void set_number_int(int _LED_BLOCK, int _to_write);

void set_alpha(int _LED_DIGIT, int _char_to_write);
void set_digit_int(int _LED_DIGIT, int _to_write);

void printHex(int a);
void printHex(std::string a);

void dispBitsToArr(unsigned Val, char* _array);

#endif

