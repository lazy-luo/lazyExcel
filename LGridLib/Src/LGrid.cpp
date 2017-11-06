//////////////////////////////////////////////////////////////////////
//@模块		 ：Grid对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-12
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LGrid.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "../../LGUILib/Src/LScrollBar.h"

CLGrid::CLGrid():m_pMergeArr(NULL),m_clrGridLine(COLOR_GRIDLINE),m_nPerLogicPixel(20)
,m_bScrollByCell(TRUE),m_bExcelMode(TRUE),m_bFillFocus(FALSE),m_nSelectMode(SELECT_BY_CELL),
m_bRangeMode(TRUE)
{
	
}

CLGrid::~CLGrid()
{
	if(m_pMergeArr)
		delete m_pMergeArr;
}
BOOL CLGrid::isMergeCell(const CELL& cell)
{
	ASSERT_CELL(cell);
	if(m_pMergeArr)
		return m_pMergeArr->isCellMerge(cell.Row,cell.Col);
	else
		return FALSE;
}
BOOL CLGrid::RemoveMergeRange(RANGE& range)
{
	BOOL bret=FALSE;
	if(m_pMergeArr)
		bret=m_pMergeArr->RemoveMergeRange(range);
	ReDraw();
	m_OldRange=m_CurrRange;
	//m_prevFocusCell=m_currentCell;
	return bret;
}
BOOL CLGrid::MergeRange(RANGE& range,INT nType)
{
	ASSERT(!range.isEmpty());
	if(m_pMergeArr==NULL)
		m_pMergeArr=new CLMergesArr(this);
	BOOL bret=TRUE;
	if(nType==MERGE_ALL)
		bret=m_pMergeArr->mergeRange(range);
	else if(nType==MERGE_ROW_ONLY){
		//只合并行
		RANGE rangeT=range;
		for(int icol=range.m_posCol.m_begin;icol<=range.m_posCol.m_end;icol++){
			rangeT.m_posCol.m_begin=rangeT.m_posCol.m_end=icol;
			if(!m_pMergeArr->mergeRange(rangeT)){
				bret=FALSE;
				break;
			}
		}
	}else if(nType==MERGE_COL_ONLY){
		//只合并列
		RANGE rangeT=range;
		for(int irow=range.m_posRow.m_begin;irow<=range.m_posRow.m_end;irow++){
			rangeT.m_posRow.m_begin=rangeT.m_posRow.m_end=irow;
			if(!m_pMergeArr->mergeRange(rangeT)){
				bret=FALSE;
				break;
			}
		}
	}
	ReDraw();
	m_OldRange=m_CurrRange;
	
	return bret;
}
//滚动支持
BOOL CLGrid::GetMergeRange(const CELL cell,RANGE& range)
{
	if(m_pMergeArr==NULL){
		range.m_posRow.m_begin=range.m_posRow.m_end=cell.Row;
		range.m_posCol.m_begin=range.m_posCol.m_end=cell.Col;
		return FALSE;
	}
	return m_pMergeArr->GetRangeInfo(cell.Row,cell.Col,range);
}
LONG CLGrid::ScrollHorz(CLScrollBar* ptrObj,DLONG val,BOOL bPixel)
{
	//如果以逻辑单元为单位则起始位置不会改变.否则必须改变起始位置
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	LONG ret=0;
	if(CanScroll(TRUE,val>0)){
		BOOL bFind=FALSE,bRedraw=TRUE;
		CLColItem* ptrCol=NULL;
		LONG nVal=0,nTot=0;
		DLONG nTotWid=0;
		LPSCROLLINFOEXT pinfo=GetScrollInfo();
		DLONG dVal=0;
		LONG iAdd=0;
		SIZE size;
		this->GetClientSize(size);
		if(m_bScrollByCell){
			//按逻辑单位滚动
			if(m_beginCell.Col<m_FixedCols+m_FreezeCols)
				m_beginCell.Col=m_FixedCols+m_FreezeCols;
			if(m_beginCell.Row<m_FixedRows+m_FreezeRows)
				m_beginCell.Row=m_FixedRows+m_FreezeRows;
			dVal=val;
			if(bPixel){
				//按像素
				BOOL bFlag=FALSE;
				if(val>0){
					//向右滚
					//找到遗失精度
					nTotWid=pinfo->m_nMaxValue-pinfo->m_nExistValue-pinfo->m_nCurrValue;
					if(nTotWid<=dVal){
						bFlag=TRUE;
						ret=0;
						dVal=nTotWid;
					}
					nTot=dVal+m_beginLeftTop.x;
					for(LONG icol=m_beginCell.Col;icol<m_Cols;icol++){
						ptrCol=GetACol(icol);
						nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						if(nTot<nVal){
							if(ret>=0 && !bFlag){
								if(nTot>dVal){
									ret=dVal;
								}else{
									ret=nTot;
									m_beginLeftTop.x=0;
								}
							}else if(bFlag){
								m_beginLeftTop.x=nTot;
							}
							break;
						}
						nTot-=nVal;
						iAdd++;
					}
					bRedraw=(dVal!=ret);
					pinfo->m_nCurrValue+=(DLONG)(dVal-ret);
					if(pinfo->m_nVirtualValue<0)
						pinfo->m_nVirtualValue+=ret;
					else
						pinfo->m_nVirtualValue=ret;
					m_beginCell.Col+=iAdd;
				}else{
					//向左滚
					nTotWid=pinfo->m_nCurrValue;
					dVal=(dVal<0?-dVal:dVal);
					if(nTotWid<=(dVal)){
						bFlag=TRUE;
						ret=0;
						dVal=nTotWid;
					}
					nTot=dVal-m_beginLeftTop.x;
					if(nTot>0){
						m_beginLeftTop.x=0;
						pinfo->m_nCurrValue-=m_beginLeftTop.x;
						for(LONG icol=m_beginCell.Col-1;icol>=m_FixedCols+m_FreezeCols;icol--){
							ptrCol=GetACol(icol);
							nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
							if(nTot<nVal){
								if(ret>=0 && !bFlag)
									ret=-nTot;
								break;
							}
							nTot-=nVal;
							iAdd++;
						}
					}else{
						if(nTot==0){
							m_beginLeftTop.x=0;
						}else{
							ret=-dVal;
						}
					}
					bRedraw=(dVal+ret!=0);
					pinfo->m_nCurrValue-=(DLONG)(dVal+ret);
					if(pinfo->m_nVirtualValue>0)
						pinfo->m_nVirtualValue+=ret;
					else
						pinfo->m_nVirtualValue=ret;
					m_beginCell.Col-=iAdd;
				}
			}else{
				if(dVal>0){
					nTotWid=pinfo->m_nMaxValue-pinfo->m_nExistValue-
						pinfo->m_nCurrValue;
					for(LONG icol=0;icol<val;icol++){
						ptrCol=GetACol(icol+m_beginCell.Col);
						nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						nTot+=nVal;
						if(nTot>=nTotWid){
							//超出范围了
							m_beginLeftTop.x=nVal-(nTot-nTotWid-m_beginLeftTop.x);
							nTot=nTotWid;
							break;
						}
						iAdd++;
					}
					pinfo->m_nCurrValue+=(DLONG)nTot;
					m_beginCell.Col+=iAdd;
				}else{
					nTotWid=pinfo->m_nCurrValue;
					for(LONG icol=0;icol<(-val);icol++){
						if(m_beginLeftTop.x>0){
							nTot+=m_beginLeftTop.x;
							m_beginLeftTop.x=0;
							continue;
						}
						ptrCol=GetACol(m_beginCell.Col-icol);
						iAdd++;
						nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						nTot+=nVal;
						if(nTot>=nTotWid){
							//超出范围了
							nTot=nTotWid;
							m_beginLeftTop.x=0;
							break;
						}
					}
					pinfo->m_nCurrValue-=(DLONG)nTot;
					m_beginCell.Col-=iAdd;
				}
			}
		}else{
			dVal=pinfo->m_nCurrValue+val*(bPixel?1:m_nPerLogicPixel);
			if(dVal<0)dVal=0;
			if(dVal>pinfo->m_nMaxValue-pinfo->m_nExistValue){
				dVal=pinfo->m_nMaxValue-pinfo->m_nExistValue;
			}
			DLONG nOff=dVal-pinfo->m_nCurrValue;
			pinfo->m_nCurrValue=dVal;
			//
			if(m_beginCell.Col<m_FixedCols+m_FreezeCols)
				m_beginCell.Col=m_FixedCols+m_FreezeCols;
			if(m_beginCell.Row<m_FixedRows+m_FreezeRows)
				m_beginCell.Row=m_FixedRows+m_FreezeRows;
			
			//起始列
			LONG nWid=GetColWidth(m_beginCell.Col);
			
			if(nOff>0){
				nTotWid=nOff-nWid+m_beginLeftTop.x;
				if(nTotWid>0){
					//肯定需要改变列
					for(LONG icol=m_beginCell.Col+1;icol<m_Cols;icol++){
						ptrCol=GetACol(icol);
						nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						nTotWid-=nVal;
						if(nTotWid<=0){
							m_beginLeftTop.x=(LONG)nTotWid+nVal;
							m_beginCell.Col=icol;//+(nTotWid==0?1:0);
							bFind=TRUE;
							break;
						}
					}
					if(!bFind){
						//没有找到匹配单元
						//ASSERT(FALSE);
					}
				}else{
					//没有超过当前列范围
					m_beginLeftTop.x+=(LONG)nOff;
				}
			}else{
				//往左滚动
				nTotWid=nOff+m_beginLeftTop.x;
				if(nTotWid<0){
					for(LONG icol=m_beginCell.Col-1;
						icol>=m_FixedCols+m_FreezeCols;icol--){
						ptrCol=GetACol(icol);
						nVal=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
						nTotWid+=nVal;
						if(nTotWid>=0){
							m_beginLeftTop.x=(LONG)nTotWid;
							m_beginCell.Col=icol;//-(nTotWid==0?1:0);
							bFind=TRUE;
							break;
						}
					}
					if(!bFind){
						//没有找到匹配单元
						//ASSERT(FALSE);
					}
				}else{
					//没有超过当前列范围
					m_beginLeftTop.x=(LONG)nTotWid;
				}
			}
		}
		if(bRedraw)
			ReDraw();
		else
			RedrawScrollBar(ptrObj);
	}else{
		if(val<0 && m_beginLeftTop.x!=0)
			m_beginLeftTop.x=0;
		RedrawScrollBar(ptrObj);
	}
	
	return ret;
}
void CLGrid::StopExtendTrack(BOOL bHorz)
{
	LPSCROLLINFOEXT pinfo=GetScrollInfo(bHorz);
	if(pinfo && pinfo->m_nVirtualValue!=0){
		pinfo->m_nVirtualValue=0;
		ReDraw();
	}
}
LONG CLGrid::ScrollVert(CLScrollBar* ptrObj,DLONG val,BOOL bPixel)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	LONG ret=0;
	if(CanScroll(FALSE,val>0)){
		LPSCROLLINFOEXT pinfo=GetScrollInfo(FALSE);
		DLONG dVal;
		BOOL bFind=FALSE,bDrawAll=TRUE;
		CLRowItem* ptrRow=NULL;
		LONG nVal;
		LONG iAdd=0;
		DLONG nTotHei,nTot=0;
		if(m_bScrollByCell){
			//按逻辑单位滚动
			if(m_beginCell.Col<m_FixedCols+m_FreezeCols)
				m_beginCell.Col=m_FixedCols+m_FreezeCols;
			if(m_beginCell.Row<m_FixedRows+m_FreezeRows)
				m_beginCell.Row=m_FixedRows+m_FreezeRows;
			dVal=val;
			if(bPixel){
				//按像素
				//向下滚
				BOOL bFlag=FALSE;
				if(dVal>0){
					//找到遗失精度
					nTotHei=pinfo->m_nMaxValue-pinfo->m_nExistValue-pinfo->m_nCurrValue;
					if(nTotHei<=dVal){
						bFlag=TRUE;
						ret=0;
						dVal=nTotHei;
					}
					nTot=dVal+m_beginLeftTop.y;
					for(LONG irow=m_beginCell.Row;irow<m_Rows;irow++){
						ptrRow=GetARow(irow);
						nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						if(nTot<nVal){
							if(ret>=0 && !bFlag){
								if(nTot>dVal){
									ret=dVal;
								}else{
									ret=nTot;
									m_beginLeftTop.y=0;
								}
							}else if(bFlag){
								m_beginLeftTop.y=nTot;
							}
							break;
						}
						nTot-=nVal;
						iAdd++;
					}
					bDrawAll=(dVal!=ret);
					pinfo->m_nCurrValue+=(DLONG)(dVal-ret);
					if(pinfo->m_nVirtualValue<0)
						pinfo->m_nVirtualValue+=ret;
					else
						pinfo->m_nVirtualValue=ret;
					m_beginCell.Row+=iAdd;
				}else{
					//向上滚
					nTotHei=pinfo->m_nCurrValue;
					dVal=(dVal<0?-dVal:dVal);
					if(nTotHei<=(dVal)){
						bFlag=TRUE;
						ret=0;
						dVal=nTotHei;
					}
					nTot=dVal-m_beginLeftTop.y;
					if(nTot>0){
						m_beginLeftTop.y=0;
						pinfo->m_nCurrValue-=m_beginLeftTop.y;
						for(LONG irow=m_beginCell.Row-1;irow>=m_FixedRows+m_FreezeRows;irow--){
							ptrRow=GetARow(irow);
							nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
							if(nTot<nVal){
								if(ret>=0 && !bFlag)
									ret=-(nTot>dVal?dVal:nTot);
								break;
							}
							nTot-=nVal;
							iAdd++;
						}
					}else{
						if(nTot==0){
							m_beginLeftTop.y=0;
						}else{
							ret=-dVal;
						}
					}
					bDrawAll=(dVal+ret!=0);
					pinfo->m_nCurrValue-=(DLONG)(dVal+ret);
					if(pinfo->m_nVirtualValue>0)
						pinfo->m_nVirtualValue+=ret;
					else
						pinfo->m_nVirtualValue=ret;
					m_beginCell.Row-=iAdd;
				}
			}else{
				LONG iAdd=0;
				if(dVal>0){
					nTotHei=pinfo->m_nMaxValue-
						pinfo->m_nExistValue-pinfo->m_nCurrValue;
					for(LONG irow=0;irow<val;irow++){
						ptrRow=GetARow(irow+m_beginCell.Row);
						nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						nTot+=nVal;
						if(nTot>=nTotHei){
							//超出范围了
							m_beginLeftTop.y=nVal-(nTot-nTotHei-m_beginLeftTop.y);
							nTot=nTotHei;
							break;
						}
						iAdd++;
					}
					pinfo->m_nCurrValue+=(DLONG)nTot;
					m_beginCell.Row+=iAdd;
				}else{
					nTotHei=pinfo->m_nCurrValue;
					for(LONG irow=0;irow<(-val);irow++){
						if(m_beginLeftTop.y>0){
							nTot+=m_beginLeftTop.y;
							m_beginLeftTop.y=0;
							continue;
						}
						ptrRow=GetARow(m_beginCell.Row-irow);
						iAdd++;
						nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						nTot+=nVal;
						if(nTot>=nTotHei){
							//超出范围了
							nTot=nTotHei;
							m_beginLeftTop.y=0;
							break;
						}
						
					}
					pinfo->m_nCurrValue-=(DLONG)nTot;
					m_beginCell.Row-=iAdd;
				}
			}
		}else{
			dVal=pinfo->m_nCurrValue+val*(bPixel?1:m_nPerLogicPixel);
			if(dVal<0)dVal=0;
			if(dVal>pinfo->m_nMaxValue-pinfo->m_nExistValue)
				dVal=pinfo->m_nMaxValue-pinfo->m_nExistValue;
			DLONG nOff=dVal-pinfo->m_nCurrValue;
			pinfo->m_nCurrValue=dVal;
			
			if(m_beginCell.Col<m_FixedCols+m_FreezeCols)
				m_beginCell.Col=m_FixedCols+m_FreezeCols;
			if(m_beginCell.Row<m_FixedRows+m_FreezeRows)
				m_beginCell.Row=m_FixedRows+m_FreezeRows;
			
			//起始行
			LONG nHei=GetRowHeight(m_beginCell.Row);
			
			if(nOff>0){
				nTotHei=nOff-nHei+m_beginLeftTop.y;
				if(nTotHei>0){
					//肯定需要改变行
					for(LONG irow=m_beginCell.Row+1;irow<m_Rows;irow++){
						ptrRow=GetARow(irow);
						nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						nTotHei-=nVal;
						if(nTotHei<=0){
							m_beginLeftTop.y=(LONG)nTotHei+nVal;

							m_beginCell.Row=irow;//+(nTotHei==0?1:0);
							bFind=TRUE;
							break;
						}
					}
					if(!bFind){
						//没有找到匹配单元
						ASSERT(FALSE);
					}
				}else{
					//没有超过当前列范围
					m_beginLeftTop.y+=(LONG)nOff;
				}
			}else{
				//往上滚动
				nTotHei=nOff+m_beginLeftTop.y;
				if(nTotHei<0){
					for(LONG irow=m_beginCell.Row-1;
						irow>=m_FixedRows+m_FreezeRows;irow--){
						ptrRow=GetARow(irow);
						nVal=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
						nTotHei+=nVal;
						if(nTotHei>=0){
							m_beginLeftTop.y=(LONG)nTotHei;

							m_beginCell.Row=irow;//-(nTotHei==0?1:0);
							bFind=TRUE;
							break;
						}
					}
					if(!bFind){
						//没有找到匹配单元
						ASSERT(FALSE);
					}
				}else{
					//没有超过当前列范围
					m_beginLeftTop.y+=(LONG)nOff;
				}
			}
		}
		if(bDrawAll)
			ReDraw();
		else
			RedrawScrollBar(ptrObj);
	}else{
		if(val<0 && m_beginLeftTop.y!=0)
			m_beginLeftTop.y=0;
		RedrawScrollBar(ptrObj);
	}
	return ret;
}
void CLGrid::RedrawScrollBar(CLScrollBar* ptrObj)
{
	
	if(ptrObj){
		HDCH hDC;
		if(GetDC(hDC)){
			RECT rct;
			((IDrawItem*)ptrObj)->GetDrawRect(rct);
			hDC.pParam=GetScrollInfo(ptrObj->IsHorz());
			ptrObj->OnDraw(&hDC,rct);
			ReleaseDC(hDC);
		}
	}else
		ReDraw();
}
BOOL CLGrid::GetCellRect(LONG irow,LONG icol,RECT& rct,RECT& rctVisible,BOOL bClip)
{
	CELL cell;
	cell.Row=irow;
	cell.Col=icol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	return GetCellRect(cell,rct,rctVisible,bClip);
}

