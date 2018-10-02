"The Boost.threads library"

Just a few years ago it was uncommon for a program to be written with multiple threads of execution. Today Internet server applications run multiple threads of execution to efficiently handle multiple client connections. To maximize throughput, transaction servers execute services on separate threads. GUI applications perform lengthy operations in a separate thread to keep the user interface responsive.
The list goes on.

The C++ Standard doesn’t mention threads, leaving programmers to wonder whether it’s even possible to write multithreaded C++ programs. Though it is not possible to write standards-compliant multithreaded  programs, programmers none the less write multithreaded programs in C++ using the libraries provided by their OS that expose the system’s support for threads. However, there are at least two major problems with doing this: these libraries are almost universally C libraries and require careful use in C++, and each OS provides its own set of libraries for handling multithreaded support. Therefore, the resulting code is not only non-standard, but also non-portable [1]. Boost.Threads is a library designed to address both problems.

Boost [2] is an organization started by members of the C++ Standards Committee Library Working Group to develop new source libraries for C++. Its current membership includes approximately 2,000 members. Many libraries can be found in the Boost source distribution [3]. To make these libraries thread-safe, Boost.Threads was created.

Many C++ experts provided input to the design of Boost.Threads. The interface was designed from the ground up and is not just a simple wrapper around any C threading API. Many features of C++ (such as the existence of constructors/destructors, function objects, and templates) were fully utilized to make the interface more flexible. The current implementation works for POSIX, Win32, and Macintosh Carbon platforms.

"Thread Creation"

The boost::thread class represents a thread of execution in the same way the std::fstream class represents a file. The default constructor creates an instance representing the current thread of execution. An overloaded constructor takes a function object called with no arguments and returning nothing. This constructor starts a new thread of execution, which in turn calls the function object.

At first it appears that this design is less useful than the typical C approach to creating a thread where a void pointer can be passed to the routine called by the new thread, which allows data to be passed. However, because Boost.Threads uses a function object instead of just a function pointer, it is possible for the function object to carry data needed by the thread. This approach is actually more flexible and is type safe. When combined with functional libraries, such as Boost.Bind, this design actually allows you to easily pass any amount of data to the newly created thread.

Currently, not a lot can be done with a thread object created in Boost.Threads. In fact only two operations can be performed. Thread objects can easily be compared for equality or inequality using  the == and != operators to verify if they refer to the same thread of execution, and you can wait for  a thread to complete by calling boost::thread::join. Other threading libraries allow you to perform other operations with a thread (for example, set its priority or even cancel it). However, because 
these operations don’t easily map into portable interfaces, research is being done to determine how they can be added to Boost.Threads.

Listing One illustrates a very simple use of the boost::thread class. A new thread is created that simply writes "Hello World" out to std::cout, while the main thread waits for it to complete.

Listing One: The boost::thread class

#include <boost/thread/thread.hpp>
#include <iostream>
 
void hello()
{
  std::cout <<
    "Hello world, I'm a thread!"
    << std::endl;
}
 
int main(int argc, char* argv[])
{
  boost::thread thrd(&hello);
  thrd.join();
  return 0;
}

Mutexes

Anyone who has written a multithreaded program understands how critical it is for multiple threads not to access shared resources at the same time. If one thread tries to change the value of shared data at the same time as another thread tries to read the value, the result is undefined behavior. To prevent this fromhappening, make use of some special primitive types and operations. The most fundamental of these typesis known as a mutex (the abbreviation for "mutual exclusion"). A mutex allows only a single thread accessto a shared resource at one time. When a thread needs to access the shared resource, it must first "lock" the mutex. If any other thread has already locked the mutex, this operation waits for the other thread tounlock the mutex first, thus ensuring that only a single thread has access to the shared resource at a time.

The mutex concept has several variations. Two large categories of mutexes that Boost.Threads supports include the simple mutex and the recursive mutex. A simple mutex can only be locked once. If the same thread tries to lock a mutex twice, it deadlocks, which indicates that the thread will wait forever. With a recursivemutex, a single thread may lock a mutex several times and must unlock the mutex the same number of times to allowanother thread to lock the mutex.

Within these two broad categories of mutexes, there are other variations on how a thread can lock the mutex. A thread may attempt to lock a mutex in three ways:

-	Try and lock the mutex by waiting until no other thread has the mutex locked.
-	Try and lock the mutex by returning immediately if any other thread has the mutex locked.
-	Try and lock the mutex by waiting until no other thread has the mutex locked or until a specified amount of time has elapsed.

