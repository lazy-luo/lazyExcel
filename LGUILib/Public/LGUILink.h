#ifndef _LGUILINK_H_INCLUDE_
#define _LGUILINK_H_INCLUDE_
#include "../../LSheetLib/Public/LSheetLink.h"
//Grid实现文件
#ifdef _WIN32
	#include "../../OSFace/WIN32/GDI/LPrintDC.cpp"
#else
	#include "../../OSFace/Linux/GDI/LPrintDC.cpp"
	//不支持的平台
#endif
#include "../../LSheetLib/Src/LSheet.cpp"
#endif