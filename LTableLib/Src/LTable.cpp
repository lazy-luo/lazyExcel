//////////////////////////////////////////////////////////////////////
//@模块		 ：表格对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-10
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LTable.h"

#define		MAX_TEST_WIDTH		
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLTable::CLTable():m_ptrOuter(NULL),m_Rows(0),
	m_Cols(0),m_FixedRows(0),m_FixedCols(0),m_FreezeRows(0),
	m_FreezeCols(0)
{
	InitSize();
}
CLTable::~CLTable()
{
	
}

void CLTable::RemoveCellStyle(LONG nRow, LONG nCol)
{
	CELL cell(nRow,nCol);
	m_StyleArr.DeleteValue(cell);
}
void CLTable::SetCols(LONG val)
{
	if(val>0){
		if(m_Cols==0)
			m_hScrollInfo.m_nMaxValue=(DLONG)((DLONG)val*DEFAULT_COL_WIDTH);
		else if(m_Cols>val){
			//减少列
			for(int i=m_Cols-1;i>val-1;i--){
				for(int j=0;j<m_Rows;j++){
					m_CellsArr.DeleteCell(j,i);
				}
				CLColItem* ptrCol=m_ColsArr.GetCol(i);
				m_hScrollInfo.m_nMaxValue-=(DLONG)(ptrCol?ptrCol->GetWidth():
					DEFAULT_COL_WIDTH);
				if(m_hScrollInfo.m_nCurrValue+m_hScrollInfo.m_nExistValue>m_hScrollInfo.m_nMaxValue)
					m_hScrollInfo.m_nCurrValue=m_hScrollInfo.m_nMaxValue-m_hScrollInfo.m_nExistValue;
				m_ColsArr.DeleteCol(i);
			}
			/*如果有必要清除单元格则在此下面写对应代码*/
		}else if(m_Cols<val){
			//增加列
			m_hScrollInfo.m_nMaxValue+=(DLONG)((DLONG)(val-m_Cols)*DEFAULT_COL_WIDTH);
		}
		m_Cols=val;
	}
}
void CLTable::SetRows(LONG val)
{
	if(val>0){
		if(m_Rows==0)
			m_vScrollInfo.m_nMaxValue=(DLONG)((DLONG)val*DEFAULT_ROW_HEIGHT);
		else if(m_Rows>val){
			//减少行
			for(int i=m_Rows-1;i>val-1;i--){
				for(int j=0;j<m_Cols;j++){
					m_CellsArr.DeleteCell(i,j);
				}
				CLRowItem* ptrRow=m_RowsArr.GetRow(i);
				m_vScrollInfo.m_nMaxValue-=(DLONG)(ptrRow?
					ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(m_vScrollInfo.m_nCurrValue+m_vScrollInfo.m_nExistValue>m_vScrollInfo.m_nMaxValue)
					m_vScrollInfo.m_nCurrValue=m_vScrollInfo.m_nMaxValue-m_vScrollInfo.m_nExistValue;
				m_RowsArr.DeleteRow(i);
			}
		}else if(m_Rows<val){
			m_vScrollInfo.m_nMaxValue+=(DLONG)((DLONG)(val-m_Rows)*DEFAULT_ROW_HEIGHT);
		}
		m_Rows=val;
	}
}
void CLTable::SetFixedRows(LONG val)
{
	if(val>=0 && val<m_Rows){
		m_beginCell.Row+=(val-m_FixedRows);
		if(m_beginCell.Row<0)m_beginCell.Row=0;
		m_FixedRows=val;
	}
}
void CLTable::SetFixedCols(LONG val)
{
	if(val>=0 && val<m_Cols){
		m_beginCell.Col+=(val-m_FixedCols);
		if(m_beginCell.Col<0)m_beginCell.Col=0;
		m_FixedCols=val;
	}
}
void CLTable::SetFreezeRows(LONG val)
{

	if(val>=0 && val+m_FixedRows<m_Rows){
		m_beginCell.Row+=(val-m_FreezeRows);
		if(m_beginCell.Row<0)m_beginCell.Row=0;
		m_FreezeRows=val;
	}
}
void CLTable::SetFreezeCols(LONG val)
{
	if(val>=0 && val+m_FixedCols<m_Cols){
		m_beginCell.Col+=(val-m_FreezeCols);
		if(m_beginCell.Col<0)m_beginCell.Col=0;
		m_FreezeCols=val;
	}
}
BOOL CLTable::HasScroll(BOOL bHorz)
{
	BOOL bRet=FALSE;
	SIZE size;

	GetClientSize(size);
	/*
	if(bHorz)
		m_hScrollInfo.m_bVisible=m_hScrollInfo.m_nMaxValue>size.cx;
	else
		m_vScrollInfo.m_bVisible=m_vScrollInfo.m_nMaxValue>size.cy;
	*/
	return bHorz?m_hScrollInfo.m_bVisible:m_vScrollInfo.m_bVisible;
}
__inline CLCellItem* CLTable::GetACell(LONG irow,LONG icol,BOOL bForceNew)
{
	if(irow>=0 && icol>=0)
		return m_CellsArr.GetCell(irow,icol,bForceNew);
	else
		return NULL;
}
__inline CLColItem*	CLTable::GetACol(LONG icol,BOOL bForceNew)
{
	if(icol>=0)
		return m_ColsArr.GetCol(icol,bForceNew);
	else
		return NULL;
}
__inline CLRowItem*	CLTable::GetARow(LONG irow,BOOL bForceNew)
{
	if(irow>=0)
		return m_RowsArr.GetRow(irow,bForceNew);
	else
		return NULL;
}
BOOL CLTable::IsDefaultCellStyle(CLStyle* ptrStyle)
{
	return (ptrStyle==(m_StyleArr.GetDefaultValue()));
}
LONG CLTable::GetColWidth(LONG icol)
{
	CLColItem* ptr=GetACol(icol);
	return (ptr?ptr->GetWidth():DEFAULT_COL_WIDTH);
}
void CLTable::AdjustSizeChange(LONG cx, LONG cy,BOOL bSpecColRowSize)
{
	ASSERT(cx!=0 || cy!=0);
	LPSCROLLINFOEXT ptrinfo=NULL;
	DLONG nleast;
	CELL cell;
	BOOL bFind=FALSE,bSkip=FALSE;
	POINT ptBegin;
	GetBeginCell(cell);
	LONG MinRow=GetFixedRows()+GetFreezeRows(),valT=0,nRow,nCol;
	LONG MinCol=GetFixedCols()+GetFreezeCols();
	GetCellBeginXY(ptBegin);
	CLColItem* ptrCol;
	CLRowItem* ptrRow;
	ptrinfo=GetScrollInfo();
	
	if(cx>0){
		nleast=ptrinfo->m_nMaxValue-ptrinfo->m_nExistValue-ptrinfo->m_nCurrValue;
		if((DLONG)cx>nleast){
			cx-=(nleast);
		}
	}else if(bSpecColRowSize){
		//尺寸减小
		cx=-cx;
	}else
		bSkip=TRUE;
	if(!bSkip){
		if(cx>ptBegin.x){
			cx-=ptBegin.x;
			ptBegin.x=0;
			nCol=cell.Col;
			for(LONG icol=nCol-1;icol>=MinCol;icol--){
				ptrCol=GetACol(icol);
				valT=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				if(cx<=valT){
					bFind=TRUE;
					if(cx==valT){
						cell.Col=(icol-1<MinCol?MinCol:icol-1);
					}else{
						cell.Col=icol;
						ptBegin.x=valT-cx;
					}
					break;
				}
				cx-=valT;
			}
			if(!bFind){
				cell.Col=MinCol;
				ptBegin.x=0;
				ptrinfo->m_nCurrValue=0;
			}
		}else{
			ptBegin.x-=cx;
		}
	}
	bFind=FALSE;
	bSkip=FALSE;
	ptrinfo=GetScrollInfo(FALSE);
	if(cy>0){
		nleast=ptrinfo->m_nMaxValue-ptrinfo->m_nExistValue-ptrinfo->m_nCurrValue;
		if((DLONG)cy>nleast){
			cy-=nleast;
		}
	}else if(bSpecColRowSize){
		//尺寸减小
		cy=-cy;
	}else
		bSkip=TRUE;
	if(!bSkip){
		if(cy>ptBegin.y){
			cy-=ptBegin.y;
			ptBegin.y=0;
			nRow=cell.Row;
			for(LONG irow=nRow-1;irow>=MinRow;irow--){
				ptrRow=GetARow(irow);
				valT=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(cy<=valT){
					bFind=TRUE;
					if(cy==valT){
						cell.Row=(irow-1<MinRow?MinRow:irow-1);
					}else{
						cell.Row=irow;
						ptBegin.y=valT-cy;
					}
					break;
				}
				cy-=valT;
			}
			if(!bFind){
				cell.Row=MinRow;
				ptBegin.y=0;
				ptrinfo->m_nCurrValue=0;
			}
		}else{
			ptBegin.y-=cy;
		}
	}
	SetCellBeginXY(ptBegin);
	SetBeginCell(cell);
}
void CLTable::SetColWidth(LONG icol, LONG val)
{
	if(val<0)val=0;
	CLColItem* ptr=GetACol(icol,TRUE);
	LONG deff=val-ptr->GetWidth();
	m_hScrollInfo.m_nMaxValue+=deff;//(DLONG)(val-ptr->GetWidth());
	if(deff<0){
		m_hScrollInfo.m_nCurrValue+=(DLONG)deff;
		if(m_hScrollInfo.m_nCurrValue<0)
			m_hScrollInfo.m_nCurrValue=0;
	}
	ptr->SetWidth(val);
	if(deff<0)
		AdjustSizeChange(deff,0,TRUE);
}

LONG CLTable::GetRowHeight(LONG irow)
{
	CLRowItem* ptrRow=GetARow(irow);
	return (ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
}

void CLTable::SetRowHeight(LONG irow, LONG val)
{
	if(val<0)val=0;
	CLRowItem* ptrRow=GetARow(irow,TRUE);
	LONG deff=val-ptrRow->GetHeight();
	m_vScrollInfo.m_nMaxValue+=deff;//(DLONG)(val-ptrRow->GetHeight());
	if(deff<0){
		m_vScrollInfo.m_nCurrValue+=(DLONG)deff;
		if(m_vScrollInfo.m_nCurrValue<0)
			m_vScrollInfo.m_nCurrValue=0;
	}
	ptrRow->SetHeight(val);
	if(deff<0)
		AdjustSizeChange(0,deff,TRUE);
	
}

CLStyle* CLTable::GetCellStyle(LONG irow,LONG icol,BOOL bForceNew)
{
	CELL cell(irow,icol);
	return GetCellStyle(cell,bForceNew);
}
CLStyle* CLTable::GetCellStyle(const CELL& cell,BOOL bForceNew)
{
	return m_StyleArr.GetValue(cell,bForceNew);
}
CLFont* CLTable::GetCellFont(const CELL& cell,BOOL bForceNew)
{
	CLStyle* ptrStyle=m_StyleArr.GetValue(cell,bForceNew);
	LONG nIndex=ptrStyle->GetFontIndex();
	INDEX index;
	index.Index=nIndex;
	CLFont* ptrFont=m_FontArr.GetValue(index,bForceNew);
	if(index.Index!=nIndex)
		ptrStyle->SetFontIndex(index.Index);
	return ptrFont;
}

BOOL CLTable::CanScroll(BOOL bHorz,BOOL bAddValue)
{
	if(!HasScroll(bHorz))return FALSE;
	LPSCROLLINFOEXT lpinfo=(bHorz?&m_hScrollInfo:&m_vScrollInfo);
	DLONG val=lpinfo->m_nMaxValue-(lpinfo->m_nCurrValue+lpinfo->m_nExistValue);
	return (bAddValue?val>0:val>=0 && lpinfo->m_nCurrValue>0);
}

LONG CLTable::GetFontSize(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return ptrFont->m_lf.lfHeight;
#else
	return GetCellFont(cell)->m_lf.lfHeight;
#endif
}
LPTSTR CLTable::GetFontName(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return ptrFont->m_lf.lfFaceName;
#else
	return GetCellFont(cell)->m_lf.lfFaceName;
#endif
}
void CLTable::SetFontSize(RANGE &range,LONG iSize)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTSIZE, \
			(WPARAM)&range,iSize);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_lf.lfHeight=iSize;
				ptrItem->m_lf.lfWidth=0;
			}
		}
		ReDraw();
	}
}
void CLTable::SetFontName(RANGE& range,LPTSTR ptrName,BYTE bytChatSet)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTNAME, \
			(WPARAM)&range,(LPARAM)ptrName);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				strncpy(ptrItem->m_lf.lfFaceName, ptrName, LF_FACESIZE);
				ptrItem->m_lf.lfCharSet=bytChatSet;
				ptrItem->m_lf.lfWidth=0;
			}
		}
		ReDraw();
	}
}
void CLTable::SetBkColor(RANGE& range,COLORREF clr)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_BKCOLOR, \
			(WPARAM)&range,(LPARAM)clr);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellStyle(cell,TRUE);
				ptrItem->SetBkColor(clr);
			}
		}
		ReDraw();
	}
}
void CLTable::SetBorderStyle(const RANGE& range,LONG style)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellStyle(cell,TRUE);
				ptrItem->SetBorderStyle(style);
			}
		}
		ReDraw();
	}
}
void CLTable::SetCashStyle(const RANGE& range,LONG style)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellStyle(cell,TRUE);
				ptrItem->SetType(style);
			}
		}
		ReDraw();
	}
}
void CLTable::SetBorderLineStyle(const RANGE& range,LONG style)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellStyle(cell,TRUE);
				ptrItem->SetBorderLineStyle(style);
			}
		}
		ReDraw();
	}
}
void CLTable::SetForeColor(RANGE& range,COLORREF clr)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTCOLOR, \
			(WPARAM)&range,(LPARAM)clr);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrFont;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrFont=GetCellFont(cell,TRUE);
				ptrFont->m_clr=clr;
			}
		}
		ReDraw();
	}
}

