// lpickerbtn.cpp : implementation file
//

#include "stdafx.h"
#include "..\LRptDesigner.h"
#include "lpickerbtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLPickerBtn

CLPickerBtn::CLPickerBtn(LONG nDefault):m_lngValue(nDefault),m_bLeftBtnDown(FALSE),m_timer(0),
	m_bInLeftBtn(FALSE),m_bRightBtnDown(FALSE),m_bMouseOut(TRUE),m_bInRightBtn(FALSE),
	m_ptrParent(NULL),m_hBitmapID(0),m_bActive(FALSE),m_bTrackSelection(FALSE)
{
}

CLPickerBtn::~CLPickerBtn()
{
	ClearTimer();
}


BEGIN_MESSAGE_MAP(CLPickerBtn, CWnd)
	//{{AFX_MSG_MAP(CLPickerBtn)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(LPN_SELENDOK,     OnSelEndOK)
    ON_MESSAGE(LPN_SELENDCANCEL, OnSelEndCancel)
    ON_MESSAGE(LPN_SELCHANGE,    OnSelChange)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLPickerBtn message handlers
BOOL CLPickerBtn::Create(CRect rect, CWnd * pParentWnd, UINT nID,LONG nBmpID)
{
	SetBitmapRes(nBmpID);
	
	ASSERT(pParentWnd);
	m_ptrParent=pParentWnd;
	if(!CWnd::Create(NULL,NULL, WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID))
		return FALSE;
	return TRUE;
}
void CLPickerBtn::SetBitmapRes(LONG nResID)
{
	if(nResID==0)return;
	m_hBitmapID=nResID;
}
LONG CLPickerBtn::GetValue()
{
	return m_lngValue;
}
void CLPickerBtn::DrawItem(CDC* pDC)
{
	BOOL bEnable=IsWindowEnabled();
	CRect rect;
	GetClientRect(&rect);
	CRect rcLeft(rect.left, rect.top, rect.right - 10, rect.bottom);
	CRect rcRight(rect.right - 10, rect.top, rect.right, rect.bottom);
	
	CBrush brBack(GetSysColor(COLOR_BTNFACE));
	pDC->FillRect(rect, &brBack);
	
	CRect rcImage(rcLeft.left+2, rcLeft.top+2, rcLeft.right-2, rcLeft.bottom-2);
	
	if (m_bInLeftBtn){ 
		if(!m_bRightBtnDown)
			pDC->Draw3dRect(&rcRight, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW)); 
		else{
			rcRight.left--;
			pDC->Draw3dRect(&rcRight, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT)); 
		}
		if(!m_bLeftBtnDown)
			pDC->Draw3dRect(&rcLeft, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW));
		else{
			rcLeft.right++;
			pDC->Draw3dRect(&rcLeft, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
			rcImage.OffsetRect(1, 1);
		}
	}else if(m_bInRightBtn || m_bRightBtnDown){
		pDC->Draw3dRect(&rcLeft, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW));
		if(!m_bRightBtnDown){
			pDC->Draw3dRect(&rcRight, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW)); 
		}else{
			rcRight.left--;
			pDC->Draw3dRect(&rcRight, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
		}
	}else if(m_bMouseOut){
		;
	}
	OnDrawButton(pDC, rcImage);
	DrawArrow(pDC, &rcRight,bEnable);	
}
void CLPickerBtn::DrawArrow(CDC* pDC,CRect* pRect,BOOL bEnable)
{
	if(bEnable){
		DrawAArrow(pDC,pRect,RGB(0,0,0));
	}else{
		DrawAArrow(pDC,pRect,GetSysColor(COLOR_BTNHIGHLIGHT));
#if	1
		CRect rect=*pRect;
		rect.left--;
		rect.right--;
		rect.top--;
		rect.bottom--;
		DrawAArrow(pDC,&rect,GetSysColor(COLOR_BTNSHADOW));
#endif
	}
}
void CLPickerBtn::DrawAArrow(CDC * pDC, CRect * pRect,COLORREF clrBk)
{
	ASSERT(pRect);
	CPoint ptCenter(pRect->left + (pRect->Width() / 2), pRect->top + (pRect->Height() / 2));

	CPoint ptArrow[3];	

	ptArrow[0].x = ptCenter.x-2;
	ptArrow[0].y = ptCenter.y-1;

	ptArrow[1].x = ptCenter.x;
	ptArrow[1].y = ptCenter.y+1;

	ptArrow[2].x = ptCenter.x+2;
	ptArrow[2].y = ptCenter.y-1;

	CBrush brBlack(clrBk);
	CPen   pen(PS_SOLID,1,clrBk);
  	CBrush * pOldBrush = pDC->SelectObject(&brBlack);
	CPen* pOldPen=pDC->SelectObject(&pen);
	pDC->Polygon(ptArrow, 3);  
  	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	brBlack.DeleteObject();
	pen.DeleteObject();
}
void CLPickerBtn::DrawTransInvertPic(HDC hDstDC, INT nXDest, INT nYDest, 
									 INT nWidth,INT nHeight, HBITMAP bmp, 
									 INT nXSrc, INT nYSrc,COLORREF bgcolor)
{
    HDC	hdc;
    HBITMAP hBitmap;
    HBITMAP hdcOldBmp;
    HDC hMaskDC;

    HBITMAP hdcOldBmpMsk;
    HBRUSH hBru;
    HBRUSH hbrShadow;
    HBRUSH hbrHilight;
    HBRUSH hOldBrush;
    COLORREF BkColor;
    
    HDC hSaveDC;
    COLORREF lngOrigColor;
    HBITMAP holdSaveBmp;
    HBITMAP hMaskBmp;
    
    HDC hVertDC;
    HBITMAP hVertBmp;
    HBITMAP hOldVertBmp;
    RECT rct;
    
    hdc = CreateCompatibleDC(hDstDC);
    hBitmap = CreateCompatibleBitmap(hdc, nWidth, nHeight);
    hdcOldBmp = (HBITMAP)SelectObject(hdc, hBitmap);
    //创建备份对象
    hSaveDC = CreateCompatibleDC(hDstDC);
    holdSaveBmp = (HBITMAP)SelectObject(hSaveDC, bmp);
    //创建黑白位图
    hVertDC = CreateCompatibleDC(hSaveDC);
    hVertBmp = CreateBitmap(nWidth, nHeight, 1, 1, NULL);
    hOldVertBmp = (HBITMAP)SelectObject(hVertDC, hVertBmp);
    //得到原始位图屏蔽颜色
    BkColor = GetPixel(hSaveDC, 0, 0);
	//bgcolor=BkColor;
    //OleTranslateColor BkColor, 0, BkColor
    lngOrigColor = SetBkColor(hSaveDC, BkColor);
    BitBlt(hVertDC, 0, 0, nWidth, nHeight, hSaveDC, 0, 0, SRCCOPY);
    SetBkColor(hSaveDC, lngOrigColor);
        
    //创建离屏DC及离屏位图
    hMaskDC = CreateCompatibleDC(hSaveDC);
    hMaskBmp = CreateCompatibleBitmap(hSaveDC, nWidth, nHeight);
    hdcOldBmpMsk = (HBITMAP)SelectObject(hMaskDC, hMaskBmp);
    
    BitBlt(hMaskDC, 0, 0, nWidth, nHeight, hSaveDC, 0, 0, SRCCOPY);
    //屏蔽掉底色
    BitBlt(hMaskDC, 0, 0, nWidth, nHeight, hVertDC, 0, 0, SRCPAINT);
    //转换背景色
	//COLORREF bgcolor=hSaveDC.GetPixel(0,0);
    hBru = CreateSolidBrush(bgcolor);
    
    rct.left = 0;
    rct.top = 0;
    rct.right = nWidth;
    rct.bottom= nHeight;
    
    PatBlt(hdc, 0, 0, nWidth, nHeight, WHITENESS);
    
    SetBkColor(hMaskDC, bgcolor);
    BitBlt(hdc, 0, 0, nWidth, nHeight, hMaskDC, nXSrc, nYSrc, SRCCOPY);
    
    SetBkColor(hMaskDC, GetSysColor(COLOR_BTNHIGHLIGHT));
    BitBlt(hdc, 0, 0, nWidth, nHeight, hMaskDC, nXSrc, nYSrc, SRCPAINT);

    FillRect(hMaskDC, &rct, hBru);

    SetBkColor(hMaskDC, RGB(0, 0, 0));
    SetTextColor(hMaskDC, RGB(255, 255, 255));
    
    hbrHilight = CreateSolidBrush(bgcolor | GetSysColor(COLOR_BTNHIGHLIGHT));
    hbrShadow = CreateSolidBrush(bgcolor & (GetSysColor(COLOR_BTNSHADOW)));
    hOldBrush = (HBRUSH)SelectObject(hMaskDC, hbrHilight);
        
    BitBlt(hMaskDC, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xE20746);
    BitBlt(hDstDC, nXDest + 1, nYDest + 1, nWidth, nHeight, hMaskDC, 0, 0, SRCCOPY);
    BitBlt(hMaskDC, 1, 1, nWidth, nHeight, hdc, 0, 0, 0xE20746);
    SelectObject(hMaskDC, hbrShadow);
    BitBlt(hMaskDC, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xE20746);
    BitBlt(hDstDC, nXDest, nYDest, nWidth, nHeight, hMaskDC, 0, 0, SRCCOPY);
    SelectObject(hdc, hdcOldBmp);
    DeleteDC(hdc);
    SelectObject(hMaskDC, hOldBrush);
    SelectObject(hMaskDC, hdcOldBmpMsk);
    DeleteDC(hMaskDC);
    SelectObject(hSaveDC, holdSaveBmp);
    DeleteDC(hSaveDC);
    SelectObject(hVertDC, hOldVertBmp);
    DeleteDC (hVertDC);
    
    DeleteObject(hVertBmp);
    DeleteObject(hMaskBmp);
    DeleteObject(hbrShadow);
    DeleteObject(hbrHilight);
    DeleteObject(hBitmap);
    DeleteObject(hBru);
}

