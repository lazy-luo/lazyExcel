#if !defined(AFX_LFLATEDIT_H__4CF54C33_E181_4334_BD69_6EAA6E89DF6C__INCLUDED_)
#define AFX_LFLATEDIT_H__4CF54C33_E181_4334_BD69_6EAA6E89DF6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LFlatEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLFlatEdit window

class CLFlatEdit : public CEdit
{
// Construction
public:
	CLFlatEdit();

// Attributes
public:
	/** 该控件是否具有当前录入焦点 */
	BOOL HasFocus();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLFlatEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLFlatEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLFlatEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
inline BOOL CLFlatEdit::HasFocus()
{	HWND hWnd = ::GetFocus();
	return (hWnd == m_hWnd || ::IsChild(m_hWnd, hWnd));
}
#endif // !defined(AFX_LFLATEDIT_H__4CF54C33_E181_4334_BD69_6EAA6E89DF6C__INCLUDED_)
