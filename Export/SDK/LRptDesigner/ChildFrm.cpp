// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "LRptDesigner.h"

#include "ChildFrm.h"
#include "LRptDesignerDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_NCCALCSIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction
void CChildFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	lpncsp->rgrc->left-=2;
	lpncsp->rgrc->top-=2;
	lpncsp->rgrc->right+=1;
	lpncsp->rgrc->bottom+=1;
	*/
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
		| WS_MAXIMIZE | WS_SIZEBOX;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
						 const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bret= CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
	return bret;
}

void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

BOOL CChildFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bret= CMDIChildWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);

	return bret;
}

CFrameWnd* CChildFrame::GetActiveFrame() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIChildWnd::GetActiveFrame();
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bret= CMDIChildWnd::OnCreateClient(lpcs, pContext);
	if(bret)
		CMainFrame::AdjustHelpMenu(m_hWnd);
	return bret;
}
