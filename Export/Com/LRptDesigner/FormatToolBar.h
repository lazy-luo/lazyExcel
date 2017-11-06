#if !defined(AFX_FORMATTOOLBAR_H__BC9F81B3_91AA_4390_A12C_CB29A4EADFDC__INCLUDED_)
#define AFX_FORMATTOOLBAR_H__BC9F81B3_91AA_4390_A12C_CB29A4EADFDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormatToolBar.h : header file
//
#include "SizeComboBox.h"	// Added by ClassView
#include "FontComboBox.h"	// Added by ClassView
#include "Comm/LColorPicker.h"
/////////////////////////////////////////////////////////////////////////////
// CFormatToolBar window


#define FNC_NAME 1

#define FNC_SIZE 2
#define msg_ncSETFONT		WM_USER+15

#define msg_ncBookBar		WM_USER+16
struct NMFONTHDR : public tagNMHDR
{
	LOGFONT lf;
	enum {FONTNAME, FONTSIZE} mask;
};

class CFormatToolBar : public CToolBar
{
// Construction
public:
	CFormatToolBar();
	CLColorPicker m_wndForeColor;
	
	CLColorPicker m_wndBackColor;
	CSize m_szBaseUnits;
	CSizeComboBox m_lstFontSize;
	CFontComboBox m_lstFontName;
// Attributes
public:
	BOOL CreateBar(CWnd* pParentWnd);
// Operations
private:
	CDC m_dcPrinter;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnUpdateCombo();
	void OnUpdateColor();
	CLColorPicker m_wndBorder;
	virtual ~CFormatToolBar();

	void NotifyOwner(UINT nCode);
protected:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//{{AFX_MSG(CFormatToolBar)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnFontSizeDropDown();
	afx_msg void OnComboCloseUp();
	afx_msg void OnFontNameKillFocus();
	afx_msg void OnFontSizeKillFocus();
	afx_msg void OnComboSetFocus();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATTOOLBAR_H__BC9F81B3_91AA_4390_A12C_CB29A4EADFDC__INCLUDED_)
