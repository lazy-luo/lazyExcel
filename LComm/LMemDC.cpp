#include "stdafx.h"
#include "LMemDC.h"
#include "LGlobalParam.h"

#ifdef USE_WINDDC
extern HINSTANCE g_hInstance;
#define ID_CMDCANCEL	100021
HWND CLMemDC::m_hWnd=NULL;
#endif
void	CLMemDC::GetClientRect(RECT &rct)
{
	rct.left-=m_rct.left;
	rct.top-=m_rct.top;
	rct.right-=m_rct.left;
	rct.bottom-=m_rct.top;
}
CLMemDC::CLMemDC(HDC hDC,RECT& rct)
{
	m_hDC=NULL;
	m_hBitMap=NULL;
	m_hOldBmp=NULL;
	m_hRelDC=hDC;
	m_rct=rct;
#ifdef USE_WINDDC
	//m_hDC=CreateDC("DISPLAY",NULL,NULL,NULL);
	
	if(!m_hWnd)
		m_hWnd=CreateWindow("STATIC","",WS_CHILD,0,0,rct.right-rct.left,rct.bottom-rct.top,GetDesktopWindow(),(HMENU)ID_CMDCANCEL,g_hInstance,NULL);
	ASSERT(m_hWnd);
	
	m_hDC=GetWindowDC(m_hWnd);
	SetWindowPos(
            m_hWnd,
            (HWND) NULL,
            0,
            0,
            1,
            1,
            SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREDRAW |
                SWP_NOZORDER | SWP_SHOWWINDOW
            );

	
	UpdateWindow(m_hWnd);
#else
	if(hDC){
		m_hDC=CreateCompatibleDC(hDC);
		//GetClipBox(hDC,&m_rct);
		//GetClientRect(rct);
		m_hBitMap = CreateCompatibleBitmap(hDC,m_rct.right-
			m_rct.left,m_rct.bottom-m_rct.top);
		if(m_hBitMap){
			m_hOldBmp=(HBITMAP)SelectObject(m_hDC,m_hBitMap);
			//BitBlt(m_hDC,0,0,m_rct.right-m_rct.left,
			//	m_rct.bottom-m_rct.top,hDC,m_rct.left,m_rct.top,SRCCOPY);
		}
#endif
		rct.right-=rct.left;
		rct.bottom-=rct.top;
		rct.left=0;
		rct.top=0;
#ifndef USE_WINDDC
	}
#endif
}

CLMemDC::~CLMemDC()
{
#ifdef USE_WINDDC
	if(m_hDC){
		BitBlt(m_hRelDC,m_rct.left,m_rct.top,m_rct.right-m_rct.left,
				m_rct.bottom-m_rct.top,m_hDC,0,0,SRCCOPY);
		
	}
#else
	if(m_hDC && m_hBitMap){
		BitBlt(m_hRelDC,m_rct.left,m_rct.top,m_rct.right-m_rct.left,
				m_rct.bottom-m_rct.top,m_hDC,0,0,SRCCOPY);
		SelectObject(m_hDC,m_hOldBmp);
		DeleteDC(m_hDC);
		DeleteObject(m_hBitMap);
	}else{
		if(m_hDC){
			DeleteDC(m_hDC);
		}else{
			DeleteObject(m_hBitMap);
		}
	}
	
#endif
	//if(m_hWnd)
	//	SendMessage(m_hWnd,WM_CLOSE,0,0);
}