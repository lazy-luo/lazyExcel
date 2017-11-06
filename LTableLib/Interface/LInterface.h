#if !defined(AFX_LINTERFACE_H__E721BE6C_D051_411F_99B3_45AA5098A966__INCLUDED_)
#define AFX_LINTERFACE_H__E721BE6C_D051_411F_99B3_45AA5098A966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../LComm/Interface.h"
#ifdef _LINUX
#define HDC	void*
#endif

class CLCellItem;
class CLColItem;
class CLRowItem;
class CLStyle;
class CLFont;
interface ITable
{
public:

	virtual	LONG GetCashStyle(const CELL& cell) ABSTRACT;
	virtual	void SetCashStyle(const CELL& cell,LONG style) ABSTRACT;
	virtual	void SetCashStyle(const RANGE& range,LONG style) ABSTRACT;

	virtual	LONG GetBorderLineStyle(const CELL& cell) ABSTRACT;
	virtual	void SetBorderLineStyle(const CELL& cell,LONG style) ABSTRACT;
	virtual void SetBorderLineStyle(const RANGE& range,LONG style) ABSTRACT;

	virtual BOOL IsFormulaCell(LONG nRow,LONG nCol) ABSTRACT;
	virtual void SetFormulaValue(LONG nRow,LONG nCol,char* pValue) ABSTRACT;
	virtual LPTSTR GetFormulaValue(LONG nRow,LONG nCol) ABSTRACT;
	virtual void SetCellMemo(LONG irow, LONG icol, LPTSTR ptrTxt) ABSTRACT;
	virtual LPTSTR GetCellMemo(LONG irow, LONG icol) ABSTRACT;

	virtual void GetBeginPos(CELL& cell,POINT& ptOffset) ABSTRACT;
	virtual void GetEndPos(CELL& cell,POINT& ptOffset,
		const SIZE& size,CELL& cellRet,POINT& ptRet) ABSTRACT;
	virtual BOOL OnSerial(CLSerial& ar) ABSTRACT;
	virtual void SetForeColor(RANGE& range,COLORREF clr) ABSTRACT;
	virtual void SetBkColor(RANGE& range,COLORREF clr) ABSTRACT;
	virtual void ClearCellData(LONG nRow,LONG nCol,BOOL bRedraw=TRUE) ABSTRACT;
	virtual BOOL CellReadOnly(LONG nRow, LONG nCol) ABSTRACT;
	virtual void CellReadOnly(LONG nRow, LONG nCol, BOOL bVal) ABSTRACT;

	virtual void SetRangeReadOnly(RANGE &range, BOOL bVal) ABSTRACT;
	virtual BOOL IsRangeReadOnly(RANGE &range) ABSTRACT;
	virtual COLORREF GetBorderLineColor(LONG irow,LONG icol) ABSTRACT;
	virtual void SetBorderColor(LONG irow,LONG icol,COLORREF clr) ABSTRACT;
	
	virtual void SetBorderStyle(LONG nRow, LONG nCol, LONG nStyle) ABSTRACT;
	virtual LONG GetBorderStyle(LONG nRow, LONG nCol) ABSTRACT;
	virtual void ReleaseDC(HDCH& hDC) ABSTRACT;
	virtual void GetOldRange(RANGE& range) ABSTRACT;
	virtual void SetOldRange(const RANGE& range) ABSTRACT;
	virtual void ClearOldRange() ABSTRACT;
	virtual void GetCurrentRange(RANGE& range) ABSTRACT;
	virtual void SetCurrentRange(const RANGE& range) ABSTRACT;
	
