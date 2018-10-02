// MyTestSuite3.h
#include <cxxtest/TestSuite.h>

class MyTestSuite3 : public CxxTest::TestSuite
{
public:
	void testAddition(void)
	{
		TS_ASSERT(1 + 1 > 1);
		TS_ASSERT_EQUALS(1 + 1, 2);
	}
	
//	void testMultiplication( void )
//	{
//		TS_TRACE("Starting multiplication test");
//		TS_ASSERT_EQUALS(2 * 2, 5); // Expect failure
//		TS_TRACE("Finishing multiplication test");
//	}

/*	
	void testSubtraction( void )
	{
		TS_ASSERT( 1 - 1 < 1 );
		TS_ASSERT_EQUALS( 1 - 1, 0 );
	}
*/

	void XtestDivision(void)
	{
		TS_ASSERT(1 / 1 < 2);
		TS_ASSERT_EQUALS(1 / 1, 1);
	}
};