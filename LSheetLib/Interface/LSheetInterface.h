#ifndef _LSHEETINTERFACE_H_
#define _LSHEETINTERFACE_H_
#include "../../LGridLib/Interface/LGridInterface.h"
#include "../../LGUILib/Base/LDrawItem.h"
typedef LONG (__stdcall *pfNotifyProc)(LONG wMsg,LONG nCmd,
	WPARAM wParam,LPARAM lParam,BOOL& bCancel,BOOL& bPassNextFilter);

class CLDrawItemBase;
class CLDrawItemMgrl;
class SHEET_EXPORT_CLASS ISheet
{
	friend class CLDrawerSheet;
private:
	virtual CLDrawItemMgrl*	GetDrawItemsArr() ABSTRACT;
public:
	virtual LONG GetMousePosition(const POINT& pt) ABSTRACT;
	virtual BOOL IsSelFixedRow() ABSTRACT;
	virtual BOOL IsSelFixedCol() ABSTRACT;
	virtual BOOL IsResizeInFixedCell() ABSTRACT;
	virtual void IsResizeInFixedCell(BOOL bVal) ABSTRACT;
	virtual void SetDDrawObj(IDirectDraw* ptrObj) ABSTRACT;
	virtual void IsActive(BOOL val) ABSTRACT;
	virtual ICallServ* GetCallServ() ABSTRACT;
	virtual void SetBeginPos(const POINT& pt) ABSTRACT;
	virtual IGrid* GetGrid() ABSTRACT;
	virtual void DeleteDrawItem(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual BOOL BringToTop(CLDrawItemBase *ptrItem) ABSTRACT;
	virtual BOOL BringToBottom(CLDrawItemBase *ptrItem) ABSTRACT;
	virtual BOOL BringToBack(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual BOOL BringToFront(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual LONG AddDrawItem(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual BOOL IsTopMost(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual BOOL IsBottom(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual CLDrawItemBase* GetTopMostItem() ABSTRACT;
	virtual CLDrawItemBase* GetBottomItem() ABSTRACT;
	virtual void SetFocusItem(CLDrawItemBase* ptrItem) ABSTRACT;
	virtual CLDrawItemBase* GetFocusItem() ABSTRACT;
	virtual LONG DefaultMessageProc(LONG wMsg,LONG nCmd,
		WPARAM wParam,LPARAM lParam,BOOL& bCancel) ABSTRACT;
	
	virtual BOOL SetMessageFilter(LPVOID ptrFun) ABSTRACT;
	virtual BOOL RemoveMessageFilter(LPVOID ptrFun) ABSTRACT;

	virtual LONG GetSheetLineStyle() ABSTRACT;
	virtual void SetSheetLineStyle(LONG val) ABSTRACT;
	virtual LPTSTR GetSheetName() ABSTRACT;
	virtual void SetSheetName(LPTSTR ptrName) ABSTRACT;
};
#endif