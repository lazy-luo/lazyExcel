// ScriptEngine.cpp : Defines the entry point for the DLL application.
//
#include "src/interface.h"

#ifdef _DEBUG
	#include "src/mem_debug/lzy_mem_debug_define.h"
#endif
#include "src/script/script_rule.h"
#include "src/script_engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#ifndef LIB_SUPPORT_C_EX
#include "src/demo/demo_fun_macro.cpp"
#endif
//用户测试类
static CLMapBase<INT,tag_program*>	g_prog_map;
void* alloc_mem(size_t sz);
void free_mem(void* p);
void* add_list_item(void* hdr,const char* pitem);
void* add_list(void* hdr,void* psublist);
int get_list_size(void* hdr);
tag_memory_mgrl g_mgrl={alloc_mem,free_mem,add_list_item,add_list,get_list_size};

BOOL is_handle_exists(INT handle){
	return (handle && g_prog_map.GetValue(handle));
}
INT get_script_handle_a(const char* script,char*& error){
	tag_program* ret_v=NULL;
	INT handle=0;
#ifdef SCRIPTENGINE_EXPORTS
	_START_(FALSE)
#endif
	{
		string s_error="";
		script_rule rule;
		script_engine scr(NULL);
		ret_v=scr.get_program(script,s_error);
		if(!ret_v){
			error=new char[s_error.size()+1];
			strcpy(error,s_error.c_str());
		}else{
			handle=*((int*)ret_v);
			g_prog_map.SetAt(handle,ret_v);
		}
	}
#ifdef SCRIPTENGINE_EXPORTS
	_END_
#endif
	return (ret_v?*((int*)ret_v):0);
}
#ifdef SCRIPTENGINE_EXPORTS
extern "C"  __declspec(dllexport) 
#endif
void free_script_handle(INT handle){
	if(handle){
		tag_program** ret_v;
		ret_v=g_prog_map.GetValue(handle);
		if(ret_v && *ret_v){
			delete (*ret_v);
			g_prog_map.RemoveKey(handle);
		}
	}
}
void* alloc_mem(size_t sz){
	return new char[sz];
}
void free_mem(void* p){
	if(p)delete p;
}
void* add_list_item(void* hdr,const char* pitem){
	vector<tag_result_value>* pret=(vector<tag_result_value>*)hdr;
	tag_result_value var;
	if(pitem){
		var.set_string(string(pitem));
		if(pret==NULL)pret=new vector<tag_result_value>();
		pret->push_back(var);
	}
	return pret;
}
void* add_list(void* hdr,void* psublist){
	vector<tag_result_value>* pret=(vector<tag_result_value>*)hdr;
	tag_result_value var;
	if(psublist){
		var.set_list((vector<tag_result_value>*)psublist,TRUE);
		if(pret==NULL)pret=new vector<tag_result_value>();
		pret->push_back(var);
	}
	return pret;
}
int get_list_size(void* hdr){
	return (hdr?((vector<tag_result_value>*)hdr)->size():0);
}
#ifdef SCRIPTENGINE_EXPORTS
extern "C"  __declspec(dllexport) 
#endif
#ifdef LIB_SUPPORT_VB
INT run_script_handle(INT handle,double& ret_dbl,BSTR* ret_str
				,pcall_function pcall,pget_macro_define pmacro){
	if(!is_handle_exists(handle)){
		*ret_str=::SysAllocString((OLECHAR*)"无效的脚本句柄");
		return -1;
	}
	INT ret=0;
	script_rule rule;
	demo_fun_macro macro(pcall,pmacro);
	script_engine scr(&macro);
#else
	#ifndef LIB_SUPPORT_C_EX
INT run_script_handle(INT handle,double& ret_dbl,char*& ret_str
				,pcall_function pcall,pget_macro_define pmacro){
	if(!is_handle_exists(handle)){
		ret_str=new char[256];
		sprintf(ret_str,"无效的脚本句柄\0");
		return -1;
	}
	INT ret=0;
	script_rule rule;
	demo_fun_macro macro(pcall,pmacro);
	script_engine scr(&macro);
	#else
INT run_script_handle(INT handle,double& ret_dbl,char*& ret_str
			,IParse_Function_Macro* pcall){
	if(!is_handle_exists(handle)){
		ret_str=new char[256];
		sprintf(ret_str,"无效的脚本句柄\0");
		return -1;
	}
	INT ret=0;
	script_rule rule;
	script_engine scr(pcall);
	#endif
#endif
	string error="",*pstr=NULL;
	tag_computer_result ret_c;
	tag_program** pprog=(tag_program**)g_prog_map.GetValue(handle);
	if(!scr.run_program((tag_program*)(*pprog),ret_c,error)){
#ifdef LIB_SUPPORT_VB
		*ret_str=::SysAllocString((OLECHAR*)error.c_str());
#else
		ret_str=new char[error.size()+1];
		strcpy(ret_str,error.c_str());
#endif
		ret=-1;
	}
	if(ret_c.is_string_type() && (pstr=ret_c.get_string())){
		ret=1;
		char* pret_str=new char[pstr->size()+1];
		strcpy(pret_str,pstr->c_str());
#ifdef LIB_SUPPORT_VB
		*ret_str=::SysAllocString((OLECHAR*)pret_str);
		delete pret_str;
#else
		ret_str=pret_str;
#endif
	}else{
		ret_dbl=ret_c.get_number();
	}
	return ret;
}
//获取脚本句柄
#ifdef SCRIPTENGINE_EXPORTS
extern "C"  __declspec(dllexport) 
#endif
#ifdef LIB_SUPPORT_VB
INT get_script_handle(BSTR script,BSTR* error){
	char* ret_s=NULL;
	INT ret_v=get_script_handle_a((char*)(script),ret_s);
	if(ret_s){
		*error=::SysAllocString((OLECHAR*)ret_s);
		delete ret_s;
	}
	return ret_v;
#else
INT get_script_handle(const char* script,char*& error){
	return get_script_handle_a(script,error);
#endif
}

#ifndef LIB_SUPPORT_C_EX
int runScript_a(char* script
						,double& ret_dbl,char*& ret_str
						,pcall_function pcall,pget_macro_define pmacro)
{
	int ret_v=0;
	_START_(FALSE)
	{
		script_rule rule;
		demo_fun_macro macro(pcall,pmacro);
		script_engine scr(&macro);
#else
int runScript_a(char* script,double& ret_dbl,char*& ret_str,IParse_Function_Macro* pcall)
{
	int ret_v=0;
#ifdef SCRIPTENGINE_EXPORTS
	_START_(FALSE)
#endif
	{
		script_rule rule;
		script_engine scr(pcall);
#endif
		string error="";
		ret_dbl=0;
		tag_computer_result ret;
		if(!scr.run_script(script,ret,error)){
			ret_v=-1;
			ret_str=new char[error.size()+1];
			strcpy(ret_str,error.c_str());
		}else{
			if(ret.is_string_type()){
				ret_v=1;
				ret_str=new char[ret.get_string()->size()+1];
				strcpy(ret_str,ret.get_string()->c_str());
			}else{
				ret_str=NULL;
				ret_dbl=ret.get_number();
			}
		}
	}
#ifdef SCRIPTENGINE_EXPORTS
	EXCLUDE_ADDRESS(ret_str);
	_END_
#endif
	return ret_v;
}
#ifdef WIN32
#ifdef SCRIPTENGINE_EXPORTS
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
#endif
#endif
#ifdef LIB_SUPPORT_VB
extern "C"  __declspec(dllexport) 
int run_script_direction(BSTR script,double& ret_dbl,BSTR* ret_str
				,pcall_function pcall,pget_macro_define pmacro)
{
	int ret_v=0;
	char* ret_s=NULL;
	ret_v=runScript_a((char*)(script),ret_dbl,ret_s,pcall,pmacro);
	if(ret_s){
		*ret_str=::SysAllocString((OLECHAR*)ret_s);
		delete ret_s;
	}
	return ret_v;
}
#else
#ifndef LIB_SUPPORT_C_EX
#ifdef SCRIPTENGINE_EXPORTS
extern "C"  __declspec(dllexport) 
#endif
int run_script_direction(char* script,double& ret_dbl,char*& ret_str
				,pcall_function pcall,pget_macro_define pmacro)
{
	return runScript_a(script,ret_dbl,ret_str,pcall,pmacro);
}
#else
#ifdef SCRIPTENGINE_EXPORTS
extern "C"  __declspec(dllexport) 
#endif
int run_script_direction(char* script,double& ret_dbl,char*& ret_str,IParse_Function_Macro* pcall)
{
	return runScript_a(script,ret_dbl,ret_str,pcall);
}
#endif
#endif