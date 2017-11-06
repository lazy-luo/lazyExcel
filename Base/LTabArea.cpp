//////////////////////////////////////////////////////////////////////
//@模块		 ：Tab对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-08
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LTabArea.h"
#include "../LComm/LMemDC.h"
#include "../LComm/LClipDC.h"
#include "../Public/LBookPublic.h"

#define TAB_AREA_CLIENT		11
#define TAB_AREA_FIRSTBT	12
#define TAB_AREA_PREVBT		13
#define TAB_AREA_NEXTBT		14
#define TAB_AREA_LASTBT		15
#define TAB_AREA_SPLICT		16
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLTabArea::CLTabArea():MAP_PAGEITEM(17,40),m_nCurrentPageNO(-1),m_bVisible(TRUE),m_nPageCount(0),
	m_bFitLeft(TRUE),m_nLeftBeginCol(-1),m_nRightEndCol(-1),m_nBeginLeft(0),
	m_nBeginRight(0),m_bHasSp(TRUE),m_nSplitWidth(TAB_SPLICT_WIDTH),m_clrBk(GetSysColor(COLOR_BTNFACE)),m_clrFore(COLOR_FOREDATA),
	m_clrBkFocus(COLOR_BKGRD),m_clrBorder(RGB(128,128,128)),m_clrForeFocus(COLOR_FOCUSE_FIXED_FORE),
	m_bEnablePre(TRUE),m_bEnableFirst(TRUE),m_bEnableNext(TRUE),m_bEnableLast(TRUE),m_nBeginColWidth(0),
	m_bChangePage(FALSE),m_ptrArea(NULL),m_ptrDrawHelp(NULL),m_bDownPre(FALSE),m_bDownFirst(FALSE),
	m_bDownNext(FALSE),m_bDownLast(FALSE),m_bRaisePre(TRUE),m_bRaiseFirst(TRUE),m_bRaiseNext(TRUE),
	m_bRaiseLast(TRUE),m_bDownSplict(FALSE),m_ptrSplict(NULL)
{
	CLPlatform::ClearRect(m_rectArea);
	CLPlatform::ClearRect(m_rctClient);
	CLPlatform::ClearRect(m_rctBtArea);
	CLPlatform::ClearRect(m_rctSplit);
	CLPlatform::ClearPoint(m_posStart);
	CLPlatform::ClearPoint(m_posStartDraw);
	CLPlatform::ClearSize(m_offSet);
}

CLTabArea::~CLTabArea()
{
	if(m_ptrArea)
		delete m_ptrArea;
	ClearAll();
}
BOOL CLTabArea::isVisible()
{
	return m_bVisible;
}
void CLTabArea::isVisible(BOOL bVal)
{
	m_bVisible=bVal;
}
CLPageItem* CLTabArea::AddPage(LPVOID ptrData, LONG nIndex)
{
	ASSERT(nIndex>0 && (m_nPageCount>0?nIndex<=m_nPageCount+1:nIndex==1));
	INDEX index;
	m_nPageCount++;
	index.Index=m_nPageCount;
	if(nIndex<=m_nCurrentPageNO)
		m_nCurrentPageNO++;
	if(m_nCurrentPageNO<0 && m_nLeftBeginCol<0 && m_nRightEndCol<0){
		m_nLeftBeginCol=1;
		m_nCurrentPageNO=1;
		m_nRightEndCol=1;
	}
	CLPageItem* pItem;
	if (Lookup(index, pItem,TRUE)){
		MovePageToB(nIndex,m_nPageCount);
		pItem=GetPage(nIndex);
		pItem->ClearToDefault();
		return pItem;
	}else
		return NULL;
}

BOOL CLTabArea::RemovePage(LONG nIndex)
{
	if(m_nPageCount<nIndex || nIndex<=0 || m_nPageCount<2)return TRUE;
	INDEX index;
	index.Index=m_nPageCount;
	MovePageToF(nIndex,m_nPageCount);
	m_nPageCount--;
	if(m_nCurrentPageNO>m_nPageCount)
		m_nCurrentPageNO=m_nPageCount;
	RemoveKey(index);
	return TRUE;
}

void CLTabArea::ClearAll()
{
	RemoveAll();
}

CLPageItem* CLTabArea::GetPage(LONG nIndex)
{
	CLPageItem* ptrItem;
	INDEX key;
	key.Index = nIndex;
	if (Lookup(key,ptrItem))
		return ptrItem;
	else
		return NULL;
}

