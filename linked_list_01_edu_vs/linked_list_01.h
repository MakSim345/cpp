#ifndef _LINKED_LIST_01_H_
#define _LINKED_LIST_01_H_
//============================================================
//
//
//============================================================
//
// File:           linked_list01.h
//
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"


struct list_item 
{
    int key;
    int value;
    list_item *next_item; 
};

class linked_list_01
{
public:    
    linked_list_01();
    ~linked_list_01();
    
    void run();
        
private:
    vector <string> matrix_array;
};


#endif
