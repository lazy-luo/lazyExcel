// stdafx.cpp : source file that includes just the standard includes
//	LGUILib.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
//HINSTANCE g_hInstance=NULL;
#include "../LComm/LGlobalParam.h"

#ifndef _LINK_DYN_TYPE_
#include "Public/LGUILink.h"
#else
	#ifdef _WIN32
		#include "../OSFace/WIN32/GDI/LDrawer.cpp"
		#include "../OSFace/WIN32/GDI/LPrintDC.cpp"
		#include "../OSFace/WIN32/LPlatform.cpp"
	#else
		#include "../OSFace/Linux/GDI/LDrawer.cpp"
		#include "../OSFace/Linux/GDI/LPrintDC.cpp"
		#include "../OSFace/Linux/LPlatform.cpp"
		//不支持的平台
	#endif
	#include "../LComm/LClipDC.cpp"
	#include "../LComm/LMemDC.cpp"
	#include "../LComm/LScript_Engine.cpp"
	#ifdef _DEBUG
		#include "../MemDebug/LDebugDef.h"
	#endif
#endif
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
