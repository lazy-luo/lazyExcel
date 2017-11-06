//////////////////////////////////////////////////////////////////////
//@模块		 ：滚动条对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-05
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LScrollBar.h"
#include "../../LComm/LMemDC.h"
#define MIN_TB_SIZE		8
#define MAX_DISTANCE	150

#define ID_SCROLLBAR_LEFTTOPBT		121
#define ID_SCROLLBAR_RIGHTBTBT		122
#define ID_SCROLLBAR_TB				123
#define ID_SCROLLBAR_FREE			124


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLScrollBar::CLScrollBar(IScrollable* ptrOuter,BOOL bHorz):m_ptrOuter(ptrOuter),m_bIsHorz(bHorz),m_pArea(NULL),m_bActive(TRUE),
	m_bLTBDown(FALSE),m_bRBBDown(FALSE),m_bLTBRaise(TRUE),m_bRBBRaise(TRUE),m_bTBtDown(FALSE),
	m_bFreeBtDown(FALSE),m_dblScal(1),m_dblValue(0),m_bLeftTpEnd(TRUE),m_bRightBtEnd(FALSE),m_PtOffset(0),
	m_bInLTFreeArea(FALSE),m_clrBk(COLOR_SCROLL_BAR),m_lngExists(0)
{
#ifdef _LZY_USE_DOUBLE_BUFF_
	m_sizeOld=-1;
#endif
	CLPlatform::ClearRect(m_rctLTB);
	CLPlatform::ClearRect(m_rctRBB);
	CLPlatform::ClearRect(m_rctTB);
	CLPlatform::ClearRect(m_rctAll);
	CLPlatform::ClearPoint(m_beginPosCur);
	CLPlatform::ClearPoint(m_ptStartDraw);
}

CLScrollBar::~CLScrollBar()
{
	if(m_pArea)
		delete m_pArea;
}
BOOL CLScrollBar::IsHorz()
{
	return m_bIsHorz;
}
void CLScrollBar::OnDraw(LPHDC pDC,const RECT& rct)
{
	ASSERT(pDC->pParam);
	LPSCROLLINFOEXT ptrInfo=(LPSCROLLINFOEXT)pDC->pParam;
	RECT rect=rct;
	SetDrawRect(rect);
#ifdef _LZY_USE_DOUBLE_BUFF_
	m_ptStartDraw.x=m_beginPosCur.x+rct.left;
	m_ptStartDraw.y=m_beginPosCur.y+rct.top;
	CLMemDC hDC(pDC->hDC,rect);
	HDC holdDC=pDC->hDC;
	pDC->hDC=hDC;
#endif
	DrawScrollBar(pDC->hDC,ptrInfo,rect);
#ifdef _LZY_USE_DOUBLE_BUFF_
	pDC->hDC=holdDC;
#endif
	
}

