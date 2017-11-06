//////////////////////////////////////////////////////////////////////
//@模块		 ：导出对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LExport.h"
#if _EXPORT_TYPE_!=2
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#if _EXPORT_TYPE_==0
CLExport::CLExport()
{

}

CLExport::~CLExport()
{

}


PRIVATE_API(CLBook*,GetBook)()
{
	return g_rptGrid.GetBook();
}
#endif
#if _EXPORT_TYPE_==1
	WIN_API(LONG,CreateReport)()
	{
		CLRptGrid* pRpt=new CLRptGrid();
		return (LONG)pRpt;
	}
	WIN_API(LONG,GetBook)(LONG rptHandle)
	{
		CLRptGrid* pRpt=(CLRptGrid*)rptHandle;
		return (LONG)&pRpt->m_book;
	}
#endif
WIN_API(void,GetCurrentRange)(LONG sheet,RANGE& range)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		ptrTable->GetCurrentRange(range);
	} 
}
WIN_API(BOOL,AddBitmapPan)(PARAM_BOOK SP_DOT LONG sheet,LPTSTR ptrName)
{
	CLBook* ptr=BOOK_PTR;
	return ptr->AddBitmapPan(sheet,ptrName);
}
WIN_API(BOOL,GetCurrentCell)(LONG sheet,CELL& cell)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	ptrTable->GetCurrentCell(cell);
	return cell.Row>=0 && cell.Col>=0;
}
WIN_API(LONG,GetFontSize)(LONG sheet, LONG nRow, LONG nCol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	return ptrTable->GetFontSize(nRow,nCol);
}
WIN_API(LPTSTR,GetFontName)(LONG sheet, LONG nRow, LONG nCol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	return ptrTable->GetFontName(nRow,nCol);
}
WIN_API(void,SetCurrentRangeFontSize)(LONG sheet, LONG nSize)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetFontSize(range,nSize);
	}
}
WIN_API(void,SetCurrentRangeFontName)(LONG sheet, LPTSTR ptrName, LONG bytChatSet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetFontName(range,ptrName,bytChatSet);
	}
}
WIN_API(LONG,GetGridLineStyle)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	return ptrSheet->GetSheetLineStyle();
}
WIN_API(void,SetGridLineStyle)(LONG sheet,LONG style)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ptrSheet->SetSheetLineStyle(style);
}
WIN_API(void,SetCurrentRangeBorderColor)(LONG sheet, LONG clr)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetBorderColor(range,clr);
	}
}
WIN_API(void,SetCurrentRangeFontItalic)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetFontItalic(range,!ptrTable->IsFontItalic(range.m_posRow.m_begin,
			range.m_posCol.m_begin));
	}
}
WIN_API(void,SetCurrentRangeFontBold)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetFontBold(range,!ptrTable->IsFontBold(range.m_posRow.m_begin,
			range.m_posCol.m_begin));
	}
}
WIN_API(void,SetCurrentRangeBorderLineStyle)(LONG sheet, LONG nStyle)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetBorderStyle(range,nStyle);
	}
}
WIN_API(void,SetCurrentRangeForeColor)(LONG sheet, LONG clr)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetForeColor(range,clr);
	}
}
WIN_API(void,SetCurrentRangeBkColor)(LONG sheet, LONG clr)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetBkColor(range,clr);
	}
}
WIN_API(void,DeleteCurrentCol)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->DeleteCurrentCol();
	}
}
WIN_API(void,CutCurrentData)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->CutDataToClipBox();
	}
}

WIN_API(void,InsertACol)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->InsertCol();
	}
}

WIN_API(void,InsertARow)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->InsertRow();
	}
}

