// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__34C61108_4D55_44B0_A1D7_D49A11DAA525__INCLUDED_)
#define AFX_MAINFRM_H__34C61108_4D55_44B0_A1D7_D49A11DAA525__INCLUDED_

#include "EditToolBar.h"	// Added by ClassView
#include "DesignerTollBar.h"	// Added by ClassView
#include "FormatToolBar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CLRptDesignerView;
class CLRptDesignerDoc;
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	static BOOL AdjustHelpMenu(HWND hwnd);
	CLRptDesignerView* GetActiveView();
	CLRptDesignerDoc* GetActiveDoc();
// Operations
public:
	void OnEnableOwnerDrawCtrl(BOOL bEnable);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFormatToolBar m_wndFormatToolBar;
	CDesignerTollBar m_wndDesignerToolBar;
	CEditToolBar m_wndEditBar;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar		m_wndReBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	void ClearHook();
	void SetMenuHook();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__34C61108_4D55_44B0_A1D7_D49A11DAA525__INCLUDED_)
