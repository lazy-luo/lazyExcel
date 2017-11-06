// LPlatformLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

LZY_API(void) Test()
{
	char ptr[MAX_PATH];
//	sprintf(ptr,"sfsfsf");
	return;
}
void copyString(char* ptrdst,const char* ptrsrc)
{
	__asm
	{
		push eax
		mov eax,ptrsrc
		
	}
}
void memcopy(char* ptrdst,const char* ptrsrc,LONG ilen)
{
	__asm{
		pushad
		//mov eax,[ptrsrc]
		mov si,ax
		//move eax,[ptrdst]
		move di,ax
		move cx,ilen
LP:
		move byte ptr [di],[si]
		inc di
		inc si
		//dec ecx;
		loopnz LP
		popad
		ret
	}
}