BOOL CLGrid::GetCellRect(const CELL &cell, RECT &rct,RECT& rctVisible, BOOL bClip)
{
	RANGE range;
	RECT rctAll;
	GetMergeRange(cell,range);
	if(GetRangeRect(range,rct,rctVisible,rctAll,getSelectMode()==SELECT_BY_ROW?0:4)){
		if(!bClip)
			rct=rctAll;
		return TRUE;
	}else{
		CLPlatform::ClearRect(rct);
		CLPlatform::ClearRect(rctVisible);
	}
	return FALSE;
}
void CLGrid::GetMasterCell(CELL& cell)
{
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	if(m_pMergeArr)
		m_pMergeArr->GetMasterCell(cell);
}
LONG CLGrid::GetNextRow(const CELL& cell)
{
	LONG ret=-1;
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	if(m_pMergeArr){
		RANGE range;
		m_pMergeArr->GetRangeInfo(cell.Row,cell.Col,range);
		ret=range.m_posRow.m_end+1;
	}else
		ret=cell.Row+1;
	return ret>=m_Rows?m_Rows-1:ret;
}
LONG CLGrid::GetPrevRow(const CELL& cell)
{
	LONG ret=-1;
	CELL cellT=cell;
	GetMasterCell(cellT);
	if(m_pMergeArr && cellT.Row>0){
		RANGE range;
		m_pMergeArr->GetRangeInfo(cellT.Row-1,cellT.Col,range);
		ret=range.m_posRow.m_begin;
	}else
		ret=cell.Row-1;
	return ret<0?0:ret;
}
LONG CLGrid::GetNextCol(const CELL& cell)
{
	LONG ret=-1;
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	if(m_pMergeArr){
		RANGE range;
		m_pMergeArr->GetRangeInfo(cell.Row,cell.Col,range);
		ret=range.m_posCol.m_end+1;
	}else
		ret=cell.Col+1;
	return ret>=m_Cols?m_Cols-1:ret;
}
LONG CLGrid::GetPrevCol(const CELL& cell)
{
	LONG ret=-1;
	CELL cellT=cell;
	GetMasterCell(cellT);
	if(m_pMergeArr && cellT.Col>0){
		RANGE range;
		m_pMergeArr->GetRangeInfo(cellT.Row,cellT.Col-1,range);
		ret=range.m_posCol.m_begin;
	}else
		ret=cellT.Col-1;
	return ret<0?0:ret;;
}
void CLGrid::GetCellRange(LONG nRow, LONG nCol, RANGE &range)
{
	CELL cell;
	cell.Row=nRow;
	cell.Col=nCol;
#ifdef _DEBUG
	ASSERT_CELL(cell);
#endif
	GetMergeRange(cell,range);
}
void CLGrid::GetCombinRange(RANGE &range, const RANGE &rangeD)
{
	RECT rct;
	RANGE rangeDst=rangeD;
	range.GetRangeRect(rct);
	range.AdjustRange();
	rangeDst.AdjustRange();
	RANGE cellRange,rangeRet=range;
	LONG nBeginRow,nEndRow,nBeginCol,nEndCol;
	
	nBeginRow=(range.m_posRow.m_begin>rangeDst.m_posRow.m_begin
		?rangeDst.m_posRow.m_begin:range.m_posRow.m_begin);
	nEndRow=(range.m_posRow.m_end>rangeDst.m_posRow.m_end
		?range.m_posRow.m_end:rangeDst.m_posRow.m_end);
	nBeginCol=(range.m_posCol.m_begin>rangeDst.m_posCol.m_begin
		?rangeDst.m_posCol.m_begin:range.m_posCol.m_begin);
	nEndCol=(range.m_posCol.m_end>rangeDst.m_posCol.m_end
		?range.m_posCol.m_end:rangeDst.m_posCol.m_end);
	for(LONG irow=nBeginRow;irow<=nEndRow;irow++){
		for(LONG icol=nBeginCol;icol<=nEndCol;icol++){
			//if(!(range.isCellInRange(irow,icol))){
			GetCellRange(irow,icol,cellRange);
			rangeRet.CombinRange(cellRange);
			if(cellRange.m_posCol.m_begin<nBeginCol || cellRange.m_posCol.m_end>nEndCol ||
				cellRange.m_posRow.m_begin<nBeginRow || cellRange.m_posRow.m_end>nEndRow ||
				cellRange.m_posCol.m_begin>nEndCol || cellRange.m_posCol.m_end<nBeginCol ||
				cellRange.m_posRow.m_begin>nEndRow || cellRange.m_posRow.m_end<nBeginRow){
				GetCombinRange(rangeRet,rangeD);
			}
			//}
		}
	}
	range=rangeRet;
}

