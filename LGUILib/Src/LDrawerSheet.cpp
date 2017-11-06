//////////////////////////////////////////////////////////////////////
//@模块		 ：工作表绘制实现类
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LDrawerSheet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//static int nttt=0;
CLDrawerSheet::CLDrawerSheet(ISheet* ptrSheet):m_scaleX(1.0),m_scaleY(1.0)
{
	m_size.cx=0;
	m_size.cy=0;
	m_beginPos.x=0;
	m_beginPos.y=0;
	AttachSheet(ptrSheet);
}

CLDrawerSheet::~CLDrawerSheet()
{
	
}
void CLDrawerSheet::AttachSheet(ISheet* ptrSheet)
{
	if(ptrSheet){
		m_ptrSheet=ptrSheet;
		m_ptrSheet->SetDDrawObj(this);
		m_ptrGrid=m_ptrSheet->GetGrid();
		m_ptrTable=m_ptrGrid->GetTable();
	}else{
		m_ptrSheet=NULL;
		m_ptrGrid=NULL;
		m_ptrTable=NULL;
	}
}
void CLDrawerSheet::FillNoClientArea(LPHDC pDC,const RECT& rctAll)
{
	RECT rect,rctT,rctClip;
	if(!pDC->bIsPrint){
		m_ptrTable->GetTableRect(rect);
		m_ptrTable->GetClientRect(rctT);
	}else{
		m_ptrTable->GetTableRect(rctAll,rect);
		m_ptrTable->GetClientRect(rctAll,rctT);
	}
	rect.right=rctT.right;
	rect.bottom=rctT.bottom;
	if(!pDC->bIsPrint){
		m_ptrTable->GetClientRect(rctT,TRUE);
	}else{
		m_ptrTable->GetClientRect(rctAll,rctT);
	}
	rctClip=rect;
	rctClip.left=rctT.right;
	
	CLDrawer::FillSolidRect(pDC->hDC,&rctClip,RGB(255,255,255));
	rctClip=rect;
	rctClip.top=rctT.bottom;
	rctClip.right=rctT.right;
	CLDrawer::FillSolidRect(pDC->hDC,&rctClip,RGB(255,255,255));
}

void CLDrawerSheet::OnDraw(LPHDC pDC,const RECT& rct)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(m_ptrSheet){
		FillNoClientArea(pDC,rct);
		DrawGridLine(pDC,rct);//最先画表格线
		//if(!pDC->bIsPrint)
		DrawClientArea(pDC,rct);
		POINT pt_freez;
		pt_freez.x=m_ptrTable->GetFreezeCols();
		pt_freez.y=m_ptrTable->GetFreezeRows();
		BOOL bHasFreezeCell=(pt_freez.x || pt_freez.y);
		
		if(bHasFreezeCell){
			DrawFreezeCells(pDC,rct);
			if(!pDC->bIsPrint)
				DrawFreeeLine(pDC);
		}
		if(!pDC->bIsPrint)
		{
			DrawFocusCell(pDC);//画焦点单元
			RANGE range;
			m_ptrTable->GetCurrentRange(range);
			DrawSelectRange(pDC,FALSE,m_ptrGrid->isFocusCell(range));
		}
		CLDrawItemMgrl* ptrDraw=m_ptrSheet->GetDrawItemsArr();
		POINT pt;
		m_ptrTable->GetBeginFreezePos(pt);
		
		//ptrDraw->OnDraw(pDC,pt,pt_freez,bHasFreezeCell?type_draw_client:type_draw_all);

		
		//画客户区外图案
		ptrDraw->OnDraw(pDC,pt,pt_freez,type_draw_all);
		/*
		if(bHasFreezeCell){
			ptrDraw->OnDraw(pDC,pt,pt_freez,type_draw_none_client);
		}
		*/
		DrawFixedCells(pDC,rct);
#ifdef SHARE_VERSION
		//共享版
		RECT rctClip;
		m_ptrTable->GetDrawPanRect(rctClip);
		rctClip.bottom=rctClip.top+FLAG_BAR_HEIGHT;
		
		HFONT hfont=CLDrawer::CreateFontIndirect(&DEFAULT_LOGFONT);
		CLDrawer::Draw3DText(pDC->hDC,hfont,SHARE_STRING,rctClip,GetSysColor(COLOR_BTNFACE));
		CLDrawer::DrawerLine(pDC->hDC,rctClip.left,rctClip.bottom-1
			,rctClip.right,rctClip.bottom-1,COLOR_GRID_BORDER);
		CLDrawer::DeleteFont(hfont);
#endif
	}
}
//画当前焦点单元
void CLDrawerSheet::DrawFocusCell(LPHDC pDC,LPCELL pCellCur,LPCELL pCellOld)
{
	if(!m_ptrSheet)return;
	HDCH hDC;
	BOOL bNull=FALSE,bExcel=m_ptrGrid->isExcelMode();
	if(!pDC){
		m_ptrTable->GetDC(hDC);
		pDC=&hDC;
		bNull=TRUE;
	}
	CELL cellCur,cellBegin,cellEnd,cellOldCur;
	LONG nBeforRow,nBeforCol;
	RECT rctClip,rctClipOld;
	POINT ptOffset;
	RANGE range;
	SIZE size;
	m_ptrTable->GetClientSize(size);
	m_ptrTable->GetRightBottomCell(size,cellEnd,ptOffset);
	m_ptrTable->GetBeginCell(cellBegin);
	if(!pCellCur)
		m_ptrTable->GetCurrentCell(cellCur);
	else
		cellCur=(*pCellCur);
	if(!pCellOld)
		m_ptrTable->GetPrevFocusCell(cellOldCur);
	else
		cellOldCur=(*pCellOld);
	
	if(cellOldCur.Row<0 || cellOldCur.Col<0){
		cellOldCur=cellCur;
		m_ptrTable->SetPrevFocusCell(cellOldCur);
	}
	m_ptrGrid->GetMergeRange(cellCur,range);
	nBeforRow=cellOldCur.Row;
	nBeforCol=cellOldCur.Col;
	if(cellCur.Row>=0 && cellCur.Col>=0){
		RECT rct;
		HRGN hrgn=NULL,hrgnBefor=NULL;
		
		//当前行/列必须已经确定
		//检查选择模式
		if(m_ptrGrid->getSelectMode()==SELECT_BY_ROW && 
			cellCur.Col>=m_ptrTable->GetFixedCols() && cellCur.Row>=m_ptrTable->GetFixedRows()){
			
			if((!(cellCur==cellOldCur)) && nBeforRow>=m_ptrTable->GetFixedRows() && nBeforRow<=cellEnd.Row){
				hrgnBefor=m_ptrGrid->GetRowRgn(nBeforRow,rctClipOld);
			}
			hrgn=m_ptrGrid->GetRowRgn(cellCur.Row,rctClip);
		}else if(cellCur.Row>=m_ptrTable->GetFixedRows() && cellCur.Col>=m_ptrTable->GetFixedCols()){
			if(!(cellCur==cellOldCur) &&
				nBeforCol>=0 && nBeforRow>=m_ptrTable->GetFixedRows() && nBeforCol>=m_ptrTable->GetFixedCols()
				&& nBeforRow<=cellEnd.Row && nBeforCol<=cellEnd.Col){
				if(m_ptrGrid->GetCellRect(nBeforRow,nBeforCol,rct,rctClipOld,FALSE)){
					if(bExcel){
						rct.right--;
						rct.bottom--;
					}else{
						rct.left--;
						rct.top--;
					}
					hrgnBefor=CLDrawer::CreateRectRgn(rct);
				}
			}
			if(m_ptrGrid->GetCellRect(cellCur.Row,cellCur.Col,rct,rctClip,FALSE)){
				if(bExcel){
					rct.right--;
					rct.bottom--;
				}else{
					rct.left--;
					rct.top--;
				}
				hrgn=CLDrawer::CreateRectRgn(rct);
			}
		}
		if(hrgnBefor!=NULL){
			//确定裁减区域
			CLClipDC clipDC(pDC->hDC,rctClipOld);
			CLDrawer::SetFocus(pDC->hDC,hrgnBefor,!bExcel && m_ptrGrid->isFillFocusMode(),
				COLOR_FOCUSE_BORDER,FALSE,
				(m_ptrGrid->getSelectMode()==SELECT_BY_CELL) && (bExcel));
			CLDrawer::DeleteRgn(hrgnBefor);
		}
		if(hrgn!=NULL){
			CLClipDC clipDC(pDC->hDC,rctClip);
			CLDrawer::SetFocus(pDC->hDC,hrgn,!bExcel && m_ptrGrid->isFillFocusMode(),
				COLOR_FOCUSE_BORDER,FALSE,
				(m_ptrGrid->getSelectMode()==SELECT_BY_CELL) && (bExcel));
			CLDrawer::DeleteRgn(hrgn);
		}
		if(bNull){
			CLDrawItemMgrl* ptrDraw=m_ptrSheet->GetDrawItemsArr();
			POINT pt,pt_freeze;
			m_ptrTable->GetBeginFreezePos(pt);
			pt_freeze.x=cellBegin.Col-1;
			pt_freeze.y=cellBegin.Row-1;
			CLClipDC clipDC(pDC->hDC,rctClip);
			ptrDraw->OnDraw(pDC,pt,pt_freeze,type_draw_all);
			m_ptrTable->ReleaseDC(hDC);
		}
	}
}
void CLDrawerSheet::DrawClientArea(LPHDC pDC,const RECT& rctAll)
{
	if(m_ptrSheet){
		LONG valx,valy,irow,icol;
		RECT rect;
		POINT posxy;
		BOOL bFind=FALSE;
		CELL cellBegin;
		m_ptrTable->GetCellBeginXY(posxy);
		if(!pDC->bIsPrint)
			m_ptrTable->GetClientRect(rect,TRUE);
		else{
			m_ptrTable->GetClientRect(rctAll,rect);
		}
		if(rect.top>=rect.bottom || rect.left>=rect.right)return;
		m_ptrTable->GetBeginCell(cellBegin);
		
		
		CLRowItem* ptrRow;
		CLColItem* ptrCol;
		RECT rctClip=rect;
		CELLITEMDRAWER	drawerCell;
		drawerCell.m_hDC=pDC->hDC;
		drawerCell.bIsPrint=pDC->bIsPrint;
		drawerCell.m_lpRect=&rctClip;
		//if(!pDC->bIsPrint)
		CLClipDC clip(pDC->hDC,rect);
		
		rctClip.left-=posxy.x;
		rctClip.top-=posxy.y;
		for(irow=cellBegin.Row;irow<m_ptrTable->GetRows();irow++){
			ptrRow=m_ptrTable->GetARow(irow);
			valy=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			rctClip.bottom=rctClip.top+valy;
			drawerCell.m_cell.Row=irow;
			bFind=FALSE;
			for(icol=cellBegin.Col;icol<m_ptrTable->GetCols();icol++){
				ptrCol=m_ptrTable->GetACol(icol);
				valx=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				rctClip.right=rctClip.left+valx;
				drawerCell.m_cell.Col=icol;
				DrawACell(drawerCell,rctAll);
				if((rctClip.right)*(pDC->bIsPrint?m_scaleX:1)>=rect.right){
					//已经到达最末列
					bFind=TRUE;
					rctClip.left=rect.left-posxy.x;
					break;
				}
				rctClip.left+=valx;
			}
			if(!bFind)
				rctClip.left=rect.left-posxy.x;
			if((rctClip.bottom)*(pDC->bIsPrint?m_scaleY:1)>=rect.bottom){
				//已经到达最末行
				break;
			}
			rctClip.top+=valy;
		}
	}
}
void CLDrawerSheet::DrawGridLine(LPHDC pDC,const RECT& rctAll)
{
	if(!m_ptrSheet)return;
	LONG nStyle=m_ptrSheet->GetSheetLineStyle();
	if(!(nStyle & GRID_NO_VERT_LINE))
		DrawVertLine(pDC,rctAll);
	if(!(nStyle & GRID_NO_HORZ_LINE)){
		DrawHorzLine(pDC,rctAll);
	}
}

