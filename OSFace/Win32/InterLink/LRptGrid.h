//////////////////////////////////////////////////////////////////////
//@模块		 ：报表对象平台相关接口定义(WIN32)
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LRPTGRID_H__E35363D2_9E3C_4B49_A00D_1EAC6812740B__INCLUDED_)
#define AFX_LRPTGRID_H__E35363D2_9E3C_4B49_A00D_1EAC6812740B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../../Src/LBook.h"
#include "InplaceCtrl/LEditCtrl.h"

extern EXPORT_G_CLASS CLMouseEventMgrl	g_nMouseEventMgrl;

class CLRptGrid:public IRedrawHelp,public ITimerCreator,public IInputable
{
private:
	ITimerListener* m_pTimerLsner;
	
	HWND	m_hWnd;
	LONG	m_pOldProc;
	CLEditCtrl*		m_ptrEdit;
	IInPlaceCtrl*	m_ptrCurrCtrl;
	LONG	m_nCurrCtrlRow;
	LONG	m_nCurrCtrlCol;

	BOOL InitInplaceCtrl();
	void SetCurrentCtrl();
	void HideInPlaceCtrl();
	void ClearInplaceCtrl();
public:
	CLBook	m_book;
	virtual __inline BOOL GetTotalRect(RECT& rct){
		if(m_hWnd){
			::GetClientRect(m_hWnd,&rct);
			return TRUE;
		}else{
			return FALSE;
		}
	};
	virtual __inline void ReleaseDC(HDCH& hDC)
	{
		if(m_hWnd){
			::ReleaseDC(m_hWnd,hDC.hDC);
		}
	}
	virtual void OnChar(LONG wParam,LONG lParam);
	virtual void OnKeyDown(LONG wParam,LONG lParam,BOOL& bCancel);
	virtual	void OnKeyUp(LONG wParam,LONG lParam,BOOL& bCancel);

	void OnLDBClick(LONG wParam,LONG lParam,BOOL& bCancel);
	virtual BOOL GetDC(HDCH& hDC);
	virtual LONG CreateTimer(ITimerListener* ptrLsner,LONG uElapse,LONG nID);
	virtual BOOL DeleteTimer(LONG iTimer);
	static LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	CLRptGrid();
	virtual ~CLRptGrid();
	__inline CLBook* GetBook(){return &m_book;};
	BOOL AttachWidow(HWND hWnd);
	virtual void ReDraw(BOOL bAll=TRUE);
	void DeattachWindow();
	__inline ISheet* GetCurrentSheet(){return m_book.GetCurrentSheet();};
	__inline ISheet* GetSheet(LONG nIndex){return m_book.GetSheet(nIndex);};

	__inline IGrid*	GetGrid(ISheet* sheet){
		if(sheet)
			return sheet->GetGrid();
		else
			return NULL;
	};
	__inline ITable*	GetTable(ISheet* sheet){
		if(sheet)
			return sheet->GetGrid()->GetTable();
		else
			return NULL;
	};
	__inline ICallServ* GetCallServer(ISheet* sheet){
		if(sheet)
			return sheet->GetCallServ();
		else
			return NULL;
	};
};

#endif // !defined(AFX_LRPTGRID_H__E35363D2_9E3C_4B49_A00D_1EAC6812740B__INCLUDED_)
