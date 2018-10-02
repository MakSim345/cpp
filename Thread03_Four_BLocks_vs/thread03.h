
#if !defined(AFX_THREAD03_H__C7C4AA7C_778B_418C_8BD5_79651892D75F__INCLUDED_)
#define AFX_THREAD03_H__C7C4AA7C_778B_418C_8BD5_79651892D75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

void SizeTheWindow(int *pxStart, int *pyStart, int *pxClient, int *pyClient);
int CheckBottom(HWND hwnd, int cyChar, int cyClient, int iLine);


typedef struct
{
	HWND hWnd;
	int cxClient;
	int cyClient;
	int cyChar;
	BOOL bKill;

} PARAMS, *PPARAMS;
#endif // !defined(AFX_THREAD03_H__C7C4AA7C_778B_418C_8BD5_79651892D75F__INCLUDED_)
