#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include "trace_logger.h"
#include "linked_list.h"
#include "print_util.h"

using namespace std;

void showlist(const char *str, const  list<int> &L)
{    
    list<int>::const_iterator i;
    cout << str << endl <<  "     " ;

    for (i=L.begin(); i != L.end(); ++i) 
        cout << *i << "     " ; 
    cout << endl; 
}

int main()
{    
    list<int> v;
    int x;
    cout <<  "Enter positive integers, followed by 0:\n";

    while (cin >> x, x!=0) 
        v.push_back(x);
    /*
    list<int>::iterator i;

    for (i=v.begin(); i != v.end(); ++i) 
        {
            cout << *i << " " ;
            cout << endl;
        }
    */
    showlist("This is a vector:", v);
    return 0; 
}

