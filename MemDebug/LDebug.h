//以下代码用于调试内存
#ifndef _LDEBUG_H_INCLUDE_
#define _LDEBUG_H_INCLUDE_

#ifdef _DEBUG_MEM
/*
#ifdef DEBUG_NEW
#undef DEBUG_NEW
#endif
*/
#include<new>
#include <list>
//#define NEW  ::new
#pragma warning(disable:4530)
	typedef struct
	{
		DWORD address;
		DWORD size;
		char file[64];
		DWORD line;
	} ALLOC_INFO;
	typedef std::list<ALLOC_INFO*> AllocList;
	extern AllocList *allocList;
	extern BOOL m_bStartDebug;
	inline void __cdecl AddTrack(DWORD addr, DWORD asize, const char *fname, DWORD lnum)
	{
		if(m_bStartDebug){
			ALLOC_INFO *info;

			if(!allocList) 
			{
				allocList = ::new(AllocList);
			}
			info = ::new(ALLOC_INFO);
			info->address = addr;
			strncpy(info->file, fname, 63);
			info->line = lnum;
			info->size = asize;
			allocList->insert(allocList->begin(), info);
		}
		
	};

	inline void __cdecl RemoveTrack(DWORD addr)
	{
		if(m_bStartDebug){
			AllocList::iterator i;

			if(!allocList)
			return;
			for(i = allocList->begin(); i != allocList->end(); i++)
			{
				if((*i)->address == addr)
				{
					allocList->remove((*i));
					break;
				}
			}
		}
	};
	inline void  __cdecl DumpUnfreed()
	{
		
		AllocList::iterator i;
		DWORD totalSize = 0;
		char buf[1024];
		if(!allocList)
			return;
		sprintf(buf, "-------------------------------------");
		OutputDebugString(buf);
		sprintf(buf, "开始调试内存[By 罗智勇]-------------------------------------\n", totalSize);
		OutputDebugString(buf);
		for(i = allocList->begin(); i != allocList->end(); i++) 
		{
			sprintf(buf, "文件: %-50s: 行: %d, 分配了%d字节未释放[<内存地址: %d>] \n",
			(*i)->file, (*i)->line, (*i)->size, (*i)->address);

			OutputDebugString(buf);
			totalSize += (*i)->size;
		}
		sprintf(buf, "-------------------------------------");
		OutputDebugString(buf);
		sprintf(buf, "未释放的内存总计: %d 字节-------------------------------------\n", totalSize);
		OutputDebugString(buf);
		
	};

inline void * __cdecl operator new(unsigned int size,const char *file, int line)
{
	void *ptr =(void *)malloc(size);
	AddTrack((DWORD)ptr, size, file, line);
	return(ptr);
};
inline void __cdecl operator delete(void *p, LPCSTR lpszFileName, int nLine)
{
	operator delete(p);
}
inline void __cdecl operator delete(void *p)
{
	RemoveTrack((DWORD)p);
	free(p);
};
inline void __cdecl operator delete[](void *p)
{
	RemoveTrack((DWORD)p);
	free(p);
};
#endif
#ifndef DEBUG_NEW
#ifdef _DEBUG_MEM
#define DEBUG_NEW new(__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#define new DEBUG_NEW
#endif
#ifdef _DEBUG_MEM
#define _START_ m_bStartDebug=TRUE;
#define _END_  {DumpUnfreed();m_bStartDebug=FALSE;}
#else
#define _START_
#define _END_
#endif
#endif