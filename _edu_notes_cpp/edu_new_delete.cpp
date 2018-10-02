2015-FEB

Technical questions on the interview. Varian Medical oy

- describe what is "delete[]" and how it works

The "delete" operator deallocates memory and calls the destructor for a single object created with "new".

The "delete []" operator deallocates memory and calls destructors for an array of objects created with "new []".

Using "delete" on a pointer returned by "new []" or using "delete []" on a pointer returned by "new" results in undefined behavior.
____________________________

1. The "delete" is used to de-allocate memory allocated for "single" object

2. The "delete[]" is used to de-allocate memory allocated for "array" of objects

class ABC{}

ABC *ptr = new ABC[100]

when we say "new[100].." compiler can get the information about how many objects that needs to be allocated(here it is 100) and will call the constructor for each of the objects created

but correspondingly if we simply use "delete ptr" for this case, compiler will not know how many objects that "ptr" is pointing to and will end up calling of destructor and deleting memory for only 1 object (leaving the invocation of destructors and deallocation of remaining 99 objects). Hence there will be a memory leak

so we need to use "delete [] ptr" in this case.
_________________________________

// operator delete[] example
#include <iostream>     // std::cout

struct MyClass
{
    MyClass() {std::cout <<"MyClass constructed\n";}
   ~MyClass() {std::cout <<"MyClass destroyed\n";}
};

int main ()
{
    MyClass * pt;

    pt = new MyClass[3];
    delete[] pt;

    return 0;
}
_________________________________
Output:
myclass constructed
myclass constructed
myclass constructed
myclass destroyed
myclass destroyed
myclass destroyed
_________________________________

"delete" and "delete[]" are not the same thing. 
In short, "delete []" invokes the destructor on every element in the allocated array, while "delete" assumes you have exactly one instance. 
You should allocate arrays with "new foo[]" and delete them with "delete[]";
For ordinary objects, use "new" and "delete". Using "delete[]" on a non-array could lead to havoc.

When we want to free a memory allocated to a pointer to an object then "delete" is used.

_________________________________
int * p;
p=new int;
// now to free the memory 
delete p;

// But when we have allocated memory for array of objects like
int * p= new int[10]; //pointer to an array of 10 integer
delete [] p; // then to free memory equal to 10 integers:

NOTE: One can free the memory even by delete p;, but it will free only the first element memory.
You "delete []" when you newed an array type, and "delete" when you didn't. Examples:

typedef int int_array[10];

int* a = new int;
int* b = new int[10];
int* c = new int_array;

delete a;
delete[] b;
delete[] c; // this is a must! even if the new-line didn't use [].