WIN_API(void,DeleteCurrentRow)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->DeleteCurrentRow();
	}
}
WIN_API(void,PasteData)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->GetDataFromClipBox();
	}
}
WIN_API(void,CopyData)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		ptrGrid->CopyDataToClipBox();
	}
}
WIN_API(void,ClearCurrentRangeData)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		RANGE range;
		ptrGrid->GetTable()->GetCurrentRange(range);
		ptrGrid->ClearRangeData(range);
	}
}
WIN_API(void,ClearCellData)(LONG sheet, LONG nRow, LONG nCol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->ClearCellData(nRow,nCol);
}
WIN_API(LONG,GetCurrentSheet)(PARAM_BOOK)
{
	CLBook* ptr= BOOK_PTR;
	return (LONG)ptr->GetCurrentSheet();
}
WIN_API(LONG,GetSheet)(PARAM_BOOK SP_DOT LONG nIndex){
	CLBook* ptr= BOOK_PTR;
	return (LONG)ptr->GetSheet(nIndex);
}
WIN_API(BOOL,AttachWidow)(PARAM_RPT SP_DOT HWND hWnd)
{
	CLRptGrid* ptr= RPT_PTR;
	return ptr->AttachWidow(hWnd);
}
WIN_API(void,DeattachWindow)(PARAM_RPT)
{
	CLRptGrid* ptr= RPT_PTR;
	ptr->DeattachWindow();
#if _EXPORT_TYPE_==1
	delete ptr;
#endif
}
WIN_API(BOOL,SaveBook)(PARAM_BOOK SP_DOT LPTSTR ptrName)
{
	CLBook* ptr= BOOK_PTR;
	if(ptr){
		CLSerial ar(ptrName,FALSE);
		return ptr->OnSerial(ar);
	}else
		return FALSE;
}
WIN_API(void,AppendACol)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid)
		ptrGrid->AppendCol();
}
WIN_API(void,AppendARow)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid)
		ptrGrid->AppendRow();
}
WIN_API(BOOL,LoadBook)(PARAM_BOOK SP_DOT LPTSTR ptrName)
{
	CLBook* ptr=BOOK_PTR;
	if(ptr){
		CLSerial ar(ptrName,TRUE);
		return ptr->OnSerial(ar);
	}else
		return FALSE;
}
WIN_API(BOOL,AddDrawItem)(LONG sheet,LPVOID ptrItem)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	if(ptrSheet && ptrItem){
		LONG ret= ptrSheet->AddDrawItem((CLDrawItemBase*)ptrItem);
		return ret!=-1;
	}else
		return FALSE;
}

WIN_API(LONG,AddLinstener)(LONG sheet,LPVOID ptrObj,LONG msgID,BOOL bAddHeader)
{
	ISheet* pSheet=(ISheet*)sheet;
	ICallServ* ptrSrv=pSheet->GetCallServ();
	ASSERT(ptrSrv);
	return ptrSrv->AddLinstener((ICallBack*)ptrObj,msgID,bAddHeader);
}
WIN_API(BOOL,SetMessageFilter)(LONG sheet,LPVOID ptrFun)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	if(ptrSheet){
		return ptrSheet->SetMessageFilter(ptrFun);
	}else{
		return FALSE;
	}
}
WIN_API(BOOL,RemoveMessageFilter)(LONG sheet,LPVOID ptrFun)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	if(ptrSheet){
		return ptrSheet->RemoveMessageFilter(ptrFun);
	}else{
		return FALSE;
	}
}
WIN_API(void,SetFocusItem)(LONG sheet,LPVOID ptrItem)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	if(ptrSheet)
		ptrSheet->SetFocusItem((CLDrawItemBase*)ptrItem);
}
WIN_API(LONG,NotifyMessage)(LONG sheet,LONG msgID,LPVOID param)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ICallServ* ptrCall=ptrSheet->GetCallServ();
	if(ptrCall)
		return ptrCall->NotifyMessage(msgID,param);
	else
		return -1;
}
WIN_API(LONG,AddSheet)(PARAM_BOOK SP_DOT LPTSTR ptrName,LONG nIndex)
{
	CLBook* ptr=BOOK_PTR;
	return (LONG)(ptr->AddSheet(ptrName,nIndex));
}
WIN_API(void,SetCurrentSheet)(PARAM_BOOK SP_DOT LONG nIndex)
{
	CLBook* ptr=BOOK_PTR;
	ptr->SetCurrentSheetIndex(nIndex);
}
WIN_API(LONG,GetCurrentSheetIndex)(PARAM_BOOK)
{
	CLBook* ptr=BOOK_PTR;
	return ptr->GetCurrentSheetIndex();
}
WIN_API(LONG,GetSheetCount)(PARAM_BOOK)
{
	CLBook* ptr=BOOK_PTR;
	return ptr->GetCount();
}
WIN_API(void,DeleteSheet)(PARAM_BOOK SP_DOT LONG nIndex)
{
	CLBook* ptr=BOOK_PTR;
	ptr->DeleteSheet(nIndex);
}
WIN_API(void,SetRows)(LONG sheet,LONG irows)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetRows(irows);
}
WIN_API(LONG,GetRows)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetRows();
	else
		return 0;
}
WIN_API(void,SetCols)(LONG sheet,LONG icols)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetCols(icols);
}
WIN_API(LONG,GetCols)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetCols();
	else
		return 0;
}
WIN_API(void,SetFixedRows)(LONG sheet,LONG irows)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetFixedRows(irows);
}
WIN_API(LONG,GetFixedRows)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetFixedRows();
	else
		return 0;
}
WIN_API(void,SetFixedCols)(LONG sheet,LONG icols)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetFixedCols(icols);
}
WIN_API(LONG,GetFixedCols)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetFixedCols();
	else
		return 0;
}
WIN_API(void,SetFreezeRows)(LONG sheet,LONG irows)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetFreezeRows(irows);
}
WIN_API(LONG,GetFreezeRows)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetFreezeRows();
	else
		return 0;
}
WIN_API(void,SetFreezeCols)(LONG sheet,LONG icols)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetFreezeCols(icols);
}
WIN_API(LONG,GetFreezeCols)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetFreezeCols();
	else
		return 0;
}

