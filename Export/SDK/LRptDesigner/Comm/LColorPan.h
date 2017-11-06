///////////////////////////////////////////////////////////////////////////////////////////////
//@模块		:	颜色选择菜单
//@作者		:	罗智勇
//@创建时间	:	2005-09-16
///////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCOLORPAN_H__CA0EE82C_229D_4A73_AD4A_375FE69FB8B3__INCLUDED_)
#define AFX_LCOLORPAN_H__CA0EE82C_229D_4A73_AD4A_375FE69FB8B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LPopupPan.h"
#include "LTooltip.h"	// Added by ClassView
typedef struct {
    COLORREF crColor;
    TCHAR    *szName;
} ColorTableEntry;

class CLColorPan : public CLPopupPan  
{
public:
	virtual void ShowToolTips(LPMSG lpMsg);
	virtual void OnMouseOver(UINT nFlags, CPoint point);
	virtual void OnMouseOut();
	virtual void GetWindowSize(CRect& rct);
	virtual void Initialise();
	virtual void OnDraw(CDC* pDC,const RECT& rctClip);
	virtual void CreateToolTips();
	CLColorPan(CPoint p, COLORREF pClr, CWnd* pParentWnd,
                 LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);
	virtual ~CLColorPan();
	

	void FindCellFromColor(COLORREF crColor);
    COLORREF GetColor(int nIndex)              { return m_crColors[nIndex].crColor; }
    LPCTSTR GetColorName(int nIndex)           { return m_crColors[nIndex].szName; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;
// Operations
protected:
	static ColorTableEntry m_crColors[];
	CLToolTip_D   m_ToolTip;
	int            m_nNumColors;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenColorSel;
    CString        m_strDefaultText;
    CString        m_strCustomText;
    CRect          m_CustomTextRect, m_DefaultTextRect, m_WindowRect;
    CFont          m_Font;
    CPalette       m_Palette;
    COLORREF       m_crInitialColor, m_crColor;
	
	
	void ChangeSelection(int nIndex);
	void DrawCell(CDC* pDC, int nIndex,BOOL bMouseOut=FALSE);
	BOOL GetCellRect(int nIndex, const LPRECT& rect);
	virtual LPVOID GetSelectValue(int& nMessage);

};

#endif // !defined(AFX_LCOLORPAN_H__CA0EE82C_229D_4A73_AD4A_375FE69FB8B3__INCLUDED_)