void CLTable::SetFormulaValue(LONG nRow,LONG nCol,char* pValue)
{
	CELL cell(nRow,nCol);
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	CLStyle* ptrStyle=GetCellStyle(cell,TRUE);
	ptrStyle->SetValue(pValue);
}
LPTSTR CLTable::GetFormulaValue(LONG nRow,LONG nCol)
{
	CELL cell(nRow,nCol);
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	CLStyle* ptrStyle=GetCellStyle(cell,TRUE);
	return ptrStyle->GetValue();
}
BOOL CLTable::IsFormulaCell(LONG nRow,LONG nCol)
{
	CELL cell(nRow,nCol);
	CLStyle* ptrStyle=GetCellStyle(cell);
	return (NULL!=ptrStyle->GetValue());
}
void CLTable::SetBorderColor(RANGE& range,COLORREF clr)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_BORDERCOLOR, \
			(WPARAM)&range,(LPARAM)clr);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellStyle(cell,TRUE);
				ptrItem->SetBorderColor(clr);
			}
		}
		ReDraw();
	}
}
BOOL CLTable::IsAlignBottom(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignVert==avBOTTOM);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignVert)==avBOTTOM);
#endif
}
BOOL  CLTable::IsAlignMiddle(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignVert==avCENTER);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignVert)==avCENTER);
#endif
}
BOOL CLTable::IsAlignTop(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignVert==avTOP);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignVert)==avTOP);
#endif
}
void CLTable::SetAlignBottom(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignVert=avBOTTOM;
			}
		}
		ReDraw();
	}
}
void CLTable::SetAlignMiddle(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignVert=avCENTER;
			}
		}
		ReDraw();
	}
}
void CLTable::SetAlignTop(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignVert=avTOP;
			}
		}
		ReDraw();
	}
}
BOOL CLTable::IsAlignRight(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignHorz==ahRIGHT);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignHorz)==ahRIGHT);
#endif
}
BOOL CLTable::IsAlignCenter(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignHorz==ahCENTER);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignHorz)==ahCENTER);
#endif
}
BOOL CLTable::IsAlignLeft(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_Alignment.bAlignHorz==ahLEFT);
#else
	return ((GetCellFont(cell)->m_Alignment.bAlignHorz)==ahLEFT);
