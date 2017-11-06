// LDlgMemo.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "LDlgMemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLDlgMemo dialog


CLDlgMemo::CLDlgMemo(CWnd* pParent /*=NULL*/)
	: CDialog(CLDlgMemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLDlgMemo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strMemo.Empty();
}


void CLDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLDlgMemo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLDlgMemo, CDialog)
	//{{AFX_MSG_MAP(CLDlgMemo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLDlgMemo message handlers

void CLDlgMemo::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItem(IDC_EDIT_MEMO)->GetWindowText(m_strMemo);
	m_strMemo.TrimRight();
	m_strMemo.TrimLeft();
	CDialog::OnOK();
}

BOOL CLDlgMemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT_MEMO)->SetWindowText(m_strMemo);
	GetDlgItem(IDC_EDIT_MEMO)->SetFocus();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
