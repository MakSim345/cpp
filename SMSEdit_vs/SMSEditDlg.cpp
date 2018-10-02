// SMSEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gen.h"
#include "RegIf.h"
#include "SMSEdit.h"
#include "SMSEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


RegIf Reg;
/////////////////////////////////////////////////////////////////////////////
// CSMSEditDlg dialog

CSMSEditDlg::CSMSEditDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSMSEditDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CSMSEditDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    trace = new CTRACE(1,0, "SMS-Edit.log");
    //trace = CTRACE(1, 0, "SMS-Edit.log");
}

CSMSEditDlg::~CSMSEditDlg()
{  
    delete trace;
}

void CSMSEditDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSMSEditDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSMSEditDlg, CDialog)
    //{{AFX_MSG_MAP(CSMSEditDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)    
    ON_BN_CLICKED(IDCopyToBuffer, OnCopyToBuffer)
    ON_BN_CLICKED(IDCLEARTEXT, OnCleartext)
    ON_BN_CLICKED(IDOK, OnExitPress)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMSEditDlg message handlers

BOOL CSMSEditDlg::OnInitDialog()
{
    CString str;
    TCHAR szSubkey[256];
    int nRegMaxLimit = MAX_LIMIT;

    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
       
    //CButton* m_pButton;
  //m_pButton = (CButton*)this->GetDlgItem(IDC_LimitBox);
    //m_pButton->SetWindowText("TEST"); 
     
    str.Format("Ver: %s. Compiled: %s %s", VERSION, __DATE__, __TIME__);
    SetDlgItemText(IDC_VERSION_INFO, str);
    // TODO: Add extra initialization here

    // Read Registry and set necessary settingse from there:
    lstrcpy (szSubkey, "Software\\SMSEdit\\Settings");    
    
    Reg.ReadIniDword(&nRegMaxLimit, szSubkey, "MaxLimit");
    //Reg.ReadIniDword(&nRegComSpeed, szSubkey, "ComSpeed");    
    
    SetDlgItemInt(IDC_LimitBox, nRegMaxLimit);
    SetDlgItemInt(IDC_CounterBox, 0);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMSEditDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HCURSOR CSMSEditDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CSMSEditDlg::OnChangeEdit1() 
{
    
    int nMaxVal = 0;    
    int nStrCtr = 0;
    CString str;
  
    GetDlgItemText(IDC_EDIT1, str);

    nStrCtr = str.GetLength();

    SetDlgItemInt(IDC_CounterBox, nStrCtr);

    nMaxVal = GetDlgItemInt(IDC_LimitBox, NULL, 1);    

    if (nMaxVal < nStrCtr)
        // Beep();
        MessageBeep(2);

    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    
    // TODO: Add your control notification handler code here
    
}
 

void CSMSEditDlg::OnCopyToBuffer() 
{
    // TODO: Add your control notification handler code here
    //HGLOBAL hData;
    //LPVOID pData;
                
    CString str;
    char * buffer;

    GetDlgItemText(IDC_EDIT1, str);
      
  if(OpenClipboard())
    {
     HGLOBAL clipbuffer;     
     EmptyClipboard();
     clipbuffer = GlobalAlloc(GMEM_DDESHARE, str.GetLength()+1);
     buffer = (char*)GlobalLock(clipbuffer);
     strcpy(buffer, LPCSTR(str));
     GlobalUnlock(clipbuffer);
     SetClipboardData(CF_TEXT,clipbuffer);
     CloseClipboard();
    }
 
    // also copy text to a log file:
    trace->TIMESTAMP(0); 
    trace->TRACEY("["); 
    trace->TRACEY(buffer, "]\n"); 
    /*
    trace.TIMESTAMP(0); 
    trace.TRACEY("["); 
    trace.TRACEY(buffer, "]\n"); 
    */

}

void CSMSEditDlg::OnCleartext() 
{
    SetDlgItemText(IDC_EDIT1, "");
    SetDlgItemInt(IDC_CounterBox, 0);
}

void CSMSEditDlg::OnExitPress() 
{
    TCHAR szSubkey[256];
    int nRegMaxLimit=1;
        
//**************************Registry*******
    // Write settings to the Registry:
    lstrcpy (szSubkey, "Software\\SMSEdit\\Settings");

    nRegMaxLimit = GetDlgItemInt(IDC_LimitBox, NULL, 1);
    //= m_pComBoxPortNum->GetCurSel();
                
    Reg.WriteIniDword(&nRegMaxLimit, szSubkey, "MaxLimit");    
//*****************************************    
    CDialog::OnOK();
}
