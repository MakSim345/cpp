#include <iostream>
#include <vector>
// #include <iostream>
#include <numeric>
#include "trace_logger.h"


#include "print_util.h"

using namespace std;

class my_class
{
public:
    int get_var() {return var;}
    void run (int a) {var = a;}

    void print_my_vector()
    {
        for (int i = 0; i < int_arr.size(); ++i)
        {
            cout << "int_arr[" << i << "] = " << int_arr[i] << "." << endl;
        }
    }

    void make_my_vector(int _var, int _count)
    {
        int_arr = vector <int>(_var, _count);
    }

    void add_to_vector(int _var)
    {
        int_arr.push_back(_var);
    }

    int vector_sum()
    {
        int _ret_val = std::accumulate (int_arr.begin(), int_arr.end(), 0);
        return _ret_val;
    }

private:
    int var;
    vector <int> int_arr;
};

int fact(int n)
/*
 * Function for calculate a factorial
 * */
{
    LOG_TRACE;
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
}


int main()
{
    int array[5] = {1,2,3,4,5};
    int _fact = 4;
    cout << "Enter a number for a factorial" << "\n";
    cin >> _fact;
    // std::cout << array << std::endl;
    // cout << "Your name is " << name << "." << endl;
    // vector <int> int_arr (23, 10);

    // vector<my_class> my_class_array;
    cout << "Factorial of " << _fact << " = " << fact(_fact) << endl;
    return 0;
}

