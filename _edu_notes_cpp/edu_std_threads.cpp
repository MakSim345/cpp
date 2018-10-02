What is Multithreading.
--------
Multithreading is an ability of a platform (Operating System, Virtual Machine  etc.) or application to create a process that consists of multiple threads of execution (threads). A thread of execution is the smallest sequence of programming instructions that can be managed independently by a scheduler. These threads can run parallel and it can increase efficiency of programs.

In Multicore and Multiprocessor systems multithreading means that different threads are executed at the same time on different cores or processors.

For single core systems multithreading divides the time between the threads. The operating system in turn sends a certain number of instructions from each thread to the processor. Threads are not executed simultaneously. Operating System only simulates their simultaneous execution. This feature of the operating system is called multithreading.

Multithreading is used when the parallel execution of some tasks leads to a more efficient use of resources of the system.

Built in support for multithreading was introduced in C++11. Header file thread.h provides functionality for creating multithreaded C++ programs.

--------
How to create a thread?

First, you have to include thread header in your program:

    #include <thread> 

When you want to create a thread, you have to create an object of a thread class.

    //this thread does not represent any thread of execution
    thread t_empty;

As you can see, when default constructor of thread class is used, we do not pass any information to the thread. This means, that nothing is executed in this thread. We have to initialize a thread. It can be done in different ways.

Initializing thread with a function

When you create a thread, you can pass a pointer of a function to its constructor. Once thread is created, this function starts its work in a separate thread. Look on an example:


    #include <iostream>
    #include <thread> 
    using namespace std;
    void threadFunc()
    {
	    cout << "Welcome to Multithreading" << endl;
    
    }
    int main()
    {
	    //pass a function to thread
	    thread funcTest1(threadFunc);
    }

Try to compile and run this program. It compiles without any errors but you will get a runtime error.

As you can see, main thread creates new thread funcTest1 with a parameter threadFunc. Main thread does not wait for funcTest1 thread termination. It continues its work. The main thread finishes execution, but funcTest1 is still running. This causes error. All the threads must be terminated before main thread is terminated.

Join threads

Thread joining is done by using join() member function of a thread class:


void join();

This function returns only after all the threads are terminated. It means that the main thread will wait until child thread does not finish its execution:

Call join() for the thread, created in the previous example and run the program again:


//pass a function to thread
thread funcTest1(threadFunc);
//main is blocked until funcTest1 is not finished
funcTest1.join();

As you can see, now program is executed successfully.

Joinable and not Joinable threads

After join() returns, thread becomes not joinable. A joinable thread is a thread that represents a thread of execution which has not yet been joined.

A thread is not joinable when it is default constructed or is moved/assigned to another thread or join() or detach() member function is called.

Not joinable thread can be destroyed safely.

You can check if a thread is joinable by using joinable() member function:


bool joinable()

This function returns true if the thread is joinable and false otherwise. It’s better to check if the thread is joinable before join() function is called:


//pass a function to thread
thread funcTest1(threadFunc);
//check if thread is joinable
if (funcTest1.joinable())
{
	//main is blocked until funcTest1 is not finished
	funcTest1.join();
}

Detaching thread

As we mentioned above, thread becomes not joinable after detach() member function is called:


void detach()

This function detaches a thread from the parent thread. It allows parent and child threads to be executed independently from each other. After the call of detach() function, the threads are not synchronized in any way:


//detach funcTest1 from main thread
funcTest1.detach();
if (funcTest1.joinable())
{
	//main is blocked until funcTest1 is not finished
	funcTest1.join();
}
else
{
	cout << "functTest1 is detached" << endl;
}

You will notice that main thread is not waiting for the termination of its child thread.

Initializing thread with an object

You can initialize a thread not only with a function. You can use for this purpose function object (functor) or a member function of a class.

A functor is an object of a class that overloads operator () - function call operator.

If you want to initialize a thread with an object of a class, this class should overload operator(). It can be done in the following way:


class myFunctor
{
public:
	void operator()()
	{
		cout << "This is my function object" << endl;
	}
};

Now you can initialize a thread by passing an object of the class myFunctor to the constructor of a thread:


myFunctor myFunc;
thread functorTest(myFunc);
if (functorTest.joinable())
functorTest.join();

If you want to initialize a thread with a public member function of a class, you have to specify the identifier of this function and pass an object of the class, which defines this member function:

Add a public member function to myFunctor class:


void publicFunction()
{
	cout << "public function of myFunctor class is called" << endl;
}

And now you can initialize thread with publicFunction() of myFunctor class:


myFunctor myFunc;
//initializing thread with member function of myFunctor class
thread functorTest(&myFunctor::publicFunction,myFunc);
if (functorTest.joinable())
	functorTest.join();

Passing arguments to thread

In the previous examples, we used only functions and objects without passing any arguments to these functions and objects.

