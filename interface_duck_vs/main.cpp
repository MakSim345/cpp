#include <conio.h>
#include <iostream>
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
};


class MallarDuck: public Duck
{
public:
    MallarDuck() 
    {
        quackBehavior = new MuteQuack();
        flyBehavior = new FlyWithWings();
    }
    void display() { cout << "Iam a real Mallar Duck." << endl; }
};

int main()
{
    cout << "APP start:" << endl;

    Duck *mallard = new MallarDuck();
    mallard->performQuack();
    mallard->performFly();

    cout << "APP end." << endl;
    // getch();
}


