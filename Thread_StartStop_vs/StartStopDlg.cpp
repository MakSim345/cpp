// StartStopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StartStop.h"
#include "ProgressMgr.h"
#include "StartStopDlg.h"
#include ".\startstopdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartStopDlg dialog
CStartStopDlg::CStartStopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartStopDlg::IDD, pParent)
		, m_ThreadState( TS_STOPPED ) // Tracks start, pause, and resume button state
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartStopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, ID_STARTPAUSERESUME, m_btnStartPauseResume);
	DDX_Control(pDX, ID_STOP, m_btnStop);
}

BEGIN_MESSAGE_MAP(CStartStopDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_STARTPAUSERESUME, OnBnClickedStartPauseResume)
	ON_BN_CLICKED(ID_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE( WM_USER_INC_PROGRESS, OnIncProgress )
	ON_MESSAGE( WM_USER_THREAD_COMPLETED, OnThreadCompleted )
END_MESSAGE_MAP()


// CStartStopDlg message handlers
BOOL CStartStopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize the progress control
	m_ctrlProgress.SetRange32( 0, 100 );
	m_ctrlProgress.SetStep( 1 );
	m_ctrlProgress.SetPos( 0 );

	return TRUE;  
}

void CStartStopDlg::OnPaint( ) 
{
	if ( IsIconic( ) )
	{
		CPaintDC dc( this ); // device context for painting

		SendMessage( WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc( ) ), 0 );

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = ( rect.Width( ) - cxIcon + 1 ) / 2;
		int y = ( rect.Height( ) - cyIcon + 1 ) / 2;

		// Draw the icon
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CDialog::OnPaint( );
	}
}

HCURSOR CStartStopDlg::OnQueryDragIcon( )
{
	return static_cast<HCURSOR>( m_hIcon );
}

//+------------------------------------------------------
// Toggles the start, pause, resume button state
//+------------------------------------------------------
INT CStartStopDlg::ToggleSPRState( )
{
	if( TS_RESUME == m_ThreadState )
	{
		m_ThreadState = TS_START;
	}
	
	m_ThreadState++;
	
	CString sButtonText = _T("");

	switch( m_ThreadState )
	{
	case TS_START:
		sButtonText = _T("Pause");
		break;
	case TS_PAUSE:
		sButtonText = _T("Resume");
		break;
	case TS_RESUME:
		sButtonText = _T("Pause");
		break;
	default:
		ASSERT( 0 ); // We shouldn't reach this
	}
	
	// Set button text
	m_btnStartPauseResume.SetWindowText( sButtonText );
	
	return m_ThreadState;
}

//+------------------------------------------------------
// Resets the start, pause, resume button state (to start)
//+------------------------------------------------------
void CStartStopDlg::ResetSPRState( )
{
	m_ThreadState = TS_STOPPED;
	m_btnStartPauseResume.SetWindowText( _T("Start") );
	m_ctrlProgress.SetPos( 0 );
}

//+------------------------------------------------------
// Standard button message handlers
//+------------------------------------------------------

//+------------------------------------------------------
// Start, pause, and resume button handler
//+------------------------------------------------------
void CStartStopDlg::OnBnClickedStartPauseResume()
{
	m_btnStartPauseResume.EnableWindow( FALSE );
	m_btnStop.EnableWindow( FALSE );

	switch( ToggleSPRState( ) )
	{
	case TS_START:
		// Start the thread
		m_ProgressMgr.Start( GetSafeHwnd( ) );
		break;
	case TS_PAUSE:
		// Pause the thread
		m_ProgressMgr.Pause( );
		break;
	case TS_RESUME:
		// Resume the thread
		m_ProgressMgr.Resume( );
		break;
	default:
		ASSERT( 0 ); // We shouldn't reach this
	}

	m_btnStartPauseResume.EnableWindow( TRUE );
	m_btnStop.EnableWindow( TRUE );
}

//+------------------------------------------------------
// Stop button handler
//+------------------------------------------------------
void CStartStopDlg::OnBnClickedStop()
{
	m_btnStartPauseResume.EnableWindow( FALSE );
	m_btnStop.EnableWindow( FALSE );

	// Stop the thread
	m_ProgressMgr.Stop( );

	// Reset the startpause button
	ResetSPRState( );

	m_btnStartPauseResume.EnableWindow( TRUE );
	m_btnStop.EnableWindow( TRUE );
}

//+------------------------------------------------------
// Cancel button handler
//+------------------------------------------------------
void CStartStopDlg::OnBnClickedCancel()
{
	// Stop the thread
	m_ProgressMgr.Stop( );
	OnCancel();
}

//+------------------------------------------------------
// User Defined Message Handlers
//+------------------------------------------------------

//+------------------------------------------------------
// OnIncProgress handler. Receives user defined message 
// posted from the secondary thread. When we receive this
// message we increment the progress bar
//+------------------------------------------------------
LRESULT CStartStopDlg::OnIncProgress( WPARAM, LPARAM )
{
	// Increment the progress control
	m_ctrlProgress.StepIt( );
	return 1;
}

//+------------------------------------------------------
// OnThreadCompleted handler. Receives user defined message 
// posted from the secondary thread. When we receive this
// message, it means the secondary thread has completed
//+------------------------------------------------------
LRESULT CStartStopDlg::OnThreadCompleted( WPARAM, LPARAM )
{
	ResetSPRState( );
	return 1;
}