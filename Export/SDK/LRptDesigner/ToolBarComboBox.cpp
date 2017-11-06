// ToolBarComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "ToolBarComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarComboBox

CToolBarComboBox::CToolBarComboBox()
{
}

CToolBarComboBox::~CToolBarComboBox()
{
}


BEGIN_MESSAGE_MAP(CToolBarComboBox, CLFlatComboBox)
	//{{AFX_MSG_MAP(CToolBarComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarComboBox message handlers
void CToolBarComboBox::GetTheText(CString& str)
{
	int nIndex = GetCurSel();
	if (nIndex == CB_ERR)
		GetWindowText(str);
	else
		GetLBText(nIndex, str);
}

void CToolBarComboBox::SetTheText(LPCTSTR lpszText,BOOL bMatchExact)
{
	int idx = (bMatchExact) ? FindStringExact(-1,lpszText) : 
		FindString(-1, lpszText);
	SetCurSel( (idx==CB_ERR) ? -1 : idx);
	if (idx == CB_ERR)
		SetWindowText(lpszText);
}

/////////////////////////////////////////////////////////////////////////////
// CBarComboBox message handlers

BOOL CToolBarComboBox::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		CToolBar* pBar = (CToolBar*)GetParent();
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_TAB:
			pBar->GetNextDlgTabItem(this)->SetFocus();
			return TRUE;
		case VK_UP:
		case VK_DOWN:
			if ((GetKeyState(VK_MENU) >= 0) && (GetKeyState(VK_CONTROL) >=0) && 
				!GetDroppedState())
			{
				ShowDropDown();
				return TRUE;
			}
		}
	}
	
	return CLFlatComboBox::PreTranslateMessage(pMsg);
}
