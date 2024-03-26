#include "gen.h"
#include "phone_book_map.h"
#include "person.h"
#include "fPrint.h"

#include <Windows.h>

class App
{
public:
    int Run()
    {
        phoneBook *myPhoneBook = new phoneBook();
        myPhoneBook->Run();
        return 0;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

vector<std::string> nestedLoopJoin(vector<std::string>& setA, vector<std::string>& setB)
{
    vector<std::string> resultSet;
    for (int i = 0; i < setA.size(); i++)
    {
        for (int j = 0; j < setB.size(); j++)
        {
            if (setA[i] == setB[j])
            {
                resultSet.push_back(setB[j]);
                break;
            }
        }
    }

    return resultSet;
}

vector<std::string> hashJoin(vector<std::string>& setA, vector<std::string>& setB)
{
    vector<std::string> resultSet;
    unordered_map <string, string> mp;

    for (int i = 0; i < setB.size(); i++)
    {
        mp[setB[i]] = setB[i]; // create a hash
    }
    for (int i = 0; i < setA.size(); i++)
    {
        if (mp.find (setA[i]) != mp.end())
        {
            resultSet.push_back(setB[i]);
        }
    }

    return resultSet;
}



int main()
{
    //std::auto_ptr <App> my_maps(new App());
    std::string initialStrings[] = {"one", "two", "three"};
    //vector<std::string> setA(initialStrings);
    //vector<std::string> setB(initialStrings);
    // nestedLoopJoin(setA, setB);

    
    std::vector<std::string> stringVector(initialStrings, initialStrings + sizeof(initialStrings) / sizeof(initialStrings[0]));

    hashJoin(stringVector, stringVector);
    /*
    std::vector<std::string> stringVector(initialStrings, initialStrings + sizeof(initialStrings) / sizeof(initialStrings[0]));
    // Print the elements of the vector
    for (const auto& str : stringVector)
    {
        std::cout << str << " ";
    }

    */
    try
    {
        //my_maps->Run();
        //my_maps->create_big_file();
        //my_maps->search_by_name();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }
    */

    //std::string p;
    //std::cout << "\nPress any key to exit...\n";
    //cin >> p;

    // this PAUSE will give a info text - press any key to continue, etc.
    // system("PAUSE");
    std::cout << "\nApplication complete.\n";
    return 1;
}
