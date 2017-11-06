// EditToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "EditToolBar.h"
#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define INDEX_NAME	0
#define INDEX_VALUE	4
/////////////////////////////////////////////////////////////////////////////
// CEditToolBar
CEditToolBar::CEditToolBar()
{
}

CEditToolBar::~CEditToolBar()
{
}


BEGIN_MESSAGE_MAP(CEditToolBar, CToolBar)
	//{{AFX_MSG_MAP(CEditToolBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditToolBar message handlers

BOOL CEditToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO: Add your specialized code here and/or call the base class
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	rect.SetRect(0, 0, 120, 200);
	if (!m_lstName.Create(WS_TABSTOP | WS_VISIBLE | WS_VSCROLL |
		CBS_DROPDOWN | CBS_AUTOHSCROLL, rect, this, ID_EDIT_NAME))
	{
		TRACE0("Failed to create name combo-box\n");
		return -1;
	}
//	m_cboName.LimitText(10);

	rect.SetRect(0, 0, 0, 20);
	if (!m_ctrlEdit.Create(WS_TABSTOP|WS_VISIBLE|ES_MULTILINE|
		ES_AUTOHSCROLL|ES_AUTOVSCROLL, rect, this, ID_EDIT_INPUT))
	{
		TRACE0("Failed to create value edit-box\n");
		return -1;
	}
	
	return 0;
}
BOOL CEditToolBar::CreateBar(CWnd* pParentWnd)
{
	if (!CreateEx(pParentWnd, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect(0, 0, 0, 0), ID_TB_EDITBAR))
		return FALSE;
	if (!LoadToolBar(IDR_EDITBAR))
		return FALSE;
	LONG style=GetClassLong(m_hWnd,GCL_STYLE);
	style |=(CS_HREDRAW|CS_VREDRAW);
	SetClassLong(m_hWnd,GCL_STYLE,style);
	CSize sizeButton(21, 20);
	CSize sizeImage(14,14);
	SetSizes(sizeButton, sizeImage);
	//SetHeight(26);

	CRect rect;
	m_lstName.GetWindowRect(&rect);

	//m_lstName.GetWindowRect(&rect);
	SetButtonInfo(INDEX_NAME, ID_EDIT_NAME, TBBS_SEPARATOR, rect.Width());
	GetItemRect(INDEX_NAME, &rect); // FontSize ComboBox
	m_lstName.SetWindowPos(NULL, rect.left, rect.top, 0, 0, 
		SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
	m_lstName.SetFont(m_pDefaultFont);
	m_lstName.SetDroppedWidth(rect.Width() * 2);

	m_ctrlEdit.GetWindowRect(&rect);
	
	
	SetButtonInfo(INDEX_VALUE, ID_EDIT_INPUT, TBBS_SEPARATOR, rect.Width());
	GetItemRect(INDEX_VALUE, &rect);
	rect.top+=2;
	rect.bottom-=2;
	m_ctrlEdit.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(),
		SWP_NOZORDER|SWP_NOACTIVATE );
	m_ctrlEdit.SetFont(m_pDefaultFont);
	return TRUE;
}


void CEditToolBar::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CToolBar::CalcWindowRect(lpClientRect, nAdjustType);
}

void CEditToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CToolBar::OnSize(nType, cx, cy);
	CRect rctT,rect;
	LONG nDeff=0;
	if(cx>0){
		GetItemRect(INDEX_VALUE, &rect);
		SetButtonInfo(INDEX_VALUE, ID_EDIT_INPUT, TBBS_SEPARATOR, cx-rect.left+nDeff);
		m_ctrlEdit.SetWindowPos(NULL, rect.left, rect.top+1, cx-rect.left+nDeff, rect.Height()-2,
			SWP_NOZORDER|SWP_NOACTIVATE);
	}
	// TODO: Add your message handler code here
}
void CEditToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	
	CToolBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);
	if (!m_lstName.HasFocus() && !m_ctrlEdit.HasFocus())
		OnUpdateData();
}
void CEditToolBar::OnUpdateData()
{
	CLRptDesignerView* pView = GetApp()->GetActiveView();
	if(pView){
		ICLBookLib* pGrid=pView->GetReport();
		if(pGrid){
			LONG sheet=pGrid->GetCurrentSheet();
			LONG nRow=pGrid->GetFocusRow(sheet),nCol=pGrid->GetFocusCol(sheet);
			CString strName=pGrid->GetTextMatrix(sheet,nRow,nCol);
			CString str;
			m_ctrlEdit.GetWindowText(str);
			if (str != strName)
				m_ctrlEdit.SetWindowText(strName);
		}
	}
}