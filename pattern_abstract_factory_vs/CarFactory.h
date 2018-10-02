#ifndef _CAR_FACTORY_H_
#define _CAR_FACTORY_H_

#include <iostream>
 
// AbstractProductA
class ICar
{
public:
    virtual void printName() = 0;
};
 
// ConcreteProductA1
class Ford : public ICar
{
public:
    virtual void printName() 
    { 
            std::cout << "Ford" << std::endl; 
    }
};
 
// ConcreteProductA2
class Toyota : public ICar
{
public:
    virtual void printName() 
    { 
            std::cout << "Toyota" << std::endl; 
    }
};
 
// AbstractProductB
class IEngine
{
public:
    virtual void printPower() = 0;
};
 
// ConcreteProductB1
class FordEngine : public IEngine
{
public:
    virtual void printPower() 
    { 
            std::cout << "Ford Engine 4.4" << std::endl; 
    }
};
 
// ConcreteProductB2
class ToyotaEngine : public IEngine
{
public:
    virtual void printPower() 
    { 
            std::cout << "Toyota Engine 3.2" << std::endl; 
    }
};
 
 
// AbstractFactory
class ICarFactory
{
public:
    virtual ICar*     createCar()    = 0;
    virtual IEngine*  createEngine() = 0;
};
 
// ConcreteFactory1
class FordFactory : public ICarFactory
{
public:
    // from ICarFactory
    virtual ICar* createCar()
    {
        return new Ford();
    }

    virtual IEngine* createEngine()
    {
        return new FordEngine();
    }
};
 
// ConcreteFactory2
class ToyotaFactory : public ICarFactory
{
public:
    // from ICarFactory
    virtual ICar* createCar()
    {
        return new Toyota();
    }

    virtual IEngine* createEngine()
    {
        return new ToyotaEngine();
    }
};
 
 
void use(ICarFactory* f)
{
    ICar*     myCar     =  f->createCar();
    IEngine*  myEngine  =  f->createEngine();

    myCar->printName();
    myEngine->printPower();

    delete myCar;
    delete myEngine;
}
#endif

