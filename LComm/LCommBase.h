//////////////////////////////////////////////////////////////////////
//@模块		 ：鼠标事件引擎
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////
#ifndef _LCOMMBASE_H_INCLUDE_
#define _LCOMMBASE_H_INCLUDE_
//区域管理对象接口
///////////////////////////////////////////////////////////////////////////////////
#include "LMap.h"
#include "Interface.h"

#define STATUS_FLAG_AUTO			0
#define STATUS_FLAG_MAN				1

#ifdef _WIN32
#include "../OSFace/WIN32/GDI/LDrawer.h"
#else
#include "../OSFace/Linux/GDI/LDrawer.h"
//不支持的平台
#endif

#ifdef _WIN32
#include "../OSFace/WIN32/LPlatform.h"
#else
#include "../OSFace/Linux/LPlatform.h"
//不支持的平台
#endif
#include "../LComm/LLockMgr.h"

class EXPORT_G_CLASS CLMouseEventMgrl:public ITimerListener
{
	friend class CLRptGrid;
private:
	IMouseEvent*	m_pCurrentObj;
	LONG			m_nCurID;
	CLCSWrapper     sm_CritSec;	//同步对象
	MOUSESTATUS		m_status;
	ITimerCreator*	m_ptrTimerCreator;
	UINT			m_iMouseDownTmr;
	UINT			m_iRaiseMouseDownTmr;
	
	BOOL			m_bTrackIN;
	LPIDAREA		m_pCurrArea;
	BOOL			m_bLock;
	void ClearTimer();
public:
	CLMouseEventMgrl();
	virtual ~CLMouseEventMgrl();
	virtual void OnTimerOut(LONG nID);
	virtual void ClearToDefault();
	__inline void SetTimerCreator(ITimerCreator* ptrSvr)
	{
		CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
		if(m_ptrTimerCreator!=ptrSvr)
			m_ptrTimerCreator=ptrSvr;
	};
	virtual void SetTopMostListener(LONG key,IMouseEvent* pobj,BOOL bForceNew=TRUE);
	virtual void RemoveListener(LONG key,IMouseEvent* pobj);
	virtual __inline void Lock(){m_bLock=TRUE;};
	virtual __inline void UnLock(){m_bLock=FALSE;};
	virtual void OnLDBClick(LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnMouseMove(LONG key,LONG x,LONG y,INT status,BOOL& bCancel);
	virtual void OnLButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnLButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnRButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnRButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnMButtonDown(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnMButtonUp(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
	virtual void OnMouseWheel(LONG key,LONG wParam,LONG lParam,BOOL& bCancel);
};
extern EXPORT_G_CLASS EVENT_MAP	*g_pEventMap;
extern EXPORT_G_CLASS CLMouseEventMgrl	g_nMouseEventMgrl;
extern EXPORT_G_CLASS IInterfaceMgrl*		g_pInterfaceManager;

#define GET_LINK(key)											\
	(g_pEventMap?g_pEventMap->GetValue(key):NULL)

#define LINK_MOUSE_EVENT(key,IDpIMouseEventImp)					\
	if(!g_pEventMap)											\
		g_pEventMap=new EVENT_MAP();							\
	{															\
		IInterfaceMgrl* ptr=g_pEventMap->GetValue(key,TRUE);	\
		ptr->AddFace(IDpIMouseEventImp);						\
	}
	
#define CLEAR_MOUSE_EVENT(key)									\
	if(g_pEventMap){											\
		g_pEventMap->DeleteValue((LONG)key);					\
	}															\
	if(g_pEventMap && g_pEventMap->GetCount()<1){				\
		delete g_pEventMap;										\
		g_pEventMap=NULL;										\
	}

//#define LINK_EVENT_OBJECT(key,IDpIMouseEventImp) \
	
//extern IInterfaceMgrl*	g_pInterfaceMgrl;
/*
#define RANGE_FUNCTION(obj)	\
	IDAREA idarea;\
	if(GetAreaIDs(idarea))\
	 g_nMouseEventMgrl.AddRangeIDs(obj,idarea)
*/
/*
#define LINK_INTERFACE(IDpIMouseEventImp) \
	if(!g_pInterfaceManager){\
		g_pInterfaceManager=new IInterfaceMgrl();\
	}\
	g_pInterfaceManager->AddFace(IDpIMouseEventImp)
*/
#define CLEAR_INTERFACE \
	if(g_pInterfaceManager)\
		delete g_pInterfaceManager;\
	g_pInterfaceManager=NULL

 //   if(IInterfaceMgrl::FindFace(IDpIMouseEventImp)==NULL) \
//	    static IInterfaceMgrl __g_##className##_face((IMouseEvent*)IDpIMouseEventImp)
		//extern IInterfaceMgrl __g_##className##_face
		//RANGE_FUNCTION(IDpIMouseEventImp)
///////////////////////////////////////////////////////////////////////////////////
class CLScrollBar;
interface IScrollable
{
public:
	virtual void StopExtendTrack(BOOL bHorz=TRUE) ABSTRACT;
	virtual void RedrawScrollBar(CLScrollBar* ptrObj) ABSTRACT;
	virtual LONG ScrollHorz(CLScrollBar* ptrObj,DLONG val,BOOL bPixel=TRUE) ABSTRACT;
	virtual LONG ScrollVert(CLScrollBar* ptrObj,DLONG val,BOOL bPixel=TRUE) ABSTRACT;
};

interface _EXPORT_G_CLASS_ IMouseEvent
{
public:
	virtual void OnMouseMove(LONG idArea,MOUSESTATUS& nstatus){};
	virtual void OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual void OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus){};
	virtual BOOL GetRect(LONG idArea,RECT& rct){return FALSE;};
	virtual BOOL GetRgn(LONG idArea,HRGN& hrgn){return FALSE;};
	virtual LPIDAREA GetAreaIDs(){return NULL;};
	virtual BOOL IsActive(){return TRUE;};
};

#endif
