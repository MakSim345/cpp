#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class NameDataSet
{
public:
    char szFirstName[128];      
    char szLastName [128];      
    int nSocialSecurity;        
    NameDataSet* pNext;
};

NameDataSet* pHead = 0;

void addTail(NameDataSet* pNDS)
{
    pNDS->pNext = 0;
    if (pHead == 0)
    {
        pHead = pNDS;
        return;
    }

    NameDataSet* pCurrent = pHead;
    while(pCurrent->pNext)
    {
        pCurrent = pCurrent->pNext;
    }
    pCurrent->pNext = pNDS;
}

NameDataSet* getData()
{
    NameDataSet* pNDS = new NameDataSet;
    cout << "Input name ";
    cin >> pNDS->szFirstName;

    if ((stricmp(pNDS->szFirstName, "exit") == 0))
    {
        delete pNDS;
        return 0;
    }
    cout << "Input surname ";
    cin >> pNDS->szLastName;
    cout << "Input a SSN ";
    cin >> pNDS->nSocialSecurity;
    pNDS->pNext - 0;
    return pNDS;
}

void displayData(NameDataSet* pNDS)
{
    cout << pNDS->szFirstName
    << " "
    << pNDS->szLastName
    << "/"
    << pNDS->nSocialSecurity
    << "\n";
}