void CLTabArea::SetPageCaption(LONG nIndex, LPTSTR ptrV)
{
	CLPageItem* ptrItem=GetPage(nIndex);
	if(ptrItem){
		ptrItem->SetCaption(ptrV);
	}
}
BOOL CLTabArea::OnSerial(CLSerial& ar)
{
	CLPageItem* ptrItem;
	char *ptrV=NULL;
	LONG val;
	if(ar.isLoading()){
		//加载
		
		ar>>m_bEnableFirst;
		ar>>m_bEnableLast;
		ar>>m_bEnableNext;
		ar>>m_bEnablePre;
		ar>>m_bFitLeft;
		ar>>m_bHasSp;
		ar>>m_bVisible;
		ar>>m_clrBk;
		ar>>m_clrBkFocus;
		ar>>m_clrBorder;
		ar>>m_clrFore;
		ar>>m_clrForeFocus;
		ar>>m_nBeginColWidth;
		ar>>m_nBeginLeft;
		ar>>m_nBeginRight;
		ar>>m_nCurrentPageNO;
		ar>>m_nLeftBeginCol;
		ar>>m_nPageCount;
		ar>>m_nRightEndCol;
		ar>>m_nSplitWidth;
		ar>>m_rctBtArea;
		ar>>m_rctClient;
		ar>>m_rectArea;
		
		for(int index=1;index<=m_nPageCount;index++){
			val=ar.GetValue();
			ptrV=new char[val+1];
			ar>>ptrV;
			ptrItem=GetPage(index);
			if(ptrItem){
				ptrItem->SetCaption(ptrV);
			}
			delete[] ptrV;
		}
		
	}else{
		
		ar<<m_bEnableFirst;
		ar<<m_bEnableLast;
		ar<<m_bEnableNext;
		ar<<m_bEnablePre;
		ar<<m_bFitLeft;
		ar<<m_bHasSp;
		ar<<m_bVisible;
		ar<<m_clrBk;
		ar<<m_clrBkFocus;
		ar<<m_clrBorder;
		ar<<m_clrFore;
		ar<<m_clrForeFocus;
		ar<<m_nBeginColWidth;
		ar<<m_nBeginLeft;
		ar<<m_nBeginRight;
		ar<<m_nCurrentPageNO;
		ar<<m_nLeftBeginCol;
		ar<<m_nPageCount;
		ar<<m_nRightEndCol;
		ar<<m_nSplitWidth;
		ar<<m_rctBtArea;
		ar<<m_rctClient;
		ar<<m_rectArea;
		for(int index=1;index<=m_nPageCount;index++){
			ptrItem=GetPage(index);
			ptrV=NULL;
			if(ptrItem){
				ptrV=ptrItem->GetCaption();
			}
			ar<<ptrV;
		}
	}
	return TRUE;
}
LPTSTR CLTabArea::GetPageCaption(LONG nIndex)
{
	CLPageItem* ptrItem=GetPage(nIndex);
	if(ptrItem){
		return ptrItem->GetCaption();
	}
	return NULL;
}

void CLTabArea::SetPageData(LONG nIndex, LPVOID ptrV)
{
	CLPageItem* ptrItem=GetPage(nIndex);
	if(ptrItem){
		ptrItem->SetData(ptrV);
	}
}

LPVOID CLTabArea::GetPageData(LONG nIndex)
{
	CLPageItem* ptrItem=GetPage(nIndex);
	if(ptrItem){
		return ptrItem->GetData();
	}
	return NULL;
}

LONG CLTabArea::GetCurrentPageNO()
{
	return m_nCurrentPageNO;
}

BOOL CLTabArea::SetCurrentPageNO(LONG nVal)
{
	if(nVal>0 && nVal<=m_nPageCount+1){
		m_bChangePage=(m_nCurrentPageNO!=nVal);
		m_nCurrentPageNO=nVal;
		return TRUE;
	}
	return FALSE;
}

void CLTabArea::DrawPages(LPDRAWER lpDrawer)
{
	if(NULL==lpDrawer || (!m_bVisible))return;
	
	m_offSet.cx=lpDrawer->m_lpRect->left;
	m_offSet.cy=lpDrawer->m_lpRect->top;
	//CLClipDC hDC(lpDrawer->m_hDC,*lpDrawer->m_lpRect);
//#ifdef _LZY_USE_DOUBLE_BUFF_
	RECT rctAll=*lpDrawer->m_lpRect;
	m_posStartDraw.x=m_posStart.x+rctAll.left;
	m_posStartDraw.y=m_posStart.y+rctAll.top;
	CLMemDC hDC(lpDrawer->m_hDC,*lpDrawer->m_lpRect);
	HDC hOldDC=lpDrawer->m_hDC;
	lpDrawer->m_hDC=hDC;
//#endif
	m_rectArea=*(lpDrawer->m_lpRect);
	DRAWER cellDrawer=*lpDrawer;

	RECT rct=*(cellDrawer.m_lpRect);
	//填充背景先
	BOOL bHasSplitBar=(lpDrawer->m_nStyle==1);
	CLDrawer::FillSolidRect(lpDrawer->m_hDC,&rct,m_clrBk);
	CLDrawer::Draw3dRect(lpDrawer->m_hDC,&rct,m_clrBorder,m_clrBorder);
	//更新数据
	RefreshStatus(m_rectArea);
	//画客户区
	DrawClient(cellDrawer);
	//画按钮功能区
	DrawBtArea(cellDrawer);
	//画分割区
	DrawSplitArea(cellDrawer);
//#ifdef _LZY_USE_DOUBLE_BUFF_
	lpDrawer->m_hDC=hOldDC;
	*lpDrawer->m_lpRect=rctAll;
//#endif
}

LONG CLTabArea::GetMaxPageNO()
{
	return m_nPageCount;
}

void CLTabArea::MovePageToF(LONG beginIndex,LONG endIndex)
{
	if(m_nPageCount<=0)return;
	ASSERT(beginIndex>0 && beginIndex<=m_nPageCount 
		&& endIndex>0 && endIndex<=m_nPageCount);
	for(LONG index=beginIndex+1;index<=endIndex;index++){
		ReplaceValue(index,index-1);
	}
}

void CLTabArea::MovePageToB(LONG nbeginIndex,LONG nendIndex)
{
	if(m_nPageCount<=0)return;
	ASSERT(nbeginIndex>0 && nbeginIndex<=m_nPageCount 
		&& nendIndex>0 && nendIndex<=m_nPageCount);
	for(LONG index=nendIndex;index>nbeginIndex;index--){
		ReplaceValue(index-1,index);
	}
}

