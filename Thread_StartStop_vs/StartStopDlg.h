// StartStopDlg.h : header file
//

#pragma once
#include <windows.h>
#include "afxcmn.h"
#include "afxwin.h"


// CStartStopDlg dialog
class CStartStopDlg : public CDialog
{
// Construction
public:
	CStartStopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STARTSTOP_DIALOG };
	enum ThreadStatus { TS_STOPPED, TS_START, TS_PAUSE, TS_RESUME };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Tracks start, pause, resume state for the ID_STARTPAUSERESUME button
	INT		m_ThreadState;

	// Progress and button controls
	CProgressCtrl m_ctrlProgress;
	CButton m_btnStartPauseResume;
	CButton m_btnStop;

	// Progress manager class, handles the threading code
	CProgressMgr m_ProgressMgr;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Button handlers
	afx_msg void OnBnClickedStartPauseResume();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedCancel();

	// User defined handlers
	afx_msg LRESULT OnIncProgress( WPARAM, LPARAM );
	afx_msg LRESULT OnThreadCompleted( WPARAM, LPARAM );

	INT ToggleSPRState( );
	void ResetSPRState( );
};
