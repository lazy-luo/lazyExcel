// stdafx.cpp : source file that includes just the standard includes
//	LSheetLib.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
//HINSTANCE g_hInstance=NULL;
#include "../LComm/LGlobalParam.h"
#include "../LGUILib/Base/LDrawItem.cpp"
#ifndef _LINK_DYN_TYPE_
#include "Public/LSheetLink.h"
#else
	#ifdef _WIN32
		#include "../OSFace/WIN32/GDI/LDrawer.cpp"
		#include "../OSFace/WIN32/LPlatform.cpp"
	#else
		#include "../OSFace/Linux/GDI/LDrawer.cpp"
		#include "../OSFace/Linux/LPlatform.cpp"
		//不支持的平台
	#endif
	#ifdef _DEBUG
		#include "../MemDebug/LDebugDef.h"
	#endif
	#include "../LComm/LScript_Engine.cpp"
#endif
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