//得到特定行区域
//注意,用完区域对象后一定要迅速释放掉!!!
HRGN CLGrid::GetRowRgn(LONG nRow,RECT& rctClip)
{
	HRGN hrgn=NULL,hrgnT=NULL;
	RECT rct,rctVisible;
	CELL cell,cellEnd;
	POINT pt;
	POINT ptStart;
	GetCellBeginXY(ptStart);
	GetBeginFreezePos(pt);
	GetClientRect(rctClip);
	rctClip.left=pt.x;
	
	GetBeginCell(cell);
	SIZE size;
	GetClientSize(size);
	GetRightBottomCell(size,cellEnd,pt);
	if(nRow>cellEnd.Row || nRow<m_FixedRows) return NULL;
	if(!(nRow==cell.Row && ptStart.y>0)){
		rctClip.top=pt.y;
	}
	for(LONG icol=m_FixedCols;icol<=cellEnd.Col;icol++){
		
		if(!GetCellRect(nRow,icol,rct,rctVisible)){
			continue;
		}
		rct.left--;
		rct.top--;
		
		hrgnT=CLDrawer::CreateRectRgn(rct);
		if(hrgn==NULL){
			hrgn=hrgnT;
		}else{
			CLDrawer::CombineRgn(hrgn,hrgn,hrgnT,RGN_OR);
			CLDrawer::DeleteRgn(hrgnT);
		}
		if(icol==m_FixedCols+m_FreezeCols-1)
			icol=cell.Col-1;
	}
	return hrgn;
}
void CLGrid::MoveRect(RECT &rct, LONG cx, LONG cy)
{
	rct.left+=cx;
	rct.top+=cy;
	rct.right+=cx;
	rct.bottom+=cy;
	
}
BOOL CLGrid::isFocusCell(const RANGE& range)
{
	RANGE rgn;
	CELL cell;
	GetCurrentCell(cell);
	GetCellRange(cell.Row,cell.Col,rgn);
	return (rgn==range);
}

