//////////////////////////////////////////////////////////////////////
//@模块		 ：工作表对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-07
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LSheet.h"
#define		SPLICT_SIZE		2

#define     EXT_DIRECTION_LEFT		1
#define     EXT_DIRECTION_RIGHT		2
#define     EXT_DIRECTION_TOP		3
#define     EXT_DIRECTION_BOTTOM	4

#define		SEL_NORMAL		0
#define		SEL_ROW			1
#define		SEL_COL			2
#define		SEL_ALL			3
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLSheet::CLSheet():m_pFunChain(NULL),m_nSheetLineStyle(GRID_LINE_DEFAULT),m_ptrArea(NULL),
	m_bActive(FALSE),m_bCanOperate(TRUE),m_bProtected(FALSE),m_strPass(NULL),m_ptrName(NULL),
	m_lpOldObj(NULL),m_bRangeBorderDown(FALSE),m_bRangeCornerDown(FALSE),m_bResizeFixedCellOnly(TRUE),
	m_bCellAreaDown(FALSE),m_bTrackColSize(FALSE),m_bTrackRowSize(FALSE),m_nTrackOffset(0),m_nRowColID(-1),
	m_ptrDDraw(NULL),m_bRowColSelDown(FALSE),m_bSelectRow(FALSE),m_bSelectCol(FALSE),
	m_nSelMask(SEL_NORMAL),m_nFillType(STYLE_FILL_COPY),m_bGraphicsDown(FALSE)
{
	CLPlatform::ClearRect(m_rctAll);
	CLPlatform::ClearRect(m_rctClient);
	CLPlatform::ClearRect(m_rctTotal);
	CLPlatform::ClearPoint(m_posStart);
	m_ptrOld_rc.x=-1;
	m_ptrOld_rc.y=-1;
	//CLPlatform::ClearPoint(m_posStartDraw);
}

CLSheet::~CLSheet()
{
	if(m_ptrArea)
		delete m_ptrArea;
	if(m_pFunChain)
		delete m_pFunChain;
	if(m_strPass)
		delete[] m_strPass;
	if(m_ptrName)
		delete[] m_ptrName;
}

void CLSheet::DeleteDrawItem(CLDrawItemBase* ptrItem)
{
	m_graphics.DeleteDrawItem(ptrItem);
}
BOOL CLSheet::BringToTop(CLDrawItemBase *ptrItem)
{
	return m_graphics.BringToTop(ptrItem);
}
BOOL CLSheet::BringToBottom(CLDrawItemBase *ptrItem)
{
	return m_graphics.BringToBottom(ptrItem);
}
BOOL CLSheet::BringToBack(CLDrawItemBase* ptrItem)
{
	return m_graphics.BringToBack(ptrItem);
}
BOOL CLSheet::BringToFront(CLDrawItemBase* ptrItem)
{
	return m_graphics.BringToFront(ptrItem);
}
CLDrawItemBase* CLSheet::GetTopMostItem()
{
	return m_graphics.GetTopMostItem();
}
CLDrawItemBase* CLSheet::GetBottomItem()
{
	return m_graphics.GetBottomItem();
}
void CLSheet::SetFocusItem(CLDrawItemBase* ptrItem)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	m_graphics.SetFocus(ptrItem);
}
LONG CLSheet::AddDrawItem(CLDrawItemBase* ptrItem)
{
	if(!ptrItem)return 0;
	ptrItem->SetSizeNotify((ISizeNotify*)this);
	LONG ret= m_graphics.AddDrawItem(ptrItem);
	ReDraw();
	return ret;
}
BOOL CLSheet::IsTopMost(CLDrawItemBase* ptrItem)
{
	return m_graphics.IsTopMost(ptrItem);
}
BOOL CLSheet::IsBottom(CLDrawItemBase* ptrItem)
{
	return m_graphics.IsBottom(ptrItem);
}

LONG CLSheet::NotifyProc(LONG wMsg,LONG nCmd,WPARAM wParam,
		LPARAM lParam,BOOL& bCancel)
{
	if(m_pFunChain){
		LPCHAIN ptr=m_pFunChain;
		pfNotifyProc pfun;
		LONG ret;
		BOOL bPassNextFilter=TRUE;
		while(ptr && ptr->ptrData){
			pfun=(pfNotifyProc)ptr->ptrData;
			ret=pfun(wMsg,nCmd,wParam,lParam,bCancel,bPassNextFilter);
			if(!bPassNextFilter || bCancel)
				break;
			ptr=ptr->ptrNext;
		}
		return ret;
	}else{
		return DefaultMessageProc(wMsg,nCmd,wParam,lParam,bCancel);
	}
}
LONG CLSheet::DefaultMessageProc(LONG wMsg,LONG nCmd,
		WPARAM wParam,LPARAM lParam,BOOL& bCancel)
{
		bCancel=FALSE;
		//MessageBox(NULL,"NotifyProc In CLSheet","TEST",MB_OK);
		return 0;
}
BOOL CLSheet::SetMessageFilter(LPVOID ptrFun)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	BOOL bRet=TRUE;
	if(ptrFun){
		//确保函数存在
		BOOL bFind=FALSE;
		LPCHAIN ptr=m_pFunChain,ptrParent=NULL;
		while(ptr && ptr->ptrData){
			if(ptrFun==ptr->ptrData){
				if(ptrParent){
					//如果在链头则不处理
					ptrParent->ptrNext=ptr->ptrNext;
					ptr->ptrNext=m_pFunChain;
					m_pFunChain=ptr;
				}
				bFind=TRUE;
				break;
			}
			ptrParent=ptr;
			ptr=ptr->ptrNext;
		}
		if(!bFind){
			//确保函数链中没有包含该回调
			LPCHAIN ptrChain=new CHAIN();
			ptrChain->ptrData=ptrFun;
			ptrChain->ptrNext=m_pFunChain;
			m_pFunChain=ptrChain;
		}
	}
	return bRet;
}
BOOL CLSheet::RemoveMessageFilter(LPVOID ptrFun)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	BOOL bRet=TRUE;
	if(ptrFun){
		//确保函数存在
		LPCHAIN ptr=m_pFunChain,ptrParent=NULL;
		while(ptr && ptr->ptrData){
			if(ptrFun==ptr->ptrData){
				if(ptrParent){
					ptrParent->ptrNext=ptr->ptrNext;
				}else{
					m_pFunChain=ptr->ptrNext;
				}
				ptr->ptrNext=NULL;
				delete ptr;
				break;
			}
			ptrParent=ptr;
			ptr=ptr->ptrNext;
		}
	}
	return bRet;
}