void CLPickerBtn::DrawTransPic(CDC* pDC, CBitmap* pBitmap, int X, int Y,BOOL bInvert)
{
	COLORREF	crOldBack = pDC->SetBkColor(0x00FFFFFF);
	COLORREF	crOldText = pDC->SetTextColor(0x00000000);

	CDC dcImage, dcTrans;

	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
	CBitmap* pOldBitmapImage = dcImage.SelectObject(pBitmap);

	// Create the mask bitmap
	BITMAP bitmap;
	pBitmap->GetBitmap(&bitmap);
	CBitmap bitmapTrans;
	bitmapTrans.CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	COLORREF crTrans=dcImage.GetPixel(0,0);
	dcImage.SetBkColor(crTrans);
	
	dcTrans.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &dcImage, 0, 0, SRCCOPY);
	
	if (bInvert)
	{
		CDC dcInvert;
		CBitmap bitmapInvert;

		dcInvert.CreateCompatibleDC(pDC);
		bitmapInvert.CreateCompatibleBitmap(&dcImage, bitmap.bmWidth, bitmap.bmHeight);
		CBitmap* pOldBitmapInvert = dcInvert.SelectObject(&bitmapInvert);
		dcInvert.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &dcImage, 0, 0, NOTSRCCOPY);
		CBrush brush(0x0080FFFF);
		CBrush* pOldBrush = dcInvert.SelectObject(&brush);
		dcInvert.PatBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, PATINVERT);

		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcInvert, 0, 0, SRCINVERT);
		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcTrans, 0, 0, SRCAND);
		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcInvert, 0, 0, SRCINVERT);

		dcInvert.SelectObject(pOldBrush);
		dcInvert.SelectObject(pOldBitmapInvert);
		brush.DeleteObject();
	}
	else
	{
		// Do the work - True Mask method - cool if not actual display
		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcImage, 0, 0, SRCINVERT);
		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcTrans, 0, 0, SRCAND);
		pDC->BitBlt(X, Y, bitmap.bmWidth, bitmap.bmHeight, &dcImage, 0, 0, SRCINVERT);
	}
	
	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);
}

