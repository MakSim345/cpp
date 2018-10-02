#ifndef _NODE_LIST_H_
#define _NODE_LIST_H_
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


struct node_item 
{
    int key;
    int value;
    node_item *next_item; 
};

class Node
{
public:    
    Node(int d) 
    {
        _data = d;
        _next = NULL;
        std::string _str = "123";
    }
    //~Node();
    Node* _next;
    int   _data;    
    
    void run();
    void append(int d)
    {
        Node nw = Node (d);
        if (_next == NULL)
        {
            _next = &nw;
        }
        else
        {
            Node *n = _next;
            while ((*n)._next != NULL)
            {
                n = (*n)._next;
            }
            (*n)._next = &nw;
        }
    };
        
private:
    vector <string> matrix_array;
};


#endif
