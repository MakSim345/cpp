#include "stdafx.h"
#include <stdio.h>
#include "myThread.h"

int gVariable;

MyThread::MyThread(int num)
{   
    number = num;
    printf ("Thread %d init.\n", number);
}

MyThread::~MyThread()
{
    // destructor
    printf ("Thread %d was killed!!!!\n", number);
}

// overloaded thread init routine:
void MyThread::init(void *pParam)
{
    // my own thread initialization
    int i = 0;
}

void MyThread::getFlag(int *pVar)
{
    // int *mP = NULL;
    pFlag = pVar;
}

void MyThread::ChangeFlag(int pVar)
{
    printf ("mP = %d\n", *pFlag);
    (*pFlag)++;
    printf ("mP = %d\n", *pFlag);
}

void MyThread::ChangeVariable(int &pVar)
{
    printf ("Before pVar = %d\n", pVar);
    pVar ++;
    printf ("After  pVar = %d\n", pVar);
}

void MyThread::CopyVariable(int &pVar)
{
    // int &mP = pVar;
    int &mP = pVar;
    printf ("mP = %d\n", mP);
    mP++;
    printf ("mP = %d\n", mP);
    // pVar ++;
}

// overloaded thread main routine:
DWORD MyThread::run()
{
    // my own thread routine
    int i = 0;
    // while (1)
    for (i=0; i < 10; i++)
    {
        //Sleep(100);
        // i++;
        // gVariable++;
        ChangeFlag(0);
        printf ("Thread %d is running (%d) Changing gVariable to %d\n", number, i, gVariable);
        //g_MyMutex->get();
        //g_MyData ++;
        //g_MyMutex->release();
    }
    printf ("Thread %d made %d iterations\n", number, i);
    return 0;
}
