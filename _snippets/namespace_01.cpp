// TestNameSpace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream.h"

namespace spaceA
{
    int MyVal=10;
}

namespace spaceB
{
    int MyVal=20;
}

namespace spaceC
{
    int MyVal=30;
}

void Test()
{
    using namespace spaceB;
    cout << MyVal << " " << "spaceB" << endl;
}

void main()
{
    using namespace spaceA;
    cout << MyVal << " " << "spaceA" << endl;
    Test();
    cout << spaceC::MyVal << " " << "spaceC" << endl;
}
