// MockGeneric.h
#include <cxxtest/TestSuite.h>
#include "generic_mock.h"
#include "generic_example.h"


class MockObjects :
	public T::Base_GlobalMethod,
	public T::Base_MyGlobalClass_ClassPublicMethod,
	public T::Base_MyGlobalClass_ClassProtectedMethod,
	public T::Base_MyGlobalClass_ClassPrivateMethod,
	public T::Base_MyName_Method,
	public T::Base_MyName_MyClass_PublicMethod,
	public T::Base_MyName_MyClass_ProtectedMethod,
	public T::Base_MyName_MyClass_PrivateMethod
{
public:
	MockObjects() {}
	bool GlobalMethod( bool b ) { return true; }
	int classPublicMethod( int n ) { return 7; }
	int classProtectedMethod( int n ) { return 7; }
	int classPrivateMethod( int n ) { return 7; }
	bool method( bool b ) { return true; }
	int publicMethod( int n ) { return 7; }
	int protectedMethod( int n ) { return 7; }
	int privateMethod( int n ) { return 7; }
};


class TestObjects : public CxxTest::TestSuite
{
public:
	void test_MockObjects()
	{
		// Use Mock Methods
		//MockObjects m(); // Will not mock the methods if using this call!
		// Must create the mock on the heap for the tests to work!!!
		MockObjects* p = new MockObjects();
		TS_ASSERT_EQUALS( UseGlobalMethod(), true );
		TS_ASSERT_EQUALS( UseGlobalClassPublicMethod(), 7 );
		TS_ASSERT_EQUALS( UseGlobalClassProtectedMethod(), 7 );
		TS_ASSERT_EQUALS( UseGlobalClassPrivateMethod(), 7 );
		TS_ASSERT_EQUALS( UseMethod(), true );
		TS_ASSERT_EQUALS( UsePublicMethod(), 7 );
		TS_ASSERT_EQUALS( UseProtectedMethod(), 7 );
		TS_ASSERT_EQUALS( UsePrivateMethod(), 7 );
		delete p;
	}

	void test_RealObjects()
	{
		// Use Real Methods
		MockObjects* p = new MockObjects();

		T::Real_GlobalMethod* q = new T::Real_GlobalMethod();
		TS_ASSERT_EQUALS( UseGlobalMethod(), false );
		delete q;

		T::Real_MyGlobalClass_ClassPublicMethod* r = new T::Real_MyGlobalClass_ClassPublicMethod();
		TS_ASSERT_EQUALS( UseGlobalClassPublicMethod(), 1 );
		delete r;

		T::Real_MyGlobalClass_ClassProtectedMethod* s = new T::Real_MyGlobalClass_ClassProtectedMethod();
		TS_ASSERT_EQUALS( UseGlobalClassProtectedMethod(), 1 );
		delete s;

		T::Real_MyGlobalClass_ClassPrivateMethod* t = new T::Real_MyGlobalClass_ClassPrivateMethod();
		TS_ASSERT_EQUALS( UseGlobalClassPrivateMethod(), 1 );
		delete t;

		T::Real_MyName_Method* u = new T::Real_MyName_Method();
		TS_ASSERT_EQUALS( UseMethod(), false );
		delete u;

		T::Real_MyName_MyClass_PublicMethod* v = new T::Real_MyName_MyClass_PublicMethod();
		TS_ASSERT_EQUALS( UsePublicMethod(), 1 );
		delete v;

		T::Real_MyName_MyClass_ProtectedMethod* w = new T::Real_MyName_MyClass_ProtectedMethod();
		TS_ASSERT_EQUALS( UseProtectedMethod(), 1 );
		delete w;

		T::Real_MyName_MyClass_PrivateMethod* x = new T::Real_MyName_MyClass_PrivateMethod();
		TS_ASSERT_EQUALS( UsePrivateMethod(), 1 );
		delete x;

		delete p;
	}
};