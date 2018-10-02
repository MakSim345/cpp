#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "gen.h"

struct Item 
{
    int info;
    Item* next;
};

struct auto_list 
{
   char _name[20];
   char _auto[20];
   int _number;
   auto_list* _next;
};

class my_list
{
public:    
   char name[20];
   char car[20];

   int _number;
   my_list* _next;

   void run ();
   void Add();

private:
    int var;    
};


#endif
