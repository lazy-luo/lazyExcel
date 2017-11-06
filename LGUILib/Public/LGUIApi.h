#ifndef _LGUIAPI_H_INCLUDE_
	#define _LGUIAPI_H_INCLUDE_
	#include "../../LComm/LGlobalParam.h"

	#ifdef LZY_API
		#undef LZY_API
	#endif
	//DRAWER对象内部消息定义
	/////////////////////////////////////////////////////
	#define MSG_ONDRAWER					1003	//绘图消息
	#define	TMSG_DRAW_CELL					1//绘制单元格
	#define	TMSG_DRAW_SCROLLBAR				2//绘制滚动条
	#define	TMSG_DRAW_TABLEITEM				3//绘制TAB项
	#define	TMSG_DRAW_TABLEBUTTOM			4//
	#ifdef LGUILIB_EXPORTS
		#define GUI_EXPORT_CLASS	__declspec(dllexport)
		#define LZY_API(type)  extern "C" type __declspec(dllexport)
	#else
		#define GUI_EXPORT_CLASS	__declspec(dllimport)
		#define LZY_API(type)  extern "C" type __declspec(dllimport)
	#endif
	#ifndef _LINK_DYN_TYPE_
		#ifndef LGUILIB_EXPORTS
			#undef GUI_EXPORT_CLASS
			#define GUI_EXPORT_CLASS
		#endif
	#else
		#pragma comment(lib,"LSheetLib.lib")
		#pragma comment(lib,"LGridLib.lib")
		#pragma comment(lib,"LTableLib.lib")
	#endif

#endif