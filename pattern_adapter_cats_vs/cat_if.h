#ifndef _CAT_IF_H_
#define _CAT_IF_H_

#include "gen.h"

class iHomeCat
{
public:
    virtual ~iHomeCat() {}

    virtual void Meow() const = 0;    
    virtual void  Scratch() const = 0;
    
    virtual std::string Name() const
    {        
        return _name;
    }        
    
    virtual void setName(std::string _new_name)
    {
        _name = _new_name;
    }        

private:
    std::string _name;
};


class iWildCat
{
public:
    virtual ~iWildCat() {}

    virtual void Growl() const = 0;    
    virtual void  Scratch() const = 0;
    
    virtual std::string Breed() const = 0;

private:
    std::string _breed;
};

#endif
