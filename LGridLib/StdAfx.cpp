// stdafx.cpp : source file that includes just the standard includes
//	LGridLib.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
//HINSTANCE g_hInstance=NULL;
#include "../LComm/LGlobalParam.h"
#ifndef _LINK_DYN_TYPE_
#include "Public/LGridLink.h"
#else
	#ifdef _DEBUG
		#include "../MemDebug/LDebugDef.h"
	#endif
	#ifdef _WIN32
		#include "../OSFace/WIN32/GDI/LDrawer.cpp"
	#else
		#include "../OSFace/Linux/GDI/LDrawer.cpp"
		//不支持的平台
	#endif
	#ifdef _WIN32
		#include "../OSFace/WIN32/LPlatform.cpp"
	#else
		#include "../OSFace/Linux/LPlatform.cpp"
		//不支持的平台
	#endif
	#include "../LComm/LScript_Engine.cpp"
#endif
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
