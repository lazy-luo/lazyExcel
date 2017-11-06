// CLBookLib.cpp : Implementation of CCLBookLib
#include "stdafx.h"
#include "CLGridBook.h"
#include "CLBookLib.h"

/////////////////////////////////////////////////////////////////////////////
// CCLBookLib

STDMETHODIMP CCLBookLib::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICLBookLib
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCLBookLib::AttachWidow(LONG hWnd, LONG *pret)
{
	// TODO: Add your implementation code here
	*pret=m_export.AttachWidow((HWND)hWnd);
	return S_OK;
}

STDMETHODIMP CCLBookLib::DeattachWindow()
{
	// TODO: Add your implementation code here
	m_export.DeattachWindow();
	return S_OK;
}

STDMETHODIMP CCLBookLib::AddSheet(BSTR ptrName, LONG index,LONG *pret)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(ptrName);
	*pret=m_export.AddSheet(ptr,index);
	return S_OK;
}

STDMETHODIMP CCLBookLib::GetCurrentSheet(LONG *sheet)
{
	// TODO: Add your implementation code here
	*sheet=m_export.GetCurrentSheet();
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_Rows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetRows(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_Rows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_Cols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetCols(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_Cols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_FixedRows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFixedRows(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_FixedRows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFixedRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_FreezeRows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFreezeRows(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_FreezeRows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFreezeRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_FixedCols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFixedCols(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_FixedCols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFixedCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_FreezeCols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFreezeCols(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_FreezeCols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFreezeCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::PrintMe(BOOL bPrintAll)
{
	// TODO: Add your implementation code here
	m_export.PrintBook(bPrintAll);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_TextMatrix(LONG sheet, LONG row, LONG col, BSTR *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	LPTSTR ptrTxt=m_export.GetTextMatrix(sheet,row,col);
	if(ptrTxt)
		*pVal=::SysAllocString((OLECHAR*)A2W(ptrTxt));
	else
		*pVal=NULL;
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_TextMatrix(LONG sheet, LONG row, LONG col, BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(newVal);
	m_export.SetTextMatrix(sheet,row,col,ptr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_RowHeight(LONG sheet, LONG row, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetRowHeight(sheet,row);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_RowHeight(LONG sheet, LONG row, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetRowHeight(sheet,row,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_ColWidth(LONG sheet, LONG col, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetColWidth(sheet,col);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_ColWidth(LONG sheet, LONG col, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetColWidth(sheet,col,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_BorderLineStyle(LONG sheet, LONG irow,
											 LONG icol, _tag_BorderLine *pVal)
{
	// TODO: Add your implementation code here
	*pVal=(_tag_BorderLine)m_export.GetBorderStyle(sheet,irow,icol);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_BorderLineStyle(LONG sheet, LONG irow,
											 LONG icol, _tag_BorderLine newVal)
{
	// TODO: Add your implementation code here
	m_export.SetBorderStyle(sheet,irow,icol,(LONG)newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::AppendACol(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.AppendACol(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::AppendARow(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.AppendARow(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::ClearCellData(LONG sheet, LONG nRow, LONG nCol)
{
	// TODO: Add your implementation code here
	m_export.ClearCellData(sheet,nRow,nCol);
	return S_OK;
}

STDMETHODIMP CCLBookLib::ClearCurrentRangeData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.ClearCurrentRangeData(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::CopyData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.CopyData(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::PasteData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.PasteData(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::DeleteCurrentCol(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.DeleteCurrentCol(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeBkColor(LONG sheet, LONG clr)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeBkColor(sheet,clr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeForeColor(LONG sheet, LONG clr)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeForeColor(sheet,clr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeBorderLineStyle(LONG sheet, LONG nStyle)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeBorderLineStyle(sheet,nStyle);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsCellReadOnly(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_IsCellReadOnly(LONG sheet, LONG nRow, LONG nCol, BOOL newVal)
{
	// TODO: Add your implementation code here
	
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeReadOnly(LONG sheet, BOOL bVal)
{
	// TODO: Add your implementation code here
	
	return S_OK;
}

STDMETHODIMP CCLBookLib::SaveData(BSTR strFile, BOOL *pret)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(strFile);
	*pret=m_export.SaveBook(ptr);
	
	return S_OK;
}

STDMETHODIMP CCLBookLib::LoadData(BSTR strFile, BOOL *pret)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(strFile);
	*pret=m_export.LoadBook(ptr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontBold(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeFontBold(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontItalic(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeFontItalic(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontUnderline(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeFontUnderLine(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontHorzAlign(LONG sheet, LONG nAlign)
{
	// TODO: Add your implementation code here
	RANGE range;
	m_export.GetCurrentRange(sheet,range);
	enum_horz_align pos;
	switch(nAlign){
	case 0:
		pos=horz_align_left;
		break;
	case 1:
		pos=horz_align_center;
		break;
	case 2:
		pos=horz_align_right;
		break;
	}
	m_export.setRangeHorzAlignPos(sheet,range,pos);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsFontUnderline(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.IsFontUnderline(sheet,nRow,nCol);
	return S_OK;
}


STDMETHODIMP CCLBookLib::get_IsAlignCenter(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isHorzAlignPos(sheet,nRow,nCol,horz_align_center);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsAlignLeft(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isHorzAlignPos(sheet,nRow,nCol,horz_align_left);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsAlignRight(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isHorzAlignPos(sheet,nRow,nCol,horz_align_right);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsFontBold(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.IsFontBold(sheet,nRow,nCol);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsFontItalic(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.IsFontItalic(sheet,nRow,nCol);
	return S_OK;
}


STDMETHODIMP CCLBookLib::get_FocusRow(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	if(m_export.GetCurrentCell(sheet,cell))
		*pVal=cell.Row;
	return S_OK;
}


STDMETHODIMP CCLBookLib::get_FocusCol(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	if(m_export.GetCurrentCell(sheet,cell))
		*pVal=cell.Col;
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsAlignTop(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isVertAlignPos(sheet,nRow,nCol,vert_align_top);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsAlignMiddle(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isVertAlignPos(sheet,nRow,nCol,vert_align_middle);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_IsAlignBottom(LONG sheet, LONG nRow, LONG nCol, BOOL *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.isVertAlignPos(sheet,nRow,nCol,vert_align_bottom);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontVertAlign(LONG sheet, LONG nAlign)
{
	// TODO: Add your implementation code here
	RANGE range;
	m_export.GetCurrentRange(sheet,range);
	enum_vert_align pos;
	switch(nAlign){
	case 0:
		pos=vert_align_top;
		break;
	case 1:
		pos=vert_align_middle;
		break;
	case 2:
		pos=vert_align_bottom;
		break;
	}
	m_export.setRangeVertAlignPos(sheet,range,pos);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeBorderColor(LONG sheet, LONG clr)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeBorderColor(sheet,clr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontName(LONG sheet, BSTR ptrName, LONG bytChatSet)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(ptrName);
	m_export.SetCurrentRangeFontName(sheet,ptr,bytChatSet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCurrentRangeFontSize(LONG sheet, LONG nSize)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentRangeFontSize(sheet,nSize);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_GetFontName(LONG sheet, LONG nRow, LONG nCol, BSTR *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	*pVal=SysAllocString((OLECHAR*)(A2W(m_export.GetFontName(sheet,nRow,nCol))));
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_GetFontSize(LONG sheet, LONG nRow, LONG nCol, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFontSize(sheet,nRow,nCol);
	return S_OK;
}

STDMETHODIMP CCLBookLib::MergeCells(LONG sheet, LONG nBeginRow,
									LONG nBeginCol, LONG nEndRow, LONG nEndCol, BOOL *retVal)
{
	// TODO: Add your implementation code here
	*retVal=m_export.MergeRange(sheet,nBeginRow,nBeginCol,nEndRow,nEndCol);
	return S_OK;
}

STDMETHODIMP CCLBookLib::MergeCurrentRange(LONG sheet, BOOL *bret)
{
	// TODO: Add your implementation code here
	*bret=m_export.MergeCurrentRange(sheet,MERGE_ALL);
	return S_OK;
}

STDMETHODIMP CCLBookLib::UnMergeCurrentRange(LONG sheet, BOOL *bret)
{
	// TODO: Add your implementation code here
	*bret=m_export.UnMergeCurrentRange(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_GridLineStyle(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetGridLineStyle(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_GridLineStyle(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetGridLineStyle(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::AddBitmapPan(LONG sheet, BSTR ptrName, BOOL *bret)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(ptrName);
	*bret=m_export.AddBitmapPan(sheet,ptr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::DeleteCurrentRow(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.DeleteCurrentRow(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::CutCurrentData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.CutCurrentData(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::InsertARow(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.InsertARow(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::InsertACol(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.InsertACol(sheet);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_CurrentCellBkColor(LONG sheet,LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellBkColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_CurrentCellBorderColor(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellBorderColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_CurrentCellForeColor(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellForeColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_MemoText(LONG sheet, LONG nRow, LONG nCol, BSTR *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	LPTSTR ptrTxt=m_export.GetCellMemo(sheet,nRow,nCol);
	if(ptrTxt)
		*pVal=::SysAllocString((OLECHAR*)A2W(ptrTxt));
	else
		*pVal=NULL;
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_MemoText(LONG sheet, LONG nRow, LONG nCol, BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(newVal);
	m_export.SetCellMemo(sheet,nRow,nCol,ptr);
	return S_OK;
}


STDMETHODIMP CCLBookLib::get_CurrentSheetIndex(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetCurrentSheetIndex();
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_CurrentSheetIndex(long newVal)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentSheet(newVal);
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_SheetCount(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetSheetCount();
	return S_OK;
}

STDMETHODIMP CCLBookLib::get_SheetCaption(LONG index, BSTR *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	LPTSTR ptrTxt=m_export.GetSheetCaption(index);
	if(ptrTxt)
		*pVal=::SysAllocString((OLECHAR*)A2W(ptrTxt));
	else
		*pVal=NULL;
	return S_OK;
}

STDMETHODIMP CCLBookLib::put_SheetCaption(LONG index, BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(newVal);
	m_export.SetSheetCaption(index,ptr);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetBorderLineDot(LONG sheet, LONG style)
{
	// TODO: Add your implementation code here
	m_export.SetBorderLineDot(sheet,style);
	return S_OK;
}

STDMETHODIMP CCLBookLib::GetBorderLineDot(LONG sheet, LONG row, LONG col, LONG *pret)
{
	// TODO: Add your implementation code here
	*pret=m_export.GetBorderLineDot(sheet,row,col);
	return S_OK;
}

STDMETHODIMP CCLBookLib::SetCashStyle(LONG sheet, LONG style)
{
	// TODO: Add your implementation code here
	m_export.SetCashStyle(sheet,style);
	return S_OK;
}

STDMETHODIMP CCLBookLib::GetCashStyle(LONG sheet, LONG row, LONG col, LONG *pret)
{
	// TODO: Add your implementation code here
	*pret=m_export.GetCashStyle(sheet,row,col);
	return S_OK;
}

STDMETHODIMP CCLBookLib::DeleteSheet(LONG index)
{
	// TODO: Add your implementation code here
	m_export.DeleteSheet(index);
	return S_OK;
}
