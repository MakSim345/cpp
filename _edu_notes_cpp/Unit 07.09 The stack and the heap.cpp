7.9 - The stack and the heap

The memory a program uses is typically divided into four different areas:

    The code area, where the compiled program sits in memory.
    The globals area, where global variables are stored.
    The heap, where dynamically allocated variables are allocated from.
    The stack, where parameters and local variables are allocated from. 

There isn’t really much to say about the first two areas. The heap and the stack are where most of the interesting stuff takes place, and those are the two that will be the focus of this section.

The heap

The heap (also known as the “free store”) is a large pool of memory used for dynamic allocation. In C++, when you use the new operator to allocate memory, this memory is assigned from the heap.

int *pValue = new int; // pValue is assigned 4 bytes from the heap
int *pArray = new int[10]; // pArray is assigned 40 bytes from the heap

Because the precise location of the memory allocated is not known in advance, the memory allocated has to be accessed indirectly -- which is why new returns a pointer. You do not have to worry about the mechanics behind the process of how free memory is located and allocated to the user. However, it is worth knowing that sequential memory requests may not result in sequential memory addresses being allocated!

int *pValue1 = new int;
int *pValue2 = new int;
// pValue1 and pValue2 may not have sequential addresses

When a dynamically allocated variable is deleted, the memory is “returned” to the heap and can then be reassigned as future allocation requests are received.

The heap has advantages and disadvantages:
1. Allocated memory stays allocated until it is specifically deallocated (beware memory leaks).
2. Dynamically allocated memory must be accessed through a pointer.
3. Because the heap is a big pool of memory, large arrays, structures, or classes should be allocated here.

The stack

The call stack (usually referred to as “the stack”) has a much more interesting role to play. Before we talk about the call stack, which refers to a particular portion of memory, let’s talk about what a stack is.

Consider a stack of plates in a cafeteria. Because each plate is heavy and they are stacked, you can really only do one of three things:
1. Look at the surface of the top plate
2. Take the top plate off the stack
3. Put a new plate on top of the stack

In computer programming, a stack is a container that holds other variables (much like an array). However, whereas an array lets you access and modify elements in any order you wish, a stack is more limited. The operations that can be performed on a stack are identical to the ones above:

1. Look at the top item on the stack (usually done via a function called top())
2. Take the top item off of the stack (done via a function called pop())
3. Put a new item on top of the stack (done via a function called push())

A stack is a last-in, first-out (LIFO) structure. The last item pushed onto the stack will be the first item popped off. If you put a new plate on top of the stack, anybody who takes a plate from the stack will take the plate you just pushed on first. Last on, first off. As items are pushed onto a stack, the stack grows larger -- as items are popped off, the stack grows smaller.

The plate analogy is a pretty good analogy as to how the call stack works, but we can actually make an even better analogy. Consider a bunch of mailboxes, all stacked on top of each other. Each mailbox can only hold one item, and all mailboxes start out empty. Furthermore, each mailbox is nailed to the mailbox below it, so the number of mailboxes can not be changed. If we can’t change the number of mailboxes, how do we get a stack-like behavior?

First, we use a marker (like a post-it note) to keep track of where the bottom-most empty mailbox is. In the beginning, this will be the lowest mailbox. When we push an item onto our mailbox stack, we put it in the mailbox that is marked (which is the first empty mailbox), and move the marker up one mailbox. When we pop an item off the stack, we move the marker down one mailbox and remove the item from that mailbox. Anything below the marker is considered “on the stack”. Anything at the marker or above the marker is not on the stack.

This is almost exactly analogous to how the call stack works. The call stack is a fixed-size chunk of sequential memory addresses. The mailboxes are memory addresses, and the “items” are pieces of data (typically either variables or addreses). The “marker” is a register (a small piece of memory) in the CPU known as the stack pointer. The stack pointer keeps track of where the top of the stack currently is.

The only difference between our hypothetical mailbox stack and the call stack is that when we pop an item off the call stack, we don’t have to erase the memory (the equivalent of emptying the mailbox). We can just leave it to be overwritten by the next item pushed to that piece of memory. Because the stack pointer will be below that memory location, we know that memory location is not on the stack.

So what do we push onto our call stack? Parameters, local variables, and… function calls.

The stack in action

Because parameters and local variables essentially belong to a function, we really only need to consider what happens on the stack when we call a function. Here is the sequence of steps that takes place when a function is called:

    The address of the instruction beyond the function call is pushed onto the stack. This is how the CPU remembers where to go after the function returns.
    Room is made on the stack for the function’s return type. This is just a placeholder for now.
    The CPU jumps to the function’s code.
    The current top of the stack is held in a special pointer called the stack frame. Everything added to the stack after this point is considered “local” to the function.
    All function arguments are placed on the stack.
    The instructions inside of the function begin executing.
    Local variables are pushed onto the stack as they are defined. 

When the function terminates, the following steps happen:

    The function’s return value is copied into the placeholder that was put on the stack for this purpose.
    Everything after the stack frame pointer is popped off. This destroys all local variables and arguments.
    The return value is popped off the stack and is assigned as the value of the function. If the value of the function isn’t assigned to anything, no assignment takes place, and the value is lost.
    The address of the next instruction to execute is popped off the stack, and the CPU resumes execution at that instruction. 

Typically, it is not important to know all the details about how the call stack works. However, understanding that functions are effectively pushed on the stack when they are called and popped off when they return gives you the fundamentals needed to understand recursion, as well as some other concepts that are useful when debugging.

Stack overflow

The stack has a limited size, and consequently can only hold a limited amount of information. If the program tries to put too much information on the stack, stack overflow will result. Stack overflow happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory.

Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls (where function A calls function B calls function C calls function D etc…) Overflowing the stack generally causes the program to crash.

Here is an example program that causes a stack overflow. You can run it on your system and watch it crash:

int main()
{
    int nStack[100000000];
    return 0;
}

This program tries to allocate a huge array on the stack. Because the stack is not large enough to handle this array, the array allocation overflows into portions of memory the program is not allowed to use. Consequently, the program crashes.

The stack has advantages and disadvantages:

    Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.
    All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
    Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes allocating large arrays, structures, and classes, as well as heavy recursion. 

