// LImagePicker.cpp: implementation of the CLImagePicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LImagePicker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLImagePicker::CLImagePicker(LONG nDefaultLine):CLPickerBtn(nDefaultLine),
	m_nRows(0),m_nCols(0)
{
	
}

CLImagePicker::~CLImagePicker()
{

}
LONG CLImagePicker::GetCurrentValue()
{
	return GetValue();
}
void CLImagePicker::SetCurrentValue(LONG nStyle)
{
	SetValue(nStyle);
}
void CLImagePicker::OnPopup()
{
	CRect rect;
    GetWindowRect(rect);
    new CLImagePan(CPoint(rect.left, rect.bottom),
                     GetCurrentValue(),
                     this,m_nRows,m_nCols,m_nBorders);

    CWnd *pParent = GetParent();
    if (pParent)
        pParent->SendMessage(LPN_DROPDOWN, (LPARAM)GetCurrentValue(), (WPARAM) GetDlgCtrlID());

}
void CLImagePicker::OnDrawButton(CDC * pDC, CRect& rect)
{
	//CRect rc = rect;
	//rc.DeflateRect(2, 2);
	SetBitmapRes(GetCurrentImageID());
	if(m_hBitmapID>0){
		CBitmap bmp;
		
		HBITMAP hBitmap=LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(m_hBitmapID));
		bmp.Attach(hBitmap);
		if(IsWindowEnabled())
			DrawTransPic(pDC,&bmp,rect.left,rect.top,FALSE);
		else
			DrawTransInvertPic(pDC->GetSafeHdc(),rect.left,rect.top,rect.right-rect.left-2,
				rect.bottom-rect.top-3,hBitmap);
	}
}

BOOL CLImagePicker::Create(CRect rect, CWnd * pParentWnd, UINT nID,LONG nRow,
		LONG nCol,ImageTableEntry*	pBorders,LONG nBmpID)
{
	
	m_nBorders=pBorders;
	m_nRows=nRow;
	m_nCols=nCol;
	SetCurrentValue(GetIndex(nBmpID));
	return CLPickerBtn::Create(rect,pParentWnd,nID,nBmpID);
}

LONG CLImagePicker::GetIndex(LONG nImagID)
{
	for(int i=0;i<m_nRows*m_nCols;i++){
		if(m_nBorders[i].nImageID==nImagID)
			return m_nBorders[i].nIndex;
	}
	return -1;
}

LONG CLImagePicker::GetCurrentImageID()
{
	LONG nIndex=GetCurrentValue();
	if(nIndex>=0){
		return m_nBorders[GetArrIndexByValue(nIndex)].nImageID;
	}else
		return 0;
}

LONG CLImagePicker::GetArrIndexByValue(LONG nVal)
{
	for(int i=0;i<m_nRows*m_nCols;i++){
		if(m_nBorders[i].nIndex==nVal)
			return i;
	}
	ASSERT(FALSE);
	return 0;
}
