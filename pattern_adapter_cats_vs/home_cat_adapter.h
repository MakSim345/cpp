#ifndef _home_cat_adapter_H_
#define _home_cat_adapter_H_

#include "gen.h"
#include "cat_if.h"
#include "tiger.h"


class HomeCatAdapter : public iHomeCat
{
public:
    HomeCatAdapter(iWildCat &aWildCat) 
    : _wildCat(new Tiger())    
    {
        // _wildCat = new Tiger();
       *_wildCat = aWildCat;
        // _wildCat->Growl();
    }

    virtual ~HomeCatAdapter() {}

    virtual std::string Name() const
    {        
        return _wildCat->Breed();
    }        
    
    virtual void Meow() const
    {
        _wildCat->Growl();
    }        

    virtual void  Scratch() const
    {
        _wildCat->Scratch();
    } 

private:
    std::string _name;
    iWildCat *_wildCat;

};

#endif
