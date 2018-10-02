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
    T *m_obj;

    my_smart_pointer(T *obj)
        :m_obj(obj)
    {
     // empry constructor;
    }

    ~my_smart_pointer()
    {
     delete m_obj;
    }
    
    // overload operators:
    T* operator-> () {return m_obj;}
    T& operator*  () {return *m_obj;}

private:    
    
};


#endif
