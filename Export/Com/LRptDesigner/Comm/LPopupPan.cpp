///////////////////////////////////////////////////////////////////////////////////////////////
//@模块		:	通用弹出画板基类（展现类似菜单）
//@作者		:	罗智勇
//@创建时间	:	2005-09-16
///////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lpopuppan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MENUCLASS       MAKEINTATOM(0x8000)
/////////////////////////////////////////////////////////////////////////////
// CLPopupPan

CLPopupPan::CLPopupPan(CPoint p, LPVOID pDefault, CWnd* pParentWnd):m_timer(0),m_bMouseIN(FALSE)
	,m_bLMouseDown(FALSE),m_bRMouseDown(FALSE),m_lpDefault_V(NULL),m_bMouseINOld(FALSE),m_bCanHide(FALSE)
{
	CLPopupPan::Create(p,pDefault,pParentWnd);
}
CLPopupPan::CLPopupPan():m_pParent(NULL),m_lpDefault_V(NULL),m_bMouseINOld(FALSE),m_bCanHide(FALSE)
{
    
}
BOOL CLPopupPan::Create(CPoint p, LPVOID pDefault, CWnd* pParentWnd)
{
	Initialise();
	m_bCanHide=FALSE;
	m_pParent=pParentWnd;
	m_lpDefault_V=pDefault;
	m_nMargin           = ::GetSystemMetrics(SM_CXEDGE);
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);
	//m_pParent->ClientToScreen(&p);
	if (!CWnd::CreateEx(WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE,
		szClassName,NULL,WS_POPUP,p.x, p.y, 100, 100, 
        pParentWnd->GetSafeHwnd(), 0, NULL))
			return FALSE;
	SetWindowLong(m_hWnd,GWL_STYLE,WS_CHILD);
//	SetOwner(pParentWnd);
	SetWindowSize();
	UpdateWindow();
	ShowWindow(SW_SHOW);
	CreateToolTips();
	SetCapture();
	return TRUE;
}
CLPopupPan::~CLPopupPan()
{
	
}


BEGIN_MESSAGE_MAP(CLPopupPan, CWnd)
	//{{AFX_MSG_MAP(CLPopupPan)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_ACTIVATEAPP()
	ON_WM_NCDESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLPopupPan message handlers
void CLPopupPan::SetWindowSize()
{
	GetWindowSize(m_WindowRect);
	SetWindowPos((CWnd*)HWND_TOP,0,0,m_WindowRect.Width(),
		m_WindowRect.Height(),SWP_NOMOVE|SWP_SHOWWINDOW);
	
}
void CLPopupPan::OnMouseMove(UINT nFlags, CPoint point) 
{
	DWORD pos = GetMessagePos();
    m_bMouseIN=m_WindowRect.PtInRect(CPoint(LOWORD(pos), HIWORD(pos)));
	if(m_bMouseINOld && !m_bMouseIN)
		OnMouseOut();
	else if(m_bMouseIN){
		m_bCanHide=TRUE;
		OnMouseOver(nFlags,point);
	}
	m_bMouseINOld=m_bMouseIN;

	CWnd::OnMouseMove(nFlags, point);
}

void CLPopupPan::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLMouseDown=m_bMouseIN;
    if (!m_bLMouseDown){
        EndSelection(LPN_SELENDCANCEL);
		GetCursorPos(&point);
		//有必要回放鼠标消息
		mouse_event(MOUSEEVENTF_LEFTDOWN,
			point.x,point.y,0,GetMessageExtraInfo());
	}else{
		OnMouseDown(nFlags,point,TRUE);
	}
}
void CLPopupPan::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_bRMouseDown=m_bMouseIN;
	CWnd::OnRButtonDown(nFlags, point);
	if (!m_bRMouseDown){
        EndSelection(LPN_SELENDCANCEL);
		GetCursorPos(&point);
		//有必要回放鼠标消息
		mouse_event(MOUSEEVENTF_RIGHTDOWN,
			point.x,point.y,0,GetMessageExtraInfo());
	}else{
		OnMouseDown(nFlags,point,FALSE);
	}
}

BOOL CLPopupPan::IsMouseIN()
{
	return m_bMouseIN;
}

void CLPopupPan::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//m_bLMouseDown=FALSE;
	m_bLMouseDown=FALSE;
	CWnd::OnLButtonUp(nFlags, point);
	DWORD pos = GetMessagePos();
    point = CPoint(LOWORD(pos), HIWORD(pos));
    
	if (m_WindowRect.PtInRect(point))
		OnMouseUp(nFlags,point,TRUE);
	if(m_bCanHide)
		EndSelection(LPN_SELENDOK);
	else
		m_bCanHide=TRUE;
}

