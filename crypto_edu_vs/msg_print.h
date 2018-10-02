#ifndef _MSG_PRINT_H_
#define _MSG_PRINT_H_
//============================================================
//
//
//============================================================
//
// File:           msg_print.h
//
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class msg_print
{
public:    
    msg_print();
    ~msg_print();
    
    // void run();
    void PrintInfoMessage();
    void PrintErrorMessage();
    void printTopFrame();
        
private:    
    // vector <string> my_array;
    int nFrame;
};


#endif
