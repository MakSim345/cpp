// SMSEdit.h : main header file for the SMSEDIT application
//

#if !defined(AFX_SMSEDIT_H__602E4E1A_ED80_4B19_9D41_75466F9DB4D0__INCLUDED_)
#define AFX_SMSEDIT_H__602E4E1A_ED80_4B19_9D41_75466F9DB4D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMSEditApp:
// See SMSEdit.cpp for the implementation of this class
//

class CSMSEditApp : public CWinApp
{
public:
	CSMSEditApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMSEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMSEditApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSEDIT_H__602E4E1A_ED80_4B19_9D41_75466F9DB4D0__INCLUDED_)
