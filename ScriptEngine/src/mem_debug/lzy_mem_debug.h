//以下代码用于调试内存
#ifndef _LDEBUG_H_INCLUDE_
#define _LDEBUG_H_INCLUDE_
#ifndef DWORD
#define DWORD long
#endif
#ifndef BOOL
#define BOOL int
#endif
#include "../lockmgrl.h"
#ifdef WIN32
#define DEBUG_STRING(x) OutputDebugString(x)
#else
#define DEBUG_STRING(x)
#endif
#ifdef _DEBUG_MEM
	#include<new>
	#include <list>
	#ifdef WIN32
	#pragma warning(disable:4530)
	#endif
	#ifndef MAX_PATH
	#define MAX_PATH 256
	#endif
	typedef struct{
		DWORD address;
		DWORD size;
		char file[MAX_PATH];
		DWORD line;
	} ALLOC_INFO;
	typedef std::list<ALLOC_INFO*> AllocList;
	extern AllocList *allocList;
	extern BOOL m_bStartDebug;
	extern BOOL m_bTrackAlloc;
	inline void __cdecl AddTrack(DWORD addr, DWORD asize, const char *fname, DWORD lnum)
	{
		if(m_bStartDebug){
			if(m_bTrackAlloc)
				printf("FILE:<%s> Line:<%d> AllocMemery Size:<%d>\n",fname,lnum,asize);
			ALLOC_INFO *info;
			
			if(!allocList){
				allocList = ::new(AllocList);
			}
			info = ::new(ALLOC_INFO);
			info->address = addr;
			strncpy(info->file, fname, MAX_PATH);
			info->line = lnum;
			info->size = asize;
			allocList->insert(allocList->begin(), info);
		}
		
	};

	inline BOOL __cdecl RemoveTrack(DWORD addr)
	{
		BOOL bret=FALSE;
		if(m_bStartDebug){
			AllocList::iterator i;

			if(!allocList || allocList->size()<1)
			return bret;
			for(i = allocList->begin(); i != allocList->end(); i++)
			{
				if((*i)->address == addr)
				{
					allocList->remove((*i));
					bret=TRUE;
					break;
				}
			}
		}
		return bret;
	};
	inline void  __cdecl DumpUnfreed(){
		AllocList::iterator i;
		DWORD totalSize = 0;
		char buf[1024];
		if(!allocList)
			return;
		sprintf(buf, "---------------开始调试内存[By 罗智勇]---------------\n");
		printf(buf);
		DEBUG_STRING(buf);
		for(i = allocList->begin(); i != allocList->end(); i++) 
		{
			sprintf(buf, "文件: %-50s: 行: %d, 分配了%d字节未释放[<内存地址: %08X>] \n",
			(*i)->file, (*i)->line, (*i)->size, (*i)->address);
			printf(buf);
			DEBUG_STRING(buf);
			totalSize += (*i)->size;
		}
		sprintf(buf, "---------------未释放的内存总计: %d 字节---------------\n", totalSize);
		printf(buf);
		DEBUG_STRING(buf);
		::delete allocList;
		allocList=NULL;
		
	};

	inline void * __cdecl operator new(size_t size,const char *file, int line)throw(){
		void *ptr =NULL;
		try{
			ptr =(void *)malloc(size);
			AddTrack((DWORD)ptr, size, file, line);
		}catch(...){
			printf("Error--allocmemery\n");
			try{
				if(ptr){
					delete(ptr);
				}
			}catch(...){}
			ptr=NULL;
		}
		return ptr;
	};
	inline void * __cdecl operator new[](size_t size,const char *file, int line)throw(){
		return operator new(size,file, line);
	}
	inline void __cdecl operator delete(void *p, const char* lpszFileName, int nLine){
		operator delete(p);
	}
	inline void __cdecl operator delete(void *p)
	{
		RemoveTrack((DWORD)p);
		free(p);
	};
	inline void __cdecl operator delete[](void *p)
	{
		operator delete(p);
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
#define _START_(track) \
	m_bStartDebug=TRUE;\
	m_bTrackAlloc=track;
#define _END_  {DumpUnfreed();m_bStartDebug=FALSE;}
#define EXCLUDE_ADDRESS(addr) RemoveTrack((DWORD)(addr))
#else
#define _START_(x)
#define _END_
#define EXCLUDE_ADDRESS(addr)
#endif
#endif