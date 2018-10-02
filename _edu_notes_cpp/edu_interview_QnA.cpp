C++ Interview Questions and Answers


"What do you mean by inline function?"

- The idea behind inline functions is to insert the code of a called function at the point where the function is called. If done carefully, this can improve the application's performance in exchange for increased compile time and possibly (but not always) an increase in the size of the generated binary executables.
___________________________

"Write a program that ask for user input from 5 to 9 then calculate the average:"

#include "iostream.h"
int main() 
{
    int MAX = 4;
    int total = 0;
    int average;
    int numb;
    for (int i=0; i<MAX; i++) 
    {
        cout << "Please enter your input between 5 and 9: ";
        cin >> numb;
        while ( numb<5 || numb>9) 
        {
            cout << "Invalid input, please re-enter: ";
            cin >> numb;
        }
        total = total + numb;
    }
    average = total/MAX;
    cout << "The average number is: " << average << "\n";
    return 0;
}
___________________________
"Write a short code using C++ to print out all odd number from 1 to 100 using a for loop"

    for( unsigned int i = 1; i < = 100; i++ )
        if( i & 0x00000001 )
            cout << i << endl ; 

___________________________
"What is public, protected, private?"

Public, protected and private are three access specifier in C++.
Public data members and member functions are accessible outside the class.
Protected data members and member functions are only available to derived classes.
Private data members and member functions can’t be accessed outside the class. However there is an exception can be using friend classes.

PRIVATE, PROTECTED and PUBLIC – the differences and give examples:

class Point2D
{
    int x; int y;

    public int color;
    protected bool pinned;
    public Point2D() : x(0) , y(0) {} //default (no argument) constructor
};

int main() 
{
    Point2D MyPoint;
    // You cannot directly access private data members when they are declared (implicitly) private:
    MyPoint.x = 5; // Compiler will issue a compile ERROR
    //Nor you can see them:
    int x_dim = MyPoint.x; // Compiler will issue a compile ERROR
    //On the other hand, you can assign and read the public data members:
    MyPoint.color = 255; // no problem
    int col = MyPoint.color; // no problem
    // With protected data members you can read them but not write them: 
    MyPoint.pinned = true; // Compiler will issue a compile ERROR
    bool isPinned = MyPoint.pinned; // no problem
}

___________________________
"Write a function that swaps the values of two integers, using "int *" as the argument type:"

void swap(int* a, int*b) 
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

___________________________
"Tell how to check whether a linked list is circular."

Create two pointers, each set to the start of the list. Update each as follows:

while (pointer1) 
{
    pointer1 = pointer1->next;
    pointer2 = pointer2->next; 
    if (pointer2) 
        pointer2=pointer2->next;
    if (pointer1 == pointer2) 
    {
        print ("circular\n");
    }
}

"OK, why does this work?"
If a list is circular, at some point pointer2 will wrap around and be either at the item just before pointer1, or the item before that. Either way, it’s either 1 or 2 jumps until they meet.

___________________________
"What is virtual constructors/destructors?"

Virtual destructors:
If an object (with a non-virtual destructor) is destroyed explicitly by applying the "delete" operator to a base-class pointer to the object, the base-class destructor function (matching the pointer type) is called on the object.
There is a simple solution to this problem declare a virtual base-class destructor.

This makes all derived-class destructors virtual even though they don’t have the same name as the base-class destructor. Now, if the object in the hierarchy is destroyed explicitly by applying the delete operator to a base-class pointer to a derived-class object, the destructor for the appropriate class is called. Virtual constructor: Constructors cannot be virtual. Declaring a constructor as a virtual function is a syntax error.

___________________________
Virtual constructor: Constructors cannot be virtual. Declaring a constructor as a virtual function is a syntax error. 

___________________________
"What are the advantages of inheritance?"
- It permits code reusability.
- Reusability saves time in program development.
- It encourages the reuse of proven and debugged high-quality software, thus reducing problem after a system becomes functional.

___________________________
"What is the difference between declaration and definition?"
The declaration tells the compiler that at some later point we plan to present the definition of this declaration.
E.g.:
void stars () //function declaration

