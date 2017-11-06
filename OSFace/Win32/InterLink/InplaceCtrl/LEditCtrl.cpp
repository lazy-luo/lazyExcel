// LEditCtrl.cpp: implementation of the CLEditCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LEditCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//static LOGFONT DEFAULT_LOGFONT={-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, _T("宋体")};

CLEditCtrl::CLEditCtrl(HWND hParent):m_hWnd(NULL),m_hParent(hParent)
,m_lngOldProc(0),m_hBrush(NULL),m_clrBk(COLOR_BKGRD),m_clrFore(COLOR_FOREDATA)
,m_fontDefault(NULL)
{
	m_fontDefault=::CreateFontIndirect(&DEFAULT_LOGFONT);
}

CLEditCtrl::~CLEditCtrl()
{
	if(m_hWnd){
		if(m_lngOldProc!=0){
			SetWindowLong(m_hWnd,GWL_WNDPROC,m_lngOldProc);
			m_lngOldProc=0;
		}
		//PostMessage(m_hWnd,WM_QUIT,0,0);
		m_hWnd=NULL;
	}
	if(m_hBrush)
		DeleteObject(m_hBrush);
	if(m_fontDefault)
		DeleteObject(m_fontDefault);
}
void CLEditCtrl::setFont(HFONT hFont)
{
	if(m_hWnd){
		::SendMessage(m_hWnd,WM_SETFONT,(WPARAM)hFont,0);
	}
}
void CLEditCtrl::setBkColor(COLORREF clr)
{
	//if(m_clrBk!=clr){
		if(m_hBrush)
			DeleteObject(m_hBrush);
		m_clrBk=clr;
		m_hBrush=CreateSolidBrush(clr);
	//}
}
void CLEditCtrl::setVisible(BOOL bShow){
	if(m_hWnd){
		ShowWindow(m_hWnd,bShow?SW_SHOW:SW_HIDE);
	}
}
BOOL CLEditCtrl::getVisible()
{
	if(m_hWnd){
		return IsWindowVisible(m_hWnd);
	}
	return FALSE;
}
LONG CLEditCtrl::getLongValue()
{
	return 0;
}
void CLEditCtrl::SetForeColor(COLORREF clr)
{
	m_clrFore=clr;
}
LPTSTR CLEditCtrl::getStringValue()
{
	LONG nLen;
	char* ptr=NULL;
	if(m_hWnd){
		nLen=::SendMessage(m_hWnd,EM_LINELENGTH,1,0);
		ptr=new char[nLen+1];
		GetWindowText(m_hWnd,ptr,nLen+1);
		ptr[nLen]='\0';
		
	}
	return ptr;
}
LPTSTR CLEditCtrl::getTag()
{
	return NULL;
}
void CLEditCtrl::setLongValue(LONG nVal)
{
	
}
void CLEditCtrl::setStringValue(LPTSTR ptrV)
{
	if(m_hWnd){
		SetWindowText(m_hWnd,ptrV);
	}
}
void CLEditCtrl::setTag(LPTSTR ptrV)
{
	
}
LRESULT CLEditCtrl::SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam)
{
	if(m_hWnd){
		return ::SendMessage(m_hWnd,Msg,wParam,lParam);
	}else
		return 0;
}
void CLEditCtrl::setPosition(LONG nLeft,LONG nTop,LONG nRight,LONG nBottom)
{
	RECT rct;
	rct.left=nLeft;
	rct.top=nTop;
	rct.right=nRight;
	rct.bottom=nBottom;
	if(m_hWnd){
		MoveWindow(m_hWnd,nLeft,nTop,nRight-nLeft,nBottom-nTop,TRUE);
	}else{
		if(!Create(rct,m_hParent)){
			ASSERT(FALSE);
		}
	}
	
	::SendMessage(m_hWnd,EM_SETRECT,0,(LPARAM)&rct);
	setVisible(TRUE);
	SetFocus(m_hWnd);
	setFont(m_fontDefault);
}

BOOL CLEditCtrl::Create(RECT& rct,HWND hParent)
{
	m_hWnd=CreateWindow("EDIT","",ES_LEFT | ES_AUTOHSCROLL | 
		WS_TABSTOP | WS_CHILD,
		rct.left,rct.top,rct.right-rct.left,
		rct.bottom-rct.top,hParent,NULL,NULL,NULL);
	m_lngOldProc=SetWindowLong(m_hWnd,GWL_WNDPROC,(LONG)WndProc);
	SetProp(m_hWnd,PROP_CTRL,this);
	return (m_hWnd!=NULL);
}
LRESULT CLEditCtrl::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	CLEditCtrl* ptrCtrl=(CLEditCtrl*)GetProp(hWnd,PROP_CTRL);
	ASSERT(NULL!=ptrCtrl);
	if(0==ptrCtrl->m_lngOldProc){
		ASSERT(FALSE);
		return 0;
	}
	switch(Msg)
	{
	case LZY_MSG_CTLCOLOR:
		if(ptrCtrl->m_hBrush){
			SetBkColor((HDC)wParam,ptrCtrl->m_clrBk);
			SetTextColor((HDC)wParam,ptrCtrl->m_clrFore);
			return (LONG)ptrCtrl->m_hBrush;
		}
		break;
	case WM_ERASEBKGND:
		{
			if(ptrCtrl->m_hBrush){
				RECT rct;
				GetClientRect(ptrCtrl->m_hWnd,&rct);
				FillRect((HDC)wParam,&rct,ptrCtrl->m_hBrush);
				return 1;
			}
		break;
		}
	case WM_KEYDOWN:
		{
			BOOL bReturn=FALSE;
			ptrCtrl->OnKeyDown(wParam,lParam,bReturn);
			if(bReturn)
				return 0;
			break;
		}
	}
	return CallWindowProc((WNDPROC)(ptrCtrl->m_lngOldProc),
		ptrCtrl->m_hWnd,Msg,wParam,lParam);
}

void CLEditCtrl::OnKeyDown(WPARAM wParam, LPARAM lParam,BOOL& bReturn)
{
	BOOL bSendParent=FALSE;
	switch(wParam){
	case VK_UP:
	case VK_DOWN:
	case VK_TAB:
	case VK_RETURN:
		bSendParent=TRUE;
		break;
	case VK_LEFT:
		{
			//看看是否输入光标已经到达最开始位置
			LONG nPos=0;
			LONG nEndPos=0;
			::SendMessage(m_hWnd,EM_GETSEL,(LONG)(&nPos),(LONG)(&nEndPos));
			if(nPos<1){
				bSendParent=TRUE;
			}
			break;
		}
	case VK_RIGHT:
		{
			LONG nCount=0;
			nCount=::SendMessage(m_hWnd,EM_LINELENGTH,1,0);
			LONG nPos=0;
			LONG nEndPos=0;
			::SendMessage(m_hWnd,EM_GETSEL,(LONG)(&nPos),(LONG)(&nEndPos));
			if(nPos>=nCount){
				bSendParent=TRUE;
			}
			break;
		}
	}
	if(bSendParent){
		bReturn=TRUE;
		::SendMessage(m_hParent,WM_KEYDOWN,wParam,lParam);
	}else
		bReturn=FALSE;
}
