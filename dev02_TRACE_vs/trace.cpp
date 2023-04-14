//============================================================
//
// Description:
// Print trace messages.
//============================================================

//#include "stdafx.h"
#include "trace.h"

#include <time.h>
#include <Windows.h>


using namespace std;

void Trace::Initialize()
{
   delete gTraceInstanceM;
   gTraceInstanceM = new Trace();
}

void Trace::Initialize(string sUserFileName)
{
   delete gTraceInstanceM;
   gTraceInstanceM = new Trace(1, 0, sUserFileName);
   //m_gInstance = new Trace();
}

void Trace::Initialize(int toFile, int toConsole, string sUserFileName)
{
   delete gTraceInstanceM;
   gTraceInstanceM = new Trace(toFile, toConsole, sUserFileName);
}

void Trace::Initialize(int toFile, int toConsole, int nFileNameAuto)
{
   delete gTraceInstanceM;
   gTraceInstanceM = new Trace(toFile, toConsole, nFileNameAuto);
}

/*static*/
void Trace::Shutdown()
{
   delete gTraceInstanceM;
   gTraceInstanceM = 0;
}

/*static*/
Trace& Trace::Instance()
{
   return *gTraceInstanceM;
}



/********************************************************************

  Declaration: Default constructor. By default it will create an 
               object which printing trace to prompt only.
  Call: Trace()
  Input: none
  Returns: none
  26.10.2007 Initial coding

*********************************************************************/
Trace::Trace():
   isFileOpenM(0),
   traceToFileM(0),
   traceToConsoleM(1)   
{
 Trace(traceToFileM, traceToConsoleM, 0);
}

/********************************************************************

  Declaration: Constructor with parameters. Allow to choose default output
               filename or timestamp-style name.
  Call:  Trace(int, int, int)
  Input: to file, to cons, default filename or not.
  Returns: none
  26.05.2008 Initial coding

*********************************************************************/
Trace::Trace(int toFile, int toConsole, int nFileNameAuto):
   isFileOpenM(0),
   traceToFileM(toFile),
   traceToConsoleM(toConsole)
{
    if (!traceToFileM)
       return;
       
    if (!nFileNameAuto)
     { 
       setDefaultFileName("allegro.log");
       traceInit(sDefFileNameM);     
     }
    else
     {     
      traceInit( putTimeStampToFilename() );
     }
}

/********************************************************************

  Declaration: Constructor with parameters. Allow to choose user-defined
               output filename. in cae of error the filename will be defined.
               
  Call:  Trace(int, int, string)
  Input: to file, to cons, filename.
  Returns: none
  26.05.2008 Initial coding

*********************************************************************/
Trace::Trace(int toFile, int toConsole, string sUserFileName):
   isFileOpenM(0),
   traceToFileM(toFile),
   traceToConsoleM(toConsole)
{
    const int nFNameLen = MAX_FILENAME_LEN;
    
    if (sUserFileName.length() > nFNameLen )
     { 
       const char *cUserFileName = sUserFileName.c_str();
       setDefaultFileName("allegro.log");
       //printf ("ATTN! Filename '%s' has more than %d characters.\n", cUserFileName, nFNameLen);
       //printf ("All TRACE will go to file '%s'\n", m_sDefFileName.c_str());
       traceInit(sDefFileNameM);
     }
     else
     { 
       traceInit(sUserFileName);
     }
     
}
/********************************************************************

  Declaration: Destructor
  Call: ~Trace()
  Input: 
  Returns: none
  26.05.2008 Initial coding

*********************************************************************/
Trace::~Trace()
{  
  //TRACEY("End time: %d\n", Get1msTimeMS());
  if (1 == isFileOpenM)
  {
   //fclose (fi);
   fileInputM.close();
  }
}


/********************************************************************

  Declaration:                
  Call:  
  Input: 
  Returns: none
  26.05.2008 Initial coding PA

*********************************************************************/
ostringstream& Trace::getStream()
{
 return stringStreamM;
}

/********************************************************************

  Declaration:                
  Call:  
  Input: 
  Returns: none
  26.05.2008 Initial coding PA

*********************************************************************/
void Trace::printTrace()
{
    m_format = stringStreamM.flags();
    
    if (1 == traceToFileM)
      fileInputM << stringStreamM.str() << endl;
    if (1 == traceToConsoleM)
      cout << stringStreamM.str() << endl;
      
    stringStreamM.clear();
    stringStreamM.str("");
    stringStreamM.flags(m_format);
}

/********************************************************************

  Declaration: If output was enabled for file, open the file. Otherwise do not.
  Call:  traceInit ()
  Input: none
  Returns: none
  26.05.2008 Initial coding

*********************************************************************/
void Trace::traceInit(std::string sLogFileNameP)
{
  if (!traceToFileM) 
    return; // no file for output!       
   
  const char *cLogFileName = sLogFileNameP.c_str();
  // open the file for input:    
  
  fileInputM.open(cLogFileName, ios::out /*ios::app*/);    // open the streams
  isFileOpenM = 1;
  printTimeStamp();
}