BOOL CLTabArea::ReplaceValue(LONG indexSrc, LONG indexDst)
{
	ASSERT(indexSrc>0 && indexSrc<=m_nPageCount 
		&& indexDst>0 && indexDst<=m_nPageCount);
	CLPageItem* ptrSrc=GetPage(indexSrc);
	CLPageItem* ptrDst=GetPage(indexDst);
	ASSERT(ptrSrc!=NULL && ptrDst!=NULL);
	*ptrDst=*ptrSrc;
	return TRUE;
}

void CLTabArea::RefreshStatus(const RECT& rctAll)
{
	//刷新区域
	GetClientRect(rctAll,m_rctClient);
	GetBtAreaRect(rctAll,m_rctBtArea);
	GetSplitRect(rctAll,m_rctSplit);
	if(m_nCurrentPageNO==m_nLeftBeginCol){
		m_bFitLeft=TRUE;
	}else if(m_nCurrentPageNO==m_nRightEndCol){
		m_bFitLeft=FALSE;
	}
}
void CLTabArea::MoveOffset(LONG nValue)
{
	if(nValue==0)return;
	LONG nLen;
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	LONG nOffP=(m_rctClient.bottom-m_rctClient.top)/4;
	if(nValue>0){
		//往右边移
		LONG deff=(m_nBeginLeft+nValue);
		if(deff>=0){
			if(m_nLeftBeginCol>1){
				RECT rctR;
				GetItemTopLine(m_nLeftBeginCol-1,rctR);
				nLen=(rctR.right-rctR.left-nOff);
				m_nLeftBeginCol--;
				m_nBeginLeft=deff-nLen-nOff;
			}else{
				m_nBeginLeft=0;
			}
		}else{
			m_nBeginLeft+=nValue;
		}
	}else{
		//往左边移
		LONG deff=(m_nBeginLeft+nValue);
		RECT rctR;
		GetItemTopLine(m_nLeftBeginCol,rctR);
		nLen=(rctR.right-rctR.left-nOff);
		deff+=(nLen);
		if(deff>=0)
			m_nBeginLeft+=(nValue);
		else{
			while(deff<0){
				if(m_nLeftBeginCol<m_nPageCount){
					m_nLeftBeginCol++;
					GetItemTopLine(m_nLeftBeginCol,rctR);
					nLen=(rctR.right-rctR.left-nOff);
					deff+=nLen;
				}else{
					deff=nLen;
					break;
				}
			}
			m_nBeginLeft=(deff-nLen-nOff);
		}
	}
}
void CLTabArea::ScrollHorz(LONG nValue, BOOL bPixel)
{
	MoveOffset(nValue);
	ReDraw(FALSE);
}
void CLTabArea::SetFitLastPage(LONG index)
{
	LONG nBeginLeft=GetItemBeginLeft(index)+m_nBeginLeft+m_rctClient.left;
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	LONG nDef=m_rctClient.right-(nBeginLeft+GetItemLength(index)+nOff);
	ScrollHorz(nDef);
}
void CLTabArea::GetClientRect(const RECT &rctClip, RECT &rct)
{
	rct=rctClip;
	rct.left+=(4*(rctClip.bottom-rctClip.top));//+1;
	rct.right-=(m_bHasSp?m_nSplitWidth:0);
	if(rct.left>rctClip.right-m_nSplitWidth)
		rct.left=rctClip.right-m_nSplitWidth;
	if(rct.right>rctClip.right-m_nSplitWidth)
		rct.right=rctClip.right-m_nSplitWidth;
}

BOOL CLTabArea::isEmptyRect(const RECT &rct)
{
	return (rct.left==0 && rct.right==0 && rct.bottom==0 && rct.top==0);
}

void CLTabArea::GetBtAreaRect(const RECT &rctClip, RECT &rct)
{
	rct=rctClip;
	rct.right=rct.left+(4*(rctClip.bottom-rctClip.top));//+1;
	if(rct.right>rctClip.right-m_nSplitWidth)
		rct.right=rctClip.right-m_nSplitWidth;
}

void CLTabArea::GetSplitRect(const RECT &rctClip, RECT &rct)
{
	rct=rctClip;
	rct.left=rct.right-m_nSplitWidth;
}

void CLTabArea::DrawClient(const DRAWER& cellDrawer)
{
	CLClipDC clip(cellDrawer.m_hDC,m_rctClient);

	LONG	nRightPos=m_rctClient.right-m_rctClient.left,nLenth=0;
	CLPageItem* ptrItem=NULL;
	HRGN hrgn=NULL;
	BOOL bFocus;
	RECT rctClip;
	BOOL bFind=FALSE,bOK=FALSE;
	LONG	nXpos=m_nBeginLeft;
	POINT pt[6];
	LONG nLen;
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	for(LONG index=m_nLeftBeginCol;index<=m_nPageCount/*m_nRightEndCol*/;index++){
		ptrItem=GetPage(index);
		ASSERT(ptrItem!=NULL);
		if(GetRegionPoints(index,rctClip,nLenth,pt,nLen,bFocus)){
			DrawAItem(cellDrawer,pt,nLen,rctClip,ptrItem->GetCaption(),bFocus);
		}
		nXpos+=(nLenth+nOff);
		if(nXpos>nRightPos-nOff){
			m_nRightEndCol=index;
			bFind=TRUE;
			break;
		}
	}
	bOK=nXpos>=nRightPos-nOff;
	if(!bFind)
		m_nRightEndCol=m_nPageCount;
	
	m_bEnableNext=m_nLeftBeginCol>1 || (m_nLeftBeginCol==1 && m_nBeginLeft<0);
	m_bEnableLast=m_bEnableNext;
	m_bEnablePre=m_nRightEndCol<m_nPageCount || bOK;
	m_bEnableFirst=m_bEnablePre;
	
	if(m_bChangePage)
		m_bChangePage=FALSE;
}