#endif
}
BOOL CLTable::IsFontBold(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return (ptrFont->m_lf.lfWeight == FW_BOLD);
#else
	return ((GetCellFont(cell)->m_lf.lfWeight) == FW_BOLD);
#endif
}
BOOL CLTable::IsFontItalic(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return ptrFont->m_lf.lfItalic;
#else
	return GetCellFont(cell)->m_lf.lfItalic;
#endif
}
BOOL CLTable::IsFontUnderline(LONG nRow,LONG nCol)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
	CLFont* ptrFont=GetCellFont(cell);
	ASSERT(ptrFont);
	return ptrFont->m_lf.lfUnderline;
#else
	return GetCellFont(cell)->m_lf.lfUnderline;
#endif
}
void CLTable::SetFontUnderline(RANGE& range,BOOL bVal)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTUNDERLINE, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_lf.lfUnderline =bVal;
			}
		}
		ReDraw();
	}
}
void CLTable::SetFontItalic(RANGE& range,BOOL bVal)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTITALIC, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_lf.lfItalic =bVal;
			}
		}
		ReDraw();
	}
}
void CLTable::SetFontBold(RANGE& range,BOOL bVal)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTBOLD, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_lf.lfWeight =(bVal?FW_BOLD:FW_NORMAL);
			}
		}
		ReDraw();
	}
}
void CLTable::SetAlignCenter(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignHorz=ahCENTER;
			}
		}
		ReDraw();
	}
}
void CLTable::SetAlignRight(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignHorz=ahRIGHT;
			}
		}
		ReDraw();
	}
}
void CLTable::SetAlignLeft(RANGE& range)
{
	if(!range.isEmpty()){
		MSG_CALLBACK(MSG_STYLECHANGE,TMSG_STYLECHANGE_FONTALIGN, \
			(WPARAM)&range,0);
		RECT rct;
		RANGE rgn=range;
		rgn.GetRangeRect(rct);
		CLFont* ptrItem;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Row=irow;
				cell.Col=icol;
#ifdef _DEBUG
				ASSERT_CELL(cell);
#endif
				ptrItem=GetCellFont(cell,TRUE);
				ptrItem->m_Alignment.bAlignHorz=ahLEFT;
			}
		}
		ReDraw();
	}
}

void CLTable::SetRedrawHelp(IRedrawHelp* ptr)
{
	m_ptrOuter=ptr;
}

LPSCROLLINFOEXT CLTable::GetScrollInfo(BOOL bHorz)
{
	return bHorz?&m_hScrollInfo:&m_vScrollInfo;
}

void CLTable::GetBeginFreezePos(POINT &pt)
{
	GetBeginTablePos(pt);
	pt.x+=GetFixedColsWidth();
	pt.y+=GetFixedRowsHeight();
}
void CLTable::SetDrawPanRect(const RECT& rct)
{
	POINT pt;
	pt.x=rct.left;
	pt.y=rct.top;
	SetBeginDrawPos(pt);
	SIZE size;
	size.cx=rct.right-rct.left;
	size.cy=rct.bottom-rct.top;
	SetDrawPanSize(size);
}
void CLTable::GetClientSize(SIZE& size)
{
	m_sizeClient.cx=m_sizeTable.cx-(GetFixedColsWidth()+GetFreezeColsWidth());
	m_sizeClient.cy=m_sizeTable.cy-(GetFixedRowsHeight()+GetFreezeRowsHeight());
	m_vScrollInfo.m_bVisible=FALSE;
	m_hScrollInfo.m_bVisible=FALSE;
	if(m_sizeTable.cx-m_sizeExtend.cx>=m_hScrollInfo.m_nMaxValue){
		if(m_sizeTable.cy-m_sizeExtend.cy<m_vScrollInfo.m_nMaxValue){
			//有垂直滚动条
			m_vScrollInfo.m_bVisible=TRUE;
			m_hScrollInfo.m_bVisible=(m_sizeTable.cx-SCROLLBAR_SIZE<m_hScrollInfo.m_nMaxValue);
		}
	}else{
		m_hScrollInfo.m_bVisible=TRUE;
		m_vScrollInfo.m_bVisible=(m_sizeTable.cy-SCROLLBAR_SIZE<m_vScrollInfo.m_nMaxValue);
	}
	m_sizeClient.cx-=(m_vScrollInfo.m_bVisible?SCROLLBAR_SIZE:m_sizeExtend.cx);
	m_sizeClient.cy-=(m_hScrollInfo.m_bVisible?SCROLLBAR_SIZE:m_sizeExtend.cy);
	size=m_sizeClient;
}
void CLTable::SetDrawPanSize(const SIZE& size)
{
	m_sizeAll=size;
	m_sizeTable.cx=m_sizeAll.cx-m_sizeFreeLeft.cx-m_sizeFreeRight.cx;
	m_sizeTable.cy=m_sizeAll.cy-m_sizeFreeTop.cy-FLAG_BAR_HEIGHT-m_sizeFreeBottom.cy;
	GetClientSize(m_sizeClient);
}
void CLTable::GetBeginTablePos(POINT &pt)
{
	pt.x=m_beginDrawPos.x+m_sizeFreeLeft.cx;
	pt.y=m_beginDrawPos.y+m_sizeFreeTop.cy+FLAG_BAR_HEIGHT;
}

