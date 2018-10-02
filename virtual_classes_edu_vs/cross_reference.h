#ifndef _CROSS_REFERENCE_H_
#define _CROSS_REFERENCE_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"
#include "derived_class.h"

class derived_class;

class cross_reference
{
public:
    cross_reference(derived_class _new_der_class) 
    {
        data = 10;
    }

    virtual void set()
    {
        std::cout << "cross_ref is increasing" << std::endl;
        data++;
    }

    int get()
    {
        set();
        return data;
    }

protected:
    int data;
    derived_class my_derived_class;
};

#endif
