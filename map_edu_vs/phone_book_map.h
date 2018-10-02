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
#include "person.h"
#include "fprint.h"
#include "phone_book_map.h"

struct Number
{
    string name;
    string number;
};

typedef map <int, Person, less<int> > type_people_map;

class phoneBook
{
public:
    phoneBook();
    phoneBook(std::string _new_filename);

    ~phoneBook();
       
    void read_data_from_file();
    int phoneBook::Run();
   
    void write_data_to_file(Person pName, long pNumber);
    
    void add_data_to_file(std::string name, long number);
    
    void read_data_file();
    
    std::string search_by_name(std::string name);
    
    void find_by_key(int _number_to_search);
    
    std::string search_by_number(long number_to_search);
    
    void insert_value(long num, std::string name);
    
    void init_map();
    
    void print_map();
    
    map<long, string> Employees; 
    map<long, string>::iterator ii;
    std::string _dataBaseFilename;
    type_people_map peopleMap;
};