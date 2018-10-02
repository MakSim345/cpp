#include "stdafx.h"
#include "Counter.h"

Counter::Counter()
    :count(0)
{
    // TODO:
}

int Counter::increment() 
{
    mutex::scoped_lock scoped_lock(mutex);
    return ++count;
}
