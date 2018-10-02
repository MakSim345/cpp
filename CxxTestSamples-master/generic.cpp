// generic.cpp
#include "generic.h"

// Global Method Definition
bool GlobalMethod( bool b ) { return !b; }

// MyClass Definition
int MyGlobalClass::ClassPublicMethod( int n ) { return n; }
int MyGlobalClass::ClassProtectedMethod( int n ) { return n; }
int MyGlobalClass::ClassPrivateMethod( int n ) { return n; }
int MyGlobalClass::UseClassPrivateMethod( int n ) { return ClassPrivateMethod( n ); } // Not Used


// Namespace Definition
namespace MyName
{
	// Namespace Method
	bool Method( bool b ) { return !b; }

	// My Class Definitions
	int MyClass::PublicMethod( int n ) { return n; }
	int MyClass::ProtectedMethod( int n ) { return n; }
	int MyClass::PrivateMethod( int n ) { return n; }
	int MyClass::UsePrivateMethod( int n ) { return PrivateMethod( n ); } // Not Used
}