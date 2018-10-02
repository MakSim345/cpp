
#include <stdafx.h>

//#include "global.h" 
#include <time.h>
#include "stdio.h"
//#include <sys/stat.h>
//#include <stdlib.h>
#include "RegIf.h"


/********************************************************************
  Declaration: Constructor.
  Call: 
  Input:
  Returns:  	  
*********************************************************************/ 
RegIf::RegIf() 
{ 
 	Start(); 
}

/********************************************************************
  Declaration: Destructor
  Call: 
  Input:
  Returns:  	  
*********************************************************************/ 
RegIf::~RegIf() 
{ 
 	 
}
/********************************************************************

  Declaration:  
  Call: 
  Input:
  Returns:
  	  
*********************************************************************/ 
void RegIf::Start()
{ 
 
}

/********************************************************************

  Declaration:  
  Call: 
  Input:
  Returns:
  	  
*********************************************************************/ 
int RegIf::Get()
{
  return 1000;
}

/********************************************************************

  Declaration:  
  Call: 
  Input:
  Returns:
  	  
*********************************************************************/ 
void RegIf::Set(int nVar)
{
  
}

/********************************************************************

  Declaration:  Write data to Registry
  Call: 
  Input:
  Returns:
  	  
*********************************************************************/ 
int RegIf::WriteIniDword(int *nRegValue, TCHAR *szSubkey, TCHAR *szKey)
{	
	int nRetVal=0;
	m_dwSizeP = sizeof (*nRegValue);	
	// Open Key for write:
	RegCreateKeyEx (HKEY_CURRENT_USER, szSubkey, 0, NULL, REG_OPTION_NON_VOLATILE,
		              KEY_SET_VALUE, NULL, &hKey, NULL);
	// Write a (default) value:
	nRetVal = RegSetValueEx (hKey, szKey, 0, REG_DWORD, (PBYTE) &(*nRegValue), m_dwSizeP);
	// Close Registry to commit changes:
	RegCloseKey (hKey);
	return nRetVal;
}


/********************************************************************

  Declaration:  Read information from Registry
  Call: ReadIniDword(int *, TCHAR *, TCHAR *)
  Input: value, path, key
  Returns: 0 if ok, 1 else.
  	  
*********************************************************************/ 
int RegIf::ReadIniDword(int *nRegValue, TCHAR *szSubkey, TCHAR *szKey)
{	
  int nRetVal=1;
	m_dwSizeP = sizeof (*nRegValue);			
	// Try to open RegKey first, if it is exit:
  if (RegOpenKeyEx (HKEY_CURRENT_USER, szSubkey, 0, KEY_QUERY_VALUE, &hKey)== ERROR_SUCCESS )
  { 
		// RegKey exists, now check is there are value:
    if (RegQueryValueEx (hKey, szKey, NULL, NULL, (PBYTE)&(*nRegValue), &m_dwSizeP) == ERROR_SUCCESS)
		{
      return 0;
		}
    else
		{
			nRetVal = WriteIniDword(nRegValue, szSubkey, szKey);
		}		
	}
	else // if Key does not exist:
		{
		  nRetVal = WriteIniDword(nRegValue, szSubkey, szKey);
		}

	return nRetVal;
}
// End of the class.