void CLTable::GetBeginClientPos(POINT &pt)
{
	GetBeginFreezePos(pt);
	pt.x+=GetFreezeColsWidth();
	pt.y+=GetFreezeRowsHeight();
}
void CLTable::GetFreeAreaSize(SIZE& size,LONG nFreeID)
{
	switch(nFreeID){
	case FREE_AREA_TOP:
		size=m_sizeFreeTop;
		break;
	case FREE_AREA_LEFT:
		size=m_sizeFreeLeft;
		break;
	case FREE_AREA_RIGHT:
		size=m_sizeFreeRight;
		break;
	case FREE_AREA_BOTTOM:
		size=m_sizeFreeBottom;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void CLTable::SetFreeAreaSize(const SIZE& size,LONG nFreeID)
{
	switch(nFreeID){
	case FREE_AREA_TOP:
		m_sizeFreeTop=size;
		break;
	case FREE_AREA_LEFT:
		m_sizeFreeLeft=size;
		break;
	case FREE_AREA_RIGHT:
		m_sizeFreeRight=size;
		break;
	case FREE_AREA_BOTTOM:
		m_sizeFreeBottom=size;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

LONG CLTable::GetFixedRowsHeight()
{
	LONG ret=0;
	if(m_FixedRows>0)
	{
		CLRowItem* ptrRow;
		for(LONG irow=0;irow<m_FixedRows;irow++){
			ptrRow=GetARow(irow);
			ret+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
		}
	}
	return ret;
}

LONG CLTable::GetFixedColsWidth()
{
	LONG ret=0;
	if(m_FixedCols>0)
	{
		CLColItem* ptrCol;
		for(LONG icol=0;icol<m_FixedCols;icol++){
			ptrCol=GetACol(icol);
			ret+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
		}
	}
	return ret;
}

LONG CLTable::GetFreezeRowsHeight()
{
	LONG ret=0;
	if(m_FreezeRows>0)
	{
		CLRowItem* ptrRow;
		for(LONG irow=0;irow<m_FreezeRows;irow++){
			ptrRow=GetARow(irow+m_FixedRows);
			ret+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
		}
	}
	return ret;
}

LONG CLTable::GetFreezeColsWidth()
{
	LONG ret=0;
	if(m_FreezeCols>0)
	{
		CLColItem* ptrCol;
		for(LONG icol=0;icol<m_FreezeCols;icol++){
			ptrCol=GetACol(icol+m_FixedCols);
			ret+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
		}
	}
	return ret;
}

void CLTable::InitSize()
{
	CLPlatform::ClearPoint(m_beginDrawPos);
	CLPlatform::ClearPoint(m_beginLeftTop);
	
	CLPlatform::ClearSize(m_sizeAll);
	CLPlatform::ClearSize(m_sizeTable);
	CLPlatform::ClearSize(m_sizeClient);
	CLPlatform::ClearSize(m_sizeFreeLeft);
	CLPlatform::ClearSize(m_sizeFreeTop);
	CLPlatform::ClearSize(m_sizeFreeRight);
	CLPlatform::ClearSize(m_sizeFreeBottom);
	CLPlatform::ClearSize(m_sizeExtend);
	
	m_prevFocusCell.Row=-1;
	m_prevFocusCell.Col=-1;

}

BOOL CLTable::GetRangeRect(const RANGE& rgn,RECT& rctClip,
						   RECT& rctVisible,RECT& rct,LONG nOffset)
{
	RECT rctClient;
	GetClientRect(rctClient);
	POINT ptxy,ptFreeze;
	GetCellBeginXY(ptxy);
	GetBeginFreezePos(ptFreeze);
	return GetRangeRect_Atom(rctClient,ptxy,ptFreeze,rgn,rctClip,rctVisible,rct,nOffset);
}

/*
           │           
		   │           
           │           
	A	   │      B    
		   │           
────────────
           │           
		   │           
	C	   │      D    
		   │           
		   │           
*/
//返回值-->FALSE意味着该范围不在可视区域内.
BOOL CLTable::GetRangeRect_Atom(const RECT& rctClp,const POINT& ptCellBeginXY/*ptCellBeginXY*/,const POINT& ptFreezeBegin/*BeginFreezePos*/,
						   const RANGE& rgn,RECT& rctClip,
						   RECT& rctVisible,RECT& rct,LONG nOffset)
{
	if(!isRangeVisible(rgn))return FALSE;
	BOOL bRet=TRUE;
	RANGE range=rgn;
	RECT rctClient=rctClp;
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	LONG irow,icol;
	SIZE size,sizeClient;
	
	POINT ptOffset,ptxy=ptCellBeginXY,ptFreeze=ptFreezeBegin,ptBegin=ptFreezeBegin;
	CELL cellEnd,cellBegin;
	LONG nMask=8;
	if(!range.isEmpty()){
		size.cx=0;
		size.cy=0;
		CLPlatform::ClearRect(rct);
		CLPlatform::ClearRect(rctClip);
		//GetClientRect(rctAll,rctClient);
		sizeClient.cx=rctClient.right-rctClient.left;
		sizeClient.cy=rctClient.bottom-rctClient.top;
		
		//GetCellBeginXY(rctAll,ptxy);
		GetBeginCell(cellBegin);
		//GetBeginFreezePos(rctAll,ptBegin);
		GetRightBottomCell(sizeClient,cellEnd,ptOffset);
		CLPlatform::ClearRect(rctClip);
		if(range.m_posRow.m_begin<(m_FixedRows+m_FreezeRows)){
			//当前范围开始于冻结行 (A OR B)
			if(range.m_posRow.m_end<(m_FixedRows+m_FreezeRows)){
				//当前范围在冻结行内(A OR B)
				if(range.m_posCol.m_begin<(m_FixedCols+m_FreezeCols)){
					//列范围开始于冻结列 (A)
					if(range.m_posCol.m_end>=m_FixedCols+m_FreezeCols){
						//冻结区域的交叉地带(B)
						//[A,B]
						nMask=3;
					}else{
						//冻结区域的固定地带
						//[A]
						nMask=1;
					}
				}else{
					//冻结区域的活动地带
					//[B]
					nMask=2;
				}
			}else{
				//当前范围是个交叉区域（冻结区域和客户区域）(A B C D)
				if(range.m_posCol.m_begin<(m_FixedCols+m_FreezeCols)){
					//列开始于冻结区域的固定地带(A OR C)
					if(range.m_posCol.m_end<(m_FixedCols+m_FreezeCols)){
						//冻结区域的交叉地带
						//[A,C]
						nMask=5;
					}else{
						//同时包含四个区域
						//[A,B,C,D]
						nMask=15;
					}
				}else{
					//和客户区相交且不包含冻结列
					//[B,D]
					nMask=10;
				}
			}
		}else if(range.m_posCol.m_begin<(m_FixedCols+m_FreezeCols)){
			//当前列范围开始于冻结区域
			if(range.m_posCol.m_end<(m_FixedCols+m_FreezeCols)){
				//[C]
				nMask=4;
			}else{
				//[C,D]
				nMask=12;
			}
		}else{
			//当前范围只在客户区
			//[D]
			nMask=8;
		}
		switch(nMask){
		case 1://[A]
			{
				//得到起始位置
				//GetBeginFreezePos(ptBegin);
				//ptBegin=ptFreezeBegin;
				rct.top+=ptFreezeBegin.y;
				rct.left+=ptFreezeBegin.x;
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				//得到实际尺寸
				rct.right=rct.left;
				rct.bottom=rct.top;
				for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				rctClip=rct;
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.left<ptFreezeBegin.x)
					rctVisible.left=ptFreezeBegin.x;
				if(rctVisible.top<ptFreezeBegin.y)
					rctVisible.top=ptFreezeBegin.y;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
			}
			break;
		case 2://[B]
			{
				//GetBeginFreezePos(ptFreeze);
				rct.top+=ptFreezeBegin.y;
				//GetBeginClientPos(ptBegin);
				ptBegin.x=rctClp.left;
				ptBegin.y=rctClp.top;
				rct.left=rctClp.left-ptxy.x;
				rct.right=rct.left;
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				rct.bottom=rct.top;
				for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				if(range.m_posCol.m_begin<cellBegin.Col){
					//部分单元不可见
					if(range.m_posCol.m_end>=cellBegin.Col){
						for(icol=cellBegin.Col-1;icol>=range.m_posCol.m_begin;icol--){
							ptrCol=GetACol(icol);
							rct.left-=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
						for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
							ptrCol=GetACol(icol);
							rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
					}else{//全部看不见
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(icol=cellBegin.Col;icol<range.m_posCol.m_begin;icol++){
						ptrCol=GetACol(icol);
						rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right=rct.left;
					for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
				}
				
				rctClip.left=(rct.left<ptBegin.x-ptxy.x?ptBegin.x-ptxy.x:rct.left);
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				rctClip.top=rct.top;
				rctClip.bottom=rct.bottom;
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.left<rctClient.left)
					rctVisible.left=rctClient.left-((ptxy.x>0 ||
					range.m_posCol.m_begin<cellBegin.Col)?0:2);
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
				if(rctVisible.top<ptFreeze.y)
					rctVisible.top=ptFreeze.y;
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
			}
			break;
		case 4://[C]
			{
				//GetBeginFreezePos(ptFreeze);
				rct.left+=ptFreezeBegin.x;
				ptBegin.x=rctClp.left;
				ptBegin.y=rctClp.top;
				//GetBeginClientPos(ptBegin);
				rct.top=rctClp.top-ptxy.y;
				rct.bottom=rct.top;
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				rct.right=rct.left;
				for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				if(range.m_posRow.m_begin<cellBegin.Row){
					//部分单元不可见
					if(range.m_posRow.m_end>=cellBegin.Row){
						for(irow=cellBegin.Row-1;irow>=range.m_posRow.m_begin;irow--){
							ptrRow=GetARow(irow);
							rct.top-=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
						
						for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
							ptrRow=GetARow(irow);
							rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
					}else{
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(irow=cellBegin.Row;irow<range.m_posRow.m_begin;irow++){
						ptrRow=GetARow(irow);
						rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom=rct.top;
					for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
				}
				
				rctClip.top=(rct.top<ptBegin.y-ptxy.y?ptBegin.y-ptxy.y:rct.top);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				rctClip.left=rct.left;
				rctClip.right=rct.right;
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.top<rctClient.top)
					rctVisible.top=rctClient.top-((ptxy.y>0
					|| range.m_posRow.m_begin<cellBegin.Row)?0:2);
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.left<ptFreeze.x)
					rctVisible.left=ptFreeze.x;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		case 8://[D]
			{
				//GetBeginClientPos(ptBegin);
				ptBegin.x=rctClp.left;
				ptBegin.y=rctClp.top;
				rct.top=rctClp.top-ptxy.y;
				rct.left=rctClp.left-ptxy.x;
				rct.right=rct.left;
				if(range.m_posCol.m_begin<cellBegin.Col){
					//部分单元不可见
					if(range.m_posCol.m_end>=cellBegin.Col){
						for(icol=cellBegin.Col-1;icol>=range.m_posCol.m_begin;icol--){
							ptrCol=GetACol(icol);
							rct.left-=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
						for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
							ptrCol=GetACol(icol);
							rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
					}else{
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(icol=cellBegin.Col;icol<range.m_posCol.m_begin;icol++){
						ptrCol=GetACol(icol);
						rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right=rct.left;
					for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
				}
				if(range.m_posRow.m_begin<cellBegin.Row){
					//部分单元不可见
					rct.bottom=rct.top;
					if(range.m_posRow.m_end>=cellBegin.Row){
						for(irow=cellBegin.Row-1;irow>=range.m_posRow.m_begin;irow--){
							ptrRow=GetARow(irow);
							rct.top-=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
						for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
							ptrRow=GetARow(irow);
							rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
					}else{
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(irow=cellBegin.Row;irow<range.m_posRow.m_begin;irow++){
						ptrRow=GetARow(irow);
						rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom=rct.top;
					for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
				}
				rctClip.top=(rct.top<ptBegin.y-ptxy.y?ptBegin.y-ptxy.y:rct.top);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				rctClip.left=(rct.left<ptBegin.x-ptxy.x?ptBegin.x-ptxy.x:rct.left);
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.top<rctClient.top)
					rctVisible.top=rctClient.top-((ptxy.y>0||m_FreezeRows<=0
					|| range.m_posRow.m_begin<cellBegin.Row)?0:2);
				if(rctVisible.left<rctClient.left)
					rctVisible.left=rctClient.left-((ptxy.x>0||m_FreezeCols<=0
					|| range.m_posCol.m_begin<cellBegin.Col)?0:2);
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		case 3://[A,B]
			{
				//得到固定部分先
				//GetBeginFreezePos(ptBegin);

				rct.top=ptFreezeBegin.y;
				rct.left=ptFreezeBegin.x;
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				rct.right=rct.left;
				rct.bottom=rct.top;
				for(icol=range.m_posCol.m_begin;icol<m_FixedCols+m_FreezeCols;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				if(range.m_posCol.m_end>=cellBegin.Col){
					for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right-=ptxy.x;
				}
				rctClip=rct;
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		case 5://[A,C]
			{
				//得到固定部分先
				//GetBeginFreezePos(ptBegin);
				rct.top=ptFreezeBegin.y;
				rct.left=ptFreezeBegin.x;
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				rct.right=rct.left;
				rct.bottom=rct.top;
				for(irow=range.m_posRow.m_begin;irow<m_FixedRows+m_FreezeRows;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				if(range.m_posRow.m_end>=cellBegin.Row){
					for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom-=ptxy.y;
				}
				rctClip=rct;
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		case 12://[C,D]
			{
				//GetBeginFreezePos(ptBegin);
				rct.left=ptFreezeBegin.x;
				ptBegin.x=rctClp.left;
				ptBegin.y=rctClp.top;
				//GetBeginClientPos(ptBegin);
				rct.top=rctClp.top-ptxy.y;;
				//找到起始位置
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				rct.right=rct.left;
				for(icol=range.m_posCol.m_begin;icol<m_FixedCols+m_FreezeCols;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				
				if(range.m_posCol.m_end>=cellBegin.Col){
					for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right-=ptxy.x;
				}
				//////
				if(range.m_posRow.m_begin<cellBegin.Row){
					//部分单元不可见
					if(range.m_posRow.m_end>=cellBegin.Row){
						rct.bottom=rct.top;
						for(irow=cellBegin.Row-1;irow>=range.m_posRow.m_begin;irow--){
							ptrRow=GetARow(irow);
							rct.top-=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
						
						for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
							ptrRow=GetARow(irow);
							rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						}
					}else{
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(irow=cellBegin.Row;irow<range.m_posRow.m_begin;irow++){
						ptrRow=GetARow(irow);
						rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom=rct.top;
					for(irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
				}
				rctClip.top=(rct.top<ptBegin.y-ptxy.y?ptBegin.y-ptxy.y:rct.top);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				rctClip.left=rct.left;
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.top<rctClient.top)
					rctVisible.top=rctClient.top-((ptxy.y>0||m_FreezeRows<=0
					|| range.m_posRow.m_begin<cellBegin.Row)?0:2);
				
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		case 10://[B,D]
			{
				//GetBeginFreezePos(ptBegin);
				rct.top=ptFreezeBegin.y;
				ptBegin.x=rctClp.left;
				ptBegin.y=rctClp.top;
				//GetBeginClientPos(ptBegin);
				rct.left=rctClp.left-ptxy.x;;
				//找到起始位置
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				rct.bottom=rct.top;
				for(irow=range.m_posRow.m_begin;irow<m_FixedRows+m_FreezeRows;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				
				if(range.m_posRow.m_end>=cellBegin.Row){
					for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom-=ptxy.y;
				}
				//////
				if(range.m_posCol.m_begin<cellBegin.Col){
					//部分单元不可见
					if(range.m_posCol.m_end>=cellBegin.Col){
						rct.right=rct.left;
						for(icol=cellBegin.Col-1;icol>=range.m_posCol.m_begin;icol--){
							ptrCol=GetACol(icol);
							rct.left-=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
						
						for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
							ptrCol=GetACol(icol);
							rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						}
					}else{
						ASSERT(FALSE);
						return FALSE;
					}
				}else{
					for(icol=cellBegin.Col;icol<range.m_posCol.m_begin;icol++){
						ptrCol=GetACol(icol);
						rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right=rct.left;
					for(icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
				}
				rctClip.left=(rct.left<ptBegin.x-ptxy.x?ptBegin.x-ptxy.x:rct.left);
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				rctClip.top=rct.top;
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);
				
				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				if(rctVisible.left<rctClient.left)
					rctVisible.left=rctClient.left-((ptxy.x>0||m_FreezeCols<=0
					|| range.m_posCol.m_begin<cellBegin.Col)?0:2);
				
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
			}
			break;
		case 15://[A,B,C,D]
			{
				//GetBeginFreezePos(ptBegin);
				rct.top=ptFreezeBegin.y;
				rct.left=ptFreezeBegin.x;
				for(irow=m_FixedRows;irow<range.m_posRow.m_begin;irow++){
					ptrRow=GetARow(irow);
					rct.top+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				for(icol=m_FixedCols;icol<range.m_posCol.m_begin;icol++){
					ptrCol=GetACol(icol);
					rct.left+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				//确定Right
				rct.right=rct.left;
				for(icol=range.m_posCol.m_begin;icol<m_FixedCols+m_FreezeCols;icol++){
					ptrCol=GetACol(icol);
					rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				}
				if(range.m_posCol.m_end>=cellBegin.Col){
					for(icol=cellBegin.Col;icol<=range.m_posCol.m_end;icol++){
						ptrCol=GetACol(icol);
						rct.right+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
					}
					rct.right-=ptxy.x;
				}
				//确定Bottom
				rct.bottom=rct.top;
				for(irow=range.m_posRow.m_begin;irow<m_FixedRows+m_FreezeRows;irow++){
					ptrRow=GetARow(irow);
					rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				}
				if(range.m_posRow.m_end>=cellBegin.Row){
					for(irow=cellBegin.Row;irow<=range.m_posRow.m_end;irow++){
						ptrRow=GetARow(irow);
						rct.bottom+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
					}
					rct.bottom-=ptxy.y;
				}
				rctClip=rct;
				rctClip.right=(rct.right>rctClient.right+ptOffset.x?
					rctClient.right+ptOffset.x:rct.right);
				rctClip.bottom=(rct.bottom>rctClient.bottom+ptOffset.y?
					rctClient.bottom+ptOffset.y:rct.bottom);

				rctVisible=rct;
				rctVisible.left-=nOffset;
				rctVisible.top-=nOffset;
				rctVisible.right+=nOffset;
				rctVisible.bottom+=nOffset;
				
				if(rctVisible.bottom>rctClient.bottom)
					rctVisible.bottom=rctClient.bottom;
				if(rctVisible.right>rctClient.right)
					rctVisible.right=rctClient.right;
			}
			break;
		}
	}
	return bRet;
}

BOOL CLTable::isRangeVisible(const RANGE &range,BOOL* pbisClip,LPRECT rctOff)
{
	CELL cellEnd;
	POINT ptOffset;
	SIZE sizeClient;
	GetClientSize(sizeClient);
	GetRightBottomCell(sizeClient,cellEnd,ptOffset);
	BOOL bOut=(range.m_posRow.m_end<m_beginCell.Row || range.m_posRow.m_begin>cellEnd.Row
		|| range.m_posCol.m_end<m_beginCell.Col || range.m_posCol.m_begin>cellEnd.Col);
	if(bOut){
		//看看是否在可见的冻结单元
		if(range.m_posRow.m_begin>=m_FixedRows+m_FreezeRows){
			if(range.m_posCol.m_begin<m_FixedCols+m_FreezeCols){
				if((range.m_posRow.m_begin>=m_beginCell.Row 
					&& range.m_posRow.m_begin<=cellEnd.Row)
					|| (range.m_posRow.m_end>=m_beginCell.Row 
					&& range.m_posRow.m_end<=cellEnd.Row)
					|| (range.m_posRow.m_begin<=m_beginCell.Row 
					&& range.m_posRow.m_end>=cellEnd.Row)){
					bOut=FALSE;
				}
			}
		}else if(range.m_posCol.m_begin>=m_FixedCols+m_FreezeCols){
			if((range.m_posCol.m_begin>=m_beginCell.Col 
				&& range.m_posCol.m_begin<=cellEnd.Col)
			|| (range.m_posCol.m_end>=m_beginCell.Col 
			&& range.m_posCol.m_end<=cellEnd.Col)
			|| (range.m_posCol.m_begin<=m_beginCell.Col 
			&& range.m_posCol.m_end>=cellEnd.Col)){
				bOut=FALSE;
			}
		}else{
			bOut=FALSE;
		}
	}else if(pbisClip && rctOff){
		//在客户区可见范围
		//检测是否被裁减
		rctOff->left=0;
		rctOff->top=0;
		rctOff->right=0;
		rctOff->bottom=0;
		*pbisClip=FALSE;
		if(range.m_posRow.m_begin==m_beginCell.Row){
			//开始行
			if(m_beginLeftTop.y!=0){
				rctOff->top=1;
				*pbisClip=TRUE;
			}
		}else if(range.m_posRow.m_end==m_beginCell.Row){
			rctOff->top=range.m_posRow.m_end-range.m_posRow.m_begin
				+(m_beginLeftTop.y!=0?1:0);
			*pbisClip=TRUE;
		}else if(range.m_posRow.m_begin==cellEnd.Row){
			rctOff->bottom=range.m_posRow.m_end-range.m_posRow.m_begin
				+(ptOffset.y!=0?1:0);
			*pbisClip=TRUE;
		}else if(range.m_posRow.m_end==cellEnd.Row){
			if(ptOffset.y!=0){
				rctOff->bottom=1;
				*pbisClip=TRUE;
			}
		}
		
		if(range.m_posCol.m_begin==m_beginCell.Col){
			//开始列
			if(m_beginLeftTop.x!=0){
				rctOff->left=1;
				*pbisClip=TRUE;
			}
		}else if(range.m_posCol.m_end==m_beginCell.Col){
			rctOff->left=range.m_posCol.m_end-range.m_posCol.m_begin
				+(m_beginLeftTop.x!=0?1:0);
			*pbisClip=TRUE;
		}else if(range.m_posCol.m_begin==cellEnd.Col){
			rctOff->right=range.m_posCol.m_end-range.m_posCol.m_begin
				+(ptOffset.x!=0?1:0);
			*pbisClip=TRUE;
		}else if(range.m_posCol.m_end==cellEnd.Col){
			if(ptOffset.x!=0){
				rctOff->right=1;
				*pbisClip=TRUE;
			}
		}
	}
	return !bOut;
}
//得到当前页面结束单元位置
void CLTable::GetRightBottomCell(const SIZE& sizeClient/*ClientSize*/,CELL &cell,POINT& ptOffsetClip)
{
	LONG cntx=0,cnty=0,valv=0,valh=0;
	SIZE size=sizeClient;
	CELL beginCell;
	GetBeginCell(beginCell);
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	
	size.cx+=m_beginLeftTop.x;
	size.cy+=m_beginLeftTop.y;
	BOOL bFind=FALSE;
	for(LONG irow=beginCell.Row;irow<m_Rows;irow++){
		ptrRow=GetARow(irow);
		valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
		cnty+=valv;
		if(cnty>=size.cy){
			bFind=TRUE;
			cell.Row=irow;
			ptOffsetClip.y=(cnty-size.cy);
			break;
		}
	}
	if(!bFind){
		cell.Row=m_Rows-1;
		ptOffsetClip.y=0;
	}else
		bFind=FALSE;
	for(LONG icol=beginCell.Col;icol<m_Cols;icol++){
		ptrCol=GetACol(icol);
		valh=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
		cntx+=valh;
		if(cntx>=size.cx){
			bFind=TRUE;
			cell.Col=icol;
			ptOffsetClip.x=(cntx-size.cx);
			break;
		}
	}
	if(!bFind){
		cell.Col=m_Cols-1;
		ptOffsetClip.x=0;
	}
}

BOOL CLTable::isFocusCell(const CELL& cell)
{
	RANGE rgn;
	CELL cellC;
	GetCurrentCell(cellC);
	return (cellC==cell);
}

LPTSTR CLTable::GetCellMemo(LONG irow, LONG icol)
{
	CLCellItem* ptrCell=GetACell(irow,icol);
	return (ptrCell?ptrCell->GetMemo():NULL);
}

void CLTable::SetCellMemo(LONG irow, LONG icol, LPTSTR ptrTxt)
{
	CLCellItem* ptrCell=GetACell(irow,icol,TRUE);
	ptrCell->SetMemo(ptrTxt);
}
LPTSTR CLTable::GetCellText(LONG irow, LONG icol)
{
	CLCellItem* ptrCell=GetACell(irow,icol);
	return (ptrCell?ptrCell->GetText():NULL);
}
void CLTable::SetCellText(LONG irow, LONG icol, LPTSTR ptrTxt)
{
	if(ptrTxt && ptrTxt[0]=='='){
		/*可能是公式*/
		BOOL berr=FALSE;
		tag_computer_result ret_v;
		string error="";
		DOUBLE dblRet=0;
		berr=calc_script((char*)(ptrTxt+1),ret_v,(IParse_Function_Macro*)this,error,TRUE);
		if(berr){
#if defined _LINK_DYN_TYPE_
			if(ret_v.type==type_result_string){
#else
			if(ret_v.get_type()==type_result_string){
#endif
#if defined _LINK_DYN_TYPE_
				SetFormulaValue(irow,icol,(char*)ret_v.str_value->c_str());
				if(ret_v.str_value){
					delete ret_v.str_value;
					ret_v.str_value=NULL;
				}
#else
				SetFormulaValue(irow,icol,(char*)ret_v.get_string()->c_str());
#endif		
			}else{
#if defined _LINK_DYN_TYPE_
				dblRet=ret_v.dbl_value;
#else
				dblRet=ret_v.get_number();
#endif
				char ptrT[256],*ptr;
				sprintf(ptrT,"%.7f",dblRet);
				for(ptr=ptrT;*ptr!='\0';ptr++);
				for(--ptr;ptr>ptrT && *ptr=='0';ptr--);
				if(*ptr=='.')
					*ptr='\0';
				else
					*(ptr+1)='\0';
				SetFormulaValue(irow,icol,ptrT);
			}
			
		}else{
			/*有错*/
			if(IsFormulaCell(irow,icol))
				SetFormulaValue(irow,icol,NULL);
		}
	}else{
		if(IsFormulaCell(irow,icol))
			SetFormulaValue(irow,icol,NULL);
	}
	CLCellItem* ptrCell=GetACell(irow,icol,TRUE);
	ptrCell->SetText(ptrTxt);
}

void CLTable::GetCurrentRange(RANGE &range)
{
	if(m_CurrRange.isEmpty()){
		CELL cell;
		GetCurrentCell(cell);
		m_CurrRange.SetSingleCellRange(cell);
	}
	range=m_CurrRange;
}

void CLTable::GetOldRange(RANGE &range)
{
	range=m_OldRange;
}
void CLTable::ClearOldRange()
{
	m_OldRange.ClearRange();
}
BOOL CLTable::CellReadOnly(LONG nRow, LONG nCol)
{
	CLStyle* ptrItem=GetCellStyle(nRow,nCol);
	if(ptrItem)
		return ptrItem->ReadOnly();
	else
		return FALSE;
}

void CLTable::CellReadOnly(LONG nRow, LONG nCol, BOOL bVal)
{
	//HideInPlaceCtrl();
	CLStyle* ptrItem=GetCellStyle(nRow,nCol,TRUE);
	ptrItem->ReadOnly(bVal);
}

void CLTable::SetRangeReadOnly(RANGE &range, BOOL bVal)
{
	if(!range.isEmpty()){
		//HideInPlaceCtrl();
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;

		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				ptrItem=GetCellStyle(irow,icol,TRUE);
				ptrItem->ReadOnly(bVal);
			}
		}
	}
}
BOOL CLTable::IsRangeReadOnly(RANGE &range)
{
	BOOL bret=TRUE;
	if(!range.isEmpty()){
		//HideInPlaceCtrl();
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		CLStyle* ptrItem;

		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				ptrItem=GetCellStyle(irow,icol,TRUE);
				if(!ptrItem->ReadOnly()){
					bret=FALSE;
					break;
				}
			}
		}
	}
	return bret;
}
BOOL CLTable::IsDefaultCellFont(CLFont* ptrFont)
{
	return (ptrFont==(m_FontArr.GetDefaultValue()));
}
void CLTable::ClearCellData(LONG nRow, LONG nCol,BOOL bRedraw)
{
	CLCellItem* ptrItem=GetACell(nRow,nCol);
	if(ptrItem){
		char* ptr=ptrItem->GetText();
		if(ptr && ptr[0]!='\0'){
			ptrItem->SetText("");
			SetFormulaValue(nRow,nCol,"");
			if(bRedraw)
				ReDraw();
		}
	}
}
//序列化接口
BOOL CLTable::OnSerial(CLSerial& ar)
{
	BYTE byt;
	LONG row,col;
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	CLStyle* ptrStyle;
	CLFont*		ptrFont;
	CLCellItem* ptrCell;
	if(!m_beginCell.OnSerial(ar))
		return FALSE;
	if(!m_currentCell.OnSerial(ar))
		return FALSE;
	if(!m_CurrRange.OnSerial(ar))
		return FALSE;
	if(!m_OldRange.OnSerial(ar))
		return FALSE;
	if(!m_prevFocusCell.OnSerial(ar))
		return FALSE;
	if(!m_hScrollInfo.OnSerial(ar))
		return FALSE;
	if(!m_vScrollInfo.OnSerial(ar))
		return FALSE;
	if(ar.isLoading()){
		//读取操作
		ar>>m_beginDrawPos>>m_beginLeftTop>>m_Cols>>m_Rows>>m_FixedCols\
			>>m_FixedRows>>m_FreezeCols>>m_FreezeRows>>m_sizeAll>>m_sizeClient\
			>>m_sizeExtend>>m_sizeFreeBottom>>m_sizeFreeLeft>>m_sizeFreeRight\
			>>m_sizeFreeTop>>m_sizeTable;
		//行对象
		for(row=0;row<m_Rows;row++){
			ar>>byt;
			if(byt==1){
				ptrRow=GetARow(row,TRUE);
				ptrRow->OnSerial(ar);
			}
		}
		//列对象
		for(col=0;col<m_Cols;col++){
			ar>>byt;
			if(byt==1){
				ptrCol=GetACol(col,TRUE);
				ptrCol->OnSerial(ar);
			}
		}
		//单元格对象
		for(row=0;row<m_Rows;row++){
			int iii=0;
			for(col=0;col<m_Cols;col++){
				ar>>byt;
				if(byt==1){
					ptrCell=GetACell(row,col,TRUE);
					ptrCell->OnSerial(ar);
				}
			}
		}
		//样式对象
		for(row=0;row<m_Rows;row++){
			for(col=0;col<m_Cols;col++){
				ar>>byt;
				if(byt==1){
					ptrStyle=GetCellStyle(row,col,TRUE);
					ptrStyle->OnSerial(ar);
				}
			}
		}
		//字体对象
		CELL cell;
		for(row=0;row<m_Rows;row++){
			for(col=0;col<m_Cols;col++){
				ar>>byt;
				if(byt==1){
					cell.Row=row;
					cell.Col=col;
					ptrFont=GetCellFont(cell,TRUE);
					ptrFont->OnSerial(ar);
				}
			}
		}
	}else{
		//保存操作
		ar<<m_beginDrawPos<<m_beginLeftTop<<m_Cols<<m_Rows<<m_FixedCols\
			<<m_FixedRows<<m_FreezeCols<<m_FreezeRows<<m_sizeAll<<m_sizeClient\
			<<m_sizeExtend<<m_sizeFreeBottom<<m_sizeFreeLeft<<m_sizeFreeRight\
			<<m_sizeFreeTop<<m_sizeTable;

		//行对象
		for(row=0;row<m_Rows;row++){
			ptrRow=GetARow(row);
			if(ptrRow){
				byt=1;
				ar<<byt;
				ptrRow->OnSerial(ar);
			}else{
				byt=0;
				ar<<byt;
			}
		}
		//列对象
		for(col=0;col<m_Cols;col++){
			ptrCol=GetACol(col);
			if(ptrCol){
				byt=1;
				ar<<byt;
				ptrCol->OnSerial(ar);
			}else{
				byt=0;
				ar<<byt;
			}
		}
		//单元格对象
		for(row=0;row<m_Rows;row++){
			for(col=0;col<m_Cols;col++){
				ptrCell=GetACell(row,col);
				if(ptrCell){
					byt=1;
					ar<<byt;
					ptrCell->OnSerial(ar);
				}else{
					byt=0;
					ar<<byt;
				}
			}
		}
		//样式对象
		for(row=0;row<m_Rows;row++){
			for(col=0;col<m_Cols;col++){
				ptrStyle=GetCellStyle(row,col);
				if(!IsDefaultCellStyle(ptrStyle)){
					byt=1;
					ar<<byt;
					ptrStyle->OnSerial(ar);
				}else{
					byt=0;
					ar<<byt;
				}
			}
		}
		//字体对象
		CELL cell;
		for(row=0;row<m_Rows;row++){
			for(col=0;col<m_Cols;col++){
				cell.Row=row;
				cell.Col=col;
				ptrFont=GetCellFont(cell);
				if(!IsDefaultCellFont(ptrFont)){
					byt=1;
					ar<<byt;
					ptrFont->OnSerial(ar);
				}else{
					byt=0;
					ar<<byt;
				}
			}
		}
	}
	return TRUE;
}
/*
void CLTable::AdjustCellInfo(CELL& cell,POINT& ptOffset)
{
	if(ptOffset.x<0){
		for(LONG irow=cell.Row;irow>=m_FixedRows;irow--){
			ptrRow=GetARow(irow);
			valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			sizeW.cy-=valv;
			if(sizeW.cy<0){
				ptRet.y=sizeW.cy+valv;
				cellRet.Row=irow;
				break;
			}
		}
	}
}
*/
void CLTable::GetBeginPos(CELL& cell,POINT& ptOffset)
{
	ASSERT_CELL(cell);
	LONG valh,valv;
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	CELL cellRet;
	POINT ptRet=ptOffset;
	if(ptOffset.x>0){
		for(LONG icol=cell.Col;icol<m_Cols;icol++){
			ptrCol=GetACol(icol);
			valh=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			ptRet.x-=valh;
			if(ptRet.x<0){
				ptRet.x+=valh;
				cellRet.Col=icol;
				break;
			}
		}
	}else{
		for(LONG icol=cell.Col-1;icol>=m_FixedCols;icol--){
			ptrCol=GetACol(icol);
			valh=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			ptRet.x+=valh;
			if(ptRet.x>=0){
				cellRet.Col=icol;
				break;
			}
		}
	}
	if(ptOffset.y>0){
		for(LONG irow=cell.Row;irow<m_Rows;irow++){
			ptrRow=GetARow(irow);
			valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			ptRet.y-=valv;
			if(ptRet.y<0){
				ptRet.y+=valv;
				cellRet.Row=irow;
				break;
			}
		}
	}else{
		for(LONG irow=cell.Row-1;irow>=m_FixedRows;irow--){
			ptrRow=GetARow(irow);
			valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			ptRet.y+=valv;
			if(ptRet.y>=0){
				cellRet.Row=irow;
				break;
			}
		}
	}
	cell=cellRet;
	ptOffset=ptRet;
}
void CLTable::GetEndPos(CELL& cell,POINT& ptOffset,const SIZE& size,
						CELL& cellRet,POINT& ptRet)
{
	ASSERT_CELL(cell);
	GetBeginPos(cell,ptOffset);
	SIZE sizeW=size;
	sizeW.cx+=ptOffset.x;
	sizeW.cy+=ptOffset.y;
	LONG valh,valv;
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	for(LONG irow=cell.Row;irow<m_Rows;irow++){
		ptrRow=GetARow(irow);
		valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
		sizeW.cy-=valv;
		if(sizeW.cy<0){
			ptRet.y=sizeW.cy+valv;
			cellRet.Row=irow;
			break;
		}
	}
	for(LONG icol=cell.Col;icol<m_Cols;icol++){
		ptrCol=GetACol(icol);
		valh=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
		sizeW.cx-=valh;
		if(sizeW.cx<0){
			ptRet.x=sizeW.cx+valh;
			cellRet.Col=icol;
			break;
		}
	}
}

BOOL CLTable::GetRangeRect(const RECT& rctAll,const RANGE& range,
						   RECT& rctClip,RECT& rctVisible,RECT& rct,LONG nOffset)
{
	RECT rctClient;
	GetClientRect(rctAll,rctClient);
	POINT ptxy,ptFreeze;
	GetCellBeginXY(ptxy);
	GetBeginFreezePos(rctAll,ptFreeze);
	return GetRangeRect_Atom(rctClient,ptxy,ptFreeze,
		range,rctClip,rctVisible,rct,nOffset);
}
