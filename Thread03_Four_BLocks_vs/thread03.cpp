// thread03.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "thread03.h"
#include "NumSequence.h"
#include "NumPrime.h"
#include "NumFibonacci.h"
#include "NumCircles.h"

#define MAX_LOADSTRING 100
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ID_TIMER 1
#if 0
#define YEAR (datetime->tm_year % 100)
#define MONTH(datetime->tm_mon + 1)
#define MDAY (datetime->tm_mday)
#define WDAY (datetime->tm_wday)
#define HOUR (datetime->tm_hour)
#define MIN (datetime->tm_min)
#define SEC (datetime->tm_sec)
#endif
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
static char szAppName[] = "DigClock";
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//int cyChar;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.	
    HWND hwnd;
    int xStart, yStart, xClient, yClient;
    WNDCLASSEX wndclass;
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	// LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THREAD03, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_THREAD03);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	static char szAppName[] = "DigClock";
    HWND hwnd;  
  
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_THREAD03);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//(LPCSTR)IDC_THREAD03;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);  

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
	 int xStart, yStart, xClient, yClient;

   hInst = hInstance; // Store instance handle in our global variable

   SizeTheWindow(&xStart, &yStart, &xClient, &yClient);
/*   
	 hWnd = CreateWindow(szWindowClass, szAppName,
		 WS_POPUP | WS_DLGFRAME | WS_SYSMENU,
		 xStart, yStart,
		 xClient, yClient,
		 NULL, NULL, hInstance, NULL);
*/


    hWnd = CreateWindow(szWindowClass, szAppName, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   
	 if(!SetTimer(hWnd, ID_TIMER, 100, NULL))
	 {
		 MessageBox(hWnd, "Too many clocks or timers!", szAppName, MB_ICONEXCLAMATION | MB_OK);
		 return FALSE;
	 }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	WNDCLASSEX wndclass;
	int i, cxClient, cyClient;
	static int nCtr = 4;
    HINSTANCE hInstance;
	static char *szChildClass[] = {"Child1", "Child2", "Child3", "Child4"};
	static HWND hwndChild[4];
	static WNDPROC ChildProc[] = {WndProc1, WndProc2, WndProc3, WndProc4}; //, WndProc2, WndProc3, WndProc4};

	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		
	   case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case WM_TIMER :
					InvalidateRect(hWnd, NULL, FALSE);
					return 0;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
    case WM_CREATE:
			
			wndclass.cbSize = sizeof(WNDCLASSEX); 
			wndclass.style			= CS_HREDRAW | CS_VREDRAW;
			wndclass.cbClsExtra		= 0;
			wndclass.cbWndExtra		= 0;
			wndclass.hInstance		= hInstance;
			wndclass.hIcon			= NULL;
			wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
			wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			wndclass.lpszMenuName	= NULL;
			wndclass.hIconSm		= NULL;
			
			for (i = 0; i<nCtr; i++)
			{
			 wndclass.lpfnWndProc = ChildProc[i];
			 wndclass.lpszClassName = szChildClass[i];
					 
			 RegisterClassEx(&wndclass);
			 hwndChild[i] = CreateWindow(szChildClass[i], NULL, WS_CHILDWINDOW|WS_BORDER|WS_VISIBLE,
                         0, 0, 0, 0, hWnd, (HMENU) i, hInstance, NULL);			 
			 
			}
			//cyChar = HIWORD(GetDialogBaseUnits());
			//SetTimer(hWnd, 1, 10, NULL);
			
			break;
    case WM_SIZE:
      cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			for (i = 0; i<nCtr; i++)
			{
			  MoveWindow(hwndChild[i], (i % 2) * cxClient / 2, (i > 1) * cyClient / 2, cxClient / 2, cyClient / 2, TRUE);
			}			
			break;

	case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;

    case WM_TIMER:
			for (i = 0; i<nCtr; i++)
			{
				SendMessage(hwndChild[i], WM_TIMER, wParam, lParam);
			}
			break;
		case WM_CHAR:
			if (wParam == 24)
				DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

void SizeTheWindow(int *pxStart, int *pyStart, int *pxClient, int *pyClient)
{
	HDC hdc;
	TEXTMETRIC tm;
	hdc = CreateIC("DISPLAY", NULL, NULL, NULL);
	GetTextMetrics(hdc, &tm);
	DeleteDC(hdc);
	*pxClient = 2 * GetSystemMetrics(SM_CXDLGFRAME) + 16*tm.tmAveCharWidth;
	*pxStart = GetSystemMetrics(SM_CXSCREEN) - *pxClient;
	*pyClient = 2 * GetSystemMetrics(SM_CYDLGFRAME) + 2*tm.tmHeight;
	*pyStart = 0;
}

int CheckBottom(HWND hwnd, int cyClient, int cyChar, int iLine)
{
	if(iLine * cyChar + cyChar > cyClient)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		iLine = 0;
	}
	return iLine;
}
