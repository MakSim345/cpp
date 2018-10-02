#ifndef _DERIVED_CLASS_H_
#define _DERIVED_CLASS_H_
//============================================================
//
//
//============================================================
//
// File:           virtual_foo.h
// Project:        Genie Carestation SW
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class cross_reference;
#include "cross_reference.h"

class derived_cl
{
public:
    derived_cl() 
    {
        data = 10;
    }

    virtual void set()
    {
        std::cout << "derived_cl class is increasing" << std::endl;
        data++;
    }

    int get()
    {
        set();
        return data;
    }

protected:
    int data;
    cross_reference *m_crf;
	
};

class derived_class : public derived_cl
{
public:
    void set()
    {
        std::cout << "derived_class is decreasing" << std::endl;
        data--;
    }
};

#endif
