#ifndef _LGRIDAPI_H_
	#define _LGRIDAPI_H_
	#include "../../LComm/LGlobalParam.h"
	
	#ifdef LZY_API
	#undef LZY_API
	#endif

	#ifdef LGRIDLIB_EXPORTS
		#define GRID_EXPORT_CLASS	__declspec(dllexport)
		#define LZY_API(type)  extern "C" type __declspec(dllexport)
	#else
		#define GRID_EXPORT_CLASS	__declspec(dllimport)
		#define LZY_API(type)  extern "C" type __declspec(dllimport)
	#endif
	#ifndef _LINK_DYN_TYPE_
		#ifndef LGRIDLIB_EXPORTS
			#undef  GRID_EXPORT_CLASS
			#define GRID_EXPORT_CLASS
		#endif
	#else
		#pragma comment(lib,"LTableLib.lib")
	#endif
#endif