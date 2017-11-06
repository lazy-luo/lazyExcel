// FormatToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "FormatToolBar.h"
#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_NAME	0
#define ID_VALUE 1
#define INDEX_BORDER	24
#define INDEX_BACKCOLOR	25
#define INDEX_FORECOLOR 26

/////////////////////////////////////////////////////////////////////////////
//
static CSize GetBaseUnits(CFont* pFont)
{
	CClientDC dc(NULL);

	ASSERT(pFont != NULL);
	ASSERT(pFont->GetSafeHandle() != NULL);
	pFont = dc.SelectObject(pFont);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	dc.SelectObject(pFont);

	return CSize(tm.tmAveCharWidth, tm.tmHeight);
}

CFormatToolBar::CFormatToolBar()
{
	CFont fnt;
  	fnt.Attach(GetStockObject(DEFAULT_GUI_FONT));
	m_szBaseUnits = GetBaseUnits(&fnt);
	CFontComboBox::m_nFontHeight = m_szBaseUnits.cy;
}

CFormatToolBar::~CFormatToolBar()
{
}


BEGIN_MESSAGE_MAP(CFormatToolBar, CToolBar)
	//{{AFX_MSG_MAP(CFormatToolBar)
		ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_CBN_DROPDOWN(ID_FORMAT_FONTSIZE, OnFontSizeDropDown)
	ON_CBN_KILLFOCUS(ID_FORMAT_FONTNAME, OnFontNameKillFocus)
	ON_CBN_KILLFOCUS(ID_FORMAT_FONTSIZE, OnFontSizeKillFocus)
	ON_CBN_SETFOCUS(ID_FORMAT_FONTNAME, OnComboSetFocus)
	ON_CBN_SETFOCUS(ID_FORMAT_FONTSIZE, OnComboSetFocus)
	ON_CBN_CLOSEUP(ID_FORMAT_FONTNAME, OnComboCloseUp)
	ON_CBN_CLOSEUP(ID_FORMAT_FONTSIZE, OnComboCloseUp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatToolBar message handlers
BOOL CFormatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	return 0;
}

BOOL CFormatToolBar::CreateBar(CWnd* pParentWnd)
{
	if (!CreateEx(pParentWnd, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect(0, 0, 0, 0), ID_TB_FORMATBAR))
		return FALSE;
	if (!LoadToolBar(IDR_TOOLBAR_FORMAT))
		return FALSE;
	//SetHeight(23);
	int ii=2;
	this->SetButtonStyle(ID_VALUE+ii,TBBS_CHECKBOX);
	this->SetButtonStyle(ID_VALUE+ii+1,TBBS_CHECKBOX);
	this->SetButtonStyle(ID_VALUE+ii+2,TBBS_CHECKBOX);

	ii+=4;
	this->SetButtonStyle(ID_VALUE+ii,TBBS_CHECKGROUP);
	this->SetButtonStyle(ID_VALUE+ii+1,TBBS_CHECKGROUP);
	this->SetButtonStyle(ID_VALUE+ii+2,TBBS_CHECKGROUP);

	ii+=4;
	this->SetButtonStyle(ID_VALUE+ii,TBBS_CHECKGROUP);
	this->SetButtonStyle(ID_VALUE+ii+1,TBBS_CHECKGROUP);
	this->SetButtonStyle(ID_VALUE+ii+2,TBBS_CHECKGROUP);

	SetButtonInfo(ID_NAME, ID_FORMAT_FONTNAME, TBBS_SEPARATOR, 168);
	SetButtonInfo(ID_VALUE, ID_FORMAT_FONTSIZE, TBBS_SEPARATOR, 64);
	SetButtonInfo(INDEX_BORDER, ID_FORMAT_BORDER, TBBS_SEPARATOR, 32);
	SetButtonInfo(INDEX_FORECOLOR, ID_FORMAT_BACKCOLOR, TBBS_SEPARATOR, 32);
	SetButtonInfo(INDEX_BACKCOLOR, ID_FORMAT_FORECOLOR, TBBS_SEPARATOR, 32);
	CRect rect;
	GetItemRect(ID_NAME, &rect);
	//rect.top++;
	rect.bottom = rect.top + 200;
	
	if (!m_lstFontName.Create(WS_TABSTOP|WS_VISIBLE|WS_TABSTOP|
		WS_VSCROLL|CBS_DROPDOWN|CBS_SORT|CBS_AUTOHSCROLL|CBS_HASSTRINGS|
		CBS_OWNERDRAWFIXED, rect, this, ID_FORMAT_FONTNAME))
	{
		TRACE0("Failed to create fontname combo-box\n");
		return -1;
	}
	m_lstFontName.LimitText(LF_FACESIZE);
	m_lstFontName.SetFont(m_pDefaultFont);
	m_lstFontName.SetDroppedWidth(rect.Width() * 3);

	GetItemRect(ID_VALUE, &rect);
	rect.bottom = rect.top + 200;
	//rect.top++;
	if (!m_lstFontSize.Create(WS_TABSTOP|WS_VISIBLE|WS_TABSTOP|
		WS_VSCROLL|CBS_DROPDOWN|CBS_SORT|CBS_AUTOHSCROLL|CBS_HASSTRINGS
		, rect, this, ID_FORMAT_FONTSIZE))
	{
		TRACE0("Failed to create fontsize combo-box\n");
		return -1;
	}
	m_lstFontSize.SetFont(m_pDefaultFont);
	//m_lstFontSize.EnumFontSizes(
	m_lstFontName.SetDroppedWidth(rect.Width() * 3 / 2);

	GetItemRect(INDEX_BORDER, &rect);
	//rect.InflateRect(0,-1,0,-1);
	
	if (!m_wndBorder.Create(rect, this, ID_FORMAT_BORDER,IDB_BMP_BORDER_COLOR))
	{
		TRACE0("Failed to create border picker\n");
		return -1;
	}
	m_wndBorder.SetColor(RGB(0,0,0));
	
	GetItemRect(INDEX_BACKCOLOR, &rect);
	//rect.InflateRect(0,-1,0,-1);
	if (!m_wndBackColor.Create(rect, this, ID_FORMAT_BACKCOLOR,IDB_BMP_BKCOLOR))
	{
		TRACE0("Failed to create back color picker\n");
		return -1;
	}
	m_wndBackColor.SetColor(RGB(255,255,255));

	GetItemRect(INDEX_FORECOLOR, &rect);
	//rect.InflateRect(0,-1,0,-1);
	if (!m_wndForeColor.Create(rect, this, ID_FORMAT_FORECOLOR,IDB_BMP_FORECOLOR))
	{
		TRACE0("Failed to create fore color picker\n");
		return -1;
	}
	m_wndForeColor.SetColor(RGB(0,0,0));
	m_lstFontSize.LimitText(4);
	m_lstFontName.EnumFontFamiliesEx(m_dcPrinter);
//	m_lstFontSize.MatchFont("ËÎÌו",134);
	
	return TRUE;
}

