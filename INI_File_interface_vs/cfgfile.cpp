///////////////////////////////////////////////////////////////////
//                 cfgfile.cpp
//
// This is a simple API wrap class used for ini file access.
// The purpose of this class is to make ini file access more
// convenient than direct API calls.
//
#include "cfgfile.h"
#include <iostream>
#include <Windows.h>

CFGFile::CFGFile()    
{
    char szFileName[255];

    memset(m_szFileName, 0x00, 255);
    sprintf(szFileName, ".\\default.ini");
    memcpy(m_szFileName, szFileName, strlen(szFileName));
}

CFGFile::CFGFile(char* szFileName)
{
    memset(m_szFileName, 0x00, 255);
    memcpy(m_szFileName, szFileName, strlen(szFileName));
}

BOOL CFGFile::GetProfileInt(char* lpszSection, char* lpszEntry, int nDefaultValue, int * lpnResult)
{  
    int RealDefaultValue;

    nDefaultValue=9999999;
    RealDefaultValue=nDefaultValue;

    *lpnResult = GetPrivateProfileInt(lpszSection,  lpszEntry, nDefaultValue, m_szFileName); 
  
    if (*lpnResult == 9999999)
    {
        *lpnResult = RealDefaultValue;
        return(FALSE);
    }
    else
    {
        return TRUE;
  } 
    
}

BOOL CFGFile::GetProfileDouble(char* pszSection, char* pszEntry, double fltDefaultValue, double* pnResult) 

{
    char szResult[255];
    char szDefault[255];
    float fltResult;

    sprintf(szDefault, "%f",fltDefaultValue);
    GetPrivateProfileString(pszSection,  pszEntry, szDefault, szResult, 255, m_szFileName); 
    fltResult =  atof(szResult);
 
    return TRUE;
}


BOOL CFGFile::GetProfileInts(char* lpszSection, char* lpszEntry, int number, int* pnDefaultValue, int * lpnResult)
{
    char str[200];
    int index = 0;
    char* cNumber = NULL;
    int nNumber;
    char* szResult = new char[255];
    
    memset(szResult, 0x00, 255);
    GetPrivateProfileString(lpszSection, lpszEntry, "", szResult, 255, m_szFileName);
    strcpy(str, szResult);
    
    if (strlen(str) < 1)
    {
        for (index=0; index<number; index++)
        {
            *lpnResult = *pnDefaultValue;
            lpnResult++;
            pnDefaultValue++;
        }
    return FALSE;
    }
    else
    {            
        index = 0;
        cNumber    = strtok(str," ");      
        while ( (cNumber != NULL) && (index < number) ) 
        {
            nNumber = atoi(cNumber);
            lpnResult[index] = nNumber;
            index++;
            cNumber    = strtok(NULL, " ");
        }
    }
    return TRUE;
}

BOOL CFGFile::GetProfileString(char* lpszSection, char* lpszEntry, char* lpszDefaultValue, char* lpszResult, int maxlen) 
{
    // char* szResult = new char[255];
    char szResult[255];
    memset(szResult, 0x00, 255);

    GetPrivateProfileString(lpszSection,  lpszEntry, lpszDefaultValue, szResult, 255, m_szFileName); 

    if ( (szResult[0]=='N') && (szResult[1] == 'a') && (szResult[2]=='N'))
    {
        strcpy(lpszResult, lpszDefaultValue);
        return FALSE;
    }
    else
    {
        strcpy(lpszResult, szResult);
        return TRUE;
    }
}

BOOL CFGFile::WriteProfileInt(char* lpszSection, char* lpszEntry, int nValue )
{
     char szValue[255];
    sprintf(szValue, "%d", nValue);
    WritePrivateProfileString(lpszSection,  lpszEntry, szValue, m_szFileName);
    return TRUE;
}

BOOL CFGFile::WriteProfileString(char* lpszSection, char* lpszEntry, char* lpszValue )
{
    WritePrivateProfileString(lpszSection,  lpszEntry, lpszValue, m_szFileName);
    return TRUE;
}


BOOL CFGFile::WriteProfileFloat(char* pszSection, char* pszEntry,float pszValue )
{
    char szValue[255];
    sprintf(szValue, "%f", pszValue);
    WritePrivateProfileString(pszSection,  pszEntry, szValue, m_szFileName); 
    return TRUE;
}

