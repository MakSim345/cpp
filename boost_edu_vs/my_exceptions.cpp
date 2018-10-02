//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "my_exceptions.h"

my_exceptions::my_exceptions()
{   
    system ("TITLE The Matrix");
    system ("color 0A");
}

void my_exceptions::run_matrix()
{
    for (int i = 0; i<25; i++)
    {
        int a=rand() % my_array.size();
        cout << " " << my_array[a];
        cout << " ";
    }
    cout << endl;
}

void my_exceptions::init_alphabet(vector<string>& alphabet)
{
    
}


void fail() // segfault generation
{
    // int *p = 0x00000000;   
    // p[0] = 13;
    const int _m_size = 25;
    char * _m_array;
    // _m_array = new int [_m_size];
    _m_array = new char[_m_size];
    for (int i = 0; i<_m_size; i++)
    {
        //int a=rand() % my_array.size();
       
        _m_array[i] = rand() % _m_size;
        cout << i <<  " - " << _m_array[i];
        printHex(_m_array[i]);
        // cout << "\n";
    }
    cout << endl;
    delete [] _m_array;
        
}

