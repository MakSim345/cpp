2015-FEB

Technical questions on the interview. Varian Medical oy

+ copy constructor. What is it and why it is ezxist?
http://geeksquiz.com/copy-constructor-in-cpp/

- What is "static_cast" and how to use it? 

+ virtual destructor. Why it is virtual and what does it mean?
http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors

+ STL containers in short: what is it and how to use it?

+ STACK UNWINDING. (Exceptions mechanism for example)

+ describe what is "delete[]" and how it works

+ what difference between class and structure in C++?

+ write a Reverce() method for linked list class

- what is "finally" in the exception means?
____________________________
Extra questions from stackoverflow.
A few questions can allow you to know a lot about a candidate:

    -Differences between a pointer and a reference, when would you use each?
    -Why would you make a destructor virtual?
    -Where is the construction order of a class attributes defined?
    -Copy constructor and operator=. When would you implement them? When would you make them private?
    -When would you use smart pointers? what things would you take into account to decide which?
    -Where else have you seen RAII idiom?
    -When would you make a parameter const? when a method?
    -When would you make an attribute mutable?
    -What is virtual inheritance?
    -What is template specialization?
    -What are traits?
    -What are policies?
    -What is SFINAE?
    -What do you know about C++Ox standard?
    -What boost libraries have you used?
    -What C++ books have you read? (Sutter? Alexandrescu?)

Some short exercises (no more than 10 minutes) about STL containers, memory management, slicing, etc. would also be useful. I would allow him to do it in a computer with a ready environment. It's important to observe the agility.

____________________________
"What can you do to avoid deadlock?"
One of the main reason deadlock can occur in a multi-threaded application is circular wait where two different threads holding two resources and each of them wait for the other resource. The other conditions deadlock to occur is no preemption, hold-and-wait and mutual-exclusion.

The best way to avoid deadlock is to maintain lock order. In other words let the threads able to get the lock in a particular order. This will restrict the threads to come into deadlock.
____________________________
A joke:

So the questions: "when have you used goto?"; "should you check a pointer parameter for NULL before using it?"; and "singleton?" should give answers respectively: "almost never, but I sometimes think about it"; "depends whether my caller is a muppet or not"; and "no, I'm engaged actually, and don't call me Tone"?