	virtual COLORREF GetBorderColor(const CELL& cell) ABSTRACT;
	virtual LONG GetBorderStyle(const CELL& cell) ABSTRACT;
	virtual void SetBorderStyle(const CELL& cell,LONG style) ABSTRACT;
	virtual void SetBorderStyle(const RANGE& range,LONG style) ABSTRACT;
	virtual BOOL isFocusCell(const CELL& cell) ABSTRACT;
	virtual void GetPrevFocusCell(CELL& cell) ABSTRACT;
	virtual void SetPrevFocusCell(const CELL& cell) ABSTRACT;
	virtual void GetRightBottomCell(const SIZE& sizeClient/*ClientSize*/,CELL& cell,POINT& ptOffsetClip) ABSTRACT;
	virtual BOOL isRangeVisible(const RANGE& range,BOOL* bisClip,LPRECT prctOff) ABSTRACT;
	virtual void AdjustSizeChange(LONG cx, LONG cy,BOOL bSpecColRowSize) ABSTRACT;
	virtual BOOL GetDC(HDCH& hDC) ABSTRACT;
	virtual void GetCurrentCell(CELL& cell) ABSTRACT;
	
	virtual void SetCurrentCell(CELL& cell) ABSTRACT;
	virtual void SetExtendSize(const SIZE& size) ABSTRACT;
	virtual void GetExtendSize(SIZE& size) ABSTRACT;
	
	virtual void SetRowHeight(LONG irow,LONG val) ABSTRACT;
	virtual LONG GetRowHeight(LONG irow) ABSTRACT;
	virtual void SetColWidth(LONG icol,LONG val) ABSTRACT;
	virtual LONG GetColWidth(LONG icol) ABSTRACT;
	virtual void SetCellText(LONG irow,LONG icol,LPTSTR ptrTxt) ABSTRACT;
	virtual LPTSTR GetCellText(LONG irow,LONG icol) ABSTRACT;
	virtual LPSCROLLINFOEXT GetScrollInfo(BOOL bHorz=TRUE) ABSTRACT;
	virtual LONG GetCols() ABSTRACT;
	virtual void SetCols(LONG val) ABSTRACT;
	virtual LONG GetRows() ABSTRACT;
	virtual void SetRows(LONG val) ABSTRACT;
	virtual LONG GetFixedRows() ABSTRACT;
	virtual void SetFixedRows(LONG val) ABSTRACT;
	virtual LONG GetFixedCols() ABSTRACT;
	virtual void SetFixedCols(LONG val) ABSTRACT;
	virtual LONG GetFreezeRows() ABSTRACT;
	virtual void SetFreezeRows(LONG val) ABSTRACT;
	virtual LONG GetFreezeCols() ABSTRACT;
	virtual void SetFreezeCols(LONG val) ABSTRACT;
	virtual BOOL HasScroll(BOOL bHorz) ABSTRACT;
	virtual BOOL CanScroll(BOOL bHorz,BOOL bAddValue) ABSTRACT;
	virtual void ReDraw(BOOL bFull=FALSE) ABSTRACT;
	
	virtual CLCellItem* GetACell(const CELL cell,BOOL bForceNew=FALSE) ABSTRACT;
	virtual CLCellItem* GetACell(LONG irow,LONG icol,BOOL bForceNew=FALSE) ABSTRACT;
	virtual CLColItem*	GetACol(LONG icol,BOOL bForceNew=FALSE) ABSTRACT;
	virtual CLRowItem*	GetARow(LONG irow,BOOL bForceNew=FALSE) ABSTRACT;
	virtual CLStyle* GetCellStyle(const CELL& cell,BOOL bForceNew=FALSE) ABSTRACT;
	virtual CLFont* GetCellFont(const CELL& cell,BOOL bForceNew=FALSE) ABSTRACT;

