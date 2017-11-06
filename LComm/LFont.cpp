//////////////////////////////////////////////////////////////////////
//@模块		 ：艺术字对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#include "LFont.h"
#include <tchar.h>
#include "LGlobalParam.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLFont::CLFont(): m_clr(0x00000000), m_bytArtStyle(ARTSHAPE_NOART), m_clrLine(0x00000000),
		m_bytArtParam1(20), m_bytArtParam2(20), m_bytShadow(0)
{
	const LOGFONT lfDefault = {-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, "宋体 (CHINESE_GB2312)"};
	m_lf = lfDefault;
}

void CLFont::ClearToDefault()
{
	m_clr=0x00000000;
	m_bytArtStyle=ARTSHAPE_NOART;
	m_clrLine=0x00000000;
	m_bytArtParam1=20;
	m_bytArtParam2=20;
	m_bytShadow=0;
	const LOGFONT lfDefault = {-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, "宋体 (CHINESE_GB2312)"};
	m_lf = lfDefault;
}
CLFont::~CLFont()
{
	
}

BOOL CLFont::isMuiltLine(LPTSTR strSrc,LONG charWid,LONG charHei,RECT& rct,LONG& totHei) const
{
	BOOL bret=FALSE;
	LONG charSP=2;
	if(strSrc && strSrc[0]!='\0'){
		int nMaxLineChar = abs(rct.right - rct.left) / charWid ;
		int nCtChar=strlen(strSrc);
		int nRows=nCtChar%nMaxLineChar?nCtChar/nMaxLineChar+1:nCtChar/nMaxLineChar;
		if(nRows>1){
			totHei=nRows*charHei;
			bret=TRUE;
			rct.left+=charSP;
			rct.top+=charSP;
			rct.right-=charSP;
			rct.bottom-=charSP;
		}
	}
	return bret;
	
}
void CLFont::DrawText(HDC hDC, RECT rect, LPTSTR pStr,
		UINT nFormat /*= DT_NOCLIP | DT_NOPREFIX*/) const
{
	if (m_bytArtStyle == ARTSHAPE_NOART)
	{
		DrawTextNomal(hDC, rect, pStr, nFormat);
		return;
	}
	
	LPPOINT lpPoints;		  // Path data points
	LPBYTE lpTypes;			  // Path data types
	int iNumPts;
	int nBkMode = SetBkMode(hDC,TRANSPARENT);
    
	BeginPath(hDC);
	DrawTextNomal(hDC, rect, pStr, nFormat);
	EndPath(hDC);    
    
	// How many points are in the path
	iNumPts = GetPath(hDC,NULL, NULL, 0);
	if (iNumPts == -1){
		return;
	}
	// Allocate room for the points
	lpPoints = (LPPOINT)GlobalAlloc(GPTR, sizeof(POINT) * iNumPts);
	if (!lpPoints){
		return;
	}
	// Allocate room for the point types
	lpTypes = (LPBYTE)GlobalAlloc(GPTR, iNumPts);
	if (!lpTypes)
	{
		GlobalFree(lpPoints);
  		return;
	}
   
	// Get the points and types from the current path
	iNumPts = GetPath(hDC,lpPoints, lpTypes, iNumPts);

	// Even more error checking
	if (iNumPts == -1)
	{
		GlobalFree(lpTypes);
		GlobalFree(lpPoints);
		
		return;
	}
   
	// Draw the new path 
	RenderText(hDC, lpPoints, lpTypes, iNumPts);
   
	GlobalFree(lpPoints);
	GlobalFree(lpTypes);

	SetBkMode(hDC,nBkMode);
	
}

const CLFont& CLFont::operator=(const CLFont& rArtFont)
{
	m_lf = rArtFont.m_lf;
	m_clr = rArtFont.m_clr;
	m_bytArtStyle = rArtFont.m_bytArtStyle;
	m_clrFill = rArtFont.m_clrFill;
	m_clrLine = rArtFont.m_clrLine;
	m_bytArtParam1 = rArtFont.m_bytArtParam1;
	m_bytArtParam2 = rArtFont.m_bytArtParam2;
	m_bytShadow = rArtFont.m_bytShadow;

	return *this;
}

