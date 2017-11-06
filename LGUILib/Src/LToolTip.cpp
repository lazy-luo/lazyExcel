// LToolTip.cpp: implementation of the CLToolTip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LToolTip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define TOOLTIP_OFFSET_X	16
#define TOOLTIP_OFFSET_Y	8
#define TOOLTIP_WIDTH		160
#define TOOLTIP_HEIGHT		100
#define SHADOW_WIDTH		4
#define TXT_PREFIX			8
CLToolTip::CLToolTip():m_ptrMsg(NULL)
{

}

CLToolTip::~CLToolTip()
{
	if(m_ptrMsg)
		delete[] m_ptrMsg;
}

void CLToolTip::SetMessage(LPTSTR ptrTxt)
{
	if(m_ptrMsg){
		delete[] m_ptrMsg;
		m_ptrMsg=NULL;
	}
	if(ptrTxt && ptrTxt[0]!='\0'){
		m_ptrMsg=new char[strlen(ptrTxt)+1];
		strcpy(m_ptrMsg,ptrTxt);
	}
}
void CLToolTip::OnDraw(LPHDC pDC,const RECT& rct)
{
	/*»­±ß¿ò¼°±³¾°*/
	if(IsVisible()){
		LPPOINT ppt;
		POINT pt[3];
		ppt=(LPPOINT)pDC->pParam;
		if(m_ptrMsg && ppt){
			
			RECT rct,rctClient;
			rct.left=ppt->x+TOOLTIP_OFFSET_X;
			rct.top=ppt->y-TOOLTIP_OFFSET_Y;
			rct.right=rct.left+TOOLTIP_WIDTH;
			rct.bottom=rct.top+TOOLTIP_HEIGHT;
			rctClient=rct;
			rctClient.left+=SHADOW_WIDTH;
			rctClient.top+=SHADOW_WIDTH;
			CLDrawer::FillSolidRect(pDC->hDC,&rctClient,RGB(128,128,128));
			rct.right-=SHADOW_WIDTH;
			rct.bottom-=SHADOW_WIDTH;
			CLDrawer::FrameRect(pDC->hDC,rct,COLOR_TOOL_TIP,RGB(64,64,64));
			pt[0].x=ppt->x-2;
			pt[0].y=ppt->y+3;
			
			pt[1].x=pt[0].x+4;
			pt[1].y=pt[0].y-8;
			
			pt[2].x=pt[1].x+4;
			pt[2].y=pt[0].y;
			HRGN hrgn=CLDrawer::CreatePolygonRgn(pt,3,WINDING);
			if(hrgn){
				CLDrawer::FillRgn(pDC->hDC,hrgn,GetSysColorBrush(COLOR_WINDOWTEXT));
				CLDrawer::DeleteRgn(hrgn);
			}
			CLDrawer::DrawerLine(pDC->hDC,ppt->x-2,ppt->y+2,rct.left,rct.top,RGB(64,64,64));
			
			rctClient=rct;
			rctClient.left+=TXT_PREFIX;
			rctClient.right-=TXT_PREFIX;
			rctClient.top+=TXT_PREFIX;
			rctClient.bottom-=TXT_PREFIX;
			HFONT hfont=::CreateFontIndirect(&DEFAULT_LOGFONT);
			HFONT hfont_old=(HFONT)CLDrawer::SelectFont(pDC->hDC,hfont);
			CLDrawer::DrawText(pDC->hDC,m_ptrMsg,strlen(m_ptrMsg),&rctClient
				,DT_LEFT|DT_SINGLELINE|DT_WORDBREAK,TRUE);
			CLDrawer::SelectFont(pDC->hDC,hfont_old);
			CLDrawer::DeleteFont(hfont);
		}
	}
}