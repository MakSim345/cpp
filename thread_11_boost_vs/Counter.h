#include "stdafx.h"
#include "utils.h"
#include <string>
#include <stdlib.h>

//#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class Counter
{
    boost::mutex mutex;
    int count;

public:
    Counter();
    int increment();
};