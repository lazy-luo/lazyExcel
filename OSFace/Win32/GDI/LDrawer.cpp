//////////////////////////////////////////////////////////////////////
//@模块		 ：可跨平台绘图引擎实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LDrawer.h"
#include "../../../LComm/LGlobalParam.h"

static HBITMAP m_hbitmap=NULL;
//extern HINSTANCE g_hInstance;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLDrawer::CLDrawer()
{

}

CLDrawer::~CLDrawer()
{

}
LONG CLDrawer::GetTextWidth(HDC hDC,LPTSTR ptrTxt,SIZE& sizeRet)
{
	if(!ptrTxt || *ptrTxt=='\0') return 0;
	LONG nLen=strlen(ptrTxt);
	SIZE size;
	GetTextExtentPoint32(hDC,ptrTxt,nLen,&size);
	sizeRet=size;
	return size.cx;
}
LONG CLDrawer::GetTextWidth(LPTSTR ptrTxt)
{
	if(!ptrTxt || *ptrTxt=='\0') return 0;
	LONG nLen=strlen(ptrTxt);
	SIZE size;
	HDC hDC=GetDC(0);
	GetTextExtentPoint32(hDC,ptrTxt,nLen,&size);
	DeleteDC(hDC);
	return size.cx;
}

void CLDrawer::DeleteBitmap(HBITMAP hbmp)
{
	::DeleteObject(hbmp);
}
HBITMAP CLDrawer::GetBitmap(LPTSTR ptrName)
{
	HBITMAP hbitmap=(HBITMAP)LoadImage(g_hInstance,
		ptrName,IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
	
	return  hbitmap;//::LoadBitmap(g_hInstance,ptrName);
}
void CLDrawer::DrawArrButton(HDC hDC, LPRECT lpRct,COLORREF clrBar, 
							 LONG nArrDirection, BOOL bRaise,BOOL bStyle)
{
	RECT rctBt=*lpRct;
	if(bRaise && bStyle==STYLE_3D_LOOK){
		CLDrawer::DrawThickRect(hDC,&rctBt,clrBar);
		LONG nDef=1;
		if(nArrDirection!=ARROW_RIGHT){
			rctBt.left-=nDef;
			rctBt.right-=nDef;
		}
		if(nArrDirection!=ARROW_DOWN){
			rctBt.top-=nDef;
			rctBt.bottom-=nDef;
		}
	}else{
		CLDrawer::FillSolidRect(hDC,&rctBt,clrBar);
		
		RECT rct=rctBt;
		/*
		rct.left++;
		rct.top++;
		rct.right--;
		rct.bottom--;
		*/
		::FrameRect(hDC,&rct,GetSysColorBrush(COLOR_3DSHADOW));
		LONG nDef=(bStyle==STYLE_FLAT_LOOK?0:1);
		if(nArrDirection==ARROW_RIGHT){
			rctBt.left+=nDef;
			rctBt.right+=nDef;
		}
		if(nArrDirection==ARROW_DOWN){
			rctBt.top+=nDef;
			rctBt.bottom+=nDef;
		}
	}
	DrawArrow(hDC,rctBt,RGB(10,10,10),nArrDirection,FALSE,TRUE);
}
void CLDrawer::DrawerLine(HDC hDC,int xsrc,int ysrc,int xdst,int ydst,COLORREF clr)
{
	POINT pt;
	MoveToEx(hDC,xsrc,ysrc,&pt);
	HPEN hpen=CreatePen(PS_SOLID,1,clr);
	HPEN hold=SelectPen(hDC,hpen);
	LineTo(hDC,xdst,ydst);
	SelectPen(hDC,hold);
	DeletePen(hpen);
}
BOOL CLDrawer::LineTo(HDC hDC, int x, int y)
{
	return ::LineTo(hDC,x,y);
}	
BOOL CLDrawer::MoveToEx(HDC hDC, int x, int y, LPPOINT lppt)
{
	return ::MoveToEx(hDC,x,y,lppt);
}
BOOL CLDrawer::PtInRegion(HRGN hrgn, INT ptx, INT pty)
{
	return ::PtInRegion(hrgn,ptx,pty);
}
BOOL CLDrawer::PtInRect(const RECT* prct,POINT pt)
{
	return ::PtInRect(prct,pt);
}
INT CLDrawer::DrawText(HDC hDC,LPCTSTR lpString,INT nCount,LPRECT lpRect,UINT uFormat,BOOL bTrans)
{
	if(!bTrans){
		return ::DrawText(hDC,lpString,nCount,lpRect,uFormat);
	}else{
		LONG mod=::SetBkMode(hDC,TRANSPARENT);
		INT ret=::DrawText(hDC,lpString,nCount,lpRect,uFormat);
		::SetBkMode(hDC,mod);
		return ret;
	}
}
COLORREF CLDrawer::SetTextColor(HDC hDC,COLORREF clr)
{
	return ::SetTextColor(hDC,clr);
}
HFONT CLDrawer::SelectFont(HDC hDC,HFONT hFont)
{
	return (HFONT)::SelectObject(hDC,hFont);
}
void CLDrawer::DeleteBrush(HBRUSH hBrush)
{
	::DeleteObject(hBrush);
}
void CLDrawer::DeletePen(HPEN hPen)
{
	::DeleteObject(hPen);
}
HPEN CLDrawer::SelectPen(HDC hDC,HPEN hPen)
{
	return (HPEN)SelectObject(hDC,hPen);
}
HPEN CLDrawer::CreatePen(INT style,INT wid,COLORREF clr)
{
	return ::CreatePen(style,wid,clr);
}

void CLDrawer::FrameRect(HDC hDC,const RECT& rct,COLORREF clrFill,COLORREF clrBorder,BOOL bFill)
{
	RECT rect=rct;
	if(bFill){
		FillSolidRect(hDC,&rect,clrFill);
	}
	Draw3dRect(hDC,&rect,clrBorder,clrBorder);
}
void CLDrawer::InvertRect(HDC hDC,const RECT& rct,COLORREF clrM)
{
	::InvertRect(hDC,&rct);
}
INT CLDrawer::SetBkMode(HDC hDC,INT style)
{
	return ::SetBkMode(hDC,style);
}
BOOL CLDrawer::FrameRgn(HDC hDC,HRGN hrgn,HBRUSH hBrush,INT wid,INT hei)
{
	return ::FrameRgn(hDC,hrgn,hBrush,wid,hei);
}
BOOL CLDrawer::FillRgn(HDC hDC,HRGN hrgn,HBRUSH hBrush)
{
	return ::FillRgn(hDC,hrgn,hBrush);
}
HBRUSH CLDrawer::SelectBrush(HDC hDC,HBRUSH hBrush)
{
	return (HBRUSH)::SelectObject(hDC,hBrush);
}
HBRUSH CLDrawer::CreateSolidBrush(COLORREF clr)
{
	return ::CreateSolidBrush(clr);
}
void CLDrawer::DeleteRgn(HRGN hrgn)
{
	DeleteObject(hrgn);
}
INT	CLDrawer::CombineRgn(HRGN rgnDst,HRGN rgnS1,HRGN rgnS2,int style)
{
	return ::CombineRgn(rgnDst,rgnS1,rgnS2,style);
}
void CLDrawer::DeleteFont(HFONT hFont)
{
	DeleteObject(hFont);
}
HFONT CLDrawer::CreateFontIndirect(const LOGFONT* lgFont)
{
	return (HFONT)::CreateFontIndirect(lgFont);
}
HRGN CLDrawer::CreatePolygonRgn(const POINT* ptArr,INT nLen,INT nMode)
{
	return ::CreatePolygonRgn(ptArr,nLen,nMode);
}
void CLDrawer::FillSolidRect(HDC hDC,LPCRECT lpRect, COLORREF clr)
{
	SetBkColor(hDC, clr);
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}
void CLDrawer::SetClipBox(HDC hDC,const RECT& rctNew,RECT& rctOld)
{
	::GetClipBox(hDC,&rctOld);
	HRGN hRgn=CreateRectRgn(rctNew);
	if(ERROR==SelectClipRgn(hDC,hRgn))
		ASSERT(FALSE);
	DeleteObject(hRgn);
}

void CLDrawer::FillSolidRect(HDC hDC,int x, int y, int cx, int cy, COLORREF clr)
{
	SetBkColor(hDC, clr);
	RECT rect;
	rect.left=x;
	rect.top=y;
	rect.right=x+cx;
	rect.bottom=y+cy;
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
}
void CLDrawer::DrawMemoFlag(HDC hDC, LPRECT lpRct, COLORREF clr)
{
	int SPACE_SK=5;
	HBRUSH brush=CreateSolidBrush(clr);
	POINT pt[3];
	pt[0].x=lpRct->right-SPACE_SK;
	pt[0].y=lpRct->top+1;
	pt[1].x=lpRct->right;
	pt[1].y=lpRct->top;
	pt[2].x=lpRct->right;
	pt[2].y=lpRct->top+SPACE_SK+1;
	HRGN hrgn=CLDrawer::CreatePolygonRgn(pt,3,WINDING);
	if(hrgn){
		CLDrawer::FillRgn(hDC,hrgn,brush);
		CLDrawer::DeleteRgn(hrgn);
	}
	CLDrawer::DeleteBrush(brush);
}
void CLDrawer::DrawTrack(HDC hDC,int nWid, LPPOINT lpTL, LPPOINT lpRB, 
						 BOOL bVert)
{
	RECT rect;
	rect.left=lpTL->x;
	rect.right=lpRB->x+(bVert?nWid:0);
	rect.top=lpTL->y;
	rect.bottom=lpRB->y+(bVert?0:nWid);
	DrawFocusRect(hDC,&rect);
}
void CLDrawer::Draw3dRect(HDC hDC,LPCRECT lpRect,
	COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	Draw3dRect(hDC,lpRect->left, lpRect->top, lpRect->right - lpRect->left,
		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
}

void CLDrawer::Draw3dRect(HDC hDC,int x, int y, int cx, int cy,
	COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	FillSolidRect(hDC,x, y, cx - 1, 1, clrTopLeft);
	FillSolidRect(hDC,x, y, 1, cy - 1, clrTopLeft);
	FillSolidRect(hDC,x + cx, y, -1, cy, clrBottomRight);
	FillSolidRect(hDC,x, y + cy, cx, -1, clrBottomRight);
}
void CLDrawer::FillARect(HDC hDC, LPRECT lpRct, HBRUSH hBrush)
{
	lpRct->right+=1;
	lpRct->bottom+=1;
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	PatBlt(hDC,lpRct->left, lpRct->top, lpRct->right-lpRct->left, 
		lpRct->bottom-lpRct->top, PATCOPY);
	if (hOldBrush != NULL)
		SelectObject(hDC, hOldBrush);
	lpRct->right-=1;
	lpRct->bottom-=1;
}
void CLDrawer::DrawerALine(HDC hDC,int xsrc,int ysrc,int xdst,int ydst,COLORREF clr
						   ,BOOL bHorz,int wid,BOOL bDot)
{
	if(bDot){
		RECT rct;
		rct.left=xsrc;
		rct.top=ysrc;
		rct.right=(bHorz?xdst+1:xsrc+wid-1);
		rct.bottom=(bHorz?ysrc+wid-1:ydst+1);
		HBRUSH hbrush=HBrushDitherCreate(clr,RGB(255,255,255));
		FillARect(hDC,&rct,hbrush);
		DeleteObject(hbrush);
	}else{
		FillSolidRect(hDC,xsrc, ysrc, bHorz?xdst-xsrc+1:wid, bHorz?wid:ydst-ysrc+1, clr);
	}
}

void CLDrawer::DrawThickRect(HDC hDC, LPRECT lpRct, COLORREF clr, BOOL bRaise,BOOL bFill,BOOL b3DFlat)
{
	RECT rct=*lpRct;
	if(bFill)
		CLDrawer::FillSolidRect(hDC,lpRct,clr);
	COLORREF clrShadow=GetSysColor(bRaise?RGB(10,10,10):COLOR_BTNFACE);
	COLORREF clrHilight=GetSysColor(bRaise?COLOR_BTNFACE:RGB(10,10,10));
	COLORREF clrShadowIn=GetSysColor(bRaise?COLOR_3DSHADOW:COLOR_3DHIGHLIGHT);
	COLORREF clrHilightIn=GetSysColor(bRaise?COLOR_3DHIGHLIGHT:COLOR_3DSHADOW);
	if(!b3DFlat){
		CLDrawer::Draw3dRect(hDC,&rct,(bRaise?clrHilight:clrHilightIn)
			,(bRaise?clrShadow:clrShadowIn));
		
		rct.top+=1;
		rct.left+=1;
		rct.bottom-=1;
		rct.right-=1;
	}
	CLDrawer::Draw3dRect(hDC,&rct,b3DFlat?clrHilightIn:(bRaise?clrHilightIn:clrHilight)
		,b3DFlat?clrShadowIn:(bRaise?clrShadowIn:clrShadow));
	
}
HRGN CLDrawer::CreateRectRgn(const RECT& rct)
{
	return ::CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
}
void CLDrawer::SetFocus(HDC hDC,HRGN hrgn,BOOL bFillArea
						,COLORREF clrFocus,BOOL bAddFocusRect,BOOL bSelectMode)
{
	if(hrgn==NULL)return;
	int OldMode;
	if(hrgn){
		HBRUSH  Brush;
		OldMode=SetROP2(hDC,R2_XORPEN);
		COLORREF clr=(clrFocus^RGB(255,255,255));
		Brush=CreateSolidBrush(clr);
		if(!bFillArea){
			if(bSelectMode){
				DrawRangeBorder(hDC,hrgn,clrFocus);
			}else
				FrameRgn(hDC,hrgn,Brush,1,1);
		}else{
			FillRgn(hDC,hrgn,Brush);
			
			if(bAddFocusRect){
				HBRUSH hBrush=HBrushDitherCreate(RGB(0,0,0),RGB(255,255,255));
				FrameRgn(hDC,hrgn,hBrush,1,1);
				DeleteObject(hBrush);
			}
			
		}
		SetROP2(hDC,OldMode);
		DeleteObject(Brush);
	}
}
HBITMAP CLDrawer::LoadBitmap(LONG resid)
{
	if(g_hInstance){
		return ::LoadBitmap(g_hInstance,MAKEINTRESOURCE(resid));
	}
	return NULL;
}
HBRUSH CLDrawer::HBrushDitherCreate(COLORREF rgbFace, COLORREF rgbHilight)
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
	hDC=GetDC(NULL); 
	hBmp=CreateDIBitmap(hDC, &bmi.bmiHeader, CBM_INIT, patGray
		,(LPBITMAPINFO)&bmi, DIB_RGB_COLORS);     
	ReleaseDC(NULL, hDC);  
	
	if (NULL!=hBmp){         
 		hBrush=CreatePatternBrush(hBmp);         
 		DeleteObject(hBmp);         
	}      
	return hBrush;
	/*
	HBRUSH          hBrush=NULL;
	if(!m_hbitmap)
		m_hbitmap=LoadBitmap(IDB_DISH_BRUSH);
	if (NULL!=m_hbitmap){ 
		hBrush=CreatePatternBrush(m_hbitmap);         
 		//DeleteObject(hBmp);         
	}      
	return hBrush;
	*/
}

void CLDrawer::DrawBorder(HDC hDC, LPRECT lpRct, COLORREF clrFocus)
{
	HBRUSH  Brush,hOld;
	int OldMode=SetROP2(hDC,R2_XORPEN);
	COLORREF clr=(clrFocus^RGB(255,255,255));
	Brush=CreateSolidBrush(clr);
	hOld=(HBRUSH)SelectObject(hDC,Brush);
	RECT rct=*lpRct;
	HRGN hrgnAll=NULL,hrgnClip=NULL;
	rct.left-=1;
	rct.top-=1;
	rct.right+=2;
	rct.bottom+=2;
	hrgnAll=CreateRectRgn(rct);
	
	rct.left+=3;
	rct.top+=3;
	rct.right-=3;
	rct.bottom-=3;
	hrgnClip=CreateRectRgn(rct);
	CombineRgn(hrgnClip,hrgnAll,hrgnClip,RGN_XOR);
	FillRgn(hDC,hrgnClip,Brush);

	DeleteObject(hrgnAll);
	DeleteObject(hrgnClip);
	SetROP2(hDC,OldMode);
	SelectObject(hDC,hOld);
	DeleteObject(Brush);
}
void CLDrawer::DrawRangeBorder(HDC hDC, HRGN hrgn, COLORREF clrFocus)
{
	if(NULL==hrgn)return;
	RECT rct;
	GetRgnBox(hrgn,&rct);
	rct.left--;
	rct.top--;
	DrawRangeBorder(hDC,&rct,clrFocus);
}
//画Excel区域边框
void CLDrawer::DrawRangeBorder(HDC hDC, LPRECT lpRct, COLORREF clrFocus)
{
	DrawBorder(hDC,lpRct,clrFocus);
	//画右下角可拖动区域
	
	RECT rct=*lpRct;
	/*
	rct.left=rct.right-1;
	rct.top=rct.bottom-1;
	DrawBorder(hDC,&rct,clrFocus);
	rct.left--;
	rct.top--;
	*/
	int OldMode=SetROP2(hDC,R2_XORPEN);
	//HRGN hrgnT;
	COLORREF clr=(clrFocus^RGB(255,255,255));
	HBRUSH Brush=CreateSolidBrush(clr),hOld;
	hOld=(HBRUSH)SelectObject(hDC,Brush);
	rct.left=rct.right-3;
	rct.top=rct.bottom-1;
	rct.bottom+=2;
	rct.right+=2;
	PatBlt(hDC,rct.left, rct.top, rct.right-rct.left, rct.bottom-rct.top, PATINVERT);
	/*
	hrgnT=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
	FillRgn(hDC,hrgnT,Brush);
	DeleteObject(hrgnT);
	*/
	rct.left=lpRct->right-1;
	rct.top=lpRct->bottom-3;
	rct.bottom=lpRct->bottom-1;
	rct.right=lpRct->right+2;
	PatBlt(hDC,rct.left, rct.top, rct.right-rct.left, rct.bottom-rct.top, PATINVERT);
	/*
	hrgnT=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
	FillRgn(hDC,hrgnT,Brush);
	DeleteObject(hrgnT);
	*/
	rct.left=lpRct->right-2;
	rct.top=lpRct->bottom-2;
	rct.bottom=lpRct->bottom+3;
	rct.right=lpRct->right+3;
	PatBlt(hDC,rct.left, rct.top, rct.right-rct.left, rct.bottom-rct.top, PATINVERT);
	/*
	hrgnT=CreateRectRgn(rct.left,rct.top,rct.right,rct.bottom);
	FillRgn(hDC,hrgnT,Brush);
	DeleteObject(hrgnT);
	*/
	/*
	hrgnT=CreateRectRgn(rct.left,rct.top,rct.right+3,rct.bottom+3);
	FillRgn(hDC,hrgnT,Brush);
	DeleteObject(hrgnT);
	DeleteObject(Brush);
	rct.left++;
	rct.top++;
	DrawBorder(hDC,&rct,clrFocus);
	
	rct.left-=1;
	rct.top-=1;
	DrawBorder(hDC,&rct,clrFocus);
	*/
	SelectObject(hDC,hOld);
	DeleteObject(Brush);
	SetROP2(hDC,OldMode);
	
}

void CLDrawer::DrawDitherBorder(HDC hDC, LPRECT lpRct, LONG nWidth, LONG nHeight)
{
	int OldMode=SetROP2(hDC,R2_XORPEN);
	HBRUSH Brush=HBrushDitherCreate(RGB(0,0,0),RGB(255,255,255));
	HRGN hRang=::CreateRectRgn(lpRct->left,lpRct->top,lpRct->right,lpRct->bottom);
	FrameRgn(hDC,hRang,Brush,nWidth,nHeight);
	DeleteObject(hRang);
	SetROP2(hDC,OldMode);
}

void CLDrawer::DrawArrow(HDC hDC, const RECT &rct, COLORREF clr, 
						 LONG bDirect,BOOL bHasEndLine,BOOL bEnable)
{
	POINT pt;
	RECT rctClip=rct;

	LONG nWidEndL=1,nSP=1;

	pt.x=rctClip.left+(rctClip.right-rctClip.left)/2;
	pt.y=rctClip.top+(rctClip.bottom-rctClip.top)/2;
	POINT ptPos[3];
	LONG offBig,offSmall;
	LONG val=(rctClip.right-rctClip.left)/4;
	LONG nyDef,nxDef;
	if(ARROW_LEFT==bDirect || ARROW_RIGHT==bDirect){
		nyDef=val;
		nxDef=val;
	}else{
		nxDef=val;
		nyDef=val;
	}
	//得到垂直方向高度
	if((val+1)%2){
		//奇数
		offSmall=(val+1)/2;
		offBig=offSmall;
	}else{
		offSmall=val/2;
		offBig=offSmall+1;
	}
	
	if(nyDef<=0)nyDef=1;
	if(nxDef<=0)nxDef=1;
	HRGN hrgn=NULL;
	HBRUSH hBrush=NULL;
	RECT rctEndL;
	switch(bDirect){
	case ARROW_LEFT:
		ptPos[0].x=pt.x-offBig;
		ptPos[0].y=pt.y;

		ptPos[1].x=pt.x+offSmall;
		ptPos[1].y=pt.y+nyDef;

		ptPos[2].x=pt.x+offSmall;
		ptPos[2].y=pt.y-nyDef;
		if(bHasEndLine){
			rctEndL.left=ptPos[0].x-(nWidEndL+nSP);
			rctEndL.right=rctEndL.left+nWidEndL;
			rctEndL.top=ptPos[2].y;
			rctEndL.bottom=ptPos[1].y;
		}
		break;
	case ARROW_RIGHT:
		ptPos[0].x=pt.x+offBig;
		ptPos[0].y=pt.y;

		ptPos[1].x=pt.x-offSmall;
		ptPos[1].y=pt.y-nyDef;

		ptPos[2].x=pt.x-offSmall;
		ptPos[2].y=pt.y+nyDef;
		if(bHasEndLine){
			rctEndL.left=ptPos[0].x+nSP;
			rctEndL.right=rctEndL.left+nWidEndL;
			rctEndL.top=ptPos[1].y;
			rctEndL.bottom=ptPos[2].y;
		}
		break;
	case ARROW_UP:
		ptPos[0].x=pt.x;
		ptPos[0].y=pt.y-offBig-1;

		ptPos[1].x=pt.x-nxDef;
		ptPos[1].y=pt.y+offSmall;

		ptPos[2].x=pt.x+nxDef;
		ptPos[2].y=pt.y+offSmall;
		if(bHasEndLine){
			rctEndL.left=ptPos[1].x;
			rctEndL.right=ptPos[2].x;
			rctEndL.top=ptPos[0].y-(nWidEndL+nSP);
			rctEndL.bottom=rctEndL.top+nWidEndL;
		}
		break;
	case ARROW_DOWN:
		ptPos[0].x=pt.x;
		ptPos[0].y=pt.y+offBig;

		ptPos[1].x=pt.x+nxDef;
		ptPos[1].y=pt.y-offSmall;

		ptPos[2].x=pt.x-nxDef+1;
		ptPos[2].y=pt.y-offSmall;
		if(bHasEndLine){
			rctEndL.left=ptPos[2].x;
			rctEndL.right=ptPos[1].x;
			rctEndL.top=ptPos[0].y+nSP;
			rctEndL.bottom=rctEndL.top+nWidEndL;
		}
		break;
	}
	if(bHasEndLine){
		if(ARROW_LEFT==bDirect || ARROW_RIGHT==bDirect)
			rctEndL.top++;
		else
			rctEndL.left++;
	}
	if(!bEnable){
		POINT ptBig[3];
		
		for(int i=0;i<3;i++){
			ptBig[i].x=ptPos[i].x+1;
			ptBig[i].y=ptPos[i].y+1;
		}
		hrgn=CreatePolygonRgn(ptBig,3,WINDING);
		hBrush=CreateSolidBrush(GetSysColor(COLOR_3DHIGHLIGHT));
		FillRgn(hDC,hrgn,hBrush);
		DeleteObject(hrgn);
		if(bHasEndLine){
			RECT rctBig=rctEndL;
			rctBig.left++;
			rctBig.right++;
			rctBig.top++;
			rctBig.bottom++;
			FillRect(hDC,&rctBig,hBrush);
		}
		DeleteObject(hBrush);
	}
	hrgn=CreatePolygonRgn(ptPos,3,WINDING);
	hBrush=CreateSolidBrush(bEnable?clr:GetSysColor(COLOR_3DSHADOW));
	FillRgn(hDC,hrgn,hBrush);
	DeleteObject(hrgn);
	if(bHasEndLine){
		FillRect(hDC,&rctEndL,hBrush);
	}
	DeleteObject(hBrush);
}

void CLDrawer::DrawBitmap(HDC hDC,POINT& ptStart,HBITMAP hbmp,SIZE& size)
{
	DrawBitmap(hDC,ptStart.x,ptStart.y,hbmp,size.cx,size.cy);
}
void CLDrawer::DrawBitmap(HDC hDC,LONG x,LONG y,HBITMAP hbmp,LONG cx,LONG cy)
{
	HDC hSDC=GetDC(NULL);
	HDC hDCT=CreateCompatibleDC(hSDC);
	ASSERT(hDCT!=NULL);
	HBITMAP hOldBmp=(HBITMAP)SelectObject(hDCT,hbmp);
	BitBlt(hDC,x,y,cx,cy,hDCT,0,0,SRCCOPY);
	SelectObject(hDCT,hOldBmp);
	DeleteObject(hDCT);
	DeleteObject(hSDC);
}
void CLDrawer::Draw3DText(HDC hDC,HFONT hFont,const LPTSTR ptrTxt
		,const RECT& rct,COLORREF clrFill,BOOL bRaise,
		BOOL bFill,COLORREF clrFace,COLORREF clrShadow)
{
	if(bFill){
		FillSolidRect(hDC,&rct,clrFill);
	}
	if(ptrTxt && ptrTxt[0]!='\0'){
		HFONT oldFont=(HFONT)SelectObject(hDC,hFont);
		SIZE size;
		LONG nLen=GetTextWidth(hDC,ptrTxt,size);
		POINT ptDraw;
		ptDraw.x=rct.left+(rct.right-rct.left-size.cx)/2;
		ptDraw.y=rct.top+(rct.bottom-rct.top-size.cy)/2;
		int mod=SetBkMode(hDC,TRANSPARENT);
		COLORREF oldClr;
		if(bRaise){
			oldClr=clrFace;
			clrFace=clrShadow;
			clrShadow=oldClr;
		}
		oldClr=SetTextColor(hDC,clrFace);
		TextOut(hDC,ptDraw.x,ptDraw.y,ptrTxt,strlen(ptrTxt));
		ptDraw.x-=1;
		ptDraw.y-=1;
		SetTextColor(hDC,clrShadow);
		TextOut(hDC,ptDraw.x,ptDraw.y,ptrTxt,strlen(ptrTxt));

		SetTextColor(hDC,oldClr);
		SetBkMode(hDC,mod);
		SelectObject(hDC,oldFont);
	}
}