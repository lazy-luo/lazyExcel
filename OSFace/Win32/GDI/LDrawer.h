//////////////////////////////////////////////////////////////////////
//@模块		 ：可跨平台绘图引擎定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LDRAWER_H__45879FE3_3BDB_4FC6_B7FC_DFB1B5183FE5__INCLUDED_)
#define AFX_LDRAWER_H__45879FE3_3BDB_4FC6_B7FC_DFB1B5183FE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//绘图场景结构

typedef struct _tag_GDI
{
	HDC		m_hDC;			//设备DC
	RECT	m_Rect;		//当前作图区域尺寸
	operator =(_tag_GDI dst){
		m_hDC=dst.m_hDC;
		m_Rect=dst.m_Rect;
	}
	_tag_GDI():m_hDC(NULL){}
}GDI,*LPGDI;
/*
typedef struct _tagDrawer
{
	HDC		m_hDC;			//设备DC
	RECT	m_Rect;		//当前作图区域尺寸
	LONG	m_nCurrPageNO;	//当前页
	BOOL	m_bIsPrinting;	//是否为打印
	operator =(_tagDrawer dst){
		m_hDC=dst.m_hDC;
		m_nCurrPageNO=dst.m_nCurrPageNO;
		m_bIsPrinting=dst.m_bIsPrinting;
		m_Rect=dst.m_Rect;
	}
	_tagDrawer():m_hDC(NULL),m_nCurrPageNO(1),
		m_bIsPrinting(FALSE){
		m_Rect.left=0;
		m_Rect.top=0;
		m_Rect.right=0;
		m_Rect.bottom=0;
	}
}DRAWER,*LPDRAWER;
*/
class CLDrawer  
{
public:
	static void Draw3DText(HDC hDC,HFONT hFont,const LPTSTR ptrTxt
		,const RECT& rct,COLORREF clrFill,BOOL bRaise=FALSE,
		BOOL bFill=TRUE,COLORREF clrFace=GetSysColor(COLOR_3DLIGHT),
		COLORREF clrShadow=GetSysColor(COLOR_3DDKSHADOW));
	static HBITMAP LoadBitmap(LONG resid);
	static void DrawMemoFlag(HDC hDC, LPRECT lpRct, COLORREF clr);
	static void DrawBitmap(HDC hDC,LONG x,LONG y,HBITMAP hbmp,LONG cx,LONG cy);
	static void DrawBitmap(HDC hDC,POINT& ptStart,HBITMAP hbmp,SIZE& size);
	static HBITMAP GetBitmap(LPTSTR ptrName);
	static void DeleteBitmap(HBITMAP hbmp);
	static INT	CombineRgn(HRGN rgnDst,HRGN rgnS1,HRGN rgnS2,int style);
	static void DrawArrButton(HDC hDC, LPRECT lpRct,COLORREF clrBar, 
		LONG nArrDirection,BOOL bRaise=TRUE,BOOL bStyle=STYLE_3D_LOOK);
	static void DrawerLine(HDC hDC,int xsrc,int ysrc,int xdst,int ydst,COLORREF clr);
	static void DrawerALine(HDC hDC,int xsrc,int ysrc,int xdst,int ydst,COLORREF clr
		,BOOL bHorz=TRUE,int wid=1,BOOL bDot=FALSE);
	static BOOL LineTo(HDC hDC, int x, int y);
	static BOOL MoveToEx(HDC hDC, int x, int y, LPPOINT lppt);
	static void SetClipBox(HDC hDC,const RECT& rctNew,RECT& rctOld);
	static HPEN SelectPen(HDC hDC,HPEN hPen);
	static void DeletePen(HPEN hPen);
	static HPEN CreatePen(INT style,INT wid,COLORREF clr);
	static BOOL PtInRect(const RECT* prct,POINT pt);
	static HBRUSH SelectBrush(HDC hDC,HBRUSH hBrush);
	static LONG GetTextWidth(HDC hDC,LPTSTR ptrTxt,SIZE& sizeRet);
	static LONG GetTextWidth(LPTSTR ptrTxt);
	static BOOL PtInRegion(HRGN hrgn, INT ptx, INT pty);
	static INT DrawText(HDC hDC,LPCTSTR lpString,INT nCount,LPRECT lpRect,UINT uFormat,BOOL bTrans=FALSE);
	static COLORREF SetTextColor(HDC hDC,COLORREF clr);
	static HFONT SelectFont(HDC hDC,HFONT hFont);
	static void DeleteBrush(HBRUSH hBrush);
	static INT SetBkMode(HDC hDC,INT style);
	static BOOL FrameRgn(HDC hDC,HRGN hrgn,HBRUSH hBrush,INT wid,INT hei);
	static void FrameRect(HDC hDC,const RECT& rct,COLORREF clrFill,COLORREF clrBorder,BOOL bFill=TRUE);
	static BOOL FillRgn(HDC hDC,HRGN hrgn,HBRUSH hBrush);
	static HBRUSH CreateSolidBrush(COLORREF clr);
	static void DeleteRgn(HRGN hrgn);
	static void InvertRect(HDC hDC,const RECT& rct,COLORREF clrM);
	static void DeleteFont(HFONT hFont);
	static HFONT CreateFontIndirect(const LOGFONT* lgFont);
	static HRGN CreatePolygonRgn(const POINT* ptArr,INT nLen,INT nMode);
	static void DrawArrow(HDC hDC,const RECT& rct,COLORREF clr,
		LONG bDirect,BOOL bHasEndLine=FALSE,BOOL bEnable=TRUE);
	static HRGN CreateRectRgn(const RECT& rct);
	static void DrawDitherBorder(HDC hDC,LPRECT lpRct,LONG nWidth,LONG nHeight);
	static void DrawRangeBorder(HDC hDC,LPRECT lpRct,COLORREF clrFocus);
	static void DrawRangeBorder(HDC hDC,HRGN hrgn,COLORREF clrFocus);
	static void DrawBorder(HDC hDC,LPRECT lpRct,COLORREF clrFocus);
	static void FillARect(HDC hDC, LPRECT lpRct, HBRUSH hBrush);
	static HBRUSH HBrushDitherCreate(COLORREF rgbFace, COLORREF rgbHilight);
	static void SetFocus(HDC hDC,HRGN hrgn,BOOL bFillArea,
		COLORREF clrFocus,BOOL bAddFocusRect=TRUE,BOOL bSelectMode=FALSE);
	static void DrawTrack(HDC hDC,int nWid, LPPOINT lpTL, LPPOINT lpRB,BOOL bVert=TRUE);
	static void DrawThickRect(HDC hDC, LPRECT lpRct, COLORREF clr, 
		BOOL bRaise=TRUE,BOOL bFill=TRUE,BOOL b3DFlat=FALSE);
	static void FillSolidRect(HDC hDC,LPCRECT lpRect, COLORREF clr);
	static void FillSolidRect(HDC hDC,int x, int y, int cx, int cy, COLORREF clr);
	static void Draw3dRect(HDC hDC,LPCRECT lpRect,COLORREF clrTopLeft, COLORREF clrBottomRight);
	static void Draw3dRect(HDC hDC,int x, int y, int cx, int cy,COLORREF clrTopLeft, COLORREF clrBottomRight);
private:
	CLDrawer();
	virtual ~CLDrawer();

};

#endif // !defined(AFX_LDRAWER_H__45879FE3_3BDB_4FC6_B7FC_DFB1B5183FE5__INCLUDED_)
