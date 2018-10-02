// ghost_mock.h
#include <cxxtest/Mock.h>

CXXTEST_SUPPLY_GLOBAL( int,				/* Return type	*/
					   ghost,			/* Name			*/
					   ( int n ),		/* Prototype	*/
					   ( n )			/* How to call	*/ );