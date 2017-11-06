//////////////////////////////////////////////////////////////////////
//@模块		 ：工作薄对象接口
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////
#ifndef _LBOOKINTERFACE_H_
#define _LBOOKINTERFACE_H_

#include "../LSheetLib/Interface/LSheetInterface.h"
interface IBook
{
public:
	virtual void SetPanKey(LONG handKey) ABSTRACT;
	virtual LONG GetPanKey() ABSTRACT;
	virtual LPTSTR GetPageName(LONG nIndex) ABSTRACT;
	virtual ISheet* GetSheet(LONG nIndex) ABSTRACT;
	virtual ISheet* GetSheetByPtr(LPVOID sheet) ABSTRACT;
	virtual ISheet*	AddSheet(LPTSTR ptrName,LONG nIndex) ABSTRACT;
	virtual ISheet*  GetCurrentSheet() ABSTRACT;
	virtual LONG	GetCount() ABSTRACT;
	virtual void	DeleteSheet(LONG nIndex) ABSTRACT;
	virtual LONG	GetCurrentSheetIndex() ABSTRACT;
	virtual LPTSTR	GetCurrentPageName() ABSTRACT;
	virtual void	SetCurrentPageName(LPTSTR ptrTxt) ABSTRACT;
	virtual void	SetPageName(LONG nIndex,LPTSTR ptrTxt) ABSTRACT;
	virtual BOOL	SetCurrentSheetIndex(LONG nIndex) ABSTRACT;
	virtual void	OnDraw(LPDRAWER	ptrCellDrawer) ABSTRACT;
	virtual BOOL	OnPrint(BOOL bPrintAll) ABSTRACT;
	virtual BOOL isTabVisible() ABSTRACT;
	virtual DOUBLE	GetWidthPercent() ABSTRACT;
	virtual void	SetWidthPercent(DOUBLE dbl) ABSTRACT;
	virtual BOOL OnSerial(CLSerial& ar) ABSTRACT;
};
#endif