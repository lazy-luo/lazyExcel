//////////////////////////////////////////////////////////////////////
//@模块		 ：裁减对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCLIPDC_H__7306AC0B_F179_4D3D_B58C_E9CD4A358282__INCLUDED_)
#define AFX_LCLIPDC_H__7306AC0B_F179_4D3D_B58C_E9CD4A358282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "LGlobalParam.h"
class  CLClipDC  
{
public:
	void SetClip(HDC hDC,RECT& rct);
	void GetSize(SIZE& size);
	CLClipDC();
	CLClipDC(HDC hDC,RECT& rct);
	virtual ~CLClipDC();
private:
	BOOL	bRestory;
	HDC		m_hDC;
	SIZE	m_Size;
	RECT	m_Rect;
};

#endif // !defined(AFX_LCLIPDC_H__7306AC0B_F179_4D3D_B58C_E9CD4A358282__INCLUDED_)