void CFormatToolBar::OnUpdateColor()
{
	CLRptDesignerView* pView = GetApp()->GetActiveView();
	if (pView == NULL)
	{
		if (m_wndBackColor.IsWindowEnabled())
			m_wndBackColor.EnableWindow(TRUE);
		if (m_wndForeColor.IsWindowEnabled())
			m_wndForeColor.EnableWindow(TRUE);
		if (m_wndBorder.IsWindowEnabled())
			m_wndBorder.EnableWindow(TRUE);
		return;
	}
	if(pView){
		ICLBookLib* pGrid=pView->GetReport();
		if(pGrid){
			LONG sheet=pGrid->GetCurrentSheet();
			LONG lngBkClr=pGrid->GetCurrentCellBkColor(sheet);
			if(lngBkClr!=(LONG)m_wndBackColor.GetColor()){
				m_wndBackColor.SetColor(lngBkClr);
				m_wndBackColor.Invalidate();
			}
			LONG lngForeClr=pGrid->GetCurrentCellForeColor(sheet);
			if(lngForeClr!=(LONG)m_wndForeColor.GetColor())
			{
				m_wndForeColor.SetColor(lngForeClr);
				m_wndForeColor.Invalidate();
			}
			
			
			LONG lngBorderClr=pGrid->GetCurrentCellBorderColor(sheet);
			if(lngBorderClr!=(LONG)m_wndBorder.GetColor()){
				m_wndBorder.SetColor(lngBorderClr);
				m_wndBorder.Invalidate();
			}
		}
	}
}
void CFormatToolBar::OnUpdateCombo()
{
	CLRptDesignerView* pView = GetApp()->GetActiveView();

	if (pView == NULL)
	{
		if (m_lstFontName.IsWindowEnabled())
			m_lstFontName.EnableWindow(TRUE);
		if (m_lstFontSize.IsWindowEnabled())
			m_lstFontSize.EnableWindow(TRUE);
		return;
	}
	if(pView){
		ICLBookLib* pGrid=pView->GetReport();
		if(pGrid){
			LONG sheet=pGrid->GetCurrentSheet();
			LONG nRow=pGrid->GetFocusRow(sheet),nCol=pGrid->GetFocusCol(sheet);
			CString strName=pGrid->GetGetFontName(sheet,nRow,nCol);
			CString str;
			m_lstFontName.GetWindowText(str);
			if (str != strName)
				m_lstFontName.SetWindowText(strName);
			LONG nHeight=pGrid->GetGetFontSize(sheet,nRow,nCol);
			CString strSize;
			if (nHeight < 0)
				strSize.Format("%d", (-nHeight)*72/96);
			else
				strSize.Format("%d", nHeight*72/96);
			m_lstFontSize.GetWindowText(str);
			if (str != strSize){
				//m_lstFontSize.EnumFontSizes(m_dcPrinter,strName);
				m_lstFontSize.SetWindowText(strSize);
			}
		}
	}
}

void CFormatToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	//CLRptDesignerView* pView = GetApp()->GetActiveView();
	CToolBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);
	// don't update combo boxes if either one has the focus
	if (!m_lstFontName.HasFocus() && !m_lstFontSize.HasFocus())
		OnUpdateCombo();
	OnUpdateColor();
/*	if (pDoc && !pDoc->GetSheet()->IsProtected())
	{
		m_wndBackColor.EnableWindow(TRUE);
		m_wndBorder.EnableWindow(TRUE);
		m_wndForeColor.EnableWindow(TRUE);
	}
	else
	{
		m_wndBackColor.EnableWindow(FALSE);
		m_wndBorder.EnableWindow(FALSE);
		m_wndForeColor.EnableWindow(FALSE);
	}*/
	/*
	
	*/
}

void CFormatToolBar::NotifyOwner(UINT nCode)
{
	NMHDR nm;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();
	nm.code = nCode;
	GetOwner()->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
}

void CFormatToolBar::OnFontSizeDropDown()
{
	CString str;
	m_lstFontName.GetTheText(str);
	LPCTSTR lpszName = NULL;
	BOOL bPrinterFont = FALSE;
	int nIndex = m_lstFontName.FindStringExact(-1, str);
	if (nIndex != CB_ERR)
	{
		CFontDesc* pDesc = (CFontDesc*)m_lstFontName.GetItemData(nIndex);
		ASSERT(pDesc != NULL);
		bPrinterFont = pDesc->m_dwFlags & PRINTER_FONT;
		lpszName = pDesc->m_strName;
	}

	int nSize = m_lstFontSize.GetTwipSize();
	if (nSize == -2) // error
	{
		//AfxMessageBox(IDS_INVALID_NUMBER, MB_OK|MB_ICONINFORMATION);
		nSize = m_lstFontSize.m_nTwipsLast;
	}
	else if ((nSize >= 0 && nSize < 20) || nSize > 32760)
	{
		//AfxMessageBox(IDS_INVALID_FONTSIZE, MB_OK|MB_ICONINFORMATION);
		nSize = m_lstFontSize.m_nTwipsLast;
	}

	if (bPrinterFont)
		m_lstFontSize.EnumFontSizes(m_dcPrinter, lpszName);
	else
	{
		CClientDC dc(NULL);
		m_lstFontSize.EnumFontSizes(dc, lpszName);
	}
	m_lstFontSize.SetTwipSize(nSize);
}

void CFormatToolBar::OnComboCloseUp()
{
	CLRptDesignerView* pView = GetApp()->GetActiveView();

	if (pView != NULL)
		pView->SetFocus();
}

void CFormatToolBar::OnComboSetFocus()
{
	NotifyOwner(NM_SETFOCUS);
}

void CFormatToolBar::OnFontNameKillFocus()
{
//	USES_CONVERSION;
	// get the current font from the view and update
	NotifyOwner(NM_KILLFOCUS);

	NMFONTHDR fh;
	fh.lf.lfFaceName[0] = NULL;

	CString str;
	int nIndex = m_lstFontName.GetCurSel();
	if (nIndex == CB_ERR)
		m_lstFontName.GetWindowText(str);
	else
		m_lstFontName.GetLBText(nIndex, str);

	// if font name box is not empty
	//if (str[0] != NULL)
	if (!str.IsEmpty())
	{
		ASSERT(str.GetLength() < LF_FACESIZE);
		lstrcpyn(fh.lf.lfFaceName, str, LF_FACESIZE);
		fh.mask = NMFONTHDR::FONTNAME;

		fh.hwndFrom = m_hWnd;
		fh.idFrom = GetDlgCtrlID();
		fh.code = msg_ncSETFONT;
		GetOwner()->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh);
	}
}

void CFormatToolBar::OnFontSizeKillFocus()
{
	NotifyOwner(NM_KILLFOCUS);
	int nSize = m_lstFontSize.GetTwipSize();
	if (nSize == -2)
		nSize = m_lstFontSize.m_nTwipsLast;
	else if ((nSize >= 0 && nSize < 20) || nSize > 32760)
		nSize = m_lstFontSize.m_nTwipsLast;
	else if (nSize > 0)
	{
		NMFONTHDR fh;

		fh.mask = NMFONTHDR::FONTSIZE;
		fh.lf.lfHeight = -(nSize / 20 * 96 / 72);

		fh.hwndFrom = m_hWnd;
		fh.idFrom = GetDlgCtrlID();
		fh.code = msg_ncSETFONT;
		GetOwner()->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh);
	}
}

