//////////////////////////////////////////////////////////////////////
//@模块		 ：工作薄对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LBook.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

////////////////////////////////////
#include "../LGUILib/Src/LDrawerSheet.h"
#include "../LGUILib/Src/LArtFontPan.h"
#include "../LGUILib/Src/LBitmapPan.h"
#include "../LGUILib/Src/LChartPan.h"
#include "../LGUILib/Src/LScrollBar.h"

#ifdef DEBUG_DRAW
extern long m_cellCount;
#endif
CLBook::CLBook(LONG key):m_perTabBar(4.0/7.0),m_ptrDrawHelp(NULL),m_bSplictFixedSize(FALSE),
	m_clrScrollBar(CLPlatform::GetSysColor(COLOR_SCROLLBAR)),m_lngWidth(0),m_handKey(key),
	m_nBorderWidth(1)
{
	
	m_pDrawer=new CLDrawerSheet();
	m_ptrHorzScroll=new CLScrollBar(NULL,TRUE);
	m_ptrVertScroll=new CLScrollBar(NULL,FALSE);
	m_table.SetSplictOwner(this);
	CLPlatform::ClearSize(m_sizePan);
}

CLBook::~CLBook()
{
	if(m_pDrawer)
		delete m_pDrawer;
	delete m_ptrHorzScroll;
	delete m_ptrVertScroll;
	ClearData();
	CLEAR_INTERFACE;
}
BOOL CLBook::GetDrawRect(RECT& rct,BOOL bdecBorder)
{
	if(m_ptrDrawHelp){
		if(m_ptrDrawHelp->GetTotalRect(rct)){
			//去掉边框
			if(bdecBorder){
				rct.left+=m_nBorderWidth;
				rct.right-=m_nBorderWidth;
				rct.top+=m_nBorderWidth;
				rct.bottom-=m_nBorderWidth;
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CLBook::GetScrollBarRect(BOOL bHorz,RECT& rct)
{
	RECT rctAll;
	ISheet* ptrSheet=GetCurrentSheet();
	if(!GetDrawRect(rctAll) || !ptrSheet)return FALSE;
	BOOL bDrawHorzBar=((CLSheet*)ptrSheet)->HasScroll(TRUE);
	BOOL bDrawVertBar=((CLSheet*)ptrSheet)->HasScroll(FALSE); 
	if(bHorz && bDrawHorzBar){
		rct=rctAll;
		rct.top=rct.bottom-SCROLLBAR_SIZE;
		rct.right-=(bDrawVertBar?SCROLLBAR_SIZE:0);
		LONG dblLen;
		if(m_bSplictFixedSize)
			dblLen=TAB_SPLICT_WIDTH;
		else
			dblLen=(LONG)((rct.right-rct.left)*m_perTabBar);
		
		rct.left+=dblLen;
		return TRUE;
	}else if(!bHorz && bDrawVertBar){
		rct=rctAll;
		rct.left=rct.right-SCROLLBAR_SIZE;
		rct.bottom-=(bDrawVertBar || m_table.isVisible()?SCROLLBAR_SIZE:0);
		return TRUE;
	}
	return FALSE;
}
BOOL CLBook::GetTabAreaRect(RECT& rct)
{
	RECT rctAll;
	ISheet* ptrSheet=GetCurrentSheet();
	if(!GetDrawRect(rctAll) || !ptrSheet)return FALSE;
	if(m_table.isVisible()){
		rct=rctAll;
		LONG dblLen;
		rct.top=rct.bottom-SCROLLBAR_SIZE;
		rct.right-=(((CLSheet*)ptrSheet)->HasScroll(FALSE)?SCROLLBAR_SIZE:0);
		if(m_bSplictFixedSize)
			dblLen=TAB_SPLICT_WIDTH;
		else
			dblLen=(LONG)((rct.right-rct.left)*m_perTabBar);
		rct.right=rct.left+dblLen;
		return TRUE;
	}
	return FALSE;
}
void CLBook::OnSizeChange(LONG offsetX, LONG offsetY)
{
	LONG ct=m_table.GetCount();
	CLSheet* psheet;
	for(LONG i=1;i<=ct;i++){
		psheet=(CLSheet*)m_table.GetPageData(i);
		if(psheet){
			psheet->AdjustSizeChange(offsetX,offsetY);
		}
	}
}
DWORD WINAPI DrawProc(LPVOID lpParameter)
{
	LPDRAWPARAM ptr=(LPDRAWPARAM)lpParameter;
	if(ptr && ptr->p_book){
		ptr->p_book->Draw_Book(ptr->lpDrawer);
	}
	return 0;
}
void CLBook::OnDraw(LPDRAWER	ptrCellDrawer)
{
	Draw_Book(ptrCellDrawer);
	/*
	DRAWPARAM param;
	DRAWER drawer;
	memcpy(&drawer,ptrCellDrawer,sizeof(DRAWER));
	param.lpDrawer=&drawer;
	param.p_book=this;
	DWORD tid;
	CreateThread((LPSECURITY_ATTRIBUTES)NULL,(DWORD)0 \
				,(LPTHREAD_START_ROUTINE)DrawProc,(LPVOID)&param,(DWORD)0,(LPDWORD)&tid);
	*/
}
void CLBook::Draw_Book(LPDRAWER	ptrCellDrawer)
{
	ISheet* ptrSheet=GetCurrentSheet();
	RECT rctALL;
	if(!ptrSheet){
		SetCurrentSheetIndex(1);
		ptrSheet=GetCurrentSheet();
	}
	if(ptrSheet){
		if(ptrSheet && GetDrawRect(rctALL,FALSE)){
			POINT ptStart;
			ptStart.x=0;
			ptStart.y=0;
			ITable* ptrTable=ptrSheet->GetGrid()->GetTable();
			HDCH hDC;
			hDC.hDC=ptrCellDrawer->m_hDC;
			//ptrTable->GetDC(hDC);
			
#ifdef _LZY_USE_DOUBLE_BUFF_
			ptrCellDrawer->m_hDC=hDC.hDC;
			CLMemDC mDC(ptrCellDrawer->m_hDC,rctALL);
			HDC holdDC=ptrCellDrawer->m_hDC;
			ptrCellDrawer->m_hDC=mDC;
#endif

			ptStart.x=rctALL.left;
			ptStart.y=rctALL.top;

			ptrSheet->SetBeginPos(ptStart);
			RECT rctBorder=rctALL;
			
			rctALL.left+=m_nBorderWidth;
			rctALL.top+=m_nBorderWidth;
			rctALL.right-=m_nBorderWidth;
			rctALL.bottom-=m_nBorderWidth;

			ptrTable->SetDrawPanRect(rctALL);
			m_pDrawer->AttachSheet(ptrSheet);
			RECT rct=rctALL;
			RECT rctTT=rct,rctBK;
			RECT rctC=rct;
			BOOL bDrawHorzBar,bDrawVertBar=FALSE;
			SIZE sizeExt;
			sizeExt.cx=0;
			sizeExt.cy=(m_table.isVisible()?SCROLLBAR_SIZE:0);
			((CLSheet*)ptrSheet)->SetExtendSize(sizeExt);
			bDrawHorzBar=((CLSheet*)ptrSheet)->HasScroll(TRUE);
			bDrawVertBar=((CLSheet*)ptrSheet)->HasScroll(FALSE);
			if(m_ptrHorzScroll)
				m_ptrHorzScroll->IsActive(bDrawHorzBar);
			if(m_ptrVertScroll)
				m_ptrVertScroll->IsActive(bDrawVertBar);
			if(m_sizePan.cx>0 && m_sizePan.cy>0){
				LONG noffsetx=(rctALL.right-rctALL.left)-m_sizePan.cx-(bDrawVertBar?SCROLLBAR_SIZE:0);
				LONG noffsety=(rctALL.bottom-rctALL.top)-m_sizePan.cy-(bDrawHorzBar?SCROLLBAR_SIZE:0);
				if(noffsetx!=0 || noffsety!=0){
					OnSizeChange(noffsetx,noffsety);
					
					m_sizePan.cx=rctALL.right-rctALL.left-(bDrawVertBar?SCROLLBAR_SIZE:0);
					m_sizePan.cy=rctALL.bottom-rctALL.top-(bDrawHorzBar?SCROLLBAR_SIZE:0);
				}
			}else{
				m_sizePan.cx=rctALL.right-rctALL.left-(bDrawVertBar?SCROLLBAR_SIZE:0);
				m_sizePan.cy=rctALL.bottom-rctALL.top-(bDrawHorzBar?SCROLLBAR_SIZE:0);
			}
			
			if(bDrawHorzBar || m_table.isVisible()){
				rctC.bottom-=SCROLLBAR_SIZE;
			}
			if(bDrawVertBar){
				rctC.right-=SCROLLBAR_SIZE;
			}
			
			hDC.bIsPrint=FALSE;
			hDC.hDC=ptrCellDrawer->m_hDC;
			rctBK=rctC;	
			
			m_pDrawer->OnDraw(&hDC,rctC);
			
			rctC.bottom+=SCROLLBAR_SIZE;
			LONG widScroll=rctC.right-rctC.left;
			m_lngWidth=widScroll;
			LONG heiScroll=rctC.bottom-rctC.top;
			
			LONG dblLen;
			if(m_table.isVisible()){
				m_table.SetBeginPos(ptStart);
				rct.top=rct.bottom-SCROLLBAR_SIZE;
				if(m_bSplictFixedSize){
					dblLen=TAB_SPLICT_WIDTH;
				}else
					dblLen=(bDrawHorzBar?(LONG)(widScroll*m_perTabBar):widScroll);
				
				rct.right=rct.left+dblLen;
				widScroll-=(rct.right-rct.left);
				CLClipDC clipDC(ptrCellDrawer->m_hDC,rct);
				ptrCellDrawer->m_lpRect=&rct;
				
				m_table.DrawPages(ptrCellDrawer);
				rct.left=rct.right;
			}
			if(bDrawHorzBar){
				hDC.pParam=((CLSheet*)ptrSheet)->GetScrollInfo();
				((LPSCROLLINFOEXT)hDC.pParam)->m_nExistValue=rctBK.right-rctBK.left;
				rct.right=rct.left+widScroll;
				m_ptrHorzScroll->SetScrollOwner((IScrollable*)ptrSheet->GetGrid());
				m_ptrHorzScroll->SetBeginPos(ptStart);
				m_ptrHorzScroll->OnDraw(&hDC,rct);
				if(bDrawVertBar){
					rct.left=rct.right;
					rct.right=rct.left+SCROLLBAR_SIZE;
					CLDrawer::FillSolidRect(hDC.hDC,&rct,GetSysColor(COLOR_BTNFACE));
				}
			}
			if(bDrawVertBar){
				//垂直滚动条
				rct=rctTT;
				hDC.pParam=((CLSheet*)ptrSheet)->GetScrollInfo(FALSE);
				((LPSCROLLINFOEXT)hDC.pParam)->m_nExistValue=rctBK.bottom-rctBK.top;
				rct.left=rct.right-SCROLLBAR_SIZE;
				rct.bottom-=(bDrawHorzBar?SCROLLBAR_SIZE:0);
				m_ptrVertScroll->SetScrollOwner((IScrollable*)ptrSheet->GetGrid());
				m_ptrVertScroll->SetBeginPos(ptStart);
				m_ptrVertScroll->OnDraw(&hDC,rct);
			}
			
			CLDrawer::Draw3dRect(hDC.hDC,&rctBorder,RGB(128,128,128),RGB(235,235,235));//,FALSE);

	#ifdef DEBUG_DRAW
			char strT[64];
			sprintf(strT,"%d\0",m_cellCount);
			((CLSheet*)ptrSheet)->SetCellText(0,1,strT);
	#endif

	#ifdef _LZY_USE_DOUBLE_BUFF_
			ptrCellDrawer->m_hDC=holdDC;
	#endif
			ptrTable->ReleaseDC(hDC);
		}
	}else{
		GetDrawRect(rctALL,FALSE);
		HDCH hDC;
		hDC.hDC=ptrCellDrawer->m_hDC;
		//ptrTable->GetDC(hDC);
		
#ifdef _LZY_USE_DOUBLE_BUFF_
		ptrCellDrawer->m_hDC=hDC.hDC;
		CLMemDC mDC(ptrCellDrawer->m_hDC,rctALL);
		HDC holdDC=ptrCellDrawer->m_hDC;
		ptrCellDrawer->m_hDC=mDC;
#endif
		CLDrawer::FillSolidRect(ptrCellDrawer->m_hDC,&rctALL,COLOR_BKGRD);
#ifdef _LZY_USE_DOUBLE_BUFF_
		ptrCellDrawer->m_hDC=holdDC;
#endif
	}
}

ISheet*	CLBook::AddSheet(LPTSTR ptrName,LONG nIndex)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	ISheet* pSheet=GetCurrentSheet();
	CLPageItem* ptr=m_table.AddPage((LPVOID)NULL,nIndex);
	if(ptr){
		CLSheet* ptrSheet=(CLSheet*)ptr->GetData();
		if(!ptrSheet){
			ptrSheet=new CLSheet();
			if(m_handKey!=0){
				LINK_MOUSE_EVENT(m_handKey,(IMouseEvent*)ptrSheet);
			}
			ptrSheet->SetRedrawHelp(m_ptrDrawHelp);
			ptr->SetData(ptrSheet);
			ptr->SetCaption(ptrName);
		}
		if(nIndex==1)
			SetCurrentSheetIndex(1);
		return ptrSheet;
	}else{
		return NULL;
	}
}
ISheet*  CLBook::GetCurrentSheet()
{
	return (ISheet*)m_table.GetPageData(m_table.GetCurrentPageNO());
}
void	CLBook::DeleteSheet(LONG nIndex)
{
	if(GetCount()<2)return;
	CLSheet* ptr=(CLSheet*)m_table.GetPageData(nIndex);
	g_nMouseEventMgrl.RemoveListener(m_handKey,(IMouseEvent*)ptr);
	m_table.RemovePage(nIndex);
	if(ptr)
		delete ptr;
}
LONG	CLBook::GetCurrentSheetIndex()
{
	return m_table.GetCurrentPageNO();
}
void	CLBook::SetPageName(LONG index,LPTSTR ptrTxt)
{
	m_table.SetPageCaption(index/*m_table.GetCurrentPageNO()*/,ptrTxt);
}
LPTSTR	CLBook::GetCurrentPageName()
{
	return GetPageName(m_table.GetCurrentPageNO());
}
void	CLBook::SetCurrentPageName(LPTSTR ptrTxt)
{
	SetPageName(m_table.GetCurrentPageNO(),ptrTxt);
}
BOOL	CLBook::SetCurrentSheetIndex(LONG nIndex)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	CLSheet* ptr=(CLSheet*)GetCurrentSheet();
	BOOL bret= m_table.SetCurrentPageNO(nIndex);
	if(bret && ptr){
		ptr->IsActive(FALSE);
		ptr=(CLSheet*)GetCurrentSheet();
		ptr->IsActive(TRUE);
	}
	return bret;
}

BOOL CLBook::isTabVisible()
{
	return m_table.isVisible();
}
DOUBLE	CLBook::GetWidthPercent()
{
	return m_perTabBar;
}
void	CLBook::SetWidthPercent(DOUBLE dbl)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	m_perTabBar=dbl;
}

void CLBook::ClearData()
{
	INDEX key;
	CLPageItem ptrItem;
	CLSheet* ptrSheet;
	POSITION pos = m_table.GetStartPosition();
	while (pos != NULL)
	{
		m_table.GetNextAssoc(pos, key, ptrItem);
		ptrSheet=(CLSheet*)ptrItem.GetData();
		if(ptrSheet){
			delete ptrSheet;
		}
	}
}

ISheet* CLBook::GetSheetByPtr(LPVOID sheet)
{
	return (ISheet*)m_table.GetValue(sheet);
}

LONG CLBook::GetCount()
{
	return m_table.GetPageCount();
}

ISheet* CLBook::GetSheet(LONG nIndex)
{
	return (ISheet*)m_table.GetPageData(nIndex);
}

LPTSTR CLBook::GetPageName(LONG nIndex)
{
	return m_table.GetPageCaption(nIndex);
}
BOOL CLBook::OnSerial(CLSerial& ar)
{
	BOOL bret=TRUE;
	INDEX key;
	CLPageItem ptrItem;
	CLSheet* ptrSheet;
	POSITION pos;
	g_nMouseEventMgrl.Lock();
	if(!m_table.OnSerial(ar)){
		ASSERT(FALSE);
		bret=FALSE;
		goto to_exit;
	}
	if(ar.isLoading()){
		ar>>m_perTabBar;
		ar>>m_bSplictFixedSize;
		ar>>m_clrScrollBar;
		ar>>m_lngWidth;
		ar>>m_nBorderWidth;
		ar>>m_perTabBar;
		ar>>m_sizePan;
	}else{
		ar<<m_perTabBar;
		ar<<m_bSplictFixedSize;
		ar<<m_clrScrollBar;
		ar<<m_lngWidth;
		ar<<m_nBorderWidth;
		ar<<m_perTabBar;
		ar<<m_sizePan;
	}
	pos = m_table.GetStartPosition();
	while (pos != NULL)
	{
		m_table.GetNextAssoc(pos, key, ptrItem);
		ptrSheet=(CLSheet*)ptrItem.GetData();
		if(ptrSheet){
			if(!ptrSheet->OnSerial(ar)){
				bret=FALSE;
				goto to_exit;
			}
		}
	}
to_exit:
	g_nMouseEventMgrl.ClearToDefault();
	g_nMouseEventMgrl.UnLock();
	return TRUE;
}

void CLBook::SetRedrawHelp(IRedrawHelp* ptr)
{
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	m_table.SetRedrawHelp(ptr);
	
	m_ptrDrawHelp=ptr;
	INDEX key;
	CLPageItem ptrItem;
	CLSheet* ptrSheet;
	POSITION pos = m_table.GetStartPosition();
	while (pos != NULL)
	{
		m_table.GetNextAssoc(pos, key, ptrItem);
		ptrSheet=(CLSheet*)ptrItem.GetData();
		if(ptrSheet){
			ptrSheet->SetRedrawHelp(m_ptrDrawHelp);
			ptrSheet->SetDrawMgrlRedrawHelp(m_ptrDrawHelp);
		}
	}
}
void CLBook::SplictChange(LONG noffset)
{
	if(noffset!=0 && m_lngWidth>0){
		DOUBLE dblLen=(DOUBLE)(m_lngWidth*m_perTabBar+noffset);
		m_bSplictFixedSize=FALSE;
		if(dblLen<TAB_SPLICT_WIDTH){
			dblLen=TAB_SPLICT_WIDTH;
			m_bSplictFixedSize=TRUE;
		}
		if(dblLen>m_lngWidth)
			dblLen=m_lngWidth;
		m_perTabBar=(DOUBLE)(dblLen)/(DOUBLE)m_lngWidth;
	}
	HDCH hDC;
	CLSheet* ptrSheet=(CLSheet*)GetCurrentSheet();
	if(m_ptrDrawHelp && ptrSheet->GetDC(hDC)){
		//重画
		RECT rctT;
		if(GetTabAreaRect(rctT)){
			DRAWER drawer;
			
			drawer.m_hDC=hDC.hDC;
			drawer.m_lpRect=&rctT;
			m_table.DrawPages(&drawer);
			if(GetScrollBarRect(TRUE,rctT)){
				hDC.pParam=ptrSheet->GetScrollInfo();
				m_ptrHorzScroll->OnDraw(&hDC,rctT);
			}
		}
		ptrSheet->ReleaseDC(hDC);
	}
}
BOOL CLBook::OnPrint(BOOL bPrintAll)
{
	bPrintAll=FALSE;
	CLLockMgr<CLCSWrapper>  lockMgr(sm_CritSec, TRUE);
	BOOL bret=TRUE;
	ISheet* ptrSheet;
	ISheet* ptrOld=GetCurrentSheet();
	if(bPrintAll){
		INDEX key;
		CLPageItem ptrItem;
		POSITION pos = m_table.GetStartPosition();
		while (pos != NULL)
		{
			m_table.GetNextAssoc(pos, key, ptrItem);
			ptrSheet=(ISheet*)ptrItem.GetData();
			if(ptrSheet){
				if(!PrintSheet(ptrSheet)){
					ASSERT(FALSE);
					bret=FALSE;
					break;
				}
			}
		}
	}else{
		ptrSheet=GetCurrentSheet();
		if(ptrSheet){
			if(!PrintSheet(ptrSheet)){
				ASSERT(FALSE);
				bret=FALSE;
			}
		}
	}
	m_pDrawer->AttachSheet(ptrOld);
	return bret;
}

BOOL CLBook::PrintSheet(ISheet *ptrSheet,BOOL bShowDlg)
{
	BOOL bret=FALSE;
	if(m_pDrawer){
		m_pDrawer->AttachSheet(ptrSheet);
		m_printer.AttachObject(m_pDrawer,ptrSheet);
		m_printer.PrintSetup(NULL,0);
		bret=TRUE;
	}
	return bret;
}
void CLBook::SetPanKey(LONG handKey)
{
	LINK_MOUSE_EVENT(handKey,(IMouseEvent*)(&m_table));
	LINK_MOUSE_EVENT(handKey,(IMouseEvent*)m_ptrHorzScroll);
	LINK_MOUSE_EVENT(handKey,(IMouseEvent*)m_ptrVertScroll);
	LONG ct=m_table.GetCount();
	CLSheet* psheet;
	for(LONG i=1;i<=ct;i++){
		psheet=(CLSheet*)m_table.GetPageData(i);
		if(psheet){
			LINK_MOUSE_EVENT(handKey,((IMouseEvent*)psheet));
		}
	}
	m_handKey=handKey;
}



BOOL CLBook::AddBitmapPan(LONG sheet, LPTSTR ptrName)
{
	ISheet* ptrSheet=(ISheet*)sheet;
	ASSERT(ptrSheet);
	CLBitmapPan* ptr=new CLBitmapPan();
	if(!ptr->SetBitmap(ptrName)){
		delete ptr;
		ptr=NULL;
		return FALSE;
	}
	CELL cell;
	POINT pt;
	ptrSheet->GetGrid()->GetTable()->GetCurrentCell(cell);
	pt.x=0;
	pt.y=0;
	ptr->MoveTo(cell,pt);
	ptr->SetRedrawHelp(m_ptrDrawHelp);
	return ptrSheet->AddDrawItem((CLDrawItemBase*)ptr);
}
