#ifndef __LZY_GLOBALDEFINE_H_
#define __LZY_GLOBALDEFINE_H_
//是否动态联编
#define STATIC_LINK

#if !defined(STATIC_LINK)
#define _LINK_DYN_TYPE_
#endif
#ifdef _LINK_DYN_TYPE_
	#ifdef LTABLELIB_EXPORTS
		#define RES_MODULE_EXPORT	__declspec(dllexport)
	#else
		#define RES_MODULE_EXPORT	__declspec(dllimport)
	#endif
#else
	#define RES_MODULE_EXPORT
#endif
//是否共享版
//#define SHARE_VERSION

#ifdef SHARE_VERSION
#define SHARE_STRING		"报表引擎(共享版) V(1.0.00)【zhiyong.luo】"
#define FLAG_BAR_HEIGHT		24
#else
#define FLAG_BAR_HEIGHT		0
#endif

#endif