void CLScrollBar::DrawScrollBar(HDC hDC, LPSCROLLINFOEXT pInfo,const RECT& rct)
{
	ASSERT(pInfo);
	m_rctAll=rct;
	
	CLClipDC cDC(hDC,m_rctAll);
	if(!GetScrollBarPart(pInfo)){
		ASSERT(FALSE);
		return;
	}
	LONG nSize=m_bIsHorz?(rct.right-rct.left)/2:(rct.bottom-rct.top)/2;
	//填充背景色
	if(nSize>16){
		HBRUSH hBrush=CLDrawer::HBrushDitherCreate(m_clrBk,RGB(255,255,255));
		RECT rctFill=m_rctLTB;
#ifdef _LZY_USE_DOUBLE_BUFF_
		//LONG vAlingn=8;
		//LONG val;
		if(m_bIsHorz){
			rctFill.left=rctFill.right;
			rctFill.right=m_rctRBB.left;
		}else{
			rctFill.top=rctFill.bottom;
			rctFill.bottom=m_rctRBB.top;
		}
		/*
		if(m_sizeOld==-1){
			if(m_bIsHorz)
				m_sizeOld=(rctFill.right-rctFill.left)%vAlingn;
			else
				m_sizeOld=(rctFill.bottom-rctFill.top)%vAlingn;
		}else{
			val=(m_sizeOld-(m_bIsHorz?(rctFill.right-rctFill.left):
				(rctFill.bottom-rctFill.top))%vAlingn);
			if(val!=0){
				if(m_bIsHorz){
					rctFill.left-=(val>0?val:vAlingn+val);
				}else{
					rctFill.top-=(val>0?val:vAlingn+val);
				}
			}
		}
		CLPlatform::DebugMsg("Size=%d,REL_SIZE=%d\n",m_sizeOld,(m_bIsHorz?(rctFill.right-rctFill.left):(rctFill.bottom-rctFill.top))%vAlingn);
		*/
		 CLDrawer::FillARect(hDC,&rctFill,hBrush);
#else
		if(m_bIsHorz){
			rctFill.left=rctFill.right;
			rctFill.right=m_rctTB.left;
		}else{
			rctFill.top=rctFill.bottom;
			rctFill.bottom=m_rctTB.top;
		}
		HRGN hrgn=CreateRectRgn(rctFill.left,rctFill.top,rctFill.right,rctFill.bottom);
		rctFill=m_rctTB;
		if(m_bIsHorz){
			rctFill.left=rctFill.right;
			rctFill.right=m_rctRBB.left;
		}else{
			rctFill.top=rctFill.bottom;
			rctFill.bottom=m_rctRBB.top;
		}
		HRGN hrgnL=CreateRectRgn(rctFill.left,rctFill.top,rctFill.right,rctFill.bottom);
		CombineRgn(hrgn,hrgn,hrgnL,RGN_OR);
		CLDrawer::DeleteRgn(hrgnL);
		CLDrawer::FillRgn(hDC,hrgn,hBrush);
		CLDrawer::DeleteRgn(hrgn);
#endif
		CLDrawer::DeleteBrush(hBrush);
	}
	//画两边按钮
	if(nSize<2)return ;
	if(nSize<SCROLLBAR_SIZE){
		if(m_bIsHorz){
			m_rctLTB.right=m_rctLTB.left+nSize;
			m_rctRBB.left=m_rctLTB.right;
			m_rctRBB.right=m_rctRBB.left+nSize;
		}else{
			m_rctLTB.bottom=m_rctLTB.top+nSize;
			m_rctRBB.top=m_rctLTB.bottom;
			m_rctRBB.bottom=m_rctRBB.top+nSize;
		}
	}
	CLDrawer::DrawArrButton(hDC,&m_rctLTB,m_clrBk,
		m_bIsHorz?ARROW_LEFT:ARROW_UP,m_bLTBRaise);
	//画右边Button
	CLDrawer::DrawArrButton(hDC,&m_rctRBB,m_clrBk,
		m_bIsHorz?ARROW_RIGHT:ARROW_DOWN,m_bRBBRaise);
	//画滑动块
	if((m_bIsHorz?rct.right-rct.left:rct.bottom-rct.top)-2*SCROLLBAR_SIZE>MIN_TB_SIZE){
		CLDrawer::DrawThickRect(hDC,&m_rctTB,m_clrBk);
	}else{
		HBRUSH hBrush=CLDrawer::HBrushDitherCreate(m_clrBk,RGB(255,255,255));
		RECT rctFill=m_rctLTB;
		if(m_bIsHorz){
			rctFill.left=rctFill.right;
			rctFill.right=m_rctRBB.left-1;
		}else{
			rctFill.top=rctFill.bottom;
			rctFill.bottom=m_rctRBB.top-1;
		}
		CLDrawer::FillARect(hDC,&rctFill,hBrush);
		CLDrawer::DeleteBrush(hBrush);
	}
}

