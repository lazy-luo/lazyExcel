// LTableLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//#include "Src/LTable.h"
extern HINSTANCE g_hInstance;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	g_hInstance=(HINSTANCE)hModule;
    return TRUE;
	
}

