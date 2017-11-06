// LPlatform.cpp: implementation of the CLPlatform class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LPlatform.h"
#include "../../LComm/LGlobalDefine.h"
//RES_MODULE_EXPORT HINSTANCE g_hInstance;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLPlatform::CLPlatform()
{

}

CLPlatform::~CLPlatform()
{

}
void CLPlatform::ClearSize(SIZE& size)
{
	size.cx=0;
	size.cy=0;
}
void CLPlatform::ClearPoint(POINT& pt)
{
	pt.x=0;
	pt.y=0;
}
BOOL CLPlatform::SameRect(const RECT& rctSrc,const RECT& rctDst)
{
	return rctSrc.left==rctDst.left && rctSrc.top==rctDst.top
		&& rctSrc.right==rctDst.right && rctSrc.bottom==rctDst.bottom;
}
BOOL CLPlatform::IsEmptyRect(const RECT& rctSrc)
{
	return rctSrc.left==0 && rctSrc.top==0
		&& rctSrc.right==0 && rctSrc.bottom==0;
}
BOOL CLPlatform::PtInRect(const RECT* lprc,POINT pt)
{
	return ::PtInRect(lprc,pt);
}
DWORD CLPlatform::GetSysColor(INT nIndex)
{
	return ::GetSysColor(nIndex);
}
void CLPlatform::DebugMsg(char* ptr,...)
{
#ifdef _DEBUG
	char    buf[4096];
	va_list args;
	
	va_start(args,ptr);
	vsprintf(buf,ptr,args);
	va_end(args);
	strcat(buf,"\n");
	OutputDebugString(buf);

#endif
}
void CLPlatform::ClearRect(RECT& rct)
{
	rct.left=0;
	rct.top=0;
	rct.bottom=0;
	rct.right=0;
}

HCURSOR CLPlatform::SetCursor(LONG resid)
{
	if(g_hInstance){
		if(resid!=DEFAULT_CURSOR)
			return ::SetCursor(LoadCursor(g_hInstance,MAKEINTRESOURCE(resid)));
	}
	return NULL;
}
BOOL CLPlatform::IsNumeric(const char* src)
{
	if(!src)return FALSE;
	BOOL bPre=TRUE;
	INT	dotCount=0;
	char val;
	while(val=*src++){
		if(bPre && val==' ')continue;//掠过前导空格
		if(bPre){
			bPre=FALSE;
			if(val=='+' || val=='-')continue;
		}
		if((val<'0' || val>'9') 
			&& !(val=='.' && !dotCount++))
			return FALSE;
	}
	return TRUE;
}
