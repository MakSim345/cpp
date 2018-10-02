//============================================================
//
// Copyright (c) 2015
//
//============================================================
//
// File:           my_templates.cpp
// Project:
//
// Author:         YS
//
//============================================================
// Description:
// Timer class
//============================================================
#include "my_templates.h"

using namespace std;



// Ret Val:
// true, ok
// false, item was not added
template <typename T>
bool Stack<T>::push(const T value)
{
    if (top == size - 1)
    {
        return false; // full Stack!
    }

    top++;
    stackPtr[top] = value; // push

    return true;
}

template <typename T>
bool Stack<T>::pop()
{
    if (top == - 1)
        return false; // Stack is empty

    stackPtr[top] = 0; // remove item
    top--;

    return true; }

// print screen
template <typename T>
void Stack<T>::printStack()
{
    for (int ix = size -1; ix >= 0; ix--)
        cout << "|" << setw(4) << stackPtr[ix] << endl;
}

/*
template <class T>
void printVector(vector <int> _mv, const int count)
{
    return;
}
*/
