#pragma once

/* http://easy-coding.blogspot.com/2009/02/c-windows-unix.html */

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#include <windows.h>
#else
#include <stdlib.h>
#include <pthread.h>
#endif

namespace sys {
#ifdef WIN32
  typedef CRITICAL_SECTION mutex_t;
#else
  typedef pthread_mutex_t mutex_t;
#endif

class Mutex {
public:
  inline Mutex();

  inline ~Mutex();

  inline void Lock();

  inline void Unlock();

private:
  mutex_t __mutex;

  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

#ifdef WIN32

// Windows API

Mutex::Mutex()             { InitializeCriticalSection(&__mutex); }
Mutex::~Mutex()            { DeleteCriticalSection(&__mutex); }
void Mutex::Lock()         { EnterCriticalSection(&__mutex); }
void Mutex::Unlock()       { LeaveCriticalSection(&__mutex); }

#else // WIN32

// UNIX

Mutex::Mutex()             { pthread_mutex_init(&__mutex, NULL); }
Mutex::~Mutex()            { pthread_mutex_destroy(&__mutex); }
void Mutex::Lock()         { pthread_mutex_lock(&__mutex); }
void Mutex::Unlock()       { pthread_mutex_unlock(&__mutex); }

#endif // WIN32
}

