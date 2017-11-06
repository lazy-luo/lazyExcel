//////////////////////////////////////////////////////////////////////
//@报表底层  ：报表导出类
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEXPORT_H__1E01CFE6_3045_4FA4_B11C_D7893E069E4F__INCLUDED_)
#define AFX_LEXPORT_H__1E01CFE6_3045_4FA4_B11C_D7893E069E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _EXPORT_TYPE_!=2
#include "../../OSFace/Win32/InterLink/LRptGrid.h"


#if _EXPORT_TYPE_==1
	//是API方式
	#define PRIVATE_API(type,name) type ##name
	#define SP_DOT	,
	#define PARAM_BOOK	LONG book
	#define BOOK_PTR	(CLBook*)book
	#define PARAM_RPT	LONG hRpt
	#define RPT_PTR		(CLRptGrid *)hRpt
	#ifdef LGRIDBOOK_EXPORTS
		#define EXPORT_CLASS
		#define WIN_API(type,name)  extern "C" type  __declspec(dllexport) name
	#else
		#ifdef _NORMAL_CALL
			#define EXPORT_CLASS
			#define WIN_API(type,name)  type name
		#else
			#define EXPORT_CLASS
			#define WIN_API(type,name)  extern "C" type __declspec(dllimport) name
		#endif
	#endif
#else
	#define WIN_API(type,name) type CLExport::##name
	#define PRIVATE_API(type,name)  WIN_API(type,name)
	#define SP_DOT	
	#define PARAM_BOOK
	#define BOOK_PTR	GetBook()
	#define PARAM_RPT
	#define RPT_PTR		&g_rptGrid
	#ifndef _LCOM_EXPORT_
		#ifdef LGRIDBOOK_EXPORTS
			#define EXPORT_CLASS	__declspec(dllexport)
		#else
			#define EXPORT_CLASS	__declspec(dllimport)
		#endif
	#else
		#define EXPORT_CLASS
	#endif
#endif

