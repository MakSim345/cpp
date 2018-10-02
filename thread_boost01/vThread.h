#ifndef _V_THREAD_H_
#define _V_THREAD_H_

#include "gen.h"
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <list>

using namespace std;

class Mutex
{
    private:
    HANDLE hMutex;
        
    public:
        
    Mutex()
    {
        // hMutex = CreateMutex(...);
    }
    
    
    virtual ~Mutex()
    {
        // DestroyObject(hMutex);
    }
    
   
    bool get(DWORD timeout=INFINITE)
    {
        return 1;
        //return (WaitForSingleObject(hMutex, timeout) == ...) ? true : false;
    }

        
    void release()
    {
        //ReleaseObject(hMutex);
    }
};

// #ifdef YS_TEST_01APR2009

/******************************************************************
** Purpose:   Wraps the Win32 API for thread operations.
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
******************************************************************/
class vThread
{
public:

    // Equivalent to LPTHREAD_START_ROUTINE
    typedef unsigned int (__stdcall *V_THREAD_ROUTINE)(void *);

    enum V_THREAD_CREATION
    {
        V_THREAD_SUSPENDED,
        V_THREAD_RUN
    };

    // Constants used to reference the thread's normal priority and quantum values.
    //static const string NORMAL_PRIORITY_NAME;
    //static const string NORMAL_QUANTUM_NAME;

    vThread(void* pParameter = NULL, const string &threadName = "")
    // vThread(void* pParameter, const string &threadName)
    {
        hSigEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        
        // init the new thread states
        init(pParameter);
    }
    
    virtual ~vThread();

//    bool Terminate( unsigned long exitCode );

    bool Wait( unsigned long timeout=0xFFFFFFFF );
    long Resume();
    long Suspend();

    int  GetPriority();
    bool SetPriority( const string &priorityName );

    int  GetQuantum();
    bool SetQuantum( const string &quantumName );

    HANDLE GetHandle() { return m_hThread; }
    void   ClearHandle() { m_hThread = NULL; }

    // send signal to thread
    void signal(DWORD dwSignalMask)
    {
        // note: not thread-safe
        lock->get();
        signals |= dwSignalMask;
        lock->release();
        SetEvent(hSigEvent);
    }   
    
    // starting thread outside.
    void start();
        
protected:
   
    // thread main routine - overload this!
    virtual DWORD run() = 0;

    // thread init routine - overload this!
    virtual void init(void *pParam) {}
    
    
    // Wait until a signal is received
    DWORD waitSignal(DWORD dwWaitForSignals = 0xffffffff, DWORD timeoutMs = INFINITE)
    {
        // bug here: what if received multiple non-wanted signals, timeout starts each time again
        do
        {
            if (WaitForSingleObject(hSigEvent, timeoutMs) == WAIT_TIMEOUT) break;
        } while (signals & dwWaitForSignals);   // loop until some expected signal received
        
        return signals;
    }    
          
private:
    
    DWORD signals;
    HANDLE hSigEvent;
    Mutex *lock;
    void *pStartParam;
    void CloseThreadHandle();
    void BuildRegKeyName();

    /// thread bootstrap routine
    static DWORD __stdcall bootThread(LPVOID pArg)
    {
        vThread *ptr = (vThread*)pArg;
        return ptr->run();
    }
    
    // Handle to the thread.
    HANDLE m_hThread;

    // Unique name that indetifies the thread. Used to look up the thread's parameters
    // in the registry.
    string m_threadName;

    // String indicating the registry location where the parameters for the thread are
    // specified.
    string m_keyName;

    vThread(const vThread &);
    vThread &operator=(const vThread &);
};

#ifdef MARKUS_SOURCE_CODE

#pragma once
#pragma warning( disable : 4201 4514 )

class vThread
{
public:
    /// constructor - creates a new thread
    vThread(void *pArg, BOOL startSuspended);
    virtual ~vThread();

    //thread states
    enum EThreadState {SUSPENDED, STARTED, FINISHED};

    /// Request the thread to stop
    virtual void stop(BOOL waitUntilStopped);

    /// Get thread state (suspended, started, finished)
    virtual EThreadState getState();
 
protected:
    /// thread main routine
    virtual DWORD run(void *pArg);

private:
    void *_pArg;
    HANDLE hThread;

    /// thread run state (suspended, started, finished)
    EThreadState state;

    /// thread bootstrap routine
    static DWORD __stdcall initThread(LPVOID pArg);
};
#endif



// some comments

#ifdef EXAMPLE_TEST_20_AUG_2008
int g_MyData;

Mutex g_MyMutex;

myThread1;
myThread2;


#define SIG_KILL_YOURSELF    0x0001
#define SIF_MESSAGE_RECEIVED 0x0002
    

void IncreaseMyData()
{
    g_MyMutex->get();
    g_MyData ++;
    g_MyMutex->release();
    
    myThread1->signal(NEW_MESSAGE_RECEIVED);
}



class MyThread : vThread
{
    protected:
        // overloaded thread init routine:
        void init(void *pParam)
        {
            // my own thread initialization
        }


        // overloaded thread main routine:
        DWORD run()
        {
            // my own thread routine
            while (1)
            {
                Sleep(10);
                
                g_MyMutex->get();
                g_MyData ++;
                g_MyMutex->release();
            }
            
            return 0;
        }
    
};
#endif //EXAMPLE_TEST_20_AUG_2008

#endif //  _V_THREAD_H_
