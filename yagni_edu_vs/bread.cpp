#include "bread.h"

Bread::Bread()
{
    std::cout << "The new product is done!\n";
}

Bread* BreadMaker::doBakeBread(ovenIf &ovenP)
{
    //return new Bread();

    if (true == ovenP.canBake())
    {
        // somehow making bread and:
        return new Bread();
    }
    else
    {
        // throw std::runtime_error ("Current oven cannot bake!\n");
        throw error_message ();
    }

}

