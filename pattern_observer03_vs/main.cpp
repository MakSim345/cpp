//

#include "stdafx.h"

#include <iostream>
#include <set>

using namespace std;

// ---------------- Observer interface -----------------
class ObserverBaseClass 
{
public:
    virtual void Update() = 0;
};

// ---------------- Observable object -------------------
class Publisher 
{
    static Publisher* instance;
    set<ObserverBaseClass*> observers;
    Publisher() { this->value = 0; };
    int value;

public:
   static Publisher* GetInstance();
   void AddObserver(ObserverBaseClass& o);
   void RemoveObserver(ObserverBaseClass& o);
   void NotifyObservers();
   void Trigger();
   void setVal(int val);
   int getVal();
};

Publisher* Publisher::instance = NULL;

Publisher* Publisher::GetInstance()
{
    if ( instance == NULL )
    {
       instance = new Publisher();
    }

    return instance;
}

void Publisher::AddObserver(ObserverBaseClass& o)
{
    observers.insert(&o);
}

void Publisher::RemoveObserver(ObserverBaseClass& o)
{
    observers.erase(&o);
}

void Publisher::setVal(int val) 
{
    value = val;
    this->NotifyObservers();
}

int Publisher::getVal() 
{
    return this->value;
}

void Publisher::NotifyObservers()
{
    set<ObserverBaseClass*>::iterator itr;
    
    for ( itr = observers.begin(); itr != observers.end(); itr++ )
    { 
        (*itr)->Update();
    }
}

// TEST METHOD TO TRIGGER
// IN THE REAL SCENARIO THIS IS NOT REQUIRED
void Publisher::Trigger()
{
    NotifyObservers();
}

// ------ Concrete class interested in notifications ---
class MyObserver : public ObserverBaseClass 
{
    Publisher* observable;

public:
   MyObserver() 
   {
      observable = Publisher::GetInstance();
      observable->AddObserver(*this);
   }

   ~MyObserver() 
   {
      observable->RemoveObserver(*this);
   }

   void Update() 
   {
       //here - receive update event and request information back: 
       cout << "Received a change event:" << endl;
       cout << "New lot is: " << observable->getVal() << endl;        
   }
};

void main()
{
    Publisher* observable = Publisher::GetInstance();
    MyObserver* obj = new MyObserver();
    MyObserver* obj2 = new MyObserver();
    observable->setVal(23);
    observable->setVal(24563);
    observable->setVal(-900898);
    
    // observable->Trigger();
    // observable->NotifyObservers();

    system("PAUSE");
}
/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/

