///////////////////////////////////////////////////////////////////////////////////////
//@module		:	表达式计算类
//@author		:	zhiyong.luo
//@create date	:	2006-12-04
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRESS_COMPUTER_H__E0D28ABF_6724_4ED8_B2F8_89E93C207803__INCLUDED_)
#define AFX_PRESS_COMPUTER_H__E0D28ABF_6724_4ED8_B2F8_89E93C207803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "interface.h"

#define BLOCK_SIZE 128
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
	(info_item_list<T>*)((CHAR*)plist+MEM_HEAD_LEN+index*(sizeof(info_item_list<T>)))
#define IS_HEAD(index) (index==-1)

#define IS_TAIL(index) (index==BLOCK_SIZE)

typedef void (*pfun)(void* ppv);
template<class T>
class LStack  
{
private:
	INLINE pmem_block_list ExtentListSize();
	INLINE void FreeMemList(pmem_block_list pList);
	INLINE BOOL get_value(T& val,BOOL bpopup=0);
	INLINE info_item_list<T>* get_top();
public:
#ifdef _DEBUG
	void print_stack(pfun pprint);
#endif
	LStack();
	virtual ~LStack();
	INLINE BOOL value(T& val);/*检索栈顶值,不弹栈*/
	INLINE BOOL pop(T& val);
	INLINE VOID push(T val);
	INLINE T* replace_top(T val);
private:
	pmem_block_list m_pcurr;
	pmem_block_list m_pmem;
	LONG m_esp;
};

class press_computer  
{
protected:
	//统计用的全局变量
#ifdef LZY_COUNT
	static INT computer_count;//计算次数
	static INT get_var_count;//取变量次数
	static INT run_block_count;//运行程序块次数
	static INT run_func_count;//函数运行次数
#endif
	IParse_Function_Macro* m_ptrOuter;
public:
	//表达式预处理函数
	static BOOL pre_computer_press(tag_press &press,string& error);
	BOOL computer(tag_runtime_context* pcontext,const tag_press& press,tag_computer_result &ret,string& error,LPVOID pparam);
	press_computer(IParse_Function_Macro* ptrOuter):m_ptrOuter(ptrOuter){};
	press_computer():m_ptrOuter(NULL){};
	virtual ~press_computer(){};
private:
#ifdef LZY_COUNT
	INLINE BOOL get_count_var(const string& name,tag_computer_result* &pret);
#endif
	INLINE BOOL computer_node(tag_runtime_context* pcontext,const tag_node &node,tag_computer_result* &pret,string& error,LPVOID pparam);
	virtual BOOL run_user_function(tag_runtime_context* pcontext,tag_user_function* pfunc,tag_func_param_value_chain* param,tag_computer_result& ret,string& error){return FALSE;}
};

#endif // !defined(AFX_PRESS_COMPUTER_H__E0D28ABF_6724_4ED8_B2F8_89E93C207803__INCLUDED_)
