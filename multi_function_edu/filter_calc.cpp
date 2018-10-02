#include "filter_calc.h"

using namespace std;

void cbInit(CircularBuffer *cb, int size) 
{
#ifdef YS_USE_NAME_    
    strcpy(cb->name, "Nan");
#endif    
    cb->size  = size + 1; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    // cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}

// void cbInit(CircularBuffer *cb, string _name, int size)
void cbInit(CircularBuffer *cb, const char * _name, int size)
{
    // cb->name = _name;
#ifdef YS_USE_NAME_    
    strcpy(cb->name, _name);
#endif    
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
    // printf("%s : \n", cb->name.c_str());
#ifdef YS_USE_NAME_    
    printf("%s : \n", cb->name);
#endif    
    // printf("Filter : cb->size = %d\n", cb->size);
    cb->elems[cb->end] = *elem;
    cb->end = (cb->end + 1) % cb->size;
    
    if (cb->end == cb->start)
    {
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
    }
}
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
void cbRead(CircularBuffer *cb, ElemType *elem)
{
    *elem = cb->elems[cb->start];
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
     elem = cb->elems[cb->start];
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
}
