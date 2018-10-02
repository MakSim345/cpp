// NumSequence.cpp: implementation of the NumSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thread03.h"
#include <process.h>
#include "NumSequence.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern int cyChar;
void Thread1 (PVOID pvoid)
{
	static int iNum, iLine;
	static short cyClient;
	char szBuffer[16];
	HDC hdc;
	PPARAMS pparams;
	pparams = (PPARAMS) pvoid;

	while (!pparams->bKill)
	{
        if(iNum < 0) {iNum = 0;}
        Sleep (100);
		iLine = CheckBottom(pparams->hWnd, pparams->cyClient, pparams->cyChar,  iLine);
		wsprintf(szBuffer, "%d", iNum++);
		hdc = GetDC(pparams->hWnd);
		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
		ReleaseDC(pparams->hWnd, hdc);
		iLine++;	
	}
	_endthread();

}

LRESULT APIENTRY WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  static PARAMS params;

	switch (message) 
	{	
	  case WM_CREATE:
		 params.hWnd = hWnd;
		 params.cyChar = HIWORD(GetDialogBaseUnits());
		 _beginthread(Thread1, 0, &params);
     return 0;

		case WM_SIZE:
		 params.cyClient = HIWORD(lParam); 
		 return 0;		 
		
	  case WM_DESTROY:
		 params.bKill = TRUE;
		 return 0;
	   
	}
  return DefWindowProc(hWnd, message, wParam, lParam);
}