BOOL CLFont::operator==(const CLFont& rArtFont) const
{
	if (memcmp(&m_lf, &rArtFont.m_lf, sizeof(LOGFONT)) != 0)
		return FALSE;
	if (memcmp(&m_clrFill, &rArtFont.m_clrFill, sizeof(FILLCOLOR)) != 0)
		return FALSE;
	return m_clr == rArtFont.m_clr && m_bytArtStyle == rArtFont.m_bytArtStyle &&
		m_clrLine == rArtFont.m_clrLine && m_bytArtParam1 == rArtFont.m_bytArtParam1 &&
		m_bytArtParam2 == rArtFont.m_bytArtParam2 && m_bytShadow == rArtFont.m_bytShadow;
}

// Implementation

void CLFont::DrawTextNomal(HDC hDC, RECT rect, LPTSTR pStr,
		UINT nFormat /*= DT_NOCLIP | DT_NOPREFIX*/) const
{
//	DrawTextInRect(hDC,pStr,&rect,0,m_Alignment.bAlignHorz,m_Alignment.bAlignVert);
//	return;
	int SP=1;
	rect.left+=SP;
	rect.right-=(SP+1);
	rect.top+=SP;
	rect.bottom-=(SP+1);
	BOOL bMultiLine = FALSE;
	
	LOGFONT lf = this->m_lf;
	
	if (pStr==NULL) return;
	
	if (strstr(pStr,"\x0d\x0a") != NULL)
		bMultiLine = TRUE;

	switch(m_Alignment.bDirection)
	{
	case adHORIZONTAL:
	case adVERTICAL:
		lf.lfEscapement = 0;
		break;
	case adLEFT:
		lf.lfEscapement = 900;
		break;
	case adRIGHT:
		lf.lfEscapement = 2700;
	}

	HFONT font, hOldFont;
	font=CreateFontIndirect(&lf);
	hOldFont = (HFONT)SelectObject(hDC,font);
	COLORREF crOldText = SetTextColor(hDC,m_clr);
    int oldmod=SetBkMode(hDC,TRANSPARENT);
	
//	UINT uTextFormat = DT_NOCLIP | DT_NOPREFIX;
	UINT uTextFormat = nFormat;

	switch(m_Alignment.bAlignHorz)
	{
	case ahLEFT:
		uTextFormat |= DT_LEFT;
		break;
	case ahRIGHT:
		uTextFormat |= DT_RIGHT;
		break;
	case ahCENTER:
		uTextFormat |= DT_CENTER;
		break;
	case ahFILL:
		uTextFormat |= DT_CENTER;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	switch(m_Alignment.bAlignVert)
	{
	case avTOP:
		uTextFormat |= DT_TOP | DT_SINGLELINE;
		break;
	case avBOTTOM:
		uTextFormat |= DT_BOTTOM | DT_SINGLELINE;
		break;
	case avCENTER:
		uTextFormat |= DT_VCENTER | DT_SINGLELINE;
		break;
	case avFILL:
		uTextFormat |= DT_VCENTER | DT_SINGLELINE;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	LONG hei;
	TEXTMETRIC tm;
	GetTextMetrics(hDC,&tm);
	if(rect.right-rect.left<tm.tmAveCharWidth || rect.bottom-rect.top<tm.tmHeight)goto to_exit;
	bMultiLine=isMuiltLine(pStr,tm.tmAveCharWidth,tm.tmHeight,rect,hei);
	if(bMultiLine){
		uTextFormat &= ~DT_SINGLELINE;
		uTextFormat|=DT_WORDBREAK;
		if(m_Alignment.bAlignVert==avCENTER && hei>0){
			LONG val=(rect.bottom-rect.top-hei)/2;
			rect.top+=(val>0?val:0);
		}
	}
	switch(m_Alignment.bDirection)
	{
	case adHORIZONTAL:
		if((uTextFormat & DT_RIGHT)&&(uTextFormat & DT_NOCLIP))
		{
			int x,y;
			int align = TA_RIGHT;
			if((uTextFormat & DT_TOP) ||(uTextFormat & DT_VCENTER))
				align = align|TA_TOP;
			else
				align = align|TA_BOTTOM;
			x = rect.right;
			if(uTextFormat & DT_VCENTER)
			{
				LONG nLen=strlen(pStr);
				SIZE size;
				GetTextExtentPoint32(hDC,pStr,nLen,&size);
				y = (rect.top+rect.bottom-size.cy)/2;
			}
			else if(uTextFormat & DT_BOTTOM)
				y = rect.bottom;
			else
			{
				LONG nLen=strlen(pStr);
				SIZE size;
				GetTextExtentPoint32(hDC,pStr,nLen,&size);
				y = rect.top + size.cy;
			}
			int oldAlign = SetTextAlign(hDC,align);
			TextOut(hDC,x,y,pStr,strlen(pStr));
			SetTextAlign(hDC,oldAlign);
		}
		else
			::DrawText(hDC,pStr,-1, &rect, uTextFormat);
		break;
	case adVERTICAL:
		{
			int nIndex, nLength, nMBLength;
			nLength = strlen(pStr);
			//setlocale(LC_ALL, "chs");
			nMBLength = strlen(pStr);

			nIndex = 0;
			LPCTSTR lpszStart = pStr;

			TEXTMETRIC tm;
			GetTextMetrics(hDC,&tm);
			int nHeight = tm.tmHeight;

			RECT rectDraw = rect;
			switch(m_Alignment.bAlignVert)
			{
			case avTOP:
				break;
			case avCENTER:
				rectDraw.top = rectDraw.top + (rectDraw.bottom-rectDraw.top - nHeight*nMBLength) / 2;
				if (rect.top > rectDraw.top)
				{
					nIndex = int((rect.top - rectDraw.top + 0.5) / nHeight);
					rectDraw.top = rect.top;
				}
				break;
			case avBOTTOM:
				rectDraw.top = rect.bottom - nHeight*nMBLength;
				if (rect.top > rectDraw.top)
				{
					nIndex = int((rect.top - rectDraw.top + 0.5) / nHeight);
					rectDraw.top = rect.top;
				}
				break;
			case avFILL:
				nHeight = (rectDraw.bottom-rectDraw.top) / nMBLength;
			}
			lpszStart += nIndex;
			rectDraw.bottom = rectDraw.top + nHeight;
			if (rectDraw.bottom > rect.bottom)
				rectDraw.bottom = rect.bottom;
			while (rectDraw.bottom > rectDraw.top && nIndex < nLength)
			{
				if (_istlead(*lpszStart))
				{
					::DrawText(hDC,lpszStart, 2, &rectDraw, uTextFormat);
					nIndex += 2;
					lpszStart += 2;
				}
				else
				{
					::DrawText(hDC,lpszStart, 1, &rectDraw, uTextFormat);
					nIndex ++;
					lpszStart ++;
				}
				rectDraw.top = rectDraw.bottom;
				rectDraw.bottom = rectDraw.top + nHeight;
				if (rectDraw.bottom > rect.bottom)
					rectDraw.bottom = rect.bottom;
			}
		}
		break;
	case adLEFT:
		{
			POINT pt;
			UINT nFlags = 0;
			switch(m_Alignment.bAlignVert)
			{
				case avTOP:
					pt.y = rect.top;
					nFlags = SetTextAlign(hDC,TA_RIGHT);
					break;
				case avCENTER:
				case avFILL:
					pt.y = rect.top + (rect.bottom-rect.top)/2;
					nFlags = SetTextAlign(hDC,TA_CENTER);
					break;
				case avBOTTOM:
					pt.y = rect.bottom;
					nFlags = SetTextAlign(hDC,TA_LEFT);
					break;
			}
			//pt.x = rect.left;
			TEXTMETRIC tm;
			GetTextMetrics(hDC,&tm);
			int nHeight = tm.tmHeight;
			switch(m_Alignment.bAlignHorz)
			{
			case ahLEFT:
				pt.x = rect.left;
				break;
			case ahRIGHT:
				pt.x = rect.right - nHeight;
				break;
			case ahCENTER:
			case ahFILL:
				pt.x = rect.left +(rect.right-rect.left)/2 - nHeight/2;
				break;
			}
			ExtTextOut(hDC,pt.x, pt.y, 0, &rect, pStr,strlen(pStr), NULL);
			SetTextAlign(hDC,nFlags);
		}
		break;
	case adRIGHT:
		{
			POINT pt;
			UINT nFlags = 0;
			switch(m_Alignment.bAlignVert)
			{
				case avTOP:
					pt.y = rect.top;
					nFlags = SetTextAlign(hDC,TA_LEFT);
					break;
				case avCENTER:
				case avFILL:
					pt.y = rect.top + (rect.bottom-rect.top)/2;
					nFlags = SetTextAlign(hDC,TA_CENTER);
					break;
				case avBOTTOM:
					pt.y = rect.bottom;
					nFlags = SetTextAlign(hDC,TA_RIGHT);
					break;
			}
			//pt.x = rect.right;
			TEXTMETRIC tm;
			GetTextMetrics(hDC,&tm);
			int nHeight = tm.tmHeight;
			switch(m_Alignment.bAlignHorz)
			{
			case ahLEFT:
				pt.x = rect.left + nHeight;
				break;
			case ahRIGHT:
				pt.x = rect.right;
				break;
			case ahCENTER:
			case ahFILL:
				pt.x = rect.right - (rect.right-rect.left)/2 + nHeight/2;
				break;
			default:
				pt.x = rect.left + nHeight;
				break;
			}
			ExtTextOut(hDC,pt.x, pt.y, 0, &rect, pStr,strlen(pStr), NULL);
			SetTextAlign(hDC,nFlags);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
to_exit:
	SetBkMode(hDC,oldmod);
	SetTextColor(hDC,crOldText);
	SelectObject(hDC,hOldFont);
	DeleteObject(font);
}

BOOL CLFont::RenderText(HDC hDC, LPPOINT lpPoints, LPBYTE lpTypes, int iNumPts) const
{
	PointsArt(lpPoints, iNumPts);

	if (m_bytShadow != 0)
	{
		LPPOINT lppShadow;
		lppShadow = (LPPOINT)GlobalAlloc(GPTR, sizeof(POINT) * iNumPts);
		if (!lppShadow) return FALSE;
		memcpy(lppShadow, lpPoints, sizeof(POINT) * iNumPts);
		PointsShadow(lppShadow, iNumPts);

		BeginPath(hDC);
		PolyDraw95(hDC, lppShadow, lpTypes, iNumPts);
		CloseFigure(hDC);
		EndPath(hDC);

		HBRUSH brush=CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH hOldBrush =(HBRUSH)SelectObject(hDC,brush);
		FillPath(hDC);
		SelectObject(hDC,hOldBrush);
		DeleteObject(brush);
		GlobalFree(lppShadow);
	}

	BeginPath(hDC); // Draw into a path so that we can use FillPath()
	PolyDraw95(hDC, lpPoints, lpTypes, iNumPts);
	CloseFigure(hDC);
	EndPath(hDC);   
	
	HPEN p=CreatePen(PS_SOLID, 1, m_clrLine);
	HPEN hPen = (HPEN)SelectObject(hDC,p); // Just say "no" to outlines
	HBRUSH b=CreateSolidBrush(m_clr);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC,b); // Paint It Black
	
	StrokeAndFillPath(hDC);  

	SelectObject(hDC,hPen);
	SelectObject(hDC,hBrush);
	DeleteObject(p);
	DeleteObject(b);
	return TRUE;
}

BOOL CLFont::PolyDraw95(HDC  hDC,              // handle of a device context 
                CONST LPPOINT lppt,	   // address of array of points 
                CONST LPBYTE lpbTypes, // address of line and curve identifiers  
                int  cCount) const 	       // count of points 
{
	int i;
  
	for (i=0; i<cCount; i++) 
    switch (lpbTypes[i])
	{
	case PT_MOVETO : 
		MoveToEx(hDC, lppt[i].x, lppt[i].y, NULL); 
		break;
      
	case PT_LINETO | PT_CLOSEFIGURE:
    case PT_LINETO : 
        LineTo(hDC,lppt[i].x, lppt[i].y); 
        break;
      
    case PT_BEZIERTO | PT_CLOSEFIGURE:
    case PT_BEZIERTO :
	    PolyBezierTo (hDC,&lppt[i], 3);
		i+=2;
        break;
	}

	return TRUE;
}  

void CLFont::PointsArt(LPPOINT lppt, int nCount) const
{
	RECT rect = GetPointsRect(lppt, nCount);
	
	switch(m_bytArtStyle)
	{
	case 0:
		ASSERT(FALSE);
		break;
	case 1:
		RotateArt1(lppt, nCount, rect);
		break;
	case 2:
		RotateArt2(lppt, nCount, rect);
		break;
	case 3:
		RotateArt3(lppt, nCount, rect);
		break;
	case 4:
		RotateArt4(lppt, nCount, rect);
		break;
	case 5:
		RotateArt5(lppt, nCount, rect);
		break;
	case 6:
		RotateArt6(lppt, nCount, rect);
		break;
	case 7:
		RotateArt7(lppt, nCount, rect);
		break;
	case 8:
		RotateArt8(lppt, nCount, rect);
		break;
	case 9:
		RotateArt9(lppt, nCount, rect);
		break;
	case 10:
		RotateArt10(lppt, nCount, rect);
		break;
	case 11:
		RotateArt11(lppt, nCount, rect);
		break;
	case 12:
		RotateArt12(lppt, nCount, rect);
		break;
	case 13:
		RotateArt13(lppt, nCount, rect);
		break;
	case 14:
		RotateArt14(lppt, nCount, rect);
		break;
	case 15:
		RotateArt15(lppt, nCount, rect);
		break;
	}
}

RECT CLFont::GetPointsRect(CONST LPPOINT lppt, int nCount) const
{
	RECT rect;

	rect.left = lppt[0].x;
	rect.right = rect.left;
	rect.top = lppt[0].y;
	rect.bottom = rect.top;
	for (int i = 1; i < nCount; i++)
	{
		if (lppt[i].x < rect.left) rect.left = lppt[i].x;
		if (lppt[i].x > rect.right) rect.right = lppt[i].x;
		if (lppt[i].y < rect.top) rect.top = lppt[i].y;
		if (lppt[i].y > rect.bottom) rect.bottom = lppt[i].y;
	}

	return rect;
}

void CLFont::RotateArt1(LPPOINT lppt, int nCount, RECT& rect) const
{
	float fXScale;

	if (m_bytArtParam1 < 50)
		fXScale = (float)m_bytArtParam1 / 50;
	else if (m_bytArtParam1 > 50)
		fXScale = (float)(100 - m_bytArtParam1) / 50;
	else
		return;

	for (int i=0; i < nCount; i++)
	{
		if (m_bytArtParam1 < 50)
			lppt[i].x = (long)(rect.left + (rect.right-rect.left) * (1 - fXScale) * (rect.bottom - lppt[i].y) / (rect.bottom-rect.top) + (lppt[i].x - rect.left) * fXScale);
		else
			lppt[i].x = (long)(rect.left + (rect.right-rect.left) * (1 - fXScale) * (lppt[i].y - rect.top) / (rect.bottom-rect.top) + (lppt[i].x - rect.left) * fXScale);
	}
}

void CLFont::RotateArt2(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xCenter = rect.left + (rect.right-rect.left) / 2;
	int yCenter = rect.top + (rect.bottom-rect.top) / 2;
	int nScale = m_bytArtParam1;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = yCenter + (lppt[i].y - yCenter) * (100 - nScale * abs(lppt[i].x - xCenter) / ((rect.right-rect.left) / 2)) / 100;
}

void CLFont::RotateArt3(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xRadius = (rect.right-rect.left) / 2;
	int xCenter = rect.left + xRadius;
	int nScale = m_bytArtParam1;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = rect.bottom - (rect.bottom - lppt[i].y) * (100 - nScale * abs(lppt[i].x - xCenter) / xRadius) / 100;
}

void CLFont::RotateArt4(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xRadius = (rect.right-rect.left) / 2;
	int xCenter = rect.left + xRadius;
	int nScale = m_bytArtParam1;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = rect.top + (lppt[i].y - rect.top) * (100 - nScale * abs(lppt[i].x - xCenter) / xRadius) / 100;
}

void CLFont::RotateArt5(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xRadius = (rect.right-rect.left) / 2;
	int xCenter = rect.left + xRadius;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.top + (rect.bottom-rect.top) * fScale * abs(lppt[i].x - xCenter) / xRadius + (lppt[i].y - rect.top) * (1 - fScale));
}

void CLFont::RotateArt6(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xRadius = (rect.right-rect.left) / 2;
	int xCenter = rect.left + xRadius;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.bottom - (rect.bottom-rect.top) * fScale * abs(lppt[i].x - xCenter) / xRadius - (rect.bottom - lppt[i].y) * (1 - fScale));
}

void CLFont::RotateArt7(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int yCenter = rect.top + (rect.bottom-rect.top) / 2;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(yCenter - (yCenter - lppt[i].y) * (1 - fScale * (lppt[i].x - rect.left) / (rect.right-rect.left)));
}

void CLFont::RotateArt8(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int yCenter = rect.top + (rect.bottom-rect.top) / 2;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(yCenter - (yCenter - lppt[i].y) * (1 - fScale * (rect.right - lppt[i].x) / (rect.right-rect.left)));
}

void CLFont::RotateArt9(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xCenter = rect.left + (rect.right-rect.left) / 2;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].x = (long)(xCenter - (xCenter - lppt[i].x) * (1 - fScale * (rect.bottom - lppt[i].y) / (rect.bottom-rect.top)));
}