We can use a function with parameters for thread initialization. Create new function for testing this possibility:


void printSomeValues(int val, char* str, double dval)
{
	cout << val << " " << str <<" " << dval << endl;

}

As you can see, this function takes three arguments. If you want to initialize a thread with this function, first you have to pass a pointer to this function, then pass the arguments to the function in the same order as they are in the parameter list of the function:


char* str = "Hello";
//5, str and 3.2 are passed to printSomeValues function
thread paramPass(printSomeValues, 5, str, 3.2);
if (paramPass.joinable())
paramPass.join();

When you want to initialize a thread with an object with parameters, we have to add corresponding parameter list to the overloading version of operator ():


class myFunctorParam
{
public:
	void operator()(int* arr, int length)
	{
		cout << "An array of length " << length << "is passed to thread" << endl;
		for (int i = 0; i != length; ++i)
			cout << arr[i] << " " << endl;
		cout << endl;
	}
};

As you can see, operator () takes two parameters:


void operator()(int* arr, int length)

The initialization of the thread with an object in this case is similar to using a function with parameters:


//these parameters will be passed to thread
int arr[5] = { 1, 3, 5, 7, 9 };
myFunctorParam objParamPass;
thread test(objParamPass, arr, 5);
if (test.joinable())
	test.join();

It is possible to use a member function of a class to pass parameters to thread. Add new public function to myFunctorParam class:


void changeSign(int* arr, int length)
{
	cout << "An arrray of length " << length << "is passed to thread" << endl;
	for (int i = 0; i != length; ++i)
		cout << arr[i] << " ";
	cout << "Changing sign of all elements of initial array" << endl;
	for (int i = 0; i != length; ++i)
	{
		arr[i] *= -1;
		cout << arr[i] << " ";
	}
}

Passing arguments to member function:


int arr2[5] = { -1, 3, 5, -7, 0 };
//initialize thread with member function
thread test2(&myFunctorParam::changeSign, &objParamPass, arr2, 5);
if (test2.joinable())
	test2.join();

When you pass arguments to the member function of a class, you have to specify arguments in the same order as they are listed in the parameter list of the function. It is done after the second parameter of the thread constructor:


thread test2(&myFunctorParam::changeSign, &objParamPass, arr2, 5);

Thread ID

Every thread has its unique identifier. Class thread has public member function that returns the ID of the thread:


id get_id()

The returned value is of type id that is specified in thread class.

Look on the following example:


//create 3 different threads
thread t1(showMessage);
thread t2(showMessage);
thread t3(showMessage);
//get id of all the threads
thread::id id1 = t1.get_id();
thread::id id2 = t2.get_id();
thread::id id3 = t3.get_id();
//join all the threads
if (t1.joinable())
{
	t1.join();
	cout << "Thread with id " << id1 << " is terminated" << endl;
}
if (t2.joinable())
{
	t2.join();
	cout << "Thread with id " << id2 << " is terminated" << endl;
}
if (t3.joinable())
{
	t3.join();
	cout << "Thread with id " << id3 << " is terminated" << endl;
}

Every thread prints its unique identifier after it finishes its execution:

Thread with id 8228 is terminated
Thread with id 10948 is terminated
Thread with id 9552 is terminated
this_thread  Namespace

this_thread namespace from thread header offers possibilities to work with current thread. This namespace contains four useful functions:

1. id_get_id() – returns the id of current thread.

2. template
    void sleep_until (const chrono::time_point<Clock,Duration>& abs_time) – blocks current thread until abs_time is not reached.

3. template
    void sleep_for (const chrono::duration<Rep,Period>& rel_time); – thread is blocked during time span specified by rel_time.

4. void yield() – current thread allows implementation to reschedule the execution of thread. It used to avoid blocking.

This is an example of using these functions:


#include <iostream>
#include <iomanip> 
#include <thread> 
#include <chrono>
#include <ctime>

using namespace std;
using std::chrono::system_clock;
int main()
{
	cout << "The id of current thread is " << this_thread::get_id << endl;

	//sleep while next minute is not reached

	//get current time
	time_t timet = system_clock::to_time_t(system_clock::now());
	//convert it to tm struct
	struct tm * time = localtime(&timet);
	cout << "Current time: " << put_time(time, "%X") << '\n';
	std::cout << "Waiting for the next minute to begin...\n";
	time->tm_min++; time->tm_sec = 0;
	//sleep until next minute is not reached
	this_thread::sleep_until(system_clock::from_time_t(mktime(time)));
	cout << std::put_time(time, "%X") << " reached!\n";
	//sleep for 5 seconds
	this_thread::sleep_for(chrono::seconds(5));
	//get current time
	timet = system_clock::to_time_t(system_clock::now());
	//convert it to tm struct
	time = std::localtime(&timet);
	cout << "Current time: " << put_time(time, "%X") << '\n';
}

You will get an output depending on your current time:

The id of current thread is 009717C6
Current time: 15:28:35
Waiting for the next minute to begin...
15:29:00 reached!
Current time: 15:29:05

Concurrent access to resources

Multithreading programming faces a problem with concurrent access to a shared resource. Simultaneous access to the same resource can leads to a lot of errors and chaos in the program.

Have a look at below example:


vector<int> vec;
void push()
{
	for (int i = 0; i != 10; ++i)
	{
		cout << "Push " << i << endl;
		_sleep(500);
		vec.push_back(i);
	}
}
void pop()
{
	for (int i = 0; i != 10; ++i)
	{
		if (vec.size() > 0)
		{
			int val = vec.back();
			vec.pop_back();
			cout << "Pop "<< val << endl;
		}
	_sleep(500);
	}
}
int main()
{
	//create two threads
	thread push(push);
	thread pop(pop);
	if (push.joinable())
		push.join();
	if (pop.joinable())
		pop.join();
}

As you can see, there is a global vector vec of integer values. Two threads push and pop try to access this vector simultaneously: the first thread pushes an element to the vector and the second one tries to pop an element from the vector.

The access to the vector is not synchronized. Threads are accessing vector non-continuously. Because of simultaneous access to shared data many errors can appear.

Mutex

Class mutex is a synchronization primitive that is used to protect shared data from simultaneous access. A mutex can be locked and unlocked. Once a mutex is locked, current thread owns mutex until it is not unlocked. It means that no other thread can execute any instructions from the block of code surrounded by mutex until thread that owns mutex unlocks it. If you want to use mutex, you have to include mutex header in the program:


#include <mutex>  

After this, you have to create a global variable of mutex type. It will be used to synchronize access to the shared data:

Once you want that a portion of program to be executed only by one thread in the same period, you have to “lock” it using mutex:


void push()
{
	m.lock();
		for (int i = 0; i != 10; ++i)
		{
			cout << "Push " << i << endl;
			_sleep(500);
			vec.push_back(i);
		}
	m.unlock();
}
void pop()
{
	m.lock();
	for (int i = 0; i != 10; ++i)
	{
		if (vec.size() > 0)
		{
			int val = vec.back();
			vec.pop_back();
			cout << "Pop " << val << endl;
		}
	_sleep(500);
	}
	m.unlock();
}

Operations of pushing and popping elements to the vector are locked using mutex. Therefore, if a thread enters a block of instructions and locks the mutex, no any thread can execute this code until mutex is unlocked. Try to execute this program again:


//create two threads
thread push(push);
thread pop(pop);
if (push.joinable())
	push.join();
if (pop.joinable())
	pop.join();

Now, the access to vector is synchronized:

Push 0
Push 1
Push 2
Push 3
Push 4
Push 5
Push 6
Push 7
Push 8
Push 9
Pop 9
Pop 8
Pop 7
Pop 6
Pop 5
Pop 4
Pop 3
Pop 2
Pop 1
Pop 0

We can examine another example of mutex usage. Imagine the following situation:

“A lot of people run to a call-box to talk to their friend. The first person to catch the door-handle of the call box is the only one who is allowed to use the phone. He must keep holding on to the handle of the door as long as he uses the call box. Otherwise, someone else will catch hold of the handle, throw him out and talk to his friend. There is no queue system as in real life. When the person finishes his call, exits the call-box and leaves the door handle, the next person that gets hold of the door handle will be allowed to use the phone.”

In this case, you have to imagine a problem of simultaneous access to data in the following way:

A thread is a person.
The mutex is the door handle.
The lock is the person's hand.
The resource is the phone.

Any thread which has to execute some lines of code which should not be executed by other threads at the same time (using the phone to talk to his friend), has to first acquire a lock on a mutex (clutching the door handle of the call-box). Only then, a thread will be able to run those lines of code (making the phone call).

Once the thread finishes executing that code, it should release the lock on the mutex so that another thread can acquire a lock on the mutex (other people being able to access the phone booth).

This is an example of this situation written using mutex:


std::mutex m;//door handle

void makeACall()
{
	m.lock();//person enters the call box and locks the door
	//now it can talk to his friend without any interruption
	cout << " Hello my friend, this is " << this_thread::get_id() << endl;
	//this person finished to talk to his friend
	m.unlock();//and he leaves the call box and unlock the door
}
int main()
{
	//create 3 persons who want to make a call from call box
	thread person1(makeACall);
	thread person2(makeACall);
	thread person3(makeACall);
	if (person1.joinable())
	{
		person1.join();
	}
	if (person2.joinable())
	{
		person2.join();
	}
	if (person3.joinable())
	{
		person3.join();
	}
}

The access to makeACall function will be synchronized. You will get an output that is similar to this one:

Hello my friend, this is 3636
Hello my friend, this is 5680
Hello my friend, this is 928

C++ Interview Questions