LONG CLSheet::GetSheetLineStyle()
{
	return m_nSheetLineStyle;
}
void CLSheet::SetSheetLineStyle(LONG val)
{
	m_nSheetLineStyle=val;
	ReDraw();
}
void CLSheet::OnMouseMove(LONG idArea,MOUSESTATUS& nstatus)
{
	BOOL bError=FALSE;
	POINT pt;
	char* ptrMsg=NULL;
	pt.x=nstatus.posx;
	pt.y=nstatus.posy;
	switch(idArea){
	case AREA_TABLE:
	//首先看看是否在画板对象上
		if(m_bCellAreaDown/*确保不是客户区域选择*/||(!m_bGraphicsDown 
			&& (!IsInDrawerObjectArea(m_hitest,nstatus,pt,bError)))){
			OnHitest(m_hitest,pt);
		}
		if(m_hitest.nButton==0){
			switch(m_hitest.nHitest){
			case AREA_IN_HORZ_SPLICT_LINE:
				CLPlatform::SetCursor(IDC_CURSIZE_NS);
				break;
			case AREA_IN_VERT_SPLICT_LINE:
				CLPlatform::SetCursor(IDC_CURSIZE_EW);
				break;
			case AREA_CLIENT:
			case AREA_FREEZE_RGN:
			case AREA_FIXED_RGN_CROSS:
				CLPlatform::SetCursor(IDC_CURCROSS);
				if(m_hitest.nButton!=AREA_FIXED_RGN_CROSS){
					/*显示批注的热键跟踪*/
					if(m_ptrOld_rc.x!=m_hitest.nRow ||
						m_ptrOld_rc.y!=m_hitest.nCol){
						ptrMsg=GetCellMemo(m_hitest.nRow,m_hitest.nCol);
						if(ptrMsg && ptrMsg[0]!='\0'){
							POINT ppt;
							RECT rctTip,rctV;
							GetCellRect(m_hitest.nRow,m_hitest.nCol,rctTip,rctV,FALSE);
							ppt.x=rctV.right;
							ppt.y=rctV.top;
							ShowToolTip(&ppt,ptrMsg);
						}else{
							ShowToolTip(NULL,NULL,FALSE);
						}
						m_ptrOld_rc.x=m_hitest.nRow;
						m_ptrOld_rc.y=m_hitest.nCol;
					}
				}
				break;
			case AREA_FIXED_RGN_HORZ:
				CLPlatform::SetCursor(IDC_CURRIGHT);
				break;
			case AREA_FIXED_RGN_VERT:
				CLPlatform::SetCursor(IDC_CURDOWN);
				break;
			case AREA_RANGE_CORNER:
				CLPlatform::SetCursor(IDC_CUR_CROSS);
				//当前范围可拖动角
				break;
			case AREA_GRAPHICS:
				if(m_lpOldObj)
					((IMouseEvent*)m_lpOldObj)->OnMouseMove(m_oldID,nstatus);
				break;
			}
		}else{
			//鼠标按钮按下了
			if(m_bTrackRowSize){
				RECT rct;
				GetClientRect(rct);
				m_nTrackOffset=nstatus.posy-m_ptTrack.y;
				if(m_ptTrack.y+m_nTrackOffset>=rct.bottom-2){
					m_nTrackOffset=rct.bottom-2-m_ptTrack.y;
				}else if(m_ptTrack.y+m_nTrackOffset<=m_rctTrack.top+2){
					m_nTrackOffset=m_rctTrack.top+2-m_ptTrack.y;
				}
				DrawTrack(TRUE);
			}else if(m_bTrackColSize){
				RECT rct;
				GetClientRect(rct);
				m_nTrackOffset=nstatus.posx-m_ptTrack.x;
				if(m_ptTrack.x+m_nTrackOffset>=rct.right-2){
					m_nTrackOffset=rct.right-2-m_ptTrack.x;
				}else if(m_ptTrack.x+m_nTrackOffset<=m_rctTrack.left+2){
					m_nTrackOffset=m_rctTrack.left+2-m_ptTrack.x;
				}
				DrawTrack(FALSE);
			}else if(m_bCellAreaDown){
				//CLPlatform::DebugMsg("RANGE(%d,%d,%d,%d)\n",m_currentCell.Row,m_currentCell.Col,
				//	m_hitest.nRow,m_hitest.nCol);
				TrackRangeSel(m_hitest.nRow,m_hitest.nCol);
			}else if(m_bRowColSelDown){
				if(m_bSelectRow){
					TrackRangeSel(m_hitest.nRow,GetCols()-1,FALSE);
				}else if(m_bSelectCol){
					TrackRangeSel(GetRows()-1,m_hitest.nCol,FALSE);
				}else{
					ASSERT(FALSE);
				}
			}else if(m_bRangeBorderDown){
				//拖动范围
				LONG nOffsetX=(m_hitest.nCol-m_ptTrack.x),
					nOffsetY=(m_hitest.nRow-m_ptTrack.y);
				m_TrackCurr.m_posRow.m_begin+=nOffsetY;
				m_TrackCurr.m_posRow.m_end+=nOffsetY;
				m_TrackCurr.m_posCol.m_begin+=nOffsetX;
				m_TrackCurr.m_posCol.m_end+=nOffsetX;
				if(m_ptrDDraw && !(m_TrackOld==m_TrackCurr)){
					m_ptrDDraw->DrawDragRange(NULL,m_TrackOld,m_TrackCurr);
					m_TrackOld=m_TrackCurr;
				}
				m_ptTrack.x=m_hitest.nCol;
				m_ptTrack.y=m_hitest.nRow;
			}else if(m_bGraphicsDown){
				if(m_lpOldObj)
					((IMouseEvent*)m_lpOldObj)->OnMouseMove(m_oldID,nstatus);
			}
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
//判断是否可以移动区域
BOOL CLSheet::isCanMove(const RECT &rctSrc, const RECT &rctTo)
{
	BOOL bret=TRUE;
	
	return bret;
}
void CLSheet::CopyRange(const RANGE& rangeSrc, const RANGE& rangeDst, BOOL bFillByRule)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	if(bFillByRule){
		if(rangeSrc.isEmpty() || rangeDst.isEmpty())return;
		//按照规则填充单元格区域
		
	}else{
		//如果需要提示信息则因当在此加入代码
		//......
		
		//移动当前区域
		if(rangeDst.isEmpty() || rangeDst==m_CurrRange)return;
		LONG xOff=rangeDst.m_posCol.m_begin-m_CurrRange.m_posCol.m_begin;
		LONG yOff=rangeDst.m_posRow.m_end-m_CurrRange.m_posRow.m_end;
		LONG nBeginRow,nBeginCol,nEndRow,nEndCol;
		BOOL bRowInc=TRUE,bColInc=TRUE;
		if(m_CurrRange.m_posCol.m_begin<=rangeDst.m_posCol.m_begin){
			nBeginCol=m_CurrRange.m_posCol.m_end;
			nEndCol=m_CurrRange.m_posCol.m_begin;
			bColInc=FALSE;
		}else{
			nBeginCol=m_CurrRange.m_posCol.m_begin;
			nEndCol=m_CurrRange.m_posCol.m_end;
		}
		if(m_CurrRange.m_posRow.m_begin<=rangeDst.m_posRow.m_begin){
			nBeginRow=m_CurrRange.m_posRow.m_end;
			nEndRow=m_CurrRange.m_posRow.m_begin;
			bRowInc=FALSE;
		}else{
			nBeginRow=m_CurrRange.m_posRow.m_begin;
			nEndRow=m_CurrRange.m_posRow.m_end;
		}

		//得检查能否覆盖指定区域数据
		RECT rct,rctTo;
		rct.top=(bRowInc?nBeginRow:nEndRow);
		rct.bottom=(bRowInc?nEndRow:nBeginRow);
		rct.left=(bColInc?nBeginCol:nEndCol);
		rct.right=(bColInc?nEndCol:nBeginCol);
		rctTo=rct;
		MoveRect(rctTo,xOff,yOff);
		CLMerge* ptrMerge=NULL;
		BOOL bCanDo=TRUE,bBorder;
		LONG nIndex;
		BOOL bDefault=FALSE;
		CLStyle* ptrStyle,*ptrStyleSrc;
		VALUE_LINK link,linkDst,*ptrLink=NULL,*ptrLkDst=NULL;
		if(isCanMove(rct,rctTo)){
			CLCellItem* ptrItem,*ptrItemTo;
			//得注意不要覆盖了有交叉的部分数据
			for(LONG irow=nBeginRow;(bRowInc?irow<=nEndRow:irow>=nEndRow);irow+=(bRowInc?1:-1)){
				for(LONG icol=nBeginCol;(bColInc?icol<=nEndCol:icol>=nEndCol);icol+=(bColInc?1:-1)){
					ptrItem=GetACell(irow,icol);
					ptrStyleSrc=GetCellStyle(irow,icol);
					bDefault=IsDefaultCellStyle(ptrStyleSrc);
					bBorder=(irow==nBeginRow || irow== nEndRow || icol==nBeginCol || icol==nEndCol);
					if(ptrItem){
						ptrItemTo=GetACell(irow+yOff,icol+xOff,TRUE);
						ptrStyle=GetCellStyle(irow+yOff,icol+xOff,ptrStyleSrc!=NULL);
						if(m_pMergeArr){
							ptrMerge=m_pMergeArr->getMergeObject(ptrItemTo);
							if(ptrMerge){
								nIndex=ptrItemTo->GetMergeIndex();
								if(!linkDst.isExist((LONG)nIndex)){
									if(NULL==ptrLkDst){
										ptrLkDst=&linkDst;
									}else{
										ptrLkDst->ptrNext=new VALUE_LINK();
										ptrLkDst=ptrLkDst->ptrNext;
									}
									ptrLkDst->nValue=(LONG)nIndex;
								}
							}
						}						
						ptrItemTo->SetCell(ptrItem);
						if(ptrStyleSrc){
							ptrStyle->CopyStyle(ptrStyleSrc);
							if(!IsDefaultCellStyle(ptrStyle)){
								RemoveCellStyle(irow,icol);
							}
						}
						
						if(m_pMergeArr){
							ptrMerge=m_pMergeArr->getMergeObject(ptrItem);
							if(ptrMerge){
								nIndex=ptrItem->GetMergeIndex();
								bCanDo=!(link.isExist((LONG)nIndex));
								if(bCanDo){
									if(ptrLink==NULL){
										ptrLink=&link;
									}else{
										ptrLink->ptrNext=new VALUE_LINK();
										ptrLink=ptrLink->ptrNext;
									}
									ptrLink->nValue=(LONG)nIndex;
									RECT rctRgn;
									ptrMerge->getRange(&rctRgn);
									MoveRect(rctRgn,xOff,yOff);
									ptrMerge->setRange(&rctRgn);
								}
							}
						}
						ptrItem->ClearToDefault();
					}else{
						ptrItemTo=GetACell(irow+yOff,icol+xOff);
						ptrStyle=GetCellStyle(irow+yOff,icol+xOff,ptrStyleSrc!=NULL);
						if(ptrStyleSrc)
							ptrStyle->CopyStyle(ptrStyleSrc);
						BOOL bD=FALSE;
						if(!IsDefaultCellStyle(ptrStyleSrc)){
							RemoveCellStyle(irow,icol);
							//ASSERT(bDefault);
						}
						if(ptrItemTo){
							if(m_pMergeArr){
								ptrMerge=m_pMergeArr->getMergeObject(ptrItemTo);
								if(ptrMerge){
									nIndex=ptrItemTo->GetMergeIndex();
									if(!linkDst.isExist((LONG)nIndex)){
										if(NULL==ptrLkDst){
											ptrLkDst=&linkDst;
										}else{
											ptrLkDst->ptrNext=new VALUE_LINK();
											ptrLkDst=ptrLkDst->ptrNext;
										}
										ptrLkDst->nValue=(LONG)nIndex;
									}
								}
							}
							ptrItemTo->ClearToDefault();
						}
					}
				}
			}
			//linkDst.SubLink(link);
			ptrLink=&linkDst;
			while(ptrLink){
				if(ptrLink->nValue!=INIT_LINK_VALUE){
					m_pMergeArr->RemoveMergeObject(ptrLink->nValue);
				}
				ptrLink=ptrLink->ptrNext;
			}
			ptrLink=&link;
			while(ptrLink){
				if(ptrLink->nValue!=INIT_LINK_VALUE){
					m_pMergeArr->RefreshMergeRange(ptrLink->nValue);
				}
				ptrLink=ptrLink->ptrNext;
			}
			
			m_CurrRange=rangeDst;
			m_currentCell.Row+=yOff;
			m_currentCell.Col+=xOff;
			if(m_prevFocusCell.Row>0)
				m_prevFocusCell.Row+=yOff;
			if(m_prevFocusCell.Col>0)
				m_prevFocusCell.Col+=xOff;
		}
	}
}
void CLSheet::ShowToolTip(LPPOINT ppt,LPTSTR ptrMsg,BOOL bShow)
{
	HDCH drawer;
	if(m_ptrDDraw && GetDC(drawer)){
		drawer.pParam=ppt;
		m_ptrDDraw->ShowToolTip(&drawer,ptrMsg,bShow);
		ReleaseDC(drawer);
	}
}
void CLSheet::DrawTrack(BOOL bHorz,BOOL bMove)
{
	HDCH drawer;
	RECT rct,rctClip;
	GetTableRect(rct);
	GetClientRect(rctClip);
	rct.right=rctClip.right;
	rct.bottom=rctClip.bottom;
	if(GetDC(drawer)){
		POINT ptS,ptE;
		if(!bMove || (bMove && m_nTrackOffset!=0)){
			if(bHorz){
				ptS.x=rct.left;
				ptS.y=m_ptTrack.y;
				ptE.x=ptS.x+(rct.right-rct.left);
				ptE.y=ptS.y;
			}else{
				ptS.x=m_ptTrack.x;
				ptS.y=rct.top;
				ptE.x=ptS.x;
				ptE.y=ptS.y+(rct.bottom-rct.top);
			}
			CLDrawer::DrawTrack(drawer.hDC,2,&ptS,&ptE,!bHorz);
		}
		if(m_nTrackOffset!=0){
			if(bHorz){
				m_ptTrack.x+=m_nTrackOffset;
				m_ptTrack.y+=m_nTrackOffset;
				ptS.y+=m_nTrackOffset;
				ptE.y+=m_nTrackOffset;
			}else{
				m_ptTrack.y+=m_nTrackOffset;
				m_ptTrack.x+=m_nTrackOffset;
				ptS.x+=m_nTrackOffset;
				ptE.x+=m_nTrackOffset;
			}	
			CLDrawer::DrawTrack(drawer.hDC,2,&ptS,&ptE,!bHorz);
		}
		ReleaseDC(drawer);
	}
}
BOOL CLSheet::IsInDrawerObjectArea(HITEST& hitest,MOUSESTATUS& nstatus
								   ,const POINT& pt,BOOL& bError,BOOL bRaiseEvent)
{
	RECT rctClip;
	POINT ptFreeze;
	GetClientRect(rctClip);
	GetBeginFreezePos(ptFreeze);//冻结单元开始位置
	rctClip.left=ptFreeze.x;
	rctClip.top=ptFreeze.y;
	MOUSESTATUS status=nstatus;
	BOOL bFind=FALSE;

	if(rctClip.top!=rctClip.bottom && CLDrawer::PtInRect(&rctClip,pt)){
		POINT ptt=pt;
		//
		//
		//ptt.x+=m_posStart.x;
		//ptt.y+=m_posStart.y;

		//ptt.x-=ptFreeze.x;
		//ptt.y-=ptFreeze.y;
		status.posx=ptt.x;
		status.posy=ptt.y;
		CLDrawItemBase* ptr=m_graphics.GetTopMostItem();
		IMouseEvent* ptrEvent;
		LPIDAREA lpidarea;
		HRGN hrgn;
		RECT rct;
		while(ptr){
			ptrEvent=(IMouseEvent*)ptr;
			lpidarea=ptrEvent->GetAreaIDs();
			while(lpidarea){
				if(lpidarea->bRect){
					if(ptrEvent->GetRect(lpidarea->lngID,rct)){
						if(CLDrawer::PtInRect(&rct,ptt)){
							bFind=TRUE;
						}
					}else{
						ASSERT(FALSE);
					}
				}else{
					if(ptrEvent->GetRgn(lpidarea->lngID,hrgn)){
						ASSERT(hrgn);
						if(CLDrawer::PtInRegion(hrgn,ptt.x,ptt.y)){
							bFind=TRUE;
						}
						CLDrawer::DeleteRgn(hrgn);
					}else{
						ASSERT(FALSE);
					}
				}
				if(bFind && bRaiseEvent){
					if(m_lpOldObj && m_lpOldObj!=(LPVOID)ptrEvent){
						((IMouseEvent*)m_lpOldObj)->OnMouseOut(m_oldID,status);
					}
					ptrEvent->OnMouseMove(lpidarea->lngID,status);
					m_lpOldObj=(LPVOID)ptrEvent;
					m_oldID=lpidarea->lngID;
					break;
				}
				lpidarea=lpidarea->ptrNext;
			}
			if(bFind){
				m_hitest.nHitest=AREA_GRAPHICS;
				break;
			}
			ptr=m_graphics.GetNextItem(ptr);
		}
	}
	if(!bFind && m_lpOldObj && bRaiseEvent){
		((IMouseEvent*)m_lpOldObj)->OnMouseOut(m_oldID,status);
		m_lpOldObj=NULL;
	}
	return bFind;
}
void CLSheet::OnHitest(HITEST& hitest,const POINT& pt)
{
	BOOL bError=FALSE;
	//首先看看是否在画板对象上
	//看看是否在客户区域
	CELL cell;
	POINT ptOffset;
	GetBeginCell(cell);
	GetCellBeginXY(ptOffset);
	ptOffset.x++;
	ptOffset.y++;

	POINT ptt=pt;
	ptt.x-=m_posStart.x;
	ptt.y-=m_posStart.y;
	hitest.nHitest=AREA_CLIENT;
	
	if(isInClient(hitest,ptt,cell,ptOffset,bError)){
		if(bError)
			hitest.nHitest=AREA_ERROR;
		return;
	}
	if(!m_bCellAreaDown){
		hitest.nHitest=AREA_FREEZE_RGN;
		if(isInFreezeArea(hitest,ptt,cell,ptOffset,bError)){
			if(bError)
				hitest.nHitest=AREA_ERROR;
			return;
		}
		if(isInFixedArea(hitest,ptt,cell,ptOffset,bError)){
			if(bError)
				hitest.nHitest=AREA_ERROR;
			return;
		}
		hitest.nHitest=AREA_OUTER;
	}else{
		hitest.nHitest=AREA_CLIENT;
		//一定在GRID外,这种情况我们最好知道当前虚拟的行/列
		OuterHitest(hitest,ptt,cell,ptOffset);
		CELL cell;
		cell.Row=hitest.nRow;
		cell.Col=hitest.nCol;
		AutoAdjustPos(cell);
	}
}
void CLSheet::OuterHitest(HITEST &hitest, const POINT &pt, 
				 const CELL &cellBegin, const POINT &ptOffset)
{
	CELL cell;
	cell.Row=hitest.nRow;
	cell.Col=hitest.nCol;
	RECT rctClip,rct;
	GetClientRect(rctClip);
	LONG offsetX=0,offsetY=0,sizeX,sizeY;
	if(pt.x<rctClip.left){
		//左边
		hitest.nUserData=EXT_DIRECTION_LEFT;
		offsetX=pt.x-rctClip.left;
	}else if(pt.x>rctClip.right){
		//右边
		hitest.nUserData=EXT_DIRECTION_RIGHT;
		offsetX=pt.x-rctClip.right;
	}
	if(pt.y<rctClip.top){
		hitest.nUserData=EXT_DIRECTION_TOP;
		offsetY=pt.y-rctClip.top;
		//上边
	}else if(pt.y>rctClip.bottom){
		//下边
		hitest.nUserData=EXT_DIRECTION_BOTTOM;
		offsetY=pt.y-rctClip.bottom;
	}
	GetCellRect(cell,rct,rctClip,FALSE);
	LONG irow,icol;
	CLColItem* ptrCol;
	CLRowItem* ptrRow;
	if(offsetX!=0){
		//在两边
		//看看行offset
		if(pt.y<rct.top){
			sizeY=rct.top;
			for(irow=cell.Row-1;irow>=m_FixedRows+m_FreezeRows;irow--){
				ptrRow=GetARow(irow);
				sizeY-=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(pt.y>=sizeY){
					hitest.nRow=irow;
					break;
				}
			}
		}else if(pt.y>rct.bottom){
			sizeY=rct.bottom;
			for(irow=cell.Row+1;irow<m_Rows;irow++){
				ptrRow=GetARow(irow);
				sizeY+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(pt.y<=sizeY){
					hitest.nRow=irow;
					break;
				}
			}
		}
		if(offsetX<0){
			//左边
			sizeX=rct.left;
			for(icol=cell.Col-1;icol>=m_FixedCols+m_FreezeCols;icol--){
				ptrCol=GetACol(icol);
				sizeX-=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				if(pt.x>=sizeX){
					hitest.nCol=icol;
					break;
				}
			}
		}else{
			//右边
			sizeX=rct.right;
			for(icol=cell.Col+1;icol<m_Cols;icol++){
				ptrCol=GetACol(icol);
				sizeX+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				if(pt.x<=sizeX){
					hitest.nCol=icol;
					break;
				}
			}
		}
	}
	if(offsetY!=0){
		//在上下
		//看看列offset
		if(pt.x<rct.left){
			sizeX=rct.left;
			for(icol=cell.Col-1;icol>=m_FixedCols+m_FreezeCols;icol--){
				ptrCol=GetACol(icol);
				sizeX-=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				if(pt.x>=sizeX){
					hitest.nCol=icol;
					break;
				}
			}
		}else if(pt.x>rct.right){
			sizeX=rct.right;
			for(icol=cell.Col+1;icol<m_Cols;icol++){
				ptrCol=GetACol(icol);
				sizeX+=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				if(pt.x<=sizeX){
					hitest.nCol=icol;
					break;
				}
			}
		}
		if(offsetY<0){
			sizeY=rct.top;
			for(irow=cell.Row-1;irow>=m_FixedRows+m_FreezeRows;irow--){
				ptrRow=GetARow(irow);
				sizeY-=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(pt.y>=sizeY){
					hitest.nRow=irow;
					break;
				}
			}
		}else{
			sizeY=rct.bottom;
			for(irow=cell.Row+1;irow<m_Rows;irow++){
				ptrRow=GetARow(irow);
				sizeY+=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
				if(pt.y<=sizeY){
					hitest.nRow=irow;
					break;
				}
			}
		}	
	}
}
BOOL CLSheet::isInFreezeArea(HITEST &hitest, const POINT &pt, 
						 const CELL &cellBegin, const POINT &ptOffset, BOOL &bError)
{
	RANGE range;
	BOOL bret=FALSE;
	RECT rct,rctClip;
	POINT ptFreeze;
	GetClientRect(rctClip);
	rct=rctClip;
	GetBeginFreezePos(ptFreeze);//冻结单元开始位置
	rctClip.bottom=rctClip.top;
	rctClip.top=ptFreeze.y;
	
	if(rctClip.top!=rctClip.bottom && CLDrawer::PtInRect(&rctClip,pt)){
		range.m_posRow.m_begin=GetFixedRows();
		range.m_posRow.m_end=range.m_posRow.m_begin+GetFreezeRows();
		range.m_posCol.m_begin=cellBegin.Col;
		range.m_posCol.m_end=GetCols();
		ptFreeze=ptOffset;
		ptFreeze.y=0;
		if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
			ASSERT(FALSE);
			bError=TRUE;
		}else{
			bret=TRUE;
		}
	}else{
		rctClip.top=rct.top;
		rctClip.left=ptFreeze.x;
		rctClip.right=rct.left;
		rctClip.bottom=rct.bottom;
		if(rctClip.left!=rctClip.right && CLDrawer::PtInRect(&rctClip,pt)){
			range.m_posRow.m_begin=cellBegin.Row;
			range.m_posRow.m_end=GetRows();
			range.m_posCol.m_begin=GetFixedCols();
			range.m_posCol.m_end=range.m_posCol.m_begin+GetFreezeCols();
			ptFreeze=ptOffset;
			ptFreeze.x=0;
			if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
				ASSERT(FALSE);
				bError=TRUE;
			}else{
				bret=TRUE;
			}
		}else{
			rctClip.top=ptFreeze.y;
			rctClip.left=ptFreeze.x;
			rctClip.right=rct.left;
			rctClip.bottom=rct.top;
			if(CLDrawer::PtInRect(&rctClip,pt)){
				range.m_posRow.m_begin=GetFixedRows();
				range.m_posRow.m_end=range.m_posRow.m_begin+GetFreezeRows();
				range.m_posCol.m_begin=GetFixedCols();
				range.m_posCol.m_end=range.m_posCol.m_begin+GetFreezeCols();
				ptFreeze.x=0;
				ptFreeze.y=0;
				if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
					ASSERT(FALSE);
					bError=TRUE;
				}else{
					bret=TRUE;
				}
			}
		}
	}
	return bret;
}
BOOL CLSheet::isInFixedArea(HITEST &hitest, const POINT &pt, 
						 const CELL &cellBegin, const POINT &ptOffset, BOOL &bError)
{
	RANGE range;
	BOOL bret=FALSE;
	RECT rct,rctClip;
	POINT ptFreeze,ptTable;
	GetBeginTablePos(ptTable);
	GetClientRect(rctClip);
	rct=rctClip;
	GetBeginFreezePos(ptFreeze);//开始位置
	rctClip.bottom=ptFreeze.y;
	rctClip.top=ptTable.y;
	if(rctClip.top!=rctClip.bottom && CLDrawer::PtInRect(&rctClip,pt)){
		range.m_posRow.m_begin=0;
		range.m_posRow.m_end=GetFixedRows();
		range.m_posCol.m_begin=cellBegin.Col;
		range.m_posCol.m_end=GetCols();
		ptFreeze=ptOffset;
		ptFreeze.y=0;
		hitest.nHitest=AREA_FIXED_RGN_VERT;
		if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
			ASSERT(FALSE);
			bError=TRUE;
		}else{
			bret=TRUE;
		}
	}else{
		rctClip.top=rct.top;
		rctClip.left=ptTable.x;
		rctClip.right=ptFreeze.x;
		rctClip.bottom=rct.bottom;
		if(rctClip.left!=rctClip.right && CLDrawer::PtInRect(&rctClip,pt)){
			range.m_posRow.m_begin=cellBegin.Row;
			range.m_posRow.m_end=GetRows();
			range.m_posCol.m_begin=0;
			range.m_posCol.m_end=GetFixedCols();
			ptFreeze=ptOffset;
			ptFreeze.x=0;
			hitest.nHitest=AREA_FIXED_RGN_HORZ;
			if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
				ASSERT(FALSE);
				bError=TRUE;
			}else{
				
				bret=TRUE;
			}
		}else{
			rctClip.top=ptTable.y;
			rctClip.left=ptTable.x;
			rctClip.right=ptFreeze.x;
			rctClip.bottom=ptFreeze.y;
			if(CLDrawer::PtInRect(&rctClip,pt)){
				range.m_posRow.m_begin=0;
				range.m_posRow.m_end=GetFixedRows();
				range.m_posCol.m_begin=0;
				range.m_posCol.m_end=GetFixedCols();
				ptFreeze.x=0;
				ptFreeze.y=0;
				hitest.nHitest=AREA_FIXED_RGN_CROSS;
				if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
					ASSERT(FALSE);
					bError=TRUE;
				}else{
					
					bret=TRUE;
				}
			}else{
				rctClip.top=ptTable.y;
				rctClip.left=ptFreeze.x;
				rctClip.right=rct.left;
				rctClip.bottom=ptFreeze.y;
				if(CLDrawer::PtInRect(&rctClip,pt)){
					range.m_posRow.m_begin=0;
					range.m_posRow.m_end=GetFixedRows();
					range.m_posCol.m_begin=GetFixedCols();
					range.m_posCol.m_end=range.m_posCol.m_begin+GetFreezeCols();
					ptFreeze.x=0;
					ptFreeze.y=0;
					hitest.nHitest=AREA_FIXED_RGN_VERT;
					if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
						ASSERT(FALSE);
						bError=TRUE;
					}else{
						
						bret=TRUE;
					}
				}else{
					rctClip.top=ptFreeze.y;
					rctClip.left=ptTable.x;
					rctClip.right=ptFreeze.x;
					rctClip.bottom=rct.top;
					if(CLDrawer::PtInRect(&rctClip,pt)){
						range.m_posRow.m_begin=GetFixedRows();
						range.m_posRow.m_end=range.m_posRow.m_begin+GetFreezeRows();
						range.m_posCol.m_begin=0;
						range.m_posCol.m_end=GetFixedCols();
						ptFreeze.x=0;
						ptFreeze.y=0;
						hitest.nHitest=AREA_FIXED_RGN_HORZ;
						if(!GetPosInfo(hitest,pt,range,ptFreeze,rctClip)){
							ASSERT(FALSE);
							bError=TRUE;
						}else{
							
							bret=TRUE;
						}
					}else{
						//没有找到匹配的单元格,在客户区外的空闲区域
						hitest.nHitest=AREA_OUTER;
					}
				}
			}
		}
	}
	return bret;
}
BOOL CLSheet::isInClient(HITEST &hitest, const POINT &pt, 
						 const CELL &cellBegin, const POINT &ptOffset, BOOL &bError)
{
	BOOL bret=FALSE;
	RECT rctClip;
	RANGE range;
	GetClientRect(rctClip);
	if(CLDrawer::PtInRect(&rctClip,pt)){
		//在客户区，看看鼠标停在哪个单元
		range.m_posRow.m_begin=cellBegin.Row;
		range.m_posRow.m_end=GetRows();
		range.m_posCol.m_begin=cellBegin.Col;
		range.m_posCol.m_end=GetCols();
		if(!GetPosInfo(hitest,pt,range,ptOffset,rctClip)){
			//在客户区域的空闲区域
			ASSERT(FALSE);
			bError=TRUE;
		}else{
			bret=TRUE;
		}
	}
	return bret;
}
BOOL CLSheet::GetPosInfo(HITEST &hitest, const POINT &pt, 
						 const RANGE &range,const POINT& ptOffset,const RECT& rctClip)
{
	BOOL bFind=FALSE,bBreak=FALSE;
	LONG nBeginLeft=ptOffset.x,nBeginTop=ptOffset.y;
	LONG nctx,ncty=rctClip.top-ptOffset.y,valh=0,valv=0,valhpre=0,valvpre=0;
	CLColItem* ptrCol;
	CLRowItem* ptrRow;
	hitest.m_Rect.top=rctClip.top-ptOffset.y;
	BOOL bResize=TRUE;
	for(LONG irow=range.m_posRow.m_begin;irow<range.m_posRow.m_end;irow++){
		nctx=rctClip.left-ptOffset.x;
		hitest.m_Rect.left=nctx;
		ptrRow=GetARow(irow);
		valvpre=valv;
		valv=(ptrRow?ptrRow->GetHeight():DEFAULT_ROW_HEIGHT);
		ncty+=valv;
		hitest.m_Rect.bottom=hitest.m_Rect.top+valv;
		//找到行先
		if(pt.y<=ncty){
			bBreak=TRUE;
			hitest.nRow=irow;
			for(LONG icol=range.m_posCol.m_begin;icol<range.m_posCol.m_end;icol++){
				ptrCol=GetACol(icol);
				valhpre=valh;
				valh=(ptrCol?ptrCol->GetWidth():DEFAULT_COL_WIDTH);
				hitest.m_Rect.right=hitest.m_Rect.left+valh;
				nctx+=valh;
				if(pt.x<=nctx){
					bFind=TRUE;
					//哈哈找到喽
					
					hitest.nCol=icol;
					///////////////测试代码///////////////////
					/*
					char ptrTxt[255];
					sprintf(ptrTxt,"%d,%d\0",irow,icol);
					SetCellText(0,0,ptrTxt);
					ReDraw();
					*/
					//////////////////End/////////////////////
					//判断是否位于行/列线，或特定区域范围
					//是否在行线上
					//if(m_bResizeFixedCellOnly){
					bResize=(irow<m_FixedRows || icol<m_FixedCols);
					//}
					if(ncty-pt.y<SPLICT_SIZE){
						if(bResize){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
						}else if(m_bRangeMode && !m_CurrRange.isEmpty()){
							if(irow==m_CurrRange.m_posRow.m_end && 
								((icol==m_CurrRange.m_posCol.m_end && nctx-pt.x<(SPLICT_SIZE+1)) || 
								(icol==m_CurrRange.m_posCol.m_end+1 && nctx-pt.x>valh-(SPLICT_SIZE-1)))){
								hitest.nHitest=AREA_RANGE_CORNER;
							}else if((irow==m_CurrRange.m_posRow.m_end || irow==m_CurrRange.m_posRow.m_begin-1) 
								&& icol>=m_CurrRange.m_posCol.m_begin && icol<=m_CurrRange.m_posCol.m_end){
								hitest.nHitest=AREA_RANGE_BORDER;
							}
						}else if(!m_bResizeFixedCellOnly){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
						}
						//在行线上(底边)本行
					}else if(ncty-pt.y>valv-SPLICT_SIZE && irow>0){
						//在行线上(上边)前一行
						if(bResize){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
							hitest.m_Rect.top-=valvpre;
							hitest.m_Rect.bottom-=valvpre;
							hitest.nRow--;
						}else if(m_bRangeMode && !m_CurrRange.isEmpty()){
							if(irow==m_CurrRange.m_posRow.m_end+1 && 
								((icol==m_CurrRange.m_posCol.m_end+1 && nctx-pt.x>valh-(SPLICT_SIZE-1)) || 
								(icol==m_CurrRange.m_posCol.m_end && nctx-pt.x<(SPLICT_SIZE+1)))){
								hitest.nHitest=AREA_RANGE_CORNER;
							}else if((irow==m_CurrRange.m_posRow.m_begin || irow==m_CurrRange.m_posRow.m_end+1)
								&& icol>=m_CurrRange.m_posCol.m_begin && icol<=m_CurrRange.m_posCol.m_end){
								hitest.nHitest=AREA_RANGE_BORDER;
							}
						}else if(!m_bResizeFixedCellOnly){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
						}
					}
					if(nctx-pt.x<SPLICT_SIZE){
						//在本列列线上
						if(bResize){
							hitest.nHitest=AREA_IN_VERT_SPLICT_LINE;
						}else if(m_bRangeMode && !m_CurrRange.isEmpty()){
							if(icol==m_CurrRange.m_posCol.m_end && 
								((irow==m_CurrRange.m_posRow.m_end+1 && ncty-pt.y>valv-(SPLICT_SIZE-1)) 
									|| (irow==m_CurrRange.m_posRow.m_end && ncty-pt.y<(SPLICT_SIZE+1)))){
								hitest.nHitest=AREA_RANGE_CORNER;
							}else if((icol==m_CurrRange.m_posCol.m_end || icol==m_CurrRange.m_posCol.m_begin-1)
								&& irow>=m_CurrRange.m_posRow.m_begin && irow<=m_CurrRange.m_posRow.m_end){
								hitest.nHitest=AREA_RANGE_BORDER;
							}
						}else if(!m_bResizeFixedCellOnly){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
						}
					}else if(nctx-pt.x>valh-SPLICT_SIZE && icol>0){
						//前一列列线上
						if(bResize){
							hitest.nHitest=AREA_IN_VERT_SPLICT_LINE;
							hitest.m_Rect.left-=valhpre;
							hitest.m_Rect.right-=valhpre;
							hitest.nCol--;
						}else if(m_bRangeMode && !m_CurrRange.isEmpty()){
							if(icol==m_CurrRange.m_posCol.m_end+1 && 
								((irow==m_CurrRange.m_posRow.m_end && ncty-pt.y<(SPLICT_SIZE+1)) 
									|| (irow==m_CurrRange.m_posRow.m_end+1 && ncty-pt.y>valv-(SPLICT_SIZE-1)))){
								hitest.nHitest=AREA_RANGE_CORNER;
							}else if((icol==m_CurrRange.m_posCol.m_begin || icol==m_CurrRange.m_posCol.m_end+1)
								&& irow>=m_CurrRange.m_posRow.m_begin && irow<=m_CurrRange.m_posRow.m_end){
								hitest.nHitest=AREA_RANGE_BORDER;
							} 
						}else if(!m_bResizeFixedCellOnly){
							hitest.nHitest=AREA_IN_HORZ_SPLICT_LINE;
						}
					}
					/*
					CLPlatform::DebugMsg("CELL(%d,%d) RECT(%d,%d,%d,%d)\n",hitest.nRow,hitest.nCol,
						hitest.m_Rect.left,hitest.m_Rect.top,hitest.m_Rect.right,hitest.m_Rect.bottom);
					*//////////////
					break;
				}
				hitest.m_Rect.left+=valh;
				if(nctx>rctClip.right){
					//一定是没有找到
					ASSERT(FALSE);
					break;
				}
			}
			
		}
		if(bBreak)
			break;
		if(ncty>rctClip.bottom){
			//一定是没有找到
			ASSERT(FALSE);
			break;
		}
		hitest.m_Rect.top+=valv;
	}
	return bFind;
}
void CLSheet::OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=1;
	//屏蔽自动事件
	if(nstatus.nStatusParam==STATUS_FLAG_MAN)return;
	if(m_lpOldObj){
		if(m_graphics.m_ptrFocus!=m_lpOldObj){
			m_graphics.SetFocus((CLDrawItemBase*)m_lpOldObj);
			ReDraw();
		}
		m_bGraphicsDown=TRUE;
		((IMouseEvent*)m_lpOldObj)->OnLButtonDown(m_oldID,nstatus);
	}else{
		m_bSelectCol=FALSE;
		m_bSelectRow=FALSE;
		switch(m_hitest.nHitest){
		case AREA_IN_HORZ_SPLICT_LINE:
			CLPlatform::SetCursor(IDC_CURSIZE_NS);
			m_nRowColID=m_hitest.nRow;
			m_nTrackOffset=0;
			m_rctTrack=m_hitest.m_Rect;
			m_bTrackRowSize=TRUE;
			m_oldPs=nstatus.posy;
			m_ptTrack.x=nstatus.posx;
			m_ptTrack.y=nstatus.posy;
			DrawTrack(TRUE,FALSE);
			break;
		case AREA_IN_VERT_SPLICT_LINE:
			CLPlatform::SetCursor(IDC_CURSIZE_EW);
			m_nTrackOffset=0;
			m_nRowColID=m_hitest.nCol;
			m_oldPs=nstatus.posx;
			m_rctTrack=m_hitest.m_Rect;
			m_bTrackColSize=TRUE;
			m_ptTrack.x=nstatus.posx;
			m_ptTrack.y=nstatus.posy;
			DrawTrack(FALSE,FALSE);
			break;
		case AREA_CLIENT:
		case AREA_FREEZE_RGN:
		case AREA_FIXED_RGN_CROSS:
			{
				BOOL bRedrawAll=TRUE;//FALSE;
				if(m_graphics.m_ptrFocus!=NULL){
					m_graphics.SetFocus(NULL);
					//bRedrawAll=TRUE;
				}
				CLPlatform::SetCursor(IDC_CURCROSS);
				LONG nRow,nCol;
				BOOL bCanDo=(m_hitest.nHitest!=AREA_FIXED_RGN_CROSS ||
					(m_hitest.nHitest==AREA_FIXED_RGN_CROSS 
					&& (m_nSelMask!=SEL_ALL)));
				if(bCanDo){
					if(m_hitest.nHitest!=AREA_FIXED_RGN_CROSS){
						m_nSelMask=SEL_NORMAL;
						m_bCellAreaDown=TRUE;
						nRow=m_hitest.nRow;
						nCol=m_hitest.nCol;
					}else{
						//整表选择
						m_bSelectRow=TRUE;
						m_bSelectCol=TRUE;
						CELL cellT;
						//GetBeginCell(cellT);
						nRow=GetFixedRows();
						nCol=GetFixedCols();	
					}
					CELL cell(nRow,nCol);
					GetMasterCell(cell);
					if(m_currentCell.Row!=cell.Row ||
						m_currentCell.Col!=cell.Col){
						m_currentCell=cell;
						GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
						if(m_ptrDDraw && !bRedrawAll)
							m_ptrDDraw->DrawFocusCell(NULL);
						else
							ReDraw();
						//
						//TrackRangeSel(nRow,nCol);
						m_prevFocusCell=m_currentCell;
					}else{
						TrackRangeSel(nRow,nCol);
						GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
						m_prevFocusCell=m_currentCell;
					}
					if(m_hitest.nHitest==AREA_FIXED_RGN_CROSS){
						m_nSelMask=SEL_ALL;
						m_CurrRange.m_posRow.m_begin=nRow;
						m_CurrRange.m_posCol.m_begin=nCol;
						m_CurrRange.m_posRow.m_end=GetRows()-1;
						m_CurrRange.m_posCol.m_end=GetCols()-1;
						m_currentCell=cell;
						if(m_ptrDDraw){
							m_ptrDDraw->DrawSelectRange(NULL);
							m_OldRange=m_CurrRange;
						}
						m_prevFocusCell=m_currentCell;
					}
				}
			}
			break;
		case AREA_FIXED_RGN_HORZ:
			CLPlatform::SetCursor(IDC_CURRIGHT);
			//整行选择
			{
				m_nSelMask=SEL_ROW;
				m_bSelectRow=TRUE;
				m_bRowColSelDown=TRUE;
				LONG nRow=m_hitest.nRow;
				LONG nCol=GetFixedCols();
				CELL cell(nRow,nCol);
				GetMasterCell(cell);
				if(m_currentCell.Row!=cell.Row ||
					m_currentCell.Col!=cell.Col){
					m_currentCell=cell;
					GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
					if(m_ptrDDraw)
						m_ptrDDraw->DrawFocusCell(NULL);
					else
						ReDraw();
					//如果旧范围是
					TrackRangeSel(nRow,nCol);
					m_prevFocusCell=m_currentCell;
				}else{
					TrackRangeSel(nRow,nCol);
					GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
					m_prevFocusCell=m_currentCell;
				}
				m_CurrRange.m_posRow.m_begin=nRow;
				m_CurrRange.m_posCol.m_begin=nCol;
				m_CurrRange.m_posRow.m_end=nRow;
				m_CurrRange.m_posCol.m_end=GetCols()-1;
				m_currentCell=cell;
				if(m_ptrDDraw){
					m_ptrDDraw->DrawSelectRange(NULL);
					m_OldRange=m_CurrRange;
				}
				m_prevFocusCell=m_currentCell;
			}
			break;
		case AREA_FIXED_RGN_VERT:
			CLPlatform::SetCursor(IDC_CURDOWN);
			//整列选择
			{
				m_nSelMask=SEL_COL;
				m_bSelectCol=TRUE;
				m_bRowColSelDown=TRUE;
				LONG nRow=GetFixedRows();
				LONG nCol=m_hitest.nCol;
				CELL cell(nRow,nCol);
				GetMasterCell(cell);
				if(m_currentCell.Row!=cell.Row ||
					m_currentCell.Col!=cell.Col){
					m_currentCell=cell;
					GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
					if(m_ptrDDraw)
						m_ptrDDraw->DrawFocusCell(NULL);
					else
						ReDraw();
					//如果旧范围是
					TrackRangeSel(nRow,nCol);
					m_prevFocusCell=m_currentCell;
				}else{
					TrackRangeSel(nRow,nCol);
					GetCellRange(m_currentCell.Row,m_currentCell.Col,m_CurrRange);
					m_prevFocusCell=m_currentCell;
				}
				m_CurrRange.m_posRow.m_begin=nRow;
				m_CurrRange.m_posCol.m_begin=nCol;
				m_CurrRange.m_posRow.m_end=GetRows()-1;
				m_CurrRange.m_posCol.m_end=nCol;
				m_currentCell=cell;
				if(m_ptrDDraw){
					m_ptrDDraw->DrawSelectRange(NULL);
					m_OldRange=m_CurrRange;
				}
				m_prevFocusCell=m_currentCell;
			}
			break;
		case AREA_RANGE_BORDER:
			//当前范围边框
			m_bRangeBorderDown=TRUE;
			{
				m_TrackOld.ClearRange();
				GetCurrentRange(m_TrackCurr);
				if(m_ptrDDraw){
					m_ptrDDraw->DrawDragRange(NULL,m_TrackOld,m_TrackCurr);
					m_TrackOld=m_TrackCurr;
				}
				m_ptTrack.x=m_hitest.nCol;
				m_ptTrack.y=m_hitest.nRow;
			}
			break;
		case AREA_RANGE_CORNER:
			CLPlatform::SetCursor(IDC_CUR_CROSS);
			//当前范围可拖动角
			
			break;
		case AREA_GRAPHICS:
			break;
		}
	}
}
void CLSheet::OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=0;
	if(m_lpOldObj){
		((IMouseEvent*)m_lpOldObj)->OnLButtonUp(m_oldID,nstatus);
		m_lpOldObj=NULL;
	}else{
		if(m_bTrackRowSize){
			m_bTrackRowSize=FALSE;
			m_nTrackOffset=0;
			LONG offset=m_ptTrack.y-m_oldPs;
			DrawTrack(TRUE,FALSE);
			if(m_nRowColID>=0){
				SetRowHeight(m_nRowColID,GetRowHeight(m_nRowColID)+offset);
			}
			ReDraw();
		}else if(m_bTrackColSize){
			m_bTrackColSize=FALSE;
			m_nTrackOffset=0;
			LONG offset=m_ptTrack.x-m_oldPs;
			DrawTrack(FALSE,FALSE);
			if(m_nRowColID>=0){
				SetColWidth(m_nRowColID,GetColWidth(m_nRowColID)+offset);
			}
			ReDraw();
		}else if(m_bRangeBorderDown){
			//拖动范围
			if(m_ptrDDraw){
				
				if(!(m_CurrRange==m_TrackCurr)){
					CopyRange(m_CurrRange,m_TrackCurr);
					ReDraw();
					m_OldRange=m_CurrRange;
				}else{
					m_TrackOld.ClearRange();
					m_ptrDDraw->DrawDragRange(NULL,m_TrackOld,m_TrackCurr);
				}
			}
		}
	}
	ClearFlags();
}
void CLSheet::OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=2;
	if(m_lpOldObj)
		((IMouseEvent*)m_lpOldObj)->OnRButtonDown(m_oldID,nstatus);
}
void CLSheet::OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=0;
	if(m_lpOldObj)
		((IMouseEvent*)m_lpOldObj)->OnRButtonUp(m_oldID,nstatus);
}
void CLSheet::OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=4;
	if(m_lpOldObj)
		((IMouseEvent*)m_lpOldObj)->OnMButtonDown(m_oldID,nstatus);
}
void CLSheet::OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	m_hitest.nButton=0;
	if(m_lpOldObj)
		((IMouseEvent*)m_lpOldObj)->OnMButtonUp(m_oldID,nstatus);
}
void CLSheet::OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus)
{
	if(m_lpOldObj)
		((IMouseEvent*)m_lpOldObj)->OnMouseWheel(m_oldID,nstatus);
	else if(idArea==AREA_TABLE)
		ScrollVert(NULL,nstatus.nParam?3:-3);
}
void CLSheet::OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus)
{
	if(m_bGraphicsDown){
		MOUSESTATUS status=nstatus;
		if(m_lpOldObj)
			((IMouseEvent*)m_lpOldObj)->OnMouseMove(m_oldID,status);
	}else if(m_lpOldObj){
		((IMouseEvent*)m_lpOldObj)->OnMouseOut(m_oldID,nstatus);
		m_lpOldObj=NULL;
	}
}
BOOL CLSheet::GetRect(LONG idArea,RECT& rct)
{
	switch(idArea){
	case AREA_TABLE:
		{
			RECT rctClip;
			GetClientRect(rctClip);
			GetTableRect(rct);
			rct.right=rctClip.right;
			rct.bottom=rctClip.bottom;
			rct.left+=m_posStart.x;
			rct.right+=m_posStart.x;
			rct.top+=m_posStart.y;
			rct.bottom+=m_posStart.y;
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;
}
BOOL CLSheet::GetRgn(LONG idArea,HRGN& hrgn)
{
	return TRUE;
}
LPIDAREA CLSheet::GetAreaIDs()
{
	if(m_ptrArea)return m_ptrArea;
	m_ptrArea=new IDAREA();
	m_ptrArea->lngID=AREA_TABLE;
	return m_ptrArea;
}
BOOL CLSheet::IsActive()
{
	return m_bActive;
}
void CLSheet::IsActive(BOOL val)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	m_bActive=val;
}

void CLSheet::SetBeginPos(const POINT &pt)
{
	m_posStart=pt;
}
LPTSTR CLSheet::GetSheetName()
{
	return m_ptrName;
}
void CLSheet::SetSheetName(LPTSTR ptrName)
{
	if(m_ptrName){
		delete[] m_ptrName;
		m_ptrName=NULL;
	}
	if(ptrName && *ptrName!='\0'){
		LONG len=strlen(ptrName);
		m_ptrName=new char[len+1];
		strcpy(m_ptrName,ptrName);
	}
}

void CLSheet::ClearFlags()
{
	m_bRangeBorderDown=FALSE;
	m_bRangeCornerDown=FALSE;
	m_bCellAreaDown=FALSE;
	m_bTrackColSize=FALSE;
	m_bTrackRowSize=FALSE;
	m_bRowColSelDown=FALSE;
	m_bGraphicsDown=FALSE;
}

void CLSheet::SetDDrawObj(IDirectDraw *ptrObj)
{
	m_ptrDDraw=ptrObj;
}
void CLSheet::TrackRangeSel(LONG nRow,LONG nCol,BOOL bCombinRgn)
{
	CELL cell;
	GetCurrentCell(cell);
	RANGE	range;
	BOOL bCell=FALSE;
	GetCellRange(nRow,nCol,range);
	RANGE rgn;
	GetCellRange(cell.Row,cell.Col,rgn);
	BOOL bDraw=TRUE;
	bCell=(range==rgn);
	if(m_hitest.nCol==4)
		int iii=0;
	if(m_hitest.nCol==3)
		int iii=0;
	if(!(range==m_CurrRange)){
		if(bCombinRgn)
			GetCombinRange(rgn,range);
		else
			rgn.CombinRange(range);
		bDraw=!(m_CurrRange==rgn);
		m_CurrRange=rgn;
	}
	if(!(m_CurrRange==m_OldRange)){
		//通过双缓存画选择区域 ********
		//if(m_ptrDDraw)
		//	m_ptrDDraw->DrawSelectRange(NULL,TRUE,bCell);
		//else
		if(bDraw)
			ReDraw();
		else
			int ii=0;
		if(bCell)
			ClearOldRange();
		else
			m_OldRange=m_CurrRange;
	}
}


BOOL CLSheet::IsResizeInFixedCell()
{
	return m_bResizeFixedCellOnly;
}
void CLSheet::IsResizeInFixedCell(BOOL bVal)
{
	m_bResizeFixedCellOnly=bVal;
}
//序列化接口
BOOL CLSheet::OnSerial(CLSerial& ar)
{
	BOOL bret=TRUE;
	if(CLGrid::OnSerial(ar)){
		//图层对象
		//m_graphics
		//回调函数链
		LONG val;
		if(ar.isLoading()){
			//读取操作
			ar>>m_bActive;
			ar>>m_bCanOperate;
			ar>>m_bProtected;
			ar>>m_bResizeFixedCellOnly;
			ar>>m_bSelectCol;
			ar>>m_bSelectRow;
			ar>>m_nRowColID;
			ar>>m_nSelMask;
			ar>>m_nSheetLineStyle;
			val=ar.GetValue();
			if(m_ptrName){
				delete[] m_ptrName;	
			}
			m_ptrName=new char[val+1];
			ar>>m_ptrName;

			val=ar.GetValue();
			if(m_strPass){
				delete[] m_strPass;	
			}
			m_strPass=new char[val+1];
			ar>>m_strPass;
		}else{
			//保存操作
			ar<<m_bActive;
			ar<<m_bCanOperate;
			ar<<m_bProtected;
			ar<<m_bResizeFixedCellOnly;
			ar<<m_bSelectCol;
			ar<<m_bSelectRow;
			ar<<m_nRowColID;
			ar<<m_nSelMask;
			ar<<m_nSheetLineStyle;
			ar<<m_ptrName;
			ar<<m_strPass;
		}
	}
	return bret;
}
CLDrawItemBase* CLSheet::GetFocusItem()
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	return m_graphics.GetFocus();
}
BOOL CLSheet::OnObjectMove(CELL& cellBegin,CELL& cellEnd,POINT& ptOffset,
		POINT& ptEndOffset,const SIZE& size,LONG cx,LONG cy,RECT& rctAll)
{
	ASSERT_CELL(cellBegin);
	RANGE range;
	ptOffset.x+=cx;
	ptOffset.y+=cy;
	GetEndPos(cellBegin,ptOffset,size,cellEnd,ptEndOffset);
	LONG rowoff=(GetFixedRows()-cellBegin.Row);
	if(rowoff>0){
		cellBegin.Row+=rowoff;
		cellEnd.Row+=rowoff;
	}
	LONG coloff=(GetFixedCols()-cellBegin.Col);
	if(coloff>0){
		cellBegin.Col+=coloff;
		cellEnd.Col+=coloff;
	}
	rowoff=(cellEnd.Row-m_Rows+1);
	if(rowoff>0){
		cellEnd.Row-=rowoff;
		cellBegin.Row-=rowoff;

	}
	coloff=(cellEnd.Col-m_Cols+1);
	if(coloff>0){
		cellEnd.Col-=coloff;
		cellBegin.Col-=coloff;
	}
	range.m_posRow.m_begin=cellBegin.Row;
	range.m_posRow.m_end=cellEnd.Row;
	range.m_posCol.m_begin=cellBegin.Col;
	range.m_posCol.m_end=cellEnd.Col;
	if(GetPanRect(range,ptOffset,size,rctAll)){
		rctAll.left+=cx;
		rctAll.right+=cx;
		rctAll.top+=cy;
		rctAll.bottom+=cy;
		return TRUE;
	}
	return FALSE;
}
void CLSheet::OnObjectSize(CELL& cellEnd,POINT& ptEndOffset,
						   LONG cx,LONG cy,RECT& rctAll)
{
	
}
BOOL CLSheet::GetPanRect(RANGE& range,POINT ptOffset,const SIZE& size,RECT& rct)
{
	RECT rctAll,rctVisible;
	BOOL ret=FALSE;
	if(GetRangeRect(range,rctAll,rctVisible,rct,0)){
		rct.left+=ptOffset.x;
		rct.right=rct.left+size.cx;
		rct.top+=ptOffset.y;
		rct.bottom=rct.top+size.cy;
		ret=TRUE;
	}else{
		CLPlatform::ClearRect(rct);
	}
	return ret;
}
BOOL CLSheet::call_function(const string& name,const tag_func_param_value_chain* param
				   ,tag_result_type type,tag_computer_result& ret,string& error,LPVOID pparam){
	return FALSE;
}
#define UPPER(ch) \
	((ch)>='a' && (ch)<='z'?(ch)-('a'-'A'):ch)
