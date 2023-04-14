//#include <iostream>
#include "utils.h"

using namespace std;

#define USE_VIRTUAL

class FlyBehavior
{
public:
    virtual void fly() = 0;
};

class FlyWithWings: public FlyBehavior
{
public:    
    void fly() { cout << "I'm flying!" << endl; }
};

class FlyNoWay: public FlyBehavior
{
public:
    void fly() { cout << "I can not fly!" << endl; }
};

class FlyRocketPowered: public FlyBehavior
{
public:
    void fly() { cout << "I am flying with a ROCKET!" << endl; }
};

class QuackBehavior
{
public:
    virtual void quack() = 0;
};

class Quack: public QuackBehavior
{
public:    
    void quack() { cout << "Quack!" << endl; }
};

class MuteQuack: public QuackBehavior
{
public:
    void quack() { cout << ".......silence......." << endl; }
};

class Squeak: public QuackBehavior
{
public:
    void quack() { cout << "Squeak!" << endl; }
};

class Duck
{   
public:    
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;

    Duck(){ }
    virtual void display() = 0;

    void performFly()
    {
        flyBehavior->fly();
    }

    void performQuack()
    {
        quackBehavior->quack();
    }

    void swim()
    {
        cout << "All ducks float. Even decoy." << endl;
    }

    void setFlyBehavior (FlyBehavior *fb)
    {
        this->flyBehavior = fb;
    }

    void setQuackBehavior (QuackBehavior *qb)
    {
        this->quackBehavior = qb;
    }
};


class MallarDuck: public Duck
{
public:
    MallarDuck() 
    {
        quackBehavior = new MuteQuack();
        flyBehavior = new FlyWithWings();
    }
    void display() { cout << "I am a real Mallar Duck." << endl; }
};


class ModelDuck: public Duck
{
public:
    ModelDuck() 
    {
        quackBehavior = new Quack();
        flyBehavior = new FlyNoWay();
    }
    void display() { cout << "I am a real model Duck." << endl; }
};

int main()
{
    cout << "Duck simulator start:" << endl;

    Duck *mallard = new MallarDuck();
    mallard->display();
    mallard->performQuack();
    mallard->performFly();

    Duck *model = new ModelDuck();
    model->display();
    model->performQuack();
    model->performFly();
    model->setFlyBehavior(new FlyRocketPowered());
    model->performFly();

    cout << "Duck simulator end." << endl;

    system("PAUSE");
    // getch();
}