The definition contains the actual implementation.
E.g.: 
void stars () // declarator
{
    for(int j=10; j>=0; j--) //function body
    cout<<"*";
    cout<<endl; 
}

___________________________
"What is function overloading and operator overloading?"

Function overloading: C++ enables several functions of the same name to be defined, as long as these functions have different sets of parameters (at least as far as their types are concerned). This capability is called function overloading. When an overloaded function is called, the C++ compiler selects the proper function by examining the number, types and order of the arguments in the call. Function overloading is commonly used to create several functions of the same name that perform similar tasks but on different data types.
Operator overloading allows existing C++ operators to be redefined so that they work on objects of user-defined classes. Overloaded operators are syntactic sugar for equivalent function calls. They form a pleasant facade that doesn't add anything fundamental to the language (but they can improve understandability and reduce maintenance costs).

___________________________

"How do you write a function that can reverse a linked-list:"
1. 
void reverselist(void)
{
    if(head==0)
        return;
    if(head->next==0)
        return;
    if(head->next==tail)
    {
        head->next = 0;
        tail->next = head;
    }
    else
    {
        node* pre = head;
        node* cur = head->next;
        node* curnext = cur->next;
        head->next = 0;
        cur-> next = head;

    for(; curnext!=0; )
    {
        cur->next = pre;
        pre = cur;
        cur = curnext;
        curnext = curnext->next;
    }

    curnext->next = cur;
    }
}

2. 
node* reverselist(node* head)
{
    if(0==head || 0==head->next)
    {
        //if head->next ==0 should return head instead of 0;
        return 0;
    }
    
    node* prev = head;
    node* curr = head->next;
    node* next = curr->next;

    for(; next!=0; )
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;

    head->next = 0;
    head = curr;
    return head;
}

___________________________
"What is the difference between an ARRAY and a LIST?"
Answer1
Array is collection of homogeneous elements.
List is collection of heterogeneous elements.

For Array memory allocated is static and continuous.
For List memory allocated is dynamic and Random.

Array: User need not have to keep in track of next memory allocation.
List: User has to keep in Track of next location where memory is allocated.

Answer2
Array uses direct access of stored members, list uses sequencial access for members.

//With Array you have direct access to memory position 5
Object x = a[5]; // x takes directly a reference to 5th element of array

//With the list you have to cross all previous nodes in order to get the 5th node:
list mylist;
list::iterator it;

for( it = list.begin() ; it != list.end() ; it++ )
{
    if( i==5)
    {
        x = *it;
        break;
    }
    i++;
}

___________________________
"What is a template?"
Templates allow to create generic functions that admit any data type as parameters and return value without having to overload the function with all the possible data types. Until certain point they fulfill the functionality of a macro. Its prototype is any of the two following ones:

template <class indetifier> function_declaration; 
template <typename indetifier> function_declaration;

The only difference between both prototypes is the use of keyword class or typename, its use is indistinct since both expressions have exactly the same meaning and behave exactly the same way.

___________________________
Define a constructor - What it is and how it might be called (2 methods).
Answer1
Constructor is a member function (method) of the class, with the name of the function being the same as the class name. 
It also specifies how the object should be initialized.

Ways of calling constructor:
1. Implicitly: automatically by complier when an object is created.
2. Calling the constructors explicitly is possible, but it makes the code unverifiable.

Answer2
class Point2D
{
    int x; int y;
    public Point2D() : x(0) , y(0) {} //default (no argument) constructor
};

main()
{
    Point2D MyPoint; // Implicit Constructor call. In order to allocate memory on stack, the default constructor is implicitly called.
    Point2D * pPoint = new Point2D(); // Explicit Constructor call. In order to allocate memory on HEAP we call the default constructor. 
}
___________________________
You have two pairs: 
    new(), delete() 
    another pair 
    malloc(), free().

