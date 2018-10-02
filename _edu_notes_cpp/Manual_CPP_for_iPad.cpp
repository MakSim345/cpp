1. Pass objects to Functions

-----------------------
Pass by value:
-----------------------

void func (vector v)

Pass variables by value when the function needs complete isolation from the environment i.e. to prevent the function from modifying the original variable as well as to prevent other threads from modifying its value while the function is being executed. This is the default in C/C++.

The downside is the CPU cycles and extra memory spent to copy the object.

-----------------------
Pass by const reference:
-----------------------

void func (const vector & v);

The main intention of this form is to allow pass-by-value behavior while removing the copying overhead. This gives the function read-only access to the original object, but it cannot modify its value.

The downside is thread safety: any change made to the original object by another thread will show up inside the function while it is still executing.

-----------------------
Pass by non-const reference:
-----------------------

void func (vector & v)

Use this if modifications made to the variable inside the function need to be reflected outside.

Just like the const reference case, this is not thread safe.

-----------------------
Pass by const pointer:
-----------------------

void func (const vector * vp);

Functionally same as pass by const-reference except for the different syntax, plus the fact that the calling function can pass NULL pointer to indicate that it has no valid data to pass.

Not thread safe.

-----------------------
Pass by non-const pointer:
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
...and optional
-----------------------

void modifies(T *param=0);  // default value optional, too
// vs
void modifies();
void modifies(T &param);

-----------------------
Parameter not modified
-----------------------
void uses(T const &param);
// vs
void uses(T param);

This is the interesting case. The rule of thumb is "cheap to copy" types are passed by value — these are generally small types (but not always) — while others are passed by const ref. However, if you need to make a copy within your function regardless, you should pass by value. (Yes, this exposes a bit of implementation detail. C'est le C++.')

-----------------------
...and optional
-----------------------

void uses(T const *param=0);  // default value optional, too
// vs
void uses();
void uses(T const &param);  // or optional(T param)

There is the least difference here between all situations, so choose whichever makes your life easiest.
-----------------------
Const by value is an implementation detail
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

So, to summarize-

   - Pass-by-value and pass-by-const-reference imply similar things - you want to be able to look at the value without being able to modify it.
   - Any time you could use pass-by-value you could instead use pass-by-const-reference without affecting the correctness of the program. However, there are performance tradeoffs between the indirection of the reference and the cost of copying and destructing the parameter.
   - Pass-by-non-const-reference should be used to indicate "I want to modify the argument."
   - You cannot pass rvalues into functions that take their arguments by non-const reference.

Hope this helps!

2. Reference Parameters in C++: VERY basic example.

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

3. Reference vs. pointers
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

4. Stack vs. heap
Stack:
- Stored in computer RAM just like the heap.
- Variables created on the stack will go out of scope and automatically deallocate.
- Much faster to allocate in comparison to variables on the heap.
- Implemented with an actual stack data structure.
- Stores local data, return addresses, used for parameter passing
- Can have a stack overflow when too much of the stack is used. (mostly from infinite (or too much) recursion, very large allocations)
- Data created on the stack can be used without pointers.
- You would use the stack if you know exactly how much data you need to allocate before compile time and it is not too big.
- Usually has a maximum size already determined when your program starts


Heap:
- Stored in computer RAM just like the stack.
- Variables on the heap must be destroyed manually and never fall out of scope. The data is freed with delete, delete[] or free
- Slower to allocate in comparison to variables on the stack.
- Used on demand to allocate a block of data for use by the program.
- Can have fragmentation when there are a lot of allocations and deallocations
- In C++ data created on the heap will be pointed to by pointers and allocated with new or malloc
- Can have allocation failures if too big of a buffer is requested to be allocated.
- You would use the heap if you do not know exactly how much data you will need at runtime or if you need to allocate a lot of data.
- Responsible for memory leaks

Example:

int foo()
{
  char *pBuffer; //<--nothing allocated yet (excluding the pointer itself, which is allocated here on the stack).
  bool b = true; // Allocated on the stack.
  if(b)
  {
    //Create 500 bytes on the stack
    char buffer[500];

    //Create 500 bytes on the heap
    pBuffer = new char[500];

   }//<-- buffer is deallocated here, pBuffer is not
}//<--- oops there's a memory leak, I should have called delete[] pBuffer;

5. Templates. Шаблоны классов в С++

