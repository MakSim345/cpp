/****************************************************************************/
/*	Copyright (c) 2012 Vitaly Lyaschenko < scxv86@gmail.com >
/*
/*	Purpose:
/*
/****************************************************************************/

#include "Logger.h"

#ifdef LOG_MULTITHREADING

#include "sys_Mutex.h"

#include <process.h>

unsigned  __stdcall  thread_func1(void* pParam )
{
	LOG_DEBUG<<"\n\t>: Dbg msg from: thread_func_1\n";
	LOG_DEBUG_1<<"\n\t>: Dbg_Level_1 msg from: thread_func_1\n";
	Sleep(100);
	LOG_WARNING<<"\n\tSome warning from thread_1";
	Sleep(100);
	return 0;
}
unsigned  __stdcall  thread_func2(void* pParam )
{
	LOG_DEBUG<<"\n\t>: Dbg msg from: thread_func_2\n";
	LOG_DEBUG_1<<"\n\t>: Dbg_Level_1 msg from: thread_func_2\n";
	Sleep(100);
	LOG_WARNING<<"\n\tSome warning from thread_2";
	Sleep(100);
	return 0;
}
unsigned  __stdcall  thread_func3(void* pParam )
{
	LOG_DEBUG<<"\n\t>: Dbg msg from: thread_func_3\n";
	LOG_DEBUG_1<<"\n\t>: Dbg_Level_1 msg from: thread_func_3\n";
	Sleep(100);
	LOG_WARNING<<"\n\tSome warning from thread_3";
	Sleep(100);
	return 0;
}
unsigned  __stdcall  thread_func4(void* pParam )
{
	LOG_DEBUG<<"\n\t>: Dbg msg from: thread_func_4\n";
	LOG_DEBUG_1<<"\n\t>: Dbg_Level_1 msg from: thread_func_4\n";
	Sleep(100);
	LOG_WARNING<<"\n\tSome warning from thread_4";
	Sleep(100);
	return 0;
}
unsigned  __stdcall  thread_func5(void* pParam )
{
	LOG_DEBUG<<"\n\t>: Dbg msg from: thread_func_5\n";
	LOG_DEBUG_1<<"\n\t>: Dbg_Level_1 msg from: thread_func_5\n";
	Sleep(100);
	LOG_WARNING<<"\n\tSome warning from thread_5";
	Sleep(100);
	return 0;
}

#endif

int main(int argc, char* argv[])
{
	// set logging level (as default DEBUG3)
	Log::ReportingLevel() = Log::LevelFromString(argv[1] ? argv[1] : "DEBUG3");

	// init the log file
	LOG_FILE_INIT( "MyLog.log" );

	LOG_IS_OUTPUT_TIME( true );

	LOG_INFO << "Initialize the log file!";

	LOG_IS_OUTPUT_TIME( false );
	
	// messages are output in the console (stderr)
	LOG_USE_STDERR;

#ifndef LOG_MULTITHREADING

	int _l[] = { 4, 8, 15, 16, 23, 42 };

	LOG_INFO << "\n\tMessage: "<<_l[0]<<_l[1]<<_l[2]<<_l[3]<<_l[4]<<_l[5]<<" end.\n";

	// messages are output in the log file
	LOG_USE_FILE;

	LOG_ERROR << "some error msg";

	// again output in the console
	LOG_USE_STDERR;

	LOG_DEBUG << "Message out in the console...";

	const int count = 7;

	LOG_DEBUG_1 << "\ncount = " << count;

	for (int i = 0; i != count; ++i)
	{
		LOG_DEBUG_2 << "the counter 'i' = " << i;

		static int val = 9;

		LOG_DEBUG_2 << "val = " << val;

		val += i;

		LOG_DEBUG_3 << "(val += i) = " << val;
	}

#else

	const int n_threads = 5;
	
	HANDLE threads[n_threads];

	// initialize
	for ( int i = 0; i != n_threads; ++i ) {
		threads[i] = INVALID_HANDLE_VALUE;
	}

	// create five threads
	threads[0] = (HANDLE) _beginthreadex( NULL, 0, &thread_func1, nullptr, 0, nullptr );
	threads[1] = (HANDLE) _beginthreadex( NULL, 0, &thread_func2, nullptr, 0, nullptr );
	threads[2] = (HANDLE) _beginthreadex( NULL, 0, &thread_func3, nullptr, 0, nullptr );
	threads[3] = (HANDLE) _beginthreadex( NULL, 0, &thread_func4, nullptr, 0, nullptr );
	threads[4] = (HANDLE) _beginthreadex( NULL, 0, &thread_func5, nullptr, 0, nullptr );

	WaitForMultipleObjects( n_threads, &threads[0], TRUE, INFINITE );

#endif

	getchar();

	return 0;
}
