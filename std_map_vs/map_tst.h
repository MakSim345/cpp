#ifndef _MAP_TEST_H_
#define _MAP_TEST_H_
//============================================================
//
// Author:         YS /
//
//============================================================
// Description:
//==========================================================
#include "gen.h"
#include <map>

void map_test ();

template<class Iterator, class Value>
Iterator find_value(Iterator begin, Iterator end, const Value& value)
{
    while (begin!=end) 
    {
        if ((*begin).second==value) 
            return begin;
        
        ++begin;
    }
    return end;
}

#endif 
