//============================================================
//
//
//============================================================
//
// File:           map.cpp
//
//
//============================================================
// Description:
//============================================================

#include "phone_book_map.h"

phoneBook::phoneBook()   {_dataBaseFilename = "text.txt"; }

phoneBook::phoneBook(std::string _new_filename)
{
    _dataBaseFilename = _new_filename;
    // this->read_data_file();
}

phoneBook::~phoneBook()
{
    std::cout << "\nGood bye!\n";
}

void phoneBook::add_data_to_file(std::string name, long number)
{
    std::ofstream data_file;
    data_file.open (this->_dataBaseFilename.c_str(), ios::app);

    // std::cout << "Writing this to a file.\n";    

    data_file << name << " " << number << std::endl;;

    data_file.close();
}

void phoneBook::write_data_to_file(Person pName, long pNumber)
{
    std::ofstream dataBaseFile;
    dataBaseFile.open (this->_dataBaseFilename.c_str(), ios::app);

    // std::cout << "Writing this to a file.\n";

    dataBaseFile << pNumber  << " " << pName.GetName() << " " << pName.GetEmail() << " " << pName.GetAge() << std::endl;
    // dataBaseFile.write((char*)&pName, sizeof(pName));
    dataBaseFile.close();
}

int phoneBook::Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        fPrint crazy_printer(std::cout);
        print_map();
        // make map of people :
        // init_map();
        read_data_from_file();
        print_map();
        // find someone by key:
        int number_to_search = 4422;
        find_by_key(number_to_search);

        // Example of erasing an element correctly ...
        // If we did the j++ as part of the for loop we would end up
        // adding 1 to an iterator that pointed to an element that was
        // removed which would lead to a crash. See Josuttis p 205.

        cout << "Erasing people of age 100" << endl;
    
        for (type_people_map::iterator j = peopleMap.begin (); j != peopleMap.end (); )
            {
                if (j->second.GetAge () == 100)
                    peopleMap.erase (j++); // iterator is advanced before the erase occurs
                else
                    ++j;                  // advance the iterator
            } // end of erase loop
    

        // now display who is left
        cout << "Printing people left after erase ..." << endl;
        for_each (peopleMap.begin(), peopleMap.end(), crazy_printer);
        /*
        people_map::iterator ii;
        for(ii = people.begin(); ii != people.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            write_data_to_file(ii->second, ii->first);
            cout << ii->first << ": " << ii->second.GetName() << endl;
        }
        */
        return 0;
}

void phoneBook::read_data_file()
{
    fstream data_file(this->_dataBaseFilename.c_str());

    if (!data_file.good())
    {
        std::cout << "file does not exist!\n";
        return;
    }

    vector <Number> telBook;
    while (true)
    {
        Number t;

        data_file >> t.name;
        //std::cout << "Name:" << t.name << " ";

        if (data_file.eof())
            break;

        data_file >> t.number;
        long number = atol(t.number.c_str());
        // data_file >> number;

        if (data_file.eof())
            break;           

        insert_value(number, t.name);
        // Employees[number] = t.name;

        //std::cout << " - Number: " << t.number;
        //std::cout << "\n";
        telBook.push_back(t);
    }
    data_file.close();
}

std::string phoneBook::search_by_name(std::string name )
{
    map<long, string>::iterator by_name;
    //by_name = Employees.find(name);
    // by_name = find_value(Employees.begin(), Employees.end(), name);
    if (by_name != Employees.end())
    {
        std::stringstream ss;
        ss << by_name->first;

        std::cout << ss.str();
        return ss.str(); // by_name->first;
    }
    else
        return "DO NOT EXIST!";
}

void phoneBook::find_by_key(int _number_to_search)
{
    fPrint crazy_printer(std::cout);
    // _number_to_search = 4422;
    std::cout << "Finding person " << _number_to_search << "...\n";

    type_people_map::const_iterator i = peopleMap.find(_number_to_search);
    if (i == peopleMap.end())
        std::cout << "Not found \n";
    else
    {
        crazy_printer(*i);
        // another way to print:
        //std::cout << "Found key = " << i->first << "\n";
        //std::cout << "Found name = " << i->second.GetName() << "\n";
    }
}

std::string phoneBook::search_by_number(long number_to_search)
    {
        map<long, string>::iterator by_number;
        by_number = Employees.find(number_to_search);
        return by_number->second;
    }
    
void phoneBook::insert_value(long num, std::string name)
    {
        Employees[num] = name;

        //cout << "Employees[" << num  << "]" << Employees[num] << endl << endl;
        //cout << "Map size: " << Employees.size() << endl;
    }

void phoneBook::init_map()
    {
        // Assignment using array index notation
        
        peopleMap[1234] = Person("Nick", "nick@yahoo.com", 21);
        peopleMap[4422] = Person ("Fred", "fred@nurk.com.au", 100);
        peopleMap[8811] = Person ("John", "john@smith.com.au", 35);
        
        peopleMap[5234] = Person("Mike C.", "Mike@yahoo.com", 21);
        peopleMap[3374] = Person("Charlie M.", "CharlieM@slash.com.uk", 40);
        peopleMap[1923] = Person("David D.", "David_and_Goliaph@gmail.com", 35);
        peopleMap[7582] = Person( "John A.", "john_doe@mail.ru", 29);
        peopleMap[5328] = Person("Peter Q.", "Peter_pen@googlemail.com", 68);

        peopleMap.insert(std::make_pair(4203, Person("Abigail", "abu-kasim@jihad.com", 20)));
        //cout << "Employees[3374]=" << Employees[3374] << endl << endl;
        // cout << "Map size: " << Employees.size() << endl;
    }

void phoneBook::print_map()
{
        fPrint crazy_printer(std::cout);
        for_each (peopleMap.begin(), peopleMap.end(), crazy_printer);
        // for( map<int, string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii)
        /*
        for(ii = Employees.begin(); ii != Employees.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            cout << ii->first << ": " << ii->second << endl;
        }
        */
    }

void phoneBook::read_data_from_file()
{
    fstream dataBaseFile(this->_dataBaseFilename.c_str());

    if (!dataBaseFile.good())
    {
        std::cout << "file does not exist!\n";
        return;
    }

    while (true)
    {
        std::string tmpStr;
        dataBaseFile >> tmpStr;
        long number = atol(tmpStr.c_str());
        //std::cout << "Name:" << t.name << " ";

        if (dataBaseFile.eof())
            break;

        std::string name;
        dataBaseFile >> name;          

        if (dataBaseFile.eof())
            break;     

        std::string email;
        dataBaseFile >> email;          

        if (dataBaseFile.eof())
            break;   

        std::string age;
        dataBaseFile >> age;          
        long _age = atol(age.c_str());
        if (dataBaseFile.eof())
            break;   
        // insert_value(number, t.name);
        // Employees[number] = t.name;

        //std::cout << " - Number: " << t.number;
        //std::cout << "\n";

        // telBook.push_back(t);
        //people.insert(std::make_pair(num, Person(name, email, _age)));
        peopleMap[number] = Person(name, email, _age);
    }
    dataBaseFile.close();
}