void CLFont::RotateArt10(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	int xCenter = rect.left + (rect.right-rect.left) / 2;
	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].x = (long)(xCenter - (xCenter - lppt[i].x) * (1 - fScale * (lppt[i].y - rect.top) / (rect.bottom-rect.top)));
}

void CLFont::RotateArt11(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.top + (rect.bottom-rect.top) * fScale * (rect.right - lppt[i].x) / (rect.right-rect.left) + (lppt[i].y - rect.top) * (1 - fScale));
}

void CLFont::RotateArt12(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	float fScale = (float)m_bytArtParam1 / 100;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.top + (rect.bottom-rect.top) * fScale * (lppt[i].x - rect.left) / (rect.right-rect.left) + (lppt[i].y - rect.top) * (1 - fScale));
}

void CLFont::RotateArt13(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	float fScale1 = (float)m_bytArtParam1 / 100;
	float fScale2 = fScale1 / 4;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.top + (rect.bottom-rect.top) * fScale2 * (rect.right - lppt[i].x) / (rect.right-rect.left) + (lppt[i].y - rect.top) * (1 - fScale2 - (fScale1 - fScale2) * (lppt[i].x - rect.left) / (rect.right-rect.left)));
}

void CLFont::RotateArt14(LPPOINT lppt, int nCount, RECT& rect) const
{
	if (m_bytArtParam1 == 0)
		return;

	float fScale1 = (float)m_bytArtParam1 / 100;
	float fScale2 = fScale1 / 4;

	for (int i = 0; i < nCount; i++)
		lppt[i].y = (long)(rect.top + (rect.bottom-rect.top) * fScale2 * (lppt[i].x - rect.left) / (rect.right-rect.left) + (lppt[i].y - rect.top) * (1 - fScale1 + (fScale1 - fScale2) * (lppt[i].x - rect.left) / (rect.right-rect.left)));
}

