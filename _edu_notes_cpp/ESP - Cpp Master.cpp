___________________________________________
"TOPIC" JAN-2015
Give parameter to function by reference.

void modifies(T &param);
// vs
void modifies(T *param);

This case is mostly about style: do you want the code to look like "call(obj)" or "call(&obj)"?

1. Pass by value:

void func (vector v)

Pass variables by value when the function needs complete isolation from the environment i.e. to prevent the function from modifying the original variable as well as to prevent other threads from modifying its value while the function is being executed. This is the default in C/C++.

The downside is the CPU cycles and extra memory spent to copy the object.

2. Pass by const reference:

void func (const vector & v);

The main intention of this form is to allow pass-by-value behavior while removing the copying overhead. This gives the function read-only access to the original object, but it cannot modify its value.

The downside is thread safety: any change made to the original object by another thread will show up inside the function while it is still executing.

3. Pass by non-const reference:

void func (vector & v)

Use this if modifications made to the variable inside the function need to be reflected outside.

Just like the const reference case, this is not thread safe.

4. Pass by const pointer:

void func (const vector * vp);

Functionally same as pass by const-reference except for the different syntax, plus the fact that the calling function can pass NULL pointer to indicate that it has no valid data to pass.

Not thread safe.

5. Pass by non-const pointer:

void func (vector * vp);

Has the advantage of pass by const pointer, where the caller can set it to null to indicate no data is passed. This is used in many glibc APIs.
Example:

void func (string * str, /* ... */)
{
    if (str != NULL)
    {
        *str = "some_value"; // assign to *sig only if it is non-null
    }
}

As with all pass by reference/pointer, not thread safe.

___________________________________________
"TOPIC" DEC-2014
Give parameter to function by const reference.
It looks like parameter by value, but in reality it is not.

int  squareByRefConst(const int& iRef)
{
    cout << "called squareByReference..." << endl;
    // iRef *= iRef; - not allowed!!!
    return iRef*iRef;
}

void squareByReference(int& iRef)
{
    cout << "called squareByReference..." << endl;
    iRef *= iRef;
}

int add(int x, int &y, int z)
{
    // REM: int &y must be a variable, any "just numbers" will occure errors!
    return x + y + z;
}

int main( int argc, char *argv[] )
{
    using namespace std;
    int z = 4;
    cout << "3 + 4 + 5 = " << add(3, z, 5) << endl;
    // cout << "3 + 4 + 5 = " << add(3, 4, 5) << endl; - not allowed!!

    cout << "before: z = "<< z << endl;
    squareByReference(z);
    cout << "after: z = "<< z << endl;

    cout << endl;
}


___________________________________________
"TOPIC" DEC-2014
In heade files, "pragma once"
#ifndef MSF_MSGFIELD_ALARMSILENCEREADIF_HPP

shall include namespace to top level.

___________________________________________
"TOPIC" DEC-2014

C++ interface and realization:

- all functions in interface class are "pure" virtual (set equal to zero):

    virtual void setDeepPause(bool isDeepP) = 0;

Example of a class:

class OvenIf
{
public:
    virtual ~OvenIf(){}

    virtual void start()=0;
    virtual void stop()=0;
    virtual void open()=0;
    virtual void close()=0;
    virtual bool canBake()=0;

private:
    int _oven_type;
};

- interface class can not be instantiated! Need to derive some other class and implement all functions.

class ElectricOven: public OvenIf { /* function implementation here*/};
___________________________________________
"TOPIC" DEC-2014

namespace:

(Hannu was pissed off about this one...)

___________________________________________
"TOPIC" DEC-2014

mutable and const in class:

- if class has "const" in the end, it means nothing can be changed there:

    bool isZeroVolume() const;

- except variable which is set as "mutable":

    mutable int viewContentsM;

(Kalle was surprized I do not really familiar with it)
___________________________________________
"TOPIC" DEC-2014

initialization lists in c++ classes:

- preferrable to use, because it does save time during class initialization:

// Bad way:
ABEntry(const std::string & name, const std::string & address, const std::list < PhoneNumber > &phones)
{
    theName = name;     // this is not initialization, but "присваивание"
    theAddress = address;
    thePhones = phones;
    numTimesConsulted = 0;
}
// Better way:
ABEntry2(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
    :theName(name)
    ,theAddress(address)
    ,thePhones(phones)
    ,numTimesConsulted(0)  // this is all initialization!
{
    // empty constructor body.
}

Этот конструктор "ABEntry2" дает тот же самый конечный результат, что и предыдущий, но часто оказывается более эффективным.
Версия, основанная на присваиваниях, сначала вызывает конструкторы по умолчанию для инициализации
"theName", "theAddress" и "thePhones",
а затем сразу присваивает им новые значения, затирая те, что уже были присвоены в конструкторах по умолчанию.
Таким образом, вся работа конструкторов по умолчанию тратится впустую.
Подход со списком инициализации членов позволяет избежать этой проблемы, поскольку аргументы в списке инициализации
используются в качестве аргументов конструкторов для различных членов-данных.
В этом случае:
    "theName" создается конструктором копирования из "name",
    "theAddress" – из "address",
    "thePhones" – из "phones".
Для большинства типов единственный вызов конструктора копирования более эффективен – иногда намного
более эффективен, чем вызов конструкторов по умолчанию с последующим вызовом операторов присваивания.
___________________________________________
"TOPIC" DEC-2014

initialization lists and member variables:

- if we have a member-variable "by value":
    int _my_var;
  it is really hard to use it if initialize in constructor.
  because assuming it will be destroyed after we left constructor?

  use "by reference"
   int* _my_var;

------ATTN: something strange, did I understand it all wrong? ? ?
___________________________________________



