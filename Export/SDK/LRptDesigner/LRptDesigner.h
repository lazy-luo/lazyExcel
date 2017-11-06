// LRptDesigner.h : main header file for the LRPTDESIGNER application
//

#if !defined(AFX_LRPTDESIGNER_H__BAAC369B_1D0F_48C9_A2D7_A8825C97BE76__INCLUDED_)
#define AFX_LRPTDESIGNER_H__BAAC369B_1D0F_48C9_A2D7_A8825C97BE76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"       // main symbols
#include "MainFrm.h"
#include "COMM\LReg.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerApp:
// See LRptDesigner.cpp for the implementation of this class
//
class CLRptDesignerView;
class CLRptDesignerDoc;

class CLRptDesignerApp : public CWinApp
{
public:
	CLRptDesignerApp();
	/** 取的活动视图 */
	CLRptDesignerView* GetActiveView() const
	{ return m_pMainWnd ? (CLRptDesignerView*)((CMainFrame*)m_pMainWnd)->GetActiveView() : NULL; }
	/** 取活动文档 */
	CLRptDesignerDoc* GetActiveDoc() const
	{ return m_pMainWnd ? ((CMainFrame*)m_pMainWnd)->GetActiveDoc() : NULL; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLRptDesignerApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLRptDesignerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	void SetFileContent();
	CLReg m_reg;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
CLRptDesignerApp* GetApp();
#endif // !defined(AFX_LRPTDESIGNER_H__BAAC369B_1D0F_48C9_A2D7_A8825C97BE76__INCLUDED_)