void CLTabArea::DrawBtArea(const DRAWER& cellDrawer)
{
	
	RECT rct=m_rctBtArea;
	//rct.right++;
	CLClipDC hDC(cellDrawer.m_hDC,rct);
	//rct.right--;
	
	LONG nWid=(m_rctClient.bottom-m_rctClient.top);
	RECT rctT=rct;
	rctT.top+=1;
	//rctT.left+=1;
	CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rctT,m_clrBk);
	
	rct=rctT;
	rctT.top=rctT.bottom-1;
	rctT.bottom=rctT.top+1;
	CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rctT,m_clrBorder);
	rctT=rct;

	rctT.right=rctT.left+nWid;
	if(m_bRaiseFirst || !m_bEnableFirst)
		CLDrawer::Draw3dRect(cellDrawer.m_hDC,&rctT,CLPlatform::GetSysColor(COLOR_3DHIGHLIGHT),
			CLPlatform::GetSysColor(COLOR_3DSHADOW));
	rct=rctT;
	if(!m_bRaiseFirst && m_bEnableFirst){
		rctT.top++;
		rctT.left++;
		rctT.right++;
		rctT.bottom++;
	}
	CLDrawer::DrawArrow(cellDrawer.m_hDC,rctT,RGB(10,10,10),ARROW_LEFT,TRUE,m_bEnableFirst);
	rctT=rct;

	rctT.left=rctT.right;
	rctT.right=rctT.left+nWid;
	if(m_bRaisePre || !m_bEnablePre)
		CLDrawer::Draw3dRect(cellDrawer.m_hDC,&rctT,
		CLPlatform::GetSysColor(COLOR_3DHIGHLIGHT)
		,CLPlatform::GetSysColor(COLOR_3DSHADOW));
	rct=rctT;
	if(!m_bRaisePre  && m_bEnablePre){
		rctT.top++;
		rctT.left++;
		rctT.right++;
		rctT.bottom++;
	}
	CLDrawer::DrawArrow(cellDrawer.m_hDC,rctT,RGB(10,10,10),ARROW_LEFT,FALSE,m_bEnablePre);
	rctT=rct;
	rctT.left=rctT.right;
	rctT.right=rctT.left+nWid;
	if(m_bRaiseNext  || !m_bEnableNext)
		CLDrawer::Draw3dRect(cellDrawer.m_hDC,&rctT,CLPlatform::GetSysColor(COLOR_3DHIGHLIGHT),
			CLPlatform::GetSysColor(COLOR_3DSHADOW));
	rct=rctT;
	if(!m_bRaiseNext  && m_bEnableNext){
		rctT.top++;
		rctT.left++;
		rctT.right++;
		rctT.bottom++;
	}
	CLDrawer::DrawArrow(cellDrawer.m_hDC,rctT,RGB(10,10,10),ARROW_RIGHT,FALSE,m_bEnableNext);
	rctT=rct;

	rctT.left=rctT.right;
	rctT.right=rctT.left+nWid;
	if(m_bRaiseLast || !m_bEnableLast)
		CLDrawer::Draw3dRect(cellDrawer.m_hDC,&rctT,CLPlatform::GetSysColor(COLOR_3DHIGHLIGHT),
			CLPlatform::GetSysColor(COLOR_3DSHADOW));
	rct=rctT;
	if(!m_bRaiseLast && m_bEnableLast){
		rctT.top++;
		rctT.left++;
		rctT.right++;
		rctT.bottom++;
	}
	CLDrawer::DrawArrow(cellDrawer.m_hDC,rctT,RGB(10,10,10),ARROW_RIGHT,TRUE,m_bEnableLast);
	rctT=rct;
}

void CLTabArea::DrawSplitArea(const DRAWER& cellDrawer)
{

	RECT rct=m_rctSplit;
	CLClipDC hDC(cellDrawer.m_hDC,rct);
	RECT rctT=rct;
	CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rct,m_clrBk);
	CLDrawer::DrawThickRect(cellDrawer.m_hDC,&rctT,CLPlatform::GetSysColor(COLOR_BTNFACE));
	
}

LONG CLTabArea::GetTextWidth(LPTSTR ptrTxt)
{
	return CLDrawer::GetTextWidth(ptrTxt)+4;
}

