#if !defined(AFX_LDLGMEMO_H__13845F7F_BD47_4DF8_A9A9_C5B1341F297A__INCLUDED_)
#define AFX_LDLGMEMO_H__13845F7F_BD47_4DF8_A9A9_C5B1341F297A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LDlgMemo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLDlgMemo dialog

class CLDlgMemo : public CDialog
{
// Construction
public:
	CLDlgMemo(CWnd* pParent = NULL);   // standard constructor
	CString m_strMemo;
// Dialog Data
	//{{AFX_DATA(CLDlgMemo)
	enum { IDD = IDD_DLG_MEMO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLDlgMemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLDlgMemo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LDLGMEMO_H__13845F7F_BD47_4DF8_A9A9_C5B1341F297A__INCLUDED_)
