#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <windows.h>

/*
 compile with:
 >cl file_name.cpp
 * */

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void test_color()
{
    WORD Attributes = 0;

    // yellow FOREGROUND_RED | FOREGROUND_GREEN );
    // Cyan FOREGROUND_BLUE | FOREGROUND_GREEN 
    // SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
    SetConsoleColour(&Attributes,  FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    
    std::cout << "Testing a line of characters-----------\n";    
    ResetConsoleColour(Attributes);    
}

void terst_all_colors()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k;    
    // you can loop k higher to see more color choices
    for(k = 1; k < 255; k++)
    {
    // pick the colorattribute k you want
    SetConsoleTextAttribute(hConsole, k);
    std::cout << k << " I want to be nice today!" << std::endl;
    }
}

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;

    printf ("main - start\n");
    test_color();    
    printf ("main - end\n");
}    
