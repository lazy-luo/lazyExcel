// LStyle.h: interface for the CLStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSTYLE_H__B851552E_6FF5_4111_8571_FE0B95B7C11D__INCLUDED_)
#define AFX_LSTYLE_H__B851552E_6FF5_4111_8571_FE0B95B7C11D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Public/LPublicDef.h"
#include "../../LComm/LFont.h"
class TABLE_EXPORT_CLASS CLStyle  
{
private:
	COLORREF	m_clrLine;//边框颜色
	COLORREF	m_clrBK;//背景色
	//前景色由对应的字体对象提供
	LONG		m_iFont;//字体对象序号
	LONG		m_iBorder;//边框对象序号
	LONG		m_nStyle;
	LPTSTR		m_pValue;//公式值
	
	LPVOID		m_lpData;//用于扩展的字段
public:
	void CopyStyle(const CLStyle *ptr);
	BOOL OnSerial(CLSerial& ar);
	void ClearToDefault();
	_inline LPTSTR GetValue(){return m_pValue;};
	_inline void SetValue(LPTSTR ptr)
	{
		if(m_pValue){
			delete[] m_pValue;
			m_pValue=NULL;
		}
		if(ptr){
			m_pValue=new char[strlen(ptr)+1];
			strcpy(m_pValue,ptr);
		}
	};
	_inline LONG GetFormatStyle(){return (LONG)m_nStyle>>16;};
	_inline void SetFormatStyle(LONG style)
	{
		
		m_nStyle=((style<<16) & 0xffff0000) | (m_nStyle & 0x0000ffff);
	};
	_inline LONG GetType(){return (m_nStyle & 0x0000ffff);};
	_inline void SetType(LONG style)
	{
		
		m_nStyle=(style & 0x0000ffff) | (m_nStyle & 0xffff0000);
	};
	_inline COLORREF GetBorderColor(){return m_clrLine;};
	_inline void SetBorderColor(COLORREF clr){m_clrLine=clr;};
	_inline COLORREF GetBkColor(){return m_clrBK;};
	_inline void SetBkColor(COLORREF clr){m_clrBK=clr;};
	_inline LONG GetFontIndex(){return m_iFont;};
	_inline void SetFontIndex(LONG index){m_iFont=index;};
	_inline LONG GetBorderStyle(){
		return (m_iBorder & 0x0000ffff);
	};
	_inline void SetBorderStyle(LONG style){
		m_iBorder=(style & 0x0000ffff) | (m_iBorder & 0xffff0000);
	}
	_inline LONG GetBorderLineStyle(){return (LONG)m_iBorder>>16;};
	_inline void SetBorderLineStyle(LONG style)
	{
		m_iBorder=((style<<16) & 0xffff0000) | (m_iBorder & 0x0000ffff);
	};
	_inline LPVOID GetExtendData(){return m_lpData;};
	_inline void SetExtendData(LPVOID ptrData){m_lpData=ptrData;};
	_inline BOOL ReadOnly()
	{
		return (((LONG)m_nStyle>>16) & READ_ONLY);
	}
	
	_inline void ReadOnly(BOOL bVal)
	{
		if(bVal){
			m_nStyle=((READ_ONLY<<16) & 0xffff0000) | (m_nStyle & 0x0000ffff);
		}else{
			m_nStyle=((~(READ_ONLY<<16)) & m_nStyle) | (m_nStyle & 0x0000ffff);
		}
	}
	CLStyle();
	virtual ~CLStyle();
};
#define CLStylesArr	CLMapBaseExt<CELL,CLStyle>
#define CLFontArr	CLIndexMapBaseExt<CLFont>
#endif // !defined(AFX_LSTYLE_H__B851552E_6FF5_4111_8571_FE0B95B7C11D__INCLUDED_)
