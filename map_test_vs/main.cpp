#include <unordered_map>
#include <random>

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
    std::map<std::string, CityRecord> cityMap;

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

void printHashMap(const unordered_map<int, int>& hashTableP)
{
    std::cout << "  Hash table: {";
    for (const auto& pair : hashTableP)
    {
        // std::cout << pair.first << ":" << pair.second << " ";
        std::cout << "[" << pair.second << "]->" << pair.first << ", ";
    }
    std::cout << "}\n";
}

void create_random_vector(std::vector<int>* numbersP)
{
    if (numbersP == nullptr) return;

    constexpr int rndCount = 10;
    constexpr int rndMinValue = 0;
    constexpr int rndMaxValue = 20;

    numbersP->clear();
    numbersP->reserve(rndCount);

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(rndMinValue, rndMaxValue);

    for (int i = 0; i < rndCount; ++i)
    {
        numbersP->push_back(dist(rng));
    }
}


void test_vector_hash_index()
{
    std::vector<int> numbers;
    numbers.reserve(10);

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 19);

    for (int i = 0; i < 10; ++i)
    {
        numbers.push_back(dist(rng));
    }

    // value -> all positions where the value appears
    std::unordered_map<int, std::vector<std::size_t>> index_by_value;
    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        index_by_value[numbers[i]].push_back(i);
    }

    std::cout << "Vector values (index:value):\n";
    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        std::cout << i << ":" << numbers[i] << "  ";
    }
    std::cout << "\n\n";

    int target = numbers[3];
    auto it = index_by_value.find(target);
    if (it != index_by_value.end())
    {
        std::cout << "Found " << target << " at positions: ";
        for (std::size_t pos : it->second)
        {
            std::cout << pos << " ";
        }
        std::cout << "\n";
    }

    int missing = 99;
    if (index_by_value.find(missing) == index_by_value.end())
    {
        std::cout << "Value " << missing << " is not in the vector.\n";
    }

    std::cout << "\nIf there are duplicate numbers, all of their indexes are stored "
                 "in the hash map (vector of positions).\n";
}

vector <int> TwoSumBruteForce(vector <int>& nums, int target)
{
    vector <int> targetIndexes;

    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i+1; j < nums.size(); j++)
        {
            std::cout << nums[i] << "+" << nums.at(j) << "=" << nums.at(i) + nums.at(j) <<" \n";
            if(nums.at(i) + nums.at(j) == target)
            {
                targetIndexes.push_back(i);
                targetIndexes.push_back(j);
                std::cout << "Found indexes: " << i << " and " << j << "\n";
                return targetIndexes;
            }
        }
    }

    return targetIndexes;
}

vector <int> TwoSumHashMap(vector <int>& vectorNumsP, const int targetP)
{
    /*
    Input: vector of numbers and target sum.
    Output: vector of indexes that form valid pair(s).
    */

    unordered_map <int, int> hash_table; //Hash map declaration value -> index

    for (std::size_t i = 0; i < vectorNumsP.size(); ++i)
    {
        std::cout << "[" << i << "]:" << vectorNumsP[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < vectorNumsP.size(); i++)
    {
        int current_integer = vectorNumsP.at(i);
        // std::cout << "Current int in vectorNumsP[{}]: " << current_integer << "\n";
        std::cout << "Current vectorNumsP[" << i << "]: " << current_integer << "\n";

        int second_integer = targetP - current_integer;

        std::cout << "Looking for second_integer: " << second_integer << "\n";

        auto found_it = hash_table.find(second_integer);

        if (found_it != hash_table.end())
        {
            std::cout << "*** OK *** " << second_integer << " found in hash map. \n";
            std::cout << "Found indexes: " << found_it->second << " and " << i << "\n";

            // check if current_integer is already in the hash map:
            // Note: insert() only adds if key does not exist:
            auto [it, inserted] = hash_table.insert({current_integer, i});

            printHashMap(hash_table);  // Print after each step
            std::cout << "\n";
            return {found_it->second, i};
        }
        else
        {
            std::cout << "The second integer " << second_integer <<" NOT found in hash." << "\n";

            // check if current_integer is already in the hash map:
            // Note: insert() only adds if key does not exist:
            auto [it, inserted] = hash_table.insert({current_integer, i});
            if (inserted)
            {
                std::cout << "+ Add to hash " << "\n";
            }
            //if (hash_table.find(current_integer) == hash_table.end())
            //{
                // std::cout << "+ Add to hash " << "\n";
                // insert current integer into the hash map:
            //    hash_table[current_integer] = i;
            //}

            else
            {
                std::cout << "- No action. Already in hash " << "\n";
            }

            // hash_table[current_integer] = i;
            printHashMap(hash_table);  // Print after each step
            std::cout << "\n";
        }
    }

    return {0, 0}; // Return a default value if no pair is found
}

int main()
{
    // test_city_vector();
    // vector<int> testArray = {2, 6, 11, 12, 3, 6, 5, 15};
    // vector<int> testArray = {10, 10};

    vector<int> testArray;
    create_random_vector(&testArray);

    // TwoSumBruteForce(testArray, 20);
    vector<int> resultArray = TwoSumHashMap(testArray, 20);

    for (std::size_t i = 0; i < testArray.size(); ++i)
    {
        std::cout << "[" << i << "]:" << testArray[i] << " ";
    }

    std::cout << "\n";
    cout << "resultArray[0] = " << resultArray[0] << "\n";
    cout << "resultArray[1] = " << resultArray[1] << "\n";

    // test_vector_hash_index();

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

