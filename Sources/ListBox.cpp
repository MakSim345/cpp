#ifdef USE_JOB_LIST
/********************************************************************
** CListBox */

/********************************************************************
** CListBox construction & destruction */

CListBox::CListBox()
{
  m_nCurPage          = 1;
  m_nCurSel           = -1;
  m_nFirstVisIndex    = -1;
  m_nShow             = 0;
}

CListBox::~CListBox()
{
  // If graphics is initialized, then DeleteWindow removes the 
  // picture; else it just deletes the structure.
  DeleteWindow(WnAddr);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Creates the listbox-control.
  Call: Create
  Input: rect: Specifies the list box size and position.
         nFont: The font to be used in list box.
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::Create(const RECT& rect, int nFont)
{
  SetWindowPos(rect);
  // at the moment these can be not set by user
  m_nSelBgColor  = Color(C_BLACK);
  m_nBgColor     = Color(C_WHITE);
  m_nBlueColor   = Color(C_SKYBLUE);
  m_nScrlBgColor = makecol(219,219,219);//(C_MIDDLEGREY);
  m_nTable = true; // by default
  m_nScrlWidth = 30; // width of a scrollbar (if is in use)

  SetFont(nFont);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Sets the font.
  Call: SetFont
  Input: nFont: font to set; dirrerent fonts defined in GrafDat.h
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::SetFont(int nFont)
{
  m_nFont = nFont;
  // 4 = offset
  m_nItemHeight = text_height((FONT*) g_pData[m_nFont].dat) + 2;
  if( IsVisible() )
    Draw();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Shows the list box
  Call: Show
  Input: 
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::Show()
{
  m_nShow = 1;
  Draw();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Hides (clear the list box-picture) the list box
  Call: Hide
  Input: 
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::Hide()
{
  m_nShow = 0;
  ClearMemBm(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Specifies whether given index is valid item-index for 
    the listbox.
  Call: IndexOk
  Input: nInd: index to check
  Returns: Nonzero if index is valid; otherwise 0.
  20.03.2002 Initial coding  YS

*********************************************************************/

bool CListBox::IndexOk(int nInd) const
{ 
  return ( (nInd >= 0 && nInd < (int)m_vItem.size()) ? true : false ); 
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration:  
  Call: GetCount
  Input: 
  Returns: The number of items in the list box. 
  20.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetCount() const
{
  return m_vItem.size();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Retrieves the zero-based index of the currently 
    selected item, if any.
  Call: 
  Input: 
  Returns: The zero-based index of the currently selected item.
  20.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetCurSel( ) const
{
  return m_nCurSel;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Selects a string and scrolls it into view, if 
    necessary. When the new string is selected, the list box removes
    the highlight from the previously selected string.
  Call: SetCurSel
  Input: nSelect: Specifies the zero-based index of the string to be 
    selected. Currently selection cannot be taken off; there is
    always one selection.
  Returns: -1, if error, otherwise 1
  20.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::SetCurSel( int nSelect )
{
  if( !IndexOk(nSelect) )
    return -1;

  int nLastInd = GetLastVisibleIndex();
  m_nCurSel = nSelect;

  if( m_nCurSel < m_nFirstVisIndex )
    SetFirstVisibleIndex(m_nCurSel); // scroll down
  else if( m_nCurSel > nLastInd )
  {
    // scroll up
    SetFirstVisibleIndex(m_nFirstVisIndex+(m_nCurSel-nLastInd));
  }
  if( IsVisible() )
    Draw();
  return 1;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Call this member function to add a string to a 
    list box.
  Call: AddString
  Input: Item: Points to the null-terminated string that is to 
    be added.
  Returns: The zero-based index to the string in the list box.
  20.03.2002 Initial coding  YS

*********************************************************************/
/*
int CListBox::AddString(const char* Item )
{
  // If it is the first item, then it will be visible in list,
  // and it is selected
//TRACE ("Inside AddString:: Item = %s, size=%d\n", Item, (int)m_vItem.size());

  if( m_vItem.size() <= 0 )
  {
    m_nFirstVisIndex = 0;
    m_nCurSel = 0;
  }
//TRACE ("Inside AddString:: Before calling push_back(Item)\n");
  //PushBack(Item);
  m_vItem.push_back(string(Item));
//TRACE ("Inside AddString:: After calling push_back(Item)\n");

  if( IsVisible() ) 
    {
//TRACE ("Inside AddString:: IsVisible==TRUE, calling Draw()\n");
    Draw();
//TRACE ("Inside AddString:: After calling Draw()\n");
    }
  else 
    {
//TRACE ("Inside AddString:: IsVisible==FALSE, Draw didn't call. Return.\n");    
    }
  return (m_vItem.size() - 1);
}
*/
/********************************************************************

  Savcor IT Oy/YS
  Declaration: Call this member function to add a string to a 
               list box. (Overloaded)
               Function push an IFmsg_st structure to the vector  
  Call: AddString
  Input: message in a IFmsg_st structure that is to be added.
  Returns: The zero-based index to the string in the list box.
  03.05.2002 Initial coding  YS

*********************************************************************/

int CListBox::AddString(IFmsg_st uMsg)
{
 
  char Item[70];

 if( m_vItem.size() <= 0 )
  {
    m_nFirstVisIndex = 0;
    m_nCurSel = 0; 
  }

  strcpy(Item, uMsg.jobId);
  strcat (Item, "#");
 
  strcat(Item,  uMsg.from);
  strcat (Item, "#");
 
  strcat(Item, uMsg.to);
  strcat (Item, "#");
    
  strcat(Item, uMsg.contId);
 
  m_vItem.push_back(Item);    
  
 if( IsVisible() )
    {
     Draw();   
     }
   
  return (m_vItem.size() - 1);
}

/********************************************************************
 
  03.05.2002 Initial coding  YS

*********************************************************************/
/*
int CListBox::AddString(IFmsg_st uMsg)
{
  //char Item[85];  
  //char *Item;  
  //int nLen=0;
  int i;
  //msg_st *uBufMsg;

  // If it is the first item, then it will be visible in list,   
  if( m_vItem.size() <= 0 )
  {
    m_nFirstVisIndex = 0;
    m_nCurSel = 0; 
  }
//
  strcpy(Item, uMsg->jobId);
  nLen = strlen(Item);
  for (i=nLen+1; i<=9; i++)
     strcat (Item, "-");

  strcat(Item,  uMsg->from);
  nLen = strlen(Item);
  for (i=nLen+1; i<=21; i++)
     strcat (Item, "-");

  strcat(Item, uMsg->to);
  nLen = strlen(Item);
  for (i=nLen+1; i<=32; i++)
     strcat (Item, "-");
    
  strcat(Item, uMsg->contId);
 ///  
      
    m_vItem.push_back(uMsg);
   
     
 //i=((int)m_vItem.size() - 1);
 
 if( IsVisible() )
    Draw();
  // return i;
  return (m_vItem.size() - 1);
}
*/
/********************************************************************

  Savcor IT Oy/YS
  Declaration: 
  Call: GetMaxItemsInList
  Input: 
  Returns: Returns the maximum number of items that can be seen 
    *completely* in the list.
  21.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetMaxItemsInList()
{
  int ReturnValue;
  
  if (!m_nTable)
    {
     ReturnValue = (m_rect.bottom - m_rect.top) / m_nItemHeight;
    }
  else
    {    
     ReturnValue = MAX_ITEMS_IN_LIST;
    }
  return ReturnValue;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Deletes an item(s) in a list box.
  Call: DeleteString 
  Input: nIndex: Specifies the zero-based index of the string to 
    be deleted. If nIndex < 0, all items of the list are deleted.
  Returns: A count of the strings remaining in the list. 
  20.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::DeleteString( int nIndex )
{
  int nMaxItemsInList = 0;

  if( nIndex >= (int)m_vItem.size() )
    return -1; // error index

  // Check the case when we delete the only visible 
  // item from the list.
  if( GetLastVisibleIndex() == m_nFirstVisIndex )
  {
    nMaxItemsInList = GetMaxItemsInList();
    if( m_vItem.size() <= 0 )
      m_nFirstVisIndex = -1;
    else
    {
      // Scroll one page down.
      // First check, if there is only one page left.
      if((int)m_vItem.size() <= nMaxItemsInList )
        m_nFirstVisIndex = 0;
      else
        m_nFirstVisIndex = m_vItem.size()-nMaxItemsInList-1;
    }
  }
  
  if( nIndex < 0 ) // delete all
    m_vItem.erase(m_vItem.begin(), m_vItem.end());
  else
    m_vItem.erase(m_vItem.begin() + nIndex);

  if( m_vItem.size() <= 0 )
  {
    m_nFirstVisIndex = -1;
    m_nCurSel = -1;
  }
  else
  {
    // Property: always one item is selected
    // if the last item is deleted, then the current last item
    // must be selected, otherwise the cur. sel. stays the same.
    if( m_nCurSel >= (int)m_vItem.size() )
      m_nCurSel = m_vItem.size() - 1;
  }

  if( IsVisible() )
    Draw();

  return (m_vItem.size() - 1);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Gets a string from a list box.
  Call: GetText
  Input:  nIndex: Specifies the zero-based index of the string to 
    be retrieved.
          cBuffer: Points to the buffer that receives the string. 
    The buffer must have sufficient space for the string and a 
    terminating null character.
  Returns: The length of the string, excluding the terminating 
    null character. 
  20.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetText( int nIndex, char* cBuffer ) const
{
  if( !IndexOk(nIndex) )
    return -1; // index error
  //strcpy(cBuffer, m_vItem[nIndex].c_str());
  // later change it
  return 1;//m_vItem[nIndex].size();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: 
  Call: GetFirstVisibleIndex
  Input: 
  Returns: The index of the first visible item in the list-window.
  21.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetFirstVisibleIndex() const
{
  return m_nFirstVisIndex;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Sets the given index to be the first in the visible
    list.
  Call: SetFirstVisibleIndex
  Input: nIndex: index of the item to be shown first in the list 
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::SetFirstVisibleIndex( int nIndex )
{
  if( m_vItem.size() <= 0 )
    return;

  m_nFirstVisIndex = nIndex;
  if( m_nFirstVisIndex < 0 )
    m_nFirstVisIndex = 0;
  else if( m_nFirstVisIndex >= (int)m_vItem.size() )
    m_nFirstVisIndex = m_vItem.size() - 1;
  if( IsVisible() )
    Draw();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Scrolls the current selection from the current 
    position whether up or down.
    NOTE: currently there is no up-down scrolling in the table 
          mode (m_nTable=true), just PgDown.
  Call: ScrollCurSel
  Input: nScroll: indicates how many steps to scroll up or down; 
    positive value means that go to end of list.
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::ScrollCurSel(int nScroll)
{
  if( m_nCurSel >= 0 && (!m_nTable) )
     SetCurSel(m_nCurSel + nScroll);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Sets the list box size and position.
  Call: SetWindowPos
  Input: rect: new size to be set
  Returns: 
  21.03.2002 Initial coding  YS

*********************************************************************/

void CListBox::SetWindowPos(const RECT& rect)
{
  m_rect.left   = rect.left;
  m_rect.right  = rect.right;
  m_rect.top    = rect.top;
  m_rect.bottom = rect.bottom;
  if( IsVisible() )
    Draw();
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: 
  Call: GetLastVisibleIndex
  Input: 
  Returns: The index of the last completely visible index in the list
    box.
  21.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetLastVisibleIndex()
{
  int nMaxItemsInList = 0;

  nMaxItemsInList = GetMaxItemsInList();
  return MIN(m_nFirstVisIndex+nMaxItemsInList-1, (int)m_vItem.size()-1);
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Handles input messages for the list box. Currently
    hendles only the keyboard messages = characters.
  Call: HandleMsg
  Input: c: character to be handled in listbox
  Returns: Nonzero if message was handled; otherwise 0.
  21.03.2002 Initial coding  YS

*********************************************************************/

int CListBox::HandleMsg(unsigned char c)
{
  int bHandled = -1;

  if( !IsVisible() || (m_vItem.size()<=0))// if unvisible or empty list.
    {  
     return bHandled;
    }
  switch(c)
  {   
  case '4':
    bHandled = GetLBItem(1);
    break;
  case '5':
    bHandled = GetLBItem(2);
    break;
  case '6':
    bHandled = GetLBItem(3);
    break;
  case '7':
    bHandled = GetLBItem(4);
    break;
  case '8':
    bHandled = GetLBItem(5);
    break;
  case '9':
    bHandled = GetLBItem(6);
    break;
  case 'a':
    bHandled = GetLBItem(7);
    break;
  case 'b':
    bHandled = GetLBItem(8);
    break;
  /*case 'q'://Debug versio
    SetTableValue(!m_nTable);
    Draw();  
  */
  case 'd':// Page down, F6
   // ScrollPage();
    bHandled = -1;
  } 
  if ((int)m_vItem.size() <= bHandled)
    {
    //if unexisted item has been choosen:
     bHandled = -1;
    }  
  return bHandled;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Draw a curent view of the ListBox control
  Call: Draw
  Input: void  
  Returns:  void
  20.03.2002 Initial coding  YS

*********************************************************************/
int CListBox::GetLimitColor(int lindex)
{
  int Loopperi;
  int ret = Color(C_WHITE);
  
  for (Loopperi=0; Loopperi < 5; Loopperi++)
  {	 
		 // TRACE("Time for %d is %d, limit %d\n",
		//	  lindex,JobList[lindex].jobAge,timeLimit[Loopperi]);
          if (JobList[lindex].jobAge >= timeLimit[Loopperi])
          {
			 // TRACE("Timelimit found\n");
              ret = timeColor[Loopperi];
              break;
          }      
  }  
  return ret;
}

void CListBox::Draw()
{
	int nCol, ycol, y2;
	int TextHeight;
	int xpos,ypos;
	int xrel;
	int rows;
	FONT *pFont; 
	const int TEXT_LINE_OFFSET = 0;
  int nMPos;
	int nBorderThickness;   
  int nHeaderYPos;
  BOOL bIsScrollBarNeeded;
  int nNulOffset = 3;
  int nFirOffset = 70;
  int nSecOffset = 170;
  int nThiOffset = 340;
  int nFouOffset = 510;
  char ItemNum[3];
  
  if( m_vItem.size() <= 0 || m_nFirstVisIndex < 0 )
    nMPos = 0;
  else
    nMPos= GetLastVisibleIndex() - m_nFirstVisIndex + 1;
 
  rows = nMPos;
  ycol = 1;

  //drawing listbox headers:
  nHeaderYPos = m_rect.top-m_nItemHeight;
  WriteTextToScreen("Job:" ,FromLSetup[0] +nFirOffset,  nHeaderYPos, ARIALBD,LEFT, FromLSetup[2]);
  WriteTextToScreen("From:",FromLSetup[0] +170, nHeaderYPos, ARIALBD,LEFT, FromLSetup[2]);
  WriteTextToScreen("To:"  ,FromLSetup[0] +340, nHeaderYPos, ARIALBD,LEFT, FromLSetup[2]);
  WriteTextToScreen("Container ID:",FromLSetup[0]+ 510,nHeaderYPos, ARIALBD,LEFT, FromLSetup[2]);   
 
    //draw a window on the define position:  
    WnAddr = CreateWindow( m_rect.left, m_rect.top, (m_rect.right - m_rect.left), 
	                   (m_rect.bottom - m_rect.top), 2, m_nBgColor, 
                     makecol(192,192,192), makecol(128,128,128), 2, 0);   
    
    
   // save current vp-values
  RECT reOldVP(g_view_port_left, g_view_port_top, g_view_port_right, g_view_port_bottom);
  int nOldVPClip = g_view_port_clip;
  
  setviewport(m_rect.left+2, m_rect.top+2, m_rect.right-2, m_rect.bottom-2, 1);
   
   pFont = (FONT*) g_pData[m_nFont].dat;
   xrel=WnAddr->thickness+5;

   TextHeight = m_nItemHeight;//text_height(pFont);
   
//Main loop
for (nCol=0; nCol<nMPos; nCol++)
 {
     // calculate xpos:  
      xpos=WnAddr->lxpos+xrel;
     if(WnAddr->bordertype == 0)
       nBorderThickness = 0;
     else if(WnAddr->bordertype == 3)
       nBorderThickness = WnAddr->thickness; // 1 border
     else
       nBorderThickness = WnAddr->thickness*2; // 2 borders
 
     ycol = 1 + nCol;
    
     // calculate ypos:
     ypos = WnAddr->lypos + WnAddr->thickness + 
      (ycol-1)*TextHeight + (ycol-1)*TEXT_LINE_OFFSET;
     //**************************************************

    text_mode(-1); // transparent
if (!m_nTable)
{  
//***************************************************************************
//* This part represent a ListBox like a usual list (black letters on white *
//* background), and obviously do not usin in RTG mode.                     *
//***************************************************************************

 /* 
   bIsScrollBarNeeded = IsScrollBarNeeded();
	 if (m_nFirstVisIndex + nCol == m_nCurSel)// selected row:
	  {
	  	// Drawing the selected row: black rectangle
	  	y2 = ypos + TextHeight;       
      if (!IsScrollBarNeeded())
        {
		      // (m_rect.right - m_rect.left): wight of the control;		
          rectfill(g_pMemBitmap, m_rect.left+2, y2, m_rect.right-2, ypos, m_nSelBgColor);          
		      //put the white text to the window:
          textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), 
                xpos, ypos, m_nBgColor);
          InvalidateRect(m_rect.left+2, y2, m_rect.right-2, ypos);       
        }
      else //m_bScrlBarVisible=true
        {                
         // draw	filledRect shorter
          rectfill(g_pMemBitmap, m_rect.left+2, y2, (m_rect.right-3) - m_nScrlWidth, ypos, m_nSelBgColor);          
		      //put the white text to the window
          textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), 
                xpos, ypos, m_nBgColor);       
          InvalidateRect(m_rect.left+2, y2, (m_rect.right-2), ypos); 
          DrawScrollBar();
        }     
  	}
   else //non-selected row:
	  {     
       if (!IsScrollBarNeeded())
        {		       
		       // put the black color text to the window
           textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), 
                     xpos, ypos, m_nSelBgColor);
           InvalidateRect(m_rect.left+2, y2, m_rect.right-2, ypos);     
        }
       else //m_bScrlBarVisible=true
        {             
		       // put the black color text to the window
           textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), 
                     xpos, ypos, m_nSelBgColor);      
           InvalidateRect(m_rect.left+2, y2, (m_rect.right-2), ypos); 
           DrawScrollBar(); 
       }    		 
  	} // end "if selected row"
 */
 }
else //if m_nTable=true
 {   
   //compose a numerated string, starts from 1:
   //sprintf(sNumStr, "%i %s", nCol+1, m_vItem[m_nFirstVisIndex+nCol].c_str());     
     //sprintf(ItemNum, "%d", nCol+1);
    sprintf(ItemNum, "%d", FirstJobId+nCol);
     bIsScrollBarNeeded=FALSE; // In RTG mode a scrollbar do not using. Ever.   
	 int nLimitColor=-1;

	 if (GetTimeLimit(0) != -1)
		 nLimitColor = GetLimitColor(nCol);
					 

 if ((m_nFirstVisIndex + nCol) % 2 != 0)// odd row:
	 {	  	
	 	y2 = ypos + TextHeight;
     // Drawing the odd row: white rectangle  
     if (!bIsScrollBarNeeded) // drawing without scrollbar
       {		 
		 if (nLimitColor == -1) nLimitColor = m_nBgColor;
	    //(m_rect.right - m_rect.left): wight of the control;		
       // rectfill(g_pMemBitmap, m_rect.left+2, y2, m_rect.right-2, ypos, m_nBgColor);          
        rectfill(g_pMemBitmap, m_rect.left+2, y2, m_rect.right-2, ypos, nLimitColor);          
	    //put the black text to the window:          
        textout(g_pMemBitmap, pFont, ItemNum, FromLSetup[0]+nNulOffset, ypos, m_nSelBgColor);
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 0), FromLSetup[0]+nFirOffset, ypos, m_nSelBgColor);        
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 1), FromLSetup[0]+nSecOffset, ypos, m_nSelBgColor);           
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 2), FromLSetup[0]+nThiOffset, ypos, m_nSelBgColor);           
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 3), FromLSetup[0]+nFouOffset, ypos, m_nSelBgColor);          
        //textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), FromLSetup[0]+30, ypos, m_nSelBgColor);          
        InvalidateRect(m_rect.left+2, y2, m_rect.right-2, ypos);     
       }
     else //m_bScrlBarVisible=true
       {    
      //draw	filledRect shorter
        rectfill(g_pMemBitmap, m_rect.left+2, y2, (m_rect.right-3) - m_nScrlWidth, ypos, m_nBgColor);          
	    //put the black text to the window                      
      //textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), FromLSetup[0] + 30, ypos, m_nSelBgColor);
        textout(g_pMemBitmap, pFont, ItemNum, FromLSetup[0]+nNulOffset, ypos, m_nSelBgColor);
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 0), FromLSetup[0]+nFirOffset, ypos, m_nSelBgColor);        
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 1), FromLSetup[0]+nSecOffset, ypos, m_nSelBgColor);           
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 2), FromLSetup[0]+nThiOffset, ypos, m_nSelBgColor);           
        textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 3), FromLSetup[0]+nFouOffset, ypos, m_nSelBgColor);          
        InvalidateRect(m_rect.left+2, y2, (m_rect.right-2), ypos); 
        DrawScrollBar();
       }     
  	}
   else // even row :
	  {   
      // Drawing the even row: blue rectangle
      y2 = ypos + TextHeight;
      if (!bIsScrollBarNeeded)
        {
		   //(m_rect.right - m_rect.left): wight of the control;		
  		 if (nLimitColor == -1) nLimitColor = m_nBlueColor;
       //  rectfill(g_pMemBitmap, m_rect.left+2, y2, m_rect.right-2, ypos, m_nBlueColor);          
        rectfill(g_pMemBitmap, m_rect.left+2, y2, m_rect.right-2, ypos, nLimitColor);          
		   //put the black text to the window:           
         textout(g_pMemBitmap, pFont, ItemNum, FromLSetup[0]+nNulOffset, ypos, m_nSelBgColor);
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 0), FromLSetup[0]+nFirOffset, ypos, m_nSelBgColor);
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 1), FromLSetup[0]+nSecOffset, ypos, m_nSelBgColor);           
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 2), FromLSetup[0]+nThiOffset, ypos, m_nSelBgColor);        
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 3), FromLSetup[0]+nFouOffset, ypos, m_nSelBgColor);          
         //textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), FromLSetup[0]+30, ypos, m_nSelBgColor);         
         InvalidateRect(m_rect.left+2, y2, m_rect.right-2, ypos); 
        }
      else //m_bScrlBarVisible=true
        {    
       //draw filledRect shorter
         rectfill(g_pMemBitmap, m_rect.left+2, y2, (m_rect.right-3) - m_nScrlWidth, ypos, m_nBlueColor);
       //put the black text to the window
       //textout(g_pMemBitmap, pFont, m_vItem[m_nFirstVisIndex+nCol].c_str(), FromLSetup[0] + 30, ypos, m_nSelBgColor);         
         textout(g_pMemBitmap, pFont, ItemNum, FromLSetup[0]+nNulOffset, ypos, m_nSelBgColor);
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 0), FromLSetup[0]+nFirOffset, ypos, m_nSelBgColor);        
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 1), FromLSetup[0]+nSecOffset, ypos, m_nSelBgColor);           
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 2), FromLSetup[0]+nThiOffset, ypos, m_nSelBgColor);           
         textout(g_pMemBitmap, pFont, ParseIFStr(m_vItem[m_nFirstVisIndex+nCol].c_str(), 3), FromLSetup[0]+nFouOffset, ypos, m_nSelBgColor);          
         InvalidateRect(m_rect.left+2, y2, (m_rect.right-2), ypos); 
         DrawScrollBar();
        }	 
  	} // end "if selected row"
 }
}// end "for"

   InvalidateWindow(WnAddr);
 //A viewport set back to old values
   setviewport(reOldVP.left, reOldVP.top, reOldVP.right, reOldVP.bottom, nOldVPClip);
}
/********************************************************************

  Savcor IT Oy/YS
  Declaration: Parses string and returns a part of it, 
               according the request.
  Call: ParseIFStr
  Input: const char*, int
  Returns:  string, which is a subset of the parameter's string.
  13.05.2002 Initial coding  YS

********************************************************************/
char* CListBox::ParseIFStr(const char* VString, int nCount)
{ 

int Store[3] = {0,0,0};
int j=0; 

  for (int i=0; i<20; i++)
    m_cParsedStr [i]= '\0';//NULL; 
 
  for (int i=0; i< (int)strlen(VString); i++)
    {
     if (VString[i]=='#')
      {
        Store[j] = i;
        j++;
      }
    }
  
  if (nCount ==0)
    {
    strncpy(m_cParsedStr, VString, Store[0]);    
    }
  else if(nCount ==1)
    {
    strncpy(m_cParsedStr, VString+Store[0]+1, Store[1]-Store[0]-1);    
    }
  else if(nCount ==2)
    {
    strncpy(m_cParsedStr, VString+Store[1]+1, Store[2]-Store[1]-1);    
    }
  else if(nCount ==3)
    {
    strncpy(m_cParsedStr, VString+Store[2]+1, strlen(VString) - Store[2]);    
    }
//TRACE ("m_cParsedStr = %s \n", m_cParsedStr);
  return m_cParsedStr;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Draw a scrollbar and an up-down arrows 
  Call: DrawScrollBar
  Input: void  
  Returns:  void
  22.03.2002 Initial coding  YS

********************************************************************/
void CListBox ::DrawScrollBar()

{

int vertUp[6];
int vertDown[6];
 
  //draw a scrollbar:
  rectfill (g_pMemBitmap,  m_rect.right - m_nScrlWidth - 2,
                           m_rect.top + 2, 
                           m_rect.right-2, 
                           m_rect.bottom - 2, 
                           m_nScrlBgColor);
  
  if (GetFirstVisibleIndex() > 0)
  {
   //drawing an UP arrow
    vertUp[0]= m_rect.right - (m_nScrlWidth/2)-1;     //VPKoord_X (290);
    vertUp[1]= m_rect.top + 7;                       //VPKoord_Y (5);

    vertUp[2]= m_rect.right - (int)(m_nScrlWidth*0.25)-1;  //VPKoord_X (280);
    vertUp[3]= m_rect.top + 25;                     //VPKoord_Y (25);
    
    vertUp[4]= m_rect.right - (int)(m_nScrlWidth*0.75)-1;  //VPKoord_X (300);
    vertUp[5]= m_rect.top + 25;                     //VPKoord_Y (25);

    polygon (g_pMemBitmap, 3, vertUp, m_nSelBgColor);    
   
  }
  
  if (GetLastVisibleIndex() < (int)m_vItem.size() - 1 )
  {
   //drawing a DOWN arrow   
    vertDown[0]= m_rect.right - (m_nScrlWidth/2)-1;    //VPKoord_X (290);
    vertDown[1]= m_rect.bottom  - 7;                 //VPKoord_Y (5);

    vertDown[2]= m_rect.right - (int)(m_nScrlWidth*0.25)-1; //VPKoord_X (280);
    vertDown[3]= m_rect.bottom - 25;                 //VPKoord_Y (25);
    
    vertDown[4]= m_rect.right - (int)(m_nScrlWidth*0.75)-1; //VPKoord_X (300);
    vertDown[5]= m_rect.bottom  - 25;                //VPKoord_Y (25);

    polygon (g_pMemBitmap, 3, vertDown, m_nSelBgColor);
     
  }
InvalidateRect( m_rect.right - m_nScrlWidth - 2,
                           m_rect.top + 2, 
                           m_rect.right-2, 
                           m_rect.bottom - 2);  
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Specifies whether scroll bar needs to be drawn. If
    the list box have more items than can be shown, then scroll
    bar is needed.
  Call: IsScrollBarNeeded
  Input: 
  Returns: Nonzero if scroll bar is needed; otherwise 0.
  21.03.2002 Initial coding  YS

*********************************************************************/

bool CListBox::IsScrollBarNeeded()
{
  bool bRet;
  if( ((int)m_vItem.size() > GetMaxItemsInList()) ||
    m_nFirstVisIndex != 0 )
  {
    bRet = true;
   }
  else    
   bRet = false;
  
  return bRet;
  
}
/*********************************************************************

  Savcor IT Oy/YS
  Declaration: Scrolling a listbox down page by page in a circle style,
               in debug mode there key "d" is using for scrolling. And 
               also setting a page-number variable m_nCurPage according
               to current page.
               In real life the key F6 is using for that purpose
  Call: ScrollPage
  Input: 
  Returns: 
  05.04.2002 Initial coding  YS

*********************************************************************/
 void CListBox::ScrollPage()
{
   if (GetCount() <= GetMaxItemsInList())
     {
      m_nCurPage  = 1;
      return;//not enough rows for scrolling
     }

  if(GetLastVisibleIndex() == GetCount()-1)
   {
     m_nFirstVisIndex = 0;//go to the first item in the list
     m_nCurPage  = 1;     //also go to the first page, wich is number one.
   }
  else
   {
     m_nFirstVisIndex = GetLastVisibleIndex() + 1; 
     m_nCurPage++ ; // next page
   } 

  if(!m_nTable) // non-RTG mode.
   {
     SetCurSel(m_nFirstVisIndex); 
   }
   
   if(IsVisible())
      Draw();
}
/********************************************************************

  Savcor IT Oy/YS
  Declaration: 
  Call: GetTableValue
  Input: -
  Returns: m_nTable private variable
  05.04.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetTableValue ( ) const
{
  return m_nTable;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: Setting a value which is response for a listbox/table view 
  Call: SetTableValue
  Input: nTableValue: 
  Returns: 1
  05.04.2002 Initial coding  YS

*********************************************************************/

int CListBox::SetTableValue ( int nTableValue )
{
  m_nTable = nTableValue;
  return 1;
}

/********************************************************************

  Savcor IT Oy/YS
  Declaration: get a list's item number according the current page and offset
  Call: GetLBItem
  Input:   
  Returns: item's number, integer. Starts from 0.
  02.05.2002 Initial coding  YS

*********************************************************************/

int CListBox::GetLBItem (int nStrNumber)
{
  int ReturnItem;

  if (m_nTable)
    {
    if (m_nCurPage <= 1)
      {
       return nStrNumber-1; //array starts from 0 but shows from 1
      }
    else
      {
       ReturnItem = 8*(m_nCurPage-1) + nStrNumber-1;
       return ReturnItem;
      }
    }

  else // not Table view
      return nStrNumber-1;
}
#endif // USE_JOB_LIST


/********************************************************************
Functionality in implementation:

********************************************************************/
CListBox lbShortList;

/*******************ListBox part***************************************/
//extern CListBox lbShortList;

void InitShortList()
{  
  RECT rect;
  rect.left = FromWSetup[0];
  rect.top = FromWSetup[1] + 35; 
    
  rect.bottom = MapWSetup[1] + MapWSetup[3];//ContWSetup[1]+ContWSetup[3];
  rect.right = MapWSetup[0] + MapWSetup[2];//ContWSetup[0]+ContWSetup[2];
  
  lbShortList.Create(rect, ARIALBD);  
}

void SwitchShortList()
{
static int nListDisplayOld=FALSE;

  if (nListDisplay != nListDisplayOld)
    {
    if(!nListDisplay)
      {
      SwitchCaptions(); // JO230802

      lbShortList.Hide();
      nListDisplay = FALSE;
      DrawAfterShortLBIsHidden();
      
      }
    else
      {
      SwitchCaptions();
      HideFromToCont();
      nListDisplay = TRUE;
      lbShortList.Show();   

      
      }
   //UpdateScreen();
    } 
  UpdateMenu(); // JO220802
  UpdateScreen();
  nListDisplayOld=nListDisplay;
}


void DrawAfterShortLBIsHidden()
{
DrawInitialScreenView();  
}

void HideFromToCont()
{
  // erase "From:" label (to avoid overdraw an error-indicator) 
  ClearMemBm(FromLSetup[0], 
             FromLSetup[1], 
             ErrWSetup[0] - 3, 
             ErrWSetup[3]); 
  // erase rest of labels and txtBoxes
  ClearMemBm(FromWSetup[0], 
             FromWSetup[1], 
             ContWSetup[0]+ContWSetup[2], 
             ContWSetup[1]+ContWSetup[3]);
  //erase map window
  ClearMemBm(MapWSetup[0],
             MapWSetup[1],
             MapWSetup[0]+MapWSetup[2],
             MapWSetup[1]+MapWSetup[3]);  
  
}