// NumCircles.cpp: implementation of the NumCircles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include "thread03.h"
#include "NumCircles.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// extern int cyChar;

void Thread4 (PVOID pvoid)
{
	static int iNum;
	int  iDiameter;
	short cyClient, cxClient;
	char szBuffer[16];
	HDC hdc;

	PPARAMS pparams;

	pparams = (PPARAMS) pvoid;

	while (!pparams->bKill)
	{    
		InvalidateRect(pparams->hWnd, NULL, TRUE);
		UpdateWindow(pparams->hWnd);
		//Sleep (100);
		iDiameter = rand() % (max(1, min(pparams->cxClient, pparams->cyClient)));
 		hdc = GetDC(pparams->hWnd);
		Ellipse(hdc, (pparams->cxClient - iDiameter)/2,
			         (pparams->cyClient - iDiameter)/2,
                     (pparams->cxClient + iDiameter)/2,
                     (pparams->cyClient + iDiameter)/2);
		
		ReleaseDC(pparams->hWnd, hdc);
	}
	_endthread();

}

LRESULT APIENTRY WndProc4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  static PARAMS params;

	switch (message) 
	{	
	  case WM_CREATE:
		 params.hWnd = hWnd;
		 params.cyChar = HIWORD(GetDialogBaseUnits());
		 _beginthread(Thread4, 0, &params);
     return 0;

		case WM_SIZE:
		 params.cyClient = HIWORD(lParam); 
		 params.cxClient = LOWORD(lParam); 		 
		 return 0;		 
		
	  case WM_DESTROY:
		 params.bKill = TRUE;
		 return 0;
	   
	}
  return DefWindowProc(hWnd, message, wParam, lParam);
}