BOOL CLTabArea::GetRegionPoints(LONG nIndex,RECT& clipRct,
		LONG& itemLen,POINT* pt,LONG& nLen,BOOL& bFocus)
{
	RECT rctClient=m_rctClient;
	
	LONG nOff=(rctClient.bottom-rctClient.top)/2;
	LONG nOffHalf=(rctClient.bottom-rctClient.top)/4;
	LONG nBeginLeft=GetItemBeginLeft(nIndex)+m_nBeginLeft+rctClient.left;
	LONG nWidth=GetItemLength(nIndex);
	LONG nDec=1;
	itemLen=nWidth;
	nLen=5;
	bFocus=FALSE;
	if(nBeginLeft>=0){
		//看看是不是当前焦点列
		if(nIndex==m_nCurrentPageNO){
			pt[0].x=nBeginLeft-nOff;
			pt[0].y=rctClient.top;
			
			pt[1].x=pt[0].x+nOff;
			pt[1].y=rctClient.bottom-nDec;
			
			pt[2].x=pt[1].x+nWidth;
			pt[2].y=pt[1].y;
			
			pt[3].x=pt[2].x+nOff;
			pt[3].y=pt[0].y;
			
			clipRct.left=pt[1].x;
			clipRct.right=pt[2].x;
			clipRct.top=pt[0].y;
			clipRct.bottom=pt[1].y;
			bFocus=TRUE;
			nLen=4;
		}else{
			if(nIndex==m_nCurrentPageNO+1){
				//焦点单元下一单元
				if(nIndex<m_nPageCount)
					nLen=6;
				pt[0].x=nBeginLeft;
				pt[0].y=rctClient.top;
				
				pt[1].x=pt[0].x-nOffHalf;
				pt[1].y=rctClient.bottom-nOff-nDec;
				
				pt[2].x=pt[0].x;
				pt[2].y=rctClient.bottom-nDec;
				
				pt[3].x=pt[2].x+nWidth;
				pt[3].y=pt[2].y;
				if(nIndex<m_nPageCount){
					pt[4].x=pt[3].x+nOffHalf;
					pt[4].y=pt[1].y;
					
					pt[5].x=pt[3].x;
					pt[5].y=pt[0].y;
				}else{
					pt[4].x=pt[3].x+nOff;
					pt[4].y=pt[0].y;
				}
				clipRct.left=pt[0].x;
				clipRct.right=pt[3].x;
				clipRct.top=pt[0].y;
				clipRct.bottom=pt[2].y;
			}else{
				//
				if(nIndex==m_nPageCount)
					nLen=4;
				pt[0].x=nBeginLeft-nOff;
				pt[0].y=rctClient.top;
				
				pt[1].x=pt[0].x+nOff;
				pt[1].y=rctClient.bottom-nDec;
				
				pt[2].x=pt[1].x+nWidth;
				pt[2].y=pt[1].y;
				
				if(nIndex<m_nPageCount){
					pt[3].x=pt[2].x+nOffHalf;
					pt[3].y=pt[2].y-nOff;
					pt[4].x=pt[2].x;
					pt[4].y=pt[0].y;
				}else{
					pt[3].x=pt[2].x+nOff;
					pt[3].y=pt[0].y;
				}
				clipRct.left=pt[1].x;
				clipRct.right=pt[2].x;
				clipRct.top=pt[0].y;
				clipRct.bottom=pt[1].y;
			}
		}
		return TRUE;
	}
	return FALSE;
}

LONG CLTabArea::GetItemBeginLeft(LONG nIndex)
{
	//if(nIndex<m_nLeftBeginCol || nIndex>m_nRightEndCol)return -1;
	LONG nRet=0;
	LONG nBeginCol=(m_nLeftBeginCol<nIndex?m_nLeftBeginCol:nIndex);
	LONG nEndCol=(m_nLeftBeginCol<nIndex?nIndex:m_nLeftBeginCol);
	for(LONG index=nBeginCol;index<nEndCol;index++){
		nRet+=GetItemLength(index);
	}
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	return nRet+nIndex*nOff;
}

LONG CLTabArea::GetItemLength(LONG nIndex)
{
	CLPageItem* ptr=GetPage(nIndex);
	return GetTextWidth(ptr?ptr->GetCaption():NULL);
}

