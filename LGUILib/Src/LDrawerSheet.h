//////////////////////////////////////////////////////////////////////
//@模块		 ：工作表绘制定义类
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LDRAWERSHEET_H__EE5C926D_1466_4180_840C_8664FBA60542__INCLUDED_)
#define AFX_LDRAWERSHEET_H__EE5C926D_1466_4180_840C_8664FBA60542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Base/LDrawItem.h"
#include "LToolTip.h"
#include "../Public/LGUIPublic.h"
#include "../Interface/LGUIInterface.h"
class GUI_EXPORT_CLASS CLDrawerSheet : public IDrawItem,public IDirectDraw
{
	friend class CLPrintDC;
private:
	void DrawCashCell(CELLITEMDRAWER &cellDrawer,char* pTxt,CLFont* pFont,BOOL bHeader,const RECT &rect);
	void DrawSelectCELL(LPHDC pDC,const RANGE& range,const CELL& cell);
	void ModifyFocusCellRect(const RANGE& range,const CELL& cell,RECT& rctClip);
	void GetClipRect(RECT& rct);
	void FillNoClientArea(LPHDC pDC,const RECT& rctAll);
	void DrawClientArea(LPHDC pDC,const RECT& rctAll);
	void DrawGridLine(LPHDC pDC,const RECT& rct,LONG begin,
		LONG end,LONG beginPos,LONG offset=0,BOOL bVert=TRUE);
	void DrawACell(CELLITEMDRAWER& cellDrawer,const RECT& rctAll);
	void DrawFreezeCells(LPHDC pDC,const RECT& rctAll);
	void DrawFixedCells(LPHDC pDC,const RECT& rctAll);
	void DrawFreeeLine(LPHDC pDC);
	void SetSizeInfo(const RECT &rct);
	LONG GetPageCount(const SIZE& pgSize);
	LPTSTR GetSheetName(void);
	CLCSWrapper     sm_CritSec;	//同步对象
	IGrid*	m_ptrGrid;
	ISheet*	m_ptrSheet;
	ITable*	m_ptrTable;
	CLToolTip	m_ttip;
	float	m_scaleX;
	float   m_scaleY;
	void DrawVertLine(LPHDC pDC,const RECT& rctAll);
	void DrawHorzLine(LPHDC pDC,const RECT& rctAll);
	void DrawGridLine(LPHDC pDC,const RECT& rctAll);
public:
	virtual void ShowToolTip(LPHDC pDC,LPTSTR ptrTip,BOOL bShow=TRUE);
	__inline void SetScale(float xscale,float yscale){m_scaleX=xscale;m_scaleY=yscale;};
	virtual void DrawDragRange(LPHDC pDC,const RANGE& rangeOld,const RANGE& range);
	virtual void DrawSelectRange(LPHDC pDC,BOOL bRestoryOld=FALSE,BOOL bIsFocusCell=FALSE);
	virtual void DrawFocusCell(LPHDC pDC,LPCELL pCellCur=NULL,LPCELL pCellOld=NULL);
	virtual void OnPrint(LPHDC pDC,const RECT& rct);
	CLDrawerSheet(ISheet* ptrSheet=NULL);
	virtual ~CLDrawerSheet();
	virtual void OnDraw(LPHDC pDC,const RECT& rct);
	
	
	void AttachSheet(ISheet* ptrSheet);
};

#endif // !defined(AFX_LDRAWERSHEET_H__EE5C926D_1466_4180_840C_8664FBA60542__INCLUDED_)
