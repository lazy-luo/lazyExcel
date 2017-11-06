// LColorPicker.cpp : implementation file
//

#include "stdafx.h"
#include "LColorPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLColorPicker

CLColorPicker::CLColorPicker(LONG nDefault):CLPickerBtn(nDefault)
{

}

CLColorPicker::~CLColorPicker()
{
	
}

void CLColorPicker::OnPopup()
{
    CRect rect;
    GetWindowRect(rect);
    new CLColorPan(CPoint(rect.left, rect.bottom),
                     GetValue(),
                     this);

    CWnd *pParent = GetParent();
    if (pParent)
        pParent->SendMessage(LPN_DROPDOWN, (LPARAM)GetColor(), (WPARAM) GetDlgCtrlID());
    
}


void CLColorPicker::OnDrawButton(CDC * pDC, CRect& rect)
{
	CRect rc = rect;
	rc.DeflateRect(2, 2);
	BOOL bEnable=IsWindowEnabled();
	COLORREF cr =GetColor();
	if(m_hBitmapID>0){
		CBitmap bmp;
		HBITMAP hBitmap=LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(m_hBitmapID));
		bmp.Attach(hBitmap);
		if(bEnable)
			DrawTransPic(pDC,&bmp,rect.left,rect.top,FALSE);
		else
			DrawTransInvertPic(pDC->GetSafeHdc(),rect.left,rect.top,rect.right-rect.left-2,
				rect.bottom-rect.top-2,hBitmap);
	}
	CRect rctC(rc.left-1, rc.top+rc.Height()*4/5, rc.right, rc.bottom);

	if(!bEnable){
		cr=GetSysColor(COLOR_BTNSHADOW);
		pDC->FillSolidRect(&rctC,cr);

		CPen pen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
		CPen* pOld=(CPen*)pDC->SelectObject(&pen);
		pDC->MoveTo(rctC.left,rctC.bottom);
		pDC->LineTo(rctC.right,rctC.bottom);
		pDC->LineTo(rctC.right,rctC.top);
		pDC->SelectObject(pOld);
		pen.DeleteObject();
	}else{
		pDC->FillSolidRect(&rctC,cr);
		rctC.InflateRect(0,1);
		CBrush Brush(RGB(168,168,168));
		pDC->FrameRect(&rctC,&Brush);
	}
	
}

void CLColorPicker::SetColor(COLORREF clr)
{
	SetValue((LONG)clr);
}

COLORREF CLColorPicker::GetColor()
{
	return (COLORREF)GetValue();
}