LPTSTR CLGrid::GetMasterCellText(LONG irow, LONG icol)
{
	CLCellItem* ptrCell=NULL;
	LONG index;
	if(m_pMergeArr==NULL)
		ptrCell=GetACell(irow,icol);
	else
		ptrCell=m_pMergeArr->GetMasterCell(irow,icol,index);
	return (ptrCell?ptrCell->GetText():NULL);
}

void CLGrid::SetMasterCellText(LONG irow, LONG icol, LPTSTR ptrTxt)
{
	CLCellItem* ptrCell=NULL;
	LONG index;
	if(m_pMergeArr==NULL)
		ptrCell=GetACell(irow,icol,TRUE);
	else
		ptrCell=m_pMergeArr->GetMasterCell(irow,icol,index,TRUE);
	ptrCell->SetText(ptrTxt);
}

BOOL CLGrid::MergeCurrentRange(LONG nType)
{
	RANGE range;
	GetCurrentRange(range);
	return MergeRange(range,nType);
}
BOOL CLGrid::UnMergeCurrentRange()
{
	RANGE range;
	GetCurrentRange(range);
	return RemoveMergeRange(range);
}

//
//剪切当前范围数据
void CLGrid::CutDataToClipBox()
{
	CopyDataToClipBox();
	ClearRangeData(m_CurrRange);
}
void CLGrid::CopyDataToClipBox()
{
	CopyDataToClipBox(m_CurrRange);
}
void CLGrid::CopyDataToClipBox(RANGE &range)
{
	if(!range.isEmpty()){
		RANGE rgn=range;
		rgn.AdjustRange();
		VALUE_LINK link,*ptrLink=NULL;
		CLMerge* ptrMerge=NULL;
		CLCellItem* ptrItem=NULL;
		RECT rct;
		BOOL bHasData=FALSE;
		std::string str="";
		char* ptrTxt=NULL;
		for(LONG irow=rgn.m_posRow.m_begin;irow<=rgn.m_posRow.m_end;irow++){
			for(LONG icol=rgn.m_posCol.m_begin;icol<=rgn.m_posCol.m_end;icol++){
				if(m_pMergeArr){
					ptrMerge=m_pMergeArr->getMergeObject(irow,icol,ptrItem,FALSE);
					if(ptrMerge){
						ptrMerge->getRange(&rct);
						if(icol>rgn.m_posCol.m_begin){
							str.append("\t\0");
						}
						if(irow==rct.top && icol==rct.left){
							//是主单元格
							ptrTxt=ptrItem->GetText();
							if(ptrTxt){
								bHasData=TRUE;
								str.append(ptrTxt);
							}
						}
					}else{
						ptrItem=GetACell(irow,icol);
						if(icol>rgn.m_posCol.m_begin){
							str.append("\t\0");
						}
						if(ptrItem){
							ptrTxt=ptrItem->GetText();
							if(ptrTxt){
								bHasData=TRUE;
								str.append(ptrTxt);
							}
						}
					}
				}else{
					//没有合并单元
					ptrItem=GetACell(irow,icol);
					if(icol>rgn.m_posCol.m_begin){
						str.append("\t\0");
					}
					if(ptrItem){
						ptrTxt=ptrItem->GetText();
						if(ptrTxt){
							bHasData=TRUE;
							str.append(ptrTxt);
						}
					}
				}
			}
			if(irow>=rgn.m_posRow.m_begin){
				str.append("\r\n\0");
			}
		}
		if(bHasData){
			//确定有数据
			DWORD nLen=str.length()+1;
			HGLOBAL hMem=GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE,nLen);
			LPVOID ptr=GlobalLock(hMem);
			
			strcpy((char*)ptr,(char*)str.c_str());
			GlobalUnlock(hMem);
			OpenClipboard(NULL);
			EmptyClipboard();
			SetClipboardData(CF_TEXT,hMem);
			CloseClipboard();
		}
	}
}