WIN_API(void,BringDrawItemToFront)(LONG sheet,LPVOID ptrItem)
{
	if(ptrItem){
		ISheet* ptrSheet=(ISheet*)sheet;
		ASSERT(ptrSheet);
		ptrSheet->BringToFront((CLDrawItemBase*)ptrItem);
	}
}
WIN_API(void,BringDrawItemToBack)(LONG sheet,LPVOID ptrItem)
{
	if(ptrItem){
		ISheet* ptrSheet=(ISheet*)sheet;
		ASSERT(ptrSheet);
		ptrSheet->BringToBack((CLDrawItemBase*)ptrItem);
	}
}
WIN_API(void,BringDrawItemToTop)(LONG sheet,LPVOID ptrItem)
{
	if(ptrItem){
		ISheet* ptrSheet=(ISheet*)sheet;
		ASSERT(ptrSheet);
		ptrSheet->BringToTop((CLDrawItemBase*)ptrItem);
	}
}
WIN_API(void,BringDrawItemToBottom)(LONG sheet,LPVOID ptrItem)
{
	if(ptrItem){
		ISheet* ptrSheet=(ISheet*)sheet;
		ASSERT(ptrSheet);
		ptrSheet->BringToBottom((CLDrawItemBase*)ptrItem);
	}
}
/*
WIN_API(LPTSTR,GetLabelText)(LONG sheet,LONG irow,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetCellMemo(irow,icol);
	else
		return NULL;
}
WIN_API(void,SetLabelText)(LONG sheet,LONG irow,LONG icol,LPTSTR ptrTxt)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetCellMemo(irow,icol,ptrTxt);
}
*/
WIN_API(LPTSTR,GetTextMatrix)(LONG sheet,LONG irow,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetCellText(irow,icol);
	else
		return NULL;
}
WIN_API(void,SetTextMatrix)(LONG sheet,LONG irow,LONG icol,LPTSTR ptrTxt)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetCellText(irow,icol,ptrTxt);
}
WIN_API(LONG,GetRowHeight)(LONG sheet,LONG irow)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetRowHeight(irow);
	else
		return 0;
}
WIN_API(void,SetRowHeight)(LONG sheet,LONG irow,LONG vheight)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetRowHeight(irow,vheight);
}
WIN_API(LONG,GetColWidth)(LONG sheet,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		return ptrTable->GetColWidth(icol);
	else
		return 0;
}
WIN_API(void,SetColWidth)(LONG sheet,LONG icol,LONG vwidth)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable)
		ptrTable->SetColWidth(icol,vwidth);
}
WIN_API(BOOL,PrintBook)(PARAM_BOOK SP_DOT BOOL bPrintAll)
{
	CLBook* ptrBook=BOOK_PTR;
	if(ptrBook){
		return ptrBook->OnPrint(bPrintAll);
	}else{
		return FALSE;
	}
}
WIN_API(BOOL,MergeRange)(LONG sheet,LONG rowBegin,
						 LONG colBegin,LONG rowEnd,LONG colEnd)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		RANGE range;
		range.m_posRow.m_begin=rowBegin;
		range.m_posRow.m_end=rowEnd;
		range.m_posCol.m_begin=colBegin;
		range.m_posCol.m_end=colEnd;
		return ptrGrid->MergeRange(range);
	}else
		return FALSE;
}
WIN_API(BOOL,RemoveMergeRange)(LONG sheet,LONG rowBegin,
							   LONG colBegin,LONG rowEnd,LONG colEnd)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	if(ptrGrid){
		RANGE range;
		range.m_posRow.m_begin=rowBegin;
		range.m_posRow.m_end=rowEnd;
		range.m_posCol.m_begin=colBegin;
		range.m_posCol.m_end=colEnd;
		return ptrGrid->RemoveMergeRange(range);
	}else
		return FALSE;
}
WIN_API(LONG,GetBorderStyle)(LONG sheet,LONG irow,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	CELL cell(irow,icol);
	return ptrTable->GetBorderStyle(cell);
}
WIN_API(void,SetBorderStyle)(LONG sheet,LONG irow,LONG icol,LONG style)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	CELL cell(irow,icol);
	ptrTable->SetBorderStyle(cell,style);
}
WIN_API(BOOL,MergeCurrentRange)(LONG sheet,LONG nType)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	return ptrGrid->MergeCurrentRange(nType);
}
WIN_API(void,SetReadOnly)(LONG sheet,BOOL val)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetRangeReadOnly(range,val);
	}
}
WIN_API(BOOL,IsReadOnly)(LONG sheet)
{
	BOOL bret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		bret=ptrTable->IsRangeReadOnly(range);
	}
	return bret;
}
WIN_API(BOOL,UnMergeCurrentRange)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	return ptrGrid->UnMergeCurrentRange();
}
WIN_API(BOOL,isHorzAlignPos)(LONG sheet,LONG irow,LONG icol,enum_horz_align pos)
{
	BOOL ret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		switch(pos){
		case horz_align_left:
			ret=ptrTable->IsAlignLeft(irow,icol);
			break;
		case horz_align_center:
			ret=ptrTable->IsAlignCenter(irow,icol);
			break;
		case horz_align_right:
			ret=ptrTable->IsAlignRight(irow,icol);
			break;
		}
		
	}
	return ret;
}

