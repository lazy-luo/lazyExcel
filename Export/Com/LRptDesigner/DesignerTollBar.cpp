// DesignerTollBar.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "DesignerTollBar.h"
#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDesignerTollBar
ImageTableEntry CDesignerTollBar::m_nBorders[] = {
	{ 0,   IDB_BMP_BORDER_NONE, _T("ÎÞ±ß¿ò")             },
	{ 1,   IDB_BMP_BORDER_LEFT, _T("×ó±ß¿ò")             },
	{ 2,   IDB_BMP_BORDER_TOP, _T("ÉÏ±ß¿ò")             },
	{ 4,   IDB_BMP_BORDER_RIGHT, _T("ÓÒ±ß¿ò")             },
	{ 8,   IDB_BMP_BORDER_BOTTOM, _T("ÏÂ±ß¿ò")             },
	{ 3,   IDB_BMP_BORDER_LT, _T("×óÉÏ±ß¿ò")             },
	{ 5,   IDB_BMP_BORDER_LR, _T("×óÓÒ±ß¿ò")             },
	{ 9,   IDB_BMP_BORDER_LB, _T("×óÏÂ±ß¿ò")             },
	{ 6,   IDB_BMP_BORDER_TR, _T("ÉÏÓÒ±ß¿ò")             },
	{ 10,   IDB_BMP_BORDER_TB, _T("ÉÏÏÂ±ß¿ò")             },
	{ 12,   IDB_BMP_BORDER_RB, _T("ÓÒÏÂ±ß¿ò")             },
	{ 13,   IDB_BMP_BORDER_LRB, _T("×óÓÒÏÂ±ß¿ò")             },
	{ 7,   IDB_BMP_BORDER_LTR, _T("×óÉÏÓÒ±ß¿ò")             },
	{ 14,   IDB_BMP_BORDER_TBR, _T("ÉÏÓÒÏÂ±ß¿ò")             },
	{ 11,   IDB_BMP_BORDER_TLB, _T("ÏÂ×óÉÏ±ß¿ò")             },
	{ 15,   IDB_BMP_BORDER_ALL, _T("ËùÓÐ±ß¿ò")           }
};
ImageTableEntry CDesignerTollBar::m_nGridLines[] = {
	{ 1,   IDB_BMP_GRIDLINE_ALL, _T("ËùÓÐ±ß¿ò")             },
	{ 2,   IDB_BMP_GRIDLINE_HORZ, _T("ºáÏò±ß¿ò")             },
	{ 4,   IDB_BMP_GRIDLINE_VERT, _T("×ÝÏò±ß¿ò")             },
	{ 7,   IDB_BMP_GRIDLINE_NONE, _T("ÎÞ±ß¿ò")             }
};

CDesignerTollBar::CDesignerTollBar()
{
}

CDesignerTollBar::~CDesignerTollBar()
{
}


BEGIN_MESSAGE_MAP(CDesignerTollBar, CToolBar)
	//{{AFX_MSG_MAP(CDesignerTollBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesignerTollBar message handlers
BOOL CDesignerTollBar::CreateBar(CWnd* pParentWnd)
{
	if (!CreateEx(pParentWnd, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect(0, 0, 0, 0), ID_TB_DESIGNER))
		return FALSE;
	if (!LoadToolBar(IDR_TOOLBAR_DESIGNER))
		return FALSE;
	SetButtonInfo(ID_BORDRLINE, ID_BORDER_LINE_STYLE, TBBS_SEPARATOR, 32);
	SetButtonInfo(ID_GRIDLINE, ID_GRID_LINE_STYLE, TBBS_SEPARATOR, 32);
	
	CRect rect;
	GetItemRect(ID_BORDRLINE, &rect);
	
	if (!m_cBorderLinePick.Create(rect, this, ID_BORDER_LINE_STYLE,4,4,m_nBorders,IDB_BMP_BORDER_NONE))
	{
		TRACE0("Failed to create fore color picker\n");
		return -1;
	}
	m_cBorderLinePick.SetCurrentValue(0);
	
	GetItemRect(ID_GRIDLINE, &rect);
	if (!m_cGridLinePick.Create(rect, this, ID_GRID_LINE_STYLE,2,2,m_nGridLines,IDB_BMP_GRIDLINE_ALL))
	{
		TRACE0("Failed to create fore color picker\n");
		return -1;
	}
	m_cGridLinePick.SetCurrentValue(1);
	return TRUE;
}

int CDesignerTollBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	return 0;
}
void CDesignerTollBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CToolBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
	OnUpdateCtrl();
}
void CDesignerTollBar::OnUpdateCtrl()
{
	CLRptDesignerView* pView = GetApp()->GetActiveView();
	if (pView == NULL)
	{
		if (m_cBorderLinePick.IsWindowEnabled())
			m_cBorderLinePick.EnableWindow(TRUE);
		if (m_cGridLinePick.IsWindowEnabled())
			m_cGridLinePick.EnableWindow(TRUE);
		return;
	}
	if(pView){
		ICLBookLib* pGrid=pView->GetReport();
		if(pGrid){
			LONG sheet=pGrid->GetCurrentSheet();
			LONG nRow=pGrid->GetFocusRow(sheet),nCol=pGrid->GetFocusCol(sheet);
			LONG lngBorderStyle=pGrid->GetBorderLineStyle(sheet,nRow,nCol);
			if(lngBorderStyle!=m_cBorderLinePick.GetCurrentValue()){
				m_cBorderLinePick.SetCurrentValue(lngBorderStyle);
				m_cBorderLinePick.Invalidate();
			}
			LONG lngGridLine=pGrid->GetGridLineStyle(sheet);
			if(lngGridLine!=m_cGridLinePick.GetCurrentValue()){

				m_cGridLinePick.SetCurrentValue(lngGridLine);
				m_cGridLinePick.Invalidate();
			}
		}
	}
}