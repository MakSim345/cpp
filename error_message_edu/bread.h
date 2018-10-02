#ifndef _BREAD_H_
#define _BREAD_H_

#include "gen.h"
#include "oven.h"
#include "error_message.h"


class Bread
{
public:
    Bread();
    ~Bread();

private:
    float weight;
};

class BreadMaker
{
public:

    Bread* BakeBread(iOven &oven)
    {
        //return new Bread();
        
        if (true == oven.canBake())
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


    int run()
    {
        return _number;
    }

private:
    int _number;
};

#endif
