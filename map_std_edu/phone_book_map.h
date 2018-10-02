#pragma once
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
#include "gen.h"

struct Number
{
    string name;
    string number;
};

class phone_book
{
public:
    phone_book()
    {
        filename = "text.txt";
    }
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //init_map();
        read_data_file();
        print_map();
        long num_to_search = 345345325;
        std::cout << "search by number " << num_to_search << " - "<< search_by_number(num_to_search) << "\n";
        Number t;
        std::cout << "\nEnter new name:\n";
        cin >> t.name;
        
        std::cout << "Enter new number:\n";
        cin >> t.number;
        
        add_data_to_file(t.name, atol(t.number.c_str()));

        return 0;
    }

    void add_data_to_file(std::string name, long number)
    {
        std::ofstream data_file;
        data_file.open (this->filename.c_str(), ios::app);
        
        // std::cout << "Writing this to a file.\n";    

        data_file << name << " " << number << std::endl;;
    
        data_file.close();
    }

    void read_data_file()
    {
        fstream data_file(this->filename.c_str());

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

    ~phone_book()
    {
        std::cout << "\nGood bye!\n";
    }

    long search_by_name(std::string name )
    {
        map<long, string>::iterator by_name;
        //by_name = Employees.find(name);
        return by_name->first;
    }

    std::string search_by_number(long number_to_search)
    {
        map<long, string>::iterator by_number;
        by_number = Employees.find(number_to_search);
        return by_number->second;
    }
    
    void insert_value(long num, std::string name)
    {
        Employees[num] = name;

        cout << "Employees[" << num  << "]" << Employees[num] << endl << endl;
        cout << "Map size: " << Employees.size() << endl;
    }

    void init_map()
    {
        // Assignment using array index notation
        Employees[5234] = "Mike C.";
        Employees[3374] = "Charlie M.";
        Employees[1923] = "David D.";
        Employees[7582] = "John A.";
        Employees[5328] = "Peter Q.";

        //cout << "Employees[3374]=" << Employees[3374] << endl << endl;
        cout << "Map size: " << Employees.size() << endl;
    }

    void print_map()
    {
        // for( map<int, string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii)
        for(ii = Employees.begin(); ii != Employees.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            cout << ii->first << ": " << ii->second << endl;
        }

    }
    map<long, string> Employees; 
    map<long, string>::iterator ii;
    std::string filename;
};


