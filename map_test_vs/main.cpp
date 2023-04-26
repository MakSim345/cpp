#include "gen.h"
#include "utils.h"

/*
REM: improper list of parameters in the class definition
     cause undefined behavior
*/

using namespace std;

void vector_string()
{
    vector<string> v_names(10, "Name - Not initialized");

    cout << "Capacity vector =" << v_names.capacity() << endl;
    cout << "Size vector =" << v_names.size() << endl;

    v_names.insert(v_names.begin(), "AAAA");

    /*
    for( int i = 0; i < v_names.size(); i++ )
    {
        cout << v_names[i] << " ";
    }
    cout << endl;
    */

    v_names.resize(5);
    cout << "After RESIZE:" << endl;
    cout << "Capacity vector =" << v_names.capacity() << endl;
    cout << "Size vector =" << v_names.size() << endl;

    vector<string>::iterator iter;

    for( iter = v_names.begin(); iter != v_names.end(); iter++ )
    {
        cout << *iter << endl;
    }
}

class ToTest
{
public:
    ToTest (int x)
    {
        std::cout << "ToTest (int x): x= " << x << "\n";
        dataM = x;
    }

    ToTest (ToTest& x)
    {
        std::cout << "ToTest (ToTest& x): x.data= " << x.dataM << "\n";
        dataM = x.dataM;
    }

    int getTestData ()
    {
        return dataM;
    }

    ~ToTest ()
    {
        std::cout << "~ToTest (): x.data= " << this->dataM << "\n";
    }

private:
    int dataM;
};

/*
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
        { //constructor body}
    void dump ()
    {
        std::cout << "a=" << a.dump() << " b=" << b.dump() << "\n";
    }
};
*/

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

struct CityRecord
{
    std::string Name;
    uint16_t Population;
    double Latitude;
    double Longitude;
};


int main()
{    
    std::vector<CityRecord> citiesVector;
    citiesVector.emplace_back("Melbourne", 50000, 2.4, 9.4);
    citiesVector.emplace_back("Lol-Town", 50000, 2.4, 9.4);
    citiesVector.emplace_back("Berlin", 50000, 2.4, 9.4);
    citiesVector.emplace_back("Paris", 50000, 2.4, 9.4);
    citiesVector.emplace_back("London", 50000, 2.4, 9.4);
    citiesVector.emplace_back("Helsinki", 50000, 2.4, 9.4);
    
    for (const auto& city : citiesVector)
    {
        if (city.Name == "Berlin")
            std::cout << "Berlin. Population: " << city.Population << "\n";
    }

    map<long, string> Employees;
    /* ATTN: this init needs C++11*/
    map <string, int> myFamilyMap =
            {{"Moter", 37},
             {"Father", 40},
             {"BigBrother", 17},
             {"Brother", 15},
             {"Sister", 12} };

    print_map(myFamilyMap);

    map<string, int> anotherFamilyMap;
    anotherFamilyMap["Mother"] = 27;
    anotherFamilyMap["Father"] = 30;
    anotherFamilyMap["BigBrother"] = 7;
    anotherFamilyMap["Brother"] = 1;
    anotherFamilyMap["Sister"] = 2;
    
    print_map(anotherFamilyMap);

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

    print_map2(ProstotronMap);

    // cout << "ProstotronMap[12] = " << ProstotronMap[12] << "\n";
    // cout << "ProstotronMap[32] = " << ProstotronMap[32] << "\n";

    //--------------------//
    const unsigned long counter = 15;
    // char c;
    map <char, int> mySecondMap;

    for (int i = 0, c = 'a'; i < counter; ++i, ++c)
    {
        mySecondMap.insert (pair<char, int> (c,i));
    }

    print_map(mySecondMap);
    
    vector_string();
    system("PAUSE");

    return 0;
}