void CLGrid::GetDataFromClipBox()
{
	OpenClipboard(NULL);
	LPVOID ptr=NULL;
	HGLOBAL hmem=GetClipboardData(CF_TEXT);
	if(hmem){
		char* ptrT=NULL;
		ptr=GlobalLock(hmem);
		if(ptr!=NULL){
			LONG nLen=strlen((char*)ptr);
			if(nLen>0){
				ptrT=new char[nLen+1];
				strcpy(ptrT,(char*)ptr);
				PasteData(ptrT);
				delete[] ptrT;
			}
			GlobalUnlock(hmem);
		}
		ReDraw(TRUE);
	}
	CloseClipboard();
}
/**
*			数据粘贴格式: 列间tab分隔 行间Return分隔
*			可以处理来自Excel的数据，但会丢失
*			格式信息:(
**/
BOOL CLGrid::PasteData(LPTSTR ptrText)
{
	BOOL bRet=FALSE;
	//得到当前焦点单元
	//如果当前行列/范围小于待粘贴的数据尺寸则自动扩展行列
	
	ROWCHAIN rowRange;
	SIZE size;
	
	if(validPasteData(ptrText,size,rowRange)){
		LONG nEndRow=m_currentCell.Row+size.cy-1,nEndCol=m_currentCell.Col+size.cx-1;
		if(nEndRow>m_Rows-1){
			SetRows(nEndRow+1);
		}
		if(nEndCol>m_Cols-1){
			SetCols(nEndCol+1);
		}
		LPROWCHAIN ptrChainRow=&rowRange;
		LPCOLCHAIN ptrChainCol=NULL;
		CLCellItem* ptrItem=NULL;
		char* ptrTxt=NULL;
		for(LONG irow=m_currentCell.Row;irow<=nEndRow;irow++){
			if(ptrChainRow){
				ptrChainCol=ptrChainRow->ptrCol;
				for(LONG icol=m_currentCell.Col;icol<=nEndCol;icol++){
					if(ptrChainCol){
						ptrTxt=ptrChainCol->ptrData;
						if(ptrTxt){
							ptrItem=GetACell(irow,icol,TRUE);
							ASSERT(ptrItem!=NULL);
							ptrItem->SetText(ptrTxt);
						}else{
							ptrItem=GetACell(irow,icol);
							if(ptrItem){
								ptrItem->SetText(ptrTxt);
							}
						}
						ptrChainCol=ptrChainCol->ptrNext;
					}
				}
				ptrChainRow=ptrChainRow->ptrNext;
			}
		}
		m_CurrRange.m_posRow.m_begin=m_currentCell.Row;
		m_CurrRange.m_posRow.m_end=nEndRow;
		m_CurrRange.m_posCol.m_begin=m_currentCell.Col;
		m_CurrRange.m_posCol.m_end=nEndCol;
	}
	ReDraw(TRUE);
	return bRet;
}
//数据校验
BOOL CLGrid::validPasteData(LPTSTR ptrText,SIZE& size,ROWCHAIN& rowRange)
{
	BOOL bRet=TRUE;
	
	char cSpRow[3]={'\r','\n','\0'};
	char* ptr=ptrText,*ptrPos=NULL,*ptrT=NULL;
	char ptrData[1024];//缓存
	LONG nTmpLen=1024;
	LONG nRows=0,nCols=0,nTmpCols;
	LONG nLen=0,nLenT=0;
	size.cx=0;
	size.cy=0;
	nLen=2;
	LPROWCHAIN	ptrRowLink=NULL;
	while(*ptr){
		//首先得到一行
		ptrPos=strstr(ptr,cSpRow);
		if(nRows==0){
			ASSERT(ptrRowLink==NULL);
			ptrRowLink=&rowRange;
		}else{
			ASSERT(ptrRowLink!=NULL);
			if(ptrRowLink->ptrNext==NULL)
				ptrRowLink->ptrNext=new ROWCHAIN();
			ptrRowLink=ptrRowLink->ptrNext;
		}
		nRows++;
		if(ptrPos){
			nLenT=ptrPos-ptr;
			if(nLenT<nTmpLen){
				strncpy(ptrData,ptr,nLenT);
				ptrData[nLenT]='\0';
				if(ptrRowLink->ptrCol==NULL)
					ptrRowLink->ptrCol=new COLCHAIN();
				nTmpCols=getARowData(ptrData,*(ptrRowLink->ptrCol));
				if(nTmpCols<=0/* || (nCols>0 && nTmpCols!=nCols)*/){
					bRet=FALSE;
				}
				if(nCols<nTmpCols)
					nCols=nTmpCols;
			}else{
				ptrT=new char[nLenT+1];
				strncpy(ptrT,ptr,nLenT);
				ptrT[nLenT]='\0';
				if(ptrRowLink->ptrCol==NULL)
					ptrRowLink->ptrCol=new COLCHAIN();
				nTmpCols=getARowData(ptrT,*(ptrRowLink->ptrCol));
				if(nTmpCols<=0/* || (nCols>0 && nTmpCols!=nCols)*/){
					bRet=FALSE;
				}
				if(nCols<nTmpCols)
					nCols=nTmpCols;
				delete[] ptrT;
				ptrT=NULL;
			}
			ptr=ptrPos+nLen;
		}else{
			//嘿嘿没有行结束标志
			//可能是最后一行了
				//真的是最后一行呵呵
			if(ptrRowLink->ptrCol==NULL)
				ptrRowLink->ptrCol=new COLCHAIN();
			nTmpCols=getARowData(ptr,*(ptrRowLink->ptrCol));
			if(nTmpCols<=0/* || (nCols>0 && nTmpCols!=nCols)*/){
				bRet=FALSE;
			}
			if(nCols<nTmpCols)
				nCols=nTmpCols;
			
			break;
		}
	}
	size.cx=nCols;
	size.cy=nRows;
	return bRet;
}

