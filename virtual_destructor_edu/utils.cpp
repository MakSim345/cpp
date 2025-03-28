#include "utils.h"

void print_message()
{
    std::cout << "This is a native C++ program." << std::endl;
}

void show_delete()
{
    // [] operators in C++
    Auto* auto_ptr;
    auto_ptr = new Auto[3];
    delete[] auto_ptr;
}

void print_my_struct(my_time* _to_print)
{
    printf("ms: %d\n", _to_print->ms);
    printf("name: %s\n", _to_print->_name);
    // cout << "name:" << _to_print._name << endl;
    /*cout << "h:" << _to_print._name << endl;
    cout << "m:" << _to_print._name << endl;
    cout << "s:" << _to_print._name << endl;
    cout << "ms:" << _to_print._name << endl;   */
}

void _my_swap(int* source, int* dest)
{
    printf("_my_swap: source address 0x%X\n", source);
    printf("_my_swap: source value %d\n", *source);
    int t = *source;
    *source = *dest;
    *dest = t;
}

void _my_swap_ref(int& source, int& dest)
{
    int t = source;
    source = dest;
    dest = t;
}