void CLDrawerSheet::DrawHorzLine(LPHDC pDC,const RECT& rctAll)
{
	if(!m_ptrTable)return;
	RECT rct;
	CELL cell;
	POINT pt,ptFreeze;
	BOOL bHasFreezeCell=m_ptrTable->GetFreezeCols()>0 || m_ptrTable->GetFreezeRows()>0;
	LONG nRows=m_ptrTable->GetRows();
	if(!pDC->bIsPrint){
		m_ptrTable->GetClientRect(rct,TRUE);
		m_ptrTable->GetBeginFreezePos(ptFreeze);
		
	}else{
		m_ptrTable->GetClientRect(rctAll,rct);
		m_ptrTable->GetBeginFreezePos(rctAll,ptFreeze);
	}
	m_ptrTable->GetBeginCell(cell);
	m_ptrTable->GetCellBeginXY(pt);
	RECT rctClient=rct;
	LONG nBeginTop=rctClient.top-pt.y-1;
	DrawGridLine(pDC,rctClient,cell.Row,nRows,nBeginTop,pt.x,FALSE);
	if(bHasFreezeCell){
		rctClient=rct;
		rctClient.right=rctClient.left;
		rctClient.left=ptFreeze.x;
		nBeginTop=rctClient.top-pt.y-1;
		DrawGridLine(pDC,rctClient,cell.Row,nRows,nBeginTop,0,FALSE);
		
		rctClient=rct;
		rctClient.left=ptFreeze.x;
		rctClient.bottom=rctClient.top;
		rctClient.top=ptFreeze.y;
		nBeginTop=rctClient.top-1;
		nRows=m_ptrTable->GetFixedRows()+m_ptrTable->GetFreezeRows();
		DrawGridLine(pDC,rctClient,m_ptrTable->GetFixedRows(),nRows,nBeginTop,0,FALSE);
	}
}

void CLDrawerSheet::DrawVertLine(LPHDC pDC,const RECT& rctAll)
{
	if(!m_ptrTable)return;
	RECT rct;
	POINT pt,ptFreeze;
	CELL cell;
	BOOL bHasFreezeCell=m_ptrTable->GetFreezeCols()>0 || m_ptrTable->GetFreezeRows()>0;
	LONG nCols=m_ptrTable->GetCols();
	m_ptrTable->GetCellBeginXY(pt);
	if(!pDC->bIsPrint){
		m_ptrTable->GetClientRect(rct,TRUE);
		m_ptrTable->GetBeginFreezePos(ptFreeze);
	}else{
		m_ptrTable->GetClientRect(rctAll,rct);
		m_ptrTable->GetBeginFreezePos(rctAll,ptFreeze);
	}
	m_ptrTable->GetBeginCell(cell);
	
	
	RECT rctClient=rct;
	LONG nBeginLeft=rctClient.left-pt.x-1;
	DrawGridLine(pDC,rctClient,cell.Col,nCols,nBeginLeft,pt.y);
	if(bHasFreezeCell){
		//画冻结单元竖线
		rctClient=rct;
		rctClient.bottom=rctClient.top;
		rctClient.top=ptFreeze.y;
		nBeginLeft=rctClient.left-pt.x-1;
		DrawGridLine(pDC,rctClient,cell.Col,nCols,nBeginLeft);
		
		rctClient=rct;
		rctClient.right=rctClient.left;
		rctClient.left=ptFreeze.x;
		rctClient.top=ptFreeze.y;
		nBeginLeft=rctClient.left-1;
		nCols=m_ptrTable->GetFixedCols()+m_ptrTable->GetFreezeCols();
		DrawGridLine(pDC,rctClient,m_ptrTable->GetFixedCols(),nCols,nBeginLeft);
	}
}

