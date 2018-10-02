//============================================================
//
// Description:
// Tracing and debugging macros
//
// Usage:
// DEB_TRACES definition activates traces
// ASSERT and VERIFY are both compiled to debug build
// VERIFY's test assignment is compiled also to release
//
//============================================================
#ifndef __TRACE_H__
#define __TRACE_H__

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <list>

using namespace std;

#define ERROR(x) Trace::Instance().getStream() << x;\
	Trace::Instance().printTrace()
#define LOG(x) Trace::Instance().getStream() << x;\
	Trace::Instance().printTrace()

#define MAX_FILENAME_LEN 20

// DEB_TRACES definition activates traces
// _DEBUG is defined when compiling debug version in Visual Studio
#ifdef _DEBUG
// Assert and verify will abort the program immediately after failing
// expression. abort() will provide possibility to break and open a debugger.
#define ASSERT(x) if ((x)==0) { \
        Trace::Instance().reportAssertFailure(__LINE__,__FILE__,#x); \
        abort(); }

#define VERIFY(x) if ((x)==0) { \
        Trace::Instance().reportVerifyFailure(__LINE__,__FILE__,#x); \
        abort(); }
        
#define TRACE(x) Trace::Instance().getStream() << x;\
	    Trace::Instance().printTrace();
	    
#define TRACE_HEX(x) Trace::Instance().getStream() << x;\
	    Trace::Instance().printHex();

#else
// NOTE that all asserts will be removed from the release compilation!
// Tests that should be there anyway must use VERIFY.
#define ASSERT(x)
#define VERIFY(x) (x)
#define TRACE(x)
#define TRACE_HEX(x)
#endif


// Trace class can be later on extended to log assert & verify failures
// automatically
class Trace
{
	
public:

    static void Initialize();
    static void Initialize(string sUserFileName);
    static void Initialize(int toFile, int toConsole, string sUserFileName);
    static void Initialize(int toFile, int toConsole, int nFileNameAuto = 0);
    
    static void Shutdown();
    static Trace& Instance();
        
	ostringstream m_ss;
	ios_base::fmtflags m_format;
	
	void printTrace();
	void printHex();
	void printTimeStamp();
	void print(const string& s);
	
	ostringstream& getStream();

    void setDefaultFileName(string sFileName);
	
    
    void reporter(const string& who,
                  int line,
                  const string& file,
                  const string& statement);                         
    
    void reportAssertFailure(int line,
                             const string& file,
                             const string& statement);
    
    void reportVerifyFailure(int line,
                             const string& file,
                             const string& statement);
	
private:

    static Trace* m_gInstance;

    Trace();
    Trace(string sUserFileName);
	Trace(int toFile, int toConsole, string sUserFileName);
	Trace(int toFile, int toConsole, int nFileNameAuto = 0);
   ~Trace();

    //Trace(const Trace&);
    //Trace& operator = (const Trace&);
    
    string putTimeStampToFilename();
    void selectMonth(int nMonthVal);
    void traceInit(string sLogFileName);
    string m_sDefFileName; //  "allegro.log";
    string m_sLogFileName;
	ofstream fInput;
	int m_FileIsOpen;
	int m_TraceToFile;
	int m_TraceToCons;
};


#endif // __TRACE_H__
