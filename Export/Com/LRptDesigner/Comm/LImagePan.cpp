// LImagePan.cpp: implementation of the CLImagePan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LImagePan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INVALID_VALUE	-1
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLImagePan::CLImagePan(CPoint p, LONG nDefaultValue, 
								 CWnd* pParentWnd,LONG nRow,LONG nCol,ImageTableEntry*	pBorders)
{
	ASSERT(nCol>0 && nRow>0);
	m_nNumRows=nRow;
	m_nNumColumns=nCol;
	m_nNumImages=nRow*nCol;
	m_pBorders=pBorders;
	ASSERT(m_pBorders!=NULL);
	Create(p,(LPVOID)nDefaultValue,pParentWnd);
	FindCellFromValue(nDefaultValue);
	m_nValue         = m_nInitialValue =nDefaultValue;
	Invalidate();
}

CLImagePan::~CLImagePan()
{
	
}

void CLImagePan::ShowToolTips(LPMSG lpMsg)
{
	if(m_ToolTip.m_hWnd){
		m_ToolTip.RelayEvent(lpMsg);
	}
}
void CLImagePan::OnMouseOver(UINT nFlags, CPoint point)
{
	int nNewSelection = INVALID_VALUE;
	
	point.x -= m_nMargin;
	point.y -= m_nMargin;

	nNewSelection = GetIndex(point.y / m_nBoxSize, point.x / m_nBoxSize);

	if (nNewSelection < 0 || nNewSelection >= m_nNumImages)
	{
		return;
	}
	if (nNewSelection != m_nCurrentSel)
		ChangeSelection(nNewSelection);
}
void CLImagePan::OnMouseOut()
{
	CClientDC dc(this);
	DrawCell(&dc, m_nCurrentSel,TRUE);
	m_nCurrentSel=INVALID_VALUE;
}
void CLImagePan::GetWindowSize(CRect& rct)
{

    CRect rect;
    GetWindowRect(rect);
    rct.SetRect(rect.left, rect.top, 
                         rect.left + m_nNumColumns*m_nBoxSize + 2*m_nMargin,
                         rect.top  + m_nNumRows*m_nBoxSize + 2*m_nMargin);

    CSize ScreenSize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
    if (rct.right > ScreenSize.cx)
        rct.OffsetRect(-(rct.right - ScreenSize.cx), 0);
    if (rct.left < 0)
        rct.OffsetRect( -rct.left, 0);
	
    if (rct.bottom > ScreenSize.cy)
    {
        CRect ParentRect;
        m_pParent->GetWindowRect(ParentRect);
        rct.OffsetRect(0, -(ParentRect.Height() + rct.Height()));
    }
}
void CLImagePan::Initialise()
{
    m_nBoxSize          = 24;
    m_nMargin           = 2*::GetSystemMetrics(SM_CXEDGE);
    m_nCurrentSel       = INVALID_VALUE;
    m_nChosenImageSel  = INVALID_VALUE;
    
    if (m_nBoxSize - 2*m_nMargin - 2 < 5) m_nBoxSize = 5 + 2*m_nMargin + 2;
}
void CLImagePan::OnDraw(CDC* pDC,const RECT& rctClip)
{
	for (int i = 0; i < m_nNumImages; i++)
        DrawCell(pDC, i);
}

void CLImagePan::CreateToolTips()
{
    if (!m_ToolTip.Create(this)) return;

	m_ToolTip.ModifyStyle(WS_CHILD,TTS_ALWAYSTIP );
	m_ToolTip.Update();
    for (int i = 0; i < m_nNumImages; i++)
    {
        CRect rect;
        if (!GetCellRect(i, rect)) continue;
            m_ToolTip.AddTool(this, GetImageName(i), rect, 1);
    }
}
void CLImagePan::FindCellFromValue(LONG nVal)
{
    for (int i = 0; i < m_nNumImages; i++)
    {
        if (GetImage(i) == nVal)
        {
            m_nChosenImageSel = i;
            return;
        }
    }
	m_nChosenImageSel=INVALID_VALUE;
}
int  CLImagePan::GetIndex(int row, int col) const
{
	if (row < 0 || col < 0 || row >= m_nNumRows || col >= m_nNumColumns)
        return INVALID_VALUE;
    else
    {
        return row*m_nNumColumns + col;
    }
}
int  CLImagePan::GetRow(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nNumImages)
        return INVALID_VALUE;
    else
        return nIndex / m_nNumColumns; 
}
int  CLImagePan::GetColumn(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nNumImages)
        return INVALID_VALUE;
    else
        return nIndex % m_nNumColumns; 
}

LPVOID CLImagePan::GetSelectValue(int& nMessage)
{
	return (LPVOID)GetImage(m_nCurrentSel);;
}

void CLImagePan::ChangeSelection(int nIndex)
{
    CClientDC dc(this);        

    if ((m_nCurrentSel >= 0 && m_nCurrentSel < m_nNumImages))
    {
        
        int OldSel = m_nCurrentSel;
        m_nCurrentSel = INVALID_VALUE;
        DrawCell(&dc, OldSel);
    }

    m_nCurrentSel = nIndex;
    DrawCell(&dc, m_nCurrentSel);

    m_nValue = GetImage(m_nCurrentSel);
    m_pParent->SendMessage(LPN_SELCHANGE, (WPARAM) m_nValue, 0);
}

void CLImagePan::DrawCell(CDC* pDC, int nIndex,BOOL bMouseOut)
{
    CRect rect;
    if (!GetCellRect(nIndex, rect)) return;


    if ((m_nChosenImageSel == nIndex && m_nCurrentSel != nIndex) 
		|| (bMouseOut && m_nChosenImageSel == nIndex)){
		HBRUSH hBrush=HBrushDitherCreate(RGB(192,192,192),RGB(255,255,255));
		CBrush brush;
		brush.Attach(hBrush);
		pDC->FillRect(&rect,&brush);
		brush.Detach();
		DeleteObject(hBrush);
    }else 
        pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));

    if (m_nCurrentSel == nIndex && m_nChosenImageSel != nIndex && !bMouseOut) 
        pDC->DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
    else if (m_nChosenImageSel == nIndex)
        pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);

    rect.DeflateRect(m_nMargin/2+1, m_nMargin/2+1);
    LONG resID=GetImageID(nIndex);
	if(resID){
		CBitmap bmp;
		HBITMAP hBitmap=LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(resID));
		bmp.Attach(hBitmap);
		DrawTransPic(pDC,&bmp,rect.left,rect.top,FALSE);
	}
	
}
BOOL CLImagePan::GetCellRect(int nIndex, const LPRECT& rect)
{
    if (nIndex < 0 || nIndex >= m_nNumImages)
        return FALSE;

    rect->left = GetColumn(nIndex) * m_nBoxSize + m_nMargin;
    rect->top  = GetRow(nIndex) * m_nBoxSize + m_nMargin;

    rect->right = rect->left + m_nBoxSize;
    rect->bottom = rect->top + m_nBoxSize;
    return TRUE;
}
void CLImagePan::DrawTransInvertPic(HDC hDstDC, INT nXDest, INT nYDest, 
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

void CLImagePan::DrawTransPic(CDC* pDC, CBitmap* pBitmap, int X, int Y,BOOL bInvert)
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


LONG CLImagePan::GetImageID(int nIndex)
{
	ASSERT(m_pBorders!=NULL);
	return m_pBorders[nIndex].nImageID;
}
