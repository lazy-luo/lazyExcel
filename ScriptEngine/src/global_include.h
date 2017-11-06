///////////////////////////////////////////////////////////////////////////////////////
//@module		:	跨平台支持文件
//@author		:	zhiyong.luo
//@create date	:	2006-11-27
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _LZY_GLOBAL_INCLUDE_H_
#define _LZY_GLOBAL_INCLUDE_H_
#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4786)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#define KEY_CASE_ABLE //是否大小写敏感

#ifndef ASSERT
#ifdef _DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif
#endif
using namespace std;
#define BEGIN_STRING_ITERATOR	0
#define INLINE inline
#define MAX_NUMBER_LEN	128
#define IS_SKIP_CHAR(ch) \
	(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')

#ifdef KEY_CASE_ABLE
#define	comp_string(src,dst)  strcmp(src,dst)
#else
#define	comp_string(src,dst)  stricmp(src,dst)
#endif

#ifndef interface 
#define interface struct
#endif
#ifndef VOID
#define   VOID void
#endif
#ifndef LPVOID
#define   LPVOID void*
#endif
#ifndef LONG
#define LONG long
#endif
#ifndef UINT
typedef unsigned int        UINT;
#endif

#ifndef CHAR
#define CHAR char
#endif
#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef DOUBLE
#define DOUBLE double
#endif
#ifndef INT
typedef int INT ;
#endif
#ifndef SHORT
#define SHORT short
#endif
#ifndef bool
#define bool INT
#endif
#ifndef BOOL
#define BOOL bool
#endif
#ifndef true
#define true				1
#endif
#ifndef false
#define false				0
#endif
#ifndef FALSE
#define FALSE               false
#endif
#ifndef TRUE
#define TRUE                true
#endif
#ifndef NULL
#define NULL 0
#endif
#ifndef ABSTRACT
#define ABSTRACT =0
#endif

#ifndef WINAPI
#define WINAPI __stdcall
#endif

#define  MIN(a,b)		a>b?b:a
#define  MAX(a,b)		a>b?a:b

#define DLONG	__int64
#define MAKEALONG(a, b)      ((LONG)(((DWORD)(a)) | ((DWORD)((DWORD)(b))) << BITLEN(a)))

#define MAKEADLONG(nCol, nRow)      \
	((DLONG)(((DLONG)(nCol)) | ((DLONG)((DLONG)(nRow))) << (8*sizeof(LONG))))

//哈希表参数
#ifndef HASH_BIG_BLOCK_SIZE
#define		HASH_BIG_BLOCK_SIZE		80
#define		HASH_SMALL_BLOCK_SIZE	40
#define		HASH_BIG_ARR_SIZE		3989
#define		HASH_SMALL_ARR_SIZE		97
#endif
#ifndef _START_
#ifdef _DEBUG
#define _DEBUG_MEM
#include "mem_debug/lzy_mem_debug.h"
#else
#define _START_(x)
#define _END_
#define EXCLUDE_ADDRESS(addr)
#endif
#endif

#endif