#pragma once

//+------------------------------------------------------
// Implementation for the CProgressMgr class. This class
// illustrates methods for starting, pausing, resuming, 
// and stopping a secondary thread. The class uses 
// _beginthreadex to create the thread and a event to
// signal thread to exit.
//+------------------------------------------------------
class CProgressMgr
{
public:

	// ctor
	CProgressMgr( )
		: m_hWnd( NULL )
		, m_hThread( NULL )
		, m_hShutdownEvent( ::CreateEvent( NULL, TRUE, FALSE, NULL ) )
	{
	}

	// dtor
	~CProgressMgr( )
	{
		ShutdownThread( );
		::CloseHandle( m_hShutdownEvent );
	}

protected:
	// Determines which type of user defined message to post
	enum	NotificationTypes { NOTIFY_INC_PROGRESS, NOTIFY_THREAD_COMPLETED };

// Public interface methods
public:

	//+------------------------------------------------------
	// Public method to pause a running thread
	//+------------------------------------------------------
	void Pause( )
	{
		if( NULL != m_hThread )
		{
			::SuspendThread( m_hThread );
		}
	}

	//+------------------------------------------------------
	// Public method to resume a suspended thread
	//+------------------------------------------------------
	void Resume( )
	{
		if( NULL != m_hThread )
		{
			::ResumeThread( m_hThread );
		}
	}

	//+------------------------------------------------------
	// Public method to start a worker thread
	//+------------------------------------------------------
	HRESULT Start( HWND hWnd )
	{
		HRESULT hr = S_OK;

		m_hWnd = hWnd;

		::ResetEvent( m_hShutdownEvent );

		if( SUCCEEDED( hr = ShutdownThread( ) ) )
		{
            hr = CreateThread( );
		}
		return hr;
	}
	
	//+------------------------------------------------------
	// Public method to stop a running thread
	//+------------------------------------------------------
	HRESULT Stop( )
	{
		m_hWnd = NULL;

		return ShutdownThread( );
	}

// Implementation
private:
	//+------------------------------------------------------
	// Helper method to create the secondary thread
	//+------------------------------------------------------
    HRESULT CreateThread( )
    {
        // Fire off the thread
        if( NULL == ( m_hThread = (HANDLE)_beginthreadex(
						NULL,
                        0,
                        ThreadProc,
                        static_cast<LPVOID>( this ),
                        0,
                        NULL)) )
        {
            return HRESULT_FROM_WIN32( ::GetLastError() );
        }

        return S_OK;
    }

	//+------------------------------------------------------
	// Called by the secondary thread to get the shutdown event handle	//
	//+------------------------------------------------------
	HANDLE& GetShutdownEvent( )
	{
		return m_hShutdownEvent;
	}

	//+------------------------------------------------------
	// Called by the secondary thread to post a inc progress or 
	// thread completed user defined message
	//+------------------------------------------------------
	void NotifyUI( UINT uNotificationType )
	{
		// Check if the hWnd is still valid before posting the message
		// Note: use PostMessage instead of SendMessage because PostMessage
		// performs an asynchronous post; whereas SendMessage sends synchronously
		// (sending synchronously would kind of defeat the purpose of using a
		// worker thread)
		if( ::IsWindow( m_hWnd ) )
		{
			switch( uNotificationType )
			{
			case NOTIFY_INC_PROGRESS:
				::PostMessage( m_hWnd, WM_USER_INC_PROGRESS, 0, 0 );
				break;
			case NOTIFY_THREAD_COMPLETED:
				::PostMessage( m_hWnd, WM_USER_THREAD_COMPLETED, 0, 0 );
				break;
			default:
				ASSERT( 0 );
			}
		}
	}

	//+------------------------------------------------------
	// Helper method to shut down the secondary thread.
	// Uses a shutdown event to signal the thread to exit
	//+------------------------------------------------------
	HRESULT ShutdownThread( )
	{
		HRESULT hr = S_OK;
	    
		// Close the worker thread
		if( NULL != m_hThread )
		{
			// Signal the thread to exit
			::SetEvent( m_hShutdownEvent );

			// This thread may be suspended, so resume before shutting down
			::ResumeThread( m_hThread );

			// Wait for the thread to exit. If it doesn’t shutdown
			// on its own, force it closed with Terminate thread        
			if ( WAIT_TIMEOUT == WaitForSingleObject( m_hThread, 1000 ) ) 
			{
				::TerminateThread( m_hThread, -1000 );
				hr = S_FALSE; 
			}

			// Close the handle and NULL it out 
			::CloseHandle( m_hThread );
			m_hThread = NULL;
		}

		// Reset the shutdown event
		::ResetEvent( m_hShutdownEvent );

		return hr;
	}

	//+------------------------------------------------------
	// Secondary thread procedure
	//+------------------------------------------------------
	static UINT WINAPI ThreadProc( LPVOID lpContext )
	{
		// Turn the passed in 'this' pointer back into a CProgressMgr instance
		CProgressMgr* pProgressMgr = reinterpret_cast< CProgressMgr* >( lpContext );

		
		for( UINT uCount = 0; uCount < 100; uCount++ )
		{
			if( WAIT_OBJECT_0 == WaitForSingleObject( pProgressMgr->GetShutdownEvent( ), 0 ) )
			{
				return 1;
			}

			// Send the progress message to the UI
			pProgressMgr->NotifyUI( NOTIFY_INC_PROGRESS );

			// Sample code - delay the operation a bit
			Sleep( 50 );
		}

		// Send the thread completed message to the UI
		pProgressMgr->NotifyUI( NOTIFY_THREAD_COMPLETED );

		return 0;
	}


// Private fields
private:
	HWND	m_hWnd;				// Window handle to the UI dialog (used to
								// post progress and completed messages)
	HANDLE	m_hThread;          // Secondary thread handle
    HANDLE	m_hShutdownEvent;	// Shutdown Event handle (causes thread to exit)

};
