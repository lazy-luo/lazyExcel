//////////////////////////////////////////////////////////////////////
//@模块		 ：裁减对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LClipDC.h"
#include "LGlobalParam.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLClipDC::CLClipDC()
{

}
CLClipDC::CLClipDC(HDC hDC,RECT& rct)
{
	SetClip(hDC,rct);
}
void CLClipDC::SetClip(HDC hDC,RECT& rct)
{
	m_hDC=hDC;
	/*
	int ret=GetClipBox(hDC,&m_Rect);
	bRestory=FALSE;
	if(ERROR==ret)
		ASSERT(FALSE);
	else if(ret!=NULLREGION)
		bRestory=TRUE;
	*/
	HRGN hRgn=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
	if(ERROR==SelectClipRgn(hDC,hRgn))
		ASSERT(FALSE);
	DeleteObject(hRgn);
	
	m_Size.cx=rct.right-rct.left;
	m_Size.cy=rct.bottom-rct.top;
}
CLClipDC::~CLClipDC()
{
	
	if(m_hDC){
		/*
		if(bRestory){
			HRGN hRgn=CreateRectRgn(m_Rect.left,m_Rect.top,
				m_Rect.right,m_Rect.bottom);
			if(ERROR==SelectClipRgn(m_hDC,hRgn))
				ASSERT(FALSE);
			DeleteObject(hRgn);
		}else{*/
			SelectClipRgn(m_hDC,NULL);
		//}
	}
	
}

void CLClipDC::GetSize(SIZE &size)
{
	size=m_Size;
}
