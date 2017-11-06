#if !defined(AFX_EDITTOOLBAR_H__3AE3ADAC_A492_48AD_993E_275056B36748__INCLUDED_)
#define AFX_EDITTOOLBAR_H__3AE3ADAC_A492_48AD_993E_275056B36748__INCLUDED_

#include "LFlatComboBox.h"	// Added by ClassView
#include "CTRL\LFlatEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditToolBar window

class CEditToolBar : public CToolBar
{
// Construction
	friend class CMainFrame;
public:
	CEditToolBar();
	//CLFlatComboBox m_lstName;
// Attributes
public:
	BOOL CreateBar(CWnd* pParentWnd);
// Operations
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditToolBar)
	protected:
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	CLFlatComboBox m_lstName;
	virtual ~CEditToolBar();

	// Generated message map functions
protected:
	void OnUpdateData();
	//{{AFX_MSG(CEditToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CLFlatEdit m_ctrlEdit;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTOOLBAR_H__3AE3ADAC_A492_48AD_993E_275056B36748__INCLUDED_)
