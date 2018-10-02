#ifndef _TIGER_H_
#define _TIGER_H_

#include "gen.h"
#include "cat_if.h"

/*
The Tiger and iWildCat classes provided by third-party developer and we can not change it's 
implementation. However, we would like to use it in Cat_info_printer just like usual cat.

For such purpose we create Adapter Home_Class_Adapter, derived from iHomeCat and 
taking iWildCat as a parameter. In that adapter we incapsulate iWildCat functions into
iHomeCat methods.

*/
class Tiger: public iWildCat
{
public:
    Tiger()  
    {
        _breed = "Tiger vulgarius";
    }
    virtual ~Tiger() {}

    virtual void Growl() const
    {
        std::cout << "Grrrrrrrrrrr\n";
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
