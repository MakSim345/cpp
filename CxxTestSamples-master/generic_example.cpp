// generic_example.cpp
#include "generic_example.h"
#include "generic_mock.h"

bool UseGlobalMethod() { return T::GlobalMethod(true); }
int UseGlobalClassPublicMethod() { return T::classPublicMethod(1); }
int UseGlobalClassProtectedMethod() { return T::classProtectedMethod(1); }
int UseGlobalClassPrivateMethod() { return T::classPrivateMethod(1); }
bool UseMethod() { return T::method(true); }
int UsePublicMethod() { return T::publicMethod(1); }
int UseProtectedMethod() { return T::protectedMethod(1); }
int UsePrivateMethod() {return T::privateMethod(1); }