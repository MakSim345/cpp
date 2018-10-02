#ifndef _FILTER_CALC_H_
#define _FILTER_CALC_H_

#include "gen.h"

/* Opaque buffer element type.  This would be defined by the application. */
typedef struct { unsigned int value; } ElemType;
 
/* Circular buffer object */
typedef struct 
{
    string name;
    int         size;   // maximum number of elements          
    int         start;  // index of oldest element
    int         end;    // index at which to write new element
    // ElemType   *el_array;  // vector of elements
    ElemType   el_array[10];  // array of elements
} CircularBuffer;
 
void cbInit(CircularBuffer *cb, int size);
void cbInit(CircularBuffer *cb, std::string _name, int size);
 
void cbFree(CircularBuffer *cb);
 
int cbIsFull(CircularBuffer *cb); 
 
int cbIsEmpty(CircularBuffer *cb);

/* Calculate average value: */
unsigned int cbDoFiltering(CircularBuffer *cb);

void cbPrintMe(CircularBuffer *cb);
 
/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cbWrite(CircularBuffer *cb, ElemType *elem);
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
void cbRead(CircularBuffer *cb, ElemType *elem);

#endif