WIN_API(BOOL,isVertAlignPos)(LONG sheet,LONG irow,LONG icol,enum_vert_align pos)
{
	BOOL ret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		switch(pos){
		case vert_align_top:
			ret=ptrTable->IsAlignTop(irow,icol);
			break;
		case vert_align_middle:
			ret=ptrTable->IsAlignMiddle(irow,icol);
			break;
		case vert_align_bottom:
			ret=ptrTable->IsAlignBottom(irow,icol);
			break;
		}
		
	}
	return ret;
}

WIN_API(void,setRangeHorzAlignPos)(LONG sheet,RANGE& range,enum_horz_align pos)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		switch(pos){
		case horz_align_left:
			ptrTable->SetAlignLeft(range);
			break;
		case horz_align_center:
			ptrTable->SetAlignCenter(range);
			break;
		case horz_align_right:
			ptrTable->SetAlignRight(range);
			break;
		}
	}
}
WIN_API(void,setRangeVertAlignPos)(LONG sheet,RANGE& range,enum_vert_align pos)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		switch(pos){
		case vert_align_top:
			ptrTable->SetAlignTop(range);
			break;
		case vert_align_middle:
			ptrTable->SetAlignMiddle(range);
			break;
		case vert_align_bottom:
			ptrTable->SetAlignBottom(range);
			break;
		}
	}
}
WIN_API(void,setHorzAlignPos)(LONG sheet,LONG irow,LONG icol,enum_horz_align pos)
{
	RANGE range;
	range.SetSingleCellRange(CELL(irow,icol));
	setRangeHorzAlignPos(sheet,range,pos);
}
WIN_API(void,setVertAlignPos)(LONG sheet,LONG irow,LONG icol,enum_vert_align pos)
{
	RANGE range;
	range.SetSingleCellRange(CELL(irow,icol));
	setRangeVertAlignPos(sheet,range,pos);
}
WIN_API(BOOL,IsFontUnderline)(LONG sheet,LONG irow,LONG icol)
{
	BOOL ret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		ret=ptrTable->IsFontUnderline(irow,icol);
	}
	return ret;
}
WIN_API(void,SetCurrentRangeFontUnderLine)(LONG sheet)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetFontUnderline(range,!ptrTable->IsFontUnderline(range.m_posRow.m_begin,
			range.m_posCol.m_begin));
	}
}
WIN_API(BOOL,IsFontBold)(LONG sheet,LONG irow,LONG icol)
{
	BOOL ret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		ret=ptrTable->IsFontBold(irow,icol);
	}
	return ret;
}
WIN_API(BOOL,IsFontItalic)(LONG sheet,LONG irow,LONG icol)
{
	BOOL ret=FALSE;
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		ret=ptrTable->IsFontItalic(irow,icol);
	}
	return ret;
}
WIN_API(LONG,GetCellForeColor)(LONG sheet,CELL cell)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		ptrGrid->GetMasterCell(cell);
		CLFont* ptrFont=ptrTable->GetCellFont(cell);
		if(ptrFont)
			return (LONG)ptrFont->m_clr;
	}
	return 0;
}
WIN_API(LONG,GetCellBkColor)(LONG sheet,CELL cell)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		ptrGrid->GetMasterCell(cell);
		CLStyle* pStyle=ptrTable->GetCellStyle(cell);
		if(pStyle)
			return (LONG)pStyle->GetBkColor();
	}
	return 0;
}
WIN_API(LONG,GetCellBorderColor)(LONG sheet,CELL cell)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		ptrGrid->GetMasterCell(cell);
		CLStyle* pStyle=ptrTable->GetCellStyle(cell);
		if(pStyle)
			return (LONG)pStyle->GetBorderColor();
	}
	return 0;
}
WIN_API(LPTSTR,GetSheetCaption)(PARAM_BOOK SP_DOT LONG index)
{
	CLBook* ptr=BOOK_PTR;
	return ptr->GetPageName(index);
}
WIN_API(void,SetSheetCaption)(PARAM_BOOK SP_DOT LONG index,LPTSTR ptrTxt)
{
	CLBook* ptr=BOOK_PTR;
	if(ptr)
		ptr->SetPageName(index,ptrTxt);
}

