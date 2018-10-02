-----------------------
"Pass by value:"
-----------------------

void func (vector v)

Pass variables by value when the function needs complete isolation from the environment i.e. to prevent the function from modifying the original variable as well as to prevent other threads from modifying its value while the function is being executed. This is the default in C/C++.

The downside is the CPU cycles and extra memory spent to copy the object.

-----------------------
"Pass by const reference:"
-----------------------
void func (const vector & v);

The main intention of this form is to allow pass-by-value behavior while removing the copying overhead. This gives the function read-only access to the original object, but it cannot modify its value.

The downside is thread safety: any change made to the original object by another thread will show up inside the function while it is still executing.

-----------------------
"Pass by non-const reference:"
-----------------------
void func (vector & v)

Use this if modifications made to the variable inside the function need to be reflected outside.

Just like the const reference case, this is not thread safe.

-----------------------
"Pass by const pointer:"
-----------------------
void func (const vector * vp);

Functionally same as pass by const-reference except for the different syntax, plus the fact that the calling function can pass NULL pointer to indicate that it has no valid data to pass.

Not thread safe.

-----------------------
"Pass by non-const pointer:"
-----------------------
void func (vector * vp);

Has the advantage of pass by const pointer, where the caller can set it to null to indicate no data is passed. This is used in many glibc APIs. Example:

void func (string * str, /* ... */)
{
    if (str != NULL) 
    {
        *str = "some_value"; // assign to *sig only if it's non-null
    }
}

As with all pass by reference/pointer, not thread safe.

--------------------------------------

There are several cases to consider.
-----------------------
Parameter modified ("out" and "in/out" parameters)
-----------------------
void modifies(T &param);
// vs
void modifies(T *param);

This case is mostly about style: do you want the code to look like call(obj) or call(&obj)? However, there are two points where the difference matters: the optional case, below, and you want to use a reference when overloading operators.

-----------------------
"...and optional"
-----------------------

void modifies(T *param=0);  // default value optional, too
// vs
void modifies();
void modifies(T &param);

-----------------------
"Parameter not modified"
-----------------------
void uses(T const &param);
// vs
void uses(T param);

This is the interesting case. The rule of thumb is "cheap to copy" types are passed by value — these are generally small types (but not always) — while others are passed by const ref. However, if you need to make a copy within your function regardless, you should pass by value. (Yes, this exposes a bit of implementation detail. C'est le C++.')

-----------------------
"...and optional"
-----------------------

void uses(T const *param=0);  // default value optional, too
// vs
void uses();
void uses(T const &param);  // or optional(T param)

There is the least difference here between all situations, so choose whichever makes your life easiest.

-----------------------
"Const by value is an implementation detail"
-----------------------
void f(T);
void f(T const);

These declarations are actually the exact same function! When passing by value, const is purely an implementation detail. Try it out:

void f(int);
void f(int const) { /* implements above function, not an overload */ }

typedef void NC(int);       // typedefing function types
typedef void C(int const);

NC *nc = &f;  // nc is a function pointer
C *c = nc;    // C and NC are identical types
a

---------------------------------

Passing by const reference is the preferred way to pass around objects as a smart alternative to pass-by-value. When you pass by const reference, you take the argument in by reference (avoiding making any copies of it), but cannot make any changes to the original object (much as would happen when you would take the parameters in by value).

If you consider these three functions:

void VersionOne(Vector v);
void VersionTwo(Vector& v);
void VersionThree(const Vector& v);

There are subtle distinctions between all of them. The first function, for example, will invoke the copy constructor when you pass in a Vector so that it has its own local copy of the Vector. If your copy constructor takes a while to run or does a lot of resource allocation and deallocation, this may be slow, but you can make any changes you want to the parameter without risking any changes propagating back up to the caller. 

There will also be a destructor call at the end of the function as the argument is cleaned up, and if this is too large a cost it may be advisable to avoid this setup. That said, for small objects it may be perfectly acceptable.

The second version of this function takes in a Vector by reference, which means that the function can make any changes it wants to the Vector and the changes will propagate back up to the caller. Whenever you see a function that takes an argument by non-const reference, like this VersionTwo function, you should assume that it will be modifying the argument, since if it were not going to make any modifications, it would be taken by const reference. 

You will most likely take in the value by reference if you need to make changes to the Vector; for example, by rotating it, scaling it, etc. One tradeoff involved here is that the Vector will not be copied when it is passed into this function, and so you will avoid a call to the copy constructor and destructor. This may have performance implications for your program, though if that is your reasoning you should probably go with pass by const reference. 

One thing to note is that following a reference is very similar to following a pointer (in fact, most implementations of references just treat them as though they were automatically-dereferenced pointers), so there may be a small performance hit every time you access the data through the reference. Only profiling can tell you whether or not this is a major problem, though, and I would not worry about it unless you had a specific reason to think it was at fault.

The final version of this function takes in a Vector by const reference, which, like passing by regular reference, avoids any copying. However, when taking the Vector by const reference, you are prohibited from making any changes to the Vector inside the function, so clients can assume that the Vector will not be modified.

(Yes, technically it could be modified if it is poorly-written or has mutable data members, but we'll ignore that for now. It's the high-level idea that is important here). This option would be good if you wanted to be able to inspect the value in the function without copying it and without mutating it.

There is one more difference between pass-by-reference and pass-by-const-reference, and that is the behavior of the function on rvalues. If you have a temporary Vector object - either you created it explicitly by writing Vector() or by doing some mathematical operation on it like writing v1 + v2 - then you cannot pass that temporary Vector into a function that takes its parameter by reference because references can only bind to lvalues. 

The idea is that if you have a function like this:

void DoSomething(Vector& v) 
{
     v.x = 0.0f;
}

Then it does not make sense to write

DoSomething(v1 + v2);

Since this would be changing the x field of a temporary expression. 
To prevent this, the compiler will refuse to compile this code.

However, C++ makes an exception and lets you pass rvalues into functions that take their argument by const reference, because, intuitively, you should not be able to modify an object through a const reference. 

Thus this code is perfectly legal:

void DoSomething(const Vector& v) 
{
    cout << v.x << endl;
}

DoSomething(v1 + v2);

So, to summarize:

   - "Pass-by-value" and "pass-by-const-reference" imply similar things - you want to be able to look at the value without being able to modify it.
   - Any time you could use "pass-by-value" you could instead use "pass-by-const-reference" without affecting the correctness of the program. However, there are performance tradeoffs between the indirection of the reference and the cost of copying and destructing the parameter.
   - "Pass-by-non-const-reference" should be used to indicate "I want to modify the argument."
   - You cannot pass "rvalues" into functions that take their arguments by "non-const reference".

Hope this helps!

