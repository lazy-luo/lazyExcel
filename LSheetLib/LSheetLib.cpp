// LSheetLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../LComm/LGlobalDefine.h"
RES_MODULE_EXPORT HINSTANCE g_hInstance;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
#ifndef _LINK_DYN_TYPE_
	g_hInstance=(HINSTANCE)hModule;
#endif
    return TRUE;
}

