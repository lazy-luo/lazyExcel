// FontComboBox.h: interface for the CFontComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTCOMBOBOX_H__65F201C6_81F1_4DBB_961A_9FB59515267F__INCLUDED_)
#define AFX_FONTCOMBOBOX_H__65F201C6_81F1_4DBB_961A_9FB59515267F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ToolBarComboBox.h"
#define PRINTER_FONT 0x0100
#define TT_FONT	0x0200
#define DEVICE_FONT 0x0400
/**
 *	字体描述对象
 *	构造字体基本特针
 */
class CFontDesc
{
public:
	CFontDesc(LPCTSTR lpszName, LPCTSTR lpszScript, BYTE nCharSet, 
		BYTE nPitchAndFamily, DWORD dwFlags);
	/** 字体名称 */
	CString m_strName;
	/** 脚本 */
	CString m_strScript;
	/** 字符 */
	BYTE m_nCharSet;
	/** 间距 */
	BYTE m_nPitchAndFamily;
	DWORD m_dwFlags;
};

class CFontComboBox : public CToolBarComboBox  
{
public:
	CFontComboBox();
public:
	/** 字体数组映射对象 */
	CPtrArray m_arrayFontDesc;
	/** 字体高度 */
	static int m_nFontHeight;
	/** 字体类型 */
	CBitmap m_bmFontType;
public:
	/** 字体系列集合 */
	void EnumFontFamiliesEx(CDC& dc, BYTE nCharSet = DEFAULT_CHARSET);
	/** 增加字体 */
	void AddFont(ENUMLOGFONT* pelf, DWORD dwType, LPCTSTR lpszScript = NULL);
	/** 字体匹配 */
	void MatchFont(LPCTSTR lpszName, BYTE nCharSet);
	void EmptyContents();

	static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBack(
		ENUMLOGFONT* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType, 
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBack(
		ENUMLOGFONT* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType, 
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType, 
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType, 
		LPVOID pThis);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontComboBox)
	public:
	/** 绘制数据项 */
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	/** 数据项尺寸 */
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	/** 数据相比较 */
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	/** 析构函数 */
	virtual ~CFontComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFontComboBox)
	/** 注销消息 */
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_FONTCOMBOBOX_H__65F201C6_81F1_4DBB_961A_9FB59515267F__INCLUDED_)
