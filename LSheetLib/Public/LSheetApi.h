#ifndef _LSHEETAPI_H_
	#define _LSHEETAPI_H_
	#include "../../LComm/LGlobalParam.h"

	#ifdef LZY_API
		#undef LZY_API
	#endif
	//SHEET对象内部消息定义
	/////////////////////////////////////////////////////
	#define MSG_ONSHEET					1002	//样式改变
	#define	TMSG_SHEET_REPLACERANGE			1//区域覆盖
	#define	TMSG_SHEET_FILLRANGE			2//区域填充
	#define	TMSG_SHEET_CLICK				3//鼠标单击消息
	
	#ifdef LSHEETLIB_EXPORTS
		#define SHEET_EXPORT_CLASS	__declspec(dllexport)
		#define LZY_API(type)  extern "C" type __declspec(dllexport)
	#else
		#define SHEET_EXPORT_CLASS	__declspec(dllimport)
		#define LZY_API(type)  extern "C" type __declspec(dllimport)
	#endif
	#ifndef _LINK_DYN_TYPE_
		#ifndef LSHEETLIB_EXPORTS
			#undef SHEET_EXPORT_CLASS
			#define SHEET_EXPORT_CLASS
		#endif
	#else
		#pragma comment(lib,"LGridLib.lib")
		#pragma comment(lib,"LTableLib.lib")
	#endif
#endif