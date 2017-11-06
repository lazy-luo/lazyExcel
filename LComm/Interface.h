//////////////////////////////////////////////////////////////////////
//@公用接口  ：
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////
#ifndef _LZY_INTERFACE_H_
#define _LZY_INTERFACE_H_
#include "LGlobalParam.h"

interface IMouseEvent;

interface ITimerListener
{
	virtual void OnTimerOut(LONG nID) ABSTRACT;
};
interface ITimerCreator
{
	virtual LONG CreateTimer(ITimerListener* ptrLsner,LONG uElapse,LONG nID) ABSTRACT;
	virtual BOOL DeleteTimer(LONG iTimer) ABSTRACT;
};

interface IMouseEventMgrl
{
public:
	virtual void AddRangeIDs(IMouseEvent* ptrObj,const IDAREA& idarr) ABSTRACT;
};

interface ISplictFace
{
public:
	virtual void SplictChange(LONG noffset) ABSTRACT;
};
class EXPORT_G_CLASS IInterfaceMgrl
{
private:
	IMouseEvent* FindFace(IMouseEvent* ptrEvent){
		for(IInterfaceMgrl* ptr=this;ptr && \
			ptr->m_ptrEvent!=ptrEvent;ptr=ptr->m_ptrNext);
		return ptr?ptr->m_ptrEvent:NULL;
	}
public:
	IInterfaceMgrl(IMouseEvent*	ptrEvent=NULL):m_ptrNext(NULL),m_ptrEvent(ptrEvent)
	{
	}
	IMouseEvent*	m_ptrEvent;
	IInterfaceMgrl*	m_ptrNext;
	
	void AddFace(IMouseEvent* ptrEvent){
		IInterfaceMgrl* ptr=this;
		for(;ptr && ptr->m_ptrNext;ptr=ptr->m_ptrNext);
		if(NULL==FindFace(ptrEvent)){
			if(ptr->m_ptrEvent==NULL){
				ptr->m_ptrEvent=ptrEvent;
			}else{
				ptr->m_ptrNext=new IInterfaceMgrl(ptrEvent);
			}
		}
	}
	~IInterfaceMgrl(){
		if(m_ptrNext)
			delete m_ptrNext;
		m_ptrNext=NULL;
	}
};

//标准输入接口
interface EXPORT_G_CLASS IInputable
{
public:
	virtual void OnChar(LONG wParam,LONG lParam) ABSTRACT;
	virtual void OnKeyDown(LONG wParam,LONG lParam,BOOL& bCancel) ABSTRACT;
	virtual	void OnKeyUp(LONG wParam,LONG lParam,BOOL& bCancel) ABSTRACT;	
};
interface _EXPORT_G_CLASS_ IScrollTyle
{
public:
	virtual BOOL IsHorz() ABSTRACT;
};
interface _EXPORT_G_CLASS_ IDirectDraw
{
public:
	virtual void ShowToolTip(LPHDC pDC,LPTSTR ptrTip,BOOL bShow=TRUE) ABSTRACT;
	virtual void DrawDragRange(LPHDC pDC,const RANGE& rangeOld,const RANGE& range) ABSTRACT;
	virtual void DrawFocusCell(LPHDC pDC,LPCELL pCellCur=NULL,LPCELL pCellOld=NULL) ABSTRACT;
	virtual void DrawSelectRange(LPHDC pDC,BOOL bRestoryOld=FALSE,BOOL bIsFocusCell=FALSE) ABSTRACT;
};
/*
interface __EXPORT_G_CLASS_ IGraphicsAddIn
{
public:
	virtual void GetBeginCell(CELL& cell) ABSTRACT;
	virtual void GetEndCell(CELL& cell) ABSTRACT;
	virtual void GetBeginOffset(POINT& pt) ABSTRACT;
	
};
*/
interface _EXPORT_G_CLASS_ IDrawable
{
public:
	virtual void OnDraw(LPHDC pDC,const RECT& rct) ABSTRACT;
};
interface _EXPORT_G_CLASS_ IDrawItem :public IDrawable 
{
protected:
	SIZE	m_size;
	POINT	m_beginPos;
public:
	virtual void GetBeginPos(POINT &pos){pos=m_beginPos;};
	virtual void SetBeginPos(const POINT &pos){m_beginPos=pos;};	
	virtual void GetDrawSize(SIZE &size){size=m_size;};
	virtual void SetDrawSize(const SIZE &size){m_size=size;};
	
	virtual BOOL GetDrawRect(RECT& rct){rct.left=m_beginPos.x,rct.right=rct.left+m_size.cx,
		rct.top=m_beginPos.y,rct.bottom=rct.top+m_size.cy;return TRUE;};
	virtual void SetDrawRect(const RECT& rct){
		m_beginPos.x=rct.left;
		m_beginPos.y=rct.top;
		m_size.cx=rct.right-rct.left;
		m_size.cy=rct.bottom-rct.top;
	};

};
interface _EXPORT_G_CLASS_ IInPlaceCtrl
{
public:
	virtual void SetForeColor(COLORREF clr) ABSTRACT;
	virtual LRESULT SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam) ABSTRACT;
	virtual void setVisible(BOOL bShow) ABSTRACT;
	virtual BOOL getVisible() ABSTRACT;
	virtual LONG getLongValue() ABSTRACT;
	virtual LPTSTR getStringValue() ABSTRACT;
	virtual LPTSTR getTag() ABSTRACT;
	virtual void setLongValue(LONG nVal) ABSTRACT;
	virtual void setStringValue(LPTSTR ptrV) ABSTRACT;
	virtual void setTag(LPTSTR ptrV) ABSTRACT;
	virtual void setFont(HFONT hFont) ABSTRACT;
	virtual void setBkColor(COLORREF clr) ABSTRACT;
	virtual void setPosition(LONG nLeft,LONG nTop,LONG nRight,LONG nBottom) ABSTRACT;
};
interface EXPORT_G_CLASS IRedrawHelp
{
	virtual void ReDraw(BOOL bAll) ABSTRACT;
	virtual BOOL GetDC(HDCH& hDC) ABSTRACT;
	virtual void ReleaseDC(HDCH& hDC) ABSTRACT;
	virtual BOOL GetTotalRect(RECT& rct) ABSTRACT;
};
interface _EXPORT_G_CLASS_ ISizeNotify
{
public:
	virtual BOOL GetPanRect(RANGE& range,POINT ptOffset,const SIZE& size,RECT& rct) ABSTRACT;
	virtual BOOL OnObjectMove(CELL& cellBegin,CELL& cellEnd,
		POINT& ptOffset,POINT& ptEndOffset,const SIZE& size,LONG cx,LONG cy,RECT& rctAll) ABSTRACT;
	virtual void OnObjectSize(CELL& cellEnd,POINT& ptEndOffset,LONG cx,LONG cy,RECT& rctAll) ABSTRACT;
};
interface _EXPORT_G_CLASS_ ICallBack
{
public:
	virtual LONG CallBackProc(LONG msg,LPVOID param,BOOL& bCancel) ABSTRACT;
};

interface EXPORT_G_CLASS ICallServ
{
public:
	virtual LONG NotifyMessage(LONG msgID,LPVOID param) ABSTRACT;
	virtual LONG AddLinstener(ICallBack* ptrObj,LONG msgID,BOOL bAddHeader=TRUE) ABSTRACT;
	virtual LONG RemoveListener(ICallBack* ptrObj,LONG msgID) ABSTRACT;
	virtual LONG ClearListener(LONG msgID) ABSTRACT;
};

#endif