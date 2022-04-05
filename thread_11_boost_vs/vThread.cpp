//============================================================
//
/* Purpose:   Wraps the Win32 API for thread operations.
** Comments:  This class can be used in the following 3 different ways:
** 1. Create a vThread object that represents the currently executing thread.  This is
**     accomplished by calling the constructor that takes just the threadName parameter.
**     This causes the thread's priority and quantum level to be retrieved from the 
**     Registry and applied to the thread. 
** 2. Spawn a new thread by calling the constuctor that takes the threadName, 
**     lpStartAddress, pParameter, creation and pThreadId parameters.  This creates
**     a new thread using the specified parameters and then reads and applies the 
**     thread's priority and quantum level from the Registry.
** 3. Spawn a new thread by calling the default constuctor and then the Create() method.
**     This is equivelent to #2 above.
*/
//============================================================

#include "stdafx.h"
#include "vThread.h"


vThread::~vThread()
{

}

// starting thread outside.
void vThread::start()
{
    // create a new thread       
    // CreateThread(bootThread, this, ...);
    m_hThread = CreateThread(0, 0, bootThread, (LPVOID)this, 0, 0);
}
        

