// generic.h


// Forward Delarations for the Mock classes to be able to access the private and
//  protected members. Did not want to include the generic_mock.h because that
//  would have formed a reference loop and why use #pragma once when not needed.
namespace T
{
	// Class Prototyptes
	class Real_MyGlobalClass_ClassProtectedMethod;
	class Real_MyGlobalClass_ClassPrivateMethod;
	class Real_MyName_MyClass_ProtectedMethod;
	class Real_MyName_MyClass_PrivateMethod;

	// Function Prototypes
	int classProtectedMethod(int);
	int classPrivateMethod(int);
	int protectedMethod(int);
	int privateMethod(int);
}


// Global Method Declaration
bool GlobalMethod( bool b );


// MyClass Declaration
class MyGlobalClass
{
	// Add the Mock classes and methods as friends so that the private and
	//  protected members can be mocked.
	friend class T::Real_MyGlobalClass_ClassProtectedMethod;
	friend class T::Real_MyGlobalClass_ClassPrivateMethod;
	friend int T::classProtectedMethod(int);
	friend int T::classPrivateMethod(int);
public:
	static int ClassPublicMethod( int n );
	int UseClassPrivateMethod( int n );
protected:
	static int ClassProtectedMethod( int n );
private:
	static int ClassPrivateMethod( int n );
};


// Namespace Declaration
namespace MyName
{
	// Namespace Method Declaration
	bool Method( bool b );

	// MyClass Declaration
	class MyClass
	{
		// Same reason as above class.
		friend class T::Real_MyName_MyClass_ProtectedMethod;
		friend class T::Real_MyName_MyClass_PrivateMethod;
		friend int T::protectedMethod(int);
		friend int T::privateMethod(int);
	public:
		static int PublicMethod( int n );
		int UsePrivateMethod( int n );
	protected:
		static int ProtectedMethod( int n );
	private:
		static int PrivateMethod( int n );
	};
}