WIN_API(LPTSTR,GetCellMemo)(LONG sheet,LONG irow,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		return ptrTable->GetCellMemo(irow,icol);
	}else{
		return NULL;
	}
}
WIN_API(void,SetCellMemo)(LONG sheet,LONG irow,LONG icol,LPTSTR ptrMemo)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		ptrTable->SetCellMemo(irow,icol,ptrMemo);
	}
}

WIN_API(void,SetBorderLineDot)(LONG sheet,LONG style)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetBorderLineStyle(range,style);
	}
}
WIN_API(LONG,GetBorderLineDot)(LONG sheet,LONG irow,LONG icol)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		return ptrTable->GetBorderLineStyle(CELL(irow,icol));
	}
	return BORDER_NO_LINE_DOT;
}

WIN_API(void,SetCashStyle)(LONG sheet,LONG style)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
	if(ptrTable){
		RANGE range;
		ptrTable->GetCurrentRange(range);
		ptrTable->SetCashStyle(range,style);
	}
}
WIN_API(LONG,GetCashStyle)(LONG sheet,LONG irow,LONG icol)
{

	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		return ptrTable->GetCashStyle(CELL(irow,icol));
	}
	return NO_CASH_STYLE;
}
WIN_API(void,SetFreeAreaSize)(LONG sheet,const SIZE& size,LONG nFreeID)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	IGrid* ptrGrid=ptrSheet->GetGrid();
	ITable* ptrTable=ptrGrid->GetTable();
	if(ptrTable){
		ptrTable->SetFreeAreaSize(size,nFreeID);
	}
}
#endif