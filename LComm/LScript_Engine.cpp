// LScript_Engine.cpp: implementation of the LScript_Engine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LScript_Engine.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LScript_Engine::LScript_Engine()
#if defined(_LINK_DYN_TYPE_)
:m_handle_script(0),m_ptrFunc_get_handle(0),
	m_pfun_run_handle(0),m_pfun_free_handle(0),m_ptrFunc(0)
{
	get_plusin_module(SCRIPT_FILE_NAME);
#else
:m_handle_script(0),m_ptrFunc_get_handle((pget_script_handle)get_script_handle),
	m_pfun_run_handle((prun_script_handle)run_script_handle)
	,m_pfun_free_handle((pfree_script_handle)free_script_handle),m_ptrFunc((prun_script_direction)run_script_direction)
{
#endif
}

LScript_Engine::~LScript_Engine()
{
	if(m_handle_script)
		m_pfun_free_handle(m_handle_script);
	m_handle_script=0;
}
BOOL LScript_Engine::calc_script(const string& script
		,tag_computer_result& ret,IParse_Function_Macro* pcall,string& error,BOOL bparse){
	BOOL ret_v=FALSE;
	if(m_ptrFunc){
		DOUBLE dbl=0;
		char* pstr_v=NULL;
		INT ret_i;
		if(bparse || m_handle_script==0){
			if(m_handle_script)
				m_pfun_free_handle(m_handle_script);
			m_handle_script=m_ptrFunc_get_handle((char*)script.c_str(),pstr_v);
			if(!m_handle_script && pstr_v){
				error=pstr_v;
				delete[] pstr_v;
			}
		}
		if(0>(ret_i=m_pfun_run_handle(m_handle_script,dbl,pstr_v,pcall))){
			error=pstr_v;
		}else{
			if(ret_i==0){
#if defined _LINK_DYN_TYPE_
				ret.type=type_result_number;
				ret.dbl_value=dbl;
#else
				ret.set_number(dbl);
#endif
			}else{
#if defined _LINK_DYN_TYPE_
				ret.type=type_result_string;
				ret.str_value=new string(pstr_v);
#else
				ret.set_string(new string(pstr_v));
#endif
			}
			ret_v=TRUE;
		}
	}else{
		error="脚本引擎未能加载，程序将无法处理脚本。";
	}
	return ret_v;
}