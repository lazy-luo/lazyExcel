// SizeComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LRptDesigner.h"
#include "SizeComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static int nFontSizes[] = 
	{8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72};

/////////////////////////////////////////////////////////////////////////////
// CSizeComboBox

CSizeComboBox::CSizeComboBox()
{
	m_nTwipsLast = 0;
}

CSizeComboBox::~CSizeComboBox()
{
}


BEGIN_MESSAGE_MAP(CSizeComboBox, CToolBarComboBox)
	//{{AFX_MSG_MAP(CSizeComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Operations

void CSizeComboBox::EnumFontSizes(CDC& dc, LPCTSTR pFontName)
{
	ResetContent();
	if (pFontName == NULL)
		return;
	if (pFontName[0] == NULL)
		return;
	
	ASSERT(dc.m_hDC != NULL);
	m_nLogVert = dc.GetDeviceCaps(LOGPIXELSY);

	::EnumFontFamilies(dc.m_hDC, pFontName,
		(FONTENUMPROC) EnumSizeCallBack, (LPARAM) this);
}

void CSizeComboBox::TwipsToPointString(LPTSTR lpszBuf, int nTwips)
{
	ASSERT(lpszBuf != NULL);
	lpszBuf[0] = NULL;
	if (nTwips >= 0)
	{
		// round to nearest half point
		nTwips = (nTwips+5)/10;
		if ((nTwips%2) == 0)
			_stprintf(lpszBuf, _T("%ld"), nTwips/2);
		else
			_stprintf(lpszBuf, _T("%.1f"), (float)nTwips/2.F);
	}
}

void CSizeComboBox::SetTwipSize(int nTwips)
{
	if (nTwips != GetTwipSize())
	{
		TCHAR buf[10];
		TwipsToPointString(buf, nTwips);
		SetTheText(buf, TRUE);
	}
	m_nTwipsLast = nTwips;
}

int CSizeComboBox::GetTwipSize()
{
	// return values
	// -2 -- error
	// -1 -- edit box empty
	// >=0 -- font size in twips
	CString str;
	GetTheText(str);
	LPCTSTR lpszText = str;

	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (lpszText[0] == NULL)
		return -1; // no text in control

	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (*lpszText != NULL)
		return -2;   // not terminated properly

	return (d<0.) ? 0 : (int)(d*20.);
}

BOOL CALLBACK AFX_EXPORT CSizeComboBox::EnumSizeCallBack(LOGFONT FAR* /*lplf*/, 
		LPNEWTEXTMETRIC lpntm, int FontType, LPVOID lpv)
{
	CSizeComboBox* pThis = (CSizeComboBox*)lpv;
	ASSERT(pThis != NULL);
	TCHAR buf[10];
	if (
		(FontType & TRUETYPE_FONTTYPE) || 
		!( (FontType & TRUETYPE_FONTTYPE) || (FontType & RASTER_FONTTYPE) )
		) // if truetype or vector font
	{
		// this occurs when there is a truetype and nontruetype version of a font
		if (pThis->GetCount() != 0)
			pThis->ResetContent();
					
		for (int i = 0; i < 16; i++)
		{
			wsprintf(buf, _T("%d"), nFontSizes[i]);
			pThis->AddString(buf);
		}
		return FALSE; // don't call me again
	}
	// calc character height in pixels
	pThis->InsertSize(MulDiv(lpntm->tmHeight-lpntm->tmInternalLeading, 
		1440, pThis->m_nLogVert));
	return TRUE; // call me again
}

void CSizeComboBox::InsertSize(int nSize)
{
	ASSERT(nSize > 0);
	DWORD dwSize = (DWORD)nSize;
	TCHAR buf[10];
	TwipsToPointString(buf, nSize);
	if (FindStringExact(-1, buf) == CB_ERR)
	{
		int nIndex = -1;
		int nPos = 0;
		DWORD dw;
		while ((dw = GetItemData(nPos)) != CB_ERR)
		{
			if (dw > dwSize)
			{
				nIndex = nPos;
				break;
			}
			nPos++;
		}
		nIndex = InsertString(nIndex, buf);
		ASSERT(nIndex != CB_ERR);
		if (nIndex != CB_ERR)
			SetItemData(nIndex, dwSize);
	}
}