	virtual LONG GetFontSize(LONG nRow,LONG nCol) ABSTRACT;
	virtual LPTSTR GetFontName(LONG nRow,LONG nCol) ABSTRACT;
	virtual void SetFontSize(RANGE &range,LONG iSize) ABSTRACT;
	virtual void SetFontName(RANGE& range,LPTSTR ptrName,BYTE bytChatSet) ABSTRACT;
	virtual void SetBorderColor(RANGE& range,COLORREF clr) ABSTRACT;
	virtual BOOL IsAlignBottom(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsAlignMiddle(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsAlignTop(LONG nRow,LONG nCol) ABSTRACT;
	virtual void SetAlignBottom(RANGE& range) ABSTRACT;
	virtual void SetAlignMiddle(RANGE& range) ABSTRACT;
	virtual void SetAlignTop(RANGE& range) ABSTRACT;
	virtual BOOL IsAlignRight(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsAlignCenter(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsAlignLeft(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsFontBold(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsFontItalic(LONG nRow,LONG nCol) ABSTRACT;
	virtual BOOL IsFontUnderline(LONG nRow,LONG nCol) ABSTRACT;
	virtual void SetFontUnderline(RANGE& range,BOOL bVal) ABSTRACT;
	virtual void SetFontItalic(RANGE& range,BOOL bVal) ABSTRACT;
	virtual void SetFontBold(RANGE& range,BOOL bVal) ABSTRACT;
	virtual void SetAlignCenter(RANGE& range) ABSTRACT;
	virtual void SetAlignRight(RANGE& range) ABSTRACT;
	virtual void SetAlignLeft(RANGE& range) ABSTRACT;
	virtual LONG NotifyProc(LONG wMsg,LONG nCmd,WPARAM wParam,
		LPARAM lParam,BOOL& bCancel) ABSTRACT;
	
	virtual BOOL isFixedCell(const CELL& cell) ABSTRACT;
	virtual BOOL isFreezeCell(const CELL& cell) ABSTRACT;
	
	virtual void GetDrawPanRect(RECT& rct) ABSTRACT;
	virtual void GetClientRect(RECT& rct,BOOL bRel=FALSE) ABSTRACT;
	virtual void GetTableRect(RECT& rct) ABSTRACT;

	virtual void GetClientRect(const RECT& rctAll,RECT& rct) ABSTRACT;	//ext
	virtual void GetTableRect(const RECT& rctAll,RECT& rct) ABSTRACT;
	virtual void GetBeginDrawPos(const RECT& rctAll,POINT &pt) ABSTRACT;
	virtual void GetBeginTablePos(const RECT& rctAll,POINT &pt) ABSTRACT;
	virtual void GetBeginClientPos(const RECT& rctAll,POINT &pt) ABSTRACT;
	virtual void GetBeginFreezePos(const RECT& rctAll,POINT &pt) ABSTRACT;
	virtual void GetDrawPanSize(const RECT& rctAll,SIZE& size) ABSTRACT;
	virtual void GetClientSize(const RECT& rctAll,SIZE& size) ABSTRACT;
	virtual BOOL GetRangeRect(const RECT& rctAll,const RANGE& range,RECT& rctClip,RECT& rctVisible,
		RECT& rct,LONG nOffset) ABSTRACT;//ext

	

	virtual void GetBeginDrawPos(POINT &pt) ABSTRACT;
	virtual void SetBeginDrawPos(const POINT& pt) ABSTRACT;
	virtual void GetBeginTablePos(POINT &pt) ABSTRACT;
	virtual void GetBeginClientPos(POINT &pt) ABSTRACT;
	virtual void GetBeginFreezePos(POINT &pt) ABSTRACT;
	virtual void GetBeginCell(CELL& cell) ABSTRACT;
	virtual void SetBeginCell(const CELL& cell) ABSTRACT;
	/////////////////////////////////////////////////////////////////////
	///////////////表格尺寸相关函数//////////////////////
	virtual void GetCellBeginXY(POINT& pt) ABSTRACT;
	virtual void SetCellBeginXY(const POINT& pt) ABSTRACT;
	virtual void SetDrawPanRect(const RECT& rct) ABSTRACT;
	virtual void GetDrawPanSize(SIZE& size) ABSTRACT;
	virtual void SetDrawPanSize(const SIZE& size) ABSTRACT;
	virtual void GetClientSize(SIZE& size) ABSTRACT;
	virtual BOOL GetRangeRect(const RANGE& range,RECT& rctClip,RECT& rctVisible,RECT& rct,LONG nOffset) ABSTRACT;
	virtual void GetFreeAreaSize(SIZE& size,LONG nFreeID) ABSTRACT;
	virtual void SetFreeAreaSize(const SIZE& size,LONG nFreeID) ABSTRACT;
	/////////////////////////////////////////////////////////////////////
	//virtual ICallServ* GetCallServer() ABSTRACT;
};

#endif