void CLDrawerSheet::SetSizeInfo(const RECT &rct)
{
	m_size.cx=rct.right-rct.left;
	m_size.cy=rct.bottom-rct.top;
	m_beginPos.x=rct.left;
	m_beginPos.y=rct.top;
}
void CLDrawerSheet::DrawACell(CELLITEMDRAWER &cellDrawer,const RECT& rctAll)
{
	if(!m_ptrTable)return;
	LONG nBorderLineWidth=1;
	LONG nBorderLineDot;
	CELLITEMDRAWER cellD=cellDrawer;
	LONG offsetX=0,offsetY=0;
	CELL cellDraw=cellDrawer.m_cell;
	m_ptrGrid->GetMasterCell(cellDraw);
	CLCellItem* ptrItem=m_ptrTable->GetACell(cellDraw);
	CLFont*	ptrFont=m_ptrTable->GetCellFont(cellDraw);
	CLStyle* ptrStyle=m_ptrTable->GetCellStyle(cellDraw);
	LONG nStyle=0;
	BOOL bFocus=FALSE;
	BOOL bCash=FALSE,bHead=FALSE;
	//ptrStyle->SetFormatStyle(CELL_NUMBER_FORMAT_DOT);
	LONG nFormatStyle;
	ASSERT(ptrFont);
	ASSERT(ptrStyle);
	COLORREF clrBk=ptrStyle->GetBkColor(),clrBorder=ptrStyle->GetBorderColor();
	BOOL	bFixedCell=m_ptrTable->isFixedCell(cellDraw),
		bFreezeCell=m_ptrTable->isFreezeCell(cellDraw),
		bIsMergeCell=m_ptrGrid->isMergeCell(cellDraw);

	nBorderLineDot=ptrStyle->GetBorderLineStyle();
	///////////////////////修改可能的属性//////////////////////////////////
	//看看是否是默认单元格颜色
	BOOL bFillClr=(!bFixedCell && clrBk!=COLOR_BKGRD);
	RECT rctClip=*cellDrawer.m_lpRect,rctC,rctVisible,rctTxt;
	if(bIsMergeCell){
		RANGE rangeT;
		CELL beginCell;
		m_ptrTable->GetBeginCell(beginCell);
		m_ptrGrid->GetMergeRange(cellDraw,rangeT);

		if(rangeT.m_posRow.m_begin>beginCell.Row)
			beginCell.Row=rangeT.m_posRow.m_begin;
		if(rangeT.m_posCol.m_begin>beginCell.Col)
			beginCell.Col=rangeT.m_posCol.m_begin;
		if(!bFreezeCell && !bFixedCell){
			if(!(beginCell==cellDrawer.m_cell)){
				return;
			}
		}

		cellD.cellParam.bMergeCell=bIsMergeCell;
		cellD.cellParam.rangeMerge=rangeT;
		if(!cellDrawer.bIsPrint){
			if(!m_ptrTable->GetRangeRect(rangeT,rctC,rctVisible,rctClip,0)){
				return;
			}
		}else{
			if(!m_ptrTable->GetRangeRect(rctAll,rangeT,rctC,rctVisible,rctClip,0)){
				return;
			}
		}
	}
	cellD.m_cell=cellDraw;
	cellD.m_lpRect=&rctClip;

	MSG_DRAW_CALLBACK(m_ptrTable,MSG_ONDRAWER,TMSG_DRAW_CELL, \
		(WPARAM)&cellD,(LPARAM)bFixedCell);
	rctTxt=rctClip;
	if(!bFixedCell){
		nStyle=m_ptrSheet->GetSheetLineStyle();
		if(nStyle & GRID_NO_VERT_LINE){
			//没有竖线
			rctClip.right++;
			offsetX=1;
		}
		if(nStyle & GRID_NO_HORZ_LINE){
			//没有横线
			rctClip.bottom++;
			offsetY=1;
		}
	}
	///////////////////////End/////////////////////////////////////////////
	//填充背景色
	BOOL bFixedSel=FALSE;
	if(bFixedCell){
		RANGE range;
		m_ptrTable->GetCurrentRange(range);
		clrBk=COLOR_FIXCOLUMNBK;
		if(m_ptrSheet->IsSelFixedRow()){
			if(cellDraw.Row>=range.m_posRow.m_begin &&
				cellDraw.Row<=range.m_posRow.m_end){
				clrBk=RGB(64,64,64);
				bFixedSel=TRUE;
			}else if(m_ptrSheet->IsSelFixedCol()){
				clrBk=RGB(64,64,64);
				bFixedSel=TRUE;		
			}
		}
		if(!bFixedSel && m_ptrSheet->IsSelFixedCol()){
			if(cellDraw.Col>=range.m_posCol.m_begin &&
				cellDraw.Col<=range.m_posCol.m_end){
				clrBk=RGB(64,64,64);
				bFixedSel=TRUE;
			}
		}
		bFocus=((cellDraw.Row>=range.m_posRow.m_begin 
			&& cellDraw.Row<=range.m_posRow.m_end) || 
			(cellDraw.Col>=range.m_posCol.m_begin 
			&& cellDraw.Col<=range.m_posCol.m_end)) && m_ptrGrid->isExcelMode();
		
		CLDrawer::DrawThickRect(cellDrawer.m_hDC,&rctClip,
			clrBk,!bFixedSel,FALSE/*TRUE*/,TRUE);
		//flat
		if(TRUE/*bFocus && !bFixedSel*/){

			//rctClip.left+=1;
			//rctClip.top+=1;
			rctClip.right-=1;
			rctClip.bottom-=1;
			CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rctClip
				,(bFocus && !bFixedSel?clrBk=RGB(245,205,115):clrBk));
			//CLDrawer::DrawThickRect(cellDrawer.m_hDC,&rctClip,
			//	clrBk,FALSE,TRUE,TRUE);
		}
	}else{
		//必须观察周边四个单元以决定实际填充的区域尺寸
		RECT rctBorder=rctClip;
		if(!bFillClr){
			rctBorder.right--;
			rctBorder.bottom--;
		}else{
			if(!bIsMergeCell){
				rctBorder.left--;
				rctBorder.top--;
				if(nStyle & GRID_NO_VERT_LINE){
					//没有竖线
					rctBorder.right--;
				}
				if(nStyle & GRID_NO_HORZ_LINE){
					//没有横线
					rctBorder.bottom--;
				}
			}else{
				if(!(nStyle & GRID_NO_VERT_LINE))
					rctBorder.left--;
				else{
					rctBorder.right--;
				}
				if(!(nStyle & GRID_NO_HORZ_LINE))
					rctBorder.top--;
				else{
					rctBorder.bottom--;
				}
			}
		}
		CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rctBorder,clrBk);
	}
	if(ptrStyle && (nFormatStyle=ptrStyle->GetType())){
		if(nFormatStyle==CELL_CASH_STYLE_HEAD){
			/*金额头*/
			bCash=TRUE;
			bHead=TRUE;
		}else if(nFormatStyle==CELL_CASH_STYLE_BODY){
			/*金额体*/
			bCash=TRUE;
		}
	}
	if(ptrItem){
		LPTSTR ptrTxt;
		if(!(ptrTxt=ptrStyle->GetValue()))
			ptrTxt=m_ptrTable->GetCellText(cellDraw.Row,cellDraw.Col);
		if(bIsMergeCell){
			//ptrTxt=m_ptrGrid->GetMasterCellText(cellDraw.Row,cellDraw.Col);
			BOOL bret=m_ptrGrid->GetMergeRange(cellDraw,
				cellDrawer.cellParam.rangeMerge);
			ASSERT(bret);
			//单元格有合并
		}//else
		//	ptrTxt=m_ptrTable->GetCellText(cellDraw.Row,cellDraw.Col);
		if(ptrTxt){
			if((bFocus && bFixedCell) || bFixedSel){
				CLFont font=(*ptrFont);
				font.m_lf.lfHeight-=2;
				font.m_lf.lfWeight=FW_BOLD;
				font.m_Alignment.bAlignHorz=ahCENTER;
				font.m_Alignment.bAlignVert=avCENTER;
				font.m_clr=(bFixedSel?RGB(255,255,255):RGB(0,0,255));
				ptrFont=&font;
			}else if(bFixedCell){
				CLFont font=(*ptrFont);
				font.m_Alignment.bAlignHorz=ahCENTER;
				font.m_Alignment.bAlignVert=avCENTER;
				ptrFont=&font;
			}
			if(!bCash){
				ptrFont->DrawText(cellDrawer.m_hDC,rctTxt,ptrTxt);
			}else{
				rctClip.right-=offsetX;
				rctClip.bottom-=offsetY;
				DrawCashCell(cellDrawer,ptrTxt,ptrFont,bHead,rctClip);
				rctClip.right+=offsetX;
				rctClip.bottom+=offsetY;
			}
			if(!bFixedCell && (nFormatStyle=ptrStyle->GetFormatStyle())){
				//看看是否是Number值
				if(CLPlatform::IsNumeric(ptrTxt)){
					if(nFormatStyle==CELL_NUMBER_FORMAT_DOT){
						
					}else if(nFormatStyle==CELL_NUMBER_FORMAT_PERCENT){
						
					}else if(nFormatStyle==CELL_NUMBER_FORMAT_MONEY){
						
					}
				}
			}
		}else{
			if(bCash){
				rctClip.right-=offsetX;
				rctClip.bottom-=offsetY;
				DrawCashCell(cellDrawer,NULL,ptrFont,bHead,rctClip);
				rctClip.right+=offsetX;
				rctClip.bottom+=offsetY;
			}
		}
		//单元格存在
	}else{
		if(bCash){
			rctClip.right-=offsetX;
			rctClip.bottom-=offsetY;
			DrawCashCell(cellDrawer,NULL,ptrFont,bHead,rctClip);
			rctClip.right+=offsetX;
			rctClip.bottom+=offsetY;
		}
	}
	if(bFixedCell)return;
	//画单元格可能的边框
	LONG iStyle=ptrStyle->GetBorderStyle();
	LONG tLineStyle;
	COLORREF clrLine;
	rctClip.left-=nBorderLineWidth;
	rctClip.top-=nBorderLineWidth;
	rctClip.bottom-=nBorderLineWidth;
	rctClip.right-=nBorderLineWidth;
	LONG style;
	CELL cell(cellDraw.Row,m_ptrGrid->GetPrevCol(cellDraw));
	if(cell.Col>=0 && !(cell==cellDraw)){
		m_ptrGrid->GetMasterCell(cell);
		style=m_ptrTable->GetBorderStyle(cell.Row,cell.Col);
		tLineStyle=m_ptrTable->GetBorderLineStyle(cell);
		if(nStyle & GRID_NO_VERT_LINE)//{
			rctClip.right--;
			if((style & BORDER_STYLE_RIGHT) && !(iStyle & BORDER_STYLE_LEFT)){
				clrLine=m_ptrTable->GetBorderColor(cell);
				CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
					rctClip.top,rctClip.left,rctClip.bottom,clrLine,FALSE
					,nBorderLineWidth,(tLineStyle & BORDER_RIGHT_LINE_DOT));
			}
		//}
	}
	cell.Row=cellDraw.Row;
	cell.Col=m_ptrGrid->GetNextCol(cellDraw);
	if(!(cell==cellDraw)){
		m_ptrGrid->GetMasterCell(cell);
		style=m_ptrTable->GetBorderStyle(cell.Row,cell.Col);
		//if((nStyle & GRID_NO_VERT_LINE)){
		tLineStyle=m_ptrTable->GetBorderLineStyle(cell);
			if((style & BORDER_STYLE_LEFT) && !(iStyle & BORDER_STYLE_RIGHT)){
				clrLine=m_ptrTable->GetBorderColor(cell);
				CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.right,
					rctClip.top,rctClip.right,rctClip.bottom,clrLine,FALSE
					,nBorderLineWidth,(tLineStyle & BORDER_LEFT_LINE_DOT));
			}
		//}
	}
	cell.Col=cellDraw.Col;
	cell.Row=m_ptrGrid->GetPrevRow(cellDraw);
	if(cell.Row>=0 && !(cell==cellDraw)){
		RANGE range;
		//m_ptrGrid->GetCellRange(cell.Row,cell.Col,range);
		
	//if(cell.Row>=0 && !(cell==cellDraw)){
		cell.Col=cellDraw.Col;
		//cell.Row=range.m_posRow.m_begin;
		m_ptrGrid->GetMasterCell(cell);
		style=m_ptrTable->GetBorderStyle(cell.Row,cell.Col);
		tLineStyle=m_ptrTable->GetBorderLineStyle(cell);
		if((nStyle & GRID_NO_HORZ_LINE))//{
			rctClip.bottom--;
			if((style & BORDER_STYLE_BOTTOM) && !(iStyle & BORDER_STYLE_TOP)){
				clrLine=m_ptrTable->GetBorderColor(cell);
				CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
					rctClip.top,rctClip.right,rctClip.top,clrLine,TRUE
					,nBorderLineWidth,(tLineStyle & BORDER_BOTTOM_LINE_DOT));
			}
		//}

		if(bFillClr){
			cell.Row=cellDraw.Row-1;
			cell.Col=cellDraw.Col-1;
			if(cell.Row>=0 && cell.Col>=0 && !(cell==cellDraw)){
				m_ptrGrid->GetCellRange(cell.Row,cell.Col,range);
				if(range.m_posCol.m_end==cellDraw.Col-1 && range.m_posRow.m_end==cellDraw.Row-1){
					cell.Row=range.m_posRow.m_begin;
					cell.Col=range.m_posCol.m_begin;
					style=m_ptrTable->GetBorderStyle(cell.Row,cell.Col);
					tLineStyle=m_ptrTable->GetBorderLineStyle(cell);
					if((style & BORDER_STYLE_BOTTOM) && !(iStyle & BORDER_STYLE_TOP)){
						clrLine=m_ptrTable->GetBorderColor(cell);
						CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
						rctClip.top,rctClip.left,rctClip.top,clrLine,TRUE
						,nBorderLineWidth,(tLineStyle & BORDER_BOTTOM_LINE_DOT));
					}else if((style & BORDER_STYLE_RIGHT) && !(iStyle & BORDER_STYLE_LEFT)){
						clrLine=m_ptrTable->GetBorderColor(cell);
						CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
						rctClip.top,rctClip.left,rctClip.top,clrLine,FALSE
						,nBorderLineWidth,(tLineStyle & BORDER_RIGHT_LINE_DOT));
					}
				}
			}
		}
	}
	cell.Col=cellDraw.Col;
	cell.Row=m_ptrGrid->GetNextRow(cellDraw);
	if(!(cell==cellDraw)){
		m_ptrGrid->GetMasterCell(cell);
		style=m_ptrTable->GetBorderStyle(cell.Row,cell.Col);
		tLineStyle=m_ptrTable->GetBorderLineStyle(cell);
		//if(!(nStyle & GRID_NO_VERT_LINE))//{
			if((style & BORDER_STYLE_TOP) && !(iStyle & BORDER_STYLE_BOTTOM)){
				clrLine=m_ptrTable->GetBorderColor(cell);
				CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
					rctClip.bottom,rctClip.right,rctClip.bottom,clrLine,TRUE
					,nBorderLineWidth,(tLineStyle & BORDER_TOP_LINE_DOT));
			}
		//}
	}
	//绘制批注标志
	if((!cellDrawer.bIsPrint) && m_ptrTable->GetCellMemo(cellDraw.Row,cellDraw.Col)){
		//画三角
		CLDrawer::DrawMemoFlag(cellDrawer.m_hDC,&rctClip,RGB(255,0,0));
	}
	if(iStyle==DEFAULT_BORDER_STYLE)return;
	//当前单元
	if(iStyle & BORDER_STYLE_TOP){
		//有上边边线
		CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
			rctClip.top,rctClip.right,rctClip.top,clrBorder,TRUE,nBorderLineWidth
			,(nBorderLineDot & BORDER_TOP_LINE_DOT));
	}
	if(iStyle & BORDER_STYLE_LEFT){
		//有左边边线
		CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
			rctClip.top,rctClip.left,rctClip.bottom,clrBorder,FALSE,nBorderLineWidth
			,(nBorderLineDot & BORDER_LEFT_LINE_DOT));
	}
	if(iStyle & BORDER_STYLE_RIGHT){
		//有右边边线
		CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.right,
			rctClip.top,rctClip.right,rctClip.bottom,clrBorder,FALSE,nBorderLineWidth
			,(nBorderLineDot & BORDER_RIGHT_LINE_DOT));
	}
	if(iStyle & BORDER_STYLE_BOTTOM){
		//有下边边线
		CLDrawer::DrawerALine(cellDrawer.m_hDC,rctClip.left,
			rctClip.bottom,rctClip.right,rctClip.bottom,clrBorder,TRUE,nBorderLineWidth
			,(nBorderLineDot & BORDER_BOTTOM_LINE_DOT));
	}
}
void CLDrawerSheet::DrawFixedCells(LPHDC pDC,const RECT& rctAll)
{
	if(!m_ptrTable)return;
	if(pDC->bIsPrint && !pDC->bPrintFixed)return;
	LONG nRows=m_ptrTable->GetFixedRows();
	LONG nCols=m_ptrTable->GetFixedCols();
	LONG totWid,totHeight,nctwid=0,nctHei=0,valLenV,valLenH;
	POINT ptFreeze,ptStart,ptXY;
	RECT rctClip,rctClient;
	CELL beginCell;
	m_ptrTable->GetBeginCell(beginCell);
	m_ptrTable->GetCellBeginXY(ptXY);
	if(!pDC->bIsPrint){
		m_ptrTable->GetClientRect(rctClient);
		m_ptrTable->GetBeginTablePos(ptStart);
		m_ptrTable->GetBeginFreezePos(ptFreeze);
	}else{
		m_ptrTable->GetClientRect(rctAll,rctClient);
		m_ptrTable->GetBeginTablePos(rctAll,ptStart);
		m_ptrTable->GetBeginFreezePos(rctAll,ptFreeze);
	}
	rctClip=rctClient;
	//当前页面总宽/高
	totHeight=rctClient.bottom-ptStart.y;
	rctClip.top=ptStart.y;
	rctClip.bottom=ptFreeze.y;
	totWid=rctClip.right-rctClip.left+ptXY.x;
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	CELLITEMDRAWER	drawerCell;
	drawerCell.m_hDC=pDC->hDC;
	drawerCell.bIsPrint=pDC->bIsPrint;
	drawerCell.m_lpRect=&rctClip;
	//画固定行
	{
		//if(!pDC->bIsPrint)
		CLClipDC clip(pDC->hDC,rctClip);
		rctClip.left-=ptXY.x;
		for(LONG irow=0;irow<nRows;irow++){
			ptrRow=m_ptrTable->GetARow(irow);
			valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			nctHei+=valLenV;
			nctwid=0;
			rctClip.bottom=rctClip.top+valLenV;
			drawerCell.m_cell.Row=irow;
			for(LONG icol=beginCell.Col;icol<m_ptrTable->GetCols();icol++){
				ptrCol=m_ptrTable->GetACol(icol);
				valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				nctwid+=valLenH;
				rctClip.right=rctClip.left+valLenH;
				drawerCell.m_cell.Col=icol;
				////////////
				DrawACell(drawerCell,rctAll);
				///////////
				if(nctwid*(pDC->bIsPrint?m_scaleX:1)>=totWid){
					rctClip.left=rctClient.left-ptXY.x;
					break;
				}
				rctClip.left+=valLenH;
			}
			if(nctHei>=totHeight){
				break;
			}
			rctClip.top+=valLenV;
		}
	}
	//画固定列
	rctClip.left=ptStart.x;
	rctClip.top=rctClient.top;
	rctClip.right=ptFreeze.x;
	rctClip.bottom=rctClient.bottom;
	totHeight=rctClient.bottom-rctClient.top+ptXY.y;
	totWid=rctClip.right-rctClip.left;
	nctwid=0;
	nctHei=0;
	{
		//if(!pDC->bIsPrint)
		CLClipDC clip(pDC->hDC,rctClip);
		rctClip.top-=ptXY.y;
		
		for(LONG icol=0;icol<nCols;icol++){
			ptrCol=m_ptrTable->GetACol(icol);
			valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			nctwid+=valLenH;
			nctHei=0;
			rctClip.right=rctClip.left+valLenH;
			drawerCell.m_cell.Col=icol;
			for(LONG irow=beginCell.Row;irow<m_ptrTable->GetRows();irow++){
				ptrRow=m_ptrTable->GetARow(irow);
				valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				nctHei+=valLenV;
				rctClip.bottom=rctClip.top+valLenV;
				drawerCell.m_cell.Row=irow;
				////////////
				DrawACell(drawerCell,rctAll);
				///////////
				if(nctHei*(pDC->bIsPrint?m_scaleY:1)>=totHeight){
					rctClip.top=ptFreeze.y-ptXY.y;
					break;
				}
				rctClip.top+=valLenV;
			}
			if(nctwid>=totWid){
				break;
			}
			rctClip.left+=valLenH;
		}
	}
	//画固定CELL
	rctClip.left=ptStart.x;
	rctClip.right=rctClient.left;
	rctClip.top=ptStart.y;
	rctClip.bottom=rctClient.top;
	totHeight=rctClip.bottom-rctClip.top;
	totWid=rctClip.right-rctClip.left;
	nctwid=0;
	nctHei=0;
	{
		//if(!pDC->bIsPrint)
		CLClipDC clip(pDC->hDC,rctClip);
		for(LONG icol=0;icol<nCols+m_ptrTable->GetFreezeCols();icol++){
			ptrCol=m_ptrTable->GetACol(icol);
			valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			nctwid+=valLenH;
			nctHei=0;
			rctClip.right=rctClip.left+valLenH;
			drawerCell.m_cell.Col=icol;
			for(LONG irow=0;irow<nRows+m_ptrTable->GetFreezeRows();irow++){
				ptrRow=m_ptrTable->GetARow(irow);
				valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				nctHei+=valLenV;
				rctClip.bottom=rctClip.top+valLenV;
				drawerCell.m_cell.Row=irow;
				////////////
				if(m_ptrTable->isFixedCell(drawerCell.m_cell))
					DrawACell(drawerCell,rctAll);
				///////////
				if(nctHei>=totHeight){
					rctClip.top=ptStart.y;
					break;
				}
				rctClip.top+=valLenV;
			}
			if(nctwid>=totWid){
				break;
			}
			rctClip.left+=valLenH;
		}
	}
}

