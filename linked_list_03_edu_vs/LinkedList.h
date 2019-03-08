#pragma once

#include "gen.h"

#include "Node.h"

class LinkedList
{
private:
    Node* head;

public:
    // initialize Linked list with a NULL head:
    LinkedList() { head = NULL; }

    // determinate if list is empty:
    bool isEmpty()
    {
        if (head == NULL) return 1;
        else return 0;
    }

    // add an item to LinkedList:
    void pushNode(int val)
    {
        Node* n = new Node(val, NULL);
        // n->data = val;
        n->next = head;
        head = n;
    }

    // add an item to LinkedList:
    void addNode(int val)
    {
        if (head == NULL)
        {
            head = new Node(val, NULL);
        }
        else
        {
            Node* n = head;
            while(n->next != NULL) 
            {
                n = n->next;
            }
            n->next = new Node(val, NULL);
        }
    }

    // print a linked list
    void printMe()
    {
        std::cout << "[";
        if(head != NULL)
        {
            if(head->next == NULL)
            {
                std::cout << head->data << "-" << head->next;
            }
            else
            {
                Node* n = head;
                while(n->next != NULL)
                {
                    std::cout << "0x" << n << ":" << n->data << "-0x" << n->next << " -> " ;
                    n = n->next;
                }
                std::cout << n->data;
            }
        }
        std::cout << "]\n";
    }

};