Explain differences between eg. new() and malloc()
Answer1
1. "new" and "delete" are preprocessors while "malloc()" and "free()" are functions. [we dont use brackets will calling new or delete].
2. no need of allocate the memory while using "new" but in "malloc()" we have to use "sizeof()".
3. "new" will initialize the new memory to 0 but "malloc()" gives random value in the new allocated memory location [better to use calloc()]

Answer2
new() allocates continous space for the object instace
malloc() allocates distributed space.
new() is castless, meaning that allocates memory for this specific type,
malloc(), calloc() allocate space for void * that is cated to the specific class type pointer. 

___________________________
"What is the difference between class and structure?"
Structure: Initially (in C) a structure was used to bundle different type of data types together to perform a particular functionality. But C++ extended the structure to contain functions also. The major difference is that all declarations inside a structure are "public" by default.
Class: "Class" is a successor of "Structure". By default all the members inside the class are "private".

___________________________
"What is namespace?"
Namespaces allow us to group a set of global classes, objects and/or functions under a name. To say it somehow, they serve to split the global scope in sub-scopes known as namespaces.
The form to use namespaces is:
namespace identifier { namespace-body }
Where identifier is any valid identifier and namespace-body is the set of classes, objects and functions that are included within the namespace. For example:
namespace general { int a, b; } In this case, a and b are normal variables integrated within the general namespace. In order to access to these variables from outside the namespace we have to use the scope operator ::. For example, to access the previous variables we would have to put:
general::a general::b
The functionality of namespaces is specially useful in case that there is a possibility that a global object or function can have the same name than another one, causing a redefinition error.

___________________________
"What is a COPY CONSTRUCTOR and when is it called?"
A copy constructor is a method that accepts an object of the same class and copies it’s data members to the object on the left part of assignement:

class Point2D
{
    int x; int y;

    public int color;
    protected bool pinned;
    public Point2D() : x(0) , y(0) {} //default (no argument) constructor
    public Point2D( const Point2D & ) ;
};

Point2D::Point2D( const Point2D & p )
{
    this->x = p.x;
    this->y = p.y;
    this->color = p.color;
    this->pinned = p.pinned;
}

main()
{
    Point2D MyPoint;
    MyPoint.color = 345;
    Point2D AnotherPoint = Point2D( MyPoint ); // now AnotherPoint has color = 345
}
___________________________
"What is "virtual class" and "friend class"?"
"Friend classes" are used when two or more classes are designed to work together and need access to each other's implementation in ways that the rest of the world shouldn't be allowed to have. In other words, they help keep private things private. For instance, it may be desirable for class DatabaseCursor to have more privilege to the internals of class Database than main() has.

___________________________
"What is the word you will use when defining a function in base class to allow this function to be a polimorphic function?"
Answer:
"virtual"

___________________________
"What do you mean by binding of data and functions?"
Encapsulation.

___________________________
"What are 2 ways of exporting a function from a DLL?"
1.Taking a reference to the function from the DLL instance.
2. Using the DLL ’s Type Library

___________________________
"What is the difference between an object and a class?"
Classes and objects are separate but related concepts. Every object belongs to a class and every class contains one or more related objects.
- A Class is static. All of the attributes of a class are fixed before, during, and after the execution of a program. The attributes of a class do not change.
- The class to which an object belongs is also (usually) static. If a particular object belongs to a certain class at the time that it is created then it almost certainly will still belong to that class right up until the time that it is destroyed.
- An Object on the other hand has a limited lifespan. Objects are created and eventually destroyed. Also during that lifetime, the attributes of the object may undergo significant change.
___________________________

"What is a class?"
Class is a user-defined data type in C++. It can be created to solve a particular kind of problem. After creation the user need not know the specifics of the working of a class.
___________________________

"What is friend function?"
As the name suggests, the function acts as a friend to a class. As a friend of a class, it can access its private and protected members. A friend function is not a member of the class. But it must be listed in the class definition.
___________________________
"What is abstraction?"
Abstraction is of the process of hiding unwanted details from the user.

___________________________
"What are virtual functions?"
A virtual function allows derived classes to replace the implementation provided by the base class. The compiler makes sure the replacement is always called whenever the object in question is actually of the derived class, even if the object is accessed by a base pointer rather than a derived pointer. This allows algorithms in the base class to be replaced in the derived class, even if users don't know about the derived class.

