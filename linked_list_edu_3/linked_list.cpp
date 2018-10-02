#include "linked_list.h"

list_ssn::list_ssn():
    pHead(0)
{
    std::cout << "Constructor - start!\n";
    pNDS = new NameDataSet("main");
}

void list_ssn::run()
{
    cout << "Read name, surname, SSN." << endl;
    cout << "Enter 'exit' for complete" <<endl;
    
    while (pNDS = getData())
    {
        this->addTail(pNDS);
    }

    cout << "\nList of elements: " <<endl;
    
    this->setCounterToHead();

    while(pNDS)
    {
        displayData(pNDS);
        pNDS = pNDS->pNext;
    }
}

void list_ssn::setCounterToHead()
{
    pNDS = pHead;
}

void list_ssn::addTail(NameDataSet* pCurrentTail)
{
    pCurrentTail->pNext = 0;

    if (pHead == 0)
    {
        std::cout << "---INFO pHead = NULL !!! ------" << std::endl;
		pHead = pCurrentTail;
        return;
    }
	// print phead!
    pHead->print_info();

    NameDataSet* pCurrent = new NameDataSet("Current");
    pCurrent = pHead;
    while(pCurrent->pNext)
    {
        pCurrent = pCurrent->pNext;
    }
    pCurrent->pNext = pCurrentTail;
}

NameDataSet* list_ssn::getData()
{
    NameDataSet* pBuffer_NDS = new NameDataSet("buffer");
    cout << "Enter name: (or 'EXIT')\n";
    cin >> pBuffer_NDS->szFirstName;

    if (pBuffer_NDS->szFirstName.find("exit") == 0)
    {
        delete pBuffer_NDS;
        return 0;
    }
    cout << "Enter surname: \n";
    cin >> pBuffer_NDS->szLastName;
    cout << "Enter SSN: \n";
    cin >> pBuffer_NDS->nSocialSecurity;
    // pBuffer_NDS->pNext - 0;
    pBuffer_NDS->pNext;
    return pBuffer_NDS;
}

void list_ssn::displayData(NameDataSet* pNDS)
{
    cout << pNDS->szFirstName
    << " "
    << pNDS->szLastName
    << "/"
    << pNDS->nSocialSecurity
    << "/"
    << pNDS->pNext
    << "\n";
}
