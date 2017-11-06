// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "clgridbook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// _ICLBookLibEvents properties

/////////////////////////////////////////////////////////////////////////////
// _ICLBookLibEvents operations


/////////////////////////////////////////////////////////////////////////////
// ICLBookLib properties

/////////////////////////////////////////////////////////////////////////////
// ICLBookLib operations

long ICLBookLib::AttachWidow(long hWnd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		hWnd);
	return result;
}

void ICLBookLib::DeattachWindow()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long ICLBookLib::AddSheet(LPCTSTR ptrName, long index)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ptrName, index);
	return result;
}

long ICLBookLib::GetCurrentSheet()
{
	long result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICLBookLib::GetRows(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetRows(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::GetCols(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetCols(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::GetFixedRows(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetFixedRows(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::GetFreezeRows(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetFreezeRows(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::GetFixedCols(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetFixedCols(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::GetFreezeCols(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetFreezeCols(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

void ICLBookLib::PrintMe(long bPrintAll)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPrintAll);
}

CString ICLBookLib::GetTextMatrix(long sheet, long row, long col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		sheet, row, col);
	return result;
}

void ICLBookLib::SetTextMatrix(long sheet, long row, long col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, row, col, lpszNewValue);
}

long ICLBookLib::GetRowHeight(long sheet, long row)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, row);
	return result;
}

void ICLBookLib::SetRowHeight(long sheet, long row, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, row, nNewValue);
}

long ICLBookLib::GetColWidth(long sheet, long col)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, col);
	return result;
}

void ICLBookLib::SetColWidth(long sheet, long col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, col, nNewValue);
}

long ICLBookLib::GetBorderLineStyle(long sheet, long irow, long icol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, irow, icol);
	return result;
}

void ICLBookLib::SetBorderLineStyle(long sheet, long irow, long icol, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, irow, icol, nNewValue);
}

void ICLBookLib::AppendACol(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::AppendARow(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::ClearCellData(long sheet, long nRow, long nCol)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nRow, nCol);
}

void ICLBookLib::ClearCurrentRangeData(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::CopyData(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::PasteData(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::DeleteCurrentCol(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::SetCurrentRangeBkColor(long sheet, long clr)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, clr);
}

void ICLBookLib::SetCurrentRangeForeColor(long sheet, long clr)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, clr);
}

void ICLBookLib::SetCurrentRangeBorderLineStyle(long sheet, long nStyle)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nStyle);
}

long ICLBookLib::GetIsCellReadOnly(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

void ICLBookLib::SetIsCellReadOnly(long sheet, long nRow, long nCol, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nRow, nCol, nNewValue);
}

void ICLBookLib::SetCurrentRangeReadOnly(long sheet, long bVal)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, bVal);
}

long ICLBookLib::SaveData(LPCTSTR strFile)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		strFile);
	return result;
}

long ICLBookLib::LoadData(LPCTSTR strFile)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		strFile);
	return result;
}

void ICLBookLib::SetCurrentRangeFontBold(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::SetCurrentRangeFontItalic(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::SetCurrentRangeFontUnderline(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::SetCurrentRangeFontHorzAlign(long sheet, long nAlign)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nAlign);
}

long ICLBookLib::GetIsFontUnderline(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsAlignLeft(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsAlignRight(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsFontBold(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsFontItalic(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetFocusRow(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::GetFocusCol(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::GetIsAlignTop(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsAlignMiddle(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsAlignBottom(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

void ICLBookLib::SetCurrentRangeFontVertAlign(long sheet, long nAlign)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nAlign);
}

void ICLBookLib::SetCurrentRangeBorderColor(long sheet, long clr)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, clr);
}

void ICLBookLib::SetCurrentRangeFontName(long sheet, LPCTSTR ptrName, long bytChatSet)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, ptrName, bytChatSet);
}

void ICLBookLib::SetCurrentRangeFontSize(long sheet, long nSize)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nSize);
}

CString ICLBookLib::GetGetFontName(long sheet, long nRow, long nCol)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetGetFontSize(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

long ICLBookLib::GetIsAlignCenter(long sheet, long nRow, long nCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

void ICLBookLib::MergeCells(long sheet, long nBeginRow, long nBeginCol, long nEndRow, long nEndCol, long* retVal)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, nBeginRow, nBeginCol, nEndRow, nEndCol, retVal);
}

long ICLBookLib::MergeCurrentRange(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::UnMergeCurrentRange(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::GetGridLineStyle(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

void ICLBookLib::SetGridLineStyle(long sheet, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nNewValue);
}

long ICLBookLib::AddBitmapPan(long sheet, LPCTSTR ptrName)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sheet, ptrName);
	return result;
}

void ICLBookLib::DeleteCurrentRow(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::CutCurrentData(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::InsertARow(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

void ICLBookLib::InsertACol(long sheet)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet);
}

long ICLBookLib::GetCurrentCellBkColor(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::GetCurrentCellBorderColor(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

long ICLBookLib::GetCurrentCellForeColor(long sheet)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		sheet);
	return result;
}

CString ICLBookLib::GetMemoText(long sheet, long nRow, long nCol)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		sheet, nRow, nCol);
	return result;
}

void ICLBookLib::SetMemoText(long sheet, long nRow, long nCol, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sheet, nRow, nCol, lpszNewValue);
}

long ICLBookLib::GetCurrentSheetIndex()
{
	long result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICLBookLib::SetCurrentSheetIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ICLBookLib::GetSheetCount()
{
	long result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString ICLBookLib::GetSheetCaption(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

void ICLBookLib::SetSheetCaption(long index, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, lpszNewValue);
}

void ICLBookLib::SetBorderLineDot(long sheet, long style)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, style);
}

long ICLBookLib::GetBorderLineDot(long sheet, long row, long col)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x45, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sheet, row, col);
	return result;
}

void ICLBookLib::SetCashStyle(long sheet, long style)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sheet, style);
}

long ICLBookLib::GetCashStyle(long sheet, long row, long col)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sheet, row, col);
	return result;
}

void ICLBookLib::DeleteSheet(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x48, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}
