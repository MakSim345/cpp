#include <iostream>
#include <map> 
#include <vector>
#include <ctype.h>
#include <errno.h>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <functional>

// #include "utils.h"

/*
REM: improper list of parameters in the class definition 
     cause undefined behavior
*/

using namespace std;

class ToTest
{
private:
    int data;

public:
    ToTest (int x)
    {
        std::cout << "ToTest (int x): x= " << x << "\n";
        data = x;
    }

    ToTest (ToTest& x)
    {
        std::cout << "ToTest (ToTest& x): x.data= " << x.data << "\n";
        data = x.data;
    }
    
    int dump ()
    {
        return data;
    }

    ~ToTest ()
    {
        std::cout << "~ToTest (): x.data= " << this->data << "\n";        
    }

};


class Base
{
public:
    virtual ~Base () {};
        
    virtual void dump () {};
};

class WrongInit : public Base
{
private:
    ToTest a;
    ToTest b;
public:
    WrongInit (int x) : 
        b(x), 
        a(b)
        { /* constructor body*/}
    void dump () 
    {
        std::cout << "a=" << a.dump() << " b=" << b.dump() << "\n";
    }    
};


// This function shall accept string and char as one parameter:
template <class T>
void print_map(map<T, int> &temp_map)
    {
        // for( map<int, string>::iterator ii=temp_map.begin(); ii!=temp_map.end(); ++ii)
        for(auto ii = temp_map.begin(); ii != temp_map.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            cout << ii->first << ": " << ii->second << endl;
        }
        /*
        for (auto it = temp_map.begin(); it != temp_map.end(); ++it)
        {
            cout << (*it).first << " : " << (*it).second << endl;
        }
        */
    }

template <class T1, class T2> 
void print_map2(map<T1, T2> &temp_map)
    {
        // for( map<int, string>::iterator ii=temp_map.begin(); ii!=temp_map.end(); ++ii)
        for(auto ii = temp_map.begin(); ii != temp_map.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            cout << ii->first << ": " << ii->second << endl;
        }
        /*
        for (auto it = temp_map.begin(); it != temp_map.end(); ++it)
        {
            cout << (*it).first << " : " << (*it).second << endl;
        }
        */
    }


int main()
{
    map<long, string> Employees;
    /* ATTN: this init needs C++11
    map <string, int> myFirstMap = {{"Moter", 37},
                                    {"Father", 40},
                                    {"BigBrother", 17},
                                    {"Brother", 15},
                                    {"Sister", 12} };*/
    map<string, int> myFirstMap; 

    myFirstMap["Mother"] = 37;
    myFirstMap["Father"] = 40;
    myFirstMap["BigBrother"] = 17;
    myFirstMap["Brother"] = 15;
    myFirstMap["Sister"] = 12;

    
    print_map(myFirstMap);

    map<int, string> ProstotronMap;
    ProstotronMap[10] = "READ - from terminal to selected memory address";
    ProstotronMap[11] = "WRITE - Print in terminal value of selected memory";
    ProstotronMap[20] = "LOAD - from selected memory address to accumulator";
    ProstotronMap[21] = "SAVE - from accumulator to selected memory address";
    ProstotronMap[30] = "ADD - number from selected memory address and accumulator. Result to accumulator";
    ProstotronMap[31] = "SUBTRACT - number from selected memory address and accumulator. Result to accumulator";
    ProstotronMap[32] = "DIVIDE - number from selected memory address and accumulator. Result to accumulator";
    ProstotronMap[33] = "MULTIPLY - number from selected memory address and accumulator. Result to accumulator";
    ProstotronMap[40] = "BRANCH - Goto selected memory address, unconditional";
    ProstotronMap[41] = "BRAMCHNEG - Goto selected memory address, if accumulator is negative";
    ProstotronMap[42] = "BRANCHZERO - Goto selected memory address, if accumulator is zero";
    ProstotronMap[43] = "HALT - full stop";

    // print_map2(ProstotronMap);
    cout << "ProstotronMap[12] = " << ProstotronMap[12] << "\n";
    
    //--------------------//
    char c;
    map <char, int> mySecondMap;

    for (int i = 0,c = 'a'; i < 5; ++i,++c)
    {
        mySecondMap.insert ( pair<char,int>(c,i) );
    }
    
    print_map(mySecondMap);

    return 0;
}