#if _EXPORT_TYPE_==0
class EXPORT_CLASS CLExport  
{
private:
	CLRptGrid	g_rptGrid;
	CLBook* GetBook();
public:
	CLExport();
	virtual ~CLExport();
	BOOL IsReadOnly(LONG sheet);
	void SetReadOnly(LONG sheet,BOOL val);
	void SetCashStyle(LONG sheet,LONG style);
	LONG GetCashStyle(LONG sheet,LONG irow,LONG icol);
	void SetBorderLineDot(LONG sheet,LONG style);
	LONG GetBorderLineDot(LONG sheet,LONG irow,LONG icol);
	BOOL GetCurrentCell(LONG sheet,CELL& cell);
	LONG GetFontSize(LONG sheet, LONG nRow, LONG nCol);
	LPTSTR GetFontName(LONG sheet, LONG nRow, LONG nCol);
	void SetCurrentRangeFontName(LONG sheet, LPTSTR ptrName, LONG bytChatSet);
	void SetCurrentRangeFontSize(LONG sheet, LONG nSize);
	LONG GetGridLineStyle(LONG sheet);
	void SetGridLineStyle(LONG sheet,LONG style);
	void SetCurrentRangeBorderColor(LONG sheet, LONG clr);
	void SetCurrentRangeFontItalic(LONG sheet);
	void SetCurrentRangeFontBold(LONG sheet);
	void SetCurrentRangeFontUnderLine(LONG sheet);
	void SetCurrentRangeBorderLineStyle(LONG sheet, LONG nStyle);
	void SetCurrentRangeForeColor(LONG sheet, LONG clr);
	void SetCurrentRangeBkColor(LONG sheet, LONG clr);
	void DeleteCurrentCol(LONG sheet);
	void PasteData(LONG sheet);
	void CopyData(LONG sheet);
	void ClearCellData(LONG sheet, LONG nRow, LONG nCol);
	void ClearCurrentRangeData(LONG sheet);
	BOOL AttachWidow(HWND hWnd);
	void DeattachWindow();
	BOOL SaveBook(LPTSTR ptrName);
	BOOL LoadBook(LPTSTR ptrName);
	BOOL AddDrawItem(LONG sheet,LPVOID ptrItem);
	void BringDrawItemToFront(LONG sheet,LPVOID ptrItem);
	void BringDrawItemToBack(LONG sheet,LPVOID ptrItem);
	void BringDrawItemToTop(LONG sheet,LPVOID ptrItem);
	void BringDrawItemToBottom(LONG sheet,LPVOID ptrItem);
	void AppendACol(LONG sheet);
	void AppendARow(LONG sheet);
	LONG GetCurrentSheet();
	LONG AddLinstener(LONG sheet,LPVOID ptrObj,LONG msgID,BOOL bAddHeader=TRUE);
	LONG GetSheet(LONG nIndex);
	BOOL SetMessageFilter(LONG sheet,LPVOID ptrFun);
	BOOL RemoveMessageFilter(LONG sheet,LPVOID ptrFun);
	void SetFocusItem(LONG sheet,LPVOID ptrItem);
	LONG NotifyMessage(LONG sheet,LONG msgID,LPVOID param);
	LONG AddSheet(LPTSTR ptrName,LONG nIndex);
	void SetCurrentSheet(LONG nIndex);
	void SetRows(LONG sheet,LONG irows);
	LONG GetRows(LONG sheet);
	void SetCols(LONG sheet,LONG icols);
	LONG GetCols(LONG sheet);
	void SetFixedRows(LONG sheet,LONG irows);
	LONG GetFixedRows(LONG sheet);
	void SetFixedCols(LONG sheet,LONG icols);
	LONG GetFixedCols(LONG sheet);
	void SetFreezeRows(LONG sheet,LONG irows);
	LONG GetFreezeRows(LONG sheet);
	void SetFreezeCols(LONG sheet,LONG icols);
	LONG GetFreezeCols(LONG sheet);
	//LPTSTR GetLabelText(LONG sheet,LONG irow,LONG icol);
	//void SetLabelText(LONG sheet,LONG irow,LONG icol,LPTSTR ptrTxt);
	LPTSTR GetTextMatrix(LONG sheet,LONG irow,LONG icol);
	void SetTextMatrix(LONG sheet,LONG irow,LONG icol,LPTSTR ptrTxt);
	LONG GetRowHeight(LONG sheet,LONG irow);
	void SetRowHeight(LONG sheet,LONG irow,LONG vheight);
	LONG GetColWidth(LONG sheet,LONG icol);
	void SetColWidth(LONG sheet,LONG icol,LONG vwidth);
	BOOL PrintBook(BOOL bPrintAll);
	BOOL MergeRange(LONG sheet,LONG rowBegin,LONG colBegin,LONG rowEnd,LONG colEnd);
	BOOL RemoveMergeRange(LONG sheet,LONG rowBegin,LONG colBegin,LONG rowEnd,LONG colEnd);
	BOOL MergeCurrentRange(LONG sheet,LONG nType);
	BOOL UnMergeCurrentRange(LONG sheet);
	LONG GetBorderStyle(LONG sheet,LONG irow,LONG icol);
	void SetBorderStyle(LONG sheet,LONG irow,LONG icol,LONG style);
	BOOL AddBitmapPan(LONG sheet,LPTSTR ptrName);
	BOOL isHorzAlignPos(LONG sheet,LONG irow,LONG icol,enum_horz_align pos);
	void setHorzAlignPos(LONG sheet,LONG irow,LONG icol,enum_horz_align pos);
	BOOL isVertAlignPos(LONG sheet,LONG irow,LONG icol,enum_vert_align pos);
	void setVertAlignPos(LONG sheet,LONG irow,LONG icol,enum_vert_align pos);
	void setRangeHorzAlignPos(LONG sheet,RANGE& range,enum_horz_align pos);
	void setRangeVertAlignPos(LONG sheet,RANGE& range,enum_vert_align pos);
	void GetCurrentRange(LONG sheet,RANGE& range);
	BOOL IsFontUnderline(LONG sheet,LONG irow,LONG icol);
	BOOL IsFontBold(LONG sheet,LONG irow,LONG icol);
	BOOL IsFontItalic(LONG sheet,LONG irow,LONG icol);
	void DeleteCurrentRow(LONG sheet);
	void CutCurrentData(LONG sheet);
	
	void InsertARow(LONG sheet);
	void InsertACol(LONG sheet);
	LONG GetCellForeColor(LONG sheet,CELL cell);
	LONG GetCellBkColor(LONG sheet,CELL cell);
	LONG GetCellBorderColor(LONG sheet,CELL cell);

	LONG GetCurrentSheetIndex();
	LONG GetSheetCount();
	void DeleteSheet(LONG nIndex);

	LPTSTR GetSheetCaption(LONG sheet);
	void SetSheetCaption(LONG sheet,LPTSTR ptrTxt);
	LPTSTR GetCellMemo(LONG sheet,LONG irow,LONG icol);
	void SetCellMemo(LONG sheet,LONG irow,LONG icol,LPTSTR ptrMemo);
	void SetFreeAreaSize(LONG sheet,const SIZE& size,LONG nFreeID);

};
#endif
#endif
#endif // !defined(AFX_LEXPORT_H__1E01CFE6_3045_4FA4_B11C_D7893E069E4F__INCLUDED_)
