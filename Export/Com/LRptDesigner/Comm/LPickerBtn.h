#if !defined(AFX_LPICKERBTN_H__FCF7D6E5_CDF1_43C5_8B88_BF4FD22212D9__INCLUDED_)
#define AFX_LPICKERBTN_H__FCF7D6E5_CDF1_43C5_8B88_BF4FD22212D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// lpickerbtn.h : header file
//
#include "LColorPan.h"
#ifndef ABSTRACT
#define ABSTRACT	=0
#endif
#define TIMER_ID	131421
struct PICKERBTNHDR : public tagNMHDR
{
	LONG iValue;
};
/////////////////////////////////////////////////////////////////////////////
// CLPickerBtn window

class CLPickerBtn : public CWnd
{
// Construction
public:
	CLPickerBtn(LONG nDefault);
	BOOL Create(CRect rect, CWnd * pParentWnd, UINT nID,LONG nBmpID=0);
	void SetBitmapRes(LONG nResID);
	
	virtual void OnPopup() ABSTRACT;
	virtual void OnDrawButton(CDC * pDC, CRect& rect) ABSTRACT;
// Attributes
private:
	BOOL	 m_bLeftBtnDown,m_bMouseOut,
		m_bInLeftBtn,m_bRightBtnDown,m_bInRightBtn;
    BOOL     m_bActive,m_bTrackSelection;       
    
    CRect    m_ArrowRect;
    
	CWnd*	m_ptrParent;
	
	
	LONG m_lngValue;
	UINT m_timer;
	
	void SetTimer();
	void ClearTimer();
	void OnSelected();
	void OnStatusChange();
	void Hitest(const CPoint& pt);
	void DrawItem(CDC* pDC);
	void DrawAArrow(CDC * pDC, CRect * pRect,COLORREF clrBk);
	void DrawArrow(CDC * pDC, CRect * pRect,BOOL bEnable);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLPickerBtn)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLPickerBtn();

	// Generated message map functions
protected:
	LONG m_hBitmapID;
	LONG GetValue();
	CRect          m_WindowRect;
	void DrawTransInvertPic(HDC hDstDC, INT nXDest, INT nYDest, 
									 INT nWidth,INT nHeight, HBITMAP bmp, 
									 INT nXSrc=0, INT nYSrc=0,COLORREF bgcolor=GetSysColor(COLOR_BTNFACE));
	void DrawTransPic(CDC* pDC, CBitmap* pBitmap, int X, int Y,BOOL bInvert);
	void SetValue(LONG val);
	//{{AFX_MSG(CLPickerBtn)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LPICKERBTN_H__FCF7D6E5_CDF1_43C5_8B88_BF4FD22212D9__INCLUDED_)