void CLTabArea::DrawAItem(const DRAWER &cellDrawer, const POINT* pt,LONG nPtCount, 
						  RECT &rctTxt, LPTSTR ptrTxt,BOOL bFocus)
{
	HRGN hRgn=CLDrawer::CreatePolygonRgn(pt,nPtCount,WINDING);
	ASSERT(hRgn);
	HPEN hFramePen=NULL,hOldPen=NULL,hHiPen=NULL;
	hFramePen=CLDrawer::CreatePen(PS_SOLID,1,RGB(0,0,0));
	hHiPen=CLDrawer::CreatePen(PS_SOLID,1,m_clrBorder);
	if(bFocus){
		HBRUSH hBrush=CLDrawer::CreateSolidBrush(bFocus?m_clrBkFocus:m_clrBk);
		CLDrawer::FillRgn(cellDrawer.m_hDC,hRgn,hBrush);
		CLDrawer::DeleteBrush(hBrush);
	}
	CLDrawer::DeleteRgn(hRgn);
	POINT ptt;
	
	
	hOldPen=CLDrawer::SelectPen(cellDrawer.m_hDC,hHiPen);
	int index,indexLft;
	switch(nPtCount){
	case 4:
		indexLft=0;
		index=2;
		break;
	case 5:
		indexLft=0;
		index=2;
		if(pt[1].y!=pt[2].y){
			indexLft=1;
			index=3;
		}
		break;
	case 6:
		indexLft=1;
		index=3;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	if(!bFocus){
		CLDrawer::MoveToEx(cellDrawer.m_hDC,pt[index].x-1,pt[index].y,&ptt);
		CLDrawer::LineTo(cellDrawer.m_hDC,pt[index+1].x-1,pt[index+1].y);
		//CLDrawer::SelectPen(cellDrawer.m_hDC,hFramePen);
		HPEN hpenH=CLDrawer::CreatePen(PS_SOLID,1,RGB(255,255,255));
		CLDrawer::SelectPen(cellDrawer.m_hDC,hpenH);
		CLDrawer::MoveToEx(cellDrawer.m_hDC,pt[indexLft].x+1,pt[indexLft].y,&ptt);
		CLDrawer::LineTo(cellDrawer.m_hDC,pt[indexLft+1].x+1,pt[indexLft+1].y);
		CLDrawer::SelectPen(cellDrawer.m_hDC,hHiPen);
		CLDrawer::DeletePen(hpenH);
	}
	CLDrawer::SelectPen(cellDrawer.m_hDC,hFramePen);
	for(int i=0;i<nPtCount;i++){
		CLDrawer::MoveToEx(cellDrawer.m_hDC,pt[i].x,pt[i].y,&ptt);
		if(i<nPtCount-1){
			CLDrawer::LineTo(cellDrawer.m_hDC,pt[i+1].x,pt[i+1].y);
		}else{
			CLDrawer::LineTo(cellDrawer.m_hDC,pt[0].x,pt[0].y);
		}
	}
	CLDrawer::SelectPen(cellDrawer.m_hDC,hHiPen);
	CLDrawer::MoveToEx(cellDrawer.m_hDC,pt[index-1].x,pt[index].y,&ptt);
	CLDrawer::LineTo(cellDrawer.m_hDC,pt[index].x,pt[index].y);
	CLDrawer::MoveToEx(cellDrawer.m_hDC,pt[0].x,pt[0].y,&ptt);
	CLDrawer::LineTo(cellDrawer.m_hDC,pt[nPtCount-1].x,pt[nPtCount-1].y);

	CLDrawer::SelectPen(cellDrawer.m_hDC,hOldPen);
	CLDrawer::DeletePen(hFramePen);
	CLDrawer::DeletePen(hHiPen);

	int oldMod=CLDrawer::SetBkMode(cellDrawer.m_hDC,TRANSPARENT);
	LONG nAlign=DT_SINGLELINE|DT_CENTER|DT_VCENTER;
	LONG nLen=strlen(ptrTxt);
	m_Font.m_lf.lfWeight=(bFocus?FW_BOLD:FW_NORMAL);
	HFONT hFont=CLDrawer::CreateFontIndirect(&(m_Font.m_lf));
	HFONT hOld=(HFONT)CLDrawer::SelectFont(cellDrawer.m_hDC,hFont);
	CLDrawer::SetTextColor(cellDrawer.m_hDC,bFocus?m_clrForeFocus:m_clrFore);
	
	rctTxt.top+=2;
	CLDrawer::DrawText(cellDrawer.m_hDC,ptrTxt,nLen,&rctTxt,nAlign);
	
	CLDrawer::SelectFont(cellDrawer.m_hDC,hOld);
	CLDrawer::SetBkMode(cellDrawer.m_hDC,oldMod);
	CLDrawer::DeleteFont(hFont);
	
	if(bFocus){
		RECT rct;
		GetFocusTopLine(rct);
		rct.left++;
		CLDrawer::FillSolidRect(cellDrawer.m_hDC,&rct,m_clrBkFocus);
	}
	
}
void CLTabArea::SetSplictOwner(ISplictFace* ptrSplict)
{
	if(m_ptrSplict!=ptrSplict)
		m_ptrSplict=ptrSplict;
}
COLORREF CLTabArea::GetBkColor()
{
	return m_clrBk;
}

void CLTabArea::SetBkColor(COLORREF clr)
{
	m_clrBk=clr;
}

COLORREF CLTabArea::GetForeColor()
{
	return m_clrFore;
}

void CLTabArea::SetForeColor(COLORREF clr)
{
	m_clrFore=clr;
}

COLORREF CLTabArea::GetBorderColor()
{
	return m_clrBorder;
}

void CLTabArea::SetBorderColor(COLORREF clr)
{
	m_clrBorder=clr;
}

COLORREF CLTabArea::GetFocusBkColor()
{
	return m_clrBkFocus;
}

void CLTabArea::SetFocusBkColor(COLORREF clr)
{
	m_clrBkFocus=clr;
}

COLORREF CLTabArea::GetFocusForeColor()
{
	return m_clrForeFocus;
}

void CLTabArea::SetFocusForeColor(COLORREF clr)
{
	m_clrForeFocus=clr;
}

void CLTabArea::Test()
{
	CLPageItem* ptr=AddPage(NULL,1);
	ASSERT(ptr!=NULL);
	ptr->SetCaption("Sheet1");

	ptr=AddPage(NULL,2);
	ASSERT(ptr!=NULL);
	ptr->SetCaption("Sheet2");

	ptr=AddPage(NULL,3);
	ASSERT(ptr!=NULL);
	ptr->SetCaption("Sheet3");

	ptr=AddPage(NULL,4);
	ASSERT(ptr!=NULL);
	ptr->SetCaption("Sheet4");

	ptr=AddPage(NULL,5);
	ASSERT(ptr!=NULL);
	ptr->SetCaption("Sheet5");
}

void CLTabArea::GetFocusTopLine(RECT &rct)
{
	GetItemTopLine(m_nCurrentPageNO,rct);
}

LONG CLTabArea::GetTableIndex(POINT &pt)
{
	CLPageItem* ptrItem;
	HRGN hrgn=NULL;
	RECT rctClip;
	BOOL bFocus;
	LONG nLength;
	POINT ppt[6];
	LONG nLen;
	for(LONG index=m_nLeftBeginCol;index<=m_nPageCount;index++){
		ptrItem=GetPage(index);
		ASSERT(ptrItem!=NULL);
		
		if(GetRegionPoints(index,rctClip,nLength,ppt,nLen,bFocus)){
			hrgn=CLDrawer::CreatePolygonRgn(ppt,nLen,WINDING);
			if(hrgn){
				if(CLDrawer::PtInRegion(hrgn,pt.x,pt.y)){
					CLDrawer::DeleteRgn(hrgn);
					return index;
				}
				CLDrawer::DeleteRgn(hrgn);
			}
		}
	}
	return -1;
}

LPVOID CLTabArea::GetValue(LPVOID nVal)
{
	if(nVal){
		INDEX key;
		BOOL bFind=FALSE;
		CLPageItem ptrItem;
		POSITION pos = GetStartPosition();
		while (pos != NULL)
		{
			GetNextAssoc(pos, key, ptrItem);
			if(ptrItem.GetData()==nVal){
				bFind=TRUE;
				break;
			}
		}
		if(bFind)
			return nVal;
		else
			return NULL;
	}
	return NULL;
}
//得到当前起始单元开始位置
void CLTabArea::ResetBeginOfLeft()
{
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	if(m_bChangePage){
		//必须是更换了页
		RECT rct;
		BOOL bFind=FALSE;
		GetFocusTopLine(rct);
		if(rct.left<m_rctClient.left){
			//左边超界
			if(m_nLeftBeginCol>1){
				RECT rctL;
				GetItemTopLine(m_nLeftBeginCol-1,rctL);
				LONG nLen=rctL.right-rctL.left-nOff;
				m_nLeftBeginCol--;
				m_nBeginLeft=-nLen;
			}else
				m_nBeginLeft=0;
			//MoveOffset(m_rctClient.left-rct.left);			
		}else if(rct.right>m_rctClient.right){
			//右边超界
			MoveOffset(m_rctClient.right-rct.right);
			/*
			RECT rctR;
			GetItemTopLine(m_nRightEndCol,rctR);
			LONG nLen=rctR.right-m_rctClient.right;
			GetItemTopLine(m_nLeftBeginCol,rctR);
			nLen-=(rctR.right-rctR.left+m_nBeginLeft-nOff);
			for(LONG i=m_nLeftBeginCol+1;i<=m_nRightEndCol;i++){
				if(nLen<0){
					bFind=TRUE;
					if(i>1){
						m_nLeftBeginCol=i-1;
						m_nBeginLeft=-(nLen+rctR.right-rctR.left+nOff);
					}else{
						m_nLeftBeginCol=1;
						m_nBeginLeft=nLen;
					}
					break;
				}
				GetItemTopLine(i,rctR);
				nLen-=(rctR.right-rctR.left+nOff);
			}
			
			if(m_nBeginLeft>=-nOff && m_nLeftBeginCol>1){
				RECT rctL;
				
				GetItemTopLine(m_nLeftBeginCol-1,rctL);
				LONG nLen=rctL.right-rctL.left-nOff;
				m_nLeftBeginCol--;
				m_nBeginLeft-=(nLen-nOff);
			}
			*/
		}
	}
}

void CLTabArea::GetItemTopLine(LONG nIndex, RECT &rct)
{
	LONG nOff=(m_rctClient.bottom-m_rctClient.top)/2;
	LONG nBeginLeft=GetItemBeginLeft(nIndex)+m_nBeginLeft+m_rctClient.left;
	LONG nWidth=GetItemLength(nIndex);
	rct.left=nBeginLeft-nOff;
	rct.top=m_rctClient.top;
	rct.right=nBeginLeft+nWidth+nOff;
	rct.bottom=rct.top+1;
}

LONG CLTabArea::GetPageCount()
{
	return m_nPageCount;
}


void CLTabArea::OnMouseMove(LONG idArea,MOUSESTATUS& nstatus)
{
	switch(idArea){
	case TAB_AREA_CLIENT:
		if(nstatus.bMouseIN){
			POINT pt;
			pt.x=nstatus.posx-m_posStartDraw.x;
			pt.y=nstatus.posy-m_posStartDraw.y;
			nstatus.nParam=GetTableIndex(pt);
		}
		break;
	case TAB_AREA_FIRSTBT:
		if(nstatus.bMouseIN && m_bRaiseFirst && m_bDownFirst){
			m_bRaiseFirst=FALSE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_PREVBT:
		if(nstatus.bMouseIN && m_bRaisePre && m_bDownPre){
			m_bRaisePre=FALSE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_NEXTBT:
		if(nstatus.bMouseIN && m_bRaiseNext && m_bDownNext){
			m_bRaiseNext=FALSE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_LASTBT:
		if(nstatus.bMouseIN && m_bRaiseLast && m_bDownLast){
			m_bRaiseLast=FALSE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_SPLICT:
		CLPlatform::SetCursor(IDC_CURSIZE_EW);
		if(m_bDownSplict){
			LONG def=nstatus.posx-m_ptTrack.x;
			m_ptTrack.x=nstatus.posx;
			if(m_ptrSplict)
				m_ptrSplict->SplictChange(def);

		}
		break;
	}
}
void CLTabArea::OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	switch(idArea){
	case TAB_AREA_CLIENT:
		if(nstatus.nStatusParam==STATUS_FLAG_AUTO)
			SetCurrentPage(nstatus.nParam);
		break;
	case TAB_AREA_FIRSTBT:
		if(nstatus.bMouseIN && m_bEnableFirst){
			m_bDownFirst=TRUE;
			m_bRaiseFirst=FALSE;
			m_nRightEndCol=m_nPageCount;
			SetFitLastPage(m_nPageCount);
		}
		break;
	case TAB_AREA_PREVBT:
		if(nstatus.bMouseIN && m_bEnablePre){
			m_bDownPre=TRUE;
			m_bRaisePre=FALSE;
			ScrollHorz(-10,TRUE);
		}
		break;
	case TAB_AREA_NEXTBT:
		if(nstatus.bMouseIN && m_bEnableNext){
			m_bDownNext=TRUE;
			m_bRaiseNext=FALSE;
			ScrollHorz(10,TRUE);
		}
		break;
	case TAB_AREA_LASTBT:
		if(nstatus.bMouseIN && m_bEnableLast){
			m_bDownLast=TRUE;
			m_bRaiseLast=FALSE;
			m_nBeginLeft=0;
			m_nLeftBeginCol=1;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_SPLICT:
		if(nstatus.nStatusParam==STATUS_FLAG_AUTO){
			CLPlatform::SetCursor(IDC_CURSIZE_EW);
			m_bDownSplict=TRUE;
			m_ptTrack.x=nstatus.posx;
			m_ptTrack.y=nstatus.posy;
		}
		break;
	}
}
void CLTabArea::OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	switch(idArea){
	case TAB_AREA_FIRSTBT:
		m_bDownFirst=FALSE;
		m_bRaiseFirst=TRUE;
		ReDraw(FALSE);
	case TAB_AREA_PREVBT:
		m_bDownPre=FALSE;
		m_bRaisePre=TRUE;
		ReDraw(FALSE);
		break;
	case TAB_AREA_NEXTBT:
		m_bDownNext=FALSE;
		m_bRaiseNext=TRUE;
		ReDraw(FALSE);
		break;
	case TAB_AREA_LASTBT:
		m_bDownLast=FALSE;
		m_bRaiseLast=TRUE;
		ReDraw(FALSE);
		break;
	case TAB_AREA_SPLICT:
		m_bDownSplict=FALSE;
		break;
	}
}
void CLTabArea::OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	
}
void CLTabArea::OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	
}
void CLTabArea::OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	
}
void CLTabArea::OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	
}
void CLTabArea::OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus)
{
	
}
void CLTabArea::OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus)
{
	switch(idArea){
	case TAB_AREA_FIRSTBT:
		if(!m_bRaiseFirst && m_bDownFirst){
			m_bRaiseFirst=TRUE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_PREVBT:
		if(!m_bRaisePre && m_bDownPre){
			m_bRaisePre=TRUE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_NEXTBT:
		if(!m_bRaiseNext && m_bDownNext){
			m_bRaiseNext=TRUE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_LASTBT:
		if(!m_bRaiseLast && m_bDownLast){
			m_bRaiseLast=TRUE;
			ReDraw(FALSE);
		}
		break;
	case TAB_AREA_SPLICT:
		break;
	}
}
BOOL CLTabArea::GetRect(LONG idArea,RECT& rct)
{
	LONG nWid=(m_rctClient.bottom-m_rctClient.top);
	RECT rctT=m_rctBtArea;
	
	switch(idArea){
	case TAB_AREA_CLIENT:
		rct=m_rctClient;
		if(rct.left>rct.right)
			rct.left=rct.right;
		rct.left+=m_posStartDraw.x;
		rct.right+=m_posStartDraw.x;
		rct.top+=m_posStartDraw.y;
		rct.bottom+=m_posStartDraw.y;
		return TRUE;
		break;
	case TAB_AREA_FIRSTBT:
		rctT.right=rctT.left+nWid;
		if(rctT.right>m_rctBtArea.right)
			rctT.right=m_rctBtArea.right;
		break;
	case TAB_AREA_PREVBT:
		rctT.left+=nWid;
		rctT.right=rctT.left+nWid;
		if(rctT.right>m_rctBtArea.right)
			rctT.right=m_rctBtArea.right;
		break;
	case TAB_AREA_NEXTBT:
		rctT.left+=2*nWid;
		rctT.right=rctT.left+nWid;
		if(rctT.right>m_rctBtArea.right)
			rctT.right=m_rctBtArea.right;
		break;
	case TAB_AREA_LASTBT:
		rctT.left+=3*nWid;
		rctT.right=rctT.left+nWid;
		if(rctT.right>m_rctBtArea.right)
			rctT.right=m_rctBtArea.right;
		break;
	case TAB_AREA_SPLICT:
		rctT=m_rctSplit;
		break;
	}
	rctT.left+=m_posStartDraw.x;
	rctT.right+=m_posStartDraw.x;
	rctT.top+=m_posStartDraw.y;
	rctT.bottom+=m_posStartDraw.y;
	rct=rctT;
	return TRUE;
}
BOOL CLTabArea::GetRgn(LONG idArea,HRGN& hrgn)
{
	return TRUE;
}
LPIDAREA CLTabArea::GetAreaIDs()
{
	if(m_ptrArea)return m_ptrArea;
	m_ptrArea=new IDAREA();
	m_ptrArea->lngID=TAB_AREA_CLIENT;
	IDAREA* ptr=new IDAREA();
	m_ptrArea->ptrNext=ptr;
	ptr->lngID=TAB_AREA_FIRSTBT;
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=TAB_AREA_PREVBT;
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=TAB_AREA_NEXTBT;
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=TAB_AREA_LASTBT;
	ptr->ptrNext=new IDAREA();
	ptr=ptr->ptrNext;
	ptr->lngID=TAB_AREA_SPLICT; 
	return m_ptrArea;
}
void CLTabArea::ReDraw(BOOL bAll)
{
	if(bAll){
		if(m_ptrDrawHelp)
			m_ptrDrawHelp->ReDraw(bAll);
	}else{
		if(m_ptrSplict)
			m_ptrSplict->SplictChange(0);
		else if(m_ptrDrawHelp)
			m_ptrDrawHelp->ReDraw(bAll);
	}
}
void CLTabArea::SetRedrawHelp(IRedrawHelp* ptrDrawHelp)
{
	m_ptrDrawHelp=ptrDrawHelp;
}

void CLTabArea::SetCurrentPage(LONG nIndex)
{
	if(nIndex>0 && nIndex!=m_nCurrentPageNO){
		ISheet* ptrSheet=NULL;
		ptrSheet=(ISheet*)GetPageData(m_nCurrentPageNO);
		if(ptrSheet){
			ptrSheet->IsActive(FALSE);
			ptrSheet=(ISheet*)GetPageData(nIndex);
			ASSERT(ptrSheet);
			SetCurrentPageNO(nIndex);
			ptrSheet->IsActive(TRUE);
			ResetBeginOfLeft();
			ReDraw(TRUE);
		}
	}
}

void CLTabArea::SetBeginPos(const POINT &pt)
{
	m_posStart=pt;
}
