#ifndef __LZY_SCRIPT_INCLUDE_H_
#define __LZY_SCRIPT_INCLUDE_H_

#ifndef _LZY_SCRIPT_ENGINE
//typedef tag_param_type ret_value_type;
enum tag_result_type{
	return_no_type,
	type_result_string,
	type_result_number,
	type_result_list,
	type_result_null
};
#endif
typedef struct _tag_result_out{
	tag_result_type type;
	union{
		char* str_value;
		double dbl_value;
		void* list_value;
	};
	int m_buse_malloc;
}tag_result_out;
typedef struct _tag_param_chain_out{
	void* next;
	tag_result_out param;
}tag_param_chain_out;
typedef void* (*palloc_mem)(size_t sz);
typedef void (*pfree_mem)(void* p);
typedef void* (*padd_list_item)(void* hdr,const char* pitem);
typedef void* (*padd_list)(void* hdr,void* psublist);
typedef int (*pget_list_size)(void* hdr);
typedef struct _tag_memory_mgrl{
	palloc_mem new_mem;
	pfree_mem delete_mem;
	padd_list_item add_list_item;
	padd_list add_list;
	pget_list_size get_list_size;
}tag_memory_mgrl;
#ifndef __cplusplus

#endif

typedef int (*pcall_function)(const char* name,const tag_param_chain_out* param
							  ,tag_result_type type,tag_result_out& ret,char*& error,tag_memory_mgrl& pmem,void* pparam);
typedef int (*pget_macro_define)(const char* name,tag_result_out& ret,char*& error,tag_memory_mgrl& pmem,void* pparam);
typedef int (*prun_script_direction)(char* script,double& ret_dbl,char*& ret_str
						  ,pcall_function pcall,pget_macro_define pmacro);
typedef int (*prun_script_handle)(INT handle,double& ret_dbl,char*& ret_str
						  ,pcall_function pcall,pget_macro_define pmacro);
typedef int (*pget_script_handle)(const char* script,char*& error);
typedef int (*pfree_script_handle)(INT handle);
#endif