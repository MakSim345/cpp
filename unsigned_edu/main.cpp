#include <iostream>
#include "utils.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;

void calc_cube()
{
    cout << "Enter cube dimention: \n" ;
    float side;
    // cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
}

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
    // print_message();
    unsigned int a = 14;
    int filteredValue = -4000;
    const float _div = 1000.0;
    // (unsigned int)filteredValue/_div

    unsigned int test_val = (unsigned int)filteredValue/_div;
    set_number_int(1, 2);
    //set_number_int(2, -5);
    printf("main. number - %d, 0x%X\n", test_val, test_val);
    // set_number_int(2, filteredValue/_div);
    set_number_int(2, -6);
    set_number_int(3, -10);
    // set_number_int(2, test_val);

    return 1;
}

