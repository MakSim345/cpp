#pragma once

#include <vector>
#include <string>

using namespace std;

class SubscriptionBase
{
  public:
    virtual string GetEventName (void) const {return "event";}
    virtual void Invoke ( void ) const{};
};


template <typename ListenerType> 
class Subscription : public SubscriptionBase
{
public:
    Subscription ( string str_event , ListenerType* listener ,  void ( ListenerType ::* action ) ( void ) )
    {
        this->str_event = str_event;
        this->listener = listener;
        this->action = action;
    };
    
    string str_event;
    ListenerType* listener;
    void (ListenerType ::* action) (void);

private:
    virtual string GetEventName (void) const
    {
        return this->str_event;
    };
					
    virtual	void Invoke ( void ) const
    {
        (this->listener ->* this->action) ( );
    };

public:
    
};


class EventDispatcher
{
  private:
    vector <SubscriptionBase*>	subscriptions;
  
  protected:

    void DispatchEvent ( const string event ) const;
  
  public:
    template <typename ListenerType>
    void AddEventListener (string, ListenerType*, void (ListenerType::*) (void) );
    
    template <typename ListenerType>
    void RemoveEventListener (string , ListenerType* , void (ListenerType::*) (void));
};


template <typename ListenerType>
void EventDispatcher::AddEventListener (string event, ListenerType* listener, void (ListenerType::*action) (void))
{
    Subscription<ListenerType>* subscription = new Subscription <ListenerType> (event, listener, action);
    this->subscriptions.push_back(subscription);
};

template <typename ListenerType>
void EventDispatcher::RemoveEventListener (string event, ListenerType* listener, void(ListenerType::*action) (void))
{
    int key = 0;
	
    for ( int key = 0; key < this->subscriptions.size(); ++key )
	{
        Subscription<ListenerType>* subscription = dynamic_cast <Subscription<ListenerType>* > (this->subscriptions[key]);
        if ( subscription && subscription->listener == listener && subscription->action == action)
        {
            this->subscriptions.erase(this->subscriptions.begin() + key);
        };
    };
};
