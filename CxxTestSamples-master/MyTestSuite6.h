// MyTestSuite6.h
#include <cxxtest/TestSuite.h>

class MyTestSuite6 : public CxxTest::TestSuite
{
public:
	static MyTestSuite6* createSuite()
	{
		#ifdef _MSC_VER
		// Only allow this test suite if using MSVC.
		return new MyTestSuite6();
		#else
		return 0;
		#endif
	}

	static void destroySuite( MyTestSuite6* suite )
	{ delete suite; }

	void test_nothing()
	{
		TS_FAIL( "Nothing to test" );
	}
};