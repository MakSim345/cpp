2015-FEB

Technical questions on the interview. Varian Medical oy

- STACK UNWINDING. (Exceptions mechanism for example)
"What do you mean by Stack unwinding?"

It is a process during exception handling when the destructor is called for all local objects between the place where the exception was thrown and where it is caught. 

----------------
Stack unwinding is a mostly C++ concept, dealing with how stack-allocated objects are destroyed when its scope is exited (either normally, or through an exception).

Say you have this fragment of code:

void hw() 
{
    string hello("Hello, ");
    string world("world!\n");
    cout << hello << world;
} // at this point, "world" is destroyed, followed by "hello"
--------------

All this relates to C++:

Definition: As you create objects statically (on the stack as opposed to allocating them in the heap memory) and perform function calls, they are "stacked up".

When a scope - i.e. anything delimited by { and } - is exited (by using "return XXX;", reaching the end of the scope or throwing an exception) everything within that scope is destroyed (destructors are called for everything). This process of destroying local objects and calling destructors is called stack unwinding. Exiting a code block using goto will not unwind the stack which is one of the reasons you should never use goto in C++.

You have the following issues related to stack unwinding:

- avoiding memory leaks:
    anything dynamically allocated that is not managed by a local object and cleaned up in the destructor will be leaked - see RAII referred to by Nikolai, and the documentation for boost::scoped_ptr or this example of using boost::mutex::scoped_lock.

- program consistency: 
    the C++ specifications state that you should never throw an exception before any existing exception has been handled. This means that the stack unwinding process should never throw an exception. Either use only code guaranteed not to throw in destructors, or surround everything in destructors with  try {} and catch(...) {}.

If any destructor throws an exception during stack unwinding you end up in the land of undefined behavior which could cause your program to terminate unexpectedly (most common behavior) or the universe to end (theoretically possible but has not been observed in practice yet).
____________________________
Stack unwinding is usually talked about in connection with exception handling. 
Here's an example:

void func( int x )
{
    char* pleak = new char[1024]; // might be lost => memory leak
    std::string s_string( "hello world" ); // will be properly destructed

    if ( x ) throw std::runtime_error( "boom" );

    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
}

int main()
{
    try
    {
        func( 10 );
    }
    catch ( const std::exception& e )
    {
        return 1;
    }

    return 0;
}

Here memory allocated for "pleak" will be lost if exception is thrown, while memory allocated to "s_string" will be properly released by "std::string" destructor in any case. The objects allocated on the stack are "unwound" when the scope is exited (here the scope is of the function func.) This is done by the compiler inserting calls to destructors of automatic (stack) variables.

Now this is a very powerful concept leading to the technique called RAII, that is Resource Acquisition Is Initialization, that helps us manage resources like memory, database connections, open file descriptors, etc. in C++.