void Trace::setDefaultFileName(string sFileName)
{
 sDefFileNameM = sFileName;
}

/********************************************************************

  Declaration: Put a time-stamp to TRACE stream
  Call: 
  Input: none
  Returns: none
  10.11.2007 Initial coding

*********************************************************************/
void Trace::printTimeStamp()
{
   char str[0x100];
   time_t system_time;
  
   time(&system_time); 
   ctime_s(str, 0x100, &system_time);
   
   getStream() << "TIMESTAMP: "<< str;
   printTrace();
 }

/********************************************************************

  Declaration:                
  Call:  
  Input: 
  Returns: none
  26.05.2008 Initial coding PA

*********************************************************************/
void Trace::print(const string& s)
{
    cout << s << endl;
}

/********************************************************************

  Declaration: Print string in Hexadecimal format to file or/and console
  Call: 
  Input: string buffer, int buffersize.
  Returns: none
  10.11.2007 Initial coding YS.

*********************************************************************/
void Trace::printHex()
{    
  unsigned char tmpchr;
  
  string strStr = stringStreamM.str();
  
  int NbrOfReadBytes = (int)strStr.length();
  const char *sStrC = strStr.c_str();
  
  stringStreamM.clear();
  stringStreamM.str("");
  
  getStream() << "Bytes: ";
  printTrace();
  
  for (int j=0; j < NbrOfReadBytes; j++)
  {
   tmpchr=(unsigned char) sStrC[j];
   if (1 == traceToFileM)
      fileInputM << "\\" << hex << showbase << (int)tmpchr;
   if (1 == traceToConsoleM)
      cout << "\\" << hex << showbase << (int)tmpchr;
  }
  
  getStream().flags( ios::dec || ios::right || ios::showbase);
  getStream() << "\n";
  printTrace();
}

/********************************************************************

  Declaration: 
  Call: 
  Input: 
  Returns: 
  10.06.2008 Initial coding.

*********************************************************************/
string Trace::putTimeStampToFilename()
{    
    SYSTEMTIME stime;    
    ::GetLocalTime(&stime);
    
    string sStr = "%.2d-%s-%.2d-%.2d-%.2d-%.2d.log";
    const char* cBuf = sStr.c_str();
    char *ctmpFileName= new char[50];
    char *m_MonthValue = new char[3];
    const int nNumCharMonth = 4;
    int nMonthVal = stime.wMonth;
    
    switch (nMonthVal)
    {
        case 1:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "JAN");
            break;
        case 2:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "FEB");
            break;
        case 3:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "MAR");
            break;
        case 4:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "APR");
            break;
        case 5:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "MAY");
            break;    
        case 6:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "JUN");
            break;
        case 7:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "JUL");
            break;
        case 8:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "AUG");
            break;
        case 9:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "SEP");
            break;
        case 10:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "OCT");
            break;
        case 11:
            sprintf_s(m_MonthValue, nNumCharMonth,"%s", "NOV");
            break;
        case 12:
            sprintf_s(m_MonthValue, nNumCharMonth, "%s", "DEC");
            break;        
        default:
            sprintf_s(m_MonthValue, nNumCharMonth, "%d", nMonthVal);
    }
    
    sprintf_s(ctmpFileName, strlen(cBuf), cBuf, stime.wYear, m_MonthValue, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
    sLogFileNameM = ctmpFileName;
    return sLogFileNameM;
}

/********************************************************************

  Declaration: 
  Call: 
  Input: 
  Returns: 
  10.06.2008 Initial coding.

*********************************************************************/
void Trace::selectMonth(const int nMonthValP)
{
 int i = nMonthValP;
}

/********************************************************************

  Declaration: 
  Call: 
  Input: 
  Returns: 
  10.01.2008 Initial coding PA.

*********************************************************************/
void  Trace::reporter(const string& sWho,
                int nLine,
                const string& sFile,
                const string& sStatement)
{
  getStream() << sWho+" failed: "+sStatement+", in file "+sFile+" on row " << nLine << "." << endl;
  printTrace();
  //cout << sWho+" failed: "+sStatement+", in file "+sFile+" on row " << nLine << "." << endl;
}

/********************************************************************

  Declaration: 
  Call: 
  Input: 
  Returns: 
  10.01.2008 Initial coding PA.

*********************************************************************/
void Trace::reportAssertFailure(int nLine,
                           const string& sFile,
                           const string& sStatement)
{
    reporter("Assert", nLine, sFile, sStatement);
}


/********************************************************************

  Declaration: 
  Call: 
  Input: 
  Returns: 
  10.01.2008 Initial coding PA.

*********************************************************************/
void Trace::reportVerifyFailure(int line,
                           const string& file,
                           const string& statement)
{
    reporter("Verify",line,file,statement);
}


// EOF
