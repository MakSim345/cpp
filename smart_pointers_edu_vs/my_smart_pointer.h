#ifndef _MY_SMART_POINTER_H_
#define _MY_SMART_POINTER_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

template <typename T>
class my_smart_pointer
{
public: 
    T *objM;

    my_smart_pointer( T *obj)
        :objM(obj)
    {
     // empry constructor;
    }

    ~my_smart_pointer()
    {
     delete objM;
    }
    
    // overload operators "->" and "*":
    T* operator-> () {return objM;}
    T& operator*  () {return *objM;}

private:    
    
};


#endif
