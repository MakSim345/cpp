#ifndef _MY_SMART_PTR_H_
#define _MY_SMART_PTR_H_

//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

#include <boost/scoped_ptr.hpp>
#include <boost/intrusive_ptr.hpp>

class sPtrClass
{
public:
    sPtrClass(){ std::cout << "Borrow the cat" << std::endl; }
    ~sPtrClass(){  std::cout << "Return the cat" << std::endl; }
};
#endif
