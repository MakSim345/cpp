// NumPrime.cpp: implementation of the NumPrime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <process.h>
#include "math.h"
#include "thread03.h"

#include "NumPrime.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern int cyChar;

void Thread2 (PVOID pvoid)
{
	int iNum=1, iLine=0;	
	char szBuffer[16];
	int i, iSqrt;
	HDC hdc;
	PPARAMS pparams;

	pparams = (PPARAMS) pvoid;

	while (!pparams->bKill)
	{
  	do {
			if(++iNum < 0)
				iNum = 0;

			iSqrt = 1; //(int)sqrt(iNum);
			for (i = 2; i<=iSqrt; i++)
				{
				 if (iNum % i == 0)
					break;
				}
			} while (i<=iSqrt);
            Sleep (100);
			iLine = CheckBottom(pparams->hWnd, pparams->cyClient, pparams->cyChar, iLine);
			wsprintf(szBuffer, "%d", iNum++);
			hdc = GetDC(pparams->hWnd);
			TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
			ReleaseDC(pparams->hWnd, hdc);
			iLine++;

	}
	_endthread();

}

LRESULT APIENTRY WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  static PARAMS params;

	switch (message) 
	{	
	  case WM_CREATE:
		 params.hWnd = hWnd;
		 params.cyChar = HIWORD(GetDialogBaseUnits());
		 _beginthread(Thread2, 0, &params);
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