void CLPickerBtn::SetTimer()
{
	if(m_timer==0)
		m_timer=::SetTimer(m_hWnd,TIMER_ID,10,NULL);
}

void CLPickerBtn::ClearTimer()
{
	if(m_timer){
		KillTimer(m_timer);
		m_timer=0;
	}
}

void CLPickerBtn::OnSelected()
{
	if(m_ptrParent){
		PICKERBTNHDR hdr;
		
		hdr.hwndFrom = m_hWnd;
		hdr.idFrom = GetDlgCtrlID();
		hdr.code = 0;//PB_SELCHANGE;
		hdr.iValue= m_lngValue;
		m_ptrParent->SendMessage(WM_NOTIFY, hdr.idFrom, (LPARAM)&hdr);
	}
}

void CLPickerBtn::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	Hitest(pt);
	if(m_bMouseOut){
		ClearTimer();
		OnStatusChange();
	}
	CWnd::OnTimer(nIDEvent);
}
void CLPickerBtn::Hitest(const CPoint &pt)
{
	CRect rect;
	GetClientRect(&rect);
	CRect rcLeft(rect.left, rect.top, rect.right - 10, rect.bottom);
	CRect rcRight(rect.right - 10, rect.top, rect.right, rect.bottom);
	BOOL bTemp,bRaise=FALSE;
	if(PtInRect(&rect,pt)){
		bTemp=m_bMouseOut;
		if(bTemp)
			bRaise=TRUE;
		m_bMouseOut=FALSE;
		bTemp=m_bInLeftBtn;
		m_bInLeftBtn=PtInRect(&rcLeft,pt);
		if(!bRaise && bTemp!=m_bInLeftBtn)
			bRaise=TRUE;
		bTemp=m_bInRightBtn;
		if(!m_bInLeftBtn)
			m_bInRightBtn=PtInRect(&rcRight,pt);
		else
			m_bInRightBtn=FALSE;
		if(!bRaise && bTemp!=m_bInRightBtn)
			bRaise=TRUE;
	}else{
		bRaise=(!m_bMouseOut || m_bInRightBtn || m_bInLeftBtn);
		m_bMouseOut=TRUE;
		m_bInRightBtn=FALSE;
		m_bInLeftBtn=FALSE;
	}
	if(bRaise)
		OnStatusChange();
}

