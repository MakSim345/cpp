#pragma once
#include "gen.h"

// Node class
class Node
{
public:
    int     data;
    Node*   next;

    // create a new node: a = new Node (1, NULL);
    Node(int x, Node* addr)
    {
        data = x;
        next = addr;
    }
};

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int x, ListNode* addr):
        val(x),
        next(addr)
    {
        // constructor
    }
};


