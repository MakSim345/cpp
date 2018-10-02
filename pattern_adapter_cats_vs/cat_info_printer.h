#ifndef _CAT_INFO_PRINTER_H_
#define _CAT_INFO_PRINTER_H_

#include "gen.h"
#include "cat_if.h"
#include "cats.h"


class CatInfoPrinter
{
public:
    CatInfoPrinter() 
    {

    }
    ~CatInfoPrinter() {}

    // void PrintCatInfo(const iHomeCat &cat)
    void PrintCatInfo(iHomeCat &cat)
    {
        // REM: Meow and all other methods have to be const in order to use here!
        std::cout << "\nCat's info. " << "\n";
        std::cout << "     name   : " << cat.Name() << "\n";
        std::cout << "     meow   : ";
        cat.Meow();         
        std::cout << "     scratch: ";
        cat.Scratch(); 
    } 
};

#endif
