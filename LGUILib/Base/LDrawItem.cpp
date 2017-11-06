//////////////////////////////////////////////////////////////////////
//@模块		 ：绘图基类对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LDrawItem.h"
CLDrawItemBase::CLDrawItemBase():m_bFocus(FALSE),m_ptrOuter(NULL),
	m_ptrSizeNotify(NULL),bMouseDown(FALSE),m_bVisible(TRUE)
{
	CLPlatform::ClearPoint(m_ptOffset);
	CLPlatform::ClearPoint(m_ptOffsetEnd);
	CLPlatform::ClearRect(m_rctOld);
	
	m_cellPos.Row = 0;
	m_cellPos.Col = 0;
}
CLDrawItemBase::~CLDrawItemBase()
{

}
void CLDrawItemBase::SetRedrawHelp(IRedrawHelp* ptrOuter)
{
	if(m_ptrOuter!=ptrOuter)
		m_ptrOuter=ptrOuter;
}
void CLDrawItemBase::SetSizeNotify(ISizeNotify* ptrOuter)
{
	if(m_ptrSizeNotify!=ptrOuter)
		m_ptrSizeNotify=ptrOuter;
}
void CLDrawItemBase::ReDraw(BOOL bVal)
{
	if(m_ptrOuter)
		m_ptrOuter->ReDraw(bVal);
}
void CLDrawItemBase::DrawTracker(LPHDC pDC, int X, int Y)
{
	int nHandleCount = GetHandleCount();
	RECT rect;
	for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
	{
		rect = GetHandleRect(nHandle);
		
		rect.left+=X;
		rect.right+=X;
		rect.top+=Y;
		rect.bottom+=Y;
		CLDrawer::FrameRect(pDC->hDC,rect,RGB(255,255,255),RGB(10,10,10));
	}
}

POINT CLDrawItemBase::GetHandle(int nHandle)
{
	POINT pt;
	switch(nHandle)
	{
	case 1:
		pt.x = 0;
		pt.y = 0;
		break;
	case 2:
		pt.x = m_size.cx;
		pt.y = 0;
		break;
	case 3:
		pt.x = m_size.cx;
		pt.y = m_size.cy;
		break;
	case 4:
		pt.x = 0;
		pt.y = m_size.cy;
		break;
	case 5:
		pt.x = m_size.cx / 2;
		pt.y = 0;
		break;
	case 6:
		pt.x = m_size.cx;
		pt.y = m_size.cy / 2;
		break;
	case 7:
		pt.x = m_size.cx / 2;
		pt.y = m_size.cy;
		break;
	case 8:
		pt.x = 0;
		pt.y = m_size.cy / 2;
		break;
	default:
		ASSERT(FALSE);
	}
	pt.x+=m_beginPos.x;
	pt.y+=m_beginPos.y;
	return pt;
}
RECT CLDrawItemBase::GetHandleRect(int nHandle)
{
	LONG hlfSize=4;
	POINT pt = GetHandle(nHandle);
	RECT rect;
	rect.left = pt.x - hlfSize;
	rect.top = pt.y - hlfSize;
	rect.right = pt.x + hlfSize;
	rect.bottom = pt.y + hlfSize;

	return rect;
}

HCURSOR CLDrawItemBase::GetHandleCursor(int nHandle)
{
	LPTSTR lpszCursorName;
	switch(nHandle)
	{
	case 1:
		lpszCursorName = IDC_SIZENWSE;
		break;
	case 2:
		lpszCursorName = IDC_SIZENESW;
		break;
	case 3:
		lpszCursorName = IDC_SIZENWSE;
		break;
	case 4:
		lpszCursorName = IDC_SIZENESW;
		break;
	case 5:
		lpszCursorName = IDC_SIZENS;
		break;
	case 6:
		lpszCursorName = IDC_SIZEWE;
		break;
	case 7:
		lpszCursorName = IDC_SIZENS;
		break;
	case 8:
		lpszCursorName = IDC_SIZEWE;
		break;
	default:
		lpszCursorName = IDC_SIZEWE;
	}

	return ::LoadCursor(g_hInstance,lpszCursorName);
}

void CLDrawItemBase::MoveHandleTo(int nHandle, const POINT& point)
{
	POINT pt = point;
	pt.x-=m_ptOffset.x;
	pt.y-=m_ptOffset.y;
	if (nHandle == 1 || nHandle == 4 || nHandle == 8)
	{
		m_ptOffset.x += pt.x;
		m_size.cx -= pt.x;
	}
	if (nHandle == 1 || nHandle == 2 || nHandle == 5)
	{
		m_ptOffset.y += pt.y;
		m_size.cy -= pt.y;
	}
	if (nHandle == 2 || nHandle == 3 || nHandle == 6)
		m_size.cx = pt.x;
	if (nHandle == 3 || nHandle == 4 || nHandle == 7)
		m_size.cy = pt.y;

}

