#pragma once

#include "gen.h"

class ObserverIf
{
public:
    virtual void Update(double IbmPrice, double ApplePrice, double GooglePrice) = 0;
};

class SubjectIf
{
public:
    // virtual Subject() {}
    virtual void Register(ObserverIf* o) = 0;
    virtual void UnRegister(ObserverIf* o)=0;
    virtual void notifyObservers() = 0;
};

class StockObserver: public ObserverIf
{
public:
    static int observerIDTracker;

    StockObserver(SubjectIf* newStockGrabber)
    {
        refStockGrabber = newStockGrabber;
        refStockGrabber->Register(this);
        this->observerID = ++observerIDTracker;
    }

    void Update(double IbmPrice, double ApplePrice, double GooglePrice)
    {
        ibmPrice = IbmPrice;
        applPrice = ApplePrice;
        googPrice = GooglePrice;
        printThePrices();
    }

    void printThePrices()
    {
        std::cout << "Observer number " << observerID << " receives:" << std::endl;
        std::cout << "IbmPrice = " << ibmPrice << std::endl;
        std::cout << "ApplePrice = " << applPrice << std::endl;
        std::cout << "GooglePrice = " << googPrice << std::endl;
        std::cout << "----------------------------" << std::endl;
    }

private:
    double ibmPrice;
    double applPrice;
    double googPrice;
    int observerID;

    SubjectIf* refStockGrabber;
};

class StockGrabber: public SubjectIf
{
public:

    StockGrabber():
      IbmPrice(0.0),
      ApplePrice(0.0),
      GooglePrice(0.0)
    {

    }

    virtual void Register(ObserverIf* newObserver)
    {
        observers.insert(newObserver);
    }

    virtual void UnRegister(ObserverIf* deleteObserver)
    {
        observers.erase(deleteObserver);
    }

    virtual void notifyObservers()
    {
        set<ObserverIf*>::iterator itr;

        for ( itr = observers.begin(); itr != observers.end(); itr++ )
        { 
            (*itr)->Update( IbmPrice, ApplePrice, GooglePrice);
        }
    }

    void setIBMPrice(double newIBMPrice)
    {
        this->IbmPrice = newIBMPrice;
        notifyObservers();
    }

    void setAPPLEPrice(double newAPPLEPrice)
    {
        this->ApplePrice = newAPPLEPrice;
        notifyObservers();
    }

    void setGOOGPrice(double newGOOGPrice)
    {
        this->GooglePrice = newGOOGPrice;
        notifyObservers();
    }

private:
    set<ObserverIf*> observers;

    double IbmPrice;
    double ApplePrice;
    double GooglePrice;
};