___________________________
"What is the difference between an external iterator and an internal iterator? Describe an advantage of an external iterator."
An internal iterator is implemented with member functions of the class that has items to step through. .An external iterator is implemented as a separate class that can be "attach" to the object that has items to step through. .An external iterator has the advantage that many difference iterators can be active simultaneously on the same object. 
___________________________
"What is a scope resolution operator?"
A scope resolution operator (::), can be used to define the member functions of a class outside the class.

___________________________
"What do you mean by pure virtual functions?"

A pure virtual member function is a member function that the base class forces derived classes to provide. Normally these member functions have no implementation. Pure virtual functions are equated to zero:

class Shape 
{ 
public: 
    virtual void draw() = 0; 
};

"What is pure virtual function?"
A class is made abstract by declaring one or more of its virtual functions to be pure. A pure virtual function is one with an initializer of = 0 in its declaration 

___________________________

"What is polymorphism? Explain with an example?"
"Poly" means "many" and "morph" means "form". Polymorphism is the ability of an object (or reference) to assume (be replaced by) or become many different forms of object.
Example: function overloading, function overriding, virtual functions. Another example can be a plus ‘+’ sign, used for adding two integers or for using it to concatenate two strings.

___________________________
"What’s the output of the following program? Why?"
#include <stdio.h>
main()
{
    typedef union
    {
        int a;
        char b[10];
        float c;
    } Union;

    Union x, y = {100};
    x.a = 50;
    strcpy(x.b,"hello");
    x.c = 21.50;
    
    printf("Union x : %d %s %f ", x.a, x.b, x.c);
    printf("Union y : %d %s%f ",  y.a, y.b, y.c);
}

___________________________
Given inputs X, Y, Z and operations | and & (meaning bitwise OR and AND, respectively)
What is output equal to in
output = (X & Y) | (X & Z) | (Y & Z)

___________________________
"Why are arrays usually processed with for loop?"
The real power of arrays comes from their facility of using an index variable to traverse the array, accessing each element with the same expression a[i]. All the is needed to make this work is a iterated statement in which the variable i serves as a counter, incrementing from 0 to a.length -1. That is exactly what a loop does.

___________________________
"What is an HTML tag?"
Answer: An HTML tag is a syntactical construct in the HTML language that abbreviates specific instructions to be executed when the HTML script is loaded into a Web browser. It is like a method in Java, a function in C++, a procedure in Pascal, or a subroutine in FORTRAN.

___________________________
"What problems might the following macro bring to the application?"
#define sq(x) x*x

___________________________
"Anything wrong with this code?"
T *p = new T[10];
delete p;

When you allocate an array of objects with "new[]", you must delete it with "delete[]". 
Failing to do so results in Undefined Behavior.

The main behavioral difference between "delete" and "delete[]" is that the latter, apart from deallocating the memory, also invokes the destructor of each object in the array.

___________________________
"Anything wrong with this code?"
T *p = 0;
delete p;

Yes, the program will crash in an attempt to delete a null pointer.

___________________________
"How do you decide which integer type to use?"
It depends on our requirement. When we are required an integer to be stored in 1 byte (means less than or equal to 255) we use short int, for 2 bytes we use int, for 8 bytes we use long int.

A char is for 1-byte integers, a short is for 2-byte integers, an int is generally a 2-byte or 4-byte integer (though not necessarily), a long is a 4-byte integer, and a long long is a 8-byte integer. 

___________________________
"What does 'extern' mean in a function declaration?"
Using extern in a function declaration we can make a function such that it can used outside the file in which it is defined.

An extern variable, function definition, or declaration also makes the described variable or function usable by the succeeding part of the current source file. This declaration does not replace the definition. The declaration is used to describe the variable that is externally defined.

If a declaration for an identifier already exists at file scope, any extern declaration of the same identifier found within a block refers to that same object. If no other declaration for the identifier exists at file scope, the identifier has external linkage.