void CLDrawItemBase::MoveTo(const CELL& cell, const POINT& point)
{
	m_cellPos = cell;

	m_ptOffset = point;
	if (cell.Row == 0 && m_ptOffset.y < 0)
		m_ptOffset.y = 0;
	if (cell.Col == 0 && m_ptOffset.x < 0)
		m_ptOffset.x = 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLDrawItemMgrl::CLDrawItemMgrl():m_ptrHead(NULL),m_ptrTail(NULL),m_ptrFocus(NULL)
{
	
}
CLDrawItemMgrl::~CLDrawItemMgrl()
{
	if(m_ptrHead){
		delete m_ptrHead;
		/*
		if(m_ptrHead->ptrData)
			delete ((CLDrawItemBase*)m_ptrHead->ptrData);
		m_ptrHead=m_ptrHead->ptrNext;
		*/
	}
}
void CLDrawItemMgrl::SetSizeNotify(ISizeNotify* ptrNotify)
{
	LPCHAIN ptr=m_ptrHead;
	while(ptr && ptr->ptrData){
		((CLDrawItemBase*)(ptr->ptrData))->SetSizeNotify(ptrNotify);
		ptr=ptr->ptrNext;
	}
}
void CLDrawItemMgrl::SetRedrawHelp(IRedrawHelp* ptrObj)
{
	LPCHAIN ptr=m_ptrHead;
	while(ptr && ptr->ptrData){
		((CLDrawItemBase*)(ptr->ptrData))->SetRedrawHelp(ptrObj);
		ptr=ptr->ptrNext;
	}

}
LONG CLDrawItemMgrl::AddDrawItem(CLDrawItemBase *ptrItem)
{
	LONG bRet=-1;
	if(ptrItem){
		if(!IsExists(ptrItem,bRet)){
			LPCHAIN ptr=new CHAIN();
			if(!m_ptrHead){
				m_ptrHead=ptr;
			}else{
				ASSERT(m_ptrTail);
				m_ptrTail->ptrNext=ptr;
			}
			m_ptrTail=ptr;
			ptr->ptrData=(LPVOID)ptrItem;
		}
	}
	return bRet;
}

BOOL CLDrawItemMgrl::BringToBack(CLDrawItemBase *ptrItem)
{
	BOOL bRet=FALSE;
	if(ptrItem && m_ptrTail){
		LPCHAIN ptrParent=NULL,ptrPParent=NULL;
		LPCHAIN ptrNode=GetNode(ptrItem,ptrParent,ptrPParent);
		if(ptrNode){
			if(ptrParent){
				if(ptrPParent){
					ptrPParent->ptrNext=ptrNode;
					ptrParent->ptrNext=ptrNode->ptrNext;
					ptrNode->ptrNext=ptrParent;
					if(ptrNode==m_ptrTail)
						m_ptrTail=ptrParent;
				}else{
					ASSERT(ptrParent==m_ptrHead);
					ptrParent->ptrNext=ptrNode->ptrNext;
					ptrNode->ptrNext=ptrParent;
					m_ptrHead=ptrNode;
					if(ptrNode==m_ptrTail)
						m_ptrTail=ptrParent;
				}
			}else{
				ASSERT(ptrNode==m_ptrHead);
			}
			bRet=TRUE;
		}
	}
	return bRet;
}
BOOL CLDrawItemMgrl::BringToFront(CLDrawItemBase *ptrItem)
{
	BOOL bRet=FALSE;
	if(ptrItem){
		LPCHAIN ptrParent=NULL,ptrT=NULL;
		LPCHAIN ptrNode=GetNode(ptrItem,ptrParent,ptrT);
		if(ptrNode){
			ptrT=ptrNode->ptrNext;
			if(ptrParent){
				if(ptrT){
					ptrParent->ptrNext=ptrT;
					ptrNode->ptrNext=ptrT->ptrNext;
					ptrT->ptrNext=ptrNode;
					if(ptrT==m_ptrTail)
						m_ptrTail=ptrNode;
				}
			}else{
				ASSERT(ptrNode==m_ptrHead);
				if(ptrT){
					m_ptrHead=ptrT;
					ptrNode->ptrNext=ptrT->ptrNext;
					ptrT->ptrNext=ptrNode;
					if(ptrT==m_ptrTail)
						m_ptrTail=ptrNode;
				}
			}
			bRet=TRUE;
		}
	}
	return bRet;
}

BOOL CLDrawItemMgrl::BringToTop(CLDrawItemBase *ptrItem)
{
	BOOL bRet=FALSE;
	if(ptrItem && m_ptrTail){
		LPCHAIN ptrParent=NULL,ptrPParent=NULL;
		LPCHAIN ptrNode=GetNode(ptrItem,ptrParent,ptrPParent);
		if(ptrNode){
			if(ptrParent){
				if(ptrNode!=m_ptrTail){
					ptrParent->ptrNext=ptrNode->ptrNext;
					ptrNode->ptrNext=NULL;
					m_ptrTail->ptrNext=ptrNode;
					m_ptrTail=ptrNode;
				}
			}else{
				if(ptrNode!=m_ptrTail){
					ASSERT(ptrNode==m_ptrHead);
					//第一个
					m_ptrHead=m_ptrHead->ptrNext;
					ptrNode->ptrNext=NULL;
					m_ptrTail->ptrNext=ptrNode;
					m_ptrTail=ptrNode;
				}
			}
			bRet=TRUE;
		}
	}
	return bRet;
}
BOOL CLDrawItemMgrl::BringToBottom(CLDrawItemBase *ptrItem)
{
	BOOL bRet=FALSE;
	if(ptrItem && m_ptrHead){
		LPCHAIN ptrParent=NULL,ptrPParent=NULL;
		LPCHAIN ptrNode=GetNode(ptrItem,ptrParent,ptrPParent);
		if(ptrNode){
			if(ptrParent){
				ptrParent->ptrNext=ptrNode->ptrNext;
				ptrNode->ptrNext=m_ptrHead;
				m_ptrHead=ptrNode;
			}
			bRet=TRUE;
		}
	}
	return bRet;
}

void CLDrawItemMgrl::OnDraw(LPHDC pDC,const POINT& ptOffset
							,const POINT& pt_freeze,tag_Drawer_Type draw_type)
{
	LPCHAIN ptr=m_ptrHead;
	RECT rct,rctCur;
	BOOL bDraw=FALSE;
	CLDrawItemBase* ptrItem=NULL;
	while(ptr){
		ptrItem=(CLDrawItemBase*)ptr->ptrData;
		if(draw_type==type_draw_all || (draw_type==type_draw_client &&ptrItem && ptrItem->m_cellPos.Row>pt_freeze.y
			&& ptrItem->m_cellPos.Col>pt_freeze.x) || (draw_type==type_draw_none_client && ptrItem 
			&& (ptrItem->m_cellPos.Row<=pt_freeze.y || ptrItem->m_cellPos.Col<=pt_freeze.x))){
			bDraw=TRUE;
			if(ptrItem){
				ptrItem->IsVisible(((IDrawItem*)ptrItem)->GetDrawRect(rct));
				/*
				rct.left+=ptOffset.x;
				rct.right+=ptOffset.x;
				rct.top+=ptOffset.y;
				rct.bottom+=ptOffset.y;
				*/
				
				ptrItem->OnDraw(pDC,rct);
			}
			if(ptrItem==m_ptrFocus)
				rctCur=rct;
		}
		ptr=ptr->ptrNext;
	}
	if(bDraw && m_ptrFocus && m_ptrFocus->IsVisible()){
		m_ptrFocus->DrawTracker(pDC,0,0);//rctCur.left,rctCur.top);//ptOffset.x,ptOffset.y);
	}
}

BOOL CLDrawItemMgrl::IsExists(CLDrawItemBase *ptrItem,LONG& ret)
{
	BOOL bRet=FALSE;
	ret=0;
	if(ptrItem){
		LPCHAIN ptr=m_ptrHead;
		while(ptr){
			if(ptr->ptrData==(LPVOID)ptrItem){
				bRet=TRUE;
				break;
			}
			ptr=ptr->ptrNext;
			ret++;
		}
	}
	ret=(bRet?ret:-1);
	return bRet;
}

LPCHAIN CLDrawItemMgrl::GetNode(CLDrawItemBase *ptrItem, 
	LPCHAIN &pparent,LPCHAIN& ppparent)
{
	LPCHAIN ptrRet=NULL;
	pparent=NULL;
	ppparent=NULL;
	if(ptrItem){
		LPCHAIN ptr=m_ptrHead;
		while(ptr){
			if(ptr->ptrData==(LPVOID)ptrItem){
				ptrRet=ptr;
				break;
			}
			ppparent=pparent;
			pparent=ptr;
			ptr=ptr->ptrNext;
		}
	}
	return ptrRet;
}

void CLDrawItemMgrl::DeleteDrawItem(CLDrawItemBase *ptrItem)
{
	if(ptrItem){
		LPCHAIN ptrParent=NULL,ptrPParent=NULL;
		LPCHAIN ptrNode=GetNode(ptrItem,ptrParent,ptrPParent);
		if(ptrNode){
			if(ptrParent){
				ptrParent->ptrNext=ptrNode->ptrNext;
				ptrNode->ptrNext=NULL;
				if(ptrNode==m_ptrTail)
					m_ptrTail=ptrParent;
				delete ptrNode;
			}else{
				ASSERT(ptrNode==m_ptrHead);
				//第一个
				if(ptrNode!=m_ptrTail){
					m_ptrHead=m_ptrHead->ptrNext;
					ptrNode->ptrNext=NULL;
					delete ptrNode;
				}else{
					//只有一个
					delete m_ptrHead;
					m_ptrHead=NULL;
					m_ptrTail=NULL;
				}
			}
			if(m_ptrFocus==ptrItem)
				m_ptrFocus=NULL;
		}
	}
}
CLDrawItemBase* CLDrawItemMgrl::GetTopMostItem()
{
	if(m_ptrTail)
		return (CLDrawItemBase*)m_ptrTail->ptrData;
	else
		return NULL;
}
CLDrawItemBase* CLDrawItemMgrl::GetPrevItem(CLDrawItemBase* ptrData)
{
	LPCHAIN ptr=NULL;
	for(ptr=m_ptrHead;ptr && ptr->ptrData!=(LPVOID)ptrData;ptr=ptr->ptrNext);
	return (ptr?(ptr->ptrNext?(CLDrawItemBase*)(ptr->ptrNext->ptrData):NULL):NULL);
}
CLDrawItemBase* CLDrawItemMgrl::GetNextItem(CLDrawItemBase* ptrData)
{
	LPCHAIN ptr=NULL,ptrP=NULL;
	for(ptr=m_ptrHead;ptr && ptr->ptrData!=(LPVOID)ptrData;ptrP=ptr,ptr=ptr->ptrNext);
	return ((ptr && ptrP)?((CLDrawItemBase*)(ptrP->ptrData)):NULL);
}
CLDrawItemBase* CLDrawItemMgrl::GetBottomItem()
{
	if(m_ptrHead)
		return (CLDrawItemBase*)m_ptrHead->ptrData;
	else
		return NULL;
}
void CLDrawItemBase::OnMouseMove(LONG idArea,MOUSESTATUS& nstatus)
{
	if(!m_ptrSizeNotify)return;
	if(bMouseDown){
		//CLPlatform::DebugMsg("POINT[%d,%d]\n",nstatus.posx,nstatus.posy);
		RECT rct;
		SIZE size;
		GetDrawSize(size);
		m_ptrSizeNotify->OnObjectMove(m_cellPos,m_cellEnd,m_ptOffset,m_ptOffsetEnd,size,
			nstatus.posx-m_ptOld.x,nstatus.posy-m_ptOld.y,rct);
		
		//SetDrawRect(rct);
		GetDrawRect(rct);
		m_ptOld.x=nstatus.posx;
		m_ptOld.y=nstatus.posy;
		if(m_ptrOuter){
			HDCH hDC;
			if(m_ptrOuter->GetDC(hDC) && !CLPlatform::SameRect(m_rctOld,rct)){
				if(!CLPlatform::IsEmptyRect(m_rctOld))
					CLDrawer::DrawDitherBorder(hDC.hDC,&m_rctOld,1,1);
				CLDrawer::DrawDitherBorder(hDC.hDC,&rct,1,1);
				m_rctOld=rct;
				m_ptrOuter->ReleaseDC(hDC);
			}
		}
	}
}
void CLDrawItemBase::OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	if(!m_ptrSizeNotify)return;
	if(!bMouseDown){
		bMouseDown=TRUE;
		m_ptOld.x=nstatus.posx;
		m_ptOld.y=nstatus.posy;
		//GetDrawRect(m_rctOld);
		/*
		if(m_ptrOuter){
			HDCH hDC;
			if(m_ptrOuter->GetDC(hDC)){
				CLDrawer::DrawDitherBorder(hDC.hDC,&m_rctOld,1,1);
			}
		}
		*/
	}
}
void CLDrawItemBase::OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus)
{
	bMouseDown=FALSE;
	if(m_ptrOuter){
		HDCH hDC;
		if(m_ptrOuter->GetDC(hDC)){
			CLDrawer::DrawDitherBorder(hDC.hDC,&m_rctOld,1,1);
			m_ptrOuter->ReleaseDC(hDC);
			CLPlatform::ClearRect(m_rctOld);
		}
		m_ptrOuter->ReDraw(TRUE);
	}
}
BOOL CLDrawItemBase::GetDrawRect(RECT& rct)
{
	BOOL bret;
	if(m_ptrSizeNotify){
		bret=m_ptrSizeNotify->OnObjectMove(m_cellPos,m_cellEnd,m_ptOffset,m_ptOffsetEnd,m_size,0,0,rct);
		m_beginPos.x=rct.left;
		m_beginPos.y=rct.top;
	}else{
		bret=IDrawItem::GetDrawRect(rct);
	}
	return bret;
}