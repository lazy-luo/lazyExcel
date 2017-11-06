// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "../../LComm/LGlobalParam.h"
#include "../../OSFace/Win32/InterLink/InplaceCtrl/LEditCtrl.cpp"
#ifndef _LINK_DYN_TYPE_
	#include "../../Public/LBookLink.h"
#else
	#ifdef _WIN32
		#include "../../OSFace/WIN32/GDI/LDrawer.cpp"
		#include "../../OSFace/WIN32/GDI/LPrintDC.cpp"
		#include "../../OSFace/WIN32/LPlatform.cpp"
	#else
		#include "../../OSFace/Linux/GDI/LDrawer.cpp"
		#include "../../OSFace/Linux/GDI/LPrintDC.cpp"
		#include "../../OSFace/Linux/LPlatform.cpp"
		//不支持的平台
	#endif
	#include "../../LComm/LScript_Engine.cpp"
	#include "../../LComm/LClipDC.cpp"
	#include "../../LComm/LMemDC.cpp"
	#ifdef _DEBUG
		#include "../../MemDebug/LDebugDef.h"
	#endif
#endif

#include "../../Base/LTabArea.cpp"
#include "../../LGUILib/Base/LDrawItem.cpp"
#include "../../LGUILib/Src/LScrollBar.cpp"
#include "../../OSFace/Win32/InterLink/LRptGrid.cpp"
#include "../../Src/LBook.cpp"
#include "../SDK/LExport.cpp"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>