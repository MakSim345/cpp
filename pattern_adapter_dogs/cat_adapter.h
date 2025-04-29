#ifndef _cat_adapter_H_
#define _cat_adapter_H_

#include "gen.h"
#include "cat.h"
#include "dog.h"


class CatAdapter : public Dog
{
public:
    CatAdapter(Cat &catP): catM(catP) { }

    /*
    virtual std::string Name() const
    {        
        return catM->Breed();
    }        
    
    */
    virtual void Bark() const override
    {
        catM.Meow();
    }        

    /*
    virtual void  Scratch() const
    {
        catM->Scratch();
    } 
    */

private:
    std::string _name;
    Cat& catM; // Reference to the Cat object
};

#endif
