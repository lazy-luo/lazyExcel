// LFlatComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "LFlatComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLFlatComboBox

CLFlatComboBox::CLFlatComboBox():m_bLBtnDown(FALSE),m_nHeight(20)
{
}

CLFlatComboBox::~CLFlatComboBox()
{
}


BEGIN_MESSAGE_MAP(CLFlatComboBox, CComboBox)
	//{{AFX_MSG_MAP(CLFlatComboBox)
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_TIMER()
		ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CLFlatComboBox::Offset()
{
	// Thanks to Todd Brannam for this suggestion...
	return ::GetSystemMetrics(SM_CXHTHUMB);
}

/////////////////////////////////////////////////////////////////////////////
// CCoolComboBox message handlers

void CLFlatComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetTimer(1,10,NULL);
	
	CComboBox::OnMouseMove(nFlags, point);
}

void CLFlatComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLBtnDown = true;
	
	CComboBox::OnLButtonDown(nFlags, point);
}

void CLFlatComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLBtnDown = false;
	Invalidate();
	
	CComboBox::OnLButtonUp(nFlags, point);
}

void CLFlatComboBox::OnTimer(UINT nIDEvent) 
{
	POINT pt;
	GetCursorPos(&pt);
	CRect rcItem;
	GetWindowRect(&rcItem);

	static bool bPainted = false;

	// OnLButtonDown, show pressed.
	if (m_bLBtnDown==true) {
		KillTimer (1);
		if (bPainted == true) {
			DrawMe(FC_DRAWPRESSD, ::GetSysColor(COLOR_BTNSHADOW),
				::GetSysColor(COLOR_BTNHIGHLIGHT));
			bPainted = false;
		}
		return;
	}

	// If mouse leaves, show flat.
	if (!rcItem.PtInRect(pt)) {
		KillTimer (1);
		if (bPainted == true) {
			DrawMe(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE),
				::GetSysColor(COLOR_BTNFACE));
			bPainted = false;
		}
		return;
	}

	// On mouse over, show raised.
	else {
		if (bPainted == true)
			return;
		else {
			bPainted = true;
			DrawMe(FC_DRAWRAISED, ::GetSysColor(COLOR_BTNSHADOW),
				::GetSysColor(COLOR_BTNHIGHLIGHT));
		}
	}
	
	CComboBox::OnTimer(nIDEvent);
}

void CLFlatComboBox::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	Default();
	DrawMe(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE),
		::GetSysColor(COLOR_BTNFACE));
	
	// Do not call CComboBox::OnPaint() for painting messages
}
/////////////////////////////////////////////////////////////////////////////
// CLFlatComboBox message handlers

void CLFlatComboBox::DrawMe(LONG dwStyle, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	
	CRect rcItem;
	GetClientRect(&rcItem);
	CDC* pDC = GetDC();
	
	// Cover up dark 3D shadow.
	pDC->Draw3dRect(rcItem, clrTopLeft, clrBottomRight);
	rcItem.DeflateRect(1,1);
	
	if (!IsWindowEnabled()) {
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
	}
	
	else {
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE),
			::GetSysColor(COLOR_BTNFACE));
	}

	// Cover up dark 3D shadow on drop arrow.
	rcItem.DeflateRect(1,1);
	rcItem.left = rcItem.right-Offset();
	pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE),
		::GetSysColor(COLOR_BTNFACE));
	
	// Cover up normal 3D shadow on drop arrow.
	rcItem.DeflateRect(1,1);
	pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE),
		::GetSysColor(COLOR_BTNFACE));
	
	if (!IsWindowEnabled()) {
		return;
	}

	switch (dwStyle)
	{
	case FC_DRAWNORMAL:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
		rcItem.left -= 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
		break;

	case FC_DRAWRAISED:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNSHADOW));
		break;

	case FC_DRAWPRESSD:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		rcItem.OffsetRect(1,1);
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNSHADOW),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
		break;
	}

	ReleaseDC(pDC);
	
}


void CLFlatComboBox::SetClientHeight(LONG nVal)
{
	m_nHeight=nVal;
	SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_FRAMECHANGED);
}

LONG CLFlatComboBox::GetClientHeight()
{
	return m_nHeight;
}
