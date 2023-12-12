2015-FEB

Technical questions on the interview. Varian Medical Oy

- What is the difference between class and structure in C++?

"Structure:"
Initially (in C) a structure was used to bundle different type of data types together to perform a particular functionality.
But C++ extended the structure to contain functions also.

The major difference is that all declarations inside a "structure" are "public" by default.

"Class:"
"Class" is a successor of "Structure". By default all the members inside the class are "private".

-----------------

Structure vs class in C++

In C++, a structure is same as class except the following differences:

1. Members of a class are "private" by default and members of struct are "public" by default.
For example program 1 fails in compilation and program 2 works fine.

// Program 1
#include <stdio.h>

class Test
{
    int x; // x is private
};

int main()
{
  Test t;
  t.x = 20; // compiler error because x is private
  getchar();
  return 0;
}
// Program 2
#include <stdio.h>

struct Test
{
    int x; // x is public
};

int main()
{
  Test t;
  t.x = 20; // works fine because x is public
  getchar();
  return 0;
}

2. When deriving a struct from a class/struct, default access-specifier for a base class/struct is "public". And when deriving a class, default access specifier is "private".
For example program 3 fails in compilation and program 4 works fine.
// Program 3
#include <stdio.h>

class Base
{
public:
    int x;
};

class Derived : Base { }; // is equilalent to class Derived : private Base {}

int main()
{
  Derived d;
  d.x = 20; // compiler error becuase inheritance is private
  getchar();
  return 0;
}
// Program 4
#include <stdio.h>

class Base
{
public:
    int x;
};

struct Derived : Base { }; // is equilalent to struct Derived : public Base {}

int main()
{
  Derived d;
  d.x = 20; // works fine becuase inheritance is public
  getchar();
  return 0;
}

