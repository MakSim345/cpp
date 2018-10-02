/************************************************************************

   Description:   Configuration file/storage interface
   File:          CFGFILE.H

    Convert the config API into a C++ class interface? 
    Constructor sets the application name, then uses that on all 
    subsequent function calls etc.
 *************************************************************************/
#ifndef CFGFILE_H
#define CFGFILE_H

#include "gen.h"

class CFGFile
{
public: 
 // Constructor with an argument:
 CFGFile(char* szFileName); 
 // Default constructor:
 CFGFile(); 
  
 /*-------------------------------------------------------------------------
  Get integer from resource file
  -------------------------------------------------------------------------*/
 BOOL GetProfileInt(char* lpszSection, char* lpszEntry, int nDefaultValue, int * lpnResult);

 /*-------------------------------------------------------------------------
  Get integers (several from same entry line, divided with whitespace) from resource file
  -------------------------------------------------------------------------*/
 BOOL GetProfileInts(char* lpszSection, char* lpszEntry, int number, int* pnDefaultValue, int * lpnResult);

 /*-------------------------------------------------------------------------
  Get a double from resource file
  -------------------------------------------------------------------------*/
 BOOL GetProfileDouble(char* pszSection, char* pszEntry, double fltDefaultValue, double* pnResult ); 

/*-------------------------------------------------------------------------
  Get string from resource file
  -------------------------------------------------------------------------*/
 BOOL GetProfileString(char* lpszSection, char* lpszEntry, char* lpszDefaultValue, char* lpszResult, int maxlen ) ;
 
 /*-------------------------------------------------------------------------
  Write integer to resource file
  -------------------------------------------------------------------------*/
 BOOL WriteProfileInt(char* lpszSection, char* lpszEntry, int nValue );  

 /*-------------------------------------------------------------------------
  Write string to resource file
  -------------------------------------------------------------------------*/
 BOOL WriteProfileString(char* lpszSection, char* lpszEntry, char* lpszValue);

/*-------------------------------------------------------------------------
  Write float to resource file
  -------------------------------------------------------------------------*/
 BOOL WriteProfileFloat(char* pszSection, char* pszEntry,float pszValue);
 
private:
  
    // The filename:
    char m_szFileName[255];

};
#endif//CFGFILE_H
