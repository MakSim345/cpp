#include "filter_calc.h"

using namespace std;

void cbInit(CircularBuffer *cb, int size) 
{
    cb->size  = size; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    cb->name = "Nan";

    // cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}

void cbInit(CircularBuffer *cb, std::string _name, int size)
{
    cb->name = _name;
    cb->size  = size + 1; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;

    // cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}
 
void cbFree(CircularBuffer *cb) 
{
    // free(cb->elems); /* OK if null */ 
}
 
int cbIsFull(CircularBuffer *cb) 
{
    return (cb->end + 1) % cb->size == cb->start; 
}
 
int cbIsEmpty(CircularBuffer *cb) 
{
    return cb->end == cb->start; 
}
 
/* 
 * Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). 
*/
void cbWrite(CircularBuffer *cb, ElemType *elem) 
{
    printf("Write to [%d] - %d\n", cb->end, elem->value);        
    printf("%s : \n", cb->name.c_str());
    // std::cout << cb->name;
    // printf("Filter : cb->size = %d\n", cb->size);
    cb->el_array[cb->end] = *elem;
    cb->end = (cb->end + 1) % cb->size;
    
    if (cb->end == cb->start)
    {
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
    }
}
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
void cbRead(CircularBuffer *cb, ElemType *elem)
{
    *elem = cb->el_array[cb->start];
    cb->start = (cb->start + 1) % cb->size;
}

/* Calculate average value: */
unsigned int cbDoFiltering(CircularBuffer *cb)
{
    int start_point = cb->start; // save start point
    unsigned int _retVal = 0;
    int elem_counter = 0;
    ElemType elem;
    
    while(cb->end != cb->start)
    { 
     //printf("Filter : i = %d\n", i);
     //printf("Filter : cb->size = %d\n", cb->size);
     elem = cb->el_array[cb->start];
     cb->start = (cb->start + 1) % cb->size;
     // elem = cb->elems[i];
     // printf("Filter : %d\n", elem.value);
     _retVal = _retVal + elem.value;
     elem_counter++;
    }
    _retVal = _retVal/elem_counter;
    
    // restore start point
    cb->start = start_point;

    return _retVal;
}

/* Calculate average value: */
void cbPrintMe(CircularBuffer *cb)
{
    /*
    int start_point = cb->start; // save start point    
    int elem_counter = 0;
    ElemType elem;
    
    while(cb->end != cb->start)
    { 
     //printf("Filter : i = %d\n", i);
     //printf("Filter : cb->size = %d\n", cb->size);
     elem = cb->elems[cb->start];
     cb->start = (cb->start + 1) % cb->size;
     // elem = cb->elems[i];
     printf(" %d ", elem.value);
     elem_counter++;
    }
    printf("\n");     
    // restore start point
    cb->start = start_point;
    */
    int i = 0;    
    printf("end = %d\n", cb->end);    
    for (i = 0; i <= cb->size - 1; i++)
    {
        int next_elem = (int)cb->el_array[i].value;
        
        if (i == cb->end)
            printf("[%d] - %d <--\n", i, next_elem);
        else    
            printf("[%d] - %d\n", i, next_elem);
    }
    printf ("\n");
}
