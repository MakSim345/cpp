



#ifndef __SIMPLETEST_H
#define __SIMPLETEST_H

#include <cxxtest/TestSuite.h>

//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//

class SimpleTest : public CxxTest::TestSuite
{
public:
    void testEquality()
    {
        TS_ASSERT_EQUALS( 1, 1 );
        TS_ASSERT_EQUALS( 1, 2 );
        TS_ASSERT_EQUALS( 'a', 'A' );
        TS_ASSERT_EQUALS( 1.0, -12345678900000000000000000000000000000000000000000.1234 );
    }

    void testAddition()
    {
        TS_ASSERT_EQUALS( 1 + 1, 2 );
        TS_ASSERT_EQUALS( 2 + 2, 5 );
    }

    void TestMultiplication()
    {
        TS_ASSERT_EQUALS( 2 * 2, 4 );
        TS_ASSERT_EQUALS( 4 * 4, 44 );
        TS_ASSERT_DIFFERS( -2 * -2, 4 );
    }

    void testComparison()
    {
        TS_ASSERT_LESS_THAN( (int)1, (unsigned long)2 );
        TS_ASSERT_LESS_THAN( -1, -2 );
    }

#endif //  __SIMPLETEST_H
