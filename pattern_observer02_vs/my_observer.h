#ifndef _MY_OBSERVER_H_
#define _MY_OBSERVER_H_

#include "gen.h"

class EventDispatcher
{
     public:
          template <typename ListenerType>
          void AddEventListener(string event, ListenerType* listener, void ( ListenerType ::* action ) ( void ));
};


template <typename ListenerType>
class Subscription
{
    private:
        std::string event;
        ListenerType* listener;
        void ( ListenerType ::* action ) ( void );
    public:
        Subscription(string event, ListenerType* listener, void ( ListenerType ::* action ) ( void ))
        {
            this->event = event;
            this->listener = listener;
            this->action = action;
        };
};

/*
class Observer 
{
    // 2. "dependent" functionality
    Subject *model;
    int denom;

public:
    Observer(Subject *mod, int div) 
    {
        model = mod;
        denom = div;
        // 4. Observers register themselves with the Subject
        model->attach(this);
    }
    virtual void update() = 0;

protected:    
    Subject *getSubject() 
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
    DivObserver(Subject *mod, int div)
        :Observer(mod, div)
    {
        // constructor
    }

    void update() 
    {
        // 6. "Pull" information of interest
        int v = getSubject()->getVal();
        int d = getDivisor();
        cout << v << " div " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer 
{
  public:
    ModObserver(Subject *mod, int div) 
        :Observer(mod, div)
    {
        // constructor
    }

    void update() 
    {
        int v = getSubject()->getVal();
        int d = getDivisor();
        cout << v << " mod " << d << " is " << v % d << '\n';
    }
};

*/
#endif