void CLFont::RotateArt15(LPPOINT lppt, int nCount, RECT& rect) const
{
	
}

void CLFont::PointsShadow(LPPOINT lppt, int nCount) const
{
	switch(m_bytShadow)
	{
	case 0:
		ASSERT(FALSE);
		break;
	case 1:
		PointsShadow1(lppt, nCount);
		break;
	case 2:
		PointsShadow2(lppt, nCount);
		break;
	case 3:
		PointsShadow3(lppt, nCount);
		break;
	case 4:
		PointsShadow4(lppt, nCount);
		break;
	}
}

void CLFont::PointsShadow1(LPPOINT lppt, int nCount) const
{
	for (int i = 0; i < nCount; i++)
	{
		lppt[i].x = lppt[i].x - 2;
		lppt[i].y = lppt[i].y - 2;
	}
}

void CLFont::PointsShadow2(LPPOINT lppt, int nCount) const
{
	for (int i = 0; i < nCount; i++)
	{
		lppt[i].x = lppt[i].x + 2;
		lppt[i].y = lppt[i].y - 2;
	}
}

void CLFont::PointsShadow3(LPPOINT lppt, int nCount) const
{
	for (int i = 0; i < nCount; i++)
	{
		lppt[i].x = lppt[i].x - 2;
		lppt[i].y = lppt[i].y + 2;
	}
}

