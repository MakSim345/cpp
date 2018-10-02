#ifndef _GEN_H_
#define _GEN_H_

#define _CRT_SECURE_NO_WARNINGS

// GENERAL settings file for the project PROSTOTRON
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// Input-Output operations:
#define READ   10 // read a word from the terminal to the memory cell
#define WRITE  11 // print a word from the memory cell to the terminal

// Save-Load operations:
#define LOAD   20 //save a word from the memory cell to an accumulator
#define STORE  21 //save a word from accumulator to memory cell

// Arithmetic operations:
#define ADD      30
#define SUBTRACT 31
#define DIVIDE   32
#define MULTIPLY 33

//Brunching operations:
#define BRANCH     40
#define BRANCHNEG  41
#define BRANCHZERO 42
#define HALT       43 // Total stop

#define START_ADDRESS 0
#define MEMORY_SIZE   100

#define ASM 1
#define CMD 0

#define TRACE_ENABLED 1


enum
{
    LOAD_LEN = 5,
    SAVE_LEN = 5,
    GOTO_LEN = 5,
    PRINT_LEN= 6
};


#endif