It appears that the best possible mutex type is a recursive type that allows all three forms of locking. 

However, overhead is involved with each variation, so Boost.Threads allows you to pick the most efficient mutex type for your specific needs. This leaves Boost.Threads with six mutex types, listed in order of preference based on efficiency: boost::mutex, boost::try_mutex, boost::timed_mutex, boost::recursive_mutex, boost::recursive_try_mutex, and boost::recursive_timed_mutex.

Deadlock may occur if every time a mutex is locked it is not subsequently unlocked. This is the most common possible error, so Boost.Threads is designed to make this impossible (or at least very difficult). No direct access to operations for locking and unlocking any of the mutex types is available. Instead, mutex classes define nested typedefs for types that implement the RAII (Resource Acquisition in Initialization) 
idiom for locking and unlocking a mutex. This is known as the Scoped Lock [4] pattern. To construct one of these types, pass in a reference to a mutex. The constructor locks the mutex and the destructor unlocks it. C++ language rules ensure the destructor will always be called, so even when an exception is thrown, the mutex will always be unlocked properly.

This pattern helps to ensure proper usage of a mutex. However, be aware that although the Scoped Lock pattern ensures that the mutex is unlocked, it does not ensure that any shared resources remain in a valid state if an exception is thrown; so just as with programming for a single thread of execution, ensure that exceptions don’t leave the program in an inconsistent state. Also, the locking objects must not be passed to another thread, as they maintain state that’s not protected from such usage.

Listing Two illustrates a very simple use of the boost::mutex class. Two new threads are created, which loop 10 times, writing out an id and the current loop count to std::cout, while the main thread waits for both to complete. The std::cout object is a shared resource, so each thread uses a global mutex to ensure that only one thread at a time attempts to write to it.

Listing Two: The boost::mutex class.
	
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
 
boost::mutex io_mutex;
 
struct count
{
  count(int id) : id(id) { }
 
  void operator()()
  {
    for (int i = 0; i < 10; ++i)
    {
      boost::mutex::scoped_lock lock(io_mutex);
      std::cout << id << ": " << i << std::endl;
    }
  }
 
  int id;
};
 
int main(int argc, char* argv[])
{
  boost::thread thrd1(count(1));
  boost::thread thrd2(count(2));
  thrd1.join();
  thrd2.join();
  return 0;
}

Many users will note that passing data to the thread in Listing Two required writing a function object by hand. Although the code is trivial, it can be tedious writing this code every time. There is an easier solution, however. Functional libraries allow you to create new function objects by binding another function object with data that will be passed to it when called. Listing Three shows how the Boost.Bind library can be used to simplify the code from Listing Two by removing the need for a hand-coded function 
object.

Listing Three: Using the Boost.Bind library to simplify the code in Listing Two
	
// This program is identical to
// listing2.cpp except that it
// uses Boost.Bind to simplify
// the creation of a thread that
// takes data.
 
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>
 
boost::mutex io_mutex;
 
void count(int id)
{
  for (int i = 0; i < 10; ++i)
  {
    boost::mutex::scoped_lock
      lock(io_mutex);
    std::cout << id << ": " <<
      i << std::endl;
  }
}
 
int main(int argc, char* argv[])
{
  boost::thread thrd1(
    boost::bind(&count, 1));
  boost::thread thrd2(
    boost::bind(&count, 2));
  thrd1.join();
  thrd2.join();
  return 0;
}

Condition Variables

Sometimes it’s not enough to lock a shared resource and use it. Sometimes the shared resource needs to be in some specific state before it can be used. For example, a thread may try and pull data off of a stack, waiting for data to arrive if none is present. A mutex is not enough to allow for this type of synchronization. Another synchronization type, known as a condition variable, can be used in this case.

A condition variable is always used in conjunction with a mutex and the shared resource(s). A thread first locks the mutex and then verifies that the shared resource is in a state that can be safely used in the  manner needed. If it’s not in the state needed, the thread waits on the condition variable. This operation causes the mutex to be unlocked during the wait so that another thread can actually change the state of 
the shared resource. It also ensures that the mutex is locked when the thread returns from the wait operation. When another thread changes the state of the shared resource, it needs to notify the threads that may be waiting on the condition variable, enabling them to return from the wait operation.