Мы уже ранее рассматривали в С++ такой инструмент, как  шаблоны, когда создавали шаблоны функций. Почему стоит пользоваться шаблонами, было написано в статье, с шаблонами функций. Там мы рассмотрели основные положения шаблонов в С++. Давайте их вспомним.

Любой шаблон начинается со слова template, будь то шаблон функции или шаблон класса. После  ключевого слова template идут угловые скобки - < >, в которых перечисляется список параметров шаблона. Каждому параметру должно предшествовать зарезервированное слово class или typename. Отсутствие этих ключевых слов будет расцениваться компилятором как синтаксическая ошибка. Некоторые примеры объявления шаблонов:

template <class T>
template <typename T>
template <typename T1, typename T2>

Ключевое слово typename говорит о том, что в шаблоне будет использоваться встроенный тип данных, такой как: int, double,float, char и т. д. А ключевое слово class сообщает компилятору, что в шаблоне функции в качестве параметра будут использоваться пользовательские типы данных, то есть классы. Но не в коем случае не путайте параметр шаблона и шаблон класса. Если нам надо создать шаблон класса, с одним параметром типа int и char, шаблон класса будет выглядеть так:

template <typename T>
class Name
{
    //тело шаблона класса
};

где T — это параметр шаблона класса, который может принимать любой из встроенных типов данных, то, что нам и нужно.

А если параметр шаблона класса должен пользовательского типа, например типа Array, где Array — это класс, описывающий массив, шаблон класса будет иметь следующий вид:

template <class T>
class Name
{
    //тело шаблона класса
};

C этим вам лучше разобраться изначально, чтобы потом не возникало никаких ошибок, даже, если шаблон класса написан правильно.

Давайте создадим шаблон класса Стек, где стек — структура данных,  в которой хранятся однотипные элементы данных. В стек можно помещать и извлекать данные. Добавляемый элемент в стек, помещается в вершину стека. Удаляются элементы стека, начиная с его вершины. В шаблоне класса Stack необходимо создать основные методы:

    "Push" - добавить элемент в стек;
    "Pop"   - удалить элемент из стека
    "printStack" — вывод стека на экран;

Итак реализуем эти три метода, в итоге получим самый простой класс, реализующий работу структуры стек. Не забываем про конструкторы и деструкторы. Смотрим код ниже.
#include "stdafx.h"
#include <iostream>
 
using namespace std;
 
#include <iomanip>
 
template <typename T>
class Stack
{
private:
    T *stackPtr; // указатель на стек
    int size; // размер стека
    T top; // вершина стека
public:
    Stack(int = 10);// по умолчанию размер стека равен 10 элементам
    ~Stack(); // деструктор
    bool push(const T  ); // поместить элемент в стек
    bool pop(); // удалить из стека элемент
    void printStack();
};
 
int main()
{
    Stack <int> myStack(5);
 
    // заполняем стек
    cout << "Заталкиваем элементы в стек: ";
    int ct = 0;
    while (ct++ != 5)
    {
        int temp;
        cin >> temp;
        myStack.push(temp);
    }
 
    myStack.printStack(); // вывод стека на экран
 
    cout << "\nУдаляем два элемента из стека:\n";
 
    myStack.pop(); // удаляем элемент из стека
    myStack.pop(); // удаляем элемент из стека
    myStack.printStack(); // вывод стека на экран
 
    return 0;
}
 
// конструктор
template <typename T>
Stack<T>::Stack(int s)
{
    size = s > 0 ? s: 10;   // инициализировать размер стека
    stackPtr = new T[size]; // выделить память под стек
    top = -1; // значение -1 говорит о том, что стек пуст
}
 
// деструктор
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; // удаляем стек
}
 
// элемент функция класса  Stack для помещения элемента в стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, элемент в стек не добавлен
template <typename T>
bool Stack<T>::push(const T value)
{
    if (top == size - 1)
        return false; // стек полон
 
    top++;
    stackPtr[top] = value; // помещаем элемент в стек
 
    return true; // успешное выполнение операции
}
 
// элемент функция класса  Stack для удаления элемента из стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, стек пуст
template <typename T>
bool Stack<T>::pop()
{
    if (top == - 1)
        return false; // стек пуст
 
    stackPtr[top] = 0; // удаляем элемент из стека
    top--;
 
    return true; // успешное выполнение операции
}
 
// вывод стека на экран
template <typename T>
void Stack<T>::printStack()
{
    for (int ix = size -1; ix >= 0; ix--)
        cout << "|" << setw(4) << stackPtr[ix] << endl;
}

