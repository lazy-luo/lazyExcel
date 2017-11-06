//////////////////////////////////////////////////////////////////////
//@模块		 ：图片画板
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LBitmapPan.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define ID_CLIENT	1
CLBitmapPan::CLBitmapPan():m_hBitmap(NULL),m_pArea(NULL)
{

}

CLBitmapPan::~CLBitmapPan()
{
	if(m_pArea)
		delete m_pArea;
	m_pArea=NULL;
	ClearBitmap();
}

void CLBitmapPan::ClearBitmap()
{
	if(m_hBitmap)
		CLDrawer::DeleteBitmap(m_hBitmap);
	m_hBitmap=NULL;
}

BOOL CLBitmapPan::SetBitmap(LPTSTR ptrName)
{
	m_hBitmap=CLDrawer::GetBitmap(ptrName);
	if(m_hBitmap){
		BITMAP	bm;
		SIZE size;
		if (!GetObject(m_hBitmap, sizeof(bm), (LPSTR)&bm)){
			ClearBitmap();
			return FALSE;
		}
		size.cx=bm.bmWidth;
		size.cy=bm.bmHeight;
		SetDrawSize(size);
	}
	return m_hBitmap!=NULL;
}
BOOL CLBitmapPan::GetRect(LONG idArea,RECT& rct)
{
	if(ID_CLIENT==idArea){
		GetDrawRect(rct);
	}
	return TRUE;
}
BOOL CLBitmapPan::GetRgn(LONG idArea,HRGN& hrgn)
{
	return FALSE;
}
LPIDAREA CLBitmapPan::GetAreaIDs()
{
	if(m_pArea)return m_pArea;
	m_pArea=new IDAREA();
	m_pArea->lngID=ID_CLIENT;
	return m_pArea;
}
void CLBitmapPan::OnDraw(LPHDC pDC,const RECT& rct)
{
	if(m_hBitmap){
		CLDrawer::DrawBitmap(pDC->hDC,rct.left,rct.top,
			m_hBitmap,rct.right-rct.left,rct.bottom-rct.top);
	}
}
void CLBitmapPan::OnMouseMove(LONG idArea,MOUSESTATUS& nstatus)
{
	CLDrawItemBase::OnMouseMove(idArea,nstatus);
	CLPlatform::SetCursor(IDC_CUR_DROPPAN);
}
void CLBitmapPan::OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus)
{
	CLDrawItemBase::OnLButtonDown(idArea,nstatus);
	CLPlatform::SetCursor(IDC_CUR_DROPPAN);
}