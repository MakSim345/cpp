#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "gen.h"

struct Item
{
    int info;
    Item* next;
};

class NameDataSet
{
public:
    NameDataSet(std::string _name):
        szFirstName("Nan"),
        szLastName("Nan"),
        nSocialSecurity(0)
    { 
        this->_my_name =_name;
        std::cout << "---START NameDataSet Constructor------" << std::endl;
        std::cout << "pNext------" << pNext << std::endl;
        std::cout << "_my_name------" << _my_name << std::endl;
        std::cout << "---COMPLETE NameDataSet Constructor------" << std::endl;
    }
    
    ~NameDataSet() 
    { 
        std::cout << ".....START....Destroy NameDataSe....." << std::endl;
        std::cout << "pNext------" << pNext << std::endl;        
        std::cout << "_my_name------" << _my_name << std::endl;
        std::cout << ".....COMPLETE....Destroy NameDataSe....." << std::endl;
    }
    
    void print_info()
    {
        std::cout << "---START NameDataSet PRINT------" << std::endl;
        std::cout << "pNext------" << pNext << std::endl;
        std::cout << "_my_name------" << _my_name << std::endl;
        std::cout << "---COMPLETE NameDataSet PRINT------" << std::endl;
    }

    // char szFirstName[128];
    // char szLastName [128];
    std::string szFirstName;
    std::string szLastName;
    std::string _my_name;
    int nSocialSecurity;
    NameDataSet* pNext;
};

class list_ssn
{
public:    
    list_ssn ();
    ~list_ssn();
    
    void run();
    void addTail(NameDataSet* pNDS);
    NameDataSet* getData();
    void displayData(NameDataSet* pNDS);

private:
    NameDataSet* pNDS;
    static std::string Indent;
    const char* _fileName;
    const char* _funcName;
    NameDataSet* pHead;
    void setCounterToHead();
};
#endif
