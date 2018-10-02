#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "gen.h"

class Observer;

class Publisher 
{
    // 1. "independent" functionality
    //vector < class Observer * > array_of_observeres; // 3. Coupled only to "interface"
    
    vector <Observer*> array_of_observeres; // 3. Coupled only to "interface"
    //vector <class Observer> array_of_observeres; // 3. Coupled only to "interface"
    int value;

public:
    
    void attach(Observer *obs) 
    {
        array_of_observeres.push_back(obs);
    }

    void setVal(int val) 
    {
        value = val;
        notify();
    }

    int getVal() 
    {
        return value;
    }

    void notify();    
};


class Observer 
{
    // 2. "dependent" functionality
    Publisher *model;
    int denom;

public:
    Observer(Publisher *mod, int div) 
    {
        model = mod;
        denom = div;
        // 4. Observers register themselves with the Publisher
        model->attach(this);
    }
    virtual void update() = 0;

protected:    
    Publisher *getPublisher() 
    {
        return model;
    }

    int getDivisor() 
    {
        return denom;
    }
};

class DivObserver: public Observer 
{
  public:
    DivObserver(Publisher *mod, int div)
        :Observer(mod, div)
    {
        // constructor
    }

    void update() 
    {
        // 6. "Pull" information of interest
        int v = getPublisher()->getVal();
        int d = getDivisor();
        cout << " call ->update() for DivObserver" << '\n';
        cout << v << " div " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer 
{
  public:
    ModObserver(Publisher *mod, int div) 
        :Observer(mod, div)
    {
        // constructor
    }

    void update() 
    {
        int v = getPublisher()->getVal();
        int d = getDivisor();
        cout << " call ->update() for ModObserver" << '\n';
        cout << v << " mod " << d << " is " << v % d << '\n';
    }
};

void Publisher::notify()
{
    // int i = array_of_observeres.size();
    // 5. Publisher broadcasts        
    for (unsigned int i = 0; i < array_of_observeres.size(); i++)
    { 
        //array_of_observeres[i]->update();
        array_of_observeres[i]->update();
    }
}

#endif