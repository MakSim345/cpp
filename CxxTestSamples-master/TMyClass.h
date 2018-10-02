// TMyClass.h

template <typename T>
class TMyClass
{
public:

	T value;

	TMyClass(T value_) : value(value_) {}

	// CxxTest require a copy constructor
	TMyClass(const TMyClass& other) : value(other.value) {}

	// This is required if you want to use TS_ASSERT_EQUALS
	bool operator==(const TMyClass& other) const { return value == other.value; }

	// If you want to use TS_ASSERT_LESS_THAN
	bool operator<(const TMyClass& other) const { return value < other.value; }
};

#ifdef CXXTEST_RUNNING
// This declaration is only activated when building a CxxTest test suite
#include <cxxtest/ValueTraits.h>
#include <stdio.h>

namespace CxxTest
{
	CXXTEST_TEMPLATE_INSTANTIATION
	class ValueTraits< TMyClass<int> >
	{
		char _s[256];
	
	public:
		ValueTraits( const TMyClass<int>& m ) { sprintf( _s, "MyClass<int>( %i )", m.value ); }
		const char *asString() const { return _s; }
	};
};
#endif // CXXTEST_RUNNING