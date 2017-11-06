#if !defined(AFX_SIZECOMBOBOX_H__908610CF_5AB8_466D_8D42_30647521D496__INCLUDED_)
#define AFX_SIZECOMBOBOX_H__908610CF_5AB8_466D_8D42_30647521D496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SizeComboBox.h : header file
//
#include "ToolBarComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CSizeComboBox window

class CSizeComboBox : public CToolBarComboBox
{
public:
	/** 字体大小选择框对象构造函数 */
	CSizeComboBox();

// Attributes
public:

	int m_nLogVert;
	int m_nTwipsLast;

// Operations
public:
	/** 字体大小列举 */
	void EnumFontSizes(CDC& dc, LPCTSTR pFontName);
	/** 大小型号列举回调函数 */
	static BOOL FAR PASCAL EnumSizeCallBack(LOGFONT FAR* lplf, 
		LPNEWTEXTMETRIC lpntm,int FontType, LPVOID lpv);
	/** 把Twips转化为点字串 */
	void TwipsToPointString(LPTSTR lpszBuf, int nTwips);
	/** 设置twips的大小 */
	void SetTwipSize(int nSize);
	/** 获取twips的大小 */
	int GetTwipSize();
	/** 插入一个大小型号 */
	void InsertSize(int nSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizeComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	/** 析构函数 */
	virtual ~CSizeComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSizeComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIZECOMBOBOX_H__908610CF_5AB8_466D_8D42_30647521D496__INCLUDED_)
