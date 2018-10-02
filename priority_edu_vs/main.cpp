// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "gen.h"
#include "Windows.h"
#include <iostream>

/*
IDLE_PRIORITY_CLASS
BELOW_NORMAL_PRIORITY_CLASS
NORMAL_PRIORITY_CLASS
ABOVE_NORMAL_PRIORITY_CLASS
HIGH_PRIORITY_CLASS
REALTIME_PRIORITY_CLASS
*/

void main()
{
	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
    
    std::wstring FullPathToExe; 
    FullPathToExe = L"c:\\windows\\notepad.exe";
    if (CreateProcess(const_cast<LPCWSTR>(FullPathToExe.c_str()),
        NULL,NULL,NULL,FALSE,
        ABOVE_NORMAL_PRIORITY_CLASS,
        NULL,NULL,&cif,&pi)==TRUE)
	{
		std::cout << "process" << std::endl;
		std::cout << "handle " << pi.hProcess << std::endl;
		::SetPriorityClass(pi.hProcess, REALTIME_PRIORITY_CLASS);
        Sleep(1000);				// wait
        TerminateProcess(pi.hProcess, NO_ERROR);	// kill process
	}
}