BOOL CLScrollBar::GetScrollBarPart(LPSCROLLINFOEXT pInfo)
{
	ASSERT(pInfo);
	m_bLeftTpEnd=FALSE;
	m_bRightBtEnd=FALSE;
	DOUBLE dblTotlWidth=m_rctAll.right-m_rctAll.left;
	DOUBLE dblTotlHeight=m_rctAll.bottom-m_rctAll.top;
	//计算滑动块大小
	DOUBLE dblLenTb=((m_bIsHorz?dblTotlWidth:dblTotlHeight)-2*SCROLLBAR_SIZE)*pInfo->m_nExistValue/pInfo->m_nMaxValue;
	//计算滑动块位置
	if(dblLenTb<MIN_TB_SIZE)dblLenTb=MIN_TB_SIZE;
	DOUBLE dblOffset=((m_bIsHorz?dblTotlWidth:dblTotlHeight)-2*SCROLLBAR_SIZE-dblLenTb)*(pInfo->m_nCurrValue+pInfo->m_nVirtualValue)/(pInfo->m_nMaxValue-pInfo->m_nExistValue);
	m_dblScal=(DOUBLE)(pInfo->m_nMaxValue-pInfo->m_nExistValue)/((m_bIsHorz?dblTotlWidth:dblTotlHeight)-2*SCROLLBAR_SIZE-dblLenTb);
	
	m_rctLTB=m_rctAll;
	if(m_bIsHorz){
		m_rctLTB.right=m_rctLTB.left+SCROLLBAR_SIZE;
		m_rctTB=m_rctLTB;
		m_rctTB.left=m_rctLTB.right+(LONG)dblOffset;
		m_rctTB.right=m_rctTB.left+(LONG)dblLenTb/*m_rctLTB.right+(LONG)(dblOffset+dblLenTb)*/;
		m_rctRBB=m_rctAll;
		m_rctRBB.left=m_rctRBB.right-SCROLLBAR_SIZE;
		
		if(pInfo->m_nCurrValue+pInfo->m_nVirtualValue>=pInfo->m_nMaxValue-pInfo->m_nExistValue){
			m_bRightBtEnd=TRUE;
			m_rctTB.right=m_rctRBB.left;
			m_rctTB.left=m_rctTB.right-(LONG)dblLenTb;
			pInfo->m_nCurrValue=pInfo->m_nMaxValue-pInfo->m_nExistValue;
		}
		if(pInfo->m_nCurrValue+pInfo->m_nVirtualValue<=0){
			m_bLeftTpEnd=TRUE;
			pInfo->m_nCurrValue=0;
		}
	}else{
		m_rctLTB.bottom=m_rctLTB.top+SCROLLBAR_SIZE;
		m_rctTB=m_rctLTB;
		m_rctTB.top=m_rctLTB.bottom+(LONG)dblOffset;
		m_rctTB.bottom=m_rctTB.top+(LONG)dblLenTb;/*m_rctLTB.bottom+(LONG)(dblOffset+dblLenTb)*/;
		m_rctRBB=m_rctAll;
		m_rctRBB.top=m_rctRBB.bottom-SCROLLBAR_SIZE;
		
		if(pInfo->m_nCurrValue+pInfo->m_nVirtualValue>=pInfo->m_nMaxValue-pInfo->m_nExistValue){
			m_bRightBtEnd=TRUE;
			m_rctTB.bottom=m_rctRBB.top;
			m_rctTB.top=m_rctTB.bottom-(LONG)dblLenTb;
			pInfo->m_nCurrValue=pInfo->m_nMaxValue-pInfo->m_nExistValue;
		}
		if(pInfo->m_nCurrValue+pInfo->m_nVirtualValue<=0){
			m_bLeftTpEnd=TRUE;
			pInfo->m_nCurrValue=0;
		}
	}
	return TRUE;
}