___________________________
"What can I safely assume about the initial values of variables which are not explicitly initialized?"
It depends on complier which may assign any garbage value to a variable if it is not initialized.

___________________________
What is the difference between 
char array[] = "string"; 
And
char *p = "string";

In the first case: 6 bytes are allocated to the variable 'array' which is fixed, 
where as in the second case if *p is assigned to some other value the allocate memory can change.

The difference is:
p is pointing to a constant string, you can never safely say
p[3]=’x';
however you can always say array[3]='x';

char a[]="string"; - character array initialization.
char *p="string" ; - non-const pointer to a const-string.( this is permitted only in the case of char pointer in C++ to preserve backward compatibility with C.)

___________________________

"What’s the auto keyword good for?"

Not much. It declares an object with automatic storage duration. Which means the object will be destroyed at the end of the objects scope. All variables in functions that are not declared as static and not dynamically allocated have automatic storage duration by default.

For example:
int main()
{
    int a; //this is the same as writing “auto int a;”
}

Answer2:
Local variables occur within a scope; they are “local” to a function. They are often called automatic variables because they automatically come into being when the scope is entered and automatically go away when the scope closes. The keyword auto makes this explicit, but local variables default to auto auto auto auto so it is never necessary to declare something as an auto auto auto auto.

___________________________
"How do I declare an array of N pointers to functions returning pointers to functions returning pointers to characters?"

Answer1
If you want the code to be even slightly readable, you will use typedefs.
typedef char* (*functiontype_one)(void);
typedef functiontype_one (*functiontype_two)(void);
functiontype_two myarray[N]; //assuming N is a const integral

Answer2
char* (* (*a[N])())()

Here a is that array. And according to question no function will not take any parameter value.

___________________________
"What does extern mean in a function declaration?"

It tells the compiler that a variable or a function exists, even if the compiler hasn’t yet seen it in the file currently being compiled. This variable or function may be defined in another file or further down in the current file.

___________________________
"How do I initialize a pointer to a function?"
This is the way to initialize a pointer to a function
void fun(int a)
{

}

void main()
{
    void (*fp)(int);
    fp=fun;
    fp(1);
}

___________________________
"How do you link a C++ program to C functions?"
By using the extern "C" linkage specification around the C function declarations.

___________________________
Explain the scope resolution operator.
It permits a program to reference an identifier in the global scope that has been hidden by another identifier with the same name in the local scope.

___________________________
"What are the differences between a C++ struct and C++ class?"

The default member and base-class access specifier are different.

___________________________
"How many ways are there to initialize an int with a constant?"
Two.
There are two formats for initializers in C++ as shown in the example that follows. The first format uses the traditional C notation. The second format uses constructor notation.
int foo = 123;
int bar (123);

___________________________
"How does throwing and catching exceptions differ from using setjmp and longjmp?"

The throw operation calls the destructors for automatic objects instantiated since entry to the try block.
___________________________

"What is a conversion constructor?"
A constructor that accepts one argument of a different type.

___________________________
"What is the difference between a copy constructor and an overloaded assignment operator?"
A copy constructor constructs a new object by using the content of the argument object. An overloaded assignment operator assigns the contents of an existing object to another existing object of the same class.

___________________________
When should you use multiple inheritance?
There are three acceptable answers: "Never," "Rarely," and "When the problem domain cannot be accurately modeled any other way."

___________________________
"Explain the ISA and HASA class relationships. How would you implement each in a class design?"
A specialized class "is" a specialization of another class and, therefore, has the ISA relationship with the other class. An Employee ISA Person. This relationship is best implemented with inheritance. Employee is derived from Person. A class may have an instance of another class. For example, an employee "has" a salary, therefore the Employee class has the HASA relationship with the Salary class. This relationship is best implemented by embedding an object of the Salary class in the Employee class.

___________________________
"When is a template a better solution than a base class?"
When you are designing a generic class to contain or otherwise manage objects of other types, when the format and behavior of those other types are unimportant to their containment or management, and particularly when those other types are unknown (thus, the generosity) to the designer of the container or manager class.

