///////////////////////////////////////////////////////////////////////////////////////////////
//@模块		:	基本数学表达式计算类(定义)
//@作者		:	罗智勇
//@创建时间	:	2005-11-16
///////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCOMPUTER_H__A3C5B024_5E85_4280_B74B_F25833523F1D__INCLUDED_)
#define AFX_LCOMPUTER_H__A3C5B024_5E85_4280_B74B_F25833523F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define BLOCK_SIZE	100

#include "LGlobalParam.h"
template<class T>
class info_item_list
{
public:
	T item;
};

typedef struct mem_block_list
{
	struct mem_block_list* pNext;
}mem_block_list,*pmem_block_list;

#define MEM_HEAD_LEN	sizeof(mem_block_list)

#define DATA_PTR(plist,index) \
	(info_item_list<T>*)((char*)plist+MEM_HEAD_LEN+index*(sizeof(info_item_list<T>)))
#define IS_HEAD(index) (index==-1)

#define IS_TAIL(index) (index==BLOCK_SIZE)

template<class T>
class LStack  
{
private:
	
	pmem_block_list ExtentListSize();
	void FreeMemList(pmem_block_list pList);
	pmem_block_list m_pcurr;
	pmem_block_list m_pmem;;
	bool get_value(T& val,bool bpopup=0);
	long m_esp;
public:
	LStack();
	virtual ~LStack();
	bool value(T& val);/*检索栈顶值,不弹栈*/
	bool pop(T& val);
	bool push(T val);
};
#define NO_LEVEL -1000

#define MAX_LEVEL	0
#define LEVEL_MUL	1
#define LEVEL_DIV	LEVEL_MUL
#define LEVEL_ADD	LEVEL_MUL+1
#define LEVEL_SUB	LEVEL_ADD

#define FLAG_NONE	0
#define FLAG_ADD	1
#define FLAG_SUB	2
#define FLAG_MUL	3
#define FLAG_DIV	4

#define MIN_LEVEL	99

typedef struct oper_flag
{
	int	oper;
	int    level;
	operator=(oper_flag dst){
		oper=dst.oper;
		level=dst.level;
	}
}oper_flag,*poper_flag;
class LComputer  
{
public:
	DOUBLE Calculate(char* pPress,BOOL& b_error);
	LComputer();
	virtual ~LComputer();
private:
	virtual DOUBLE OnFunction(char*pName,char*& pParam,BOOL& b_error) ABSTRACT;
	virtual DOUBLE OnDefinedValue(char*pName,BOOL& b_error) ABSTRACT;
};

#endif // !defined(AFX_LCOMPUTER_H__A3C5B024_5E85_4280_B74B_F25833523F1D__INCLUDED_)
