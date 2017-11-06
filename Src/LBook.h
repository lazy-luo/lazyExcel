//////////////////////////////////////////////////////////////////////
//@模块		 ：工作薄对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBOOK_H__EDA2C642_A461_4976_A8F1_98AD4F5A1409__INCLUDED_)
#define AFX_LBOOK_H__EDA2C642_A461_4976_A8F1_98AD4F5A1409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Public/LBookPublic.h"
#include "../INTERFACE/LBookInterface.h"

#include "../Base/LTabArea.h"

#include "../LSheetLib/Src/LSheet.h"


class CLScrollBar;
class CLDrawerSheet;
class CLBitmapPan;

class CLBook : public IBook,public ISplictFace
{
public:
	friend DWORD WINAPI DrawProc(LPVOID lpParameter);
	BOOL AddBitmapPan(LONG sheet,LPTSTR ptrName);
	CLBook(LONG key=0);
	virtual ~CLBook();
	virtual LONG GetCount();
	virtual void SetRedrawHelp(IRedrawHelp* ptr);
	virtual LPTSTR GetPageName(LONG nIndex);
	virtual ISheet* GetSheet(LONG nIndex);
	virtual ISheet* GetSheetByPtr(LPVOID sheet);
	virtual ISheet*	AddSheet(LPTSTR ptrName,LONG nIndex);
	virtual ISheet*  GetCurrentSheet();
	virtual void	DeleteSheet(LONG nIndex);
	virtual LONG	GetCurrentSheetIndex();
	virtual void	SetPageName(LONG nIndex,LPTSTR ptrTxt);
	virtual LPTSTR	GetCurrentPageName();
	virtual void	SetCurrentPageName(LPTSTR ptrTxt);
	virtual BOOL	SetCurrentSheetIndex(LONG nIndex);
	virtual BOOL isTabVisible();
	virtual DOUBLE	GetWidthPercent();
	virtual void	SetWidthPercent(DOUBLE dbl);
	virtual void	OnDraw(LPDRAWER	ptrCellDrawer);
	virtual BOOL OnSerial(CLSerial& ar);
	virtual BOOL	OnPrint(BOOL bPrintAll=FALSE);
	virtual void SetPanKey(LONG handKey);
	virtual LONG GetPanKey(){return m_handKey;};
	
	virtual void SplictChange(LONG noffset);
private:
	void SetCurrentCtrl();
	void OnSizeChange(LONG offsetX,LONG offsetY);
	BOOL PrintSheet(ISheet* ptrSheet,BOOL bShowDlg=TRUE);
	BOOL GetDrawRect(RECT& rct,BOOL bdecBorder=TRUE);
	BOOL GetScrollBarRect(BOOL bHorz,RECT& rct);
	BOOL GetTabAreaRect(RECT& rct);
	void Draw_Book(LPDRAWER	ptrCellDrawer);
	void ClearData();
	CLTabArea m_table;
	DOUBLE m_perTabBar;
	CLCSWrapper sm_CritSec;
	CLDrawerSheet* m_pDrawer;
	IRedrawHelp* m_ptrDrawHelp;
	//水平滚动条
	CLScrollBar* m_ptrHorzScroll;
	//垂直滚动条
	CLScrollBar* m_ptrVertScroll;
	COLORREF	m_clrScrollBar;
	LONG	m_lngWidth;
	BOOL m_bSplictFixedSize;
	CLPrintDC	m_printer;
	LONG	m_nBorderWidth;
	SIZE	m_sizePan;
	LONG m_handKey;	//画板Key
};
typedef struct tag_DrawParameter{
	CLBook*		p_book;
	LPDRAWER	lpDrawer;
}DRAWPARAM,*LPDRAWPARAM;
#endif // !defined(AFX_LBOOK_H__EDA2C642_A461_4976_A8F1_98AD4F5A1409__INCLUDED_)
