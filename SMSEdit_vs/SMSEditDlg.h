// SMSEditDlg.h : header file
//

#if !defined(AFX_SMSEDITDLG_H__EA44B8C7_93AB_4C0C_82A4_B5A74615EA2A__INCLUDED_)
#define AFX_SMSEDITDLG_H__EA44B8C7_93AB_4C0C_82A4_B5A74615EA2A__INCLUDED_


#include "LogServ.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_LIMIT 139
/////////////////////////////////////////////////////////////////////////////
// CSMSEditDlg dialog

class CSMSEditDlg : public CDialog
{
// Construction
public:
    CSMSEditDlg(CWnd* pParent = NULL);    // standard constructor
    ~CSMSEditDlg();    // destructor
// Dialog Data
    //{{AFX_DATA(CSMSEditDlg)
    enum { IDD = IDD_SMSEDIT_DIALOG };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSMSEditDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    CTRACE *trace;
    // CTRACE trace;

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CSMSEditDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnChangeEdit1();
    afx_msg void OnSelchangeList1();
    afx_msg void OnCopyToBuffer();
    afx_msg void OnCleartext();
    afx_msg void OnExitPress();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSEDITDLG_H__EA44B8C7_93AB_4C0C_82A4_B5A74615EA2A__INCLUDED_)
