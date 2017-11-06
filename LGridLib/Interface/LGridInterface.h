#ifndef _LGRIDINTERFACE_H_
#define _LGRIDINTERFACE_H_
#include "../../LTableLib/Interface/LInterface.h"

interface IGrid:public IScrollable
{
public:
	virtual LONG GetNextRow(const CELL& cell) ABSTRACT;
	virtual LONG GetPrevRow(const CELL& cell) ABSTRACT;
	virtual LONG GetNextCol(const CELL& cell) ABSTRACT;
	virtual LONG GetPrevCol(const CELL& cell) ABSTRACT;
	virtual void ClearRangeData(RANGE& range) ABSTRACT;
	virtual void SetRangeBorderLineStyle(RANGE &range, LONG nStyle) ABSTRACT;
	virtual void SetRangeForeColor(RANGE &range, COLORREF clr) ABSTRACT;
	virtual void SetRangeBkColor(RANGE &range, COLORREF clr) ABSTRACT;
	virtual void DeleteCurrentCol() ABSTRACT;
	virtual BOOL AppendCol() ABSTRACT;
	virtual BOOL InsertCol(BOOL bBefore=TRUE) ABSTRACT;
	virtual void DeleteCurrentRow() ABSTRACT;
	virtual BOOL InsertRow(BOOL bBefore=TRUE) ABSTRACT;
	virtual BOOL AppendRow() ABSTRACT;
	virtual void CutDataToClipBox() ABSTRACT;
	virtual void GetDataFromClipBox() ABSTRACT;
	virtual BOOL PasteData(LPTSTR ptrText) ABSTRACT;
	virtual void CopyDataToClipBox(RANGE &range) ABSTRACT;
	virtual void CopyDataToClipBox() ABSTRACT;
	virtual void GetMasterCell(CELL& cell) ABSTRACT;
	virtual BOOL MergeCurrentRange(LONG nType=MERGE_ALL) ABSTRACT;
	virtual BOOL UnMergeCurrentRange() ABSTRACT;
	virtual void SetMasterCellText(LONG irow,LONG icol,LPTSTR ptrTxt) ABSTRACT;
	virtual LPTSTR GetMasterCellText(LONG irow,LONG icol) ABSTRACT;
	virtual BOOL isFocusCell(const RANGE& range) ABSTRACT;
	virtual HRGN GetRowRgn(LONG nRow,RECT& rctClip) ABSTRACT;
	virtual BOOL isRangeMode() ABSTRACT;
	virtual void isRangeMode(BOOL val) ABSTRACT;
	virtual void GetCellRange(LONG nRow, LONG nCol, RANGE &range) ABSTRACT;
	virtual void GetCombinRange(RANGE &range,const RANGE &rangeD) ABSTRACT;
	virtual BOOL GetCellRect(LONG irow,LONG icol,RECT& rct,RECT& rctVisible,BOOL bClip=TRUE) ABSTRACT;
	virtual LONG getSelectMode() ABSTRACT;
	virtual void setSelectMode(LONG mod) ABSTRACT;
	virtual BOOL isFillFocusMode() ABSTRACT;
	virtual void isFillFocusMode(BOOL val) ABSTRACT;

	virtual ITable* GetTable() ABSTRACT;
	virtual BOOL RemoveMergeRange(RANGE& range) ABSTRACT;
	virtual BOOL MergeRange(RANGE& range,INT nType=MERGE_ALL) ABSTRACT;
	virtual BOOL isExcelMode() ABSTRACT;
	virtual void isExcelMode(BOOL val) ABSTRACT;
	virtual COLORREF GetGridLineColor() ABSTRACT;
	virtual void SetGridLineColor(COLORREF clr) ABSTRACT;
	virtual BOOL GetMergeRange(const CELL cell,RANGE& range) ABSTRACT;
	virtual BOOL isMergeCell(const CELL& cell) ABSTRACT;
	//支持自动适应滚动到任意位置
	virtual void AutoAdjustPos(const CELL& cell) ABSTRACT;
};
#endif