void CLFont::PointsShadow4(LPPOINT lppt, int nCount) const
{
	for (int i = 0; i < nCount; i++)
	{
		lppt[i].x = lppt[i].x + 2;
		lppt[i].y = lppt[i].y + 2;
	}
}
BOOL CLFont::OnSerial(CLSerial& ar)
{
	if(ar.isLoading()){
		ar>>m_bytArtParam1>>m_bytArtParam2>>m_bytArtStyle>>m_bytShadow\
			>>m_clr>>m_clrLine>>m_lf.lfCharSet>>m_lf.lfClipPrecision\
			>>m_lf.lfEscapement>>m_lf.lfFaceName>>m_lf.lfHeight>>m_lf.lfItalic\
			>>m_lf.lfOrientation>>m_lf.lfOutPrecision>>m_lf.lfPitchAndFamily\
			>>m_lf.lfQuality>>m_lf.lfStrikeOut>>m_lf.lfUnderline>>m_lf.lfWeight\
			>>m_lf.lfWidth;
		BYTE byt;
		ar>>byt;
		m_Alignment.setValue(byt);
	}else{
		ar<<m_bytArtParam1<<m_bytArtParam2<<m_bytArtStyle<<m_bytShadow<<m_clr\
			<<m_clrLine<<m_lf.lfCharSet<<m_lf.lfClipPrecision<<m_lf.lfEscapement\
			<<m_lf.lfFaceName<<m_lf.lfHeight<<m_lf.lfItalic<<m_lf.lfOrientation\
			<<m_lf.lfOutPrecision<<m_lf.lfPitchAndFamily<<m_lf.lfQuality<<m_lf.lfStrikeOut\
			<<m_lf.lfUnderline<<m_lf.lfWeight<<m_lf.lfWidth;
		BYTE byt=m_Alignment.getValue();
		ar<<byt;
	}
	m_clrFill.OnSerial(ar);
	return TRUE;
}