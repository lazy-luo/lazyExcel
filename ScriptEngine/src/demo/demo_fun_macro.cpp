// demo_fun_macro.cpp: implementation of the demo_fun_macro class.
//
//////////////////////////////////////////////////////////////////////

#include "demo_fun_macro.h"
extern tag_memory_mgrl g_mgrl;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

demo_fun_macro::demo_fun_macro():m_pcall(NULL),m_pmacro(NULL){}
demo_fun_macro::~demo_fun_macro()
{
	m_pcall=NULL;
	m_pmacro=NULL;
}
BOOL demo_fun_macro::call_function(const string& name,const tag_func_param_value_chain* param
								   ,tag_result_type type,tag_computer_result& ret,string& error,LPVOID pparam)
{
	BOOL ret_v=FALSE;
	if(m_pcall){
		tag_param_chain_out* out_p=new tag_param_chain_out();
		tag_param_chain_out* const pp_out=out_p;
		memset(out_p,0x00,sizeof(tag_param_chain_out));
		if(param){
			copy_result_param_chain_in_2_out(*param,*out_p);
		}
		tag_result_out ret_out;
		char* perror=NULL,*p=(char*)name.c_str();
		memset(&ret_out,0x00,sizeof(tag_result_out));
		copy_result_in_2_out(ret,ret_out);
		if(m_pcall(p,(param?pp_out:NULL),type,ret_out,perror,g_mgrl,pparam)){
			ret_v=TRUE;
			copy_result_out_2_in(ret_out,ret);
		}else{
			if(perror){
				error=perror;
			}
		}
		if(perror){
			try{
				delete perror;
			}catch(...){
				try{
					free(perror);
				}catch(...){}
			}
		}
		clear_param_chain_out(out_p);
		clear_result_out(&ret_out);
	}
	return ret_v;
}
BOOL demo_fun_macro::get_macro_define(const string& name,tag_computer_result& ret
									  ,string& error,LPVOID pparam)
{
	BOOL ret_v=FALSE;
	if(m_pmacro){
		tag_result_out ret_out;
		char* perror=NULL;
		memset(&ret_out,0x00,sizeof(tag_result_out));
		copy_result_in_2_out(ret,ret_out);
		if(m_pmacro(name.c_str(),ret_out,perror,g_mgrl,pparam)){
			ret_v=TRUE;
			copy_result_out_2_in(ret_out,ret);
		}else{
			if(perror){
				error=perror;
			}
		}
		if(perror){
			try{
				delete perror;
			}catch(...){
				try{
					free(perror);
				}catch(...){}
			}
		}
		clear_result_out(&ret_out);
	}
	return ret_v;
}
