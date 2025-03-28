#include <iostream>
#include "utils.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;

void test_division()
{
    int a = 123;
    int b = 100;
    int i = a % b;
    printf("result %d DIV_10 %d = %d\n",a , b, i);
    float res = a / 10.0;
    printf("result %d DIV %d = %f\n",a , b, res);
}


int main()
{
    int *ptr = 0, x = 9; // pointer and variable declaration
    ptr = &x; // pointer to variable "x"
    int &j = x; // reference declaration; reference to variable "x"
    cout << "int *ptr = 0, x = 9; // pointer and variable declaration" << endl;
    cout << "ptr = &x; // pointer to variable x" << endl;
    cout << "int &j = x; // reference declaration; reference to variable x" << endl;
    cout << "    x = " << x << endl;
    cout << "    &x = " << &x << endl;
    cout << "    j = " << j << endl;
    cout << "    &j = " << &j << endl;
    cout << "    *ptr = " << *ptr << endl;
    cout << "    ptr = " << ptr << endl;
    cout << "    &ptr = " << &ptr << endl;

    x = 78;
    cout << "----x = " << x << endl << endl;
    cout << "    x = " << x << endl;
    cout << "    &x = " << &x << endl;
    cout << "    j = " << j << endl;
    cout << "    &j = " << &j << endl;
    cout << "    *ptr = " << *ptr << endl;
    cout << "    ptr = " << ptr << endl;
    cout << "    &ptr = " << &ptr << endl;

    // getch();
}

void calc_cube()
{
    cout << "Enter cube dimention: \n" ;
    float side;
    // cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
}

