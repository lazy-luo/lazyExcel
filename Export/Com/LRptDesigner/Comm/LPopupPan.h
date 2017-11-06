///////////////////////////////////////////////////////////////////////////////////////////////
//@模块		:	通用弹出画板基类（展现类似菜单）
//@作者		:	罗智勇
//@创建时间	:	2005-09-16
///////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPOPUPPAN_H__98C712AC_E90B_41DD_AA28_30F0F4057134__INCLUDED_)
#define AFX_LPOPUPPAN_H__98C712AC_E90B_41DD_AA28_30F0F4057134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CLPopupPan window
//当前位置在Pan中的域
#define LPN_SELCHANGE        WM_USER + 1001        // 弹出控件选择事件
#define LPN_DROPDOWN         WM_USER + 1002        // 下拉事件
#define LPN_CLOSEUP          WM_USER + 1003        // 关闭弹出控件
#define LPN_SELENDOK         WM_USER + 1004        // 选择并关闭
#define LPN_SELENDCANCEL     WM_USER + 1005        // 取消并关闭
#ifndef ABSTRACT
#define ABSTRACT	=0
#endif
#ifndef WM_DISABLEMODAL
#define WM_DISABLEMODAL     0x036C
#endif
class CLPopupPan : public CWnd
{
// Construction
public:
	CLPopupPan();
    CLPopupPan(CPoint p, LPVOID pDefault, CWnd* pParentWnd);
	BOOL Create(CPoint p, LPVOID pDefault, CWnd* pParentWnd);
// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLPopupPan)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	HBRUSH HBrushDitherCreate(COLORREF rgbFace, COLORREF rgbHilight);
	BOOL IsRightButtonDown();
	BOOL IsLeftButtonDown();
	BOOL IsMouseIN();
	virtual void ShowToolTips(LPMSG lpMsg){};
	virtual void OnMouseOver(UINT nFlags, CPoint point) ABSTRACT;
	virtual void OnMouseDown(UINT nFlags, CPoint point,BOOL bLeft){};
	virtual void OnMouseUp(UINT nFlags, CPoint point,BOOL bLeft){};
	virtual void OnMouseOut() ABSTRACT;
	virtual void GetWindowSize(CRect& rct) ABSTRACT;
	virtual void CreateToolTips(){};
	virtual void Initialise() ABSTRACT;
	virtual void OnDraw(CDC* pDC,const RECT& rctClip) ABSTRACT;
	virtual ~CLPopupPan();
	// Generated message map functions
protected:
	virtual LPVOID GetSelectValue(int& nMessage) ABSTRACT;
	//{{AFX_MSG(CLPopupPan)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnNcDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL	m_bMouseINOld;
	CRect m_WindowRect;
	BOOL m_bRMouseDown;
	BOOL m_bLMouseDown;
	CWnd*	m_pParent;
	BOOL m_bMouseIN;
	UINT m_timer;
	LONG m_nMargin;
	LPVOID	m_lpDefault_V;

	BOOL	m_bCanHide;
	void SetWindowSize();
	void EndSelection(int nMessage);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LPOPUPPAN_H__98C712AC_E90B_41DD_AA28_30F0F4057134__INCLUDED_)