void CLScrollBar::OnMouseMove(LONG idArea,MOUSESTATUS& nstatus)
{
	POINT pt;
	pt.x=nstatus.posx-m_ptStartDraw.x;
	pt.y=nstatus.posy-m_ptStartDraw.y;
	switch(idArea){
	case ID_SCROLLBAR_LEFTTOPBT:
		if(nstatus.bMouseIN && m_bLTBRaise && m_bLTBDown){
			m_bLTBRaise=FALSE;
			//OnScroll(-1);
			Redraw();
		}
		break;
	case ID_SCROLLBAR_RIGHTBTBT:
		if(nstatus.bMouseIN && m_bRBBRaise && m_bRBBDown){
			m_bRBBRaise=FALSE;
			//OnScroll(1);
			Redraw();
		}
		break;
	case ID_SCROLLBAR_TB:
		if(m_bTBtDown){
			RECT rct=m_rctTB;
			LONG def=0;
			DOUBLE dblV=0;
			if(m_bIsHorz){
				if(pt.x<m_rctLTB.left)pt.x=m_rctLTB.left; 
				if(pt.x>m_rctRBB.left)pt.x=m_rctRBB.left;
				//if(pt.x>=m_rctLTB.left && pt.x<=m_rctRBB.left){
					def=pt.x-m_ptTrack.x;
					if(def!=0){
						if(abs(pt.y-rct.bottom)<MAX_DISTANCE 
							|| abs(rct.top-pt.y)<MAX_DISTANCE){
							dblV=def*m_dblScal+m_dblValue;
							m_dblValue=dblV-(DOUBLE)((LONG)dblV);
							m_lngExists=OnScroll((DLONG)(dblV+m_lngExists),TRUE);
							if(!m_bLeftTpEnd && !m_bRightBtEnd){
								m_ptTrack.x+=def;/*m_rctTB.left+m_PtOffset;*/
								m_ptTrack.y=pt.y;
							}
						}
					}
				//}
			}else{
				if(pt.y<m_rctLTB.top)pt.y=m_rctLTB.top; 
				if(pt.y>m_rctRBB.top)pt.y=m_rctRBB.top;
				//if(pt.y>=m_rctLTB.top && pt.y<=m_rctRBB.top){
					def=pt.y-m_ptTrack.y;
					if(def!=0){
						if(abs(pt.x-rct.right)<MAX_DISTANCE 
							|| abs(pt.x-rct.left)<MAX_DISTANCE){
							dblV=def*m_dblScal+m_dblValue;
							m_dblValue=dblV-(DOUBLE)((LONG)dblV);
							m_lngExists=OnScroll((DLONG)(dblV+m_lngExists),TRUE);
							if(!m_bLeftTpEnd && !m_bRightBtEnd){
								m_ptTrack.x=pt.x;
								
								m_ptTrack.y+=def;/*m_rctTB.top+m_PtOffset;*/
							}
						}
					}
				//}
			}
		}
		break;
	case ID_SCROLLBAR_FREE:
		/*
		if(nstatus.bMouseIN && m_bFreeBtDown){
			BOOL bIn=isPtInLeftTopFreeArea(nstatus.posx,nstatus.posy);
			if(m_bInLTFreeArea==bIn){
				OnScroll(m_bInLTFreeArea?-10:10);
			}
		}*/
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void CLScrollBar::OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus) 
{
	switch(idArea){
	case ID_SCROLLBAR_LEFTTOPBT:
		if(!m_bLTBRaise && m_bLTBDown){
			m_bLTBRaise=TRUE;
			Redraw();
		}
		break;
	case ID_SCROLLBAR_RIGHTBTBT:
		if(!m_bRBBRaise && m_bRBBDown){
			m_bRBBRaise=TRUE;
			Redraw();
		}
		break;
	case ID_SCROLLBAR_TB:
		break;
	case ID_SCROLLBAR_FREE:
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void CLScrollBar::OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus) 
{
	switch(idArea){
	case ID_SCROLLBAR_LEFTTOPBT:
		if(nstatus.bMouseIN){
			m_bLTBDown=TRUE;
			m_bLTBRaise=FALSE;
			OnScroll(-1);
		}
		break;
	case ID_SCROLLBAR_RIGHTBTBT:
		if(nstatus.bMouseIN){
			m_bRBBDown=TRUE;
			m_bRBBRaise=FALSE;
			OnScroll(1);
		}
		break;
	case ID_SCROLLBAR_TB:
		if(nstatus.bMouseIN && 
			nstatus.nStatusParam==STATUS_FLAG_AUTO){
			m_ptTrack.x=nstatus.posx-m_ptStartDraw.x;
			m_ptTrack.y=nstatus.posy-m_ptStartDraw.y;
			if(m_bIsHorz){
				m_PtOffset=m_ptTrack.x-m_rctTB.left;
			}else{
				m_PtOffset=m_ptTrack.y-m_rctTB.top;
			}
			m_bTBtDown=TRUE;
		}
		break;
	case ID_SCROLLBAR_FREE:
		if(nstatus.bMouseIN){
			if(nstatus.nStatusParam==STATUS_FLAG_AUTO){
				m_bInLTFreeArea=isPtInLeftTopFreeArea(nstatus.posx-m_ptStartDraw.x,nstatus.posy-m_ptStartDraw.y);
				m_bFreeBtDown=TRUE;
				OnScroll(m_bInLTFreeArea?-2:2);
			}else{
				BOOL bIn=isPtInLeftTopFreeArea(nstatus.posx-m_ptStartDraw.x,nstatus.posy-m_ptStartDraw.y);
				if(m_bInLTFreeArea==bIn){
					OnScroll(m_bInLTFreeArea?-2:2);
				}
			}
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

void CLScrollBar::OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus) 
{
	switch(idArea){
	case ID_SCROLLBAR_LEFTTOPBT:
		m_bLTBDown=FALSE;
		m_bLTBRaise=TRUE;
		Redraw();
		break;
	case ID_SCROLLBAR_RIGHTBTBT:
		m_bRBBDown=FALSE;
		m_bRBBRaise=TRUE;
		Redraw();
		break;
	case ID_SCROLLBAR_TB:
		m_bTBtDown=FALSE;
		m_lngExists=0;
		if(m_ptrOuter)
			m_ptrOuter->StopExtendTrack(m_bIsHorz);
		m_dblValue=0;
		m_PtOffset=0;
		break;
	case ID_SCROLLBAR_FREE:
		m_bFreeBtDown=FALSE;
		m_bInLTFreeArea=FALSE;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void CLScrollBar::Redraw()
{
	if(m_ptrOuter)
		m_ptrOuter->RedrawScrollBar(this);
}
void CLScrollBar::OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus) 
{
	
}
void CLScrollBar::OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus) 
{
	
}

void CLScrollBar::OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus) 
{
	
}
void CLScrollBar::OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus) 
{
	
}
void CLScrollBar::OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus) 
{
	OnScroll(nstatus.nParam?3:-3);
}
BOOL CLScrollBar::GetRect(LONG idArea,RECT& rct) 
{
	if(IsEmptyRect(m_rctAll))return FALSE;
	switch(idArea){
	case ID_SCROLLBAR_LEFTTOPBT:
		rct=m_rctLTB;
		break;
	case ID_SCROLLBAR_RIGHTBTBT:
		rct=m_rctRBB;
		break;
	case ID_SCROLLBAR_TB:
		rct=m_rctTB;
		break;
	default:
		ASSERT(FALSE);
		return FALSE;
	}
	rct.left+=m_ptStartDraw.x;
	rct.right+=m_ptStartDraw.x;
	rct.top+=m_ptStartDraw.y;
	rct.bottom+=m_ptStartDraw.y;
	return TRUE;
}
BOOL CLScrollBar::GetRgn(LONG idArea,HRGN& hrgn)
{
	if(idArea==ID_SCROLLBAR_FREE){
		if(IsEmptyRect(m_rctAll))return FALSE;
		RECT rct=m_rctLTB;
		if(m_bIsHorz){
			rct.left=rct.right;
			rct.right=m_rctTB.left;
		}else{
			rct.top=rct.bottom;
			rct.bottom=m_rctTB.top;
		}
		rct.left+=m_ptStartDraw.x;
		rct.right+=m_ptStartDraw.x;
		rct.top+=m_ptStartDraw.y;
		rct.bottom+=m_ptStartDraw.y;
		HRGN hrgnT=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
		rct=m_rctRBB;
		if(m_bIsHorz){
			rct.right=rct.left;
			rct.left=m_rctTB.right;
		}else{
			rct.bottom=rct.top;
			rct.top=m_rctTB.bottom;
		}
		rct.left+=m_ptStartDraw.x;
		rct.right+=m_ptStartDraw.x;
		rct.top+=m_ptStartDraw.y;
		rct.bottom+=m_ptStartDraw.y;
		hrgn=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
		CombineRgn(hrgn,hrgn,hrgnT,RGN_OR);
		CLDrawer::DeleteRgn(hrgnT);
		return TRUE;
	}else{
		ASSERT(FALSE);
		return FALSE;
	}
}
LPIDAREA CLScrollBar::GetAreaIDs() 
{
	if(m_pArea)return m_pArea;
	m_pArea=new IDAREA();
	m_pArea->lngID=ID_SCROLLBAR_LEFTTOPBT;
	m_pArea->ptrNext=new IDAREA();
	LPIDAREA ptr=m_pArea->ptrNext;
	ptr->lngID=ID_SCROLLBAR_RIGHTBTBT;
	
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=ID_SCROLLBAR_TB;
	
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=ID_SCROLLBAR_FREE;
	ptr->bRect=FALSE;

	return m_pArea;
}
BOOL CLScrollBar::IsActive()
{
	return m_bActive;
}

BOOL CLScrollBar::IsEmptyRect(const RECT &rct)
{
	return (rct.top==0 && rct.left==0 && rct.right==0 && rct.bottom==0);
}

LONG CLScrollBar::OnScroll(DLONG val, BOOL bPixel)
{
	if(m_ptrOuter){
		if(m_bIsHorz)
			return m_ptrOuter->ScrollHorz(this,val,bPixel);
		else
			return m_ptrOuter->ScrollVert(this,val,bPixel);
	}
	return 0;
}

BOOL CLScrollBar::isPtInLeftTopFreeArea(INT x,INT y)
{
	if(m_bIsHorz)
		return (x>m_rctLTB.right && x<m_rctTB.left && 
			y>=m_rctLTB.top && y<=m_rctLTB.bottom);
	else
		return (x>=m_rctLTB.left && x<=m_rctLTB.right && 
			y>m_rctLTB.bottom && y<m_rctTB.top);
}

void CLScrollBar::SetBkColor(COLORREF clr)
{
	m_clrBk=clr;
}

COLORREF CLScrollBar::GetBkColor()
{
	return m_clrBk;
}