Как видите шаблон класса Stack объявлен и определен в файле с main-функцией. Конечно же такой способ утилизации шаблонов никуда не годится, но для примера сойдет. В строках 7 — 20 объявлен интерфейс шаблона класса.  Объявление класса выполняется привычным для нас образом, а перед классом находится объявление шаблона, в строке 7. При объявлении шаблона класса, всегда используйте такой синтаксис.

Строки 47 — 100 содержат элемент-функции шаблона класса Stack, причем перед каждой функцией необходимо объявлять шаблон, точно такой же, как и перед классом - template <typename T>. То есть получается, элемент-функции шаблона класса, объявляются точно также, как и обычные шаблоны функций. Если бы мы описали реализацию методов внутри класса, то заголовок шаблона - template <typename T> для каждой функции прописывать не надо.

Чтобы привязать каждую элемент-функцию к шаблону класса, как обычно используем бинарную операцию разрешения области действия — :: с именем шаблона класса - Stack<T>. Что мы и сделали в строках 49, 58, 68, 83, 96.

Обратите внимание на объявление объекта myStack шаблона класса Stack в функции main, строка 24. В угловых скобочка необходимо явно указывать используемый тип данных, в шаблонах функций этого делать не нужно было. Далее в main запускаются некоторые функции, которые демонстрируют работу шаблона класса Stack.
END.
----------------
6. Virtual Functions
Тут без виртуальности — ну никак!

Зачем нужны виртуальные функции
При наследовании часто бывает необходимо, чтобы поведение некоторых методов базового класса и классов-наследников отличались. Решение, на первый взгляд, очевидное: переопределить соответствующие методы в производном классе. Однако тут возникает одна проблема, которую лучше рассмотреть на простом примере (листинг 9.1).

//Листинг 9.1. Необходимость виртуальных функций
#include <iostream>
using namespace std;
class Base                                 // базовый класс
{  public:
    int f(const int &d)                    // метод базового класса
    { 
        return 2*d; 
    }
    
    int CallFunction(const int &d)         // предполагается
    { 
        return f(d)+1;                       // вызов метода базового класса
    }
};

class Derived: public Base                 // производный класс
{  public:                                 // CallFunction наследуется
    int f(const int &d)                    // метод f переопределяется
    { 
        return d*d; 
    }
};

int main()
{   Base a;                                // объект базового класса
    cout << a.CallFunction(5)<< endl;      // получаем 11
    Derived b;                             // объект производного власса
    cout << b.CallFunction(5)<< endl;      // какой метод f вызывается?
    return 0;
}

В базовом классе определены два метода — f() и CallFunction(), — причем во втором методе вызывается первый. В классе-наследнике метод f() переопределен, а метод CallFunction() унаследован. Очевидно, метод f() переопределяется для того, чтобы объекты базового класса и класса-наследника вели себя по-разному. Объявляя объект b типа Derived, программист, естественно, ожидает получить результат 5 * 5 + 1 = 26 — для этого и переопределялся метод f(). Однако на экран, как и для объекта а типа Base, выводится число 11, которое очевидно вычисляется как 2 * 5 + 1 = 11. Несмотря на переопределение метода f() в классе-наследнике, в унаследованной функции CallFunction() вызывается «родная» функция f(), определенная в базовом классе!
Аналогичная проблема возникает и в несколько другом контексте: при подстановке ссылки или указателя на объект производного класса вместо ссылки или указателя на объект базового. Рассмотрим опять пример с часами и будильником (листинг 9.2).
// Листинг 9.2. Неожиданная работа принципа подстановки
// REM: tested in edu_43_interface.
class Clock               // базовый класс — часы
{ public:
    void print() const { cout << "Clock!" << endl; }
};
class Alarm: public Clock // производный класс — будильник
{ public:
    void print() const    // переопределенный метод
    { cout << "Alarm!" << endl; }
};
void settime(Clock &d)    // функция установки времени
{ d.print(); }            // предполагается вызов метода базового класса
//...
Clock W;                  // объект базового класса
settime(W);               // выводится "Clock"
Alarm U;                  // объект производного класса
settime(U);               // ссылка на производный вместо базового 
Clock *c1 = &W;           // адрес объекта базового класса
c1->print();              // вызов базового метода 
c1 = &U;                  // адрес объекта производного типа вместо базового
c1->print();              // какой метод вызываетя, базовый или производный?

