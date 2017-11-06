// FontComboBox.cpp: implementation of the CFontComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LRptDesigner.h"
#include "FontComboBox.h"

#ifndef _DEBUG_MEM
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
#define BMW 16
#define BMH 15

int CFontComboBox::m_nFontHeight = 0;

CFontDesc::CFontDesc(LPCTSTR lpszName, LPCTSTR lpszScript, BYTE nCharSet, 
	BYTE nPitchAndFamily, DWORD dwFlags)
{
	m_strName = lpszName;
	m_strScript = lpszScript;
	m_nCharSet = nCharSet;
	m_nPitchAndFamily = nPitchAndFamily;
	m_dwFlags = dwFlags;
}

/////////////////////////////////////////////////////////////////////////////
// CFontComboBox

CFontComboBox::CFontComboBox()
{
	VERIFY(m_bmFontType.LoadBitmap(IDB_FONTTYPE));
}

CFontComboBox::~CFontComboBox()
{

}

BEGIN_MESSAGE_MAP(CFontComboBox, CToolBarComboBox)
	//{{AFX_MSG_MAP(CFontComboBox)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Operations

void CFontComboBox::EnumFontFamiliesEx(CDC& dc, BYTE nCharSet)
{
	CMapStringToPtr map;
	CString str;
	GetTheText(str);

	EmptyContents();
	ResetContent();
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfCharSet = nCharSet;

	if (dc.m_hDC != NULL)
		::EnumFontFamiliesEx(dc.m_hDC, &lf,
			(FONTENUMPROC) EnumFamPrinterCallBackEx, (LPARAM) this, NULL);
	else
	{
		CClientDC dc(NULL);
		HDC hDC = dc.m_hDC;
		ASSERT(hDC != NULL);
		::EnumFontFamiliesEx(hDC, &lf,
			(FONTENUMPROC) EnumFamScreenCallBackEx, (LPARAM) this, NULL);
	}
	// now walk through the fonts and remove (charset) from fonts with only one

	int nCount = m_arrayFontDesc.GetSize();
	// walk through fonts adding names to string map
	// first time add value 0, after that add value 1
	for (int i = 0; i<nCount;i++)
	{
		CFontDesc* pDesc = (CFontDesc*)m_arrayFontDesc[i];
		void* pv = NULL;
		if (map.Lookup(pDesc->m_strName, pv)) // found it
		{
			if (pv == NULL) // only one entry so far
			{
				map.RemoveKey(pDesc->m_strName);
				map.SetAt(pDesc->m_strName, (void*)1);
			}
		}
		else // not found
			map.SetAt(pDesc->m_strName, (void*)0);
	}

	for (i = 0; i<nCount;i++)
	{
		CFontDesc* pDesc = (CFontDesc*)m_arrayFontDesc[i];
		CString str = pDesc->m_strName;
		void* pv = NULL;
		VERIFY(map.Lookup(str, pv));
		if (pv != NULL && !pDesc->m_strScript.IsEmpty())
		{
			str += " (";
			str += pDesc->m_strScript;
			str += ")";
		}

		int nIndex = AddString(str);
		ASSERT(nIndex >=0);
		if (nIndex >=0) //no error
			SetItemData(nIndex, (DWORD)pDesc);
	}

	SetTheText(str);
	m_arrayFontDesc.RemoveAll();
}

void CFontComboBox::AddFont(ENUMLOGFONT* pelf, DWORD dwType, LPCTSTR lpszScript)
{
	LOGFONT& lf = pelf->elfLogFont;
	if (lf.lfCharSet == MAC_CHARSET) // don't put in MAC fonts, commdlg doesn't either
		return;
	// Don't display vertical font for FE platform
	if ((GetSystemMetrics(SM_DBCSENABLED)) && (lf.lfFaceName[0] == '@'))
		return;
	// don't put in non-printer raster fonts
	CFontDesc* pDesc = new CFontDesc(lf.lfFaceName, lpszScript, 
		lf.lfCharSet, lf.lfPitchAndFamily, dwType);
	m_arrayFontDesc.Add(pDesc);
}

void CFontComboBox::MatchFont(LPCTSTR lpszName, BYTE nCharSet)
{
	int nFirstIndex = FindString(-1, lpszName);
	if (nFirstIndex != CB_ERR)
	{
		int nIndex = nFirstIndex;
		do
		{ 
			CFontDesc* pDesc = (CFontDesc*)GetItemData(nIndex);
			ASSERT(pDesc != NULL);
			// check the actual font name to avoid matching Courier western
			// to Courier New western
			if ((nCharSet == DEFAULT_CHARSET || pDesc->m_nCharSet == nCharSet) && 
				lstrcmp(lpszName, pDesc->m_strName)==0)
			{
				//got a match
				if (GetCurSel() != nIndex)
					SetCurSel(nIndex);
				return;
			}
			nIndex = FindString(nIndex, lpszName);
		} while (nIndex != nFirstIndex);
		// loop until found or back to first item again
	}
	//enter font name
	SetTheText(lpszName, TRUE);
}

