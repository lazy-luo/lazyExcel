// stdafx.cpp : source file that includes just the standard includes
//	LGridBook.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
//HINSTANCE g_hInstance=NULL;
#include "LComm/LGlobalParam.h"
#include "LGUILib/Base/LDrawItem.cpp"
#include "LGUILib/Src/LScrollBar.cpp"

#ifndef _LINK_DYN_TYPE_
	#include "Public/LBookLink.h"
#else
	#ifdef _WIN32
		#include "OSFace/WIN32/GDI/LDrawer.cpp"
		#include "OSFace/WIN32/LPlatform.cpp"
		#include "OSFace/WIN32/GDI/LPrintDC.cpp"
	#else
		#include "OSFace/Linux/GDI/LDrawer.cpp"
		#include "OSFace/Linux/LPlatform.cpp"
		#include "OSFace/Linux/GDI/LPrintDC.cpp"
		//不支持的平台
	#endif
	#include "LComm/LClipDC.cpp"
	#include "LComm/LMemDC.cpp"
	#ifdef _DEBUG
		#include "MemDebug/LDebugDef.h"
	#endif
#endif
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
