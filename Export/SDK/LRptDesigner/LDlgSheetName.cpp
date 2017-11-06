// LDlgSheetName.cpp : implementation file
//

#include "stdafx.h"
#include "LRptDesigner.h"
#include "LDlgSheetName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLDlgSheetName dialog


CLDlgSheetName::CLDlgSheetName(CWnd* pParent /*=NULL*/)
	: CDialog(CLDlgSheetName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLDlgSheetName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCaption.Empty();
}


void CLDlgSheetName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLDlgSheetName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLDlgSheetName, CDialog)
	//{{AFX_MSG_MAP(CLDlgSheetName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLDlgSheetName message handlers

void CLDlgSheetName::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItem(IDC_EDIT_SHEET_NAME)->GetWindowText(m_pCaption);
	m_pCaption.TrimRight();
	m_pCaption.TrimLeft();
	if(m_pCaption.IsEmpty()){
		MessageBox("您必须输入工作表的名称,请检查!","提示信息",MB_OK | MB_ICONQUESTION);
	}else{
		CDialog::OnOK();
	}
}

BOOL CLDlgSheetName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT_SHEET_NAME)->SetWindowText(m_pCaption);
	GetDlgItem(IDC_EDIT_SHEET_NAME)->SetFocus();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
