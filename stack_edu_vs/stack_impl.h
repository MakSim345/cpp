#ifndef _STACK_IMLP_H_
#define _STACK_IMLP_H_

#include "gen.h"
 // app shall create a stack consists 5 int numbers.
 
struct Node 
{
    int d;         //data
    Node *p;       //poiunter to next same structure
};

//-----------------------------
//Create first element(new)
Node *first(int d);   

// Add to stack:
void push(Node **top, int d);

//delete from stack:
int pop(Node **top);

#endif



