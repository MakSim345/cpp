//============================================================
//
// Description:
//============================================================
#include "vector_tst.h"

using namespace std;

int vector_module (int heigh)
{
   return  heigh*heigh*heigh;
}

void some_function(const vector<int>& _vector_param)
{
   // OK
}

void vector_string ()
{
    vector<string> v_names(100, "Unknown");

    cout << "Capacity vector =" << v_names.capacity() << endl;
    cout << "Size vector =" << v_names.size() << endl;

    // v.insert(v.begin() 3);
    /*
    for( int i = 0; i < v_names.size(); i++ )
    {
        cout << v_names[i] << " ";
    }
    cout << endl;
    */

    // v_names.resize(25);
    cout << "Capacity vector =" << v_names.capacity() << endl;
    cout << "Size vector =" << v_names.size() << endl;

    vector<string>::iterator iter;

    for( iter = v_names.begin(); iter != v_names.end(); iter++ )
    {
        cout << *iter << endl;
    }
}

void vector_test_float()
{
    vector<float> v;

    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;

    v.assign( 5, 10 );

    v[2] = 16.4;
    v[3] = 20.6;
    v.push_back(17.8);
    v.push_back(-7.3);

    // v.insert(v.begin() 3);
    v.resize(20);

    for( int i = 0; i < v.size(); i++ )
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;

    cout << v.front() << " " << v.at(2) << " " << v.back() << endl;

    vector<float>::iterator iter;

    for( iter = v.begin(); iter != v.end(); iter++ )
    {
        cout << *iter << endl;
    }
}

void vector_test ()
{
    vector<float> v;

    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;

    v.assign( 5, 10 );

    v[2] = 16.4;
    v[3] = 20.6;
    v.push_back(17.8);
    v.push_back(-7.3);

    // v.insert(v.begin() 3);
    v.resize(20);

    for( int i = 0; i < v.size(); i++ )
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;

    cout << v.front() << " " << v.at(2) << " " << v.back() << endl;

    vector<float>::iterator iter;

    for( iter = v.begin(); iter != v.end(); iter++ )
    {
        cout << *iter << endl;
    }
}
