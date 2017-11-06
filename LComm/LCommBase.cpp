//////////////////////////////////////////////////////////////////////
//@模块		 ：鼠标事件引擎
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LCommBase.h"

#define MOUSE_DOWN_TIME_ID		10002
#define MOUSE_DOWN_TIME_OUT		500

#define MOUSE_DOWN_TIMEEVENT_ID		10003
#define MOUSE_DOWN_TIMEEVENT_OUT	50


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IInterfaceMgrl*		g_pInterfaceManager=NULL;
CLMouseEventMgrl	g_nMouseEventMgrl;
EVENT_MAP	*g_pEventMap=NULL;
CLMouseEventMgrl::CLMouseEventMgrl():m_pCurrentObj(NULL),
	m_nCurID(0),m_ptrTimerCreator(NULL),m_iRaiseMouseDownTmr(0),
	m_iMouseDownTmr(0),m_bTrackIN(FALSE),m_pCurrArea(NULL),m_bLock(FALSE)
{
	
}

CLMouseEventMgrl::~CLMouseEventMgrl()
{
	ClearTimer();
}
void CLMouseEventMgrl::ClearToDefault()
{
	ClearTimer();
	m_pCurrentObj=NULL;
	m_nCurID=0;
	m_iRaiseMouseDownTmr=0;
	m_iMouseDownTmr=0;
	m_bTrackIN=FALSE;
	m_pCurrArea=NULL;
	m_bLock=FALSE;
}
void CLMouseEventMgrl::SetTopMostListener(LONG key,IMouseEvent* pobj,BOOL bForceNew)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(!pobj)return;
	IInterfaceMgrl* ptr=GET_LINK(key),*ptrParent=NULL,*ptrHead=NULL;
	ptrHead=ptr;
	BOOL bFind=FALSE;
	while(ptr){
		if(ptr->m_ptrEvent==pobj){
			if(ptrParent){
				ptrParent->m_ptrNext=ptr->m_ptrNext;
				ptr->m_ptrNext=g_pInterfaceManager;
				g_pInterfaceManager=ptr;
			}
			bFind=TRUE;
			break;
		}
		ptrParent=ptr;
		ptr=ptr->m_ptrNext;
	}
	if(!bFind && bForceNew){
		ptr=g_pInterfaceManager;
		g_pInterfaceManager=new IInterfaceMgrl((IMouseEvent*)pobj);
		g_pInterfaceManager->m_ptrNext=ptr;
	}
}
void CLMouseEventMgrl::RemoveListener(LONG key,IMouseEvent* pobj)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(!pobj)return;
	IInterfaceMgrl* ptr=GET_LINK(key),*ptrParent=NULL;
	while(ptr){
		if(ptr->m_ptrEvent==pobj){
			if(ptrParent){
				ptrParent->m_ptrNext=ptr->m_ptrNext;
			}else{
				ASSERT(ptr==g_pInterfaceManager);
				g_pInterfaceManager=ptr->m_ptrNext;
			}
			m_pCurrentObj=NULL;
			ptr->m_ptrNext=NULL;
			delete ptr;
			break;
		}
		ptrParent=ptr;
		ptr=ptr->m_ptrNext;
		
	}
}
void CLMouseEventMgrl::OnMouseMove(LONG key,LONG x,LONG y,INT status,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	IInterfaceMgrl* ptr=GET_LINK(key);
	ASSERT(ptr);
	if(!ptr)return;
	IMouseEvent* ptrEvent=NULL;
	BOOL bFind=FALSE;
	LPIDAREA	pidarea;
	RECT rct;
	POINT pt;
	pt.x=x;
	pt.y=y;
	HRGN hrgn=NULL;
	m_status.nButton=status;
	m_status.bIsLock=(status!=0);
	m_status.posx=x;
	m_status.posy=y;
	m_status.bMouseIN=FALSE;
	while(ptr){
		if(ptr->m_ptrEvent && ((IMouseEvent*)(ptr->m_ptrEvent))->IsActive()){
			ASSERT(ptr->m_ptrEvent);
			pidarea=ptr->m_ptrEvent->GetAreaIDs();
			while(pidarea){
				if(pidarea->bRect){
					if(ptr->m_ptrEvent->GetRect(pidarea->lngID,rct)){
						//是矩形区域
						if(CLDrawer::PtInRect(&rct,pt)){
							bFind=TRUE;
						}
					}
				}else{
					if(ptr->m_ptrEvent->GetRgn(pidarea->lngID,hrgn)){
						//是区域
						ASSERT(hrgn);
						if(CLDrawer::PtInRegion(hrgn,pt.x,pt.y)){
							bFind=TRUE;
						}
						CLDrawer::DeleteRgn(hrgn);
					}
				}
				if(bFind){
					if(m_pCurrentObj!=ptr->m_ptrEvent
						|| m_nCurID!=pidarea->lngID){
						
						if(m_pCurrentObj){
							if(m_status.bIsLock){
								if(m_bTrackIN){
									m_bTrackIN=FALSE;
									m_pCurrentObj->OnMouseOut(m_nCurID,m_status);
								}
							}else
								m_pCurrentObj->OnMouseOut(m_nCurID,m_status);
						}
						if(!m_status.bIsLock){
							m_pCurrArea=pidarea;
							m_pCurrentObj=ptr->m_ptrEvent;
							m_status.bMouseIN=TRUE;
							m_pCurrentObj->OnMouseMove(pidarea->lngID,m_status);
							m_nCurID=pidarea->lngID;
						}else{
							m_status.bMouseIN=FALSE;
							if(m_pCurrentObj)
								m_pCurrentObj->OnMouseMove(m_nCurID,m_status);
						}
						
					}else{
						m_status.bMouseIN=TRUE;
						if(m_status.bIsLock && !m_bTrackIN)
							m_bTrackIN=TRUE;
						//CLPlatform::DebugMsg("OnMouseMove [ID=%d]",m_nCurID);
						if(m_pCurrentObj)
							m_pCurrentObj->OnMouseMove(m_nCurID,m_status);
					}
					break;
				}
				pidarea=pidarea->ptrNext;
			}
			if(bFind){
				break;
			}
		}
		ptr=ptr->m_ptrNext;
	}
	if(!bFind && m_pCurrentObj){
		//很明显应该触发离开事件
		if(!m_status.bIsLock){
			m_pCurrentObj->OnMouseOut(m_nCurID,m_status);
			m_pCurrArea=NULL;
			m_pCurrentObj=NULL;
		}else{
			if(m_bTrackIN){
				m_bTrackIN=FALSE;
				m_pCurrentObj->OnMouseOut(m_nCurID,m_status);
			}else
				m_pCurrentObj->OnMouseMove(m_nCurID,m_status);
		}
	}
}
void CLMouseEventMgrl::OnLButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		m_pCurrentObj->OnLButtonDown(m_nCurID,m_status);
		m_bTrackIN=TRUE;
		if(m_ptrTimerCreator)
			m_iMouseDownTmr=m_ptrTimerCreator->CreateTimer(this,
					MOUSE_DOWN_TIME_OUT,MOUSE_DOWN_TIME_ID);
	}
}
void CLMouseEventMgrl::OnLButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		ClearTimer();
		m_pCurrentObj->OnLButtonUp(m_nCurID,m_status);
		m_bTrackIN=FALSE;
		if(!m_status.bMouseIN)
			m_pCurrentObj=NULL;
		m_status.bIsLock=FALSE;
	}
}
void CLMouseEventMgrl::OnRButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		m_pCurrentObj->OnLButtonDown(m_nCurID,m_status);
	}
}
void CLMouseEventMgrl::OnRButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		m_pCurrentObj->OnRButtonUp(m_nCurID,m_status);
	}
}
void CLMouseEventMgrl::OnMButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		m_pCurrentObj->OnMButtonDown(m_nCurID,m_status);
	}
}
void CLMouseEventMgrl::OnMButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_pCurrentObj){
		m_status.nStatusParam=STATUS_FLAG_AUTO;
		m_pCurrentObj->OnMButtonUp(m_nCurID,m_status);
	}
}
void CLMouseEventMgrl::OnMouseWheel(LONG key,LONG wParam,LONG lParam,BOOL& bCancel)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	short fwKeys = ((short)LOWORD((LONG)wParam));
	short zDelta = ((short)HIWORD(wParam));
	if((fwKeys & MK_LBUTTON) || (fwKeys & MK_RBUTTON)){
		return;
	}else{
		POINT pt;
		pt.x = ((short)LOWORD(lParam));
		pt.y = ((short)HIWORD(lParam));
		m_status.nParam=zDelta<0;
		if(m_pCurrentObj){
			m_status.bIsLock=FALSE;
			m_status.nStatusParam=STATUS_FLAG_AUTO;
			m_pCurrentObj->OnMouseWheel(m_nCurID,m_status);
		}
	}
}
void CLMouseEventMgrl::OnTimerOut(LONG nID)
{
	if(m_bLock)return;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	switch(nID){
	case MOUSE_DOWN_TIME_ID:
		{
			if(m_ptrTimerCreator){
				m_ptrTimerCreator->DeleteTimer(m_iMouseDownTmr);
				m_iMouseDownTmr=0;
				m_iRaiseMouseDownTmr=m_ptrTimerCreator->CreateTimer(this,
					MOUSE_DOWN_TIMEEVENT_OUT,MOUSE_DOWN_TIMEEVENT_ID);
			}
		}
		break;
	case MOUSE_DOWN_TIMEEVENT_ID:
		{
			if(m_status.bMouseIN){
				if(m_pCurrentObj){
					m_status.nStatusParam=STATUS_FLAG_MAN;
					if(m_pCurrArea){
						if(m_pCurrArea->bRect){
							RECT rct;
							POINT pt;
							pt.x=m_status.posx;
							pt.y=m_status.posy;
							if(m_pCurrentObj->GetRect(m_nCurID,rct))
								m_status.bMouseIN=CLDrawer::PtInRect(&rct,pt);
						}else{
							HRGN hrgn=NULL;
							if(m_pCurrentObj->GetRgn(m_nCurID,hrgn)){
								m_status.bMouseIN=CLDrawer::PtInRegion(hrgn,m_status.posx,m_status.posy);
								CLDrawer::DeleteRgn(hrgn);
							}
						}
					}
					m_pCurrentObj->OnLButtonDown(m_nCurID,m_status);
				}
			}
		}
		break;
	default:
		break;
	}
}
void CLMouseEventMgrl::ClearTimer()
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_ptrTimerCreator){
		if(m_iRaiseMouseDownTmr){
			m_ptrTimerCreator->DeleteTimer(m_iRaiseMouseDownTmr);
			m_iRaiseMouseDownTmr=0;
		}
		if(m_iMouseDownTmr){
			m_ptrTimerCreator->DeleteTimer(m_iMouseDownTmr);
			m_iMouseDownTmr=0;
		}
	}
	m_pCurrArea=NULL;
}
void CLMouseEventMgrl::OnLDBClick(LONG wParam,LONG lParam,BOOL& bCancel)
{

}