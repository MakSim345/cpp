// MockGhost.h
#include <cxxtest/TestSuite.h>
#include "ghost_mock.h"

int useGhost();

class MockGhost : public T::Base_ghost
{
public:
	MockGhost() {}
	int ghost( int n ) { return 7; }
};

class TestGhost : public CxxTest::TestSuite
{
public:
	void test_Ghost()
	{
		// The mock object must be on the Heap in order to intercept the method call!
		MockGhost* m = new MockGhost();
		TS_ASSERT_EQUALS(useGhost(), 7);
		delete m;
	}
};