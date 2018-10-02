// generic_main.cpp
#include <iostream>
#include "generic_example.h"

using namespace std;

// Entry Point
int main( int argc, char *argv[] )
{
	cout << UseGlobalMethod() << endl;
	cout << UseGlobalClassPublicMethod() << endl;
	cout << UseGlobalClassProtectedMethod() << endl;
	cout << UseGlobalClassPrivateMethod() << endl;
	cout << UseMethod() << endl;
	cout << UsePublicMethod() << endl;
	cout << UseProtectedMethod() << endl;
	cout << UsePrivateMethod() << endl;
	return 0;
}