Опять в классе-наследнике переопределен метод для того, чтобы обеспечить различное поведение объектов базового и производного классов. Однако и при передаче параметра по ссылке базового класса в функцию settime(), и при явном вызове метода print() через указатель базового класса наблюдается одна и та же картина: всегда вызывается метод базового класса, хотя намерения программиста состоят в том, чтобы вызвать метод производного.
Для того чтобы разобраться в ситуации, необходимо уяснить, что такое связывание. Связывание — это сопоставление вызова функции с телом. В приведенных ранее примерах связывание выполняется на этапе трансляции (до запуска) программы. Такое связывание обычно называют ранним, или статическим.

При трансляции класса Base (см. листинг 9.1) компилятор ничего не знает о классах-наследниках , поэтому он не может предполагать, что метод f() будет переопределен в классе Derived. Его естественное поведение — «прочно» связать вызов f() с телом метода класса Base. Аналогично при трансляции функции settime() компилятору ничего не известно о типе реально передаваемого объекта во время выполнения программы. Поэтому вызов метода print() связывается с телом метода базового класса Clock, как и определено в заголовке функции settime(). Точно так же указатель на базовый класс «прочно» связывается с методом базового класса во время трансляции.
Конечно, при вызове метода по указателю в данном конкретном случае мы можем вызвать метод производного класса, задав явное преобразование указателя:
static_cast<Alarm*>(c1)->print();

Или так:
((Alarm *)c1)->print();                // "лишние" скобки нужны!

Однако для функции settime() и метода CallFunction() это сделать невозможно — нам необходимо именно разное поведение в зависимости от типа объекта. Да и с указателем не все так просто: если такой вызов прописан внутри функции, которая принимает этот указатель как параметр (например, settime(Clock *c1)), то мы имеем те же проблемы.

"Определение виртуальных функций"
Получается, что в С++ должен существовать механизм, с помощью которого можно узнать тип объекта во время выполнения программы. Такой механизм в С++ есть и он, как уже отмечалось, называется динамической идентификацией типов (RTTI). Однако в ситуациях, подобных описанным, применяется другой, более «сильный» и элегантный механизм С++ — механизм виртуальных функций (см. п. 10.3 в Стандарте).

Чтобы добиться разного поведения в зависимости от типа, необходимо объявить функцию-метод виртуальной; в С++ это делается с помощью ключевого слова virtual. Таким образом, в листинге 9.1 объявление метода f() в базовом и производном классе должно быть таким:

virtual int f(const int &d)                // в базовом классе
            { return 2*d; }
virtual int f(const int &d)                // в производном классе
            { return d*d; }

После этого для объектов базового и производного классов мы получаем разные результаты: 11 и 26.
Аналогично в листинге 9.2 объявление метода print() тоже должно начинаться со слова virtual:

virtual    void print() const              // в базовом классе
{ cout << "Clock!" << endl; }
virtual    void print() const              // в производном классе
{ cout << "Alarm!" << endl; }

После этого вызов settime() с параметром базового класса обеспечит нам вывод на экран слова «Clock», а с параметром производного класса — слова «Alarm». И при вызове по указателю наблюдается та же картина.

Вообще-то ключевое слово virtual достаточно написать только один раз — в объявлении функции базового класса. Определение можно писать без слова virtual — все равно функция будет считаться виртуальной. Однако лучше всегда это делать явным образом, чтобы всегда по тексту было видно, что функция является виртуальной.

Для виртуальных функций обеспечивается не статическое, а динамическое (позднее, отложенное) связывание, которое реализуется во время выполнения программы. Естественно, это влечет за собой некоторые накладные расходы, однако на них можно не обращать внимания, так как обеспечивается динамический полиморфизм. 

Александреску указывает, что в С++ реализованы два типа полиморфизма:
1. "статический полиморфизм", или полиморфизм времени компиляции ("compile-time polymorphism"), осуществляется за счет перегрузки и шаблонов функций;
2. "динамический полиморфизм", или полиморфизм времени выполнения ("run-time polymorphism"), реализуется виртуальными функциями.

С перегрузкой функций «разбирается» компилятор, правильно подбирая вариант функции в той или иной ситуации. И полиморфизм шаблонных функций тоже реализуется на этапе компиляции. Естественно, выбор осуществляется статически. Выбор же виртуальной функции происходит динамически — при выполнении программы. Класс, включающий виртуальные функции, называется полиморфным.

