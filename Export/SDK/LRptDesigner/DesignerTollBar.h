#if !defined(AFX_DESIGNERTOLLBAR_H__69441F86_C078_473B_8E51_0BD017C28CF7__INCLUDED_)
#define AFX_DESIGNERTOLLBAR_H__69441F86_C078_473B_8E51_0BD017C28CF7__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DesignerTollBar.h : header file
//
#include "Comm/LImagePicker.h"
/////////////////////////////////////////////////////////////////////////////
// CDesignerTollBar window
#define ID_BORDRLINE	21
#define ID_GRIDLINE		22
class CDesignerTollBar : public CToolBar
{
	friend class CMainFrame;
// Construction
public:
	CDesignerTollBar();
	BOOL CreateBar(CWnd* pParentWnd);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
// Attributes
private:
	static ImageTableEntry m_nBorders[];
	static ImageTableEntry m_nGridLines[];
	void OnUpdateCtrl();
	CLImagePicker	m_cBorderLinePick;
	CLImagePicker	m_cGridLinePick;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignerTollBar)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CDesignerTollBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDesignerTollBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESIGNERTOLLBAR_H__69441F86_C078_473B_8E51_0BD017C28CF7__INCLUDED_)