void CLPickerBtn::OnStatusChange()
{
	Invalidate();
}

void CLPickerBtn::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);
	CWnd::PreSubclassWindow();
}

void CLPickerBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	DrawItem(&dc);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CLPickerBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Hitest(point);
	SetTimer();
	CWnd::OnMouseMove(nFlags, point);
}

void CLPickerBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftBtnDown=m_bInLeftBtn;
	m_bRightBtnDown=m_bInRightBtn;
	ASSERT(!(m_bLeftBtnDown && m_bRightBtnDown));
	CWnd::OnLButtonDown(nFlags, point);
	if(m_bRightBtnDown || m_bLeftBtnDown)
		OnStatusChange();
	if(m_bRightBtnDown){
		OnPopup();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CLPickerBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLeftBtnDown && m_bInLeftBtn){
		OnSelected();
	}
	m_bLeftBtnDown=FALSE;
	m_bRightBtnDown=FALSE;
	OnStatusChange();
	CWnd::OnLButtonUp(nFlags, point);
}

LONG CLPickerBtn::OnSelEndOK(UINT lParam, LONG /*wParam*/)
{
	
    LONG vNew = (LONG) lParam;
    m_bActive = FALSE;
    m_lngValue=((LONG) lParam);
	
    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(LPN_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(LPN_SELENDOK, lParam, (WPARAM) GetDlgCtrlID());
    }
	
    if (vNew !=m_lngValue)
        if (pParent) pParent->SendMessage(LPN_SELCHANGE, lParam, (WPARAM) GetDlgCtrlID());
	
	m_bRightBtnDown=FALSE;
	OnStatusChange();
	OnSelected();
    return TRUE;
}

LONG CLPickerBtn::OnSelEndCancel(UINT lParam, LONG /*wParam*/)
{
	
    m_bActive = FALSE;
    //m_lngValue=((LONG) lParam);
    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(LPN_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(LPN_SELENDCANCEL, lParam, (WPARAM) GetDlgCtrlID());
    }
	m_bRightBtnDown=FALSE;
	OnStatusChange();
    return TRUE;
}

LONG CLPickerBtn::OnSelChange(UINT lParam, LONG /*wParam*/)
{
	
    if (m_bTrackSelection) m_lngValue=((LONG) lParam);

    CWnd *pParent = GetParent();
    if (pParent) pParent->SendMessage(LPN_SELCHANGE, lParam, (WPARAM) GetDlgCtrlID());
	
    return TRUE;
}
void CLPickerBtn::SetValue(LONG val)
{
	m_lngValue=val;
}