___________________________
"What is an explicit constructor?"
A conversion constructor declared with the explicit keyword. The compiler does not use an explicit constructor to implement an implied conversion of types. It’s purpose is reserved explicitly for construction.

___________________________
"What is a mutable member?"
One that can be modified by the class even when the object of the class or the member function doing the modification is const.

___________________________
"What is mutable?"
Answer1.
"mutable" is a C++ keyword. When we declare const, none of its data members can change. When we want one of its members to change, we declare it as mutable.

Answer2.
A "mutable" keyword is useful when we want to force a "logical const" data member to have its value modified. A logical const can happen when we declare a data member as non-const, but we have a const member function attempting to modify that data member. For example:

class Dummy 
{
public:
    bool isValid() const;
private:
    mutable int size_ = 0;
    mutable bool validStatus_ = FALSE;
    // logical const issue resolved
};

bool Dummy::isValid() const
// data members become bitwise const
{
    if (size > 10) 
    {
        validStatus_ = TRUE; // fine to assign
        size = 0; // fine to assign
    }
}


Answer2.
"mutable" keyword in C++ is used to specify that the member may be updated or modified even if it is member of constant object. Example:
class Animal 
{
private:
    string name;
    string food;
    mutable int age;
public:
    void set_age(int a);
};

void main() 
{
    const Animal Tiger(Fulffy, "antelope", 1);
    Tiger.set_age(2);
    // the age can be changed since its mutable
}

___________________________
Differentiate between a template class and class template.
Template class: A generic definition or a parameterized class not instantiated until the client provides the needed information. It’s jargon for plain templates. Class template: A class template specifies how individual classes can be constructed much like the way a class specifies how individual objects can be constructed. It’s jargon for plain classes.

___________________________
Define namespace.
It is a feature in C++ to minimize name collisions in the global name space. This namespace keyword assigns a distinct name to a library that allows other libraries to use the same identifier names without creating any name collisions. Furthermore, the compiler uses the namespace signature for differentiating the definitions.
___________________________
"What is the use of "using" declaration. ?"
A using declaration makes it possible to use a name from a namespace without the scope operator.
___________________________

"What is an Iterator class ?"

A class that is used to traverse through the objects maintained by a container class. There are five categories of iterators: input iterators, output iterators, forward iterators, bidirectional iterators, random access. An iterator is an entity that gives access to the contents of a container object without violating encapsulation constraints. Access to the contents is granted on a one-at-a-time basis in order. The order can be storage order (as in lists and queues) or some arbitrary order (as in array indices) or according to some ordering relation (as in an ordered binary tree). The iterator is a construct, which provides an interface that, when called, yields either the next element in the container, or some value denoting the fact that there are no more elements to examine. Iterators hide the details of access to and update of the elements of a container class.
The simplest and safest iterators are those that permit read-only access to the contents of a container class. 
___________________________

"What is an incomplete type?"
Incomplete types refers to pointers in which there is non availability of the implementation of the referenced location or it points to some location whose value is not available for modification.

int *i=0x400 // i points to address 400
*i=0; //set the value of memory location pointed by i.

Incomplete types are otherwise called uninitialized pointers.
___________________________

"What is a dangling pointer?"
A dangling pointer arises when you use the address of an object after
its lifetime is over. This may occur in situations like returning
addresses of the automatic variables from a function or using the
address of the memory block after it is freed. The following
code snippet shows this

class Sample
{
public:
int *ptr;
Sample(int i)
{
ptr = new int(i);
}

~Sample()
{
delete ptr;
}
void PrintVal()
{
cout << "The value is " << *ptr;
}
};

void SomeFunc(Sample x)
{
cout << "Say i am in someFunc " << endl;
}

int main()
{
Sample s1 = 10;
SomeFunc(s1);
s1.PrintVal();
}

In the above example when PrintVal() function is
called it is called by the pointer that has been freed by the
destructor in SomeFunc.
___________________________

"What is an adaptor class or Wrapper class?"
A class that has no functionality of its own. Its member functions hide the use of a third party software component or an object with the non-compatible interface or a non-object-oriented implementation.
___________________________

