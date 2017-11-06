//////////////////////////////////////////////////////////////////////
//@模块		 ：滚动条对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-05
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSCROLLBAR_H__EC8F83CD_426B_4024_8E0E_81606D41A93D__INCLUDED_)
#define AFX_LSCROLLBAR_H__EC8F83CD_426B_4024_8E0E_81606D41A93D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BASE/LDrawItem.h"
#include "../../LComm/LClipDC.h"
class CLScrollBar :public IDrawItem,public IMouseEvent ,public IScrollTyle
{
private:
	BOOL isPtInLeftTopFreeArea(INT x,INT y);
	LONG OnScroll(DLONG val,BOOL bPixel=FALSE);
	void Redraw();
	BOOL IsEmptyRect(const RECT& rct);
	BOOL GetScrollBarPart(LPSCROLLINFOEXT pInfo);
	void DrawScrollBar(HDC hDC,LPSCROLLINFOEXT pInfo,const RECT& rct);
	
	BOOL	m_bLTBDown;
	BOOL    m_bRBBDown;
	BOOL	m_bTBtDown;
	BOOL	m_bFreeBtDown;
	BOOL	m_bInLTFreeArea;//
	DLONG	m_lngExists;//像素滚动时遗留精度
	
#ifdef _LZY_USE_DOUBLE_BUFF_
	LONG	m_sizeOld;
#endif
	BOOL	m_bLTBRaise;
	BOOL	m_bRBBRaise;
	
	BOOL	m_bLeftTpEnd;
	BOOL	m_bRightBtEnd;
	LPIDAREA	m_pArea;
	BOOL	m_bActive;
	RECT m_rctAll;
	RECT m_rctLTB;
	RECT m_rctRBB;
	RECT m_rctTB;
	BOOL m_bIsHorz;
	
	DOUBLE  m_dblValue;//滚动值
	
	DOUBLE	m_dblScal;
	POINT	m_ptTrack;
	POINT	m_beginPosCur;
	POINT	m_ptStartDraw;
	LONG	m_PtOffset;
	
	COLORREF m_clrBk;
	
	CLCSWrapper sm_CritSec;
	IScrollable*	m_ptrOuter;
public:
	virtual BOOL IsHorz();
	COLORREF GetBkColor();
	void SetBkColor(COLORREF clr);
	virtual void OnDraw(LPHDC pDC,const RECT& rct);
	CLScrollBar(IScrollable* ptrOuter=NULL,BOOL bHorz=TRUE);
	virtual ~CLScrollBar();
	
	__inline void	SetScrollOwner(IScrollable* ptrOuter)
	{
		CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
		if(ptrOuter!=m_ptrOuter)
			m_ptrOuter=ptrOuter;
			
	}
	virtual void OnMouseMove(LONG idArea,MOUSESTATUS& nstatus);
	virtual void OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus);
	virtual BOOL GetRect(LONG idArea,RECT& rct);
	virtual BOOL GetRgn(LONG idArea,HRGN& hrgn);
	virtual LPIDAREA GetAreaIDs();
	virtual BOOL IsActive();
	__inline void IsActive(BOOL bval){m_bActive=bval;};
};

#endif // !defined(AFX_LSCROLLBAR_H__EC8F83CD_426B_4024_8E0E_81606D41A93D__INCLUDED_)
