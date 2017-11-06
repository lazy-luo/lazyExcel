// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "Childfrm.h"
#include "MainFrm.h"
#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
typedef BOOL (__stdcall *fpBeginHook)(void);
typedef BOOL (__stdcall *fpEndHook)(void);
static fpBeginHook pBeginHook=NULL;
static fpEndHook  pEndHook=NULL;
HMODULE	m_hMod=NULL;
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
void CMainFrame::OnEnableOwnerDrawCtrl(BOOL bEnable)
{
	m_wndDesignerToolBar.m_cBorderLinePick.EnableWindow(bEnable);
	m_wndDesignerToolBar.m_cGridLinePick.EnableWindow(bEnable);
	m_wndDesignerToolBar.Invalidate();

	m_wndEditBar.m_ctrlEdit.EnableWindow(bEnable);
	m_wndEditBar.m_lstName.EnableWindow(bEnable);
	m_wndEditBar.Invalidate();

	m_wndFormatToolBar.m_wndForeColor.EnableWindow(bEnable);
	m_wndFormatToolBar.m_wndBorder.EnableWindow(bEnable);
	m_wndFormatToolBar.m_wndBackColor.EnableWindow(bEnable);
	m_wndFormatToolBar.m_lstFontSize.EnableWindow(bEnable);
	m_wndFormatToolBar.m_lstFontName.EnableWindow(bEnable);
	m_wndFormatToolBar.Invalidate();
}
BOOL CMainFrame::AdjustHelpMenu(HWND hwnd)
{
	if(!hwnd)return FALSE;
	MENUITEMINFO mInfo;
	LONG buffsize;
	HMENU hmenu;
	LONG nRet;
	buffsize=128;
	BOOL bRet=FALSE;
	char buff[128];
	hmenu=::GetMenu(hwnd);
	
	if(hmenu){
		LONG nct=::GetMenuItemCount(hmenu)-1;
		//if(nct<0)nct=6;
		mInfo.cbSize=sizeof(MENUITEMINFO);
		mInfo.fMask = MIIM_TYPE;
        mInfo.cch = buffsize;
        mInfo.dwTypeData =(char*)&buff;
        nRet = GetMenuItemInfo(hmenu, nct, 1, &mInfo);
		if(nRet){
			mInfo.fMask = MIIM_TYPE;
			mInfo.fType = mInfo.fType | MFT_RIGHTJUSTIFY;
			nRet = SetMenuItemInfo(hmenu, nct, 1, &mInfo);
			bRet = nRet !=NULL;
		}
	}
	return bRet;
}
CMainFrame::CMainFrame()
{
	::CoInitialize(NULL);
	//SetMenuHook();
}

CMainFrame::~CMainFrame()
{
	::CoUninitialize();
	//ClearHook();
}
CLRptDesignerView* CMainFrame::GetActiveView()
{
	// Get the active MDI child window.
	CChildFrame *pChild = (CChildFrame*)GetActiveFrame();
	// Get the active view attached to the active MDI child window.
	return (CLRptDesignerView*)pChild->GetActiveView();
}

CLRptDesignerDoc* CMainFrame::GetActiveDoc()
{
	CLRptDesignerView* pView = GetActiveView();
	if (pView)
		return pView->GetDocument();
	else
		return NULL;
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_wndReBar.Create(this)){
		TRACE0("创建工具条失败\n");
		return -1;
	}
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,  WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if(!m_wndDesignerToolBar.CreateBar(this)){
		TRACE0("Failed to create toolbar\n");
		return -1;  
	}
	if(!m_wndFormatToolBar.CreateBar(this)){
		TRACE0("创建工具条失败\n");
		return -1;
	}
	
	if(!m_wndEditBar.CreateBar(this)){
		TRACE0("创建工具条失败\n");
		return -1;
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if(!m_wndReBar.AddBar((CWnd*)&m_wndToolBar)
		|| !m_wndReBar.AddBar((CWnd*)&m_wndDesignerToolBar)
		|| !m_wndReBar.AddBar((CWnd*)&m_wndFormatToolBar)
		|| !m_wndReBar.AddBar((CWnd*)&m_wndEditBar)){
		TRACE0("创建工具条失败\n");
		return -1;
	}
	/*
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDesignerToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormatToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndEditBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndDesignerToolBar);
	DockControlBar(&m_wndFormatToolBar);
	DockControlBar(&m_wndEditBar);
	*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::SetMenuHook()
{
	
	if(m_hMod==NULL){
		m_hMod=::LoadLibrary("LMenuBase.dll");
		if(m_hMod){
			pBeginHook=(fpBeginHook)::GetProcAddress(m_hMod,"BeginHook");
			if(!pBeginHook){
				goto to_clear;
			}
			pEndHook=(fpEndHook)::GetProcAddress(m_hMod,"EndHook");
			if(!pEndHook){
				goto to_clear;
			}
			(*pBeginHook)();
		}
	}
	return;
to_clear:
	if(m_hMod){
		::FreeLibrary(m_hMod);
		try{
			::CloseHandle(m_hMod);
		}catch(...){}
		m_hMod=NULL;
		pBeginHook=NULL;
		pBeginHook=NULL;
	}
	
}

void CMainFrame::ClearHook()
{
	if(pEndHook){
		(*pEndHook)();
		if(m_hMod){
			::FreeLibrary(m_hMod);
			m_hMod=NULL;
			pBeginHook=NULL;
			pEndHook=NULL;
		}
	}
}

BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(wParam){
	case ID_FORMAT_BORDER:
	case ID_FORMAT_BACKCOLOR:
	case ID_FORMAT_FORECOLOR:
	case ID_GRID_LINE_STYLE:
	case ID_BORDER_LINE_STYLE:
		{
			CMDIFrameWnd *pFrame = 
             (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

			CMDIChildWnd *pChild = 
             (CMDIChildWnd *) pFrame->GetActiveFrame();

			CLRptDesignerView *pView = (CLRptDesignerView *) pChild->GetActiveView();

			//CLRptDesignerView* pView=(CLRptDesignerView*)AfxGetApp()->m_pMainWnd->GetActiveView();
			pView->OnNotify(wParam,lParam,pResult);
			//::SendMessage(pView->m_hWnd,WM_NOTIFY,wParam,lParam);
			return TRUE;
		}
	}
	return CMDIFrameWnd::OnNotify(wParam, lParam, pResult);
}

