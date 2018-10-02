
// MyTestSuite1.h
#include <cxxtest/TestSuite.h>

class MyTestSuite: public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT (1 + 1 > 1);
        TS_ASSERT_EQUALS (1 + 1, 2);
    }

    void testMultiplication(void)
    {
        TS_ASSERT_EQUALS(2 * 2, 4)
    }
    
    void TestMultiplication()
    {
        TS_ASSERT_EQUALS(2 * 2, 4);
        TS_ASSERT_EQUALS(4 * 4, 16);
        TS_ASSERT_DIFFERS(2 * 2, 3); // -2 * -2 = 4?
    }

    void testComparison()
    {
        TS_ASSERT_LESS_THAN((int)1, (unsigned long)2);
        TS_ASSERT_LESS_THAN(-3, -2);
    }

    void testEquality()
    {
        //TS_ASSERT_EQUALS( 1, 1 );
        TS_ASSERT_EQUALS( 1, 2 );
        //TS_ASSERT_EQUALS( 'a', 'A' );
        // TS_ASSERT_EQUALS( 1.0, -12345678900000000000000000000000000000000000000000.1234 );
    }
};