Listing Four illustrates a very simple use of the boost::condition class. A class is defined implementing a bounded buffer, a container with a fixed size allowing FIFO input and output. This buffer is made thread-safe internally through the use of a boost::mutex. The put and get operations use a condition variable to ensure that a thread waits for the buffer to be in the state needed to complete the operation.

Two threads are created, one that puts 100 integers into this buffer and the other pulling the integers back out. The bounded buffer can only hold 10 integers at one time, so the two threads wait for the other thread periodically. To verify that it is happening, the put and get operations output diagnostic strings to std::cout. Finally, the main thread waits for both threads to complete.

Listing Four: The boost::condition class
	
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>
 
const int BUF_SIZE = 10;
const int ITERS = 100;
 
boost::mutex io_mutex;
 
class buffer
{
public:
  typedef boost::mutex::scoped_lock
    scoped_lock;
     
  buffer()
    : p(0), c(0), full(0)
  {
  }
     
  void put(int m)
  {
    scoped_lock lock(mutex);
    if (full == BUF_SIZE)
    {
      {
        boost::mutex::scoped_lock
          lock(io_mutex);
        std::cout <<
          "Buffer is full. Waiting..."
          << std::endl;
      }
      while (full == BUF_SIZE)
        cond.wait(lock);
    }
    buf[p] = m;
    p = (p+1) % BUF_SIZE;
    ++full;
    cond.notify_one();
  }
 
  int get()
  {
    scoped_lock lk(mutex);
    if (full == 0)
    {
      {
        boost::mutex::scoped_lock
          lock(io_mutex);
        std::cout <<
          "Buffer is empty. Waiting..."
          << std::endl;
      }
      while (full == 0)
        cond.wait(lk);
    }
    int i = buf[c];
    c = (c+1) % BUF_SIZE;
    --full;
    cond.notify_one();
    return i;
  }
     
private:
  boost::mutex mutex;
  boost::condition cond;
  unsigned int p, c, full;
  int buf[BUF_SIZE];
};
 
buffer buf;
 
void writer()
{
  for (int n = 0; n < ITERS; ++n)
  {
    {
      boost::mutex::scoped_lock
        lock(io_mutex);
      std::cout << "sending: "
        << n << std::endl;
    }
    buf.put(n);
  }
}
 
void reader()
{
  for (int x = 0; x < ITERS; ++x)
  {
    int n = buf.get();
    {
      boost::mutex::scoped_lock
        lock(io_mutex);
      std::cout << "received: "
        << n << std::endl;
    }
  }
}
     
int main(int argc, char* argv[])
{
  boost::thread thrd1(&reader);
  boost::thread thrd2(&writer);
  thrd1.join();
  thrd2.join();
  return 0;
}

Thread Local Storage

Many functions are not implemented to be reentrant. This means that it is unsafe to call the functionwhile another thread is calling the same function. A non-reentrant function holds static data over successive calls or returns a pointer to static data. For example, std::strtok is not reentrant because it uses static data to hold the string to be broken into tokens.

A non-reentrant function can be made into a reentrant function using two approaches. One approach is tochange the interface so that the function takes a pointer or reference to a data type that can be used in place of the static data previously used. For example, POSIX defines strtok_r, a reentrant variant of std::strtok, which takes an extra char** parameter that’s used instead of static data. This solution is simple and gives the best possible performance; however, it means changing the public interface, which potentially means changing a lot of code. The other approach leaves the public interface as is and replaces the static data with thread local storage (sometimes referred to as thread-specific storage).

Thread local storage is data that’s associated with a specific thread (the current thread). Multithreading libraries give access to thread local storage through an interface that allows access to the current thread’s instance of the data. Every thread gets its own instance of this data, so there’s never an issue with concurrent access. However, access to thread local storage is slower than access to static or local data; therefore it’s not always the best solution. However, it’s the only solution available
when it’s essential not to change the public interface.

Boost.Threads provides access to thread local storage through the smart pointer boost::thread_specific_ptr. The first time every thread tries to access an instance of this smart pointer, it has a NULL value, so code should be written to check for this and initialize the pointer on first use. The Boost.Threads library ensures that the data stored in thread local storage is cleaned up when the thread exits.

Listing Five illustrates a very simple use of the boost::thread_specific_ptr class. Two new threads are created to initialize the thread local storage and then loop 10 times incrementing the integer contained in the smart pointer and writing the result to std::cout (which is synchronized with a mutex because it is a shared resource). The main thread then waits for these two threads to complete. The output of this example clearly shows that each thread is operating on its own instance of data, even though both are using the same boost::thread_specific_ptr.