void CLDrawerSheet::DrawFreezeCells(LPHDC pDC,const RECT& rctAll)
{
	if(!m_ptrTable)return;
	LONG nRows=m_ptrTable->GetFixedRows();
	LONG nCols=m_ptrTable->GetFixedCols();
	LONG totWid,totHeight,nctwid=0,nctHei=0,valLenV,valLenH;
	POINT ptFreeze,ptXY;
	RECT rctClip,rctClient;
	if(!pDC->bIsPrint)
		m_ptrTable->GetClientRect(rctClient);
	else
		m_ptrTable->GetClientRect(rctAll,rctClient);

	CELL beginCell;
	m_ptrTable->GetBeginCell(beginCell);
	rctClip=rctClient;
	//当前页面总宽/高
	m_ptrTable->GetCellBeginXY(ptXY);
	if(!pDC->bIsPrint)
		m_ptrTable->GetBeginFreezePos(ptFreeze);
	else
		m_ptrTable->GetBeginFreezePos(rctAll,ptFreeze);

	totHeight=rctClient.top-ptFreeze.y+ptXY.y;
	totWid=rctClient.right-rctClient.left+ptXY.x;
	rctClip.bottom=rctClip.top;
	rctClip.top=ptFreeze.y;
	
	CLRowItem* ptrRow;
	CLColItem* ptrCol;
	CELLITEMDRAWER	drawerCell;
	drawerCell.m_hDC=pDC->hDC;
	drawerCell.bIsPrint=pDC->bIsPrint;
	drawerCell.m_lpRect=&rctClip;
	CLClipDC clip;
	//画冻结行
	{
		if(!pDC->bIsPrint)
			clip.SetClip(pDC->hDC,rctClip);
		rctClip.left-=ptXY.x;
		for(LONG irow=0;irow<m_ptrTable->GetFreezeRows();irow++){
			ptrRow=m_ptrTable->GetARow(irow+nRows);
			valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			nctHei+=valLenV;
			nctwid=0;
			rctClip.left=rctClient.left-ptXY.x;
			rctClip.bottom=rctClip.top+valLenV;
			drawerCell.m_cell.Row=irow+nRows;
			for(LONG icol=beginCell.Col;icol<m_ptrTable->GetCols();icol++){
				ptrCol=m_ptrTable->GetACol(icol);
				valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				nctwid+=valLenH;
				rctClip.right=rctClip.left+valLenH;
				drawerCell.m_cell.Col=icol;
				////////////
				DrawACell(drawerCell,rctAll);
				///////////
				if(nctwid*(pDC->bIsPrint?m_scaleX:1)>=totWid){
					//rctClip.left=rctClient.left-ptXY.x;
					break;
				}
				rctClip.left+=valLenH;
			}
			if(nctHei>=totHeight){
				break;
			}
			rctClip.top+=valLenV;
		}
	}
	//画冻结列
	rctClip.left=ptFreeze.x;
	rctClip.bottom=rctClient.bottom;
	rctClip.right=rctClient.left;
	rctClip.top=rctClient.top;
	totHeight=rctClient.bottom-rctClient.top+ptXY.y;
	totWid=rctClient.left-ptFreeze.x;
	nctwid=0;
	nctHei=0;
	{
		if(!pDC->bIsPrint)
			clip.SetClip(pDC->hDC,rctClip);
		rctClip.top-=ptXY.y;
		for(LONG icol=0;icol<m_ptrTable->GetFreezeCols();icol++){
			ptrCol=m_ptrTable->GetACol(icol+nCols);
			valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			nctwid+=valLenH;
			nctHei=0;
			rctClip.top=rctClient.top-ptXY.y;
			rctClip.right=rctClip.left+valLenH;
			drawerCell.m_cell.Col=icol+nCols;
			for(LONG irow=beginCell.Row;irow<m_ptrTable->GetRows();irow++){
				ptrRow=m_ptrTable->GetARow(irow);
				valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				nctHei+=valLenV;
				rctClip.bottom=rctClip.top+valLenV;
				rctClip.right=rctClip.left+valLenH;
				
				drawerCell.m_cell.Row=irow;
				////////////
				DrawACell(drawerCell,rctAll);
				///////////
				if(nctHei*(pDC->bIsPrint?m_scaleY:1)>=totHeight){
					break;
				}
				rctClip.top+=valLenV;
			}
			if(nctwid>=totWid){
				break;
			}
			rctClip.left+=valLenH;
		}
	}
	//画固定CELL
	rctClip.left=ptFreeze.x;
	rctClip.right=rctClient.left;
	rctClip.top=ptFreeze.y;
	rctClip.bottom=rctClient.top;
	totHeight=rctClip.bottom-rctClip.top;
	totWid=rctClip.right-rctClip.left;
	nctwid=0;
	nctHei=0;
	{
		if(!pDC->bIsPrint)
			clip.SetClip(pDC->hDC,rctClip);
		for(LONG icol=0;icol<m_ptrTable->GetFreezeCols();icol++){
			ptrCol=m_ptrTable->GetACol(icol+nCols);
			valLenH=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			nctwid+=valLenH;
			nctHei=0;
			rctClip.right=rctClip.left+valLenH;
			drawerCell.m_cell.Col=icol+nCols;
			for(LONG irow=0;irow<m_ptrTable->GetFreezeRows();irow++){
				ptrRow=m_ptrTable->GetARow(irow+nRows);
				valLenV=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				nctHei+=valLenV;
				rctClip.bottom=rctClip.top+valLenV;
				drawerCell.m_cell.Row=irow+nRows;
				////////////
				DrawACell(drawerCell,rctAll);
				///////////
				if(nctHei>=totHeight){
					rctClip.top=ptFreeze.y;
					break;
				}
				rctClip.top+=valLenV;
			}
			if(nctwid>=totWid){
				break;
			}
			rctClip.left+=valLenH;
		}
	}
}
void CLDrawerSheet::DrawFreeeLine(LPHDC pDC)
{
	/*计算冻结单元横向线位置*/
	if(!m_ptrTable)return;
	RECT rct;
	POINT ptFreeze;
	m_ptrTable->GetClientRect(rct,TRUE);
	m_ptrTable->GetBeginFreezePos(ptFreeze);
	RECT rctClient=rct;

	CLDrawer::FillSolidRect(pDC->hDC,ptFreeze.x,
					rctClient.top-1,rct.right-ptFreeze.x,1,COLOR_FREEZE_LINE);
	/*计算冻结单元纵向线位置*/
	CLDrawer::FillSolidRect(pDC->hDC,rctClient.left-1,
					ptFreeze.y,1,rct.bottom-ptFreeze.y,COLOR_FREEZE_LINE);
}
void CLDrawerSheet::DrawGridLine(LPHDC pDC,const RECT& rct,
								 LONG begin,LONG end,LONG beginPos,LONG offset,BOOL bVert)
{
	RECT rctClient=rct;
	BOOL bFirst=TRUE;
	//if(!pDC->bIsPrint)
	CLClipDC clip(pDC->hDC,rctClient);
	if(bVert){
		rctClient.top-=offset;
		CLColItem* ptrCol;
		for(LONG icol=begin;icol<end;icol++){
			if(beginPos>=rctClient.left || (bFirst && pDC->bIsPrint)){
				bFirst=FALSE;
				CLDrawer::FillSolidRect(pDC->hDC,beginPos,
					rctClient.top-1,1,rctClient.bottom-rctClient.top+1,m_ptrGrid->GetGridLineColor());
			}
			ptrCol=m_ptrTable->GetACol(icol);
			beginPos+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
			
			if(beginPos*(pDC->bIsPrint?m_scaleX:1)>rctClient.right+1 || icol==end-1){
				CLDrawer::FillSolidRect(pDC->hDC,beginPos,
					rctClient.top,1,rctClient.bottom-rctClient.top+1,m_ptrGrid->GetGridLineColor());
				break;
			}
		}
	}else{
		rctClient.left-=offset;
		CLRowItem* ptrRow;
		for(LONG irow=begin;irow<end;irow++){
			if(beginPos>=rctClient.top || (bFirst && pDC->bIsPrint)){
				bFirst=FALSE;
				CLDrawer::FillSolidRect(pDC->hDC,rctClient.left-1,
					beginPos,rctClient.right-rctClient.left+1,1,m_ptrGrid->GetGridLineColor());
			}
			ptrRow=m_ptrTable->GetARow(irow);
			beginPos+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
			if(beginPos*(pDC->bIsPrint?m_scaleY:1)>rctClient.bottom+1 || irow==end-1){
				CLDrawer::FillSolidRect(pDC->hDC,rctClient.left,
					beginPos,rctClient.right-rctClient.left+1,1,m_ptrGrid->GetGridLineColor());
				break;
			}
		}
	}
}
LONG CLDrawerSheet::GetPageCount(const SIZE& pgSize)
{
	if(m_ptrTable){
		LPSCROLLINFOEXT lpinfo=m_ptrTable->GetScrollInfo();
		LONG xct=(LONG)(lpinfo->m_nMaxValue/pgSize.cx);
		if(lpinfo->m_nMaxValue%pgSize.cx)
			xct++;
		lpinfo=m_ptrTable->GetScrollInfo(FALSE);
		LONG yct=(LONG)(lpinfo->m_nMaxValue/pgSize.cy);
		if(lpinfo->m_nMaxValue%pgSize.cy)
			yct++;
		return (LONG)(xct*yct);
	}
	return 1;
}
void CLDrawerSheet::OnPrint(LPHDC pDC,const RECT& rct)
{
	OnDraw(pDC,rct);
}
LPTSTR CLDrawerSheet::GetSheetName(void)
{
	if(m_ptrSheet){
		return m_ptrSheet->GetSheetName();
	}
	return NULL;
}