"What is a Null object?"
It is an object of some class whose purpose is to indicate that a real object of that class does not exist. One common use for a null object is a return value from a member function that is supposed to return an object with some specified properties but cannot find such an object. 
___________________________

"What is class invariant?"
A class invariant is a condition that defines all valid states for an object. It is a logical condition to ensure the correct working of a class. Class invariants must hold when an object is created, and they must be preserved under all operations of the class. In particular all class invariants are both preconditions and post-conditions for all operations or member functions of the class.

___________________________
"What do you mean by Stack unwinding?"
It is a process during exception handling when the destructor is called for all local objects between the place where the exception was thrown and where it is caught.

___________________________
Define precondition and post-condition to a member function.
Precondition: A precondition is a condition that must be true on entry to a member function. A class is used correctly if preconditions are never false. An operation is not responsible for doing anything sensible if its precondition fails to hold. For example, the interface invariants of stack class say nothing about pushing yet another element on a stack that is already full. We say that isful() is a precondition of the push operation. Post-condition: A post-condition is a condition that must be true on exit from a member function if the precondition was valid on entry to that function. A class is implemented correctly if post-conditions are never false. For example, after pushing an element on the stack, we know that isempty() must necessarily hold. This is a post-condition of the push operation.

___________________________
"What are the conditions that have to be met for a condition to be an invariant of the class?"
- The condition should hold at the end of every constructor.
- The condition should hold at the end of every mutator (non-const) operation.
___________________________
Name some pure object oriented languages.
Smalltalk, Java, Eiffel, Sather. 

___________________________
"What is an orthogonal base class?"
If two base classes have no overlapping methods or data they are said to be independent of, or orthogonal to each other. Orthogonal in the sense means that two classes operate in different dimensions and do not interfere with each other in any way. The same derived class may inherit such classes with no difficulty.

___________________________
Write a Struct Time where integer m, h, s are its members:
struct Time
{
    int m;
    int h;
    int s;
};

___________________________
"What is the two main roles of Operating System?"
As a resource manager
As a virtual machine

___________________________
"In the derived class, which data member of the base class are visible?"
In the public and protected sections.

___________________________
"What is semaphore?"
Semaphore is a special variable, it has two methods: up and down. Semaphore performs atomic operations, which means ones a semaphore is called it can not be interrupted.

___________________________
"Is C an object-oriented language?"
C is not an object-oriented language, but limited object-oriented programming can be done in C.

___________________________
"Name some major differences between C++ and Java."
C++ has pointers; Java does not. 
REM: Java does have pointers. In fact all variables in Java are pointers. The difference is that Java does not allow you to manipulate the addresses of the pointer

Java is platform-independent; C++ is not. 

Java has garbage collection; C++ does not. 
___________________________

"What is the difference between Stack and Queue?"
Stack is a Last In First Out (LIFO) data structure.
Queue is a First In First Out (FIFO) data structure

___________________________
Write a fucntion that will reverse a string.
int getline(char s[]) 
{
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}

char * reverse(char s[]) 
{
    int string_length;
    string_length = getline(s);
    char myString[MAXLINE];
    int i, a =0;
    i = string_length-1;
    while (i >= 0) {
        myString[a]=s[i];
        a++;
        i--;
    }
    myString[a] ='\0';
    copy(s, myString);

    return s;
}

___________________________
"What is the software Life-Cycle?"
The software Life-Cycle are
1. Analysis and specification of the task
2. Design of the algorithms and data structures
3. Implementation (coding)
4. Testing
5. Maintenance and evolution of the system
6. Obsolescence

___________________________
"Name 7 layers of the OSI Reference Model?"
- Application layer
- Presentation layer
- Session layer
- Transport layer
- Network layer
- Data Link layer
- Physical layer

___________________________
"Describe Stacks and name a couple of places where stacks are useful."

A Stack is a linear structure in which insertions and deletions are always made at one end, called the top. This updating policy is called last in, first out (LIFO). It is useful when we need to check some syntex errors, such as missing parentheses.





___________________________