LONG CLGrid::getARowData(LPTSTR ptrData, COLCHAIN &colRange)
{
	ASSERT(ptrData!=NULL);
	char cSpCol[2]={'\t','\0'};
	LONG nCols=0,nLenSp=1,nLen;
	char* ptr=ptrData,*ptrPos=NULL,*ptrT=NULL;
	char tmpStr[256];
	LONG nTmpLen=256;
	LPCOLCHAIN	ptrColLink=NULL;
	while(*ptr){
		ptrPos=strstr(ptr,cSpCol);
		if(nCols==0){
			//第一列
			ASSERT(ptrColLink==NULL);
			ptrColLink=&colRange;
		}else{
			ASSERT(ptrColLink!=NULL);
			if(ptrColLink->ptrNext==NULL)
				ptrColLink->ptrNext=new COLCHAIN();
			ptrColLink=ptrColLink->ptrNext;
		}
		nCols++;
		if(ptrPos){
			nLen=ptrPos-ptr;
			if(ptrPos>ptr){
				//确保列值不为空
				if(nTmpLen>nLen){
					strncpy(tmpStr,ptr,nLen);
					tmpStr[nLen]='\0';
					ptrColLink->setText(tmpStr);
				}else{
					ptrT=new char[nLen+1];
					strncpy(ptrT,ptr,nLen);
					ptrT[nLen]='\0';
					ptrColLink->setText(ptrT);
					delete[] ptrT;
					ptrT=NULL;
				}
			}
			ptr=ptrPos+nLenSp;
			if(!(*ptr)){
				if(nCols==0){
					//第一列
					ASSERT(ptrColLink==NULL);
					ptrColLink=&colRange;
				}else{
					ASSERT(ptrColLink!=NULL);
					if(ptrColLink->ptrNext==NULL)
						ptrColLink->ptrNext=new COLCHAIN();
					ptrColLink=ptrColLink->ptrNext;
				}
				nCols++;
			}
		}else{
			//最后一列
			ptrColLink->setText(ptr);
			break;
		}
	}
	return nCols;
}

BOOL CLGrid::AppendRow()
{
	SetRows(m_Rows+1);
	ReDraw(TRUE);
	return TRUE;
}

BOOL CLGrid::InsertRow(BOOL bBefore)
{
	if(m_currentCell.Row>=0){
		SetRows(m_Rows+1);
		LONG nPosRow=m_currentCell.Row;
		if(!bBefore){
			nPosRow++;
		}
		MoveRows(nPosRow);
		BOOL bclrMerge=AdjustMergeObjectRange(nPosRow,1);
		ClearARow(nPosRow,bclrMerge);
		if(bBefore){
			m_prevFocusCell.Row++;
			m_currentCell.Row++;
		}
		m_CurrRange.ClearRange();
		m_OldRange.ClearRange();
		ReDraw(TRUE);
		return TRUE;
	}
	return FALSE;
}

