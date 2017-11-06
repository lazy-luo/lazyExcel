#ifndef __LZY_SCRIPT_INCLUDE_CEX_H_
#define __LZY_SCRIPT_INCLUDE_CEX_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define SCRIPT_FILE_NAME "script_engine.dll"
using namespace std;
#ifndef LPVOID
#define LPVOID void*
#endif
#ifndef BOOL
#define BOOL int
#endif
#ifndef DOUBLE
#define DOUBLE double
#endif
#ifndef ABSTRACT
#define ABSTRACT =0
#endif
#ifndef interface
#define interface struct
#endif
enum tag_result_type{
	return_no_type,
	type_result_string,
	type_result_number
};
typedef struct _tag_computer_result{
	tag_result_type type;
	union{
		string* str_value;
		DOUBLE dbl_value;
		void* list_value;
	};
	int ref_type;
	void* pref_obj;
}tag_computer_result;
typedef struct _tag_func_param_value_chain{
	_tag_func_param_value_chain* next;
	tag_computer_result param;
}tag_func_param_value_chain;
typedef void* (*palloc_mem)(size_t sz);
typedef void (*pfree_mem)(void* p);
typedef void* (*padd_list_item)(void* hdr,const char* pitem);
typedef void* (*padd_list)(void* hdr,void* psublist);
typedef struct _tag_memory_mgrl{
	palloc_mem new_mem;
	pfree_mem delete_mem;
	padd_list_item add_list_item;
	padd_list add_list;
}tag_memory_mgrl;

interface IParse_Function_Macro
{
public:
	virtual BOOL call_function(const string& name,const tag_func_param_value_chain* param
		,tag_result_type type,tag_computer_result& ret,string& error,LPVOID pparam) ABSTRACT;
	virtual BOOL get_macro_define(const string& name,tag_computer_result& ret
		,string& error,LPVOID pparam) ABSTRACT;
};
typedef int (*prun_script_direction)(char* script,double& ret_dbl,char*& ret_str
						  ,IParse_Function_Macro* pcall);
typedef int (*prun_script_handle)(INT handle,double& ret_dbl,char*& ret_str
						  ,IParse_Function_Macro* pcall);
typedef int (*pget_script_handle)(const char* script,char*& error);
typedef int (*pfree_script_handle)(INT handle);
#endif