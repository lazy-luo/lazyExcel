// LEditCtrl.h: interface for the CLEditCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEDITCTRL_H__1A7428AF_D8AA_4EC1_ACF9_10B01E201DEF__INCLUDED_)
#define AFX_LEDITCTRL_H__1A7428AF_D8AA_4EC1_ACF9_10B01E201DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../../../LComm/Interface.h"

#define LZY_MSG_CTLCOLOR	WM_USER+10023
#define PROP_CTRL	"^&(*)*df)(IKJ"
class CLEditCtrl : public IInPlaceCtrl
{
private:
	void OnKeyDown(WPARAM wParam,LPARAM lParam,BOOL& bReturn);
	BOOL Create(RECT& rct,HWND hParent=NULL);
	HWND m_hWnd;
	HWND m_hParent;
	LONG	m_lngOldProc;
	HBRUSH m_hBrush;
	COLORREF m_clrFore;
	COLORREF m_clrBk;
	HFONT m_fontDefault;
public:
	CLEditCtrl(HWND hParent=NULL);
	virtual ~CLEditCtrl();
	virtual void SetForeColor(COLORREF clr);
	virtual void setFont(HFONT hFont);
	virtual void setBkColor(COLORREF clr);
	virtual void setVisible(BOOL bShow);
	virtual BOOL getVisible();
	virtual LONG getLongValue();
	virtual LPTSTR getStringValue();
	virtual LPTSTR getTag();
	virtual LRESULT SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam);
	virtual void setLongValue(LONG nVal);
	virtual void setStringValue(LPTSTR ptrV);
	virtual void setTag(LPTSTR ptrV);
	virtual void setPosition(LONG nLeft,LONG nTop,LONG nRight,LONG nBottom);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_LEDITCTRL_H__1A7428AF_D8AA_4EC1_ACF9_10B01E201DEF__INCLUDED_)
