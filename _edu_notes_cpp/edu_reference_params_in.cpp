Q: Reference Parameters in C++: VERY basic example.

A:
Think of a reference as an alias. When you invoke something on a reference, you are really invoking it on the object to which the reference refers.

int i;
int& j = i; // j is an alias to i

j = 5; // same as i = 5

When it comes to functions, consider:

void foo(int i)
{
    i = 5;
}

Above, "int i" is a value and the argument passed is passed "by value". That means if we say:

int x = 2;
foo(x);

The 'i' will be a copy of 'x'. Thus setting 'i' to 5 has no effect on 'x', because it's the copy of 'x' being changed. However, if we make 'i' a reference:

void foo(int& i) // i is an alias for a variable
{
    i = 5;
}

Then saying foo(x) no longer makes a copy of 'x'; 'i' is 'x'. So if we say foo(x), inside the function i = 5; is exactly the same as x = 5; and 'x' changes.


Why is this important? When you program, you never want to copy and paste code. You want to make a function that does one task and it does it well. Whenever that task needs to be performed, you use that function.

So let's say we want to swap two variables. That looks something like this:

int x, y;

// swap:
int temp = x; // store the value of x
x = y;        // make x equal to y
y = temp;     // make y equal to the old value of x

Okay, great. We want to make this a function, because: swap(x, y); is much easier to read. 
So, let's try this:

void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}

This won't work! The problem is that this is swapping copies of two variables. That is:

int a, b;
swap(a, b); // hm, x and y are copies of a and b... a and b remain unchanged

In C, where references do not exist, the solution was to pass the address of these variables; that is, use pointers*:

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int a, b;
swap(&a, &b);

This works well. However, it's a bit clumsy to use, and actually a bit unsafe. swap(nullptr, nullptr), swaps two nothings and dereferences null pointers...undefined behavior! Fixable with some checks:

void swap(int* x, int* y)
{
    if (x == nullptr || y == nullptr)
        return; // one is null; this is a meaningless operation

    int temp = *x;
    *x = *y;
    *y = temp;
}

But looks how clumsy our code has gotten. C++ introduces references to solve this problem. If we can just alias a variable, we get the code we were looking for:

void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

int a, b;
swap(a, b); // inside, x and y are really a and b

Both easy to use, and safe. (We can't accidentally pass in a null, there are no null references.) This works because the swap happening inside the function is really happening on the variables being aliased outside the function.

(Note, never write a swap function. :) One already exists in the header <algorithm>, and it's templated to work with any type.

Another use is to remove that copy that happens when you call a function. Consider we have a data type that's very big. 
Copying this object takes a lot of time, and we'd like to avoid that:

struct big_data
{ char data[9999999]; }; // big!

void do_something(big_data data);

big_data d;
do_something(d); // ouch, making a copy of all that data :<

However, all we really need is an alias to the variable, so let's indicate that. (Again, back in C we'd pass the address of our big data type, solving the copying problem but introducing clumsiness.):

void do_something(big_data& data);

big_data d;
do_something(d); // no copies at all! data aliases d within the function
____________________

This is why you'll hear it said you should pass things by reference all the time, unless they are primitive types. (Because internally passing an alias is probably done with a pointer, like in C. For small objects it's just faster to make the copy then worry about pointers.)

Keep in mind you should be const-correct. This means if your function doesn't modify the parameter, mark it as const. If "do_something" above only looked at but didn't change data, we'd mark it as const:

void do_something(const big_data& data); // alias a big_data, and don't change it

We avoid the copy and we say "hey, we won't be modifying this." This has other side effects (with things like temporary variables), but you shouldn't worry about that now.

In contrast, our swap function cannot be const, because we are indeed modifying the aliases.

Hope this clarifies some more.

*Rough pointers tutorial:

A pointer is a variable that holds the address of another variable. For example:

int i; // normal int

int* p; // points to an integer (is not an integer!)
p = &i; // &i means "address of i". p is pointing to i

*p = 2; // *p means "dereference p". that is, this goes to the int
        // pointed to by p (i), and sets it to 2.

So, if you've seen the pointer-version swap function, we pass the address of the variables we want to swap, and then we do the swap, dereferencing to get and set values.