//
void CLDrawerSheet::GetClipRect(RECT &rct)
{
	if(m_ptrSheet){
		RECT rctT;
		POINT ptStart;
		LONG border=4;
		rct.left-=border;
		rct.top-=border;
		rct.right+=border;
		rct.bottom+=border;
		m_ptrTable->GetBeginFreezePos(ptStart);
		m_ptrTable->GetClientRect(rctT);
		rctT.left=ptStart.x;
		rctT.top=ptStart.y;
		
		if(rct.left<rctT.left)
			rct.left=rctT.left;
		if(rct.top<rctT.top)
			rct.top=rctT.top;
		if(rct.right>rctT.right)
			rct.right=rctT.right;
		if(rct.bottom>rctT.bottom)
			rct.bottom=rctT.bottom;
	}
}
//解决直接写屏时闪烁问题
void CLDrawerSheet::DrawSelectCELL(LPHDC pDC,const RANGE& range,const CELL& cell)
{
	if(m_ptrSheet && m_ptrGrid->isRangeMode()){
		RANGE range;
		CELL cell;
		m_ptrTable->GetCurrentRange(range);
	}
}
//画范围拖动效果
void CLDrawerSheet::DrawDragRange(LPHDC pDC,const RANGE& rangeOld,const RANGE& range)
{
	if(!m_ptrSheet)return;
	BOOL bNewDrawer=FALSE;
	HDCH hDC;
	RECT rctAll,rctClip,rctVisible;
	if(!pDC){
		m_ptrTable->GetDC(hDC);
		pDC=&hDC;
		bNewDrawer=TRUE;
	}
	if(!rangeOld.isEmpty()){
		m_ptrTable->GetRangeRect(rangeOld,rctClip,rctVisible,rctAll,4);
		//if(!pDC->bIsPrint)
		CLClipDC clipDC(pDC->hDC,rctVisible);
		//裁剪绘图区域
		//清除前一次区域
		rctClip.left-=2;
		rctClip.top-=2;
		rctClip.right+=1;
		rctClip.bottom+=1;
		CLDrawer::DrawDitherBorder(pDC->hDC,&rctClip,3,3);
	}
	m_ptrTable->GetRangeRect(range,rctClip,rctVisible,rctAll,4);
	//if(!pDC->bIsPrint)
	CLClipDC clipDCT(pDC->hDC,rctVisible);
	rctClip.left-=2;
	rctClip.top-=2;
	rctClip.right+=1;
	rctClip.bottom+=1;
	CLDrawer::DrawDitherBorder(pDC->hDC,&rctClip,3,3);
	if(bNewDrawer){
		m_ptrTable->ReleaseDC(hDC);
	}
}
//画当前选中区域(只有在区域模式下才画),必须要在画完固定单元后进行
void CLDrawerSheet::DrawSelectRange(LPHDC pDC,BOOL bRestoryOld,BOOL bIsFocusCell)
{
	if(m_ptrSheet && m_ptrGrid->isRangeMode()){
		RECT rctCur;
		RANGE rangeCur,rangeOld,rangeCellCur;
		m_ptrTable->GetCurrentRange(rangeCur);
		LONG fixedRows=m_ptrTable->GetFixedRows();
		LONG fixedCols=m_ptrTable->GetFixedCols();
		/*
		BOOL bSetCurrentRgn=FALSE;
		if(rangeCur.m_posRow.m_begin<fixedRows){
			rangeCur.m_posRow.m_begin=fixedRows;
			bSetCurrentRgn=TRUE;
		}
		if(rangeCur.m_posRow.m_end<fixedRows){
			rangeCur.m_posRow.m_end=fixedRows;
			bSetCurrentRgn=TRUE;
		}
		if(rangeCur.m_posCol.m_begin<fixedCols){
			rangeCur.m_posCol.m_begin=fixedCols;
			bSetCurrentRgn=TRUE;
		}
		if(rangeCur.m_posCol.m_end<fixedCols){
			rangeCur.m_posCol.m_end=fixedCols;
			bSetCurrentRgn=TRUE;
		}
		if(bSetCurrentRgn)
			m_ptrTable->SetCurrentRange(rangeCur);
		*/
		((CLSheet*)m_ptrSheet)->GetOldRange(rangeOld);

		if(rangeOld.m_posRow.m_begin<fixedRows){
			rangeOld.m_posRow.m_begin=fixedRows;
		}
		if(rangeOld.m_posRow.m_end<fixedRows){
			rangeOld.m_posRow.m_end=fixedRows;
		}
		if(rangeOld.m_posCol.m_begin<fixedCols){
			rangeOld.m_posCol.m_begin=fixedCols;
		}
		if(rangeOld.m_posCol.m_end<fixedCols){
			rangeOld.m_posCol.m_end=fixedCols;
		}
		

		HDCH hDC;
		BOOL bDraw=FALSE,bNULL=(!pDC);
		CELL cellCur,cellOld;
		
		if(!rangeCur.isEmpty()){
			m_ptrTable->GetPrevFocusCell(cellOld);
			m_ptrTable->GetCurrentCell(cellCur);
			m_ptrGrid->GetCellRange(cellCur.Row,cellCur.Col,rangeCellCur);
			
			RECT rct,rctClip,rctVisible;
			
			if(!pDC){
				m_ptrTable->GetDC(hDC);
				pDC=&hDC;
			}
			HRGN hrgn=NULL;
			CELL cellBegin;
			LONG nRowsF=m_ptrTable->GetFixedRows()+m_ptrTable->GetFreezeRows();
			LONG nColsF=m_ptrTable->GetFixedCols()+m_ptrTable->GetFreezeCols();
			m_ptrTable->GetBeginCell(cellBegin);
			if(!rangeOld.isEmpty() && !rangeOld.isSingleCellRange() && !(rangeOld==rangeCur) && bRestoryOld){
				if(m_ptrTable->GetRangeRect(rangeOld,rctClip,rctVisible,rct,4)){
					if(rangeOld.m_posRow.m_begin<cellBegin.Row 
						&& rangeOld.m_posRow.m_begin>=nRowsF)
						rctVisible.top++;
					if(rangeOld.m_posCol.m_begin<cellBegin.Col 
						&& rangeOld.m_posCol.m_begin>=nColsF)
						rctVisible.left++;
					rctClip.left--;
					rctClip.top--;
					rctClip.right--;
					rctClip.bottom--;
					DrawFocusCell(pDC,&cellOld,&cellOld);
					//if(!pDC->bIsPrint)
					CLClipDC hDC(pDC->hDC,rctVisible);

					CLDrawer::DrawRangeBorder(pDC->hDC,&rctClip,COLOR_FOCUSE_BORDER);
					ModifyFocusCellRect(rangeOld,cellOld,rctCur);
					hrgn=CLDrawer::CreateRectRgn(rctCur);
					CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
					CLDrawer::DeleteRgn(hrgn);
					
					rctClip.left+=3;
					rctClip.top+=3;
					rctClip.right-=2;
					rctClip.bottom-=2;
					if(rangeOld.m_posRow.m_begin<cellBegin.Row 
						&& rangeOld.m_posRow.m_begin>=nRowsF){
						rctClip.top-=1;
						rctVisible.top--;
					}
					if(rangeOld.m_posCol.m_begin<cellBegin.Col 
						&& rangeOld.m_posCol.m_begin>=nColsF){
						rctVisible.left--;
						rctClip.left-=1;
					}
					//if(!pDC->bIsPrint)
					CLClipDC hDCT(pDC->hDC,rctVisible);
					hrgn=CLDrawer::CreateRectRgn(rctClip);
					CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
					CLDrawer::DeleteRgn(hrgn);
				}
			}
			if(!bIsFocusCell && !rangeCur.isSingleCellRange() && m_ptrTable->GetRangeRect(rangeCur,rctClip,rctVisible,rct,4)){
				bDraw=TRUE;
				if(rangeOld.m_posRow.m_begin<cellBegin.Row 
					&& rangeOld.m_posRow.m_begin>=nRowsF)
					rctVisible.top++;
				if(rangeOld.m_posCol.m_begin<cellBegin.Col 
					&& rangeOld.m_posCol.m_begin>=nColsF)
					rctVisible.left++;
				rctClip.left--;
				rctClip.top--;
				rctClip.right--;
				rctClip.bottom--;
				DrawFocusCell(pDC);
				//if(!pDC->bIsPrint)
				CLClipDC hDC(pDC->hDC,rctVisible);
				
				CLDrawer::DrawRangeBorder(pDC->hDC,&rctClip,COLOR_FOCUSE_BORDER);
				ModifyFocusCellRect(rangeCur,cellCur,rctCur);
				hrgn=CLDrawer::CreateRectRgn(rctCur);
				CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
				CLDrawer::DeleteRgn(hrgn);
				
				rctClip.left+=3;
				rctClip.top+=3;
				rctClip.right-=2;
				rctClip.bottom-=2;
				if(rangeOld.m_posRow.m_begin<cellBegin.Row 
					&& rangeOld.m_posRow.m_begin>=nRowsF){
					rctVisible.top--;
					rctClip.top-=1;
				}
				if(rangeOld.m_posCol.m_begin<cellBegin.Col 
					&& rangeOld.m_posCol.m_begin>=nColsF){
					rctVisible.left--;
					rctClip.left-=1;
				}
				//if(!pDC->bIsPrint)
				CLClipDC hDCT(pDC->hDC,rctVisible);
				hrgn=CLDrawer::CreateRectRgn(rctClip);
				CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
				CLDrawer::DeleteRgn(hrgn);
			}
			
		}
		//if(bDraw){
			DrawFixedCells(pDC,rctCur);
		//}
		if(bNULL)
			m_ptrTable->ReleaseDC(hDC);
	}
}
/*
void CLDrawerSheet::DrawSelectRange(LPHDC pDC,BOOL bRestoryOld,BOOL bIsFocusCell)
{
	if(m_ptrSheet && m_ptrGrid->isRangeMode()){
		RECT rctCur;
		RANGE rangeCur,rangeOld,rangeCellCur;
		m_ptrTable->GetCurrentRange(rangeCur);
		((CLSheet*)m_ptrSheet)->GetOldRange(rangeOld);
		HDCH hDC;
		BOOL bDraw=FALSE;
		CELL cellCur,cellOld;
		
		if(!rangeCur.isEmpty()){
			m_ptrTable->GetPrevFocusCell(cellOld);
			m_ptrTable->GetCurrentCell(cellCur);
			m_ptrGrid->GetCellRange(cellCur.Row,cellCur.Col,rangeCellCur);
			
			RECT rct,rctClip,rctVisible;
			if(!pDC){
				m_ptrTable->GetDC(hDC);
				pDC=&hDC;
			}
			HRGN hrgn=NULL;
			if(!rangeOld.isEmpty() && !rangeOld.isSingleCellRange() && !(rangeOld==rangeCur) && bRestoryOld){
				if(m_ptrTable->GetRangeRect(rangeOld,rctClip,rctVisible,rct,0)){
					
					rctVisible.left--;
					rctVisible.top--;
					rctVisible.right--;
					rctVisible.bottom--;
					
					//CLClipDC hDC(pDC->hDC,rctVisible);
					CLDrawer::DrawRangeBorder(pDC->hDC,&rctVisible,COLOR_FOCUSE_BORDER);
					DrawFocusCell(pDC,&cellOld,&cellOld);
					
					ModifyFocusCellRect(rangeOld,cellOld,rctCur);
					hrgn=CLDrawer::CreateRectRgn(rctCur);
					CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
					CLDrawer::DeleteRgn(hrgn);
					
					rctVisible.left+=3;
					rctVisible.top+=3;
					rctVisible.right-=2;
					rctVisible.bottom-=2;
					
					hrgn=CLDrawer::CreateRectRgn(rctVisible);
					CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
					CLDrawer::DeleteRgn(hrgn);
				}
			}
			if(!bIsFocusCell && !rangeCur.isSingleCellRange() && m_ptrTable->GetRangeRect(rangeCur,rctClip,rctVisible,rct,0)){
				bDraw=TRUE;
				rctVisible.left--;
				rctVisible.top--;
				rctVisible.right--;
				rctVisible.bottom--;
				//CLClipDC hDC(pDC->hDC,rctVisible);
				CLDrawer::DrawRangeBorder(pDC->hDC,&rctVisible,COLOR_FOCUSE_BORDER);
				DrawFocusCell(pDC);

				ModifyFocusCellRect(rangeCur,cellCur,rctCur);
				hrgn=CLDrawer::CreateRectRgn(rctCur);
				CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
				CLDrawer::DeleteRgn(hrgn);

				rctVisible.left+=3;
				rctVisible.top+=3;
				rctVisible.right-=2;
				rctVisible.bottom-=2;
				hrgn=CLDrawer::CreateRectRgn(rctVisible);
				CLDrawer::SetFocus(pDC->hDC,hrgn,TRUE,COLOR_RANGE_SEL,FALSE,TRUE);
				CLDrawer::DeleteRgn(hrgn);
			}
			
		}
		//if(bDraw){
			DrawFixedCells(pDC);
		//}
	}
}
*/
void CLDrawerSheet::ModifyFocusCellRect(const RANGE &range, 
										const CELL &cell, RECT& rctClip)
{
	if(!m_ptrSheet)return;
	RECT rctDec,rctVisible;
	RANGE rgn;
	LONG nDef=2;
	CELL cellT;
	m_ptrGrid->GetCellRange(cell.Row,cell.Col,rgn);
	
	CLPlatform::ClearRect(rctDec);
	m_ptrGrid->GetCellRect(cell.Row,cell.Col,rctClip,rctVisible);
	rctClip.right--;
	rctClip.bottom--;
	if(rgn.m_posRow.m_begin==range.m_posRow.m_begin){
		if(rgn.m_posCol.m_begin==range.m_posCol.m_begin){
			//左上角
			rctDec.left+=nDef;
			rctDec.top+=nDef;
			if(rgn.m_posCol.m_end==range.m_posCol.m_end){
				rctDec.right+=nDef;
			}
			if(rgn.m_posRow.m_end==range.m_posRow.m_end){
				rctDec.bottom+=nDef;
			}
		}else if(rgn.m_posCol.m_end==range.m_posCol.m_end){
			//右上角
			rctDec.right+=nDef;
			rctDec.top+=nDef;
			if(rgn.m_posRow.m_end==range.m_posRow.m_end){
				rctDec.bottom+=nDef;
			}
		}else{
			//上边
			rctDec.top+=nDef;
			if(rgn.m_posRow.m_end==range.m_posRow.m_end){
				rctDec.bottom+=nDef;
			}
		}
	}else if(rgn.m_posRow.m_end==range.m_posRow.m_end){
		if(rgn.m_posCol.m_begin==range.m_posCol.m_begin){
			//左下角
			rctDec.left+=nDef;
			rctDec.bottom+=nDef;
			if(rgn.m_posCol.m_end==range.m_posCol.m_end){
				rctDec.right+=nDef;
			}
		}else if(rgn.m_posCol.m_end==range.m_posCol.m_end){
			//右下角
			rctDec.right+=nDef;
			rctDec.bottom+=nDef;
		}else{
			//下边
			rctDec.bottom+=nDef;
		}
	}else if(rgn.m_posCol.m_begin==range.m_posCol.m_begin){
		//左边
		rctDec.left+=nDef;
		if(rgn.m_posCol.m_end==range.m_posCol.m_end){
			rctDec.right+=nDef;
		}
	}else if(rgn.m_posCol.m_end==range.m_posCol.m_end){
		//右边
		rctDec.right+=nDef;
	}
	rctClip.left+=rctDec.left;
	rctClip.top+=rctDec.top;
	rctClip.right-=rctDec.right;
	rctClip.bottom-=rctDec.bottom;
}
//画金额单元
void CLDrawerSheet::DrawCashCell(CELLITEMDRAWER &cellDrawer,char* pTxt
								 ,CLFont* pFont,BOOL bHeader,const RECT &rect)
{
	ASSERT(pFont!=NULL);
	RECT rct=rect,rctT;
	LPTSTR ptrStr=pTxt;
	rctT=rct;
	HFONT hFont=CreateFontIndirect(&pFont->m_lf);
	HFONT hOldFont=(HFONT)SelectObject(cellDrawer.m_hDC,hFont);
	HPEN hPen=CLDrawer::CreatePen(PS_SOLID,1,RGB(255,0,0));
	HBRUSH hBrush=CLDrawer::HBrushDitherCreate(RGB(250,100,100),RGB(255,200,200));
	HPEN hOldPen=(HPEN)SelectObject(cellDrawer.m_hDC,hPen);
	int ioldmod=SetBkMode(cellDrawer.m_hDC,TRANSPARENT);
	//间隔宽度
	LONG nSp=11;
	LONG nPosX=rct.right-nSp;
	POINT pt;
	LONG nPos=0;
	
	char *ptrT=NULL,*ptrText=(bHeader?CASHNAME:ptrStr);
	CLDrawer::SetTextColor(cellDrawer.m_hDC,pFont->m_clr);
	if(ptrText!=NULL && strlen(ptrText) && !bHeader){
		DOUBLE dblT;
		ptrT=new char[strlen(ptrText)+5];
		dblT=atof(ptrText)*100;
		sprintf(ptrT,"%.0f\0",(dblT<0?(-dblT):dblT));
		nPos=strlen(ptrT)-1;
		if(dblT<0){
			CLDrawer::SetTextColor(cellDrawer.m_hDC,RGB(255,0,0));
		}else{
			CLDrawer::SetTextColor(cellDrawer.m_hDC,pFont->m_clr);
		}
	}else{
		if(ptrText!=NULL && strlen(ptrText))
			nPos=strlen(ptrText)-2;
		else
			nPos=-1;
	}
	LONG i=0;
	while(nPosX>=rct.left){
		if(nPos>=0){
			rctT.left=nPosX+1;
			rctT.right=rctT.left+nSp;
			CLDrawer::DrawText(cellDrawer.m_hDC
				,(char*)((bHeader?ptrText:ptrT)+nPos),(bHeader?2:1),&rctT,
				DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			nPos-=(bHeader?2:1);
		}
		if(nPosX>=rct.left+2){
			if(i==1){
				CLDrawer::MoveToEx(cellDrawer.m_hDC,nPosX,rct.top,&pt);
				CLDrawer::LineTo(cellDrawer.m_hDC,nPosX,rct.bottom);	
			}else if((i-1)%3==0){
				rctT.left=nPosX;
				rctT.right=rctT.left+1;
				CLDrawer::FillARect(cellDrawer.m_hDC,&rctT,hBrush);
			}else{
				rctT.left=nPosX;
				rctT.right=rctT.left;
				CLDrawer::FillARect(cellDrawer.m_hDC,&rctT,hBrush);
			}
		}
		i++;
		nPosX-=nSp;
	}
	if(ptrT){
		delete[] ptrT;
		ptrT=NULL;
	}
	DeleteObject(hBrush);
	SelectObject(cellDrawer.m_hDC,hOldFont);
	SetBkMode(cellDrawer.m_hDC,ioldmod);
	SelectObject(cellDrawer.m_hDC,hOldPen);
	DeleteObject(hPen);
	DeleteObject(hFont);
}
void CLDrawerSheet::ShowToolTip(LPHDC pDC,LPTSTR ptrTip,BOOL bShow)
{
	/*显示批注*/
	BOOL bT=m_ttip.IsVisible();
	if( bT^bShow ){
		m_ttip.SetMessage(ptrTip);
		RECT rct;
		m_ttip.IsVisible(bShow);
		m_ttip.OnDraw(pDC,rct);
		if(!bShow && m_ptrSheet)
			((CLTable*)m_ptrSheet->GetGrid()->GetTable())->ReDraw();
	}
}