// generic_mock.h
#include "generic.h"
#include <cxxtest/Mock.h>


// MOCK MACROS:
// CXXTEST_MOCK                 ( MOCK, TYPE, NAME, ARGS, REAL, CALL )
// CXXTEST_MOCK_VOID            ( MOCK, NAME, ARGS, REAL, CALL )
// CXXTEST_SUPPLY               ( MOCK, TYPE, NAME, ARGS, REAL, CALL )
// CXXTEST_SUPPLY_VOID          ( MOCK, NAME, ARGS, REAL, CALL )
// CXXTEST_SUPPLY_C             ( MOCK, TYPE, NAME, ARGS, REAL, CALL )
// CXXTEST_SUPPLY_VOID_C        ( MOCK, NAME, ARGS, REAL, CALL )
// CXXTEST_MOCK_GLOBAL          ( TYPE, NAME, ARGS, CALL )
// CXXTEST_MOCK_VOID_GLOBAL     ( NAME, ARGS, CALL )
// CXXTEST_SUPPLY_GLOBAL        ( TYPE, NAME, ARGS, CALL )
// CXXTEST_SUPPLY_VOID_GLOBAL   ( NAME, ARGS, CALL )
// CXXTEST_SUPPLY_GLOBAL_C      ( TYPE, NAME, ARGS, CALL )
// CXXTEST_SUPPLY_VOID_GLOBAL_C ( NAME, ARGS, CALL )
//
// LEGEND:
// MOCK - Full path mock class name. (e.g. Namespace_Class_Method)
// TYPE - Return type of the method.
// NAME - If the MACRO has a REAL parameter, the custom name of the Mock method. (Must be different from the real method name!)
//        If the MACRO does not have a REAL parameter, the real name of the method being mocked.
// ARGS - Prototype parameters type and name list. (Must contain surrounding parenthases to prevent comma confusion!)
// REAL - The full real name of the method being mocked. (e.g. Namespace::Class::Method)
// CALL - List of just the parameter argument names. (e.g. ARGS = ( int n, bool b, char c ) then CALL = ( n, b, c )


// Mocks
CXXTEST_MOCK_GLOBAL( bool,					/* Return type			*/
					 GlobalMethod,			/* Name of real method	*/
					 ( bool b ),			/* Prototype			*/
					 ( b )					/* Argument list		*/ );

CXXTEST_MOCK( MyGlobalClass_ClassPublicMethod,	/* Suffix of mock class/namespace	*/
			  int,								/* Return type						*/
			  classPublicMethod,				/* Name of mock function			*/
			  ( int n ),						/* Prototype						*/
			  MyGlobalClass::ClassPublicMethod,	/* Name of the real method			*/
			  ( n )								/* Parameter list					*/ );

CXXTEST_MOCK( MyGlobalClass_ClassProtectedMethod,	/* Suffix of mock class/namespace	*/
			  int,									/* Return type						*/
			  classProtectedMethod,					/* Name of mock function			*/
			  ( int n ),							/* Prototype						*/
			  MyGlobalClass::ClassProtectedMethod,	/* Name of the real method			*/
			  ( n )									/* Parameter list					*/ );

CXXTEST_MOCK( MyGlobalClass_ClassPrivateMethod,		/* Suffix of mock class/namespace	*/
			  int,									/* Return type						*/
			  classPrivateMethod,					/* Name of mock function			*/
			  ( int n ),							/* Prototype						*/
			  MyGlobalClass::ClassPrivateMethod,	/* Name of the real method			*/
			  ( n )									/* Parameter list					*/ );

CXXTEST_MOCK( MyName_Method,	/* Suffix of mock class/namespace	*/
			  bool,				/* Return type						*/
			  method,			/* Name of mock function				*/
			  ( bool b ),		/* Prototype						*/
			  MyName::Method,	/* Name of the real method			*/
			  ( b )				/* Parameter list					*/ );

CXXTEST_MOCK( MyName_MyClass_PublicMethod,		/* Suffix of mock class/namespace	*/
			  int,								/* Return type						*/
			  publicMethod,						/* Name of mock function			*/
			  ( int n ),						/* Prototype						*/
			  MyName::MyClass::PublicMethod,	/* Name of the real method			*/
			  ( n )								/* Parameter list					*/ );

CXXTEST_MOCK( MyName_MyClass_ProtectedMethod,	/* Suffix of mock class/namespace	*/
			  int,								/* Return type						*/
			  protectedMethod,					/* Name of mock function			*/
			  ( int n ),						/* Prototype						*/
			  MyName::MyClass::ProtectedMethod,	/* Name of the real method			*/
			  ( n )								/* Parameter list					*/ );

CXXTEST_MOCK( MyName_MyClass_PrivateMethod,		/* Suffix of mock class/namespace	*/
			  int,								/* Return type						*/
			  privateMethod,					/* Name of mock function			*/
			  ( int n ),						/* Prototype						*/
			  MyName::MyClass::PrivateMethod,	/* Name of the real method			*/
			  ( n )								/* Parameter list					*/ );
