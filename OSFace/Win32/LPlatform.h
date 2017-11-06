// LPlatform.h: interface for the CLPlatform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPLATFORM_H__9415B60E_1B4A_4F9D_B21F_263B8175BA36__INCLUDED_)
#define AFX_LPLATFORM_H__9415B60E_1B4A_4F9D_B21F_263B8175BA36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLPlatform  
{
public:
	CLPlatform();
	virtual ~CLPlatform();
	static BOOL IsNumeric(const char* src);
	static BOOL IsEmptyRect(const RECT& rctSrc);
	static BOOL PtInRect(const RECT* lprc,POINT pt);
	static DWORD GetSysColor(INT nIndex);
	static void	DebugMsg(char* ptr,...);
	static HCURSOR SetCursor(LONG resid);
	static void ClearRect(RECT& rct);
	static void ClearSize(SIZE& size);
	static void ClearPoint(POINT& pt);
	
	static BOOL SameRect(const RECT& rctSrc,const RECT& rctDst);
};

#endif // !defined(AFX_LPLATFORM_H__9415B60E_1B4A_4F9D_B21F_263B8175BA36__INCLUDED_)