void CLPopupPan::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bRMouseDown=FALSE;
	CWnd::OnRButtonUp(nFlags, point);
	DWORD pos = GetMessagePos();
    point = CPoint(LOWORD(pos), HIWORD(pos));
    if (m_WindowRect.PtInRect(point)){
		OnMouseUp(nFlags,point,TRUE);
		EndSelection(LPN_SELENDOK);
	}
}

BOOL CLPopupPan::IsLeftButtonDown()
{
	return m_bLMouseDown;
}

BOOL CLPopupPan::IsRightButtonDown()
{
	return m_bRMouseDown;
}


BOOL CLPopupPan::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	ShowToolTips(pMsg);
	if (GetCapture()->GetSafeHwnd() != m_hWnd)
        SetCapture(); 
	return CWnd::PreTranslateMessage(pMsg);
}
void CLPopupPan::EndSelection(int nMessage)
{
	ReleaseCapture();
	LPVOID ptrV=GetSelectValue(nMessage);
	m_pParent->SendMessage(nMessage, (WPARAM) ptrV, 0);
    DestroyWindow();
}
void CLPopupPan::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CWnd::OnActivateApp(bActive, hTask);
	if (!bActive)
		 EndSelection(LPN_SELENDCANCEL);

}

void CLPopupPan::OnNcDestroy() 
{
	CWnd::OnNcDestroy();
	delete this;
}

void CLPopupPan::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
    GetClientRect(rect);
	OnDraw(&dc,rect);
    dc.DrawEdge(rect, EDGE_RAISED, BF_RECT);
}

BOOL CLPopupPan::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	return CWnd::OnQueryNewPalette();
}

void CLPopupPan::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CWnd::OnPaletteChanged(pFocusWnd);
	if (pFocusWnd->GetSafeHwnd() != GetSafeHwnd())
        Invalidate();
	// TODO: Add your message handler code here
	
}

void CLPopupPan::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	ReleaseCapture();
	// TODO: Add your message handler code here
}

void CLPopupPan::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

HBRUSH CLPopupPan::HBrushDitherCreate(COLORREF rgbFace, COLORREF rgbHilight)
{
	struct    
	{
		BITMAPINFOHEADER    bmiHeader;        
		RGBQUAD             bmiColors[16];       
	} bmi;     
	HBRUSH          hBrush=NULL;     
	DWORD           patGray[8];    
	HDC             hDC;    
	HBITMAP         hBmp;   
	bmi.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);     
	bmi.bmiHeader.biWidth        = 8;     
	bmi.bmiHeader.biHeight       = 8;     
	bmi.bmiHeader.biPlanes       = 1;     
	bmi.bmiHeader.biBitCount     = 1;     
	bmi.bmiHeader.biCompression  = BI_RGB;     
	bmi.bmiHeader.biSizeImage    = 0;     
	bmi.bmiHeader.biXPelsPerMeter= 0;     
	bmi.bmiHeader.biYPelsPerMeter= 0;     
	bmi.bmiHeader.biClrUsed      = 0;     
	bmi.bmiHeader.biClrImportant = 0;      
	bmi.bmiColors[0].rgbBlue     = GetBValue(rgbFace);     
	bmi.bmiColors[0].rgbGreen    = GetGValue(rgbFace);     
	bmi.bmiColors[0].rgbRed      = GetRValue(rgbFace);     
	bmi.bmiColors[0].rgbReserved = 0;      
	bmi.bmiColors[1].rgbBlue     = GetBValue(rgbHilight);     
	bmi.bmiColors[1].rgbGreen    = GetGValue(rgbHilight);     
	bmi.bmiColors[1].rgbRed      = GetRValue(rgbHilight);     
	bmi.bmiColors[1].rgbReserved = 0; 
	patGray[6]=patGray[4]=patGray[2]=patGray[0]=0x5555AAAAL;     
	patGray[7]=patGray[5]=patGray[3]=patGray[1]=0xAAAA5555L;    
	hDC=::GetDC(NULL); 
	hBmp=CreateDIBitmap(hDC, &bmi.bmiHeader, CBM_INIT, patGray
		,(LPBITMAPINFO)&bmi, DIB_RGB_COLORS);     
	::ReleaseDC(NULL, hDC);  
	if (NULL!=hBmp){         
 		hBrush=CreatePatternBrush(hBmp);         
 		DeleteObject(hBmp);         
	}      
	return hBrush;
}
