//============================================================
//
//
//============================================================
//
// File:           msg_print.cpp
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "msg_print.h"

msg_print::msg_print()
{
    nFrame = 59;
}

void msg_print::printTopFrame()
{
    for (int i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }
}

void msg_print::PrintInfoMessage()
{
    int i;
    printf ("\n");
    printf ("\t%c", 201);
    
    this->printTopFrame();
    
    printf ("%c\n", 187);    
    printf ("\t%c  Welcome to the Coding World!                             %c\n", 186, 186);
    printf ("\t%c  Now your file will be coded or decoded according         %c\n", 186, 186);
    printf ("\t%c  to the KEY you had set in the BAT file.                  %c\n", 186, 186);
    printf ("\t%c  It may take some time - depends of the file's size.      %c\n", 186, 186);
    printf ("\t%c  After program complete, you will see an appropriate      %c\n", 186, 186);
    printf ("\t%c  message and value of bytes which been changed.           %c\n", 186, 186);    
    printf ("\t%c  Good luck.                                               %c\n", 186, 186);
    
    printf ("\t%c", 200);
    
    this->printTopFrame();
    
    printf ("%c\n", 188);    

};

void msg_print::PrintErrorMessage()
{
    printf ("\n");
    printf ("\t%c", 201);
    
    this->printTopFrame();
    
    printf ("%c\n", 187);    
    printf ("\t%c  Welcome to the Coding World!                             %c\n", 186, 186);
    printf ("\t%c  I'm sorry, but program can not run with the data you     %c\n", 186, 186);
    printf ("\t%c  give to it. Please, check the input parameters.          %c\n", 186, 186);
    printf ("\t%c  Actually, it has to be like follow:                      %c\n", 186, 186);
    printf ("\t%c  dcript.exe <KEY> <source_file> <dest_file> [Print_info]  %c\n", 186, 186);
    printf ("\t%c  Where: KEY - is your coding key; sourse file is a text   %c\n", 186, 186);
    printf ("\t%c  you want to hide, dest - is a result file; [Print_info]  %c\n", 186, 186);
    printf ("\t%c  is an addiditional parameter and do not use it at all:-) %c\n", 186, 186);
    printf ("\t%c  Good luck.                                               %c\n", 186, 186);
    
    printf ("\t%c", 200);
    
    this->printTopFrame();
    
    printf ("%c\n", 188);    
    printf ("\nApplication complete. There was 0 iterations\n");
};

