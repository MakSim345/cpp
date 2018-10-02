#ifdef USE_JOB_LIST

#define MAX_ITEMS_IN_LIST 8

//CListBox functionality
void InitShortList(void);
void SwitchShortList();
void DrawAfterShortLBIsHidden();
void HideFromToCont();
/*
CListBox class. 
Description: List box control. 'Almost' windows-style listbox 
(see Visual C, MFC, CListBox). Currently list box have always a
selection: if you for example add one item, it is automatically
selected (becouse there is of course no selection before that).
Usage: Is used like all normal listboxes. See corresponding Microsoft 
Foundation class library class (same class-name). 
*/
class CListBox
{
public:
// Constructor

  CListBox();

// Attributes  & Operations
  void Create(const RECT& rect, int nFont);
  int GetCount( ) const;

  int GetCurSel( ) const;
  int SetCurSel( int nSelect );
  int GetFirstVisibleIndex( ) const;
  void SetFirstVisibleIndex( int nIndex );
  
  int AddString(IFmsg_st uMsg);
  int DeleteString( int nIndex );
  int GetText( int nIndex, char* cBuffer ) const;
  void ScrollCurSel(int nScroll);
  void SetWindowPos(const RECT& rect);
  void SetFont(int nFont);

  void Show();
  void Hide();
  bool IsVisible() { return (m_nShow != 0); }

  int HandleMsg(unsigned char c);
// functions
  void ScrollPage();
  int GetTableValue( ) const;
  int SetTableValue( int nTableValue );
  int GetLBItem (int nStrNumber);

  void SetTimeLimit(int tindex, int tvalue)
      { timeLimit[tindex] = tvalue; }
  int GetTimeLimit(int tindex)
      { return timeLimit[tindex]; }
  void SetTimeColor(int cindex, int cvalue)
      { timeColor[cindex] = cvalue; }
  int GetTimeColor(int cindex)
      { return timeColor[cindex]; }

  int GetLimitColor(int lindex);

// Implementation
public:
  ~CListBox();

protected:
  void Draw();
  void DrawScrollBar();
  bool IndexOk(int nInd) const;
  int  GetLastVisibleIndex();
  int  GetMaxItemsInList();  
  char* ParseIFStr(const char*, int);
  vector<string> m_vItem;
  //vector<IFmsg_st> m_vItem;
  //vector<msg_st> m_vItem;
  
  char m_cParsedStr[20];
  RECT m_rect;
  int m_nSelBgColor;
  int m_nBgColor;
  int m_nBlueColor;
  int m_nScrlBgColor;//(C_MIDDLEGREY);
  int m_nScrlWidth;
  int m_nItemHeight;
  int m_nFont;
  int m_nShow;  // does list box visible (1) or not (0)
  int m_nTable; // does list box looks like a DB table (1) or not (0)
  int m_nCurPage; // current page
  wnd_t* WnAddr; // window
  // state of items
  int m_nCurSel; // -1 -> no selection
  int m_nFirstVisIndex;
  // scroll bar
  bool IsScrollBarNeeded();
  int timeLimit[5];
  int timeColor[5];
 
};

#endif // USE_JOB_LIST