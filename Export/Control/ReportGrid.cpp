// ReportGrid.cpp : Implementation of CReportGrid

#include "stdafx.h"
#include "GridBook.h"
#include "ReportGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CReportGrid


STDMETHODIMP CReportGrid::get_hWnd(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CReportGrid::AddBitmapPan(LONG sheet, BSTR ptrName, BOOL *bret)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(ptrName);
	*bret=m_export.AddBitmapPan(sheet,ptr);
	return S_OK;
}

STDMETHODIMP CReportGrid::AddSheet(BSTR ptrName, LONG index, LONG *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(ptrName);
	*pVal=m_export.AddSheet(ptr,index);
	return S_OK;
}

STDMETHODIMP CReportGrid::AppendACol(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.AppendACol(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::AppendARow(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.AppendARow(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::ClearCellData(LONG sheet, LONG nRow, LONG nCol)
{
	// TODO: Add your implementation code here
	m_export.ClearCellData(sheet,nRow,nCol);
	return S_OK;
}

STDMETHODIMP CReportGrid::ClearCurrentRangeData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.ClearCurrentRangeData(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::CopyData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.CopyData(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::CutCurrentData(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.CutCurrentData(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::DeleteCurrentCol(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.DeleteCurrentCol(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::DeleteCurrentRow(LONG sheet)
{
	// TODO: Add your implementation code here
	m_export.DeleteCurrentRow(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::DeleteSheet(LONG index)
{
	// TODO: Add your implementation code here
	m_export.DeleteSheet(index);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_Cols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetCols(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_Cols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_Rows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetRows(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_Rows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_ColWidth(LONG sheet, LONG col, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetColWidth(sheet,col);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_ColWidth(LONG sheet, LONG col, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetColWidth(sheet,col,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_CurrentSheetIndex(LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetCurrentSheetIndex();
	return S_OK;
}

STDMETHODIMP CReportGrid::put_CurrentSheetIndex(LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetCurrentSheet(newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_FixedCols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFixedCols(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_FixedCols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFixedCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_FixedRows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFixedRows(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_FixedRows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFixedRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_FreezeCols(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFreezeCols(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_FreezeCols(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFreezeCols(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_FreezeRows(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	*pVal=m_export.GetFreezeRows(sheet);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_FreezeRows(LONG sheet, LONG newVal)
{
	// TODO: Add your implementation code here
	m_export.SetFreezeRows(sheet,newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_TextMatrix(LONG sheet, LONG row, LONG col, BSTR *pVal)
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

STDMETHODIMP CReportGrid::put_TextMatrix(LONG sheet, LONG row, LONG col, BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	TCHAR* ptr=W2A(newVal);
	m_export.SetTextMatrix(sheet,row,col,ptr);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_BorderLineStyle(LONG sheet, LONG irow, LONG icol, _tag_BorderLine *pVal)
{
	// TODO: Add your implementation code here
	*pVal=(_tag_BorderLine)m_export.GetBorderStyle(sheet,irow,icol);
	return S_OK;
}

STDMETHODIMP CReportGrid::put_BorderLineStyle(LONG sheet, LONG irow, LONG icol, _tag_BorderLine newVal)
{
	// TODO: Add your implementation code here
	m_export.SetBorderStyle(sheet,irow,icol,(LONG)newVal);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_CurrentCellBkColor(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellBkColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_CurrentCellBorderColor(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellBorderColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_CurrentCellForeColor(LONG sheet, LONG *pVal)
{
	// TODO: Add your implementation code here
	CELL cell;
	m_export.GetCurrentCell(sheet,cell);
	*pVal=m_export.GetCellForeColor(sheet,cell);
	return S_OK;
}

STDMETHODIMP CReportGrid::get_GetFontName(LONG sheet, LONG nRow, LONG nCol, BSTR *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	*pVal=SysAllocString((OLECHAR*)(A2W(m_export.GetFontName(sheet,nRow,nCol))));
	return S_OK;
}
