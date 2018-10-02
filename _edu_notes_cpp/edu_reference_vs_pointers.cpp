- A reference is an alias for another variable whereas a pointer holds the memory address of a variable. References are generally used as function parameters so that the passed object is not the copy but the object itself.

    void fun(int &a, int &b); // A common usage of references.
    int a = 0;
    int &b = a; // b is an alias for a. Not so common to use. 

- A pointer can be re-assigned:

    int x = 5;
    int y = 6;
    int *p;
    p =  &x;
    p = &y;
    *p = 10;
    assert(x == 5);
    assert(y == 10);

- A reference cannot, and must be assigned at initialization:

    int x = 5;
    int y = 6;
    int &r = x;

- A pointer has its own memory address and size on the stack (4 bytes on x86), whereas a reference shares the same memory address (with the original variable) but also takes up some space on the stack. Since a reference has the same address as the original variable itself, it is safe to think of a reference as another name for the same variable. Note: What a pointer points to can be on the stack or heap. Ditto a reference. My claim in this statement is not that a pointer must point to the stack. A pointer is just a variable that holds a memory address. This variable is on the stack. Since a reference has its own space on the stack, and since the address is the same as the variable it references. More on stack vs heap. This implies that there is a real address of a reference that the compiler will not tell you.

    int x = 0;
    int &r = x;
    int *p = &x;
    int *p2 = &r;
    assert(p == p2);

- You can have pointers to pointers to pointers offering extra levels of indirection. Whereas references only offer one level of indirection.

    int x = 0;
    int y = 0;
    int *p = &x;
    int *q = &y;
    int **pp = &p;
    pp = &q;//*pp = q
    **pp = 4;
    assert(y == 4);
    assert(x == 0);

- Pointer can be assigned NULL directly, whereas reference cannot. If you try hard enough, and you know how, you can make the address of a reference NULL. Likewise, if you try hard enough you can have a reference to a pointer, and then that reference can contain NULL.

    int *p = NULL;
    int &r = NULL; <--- compiling error

- Pointers can iterate over an array, you can use ++ to go to the next item that a pointer is pointing to, and + 4 to go to the 5th element. This is no matter what size the object is that the pointer points to.

- A pointer needs to be dereferenced with * to access the memory location it points to, whereas a reference can be used directly. A pointer to a class/struct uses -> to access it's members whereas a reference uses a ..

- A pointer is a variable that holds a memory address. Regardless of how a reference is implemented, a reference has the same memory address as the item it references.

- References cannot be stuffed into an array, whereas pointers can be (Mentioned by user @litb)

- Const references can be bound to temporaries. Pointers cannot (not without some indirection):

    const int &x = int(12); //legal C++
    int *y = &int(12); //illegal to dereference a temporary.

This makes const& safer for use in argument lists and so forth.
____________________

What's a C++ reference (for C programmers)

A reference can be thought of as a constant pointer (not to be confused with a pointer to a constant value!) with automatic indirection, ie the compiler will apply the * operator for you.

All references must be initialized with a non-null value or compilation will fail. It's neither possible to get the address of a reference - the address operator will return the address of the referenced value instead - nor is it possible to do arithmetics on references.

C programmers might dislike C++ references as it will no longer be obvious when indirection happens or if an argument gets passed by value or by pointer without looking at function signatures.

C++ programmers might dislike using pointers as they are considered unsafe - although references aren't really any safer than constant pointers except in the most trivial cases - lack the convenience of automatic indirection and carry a different semantic connotation.

Consider the following statement from the C++ FAQ:

    Even though a reference is often implemented using an address in the underlying assembly language, please do not think of a reference as a funny looking pointer to an object. A reference is the object. It is not a pointer to the object, nor a copy of the object. It is the object.

But if a reference really were the object, how could there be dangling references? In unmanaged languages, it's impossible for references to be any 'safer' than pointers - there generally just isn't a way to reliably alias values across scope boundaries!
Why I consider C++ references useful

Coming from a C background, C++ references may look like a somewhat silly concept, but one should still use them instead of pointers where possible: Automatic indirection is convenient, and references become especially useful when dealing with RAII - but not because of any perceived safety advantage, but rather because they make writing idiomatic code less awkward.

RAII is one of the central concepts of C++, but it interacts non-trivially with copying semantics. Passing objects by reference avoids these issues as no copying is involved. If references were not present in the language, you'd have to use pointers instead, which are more cumbersome to use, thus violating the language design principle that the best-practice solution should be easier than the alternatives.


