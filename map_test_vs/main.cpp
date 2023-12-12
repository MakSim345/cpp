#include "gen.h"
#include "utils.h"

/*
REM: improper list of parameters in the class definition
     cause undefined behavior
*/

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


void test_prostotron()
{
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
}


void testFamily()
{
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
}

void test_map()
{
    const unsigned long counter = 15;
    // char c;
    map <char, int> mySecondMap;

    for (int i = 0, c = 'a'; i < counter; ++i, ++c)
    {
        mySecondMap.insert(pair<char, int> (c,i));
    }

    print_map(mySecondMap);
}

void test_city_vector()
{
    std::vector<CityRecord> citiesVector;

    CityRecord mlbrn {"Melbourne", 24500, 101.4, 91.4};
    citiesVector.emplace_back(mlbrn);
    // citiesVector.emplace_back("Melbourne", 50000, 2.4, 9.4);

    CityRecord lol_town {"Lol-Town",  50, 12.55, 23.5};
    citiesVector.emplace_back(lol_town);
    //citiesVector.emplace_back("Lol-Town",  50000, 2.4, 9.4);

    CityRecord brln {"Berlin", 350000, 97.4, 119.24};
    citiesVector.emplace_back(brln);
    //citiesVector.emplace_back("Berlin",    50000, 2.4, 9.4);

    CityRecord paris {"Paris", 150000, 54.4, 3.34};
    citiesVector.emplace_back(paris);
    //citiesVector.emplace_back("Paris",     50000, 2.4, 9.4);

    CityRecord london {"London", 900000, 66.9, 12.38};
    citiesVector.emplace_back(london);
    //citiesVector.emplace_back("London",    50000, 2.4, 9.4);

    CityRecord hki {"Helsinki", 23600, 1.1, 1.1};
    citiesVector.emplace_back(hki);
    //citiesVector.emplace_back("Helsinki",  50000, 2.4, 9.4);

    for (const auto& city : citiesVector)
    {
        if (city.Name == "Berlin")
            std::cout << "Berlin. Population: " << city.Population << "\n";
    }

}

void test_city_map()
{
    std:map<std::string, CityRecord> cityMap;

    CityRecord mlbrn {"Melbourne", 24500, 101.4, 91.4};
    cityMap["Melbourne"] = mlbrn;

    CityRecord lol_town {"Lol-Town",  50, 12.55, 23.5};
    cityMap["Lol-Town"] = lol_town;

    CityRecord brln {"Berlin", 350000, 97.4, 119.24};
    cityMap["Berlin"] = brln;

    CityRecord paris {"Paris", 150000, 54.4, 3.34};
    cityMap["Paris"] = paris;

    CityRecord london {"London", 900000, 66.9, 12.38};
    cityMap["London"] = london;

    CityRecord hki {"Helsinki", 23600, 1.1, 1.1};
    cityMap["Helsinki"] = hki;

    for (const auto& city : cityMap)
    {
       std::cout << city.first << " : "<<  city.second.Population << "\n";
    }

    std::cout << "Berlin. Population: " <<  cityMap["Berlin"].Population << "\n";

}

int main(){
    // test_city_vector();

    test_city_map();

    // cout << "ProstotronMap[12] = " << ProstotronMap[12] << "\n";
    // cout << "ProstotronMap[32] = " << ProstotronMap[32] << "\n";

    //--------------------//

    // run test vectors function:
    // vector_string();
#ifdef WIN32_APP
    system("PAUSE");
#endif

    return 0;
}