void CLGrid::DeleteCurrentRow()
{
	if(m_currentCell.Row>=0){
		MoveRows(m_currentCell.Row,1,FALSE);
		LONG cy=GetRowHeight(m_currentCell.Row);
		AdjustMergeObjectRange(m_currentCell.Row,1,TRUE,FALSE);
		ClearARow(m_Rows-1);
		SetRows(m_Rows-1);
		AdjustSizeChange(0,cy);
		ReDraw(TRUE);
	}
}

BOOL CLGrid::InsertCol(BOOL bBefore)
{
	if(m_currentCell.Col>=0){
		SetCols(m_Cols+1);
		LONG nPosCol=m_currentCell.Col;
		if(!bBefore){
			nPosCol++;
		}
		MoveCols(nPosCol);
		BOOL bclrMerge=AdjustMergeObjectRange(nPosCol,1,FALSE);
		ClearACol(nPosCol,bclrMerge);
		if(bBefore){
			m_prevFocusCell.Col++;
			m_currentCell.Col++;
		}
		m_CurrRange.ClearRange();
		m_OldRange.ClearRange();
		ReDraw(TRUE);
		return TRUE;
	}
	return FALSE;
}

BOOL CLGrid::AppendCol()
{
	SetCols(m_Cols+1);
	ReDraw(TRUE);
	return TRUE;
}

void CLGrid::DeleteCurrentCol()
{
	if(m_currentCell.Col>=0){
		MoveCols(m_currentCell.Col,1,FALSE);
		LONG cx=GetColWidth(m_currentCell.Col);
		AdjustMergeObjectRange(m_currentCell.Col,1,FALSE,FALSE);
		ClearACol(m_Cols-1);
		SetCols(m_Cols-1);
		AdjustSizeChange(cx,0);
		ReDraw(TRUE);
	}
}
//调整合并对象范围
BOOL CLGrid::AdjustMergeObjectRange(LONG nPos, LONG nOffset, 
		 BOOL bIsRow,BOOL bIsAdd, BOOL bDisMergeCurrentCell)
{
	BOOL bRet=FALSE;
	if(m_pMergeArr){
		INDEX key;
		LONG nInc=(bIsAdd?1:-1);
		CLMerge* ptrItem;
		POSITION pos = m_pMergeArr->GetStartPosition();
		RECT rct;
		while (pos != NULL)
		{
			m_pMergeArr->GetNextAssoc(pos, key, ptrItem);
			ptrItem->getRange(&rct);
			if(bIsRow){
				if(bDisMergeCurrentCell){
					//需要解散包含当前行的所有合并对象
					if(rct.top<=nPos && rct.bottom>=nPos){
						
					}else if(rct.top>nPos){
						rct.top+=nInc;
						rct.bottom+=nInc;
						if(rct.top<nPos)
							rct.top=nPos;
						if(rct.bottom<nPos)
							rct.bottom=nPos;
						bRet=TRUE;
						ptrItem->setRange(&rct);
					}
				}else{
					//不解散，但需要更新当前行合并域
					if(rct.top<nPos){
						if(rct.bottom>=nPos)
							rct.bottom+=nInc;
						ptrItem->setRange(&rct);
					}else if(rct.top>=nPos){
						rct.bottom+=nInc;
						rct.top+=nInc;
						ptrItem->setRange(&rct);
						bRet=TRUE;
					}
				}
			}else{
				//是列
				if(bDisMergeCurrentCell){
					//需要解散包含当前行的所有合并对象
					if(rct.left<=nPos && rct.right>=nPos){
						
					}else if(rct.left>nPos){
						rct.left+=nInc;
						rct.right+=nInc;
						if(rct.left<nPos)
							rct.left=nPos;
						if(rct.right<nPos)
							rct.right=nPos;
						ptrItem->setRange(&rct);
						bRet=TRUE;
					}
				}else{
					//不解散，但需要更新当前行合并域
					if(rct.left<nPos){
						//在起始区域右边
						if(rct.right>=nPos)
							rct.right+=nInc;
						ptrItem->setRange(&rct);
					}else if(rct.left>=nPos){
						rct.right+=nInc;
						rct.left+=nInc;
						ptrItem->setRange(&rct);
						bRet=TRUE;
					}
				}
			}
		}
	}
	return bRet;
}

void CLGrid::MoveCols(LONG nReplaceCol, LONG nCols,BOOL bAdd)
{
	if(bAdd){
		for(LONG nCol=m_Cols-2;nCol>=nReplaceCol;nCol--){
			ReplaceACol(nCol+1,nCol);
		}
	}else{
		for(LONG nCol=nReplaceCol+1;nCol<m_Cols;nCol++){
			ReplaceACol(nCol-1,nCol);
		}
	}
}

void CLGrid::MoveRows(LONG nReplaceRow, LONG nRows,BOOL bAdd)
{
	if(bAdd){
		for(LONG nRow=m_Rows-2;nRow>=nReplaceRow;nRow--){
			ReplaceARow(nRow+1,nRow);
		}
	}else{
		for(LONG nRow=nReplaceRow+1;nRow<m_Rows;nRow++){
			ReplaceARow(nRow-1,nRow);
		}
	}
}

void CLGrid::ClearARow(LONG nRow,BOOL bclrMerge)
{
	if(nRow>=0 && nRow<m_Rows){
		CLCellItem* ptrItem;
		CLStyle* ptrStyle;
		CLFont* ptrFont;
		for(LONG nCol=0;nCol<m_Cols;nCol++){
			ptrItem=GetACell(nRow,nCol);
			ptrStyle=GetCellStyle(nRow,nCol);
			ptrFont=GetCellFont(CELL(nRow,nCol));
			if(ptrItem)
				ptrItem->ClearToDefault(bclrMerge);
			if(ptrStyle)
				ptrStyle->ClearToDefault();
			if(ptrFont)
				ptrFont->ClearToDefault();
		}
	}
}

void CLGrid::ClearACol(LONG nCol,BOOL bclrMerge)
{
	if(nCol>=0 && nCol<m_Cols){
		CLCellItem* ptrItem;
		CLStyle* ptrStyle;
		CLFont* ptrFont;
		for(LONG nRow=0;nRow<m_Rows;nRow++){
			ptrItem=GetACell(nRow,nCol);
			ptrStyle=GetCellStyle(nRow,nCol);
			ptrFont=GetCellFont(CELL(nRow,nCol));
			if(ptrItem)
				ptrItem->ClearToDefault(bclrMerge);
			if(ptrStyle)
				ptrStyle->ClearToDefault();
			if(ptrFont)
				ptrFont->ClearToDefault();
		}
	}
}

