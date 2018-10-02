#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>

#define MAX_LED_BLOCK 6

void print_message();

void printHex(int a);
void printHex(std::string a);

void dispBitsToArr(unsigned Val, char* _array);

#endif