Listing Six: The boost::thread_specific_ptr class.
  
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include <iostream>
 
boost::mutex io_mutex;
boost::thread_specific_ptr<int> ptr;
 
struct count
{
  count(int id) : id(id) { }
 
  void operator()()
  {
    if (ptr.get() == 0)
      ptr.reset(new int(0));
 
    for (int i = 0; i < 10; ++i)
    {
      (*ptr)++;
      boost::mutex::scoped_lock
        lock(io_mutex);
      std::cout << id << ": "
        << *ptr << std::endl;
    }
  }
 
  int id;
};
 
int main(int argc, char* argv[])
{
  boost::thread thrd1(count(1));
  boost::thread thrd2(count(2));
  thrd1.join();
  thrd2.join();
  return 0;
}

Once Routines

There’s one issue left to deal with: how to make initialization routines (such as constructors) thread-safe. For example, when a "global" instance of an object is created as a singleton for an application, knowing that there’s an issue with the order of instantiation, a function is used that returns a static instance, ensuring the static instance is created the first time the method is called. The problem here is that if multiple threads call this function at the same time, the constructor for the static instance may be called multiple times as well, with disastrous results.

The solution to this problem is what’s known as a "once routine." A once routine is called only once by an application. If multiple threads try to call the routine at the same time, only one actually is able to do so while all others wait until that thread has finished executing the routine. To ensure that it is executed only once, the routine is called indirectly by another function that’s passed a pointer to the routine and a reference to a special flag type used to check if the routine has been called yet. This flag is initialized using static initialization, which ensures that it is initialized at compile time and not run time. 
Therefore, it is not subject to multithreaded initialization problems. Boost.Threads provides calling once routines through boost::call_once and also defines the flag type boost::once_flag and a special macro used to statically initialize the flag named BOOST_ONCE_INIT.

Listing Six illustrates a very simple use of boost::call_once. A global integer is statically initialized to zero and an instance of boost::once_flag is statically initialized using BOOST_ONCE_INIT. Then main starts two threads, both trying to "initialize" the global integer by calling boost::call_once with a pointer to a function that increments the integer. Next main waits for these two threads to complete and writes out the final value of the integer to std::cout. The output illustrates that the routine truly was only called once because the value of the integer is only one.

Listing Six: A very simple use of boost::call_once.

#include <boost/thread/thread.hpp>
#include <boost/thread/once.hpp>
#include <iostream>
 
int i = 0;
boost::once_flag flag =
  BOOST_ONCE_INIT;
 
void init()
{
  ++i;
}
 
void thread()
{
  boost::call_once(&init, flag);
}
 
int main(int argc, char* argv[])
{
  boost::thread thrd1(&thread);
  boost::thread thrd2(&thread);
  thrd1.join();
  thrd2.join();
  std::cout << i << std::endl;
  return 0;
}

The Future of Boost.Threads

There are several additional features planned for Boost.Threads. There will be a boost::read_write_mutex, which will allow multiple threads to read from the shared resource at the same time, but will ensure exclusive access to any threads writing to the shared resource. There will also be a boost::thread_barrier, which will make a set of threads wait until all threads have "entered" the barrier. 

A boost::thread_pool is also planned to allow for short routines to be executed asynchronously without the need to create or destroy a thread each time.

Boost.Threads has been presented to the C++ Standards Committee’s Library Working Group for possible inclusion in the Standard’s upcoming Library Technical Report, as a prelude to inclusion in the next version of the Standard. The committee may consider other threading libraries; however, they viewed the initial presentation of Boost.Threads favorably, and they are very interested in adding some support for 
multithreaded programming to the Standard. So, the future is looking good for multithreaded programming in C++.

References

[1] The POSIX standard defines multithreaded support in what’s commonly known as the pthread library. 
This provides multithreaded support for a wide range of operating systems, including Win32 through the 
pthreads-win32 port. However, this is a C library that fails to address some C++ concepts and is not 
available on all platforms.

[2] Visit the Boost website at http://www.boost.org.

[3] See Bjorn Karlsson article, Smart Pointers in Boost, C/C++ Users Journal, April 2002.

[4] Douglas Schmidt, Michael Stal, Hans Rohnert, and Frank Buschmann. 
Pattern-Oriented Software Architecture Volume 2 — Patterns for Concurrent and Networked Objects 
(Wiley, 2000).

