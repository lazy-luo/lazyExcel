//////////////////////////////////////////////////////////////////////
//@模块		 ：绘图基类对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LDRAWITEM_H__A9038050_4323_4CC9_B38C_B0B14C733702__INCLUDED_)
#define AFX_LDRAWITEM_H__A9038050_4323_4CC9_B38C_B0B14C733702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MSG_DRAW_CALLBACK(pobj,msg,command,wparam,lparam) \
	BOOL bCancel=FALSE;\
	pobj->NotifyProc(msg,command,wparam,lparam,bCancel);\
	if(bCancel)return

#include "../../LComm/LCommBase.h"
class _EXPORT_G_CLASS_ CLDrawItemBase:public IMouseEvent,public IDrawItem
{
	friend class CLDrawItemMgrl;
protected:
	BOOL m_bFocus;
	CELL	m_cellPos;
	CELL	m_cellEnd;
	POINT   m_ptOffset;
	POINT	m_ptOffsetEnd;
	IRedrawHelp*	m_ptrOuter;
	ISizeNotify* m_ptrSizeNotify;
	POINT m_ptOld;
	BOOL bMouseDown;
	RECT m_rctOld;
	BOOL m_bVisible;
public:
	
	CLDrawItemBase();
	virtual ~CLDrawItemBase();
	void DrawTracker(LPHDC pDC, int X, int Y);
	__inline void SetFocus(BOOL bFocus){m_bFocus=bFocus;};
	__inline BOOL IsVisible(){return m_bVisible;};
	__inline void IsVisible(BOOL val){m_bVisible=val;};
	__inline BOOL IsFocus(){return m_bFocus;};
	virtual POINT GetHandle(int nHandle);
	__inline virtual INT GetHandleCount() { return 8; };
	RECT GetHandleRect(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, const POINT& point);
	virtual void MoveTo(const CELL& cell, const POINT& point);
	virtual void SetRedrawHelp(IRedrawHelp* ptrOuter);
	virtual void OnDraw(LPHDC pDC,const RECT& rct){};
	void ReDraw(BOOL bVal=TRUE);
	virtual void SetSizeNotify(ISizeNotify* ptrNotify);
	virtual void OnMouseMove(LONG idArea,MOUSESTATUS& nstatus);
	virtual void OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual void OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual void OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual void OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual void OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual void OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus) {};
	virtual BOOL GetRect(LONG idArea,RECT& rct) {return FALSE;};
	virtual BOOL GetRgn(LONG idArea,HRGN& hrgn) {return FALSE;};
	virtual LPIDAREA GetAreaIDs() {return NULL;};
	virtual BOOL IsActive(){return TRUE;};
	virtual void GetBeginPos(POINT &pos){
		RECT rct;
		GetDrawRect(rct);
		pos.x=rct.left;
		pos.y=rct.top;
	};	
	virtual BOOL GetDrawRect(RECT& rct);
	virtual void SetDrawRect(const RECT& rct){};
};
//绘制对象管理器
class CLDrawItemMgrl
{
	friend class CLSheet;
private:
	LPCHAIN GetNode(CLDrawItemBase* ptrItem, LPCHAIN& pparent,LPCHAIN& ppparent);
	BOOL IsExists(CLDrawItemBase* ptrItem,LONG& ret);
	LPCHAIN	m_ptrHead;//链表头指针
	LPCHAIN	m_ptrTail;//链表尾指针
	CLDrawItemBase* m_ptrFocus;
	
public:
	void SetSizeNotify(ISizeNotify* ptr);
	CLDrawItemBase* GetPrevItem(CLDrawItemBase* ptrData);
	CLDrawItemBase* GetNextItem(CLDrawItemBase* ptrData);
	void SetRedrawHelp(IRedrawHelp* ptrObj);
	void DeleteDrawItem(CLDrawItemBase* ptrItem);
	virtual void OnDraw(LPHDC pDC,const POINT& ptOffset,const POINT& pt_freeze
		,tag_Drawer_Type draw_type);
	BOOL BringToTop(CLDrawItemBase *ptrItem);
	BOOL BringToBottom(CLDrawItemBase *ptrItem);
	BOOL BringToBack(CLDrawItemBase* ptrItem);
	BOOL BringToFront(CLDrawItemBase* ptrItem);
	LONG AddDrawItem(CLDrawItemBase* ptrItem);
	__inline CLDrawItemBase*  GetFocus(){
		return m_ptrFocus;
	}
	__inline void SetFocus(CLDrawItemBase* ptrItem){
		if(m_ptrFocus)
			m_ptrFocus->SetFocus(FALSE);
		if(ptrItem){
			ptrItem->SetFocus(TRUE);
		}
		m_ptrFocus=ptrItem;
	};
	CLDrawItemBase* GetTopMostItem();
	CLDrawItemBase* GetBottomItem();
	__inline BOOL IsTopMost(CLDrawItemBase* ptrItem){return (m_ptrTail?m_ptrTail->ptrData==(LPVOID)ptrItem:FALSE);};
	__inline BOOL IsBottom(CLDrawItemBase* ptrItem){return (m_ptrHead?m_ptrHead->ptrData==(LPVOID)ptrItem:FALSE);};
	CLDrawItemMgrl();
	virtual ~CLDrawItemMgrl();
};
#endif // !defined(AFX_LDRAWITEM_H__A9038050_4323_4CC9_B38C_B0B14C733702__INCLUDED_)