void CFontComboBox::EmptyContents()
{
	// destroy all the CFontDesc's
	int nCount = GetCount();
	for (int i=0;i<nCount;i++)
		delete (CFontDesc*)GetItemData(i);
}

BOOL CALLBACK AFX_EXPORT CFontComboBox::EnumFamScreenCallBack(ENUMLOGFONT* pelf, 
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID pThis)
{
	// don't put in non-printer raster fonts
	if (FontType & RASTER_FONTTYPE)
		return 1;
	DWORD dwData = (FontType & TRUETYPE_FONTTYPE) ? TT_FONT : 0;
	((CFontComboBox *)pThis)->AddFont(pelf, dwData);
	return 1;
}

BOOL CALLBACK AFX_EXPORT CFontComboBox::EnumFamPrinterCallBack(ENUMLOGFONT* pelf, 
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID pThis)
{
	DWORD dwData = PRINTER_FONT;
	if (FontType & TRUETYPE_FONTTYPE)
		dwData |= TT_FONT;
	else if (FontType & DEVICE_FONTTYPE)
		dwData |= DEVICE_FONT;
	((CFontComboBox *)pThis)->AddFont(pelf, dwData);
	return 1;
}

BOOL CALLBACK AFX_EXPORT CFontComboBox::EnumFamScreenCallBackEx(ENUMLOGFONTEX* pelf, 
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID pThis)
{
	// don't put in non-printer raster fonts
	if (FontType & RASTER_FONTTYPE)
		return 1;
	DWORD dwData = (FontType & TRUETYPE_FONTTYPE) ? TT_FONT : 0;
	((CFontComboBox *)pThis)->AddFont((ENUMLOGFONT*)pelf, dwData, CString(pelf->elfScript));
	return 1;
}

BOOL CALLBACK AFX_EXPORT CFontComboBox::EnumFamPrinterCallBackEx(ENUMLOGFONTEX* pelf, 
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID pThis)
{
	DWORD dwData = PRINTER_FONT;
	if (FontType & TRUETYPE_FONTTYPE)
		dwData |= TT_FONT;
	else if (FontType & DEVICE_FONTTYPE)
		dwData |= DEVICE_FONT;
	((CFontComboBox *)pThis)->AddFont((ENUMLOGFONT*)pelf, dwData, CString(pelf->elfScript));
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CFontComboBox message handlers

void CFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	int id = (int)(WORD)lpDrawItemStruct->itemID;

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc(lpDrawItemStruct->rcItem);
	if (lpDrawItemStruct->itemState & ODS_FOCUS)
		pDC->DrawFocusRect(rc);
	int nIndexDC = pDC->SaveDC();

	CBrush brushFill;
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		brushFill.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
		brushFill.CreateSolidBrush(pDC->GetBkColor());
	pDC->SetBkMode(TRANSPARENT);
	pDC->FillRect(rc, &brushFill);

	CFontDesc* pDesc= (CFontDesc*)lpDrawItemStruct->itemData;
	ASSERT(pDesc != NULL);
	DWORD dwData = pDesc->m_dwFlags;
	if (dwData & (TT_FONT|DEVICE_FONT)) // truetype or device flag set by SetItemData
	{
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		CBitmap* pBitmap = dc.SelectObject(&m_bmFontType);
		if (dwData & TT_FONT)
			pDC->BitBlt(rc.left, rc.top, BMW, BMH, &dc, BMW, 0, SRCAND);
		else // DEVICE_FONT
			pDC->BitBlt(rc.left, rc.top, BMW, BMH, &dc, 0, 0, SRCAND);
		dc.SelectObject(pBitmap);
	}
	LOGFONT lf={-14, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, _T("ËÎÌו")};
	rc.left += BMW + 6;
	CString strText;
	GetLBText(id, strText);
	strcpy(lf.lfFaceName,strText);
	CFont font;
	font.CreateFontIndirect(&lf);
	CFont* pOldFont=pDC->SelectObject(&font);
	pDC->TextOut(rc.left,rc.top,strText,strText.GetLength());
	pDC->SelectObject(pOldFont);
	pDC->RestoreDC(nIndexDC);	
}

void CFontComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	ASSERT(lpMeasureItemStruct->CtlType == ODT_COMBOBOX);
	ASSERT(m_nFontHeight > 0);
	CRect rc;
	
	GetWindowRect(&rc);
	lpMeasureItemStruct->itemWidth = rc.Width();
	lpMeasureItemStruct->itemHeight = max(BMH, m_nFontHeight);	
}

int CFontComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	ASSERT(lpCompareItemStruct->CtlType == ODT_COMBOBOX);
	int id1 = (int)(WORD)lpCompareItemStruct->itemID1;
	int id2 = (int)(WORD)lpCompareItemStruct->itemID2;
	CString str1,str2;
	if (id1 == -1)
		return -1;
	if (id2 == -1)
		return 1;
	GetLBText(id1, str1);
	GetLBText(id2, str2);
	return str1.Collate(str2);
}

void CFontComboBox::OnDestroy() 
{
	CToolBarComboBox::OnDestroy();
	
	// destroy all the CFontDesc's
	EmptyContents();	
}



