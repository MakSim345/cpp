/**
 * A sample code of C++ reversing a linked list.
 * Outline: take out each node from the old list, and add it to the
 * new list in reverse-sequence.
 */

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

/*
 A linked list is a list constructed using pointers. It is not fixed in
 size and could grow and shrink while the program is running.
 
 A typical definition of list nodes contains at least two parts, both the
 content or data of each element and the pointer to the next element,
 which is shown in the figure below.
 
 +---------+
 |  Data   | -----> holds the data of this element in the list.
 +---------+
 | pointer | -----> is a pointer to the next element in the list.
 +---------+
 
 ***Attention***:
 The pointer holds the address of the next element, not the address of the
 data in the next element, even though they are the same in value sometimes.
 And It should be set to NULL while acting as the last node of the list.
 
 
 Implementation of the single linked list:
 +---------+    --->+---------+    --->+---------+
 |  Data   |    |   |  Data   |    |   |  Data   |
 +---------+    |   +---------+    |   +---------+
 | pointer |-----   | pointer |-----   | pointer |
 +---------+        +---------+        +---------+
 */

/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int _value; /* data, can be any data type, but use integer for easiness */
    Node *_pNext; /* pointer to the next node */
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : _pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : _value(val), _pNext(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* next)
    : _value(val), _pNext(next)
    {}
    
    /* Getters */
    int getValue(void)
    { return _value; }
    
    Node* getNext(void)
    { return _pNext; }
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *_pHead;
    /* pointer of tail node */
    Node *_pTail;
    
public:
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Function to append a node to the end of a linked list */
    void tailAppend(int val);
    
    /* Function to reverse the list */
    void reverse();
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
};

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    _pHead = new Node(val);
    _pTail = _pHead;
}

LinkedList::~LinkedList()
{
    /*
     * Leave it empty temporarily.
     * It will be described in detail in the example "How to delete a linkedlist".
     */
}

void LinkedList::tailAppend(int val)
{
    /* The list is empty? */
    if (_pHead == NULL) 
    {
        /* the same to create a new list with a given value */
        _pTail = _pHead = new Node(val);
    }
    else
    {
        /* Append the new node to the tail */
        _pTail->_pNext = new Node(val);
        /* Update the tail pointer */
        _pTail = _pTail->_pNext;
    }
}

void LinkedList::reverse()
{
    Node *pTempHead = _pHead;
    Node *pRestNodes = NULL;
    Node *pNextNode = NULL;
    /* The list is empty? do nothing */
    if (_pHead == NULL)
        return;
    /* The previous head node will act as the tail node after reversing */
    _pTail = _pHead;
    /* Take out the head node and make the reverse list basing on it */
    pRestNodes = _pHead->_pNext;
    
    while (pRestNodes != NULL) 
    {
        /* Step1: Take out the next node */
        pNextNode = pRestNodes;
        /* Step2: Update the pointer of rest nodes after taking out the first */
        pRestNodes = pRestNodes->_pNext;
        /* Step3: Add the taken out node to the new list */
        pNextNode->_pNext = pTempHead;
        /* Step4: Update the new temp head node */
        pTempHead = pNextNode;
        /* Repeat Step 1-4 */
    }
    _pHead = pTempHead;
    _pTail->_pNext = NULL;
}

void LinkedList::traverse_and_print()
{
    Node *p = _pHead;
    
    /* The list is empty? */
    if (_pHead == NULL) 
    {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) 
    { 
        /* while there are some more nodes left */
        /* output the value */
        cout << p->_value << " ";
        /* The pointer moves along to the next one */
        p = p->_pNext;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    /* Create a list with only one node */
    LinkedList list(1);
    /* Append 3 nodes to the end of the list */
    list.tailAppend(2);
    list.tailAppend(3);
    list.tailAppend(4);
    
    cout << "Before reversing:" << endl;
    list.traverse_and_print();
    list.reverse();
    cout << "After reversing:" << endl;
    list.traverse_and_print();
    
    return 0;
}


