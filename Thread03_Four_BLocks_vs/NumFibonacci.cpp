// NumFibonacci.cpp: implementation of the NumFibonacci class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thread03.h"
#include <process.h>
#include "NumFibonacci.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern int cyChar;
void Thread3 (PVOID pvoid)
{
	static long iNum=0, iNext=1, iTemp, iLine;
	static short cyClient;
	char szBuffer[16];
	HDC hdc;

	PPARAMS pparams;

	pparams = (PPARAMS) pvoid;

	while (!pparams->bKill)
	{
        if(iNum < 0)
        {
            iNum = 0;
            iNext= 1;
        }
    Sleep (100);
	iLine = CheckBottom(pparams->hWnd, pparams->cyClient, pparams->cyChar, iLine);
    wsprintf(szBuffer, "%ld", iNum++);
    hdc = GetDC(pparams->hWnd);
    TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
    ReleaseDC(pparams->hWnd, hdc);
    iTemp = iNum;
    iNum =  iNext;
    iNext += iTemp;
    iLine++;
	}
	_endthread();
}

LRESULT APIENTRY WndProc3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  static PARAMS params;

	switch (message)
	{
	  case WM_CREATE:
		 params.hWnd = hWnd;
		 params.cyChar = HIWORD(GetDialogBaseUnits());
		 _beginthread(Thread3, 0, &params);
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


