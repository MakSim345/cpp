15.3 — Exceptions, functions, and stack unwinding

In the previous lesson on basic exception handling, we explained how throw, try, and catch work together to enable exception handling. This lesson is dedicated to showing more examples of exception handling at work in various cases.

Exceptions within functions

In all of the examples in the previous lesson, the throw statements were placed directly within a try block. If this were a necessity, exception handling would be of limited use.

One of the most useful properties of exception handling is that the throw statements do NOT have to be placed directly inside a try block due to the way exceptions propagate when thrown. This allows us to use exception handling in a much more modular fashion. We’ll demonstrate this by rewriting the square root program from the previous lesson to use a modular function.

#include "math.h" // for sqrt() function
using namespace std;
 
// A modular square root function
double MySqrt(double dX)
{
    // If the user entered a negative number, this is an error condition
    if (dX < 0.0)
        throw "Can not take sqrt of negative number"; // throw exception of type char*
 
    return sqrt(dX);
}
 
int main()
{
    cout << "Enter a number: ";
    double dX;
    cin >> dX;
 
    try // Look for exceptions that occur within try block and route to attached catch block(s)
    {
        cout << "The sqrt of " << dX << " is " << MySqrt(dX) << endl;
    }
    catch (char* strException) // catch exceptions of type char*
    {
        cerr << "Error: " << strException << endl;
    }
}

In this program, we’ve taken the code that checks for an exception and calculates the square root and put it inside a modular function called MySqrt(). We’ve then called this MySqrt() function from inside a try block. Let’s verify that it still works as expected:

Enter a number: -4
Error: Can not take sqrt of negative number

It does!

The most interesting part of this program is the MySqrt() function, which potentially raises an exception. However, you will note that this exception is not inside of a try block! This essentially means MySqrt is willing to say, “Hey, there’s a problem!”, but is unwilling to handle the problem itself. It is, in essence, delegating that responsibility to its caller (the equivalent of how using a return code passes the responsibility of handling an error back to a function’s caller).

Let’s revisit for a moment what happens when an exception is raised. First, the program looks to see if the exception can be handled immediately (which means it was thrown inside a try block). If not, it immediately terminates the current function and checks to see if the caller will handle the exception. If not, it terminates the caller and checks the caller’s caller. Each function is terminated in sequence until a handler for the exception is found, or until main() terminates. This process is called unwinding the stack (see the lesson on the stack and the heap if you need a refresher on what the call stack is).

Now, let’s take a detailed look at how that applies to this program when MySqrt(-4) is called and an exception is raised.

First, the program checks to see if we’re immediately inside a try block within the function. In this case, we are not. Then, the stack begins to unwind. First, MySqrt() terminates, and control returns to main(). The program now checks to see if we’re inside a try block. We are, and there’s a char* handler, so the exception is handled by the try block within main(). To summarize, MySqrt() raised the exception, but the try/catch block in main() was the one who captured and handled the exception.

At this point, some of you are probably wondering why it’s a good idea to pass errors back to the caller. Why not just make MySqrt() handle it’s own error? The problem is that different applications may want to handle errors in different ways. A console application may want to print a text message. A windows application may want to pop up an error dialog. In one application, this may be a fatal error, and in another application it may not. By passing the error back up the stack, each application can handle an error from MySqrt() in a way that is the most context appropriate for it! Ultimately, this keeps MySqrt() as modular as possible, and the error handling can be placed in the less-modular parts of the code.

Another stack unwinding example

Here’s another example showing stack unwinding in practice, using a larger stack. Although this program is long, it’s pretty simple: main() calls First(), First() calls Second(), Second() calls Third(), Third() calls Last(), and Last() throws an exception.

#include <iostream>
using namespace std;
 
void Last() // called by Third()
{
    cout << "Start Last" << endl;
    cout << "Last throwing int exception" << endl;
    throw -1;
    cout << "End Last" << endl;
 
}
 
void Third() // called by Second()
{
    cout << "Start Third" << endl;
    Last();
    cout << "End Third" << endl;
}
 
void Second() // called by First()
{
    cout << "Start Second" << endl;
    try
    {
        Third();
    }
    catch(double)
    {
         cerr << "Second caught double exception" << endl;
    }
    cout << "End Second" << endl;
}
 
void First() // called by main()
{
    cout << "Start First" << endl;
    try
    {
        Second();
    }
    catch (int)
    {
         cerr << "First caught int exception" << endl;
    }
    catch (double)
    {
         cerr << "First caught double exception" << endl;
    }
    cout << "End First" << endl;
}
 
int main()
{
    cout << "Start main" << endl;
    try
    {
        First();
    }
    catch (int)
    {
         cerr << "main caught int exception" << endl;
    }
    cout << "End main" << endl;
 
    return 0;
}

Take a look at this program in more detail, and see if you can figure out what gets printed and what doesn’t when it is run. The answer follows:

Start main
Start First
Start Second
Start Third
Start Last
Last throwing int exception
First caught int exception
End First
End main

Let’s examine what happens in this case. The printing of all the start statements is straightforward and doesn’t warrant further explanation. Last() prints “Last throwing int exception” and then throws an int exception. This is where things start to get interesting.

Because Last() doesn’t handle the exception itself, the stack begins to unwind. Last() terminates immediately and control returns to the caller, which is Third().

Third() doesn’t handle any exceptions either, so it terminates immediately and control returns to Second().

Second() has a try block, and the call to Third() is within it, so the program attempts to match the exception with an appropriate catch block. However, there are no handlers for exceptions of type int here, so Second() terminates immediately and control returns to First().

First() also has a try block, and the call to Second() is within it, so the program looks to see if there is a catch handler for int exceptions. There is! Consequently, First() handles the exception, and prints “First caught int exception”.

Because the exception has now been handled, control continues normally at the end of the catch block within First(). This means First() prints “End First” and then terminates normally.

Control returns to main(). Although main() has an exception handler for int, our exception has already been handled by First(), so the catch block within main() does not get executed. main() simply prints “End main” and then terminates normally.

There are quite a few interesting principles illustrated by this program:

First, the immediate caller of a function that throws an exception doesn’t have to handle the exception if it doesn’t want to. In this case, Third() didn’t handle the exception thrown by Last(). It delegated that responsibility to one of it’s callers up the stack.

Second, if a try block doesn’t have a catch handler for the type of exception being thrown, stack unwinding occurs just as if there were no try block at all. In this case, Second() didn’t handle the exception either because it didn’t have the right kind of catch block.

Third, once an exception is handled, control flow proceeds as normal starting from the end of the catch blocks. This was demonstrated by First() handling the error and then terminating normally. By the time the program got back to main(), the exception had been thrown and handled already -- main() had no idea there even was an exception at all!

As you can see, stack unwinding provides us with some very useful behavior -- if a function does not want to handle an exception, it doesn’t not have to. The exception will propagate up the stack until it finds someone who will! This allows us to decide where in the call stack is the most appropriate place to handle any errors that may occur.

In the next lesson, we’ll take a look at what happens when you don’t capture an exception, and a method to prevent that from happening.