Правила описания и использования виртуальных функций-методов следующие:
1. Виртуальная функция может быть только методом класса.
2. Любую перегружаемую операцию-метод класса можно сделать виртуальной, например, операцию присваивания или операцию преобразования типа.
3. Виртуальная функция, как и сама виртуальность, наследуется.
4. Виртуальная функция может быть константной.
5. Если в базовом классе определена виртуальная функция, то метод производного класса с такими же именем и прототипом (включая тип возвращаемого значения и константность метода) автоматически является виртуальным (слово virtual указывать необязательно) и замещает функцию-метод базового класса.
6. "Конструкторы не могут быть виртуальными.!"
7. Статические методы не могут быть виртуальными.
8. Деструкторы могут (чаще — должны) быть виртуальными — это гарантирует корректный возврат памяти через указатель базового класса.

7. Class Vs. structure
- What is the difference between class and structure in C++?

-Structure:
Initially (in C) a structure was used to bundle different type of data types together to perform a particular functionality.
But C++ extended the structure to contain functions also.

The major difference is that all declarations inside a "structure" are "public" by default.

-Class:
"Class" is a successor of "Structure". By default all the members inside the class are "private".

8. Delete and delete[]
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

but correspondingly if we simply use "delete ptr" for this case, compiler will not know how many objects that ptr is pointing to and will end up calling of destructor and deleting memory for only 1 object (leaving the invocation of destructors and deallocation of remaining 99 objects). Hence there will be a memory leak

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
In short, "delete []" invokes the destructor on every element in the allocated array, while delete assumes you have exactly one instance. 
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

// NOTE: One can free the memory even by delete p;, but it will free only the first element memory.
// You delete [] when you newed an array type, and delete when you didn't. Examples:

typedef int int_array[10];

int* a = new int;
int* b = new int[10];
int* c = new int_array;

delete a;
delete[] b;
delete[] c; // this is a must! even if the new-line didn't use [].

9. Virtual destructor
- virtual destructor. Why it is virtual and what does it mean?
"http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors"

A virtual destructor ensures a C++ object will correctly call the destructor of the most-derived class when a polymorphic object is deleted through a pointer to its base class.

Virtual destructors are useful when you can delete an instance of a derived class through a pointer to base class:
____________________________
#include <iostream>
using namespace std;
class base
{
public:
    base(){cout<<"Base Constructor Called\n";}
   ~base(){cout<<"Base Destructor called\n";}
    //virtual ~base(){cout<<"Base Destructor called\n";}

};
class derived1:public base
{

public:
    derived1(){cout<<"Derived constructor called\n";}
   ~derived1(){cout<<"Derived destructor called\n";}
};
____________________________

Here, you'll notice that I didn't declare "base" destructor to be virtual.
Now, let's have a look at the following snippet:
____________________________
int main()
{
    base* b;
    b=new derived1;
    delete b; // Here's the problem!
}
____________________________
Output:
Base Constructor Called
Derived constructor called
Base Destructor called
____________________________

Since Base's destructor is not virtual and b is a base* pointing to a derived1 object, delete b has undefined behaviour. 
In most implementations, the call to the destructor will be resolved like any non-virtual code, 
meaning that the destructor of the base class will be called but not the one of the derived class, resulting in resources leak.

To sum up, always make base classes' destructors virtual when they're meant to be manipulated polymorphically.

If you want to prevent the deletion of an instance through a base class pointer, you can make the base class destuctor protected and nonvirtual; by doing so, the compiler won't let you call delete on a base class pointer.

10. General interview questions.
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
If an object (with a non-virtual destructor) is destroyed explicitly by applying the delete operator to a base-class pointer to the object, the base-class destructor function (matching the pointer type) is called on the object.
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
1. "new" and "delete" are preprocessors while “malloc() and free()” are functions. [we dont use brackets will calling new or delete].
2. no need of allocate the memory while using “new” but in “malloc()” we have to use “sizeof()”.
3. "new" will initlize the new memory to 0 but "malloc()" gives random value in the new alloted memory location [better to use calloc()]

Answer2
new() allocates continous space for the object instace
malloc() allocates distributed space.
new() is castless, meaning that allocates memory for this specific type,
malloc(), calloc() allocate space for void * that is cated to the specific class type pointer. 

___________________________
"What is the difference between class and structure?"
Structure: Initially (in C) a structure was used to bundle different type of data types together to perform a particular functionality. But C++ extended the structure to contain functions also. The major difference is that all declarations inside a structure are by default public.
Class: Class is a successor of Structure. By default all the members inside the class are private.

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
What is the software Life-Cycle?
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

