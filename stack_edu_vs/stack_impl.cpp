#include "gen.h"
 // app shall create a stack consists 5 int numbers.
 
struct Node 
{
    int d;         //data
    Node *p;       //pointer to next same structure
};

//------------------------------
Node *first(int d)
{
    Node *pv=new Node;    //create a structure
    pv->d=d;              //add same data to data field
    pv->p=0;              //First element has to point to NULL
    cout << pv->d << ' '; //TRACE
    return pv;            //return self address
}
 
void push(Node **top, int d)
{
    Node *pv = new Node;       //create a structure
    pv->d = d;                 //add same data to data field
    pv->p = *top;              //New element. Linking with one on the top.
    *top = pv;                 //New element: Place to stack top;
    cout << (*top)->d << ' ';  //TRACE
}

//-----------------------------
int pop(Node **top)
{
    int temp=(*top)->d;        //Get data from top
    Node *pv=*top;             //get address of top element
    (*top) = (*top)->p;        //Put new element to a TOP
    delete pv;                 //Remove old TOP
    return temp;               //return data from old TOP
}


