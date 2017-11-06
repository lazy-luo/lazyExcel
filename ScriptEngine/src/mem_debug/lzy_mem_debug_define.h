#ifdef _DEBUG_MEM
#ifndef _DEBUG_FLAG_
#include <list>
typedef std::list<ALLOC_INFO*> AllocList;
#ifndef BOOL
#define BOOL int
#endif
#ifndef FALSE
#define FALSE 0
#endif
	#ifdef WIN32
	#pragma warning(disable:4530)
	#endif
	class CLCSWrapper;
	AllocList *allocList;
	BOOL m_bStartDebug=FALSE;
	BOOL m_bTrackAlloc=FALSE;
#endif
#endif