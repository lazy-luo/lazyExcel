#if !defined(AFX_LFLATCOMBOBOX_H__0C5B6283_31A4_4D83_81D8_DFD6FFE045CB__INCLUDED_)
#define AFX_LFLATCOMBOBOX_H__0C5B6283_31A4_4D83_81D8_DFD6FFE045CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LFlatComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLFlatComboBox window
#define FC_DRAWNORMAL	0x00000001
#define FC_DRAWRAISED	0x00000002
#define FC_DRAWPRESSD	0x00000004
class CLFlatComboBox : public CComboBox
{
// Construction
public:
	CLFlatComboBox();
	bool		m_bLBtnDown;
	COLORREF	m_clrHilite;
	COLORREF	m_clrShadow;
	COLORREF    m_clrDkShad;
	COLORREF	m_clrButton;
// Attributes
public:
private:
	LONG	m_nHeight;
// Operations
public:
	/** 该控件是否具有当前录入焦点 */
	BOOL HasFocus();
	int Offset();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLFlatComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	LONG GetClientHeight();
	void SetClientHeight(LONG nVal);
	virtual ~CLFlatComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLFlatComboBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void DrawMe(LONG nStata,COLORREF clrTL,COLORREF clrBR);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
inline BOOL CLFlatComboBox::HasFocus()
{	HWND hWnd = ::GetFocus();
	return (hWnd == m_hWnd || ::IsChild(m_hWnd, hWnd));
}
#endif // !defined(AFX_LFLATCOMBOBOX_H__0C5B6283_31A4_4D83_81D8_DFD6FFE045CB__INCLUDED_)
