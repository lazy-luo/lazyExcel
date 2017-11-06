//////////////////////////////////////////////////////////////////////
//@模块		:	双缓冲支持类
//@作者		:	罗智勇
//@创建时间	:	2004-09-05
//////////////////////////////////////////////////////////////////////
#if !defined(_LZY_MEMDC) 
#define _LZY_MEMDC

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#define USE_WINDDC
#include "LGlobalParam.h"
class  CLMemDC  
{
private:
	HDC m_hDC,m_hRelDC;
	HBITMAP m_hBitMap,m_hOldBmp;
	RECT m_rct;
#ifdef USE_WINDDC
	static HWND	m_hWnd;
#endif
	void	GetClientRect(RECT &rct);
public:
	CLMemDC(HDC hDC,RECT& rct);
	virtual ~CLMemDC();
	inline operator HDC(){return (m_hDC?m_hDC:m_hRelDC);}
	
};


#endif