void CLGrid::ReplaceARow(LONG nDstRow, LONG nSrcRow)
{
	CLCellItem* ptrItemSrc,*ptrItemDst;
	for(LONG nCol=0;nCol<m_Cols;nCol++){
		ptrItemSrc=GetACell(nSrcRow,nCol);
		if(ptrItemSrc){
			ptrItemDst=GetACell(nDstRow,nCol,TRUE);
			ptrItemDst->SetCell(ptrItemSrc);
		}else{
			ptrItemDst=GetACell(nDstRow,nCol);
			if(ptrItemDst){
				ptrItemDst->ClearToDefault();
			}
		}
	}
}

void CLGrid::ReplaceACol(LONG nDstCol, LONG nSrcCol)
{
	CLCellItem* ptrItemSrc,*ptrItemDst;
	for(LONG nRow=0;nRow<m_Rows;nRow++){
		ptrItemSrc=GetACell(nRow,nSrcCol);
		if(ptrItemSrc){
			ptrItemDst=GetACell(nRow,nDstCol,TRUE);
			ptrItemDst->SetCell(ptrItemSrc);
		}else{
			ptrItemDst=GetACell(nRow,nDstCol);
			if(ptrItemDst){
				ptrItemDst->ClearToDefault();
			}
		}
	}
}

void CLGrid::SetRangeBkColor(RANGE &range, COLORREF clr)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		CLStyle* ptrStyle;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				ptrStyle=GetCellStyle(irow,icol,TRUE);
				ptrStyle->SetBkColor(clr);
			}
		}
		ReDraw();
	}
}

void CLGrid::SetRangeForeColor(RANGE &range, COLORREF clr)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		CLFont* ptrFont;
		CELL cell;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			cell.Row=irow;
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				cell.Col=icol;
				ptrFont=GetCellFont(cell,TRUE);
				ptrFont->m_clr=clr;
			}
		}
		ReDraw();
	}
}


void CLGrid::SetRangeBorderLineStyle(RANGE &range, LONG nStyle)
{
	if(!range.isEmpty()){
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				SetBorderStyle(irow,icol,nStyle);
			}
		}
		ReDraw();
	}
}


void CLGrid::HideInPlaceCtrl()
{
	
}
void CLGrid::ClearRangeData(RANGE &range)
{
	if(!range.isEmpty()){
		HideInPlaceCtrl();
		RECT rct;
		RANGE rgn=range;
		rgn.AdjustRange();
		rgn.GetRangeRect(rct);
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				ClearCellData(irow,icol,FALSE);
			}
		}
		ReDraw();
	}
}
//序列化接口
BOOL CLGrid::OnSerial(CLSerial& ar)
{
	BOOL bret=TRUE;
	if(CLTable::OnSerial(ar)){
		BYTE byt;
		LONG val;
		CLMerge* ptrItem;
		if(!m_TrackCurr.OnSerial(ar))
			return FALSE;
		if(!m_TrackOld.OnSerial(ar))
			return FALSE;
		if(ar.isLoading()){
			//读取操作
			ar>>m_bExcelMode;
			ar>>m_bFillFocus;
			ar>>m_bRangeMode;
			ar>>m_bScrollByCell;
			ar>>m_clrGridLine;
			ar>>m_nPerLogicPixel;
			ar>>m_nSelectMode;
			ar>>byt;
			if(byt==1){
				//有合并对象
				if(m_pMergeArr)
					delete m_pMergeArr;
				m_pMergeArr=new CLMergesArr(this);
				m_pMergeArr->OnSerial(ar);
				ar>>byt;
				while(byt==1){
					//有合并项
					ar>>val;
					ptrItem=m_pMergeArr->NewMerge(val);
					ASSERT(ptrItem!=NULL);
					ptrItem->OnSerial(ar);
					ar>>byt;
				}
			}
		}else{
			//保存操作
			ar<<m_bExcelMode;
			ar<<m_bFillFocus;
			ar<<m_bRangeMode;
			ar<<m_bScrollByCell;
			ar<<m_clrGridLine;
			ar<<m_nPerLogicPixel;
			ar<<m_nSelectMode;
			if(m_pMergeArr){
				byt=1;
				ar<<byt;
				m_pMergeArr->OnSerial(ar);
				INDEX key;
				
				POSITION pos = m_pMergeArr->GetStartPosition();

				if(pos==NULL){
					byt=0;
					ar<<byt;
				}else{
					while (pos != NULL){
						m_pMergeArr->GetNextAssoc(pos, key, ptrItem);
						byt=1;
						ar<<byt;
						val=key.Index;
						ar<<val;
						ptrItem->OnSerial(ar);
					}
					byt=0;
					ar<<byt;
				}
			}else{
				byt=0;
				ar<<byt;
			}
		}
	}
	return bret;
}
//自动滚动到能够完全看到指定单元格
void CLGrid::AutoAdjustPos(const CELL& cell)
{
	//首先看看指定单元格是否可见
	RANGE range;
	GetMergeRange(cell,range);
	
	BOOL bClip=FALSE;
	RECT rctOff;
	if(isRangeVisible(range,&bClip,&rctOff)){
		//可见
		if(bClip){
			//被裁减了
			if(rctOff.left>0){
				ScrollHorz(NULL,-rctOff.left);
			}else if(rctOff.right>0){
				ScrollHorz(NULL,rctOff.right);
			}
			if(rctOff.top>0){
				ScrollVert(NULL,-rctOff.top);
			}else if(rctOff.bottom>0){
				ScrollVert(NULL,rctOff.bottom);
			}
		}
	}else{
		//不可见
		CELL cellEnd;
		POINT ptOffset;
		SIZE size;
		GetClientSize(size);
		GetRightBottomCell(size,cellEnd,ptOffset);
		CELL cellC;
		GetBeginCell(cellC);
		if(cell.Row<cellC.Row)
			ScrollVert(NULL,cell.Row-cellC.Row);
		else if(cell.Row>cellEnd.Row)
			ScrollVert(NULL,cell.Row-cellEnd.Row);
		if(cell.Col<cellC.Col)
			ScrollHorz(NULL,cell.Col-cellC.Col);
		else if(cell.Col>cellEnd.Col)
			ScrollHorz(NULL,cell.Col-cellEnd.Col);
	}
}