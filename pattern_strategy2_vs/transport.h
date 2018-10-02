#ifndef _TRANSPORT_H_ 
#define _TRANSPORT_H_

#include "gen.h"

class transport;

class TakeTransport
{
public:
    enum TransportType
    {
     OWN_CAR, TAXI, LIMO
    };
    
    TakeTransport()
    {
        _transport = NULL;    
    }
    void setStrategy(int type);
    void doIt();

private:    
    // this would be an interface to any possible selected transport:
    transport * _transport;
};

class transport
{
public:
    transport() {} ;
    virtual void drive() = 0;
};

class own_car : public transport
{
  public:
    own_car():
        m_name("own_car") {};
    void drive() 
    {
        cout << "Drive with " << m_name << "- ... " << endl;
    }

private:
    const string m_name;
};

class taxi : public transport
{
  public:
    taxi():
        m_name("taxi") {};
    void drive() 
    {
        cout << "Drive with " << m_name << "- ... " << endl;
    }

private:
    const string m_name;
};

class limo : public transport
{
  public:
    limo():
        m_name("limousine") {};
    void drive() 
    {
        cout << "Drive with " << m_name << "- ... " << endl;
    }

private:
    const string m_name;
};
/*
Several options exist such as:
    - driving ones own car, 
    - taking a taxi, 
    - a limousine service. 
    - an airport shuttle, 
    - a city bus,     
For some airports are also available:
    - subways 
    - helicopters
*/

void TakeTransport::setStrategy(int type)
{
    delete _transport;
    if (type == OWN_CAR)
    {
        _transport = new own_car();
    }
    else if (type == TAXI)
    {
        _transport = new taxi();
    }
    else if (type == LIMO)
    {
        _transport = new limo();
    }

}

void TakeTransport::doIt()
{
    _transport->drive();    
}

#endif