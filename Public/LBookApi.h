//////////////////////////////////////////////////////////////////////
//@模块		 ：工作薄基础支持定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////
#ifndef _LBOOKAPI_H_
	#define _LBOOKAPI_H_
	#include "../LComm/LGlobalParam.h"

	#ifdef LZY_API
		#undef LZY_API
	#endif

	#ifdef LGRIDBOOK_EXPORTS
		#define BOOK_EXPORT_CLASS	__declspec(dllexport)
		#define LZY_API(type)  extern "C" type __declspec(dllexport)
	#else
		#define BOOK_EXPORT_CLASS	__declspec(dllimport)
		#define LZY_API(type)  extern "C" type __declspec(dllimport)
	#endif
	#ifndef _LINK_DYN_TYPE_
		#ifndef LGRIDBOOK_EXPORTS
			#undef BOOK_EXPORT_CLASS
			#define BOOK_EXPORT_CLASS
		#endif
	#else
		#pragma comment(lib,"LGUILib.lib")
		#pragma comment(lib,"LSheetLib.lib")
		#pragma comment(lib,"LGridLib.lib")
		#pragma comment(lib,"LTableLib.lib")
	#endif
#endif