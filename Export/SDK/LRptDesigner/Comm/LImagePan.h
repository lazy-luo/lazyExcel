// LImagePan.h: interface for the CLImagePan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LImagePAN_H__1C19B565_0CA9_4CAE_80F8_12D418D63432__INCLUDED_)
#define AFX_LImagePAN_H__1C19B565_0CA9_4CAE_80F8_12D418D63432__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lpopuppan.h"
typedef struct {
    LONG		nIndex;
	LONG		nImageID;
    TCHAR		*szName;
} ImageTableEntry;

class CLImagePan : public CLPopupPan  
{
public:
	CLImagePan(CPoint p, LONG nDefaultValue,
		CWnd* pParentWnd,LONG nRow,LONG nCol,ImageTableEntry*	pBorders);
	virtual ~CLImagePan();

	virtual void ShowToolTips(LPMSG lpMsg);
	virtual void OnMouseOver(UINT nFlags, CPoint point);
	virtual void OnMouseOut();
	virtual void GetWindowSize(CRect& rct);
	virtual void Initialise();
	virtual void OnDraw(CDC* pDC,const RECT& rctClip);
	virtual void CreateToolTips();	

	void FindCellFromValue(LONG nVal);
    LONG GetImage(int nIndex)              
	{
		ASSERT(m_pBorders!=NULL);
		return m_pBorders[nIndex].nIndex; 
	}
    LPCTSTR GetImageName(int nIndex)           
	{ 
		ASSERT(m_pBorders!=NULL);
		return m_pBorders[nIndex].szName; 
	}
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

private:
	LONG GetImageID(int nIndex);
	LONG m_nValue,m_nInitialValue;
	ImageTableEntry*	m_pBorders;
	CToolTipCtrl   m_ToolTip;
	int            m_nNumImages;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenImageSel;
    CRect          m_WindowRect;
	void DrawTransInvertPic(HDC hDstDC, INT nXDest, INT nYDest, 
									 INT nWidth,INT nHeight, HBITMAP bmp, 
									 INT nXSrc=0, INT nYSrc=0,COLORREF bgcolor=GetSysColor(COLOR_BTNFACE));
	void DrawTransPic(CDC* pDC, CBitmap* pBitmap, int X, int Y,BOOL bInvert);
	void ChangeSelection(int nIndex);
	void DrawCell(CDC* pDC, int nIndex,BOOL bMouseOut=FALSE);
	BOOL GetCellRect(int nIndex, const LPRECT& rect);
	virtual LPVOID GetSelectValue(int& nMessage);
};

#endif // !defined(AFX_LBORDERLINEPAN_H__1C19B565_0CA9_4CAE_80F8_12D418D63432__INCLUDED_)
