#pragma once

#include "gen.h"
#include "FlyBehaviorIf.h"

class Animal
{   
public:    

    Animal(){ }

    // virtual void display() = 0;

    FlyBehaviorIf *flyingType;

    void tryTofly()
    {
        flyingType->fly();
    }

    void setFlyingAbility(FlyBehaviorIf *newFlyingType )
    {
        this->flyingType = newFlyingType;
    }

    string getName() { return name;};
    void   setName(string new_name) {name = new_name;};

    string getSound() { return sound;};
    void   setSound(string new_sound) {sound = new_sound;};
    
private:
	string name;
	double height;
    int weight;
    string favFood;
    double speed;
    string sound;
};

class Dog: public Animal
{
public:
    
    Dog()
    {
        setSound("Bark");
        flyingType = new FlyNoWay();
    }

    void digHole()
    {
        cout << "Dug a hole\n";
    }
private:

};

class Bird: public Animal
{
public:

    Bird()
    {
        setSound("Tweet");
        flyingType = new FlyCanDo();
    }
private:

};
