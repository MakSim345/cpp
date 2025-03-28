#include <iostream>
#include <stdint.h>
#include "utils.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;

int foo(int q)
{
    int x = 1;
    return (q + x);
}

int main()
{
    // print_message();
    cout << "Enter cube dimention: " ;
    float side = 12;
    // cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
    int a = 123;
    int b = 100;
    int i = a % b;
    printf("result %d DIV_10 %d = %d\n",a , b, i);
    float res = a / 10.0;
    printf("result %d DIV %d = %f\n",a , b, res);

    int x = 0;
    while (x < 3)
    {
        printf ("%i", x);
        x = x + foo(x);
    }
    /*
    int x = 0, y = 1;
    if (x || !y )
        printf ("1");
    else if (y && x)
        printf ("2");
    else
        printf ("3");
    if ( (10 || (5-2)) && ((6 / 2) - (1+2)) )
        printf ("TRUE");
    else
        printf ("FALSE");
   a*/
    return 1;
}

