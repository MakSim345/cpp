#ifndef _DOG_H_
#define _DOG_H_

#include "gen.h"

// Interface class:
class Dog
{
public:    
    virtual ~Dog() = default;// virtual destructor
    virtual void Bark() const = 0; // pure virtual function    
};

class PuddleDog: public Dog
{
public:
    PuddleDog()  
    {
        _breed = "PuddleDog vulgarius";
    }
    virtual ~PuddleDog() {}

    virtual void Bark() const
    {
        std::cout << "Hau-Hau\n";
    }        

    virtual void  Scratch() const
    {
        std::cout << "Terrible deadly Scratch!\n";
    } 
    
    virtual std::string Breed() const
    {        
        return _breed;
    }  

private:
    std::string _breed;    

};

#endif