BOOL CLSheet::get_macro_define(const string& name,tag_computer_result& ret
							   ,string& error,LPVOID pparam){
	string strT="",strN="";
	if(name.size()<=0)return FALSE;
	char ch,*ptr=NULL;
	int i=0,j=0;
	long nrow=0,ncol=0;
	for(ch=UPPER(name.at(i))
		;'A'<=ch && ch<='Z';i++,ch=UPPER(name.at(i))){
		strT+=ch;
	}
	if(i<1)return FALSE;
	strN=name.substr(i);
	//得到列值
	for(i=strT.size()-1;i>=0;i--,j++){
		ncol+=(strT.at(i)-'A')*pow(26,j);
	}
	ncol+=1;
	//
	if(!CLPlatform::IsNumeric(strN.c_str())){
		//不是数值
		return FALSE;
	}
	nrow=strtol(strN.c_str(),&ptr,10);
	if(!IsFormulaCell(nrow,ncol)){
		ptr=GetCellText(nrow,ncol);
	}else{
		//因该得到公式的值
		ptr=GetFormulaValue(nrow,ncol);
	}
	if(ptr){
		if(!CLPlatform::IsNumeric(ptr)){
#ifdef _LINK_DYN_TYPE_
			if(ret.type==type_result_string && ret.str_value)
				delete ret.str_value;
			ret.type=type_result_string;
			ret.str_value=new string(ptr);
#else
			string strT="";
			strT+=ptr;
			ret.set_string(&strT);
#endif
		}else{
#ifdef _LINK_DYN_TYPE_
			if(ret.type==type_result_string && ret.str_value)
				delete ret.str_value;
			ret.type=type_result_number;
			ret.dbl_value=strtod(ptr,&ptr);
#else
			ret.set_number(strtod(ptr,&ptr));
#endif
		}
	}else{
#ifdef _LINK_DYN_TYPE_
		if(ret.type==type_result_string && ret.str_value)
			delete ret.str_value;
		ret.type=type_result_number;
		ret.dbl_value=0;
#else
		ret.set_number(0);
#endif
	}
	return TRUE;
}