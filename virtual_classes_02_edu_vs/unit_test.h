// MyTestSuite1.h
#include <cxxtest/TestSuite.h>

#include "base.h"

class baseTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateBase()
    {
        MyBase a;
        // cout << "a.CallFunction(5) = " << a.CallFunction(5)<< endl;      // 11
        TS_ASSERT_EQUALS(11, a.CallFunction(5));
    }

    void testCreateDerived()
    {
        //atient * _my_patient = new Patient("Alive", "bed9");
        //TS_ASSERT(_my_patient->isAlive());
        Derived d;
        // cout << "d.CallFunction(5) = " << d.CallFunction(5)<< endl;      // which f() to call?
        TS_ASSERT_EQUALS(26, d.CallFunction(5));
    }
};
 
