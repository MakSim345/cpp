#ifndef _LINKED_LIST_02_H_
#define _LINKED_LIST_02_H_
//============================================================
//
//
//============================================================
//
// File:           linked_list02.h
//
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

struct a_node
{
    int data;
    a_node *next;
};

class ItemList
{
public:
    struct ListItem 
    {
        int item;
        ListItem *next; 

        ListItem (int i, ListItem *n = NULL)
        {
            item = i;
            next = n;
        }
    };

    ItemList()
    {
        itemsCount = 0;
        first = last = NULL;
    }

    ItemList (const ItemList & src)
    {
        itemsCount = 0;
        first = last = NULL;
        AddLast(src);
    }
    ~ItemList()
    {
        ListItem *current = NULL;
        ListItem *next = first;
        while(next)
        {
            // next = next->next;
            delete current;
        }
    }
    
    int Head () const 
    {
        return first->item;
    }
/*
    int & Head () const 
    {
        return first->item;
    }
*/
    int Tail () const 
    {
        return first->item;
    }
/*
    int & Tail () const 
    {
        return first->last;
    }
*/
    void AddLast(const ItemList & src)
    {
       
    }
    
    void AddFirst(int _new_item)
    {
        ListItem *newItem = new ListItem(_new_item, this->first);
        if (!first)
        {
            last = newItem;
        }
        first = newItem;
        itemsCount++;

    }
   
    void AddLast(int _new_item)
    {
     ListItem *newItem = new ListItem(_new_item);
        if (!last)
        {
            first = newItem;
        }
        else
        {
            last->next = newItem;
        }

        last = newItem;
        itemsCount++;
    }

    int RemoveFirst();
    bool Remove(int n); // remove from list element with exact value
    void Insert(int n); // insert an element with value n;

    int GetItemCount()
    {
        return itemsCount;
    }

    std::string GetAllItemsInfo();

    int itemsCount;
    ListItem *first;
    ListItem *last;
        
private:
    vector <string> matrix_array;
};


#endif
