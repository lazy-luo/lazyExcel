///////////////////////////////////////////////////////////////////////////////////////
//@module		:	脚本引擎类
//@author		:	zhiyong.luo
//@create date	:	2006-12-07
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPT_ENGINE_H__2C6E480E_810A_40E9_AC9A_6F2BB2A1F34B__INCLUDED_)
#define AFX_SCRIPT_ENGINE_H__2C6E480E_810A_40E9_AC9A_6F2BB2A1F34B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "press_computer.h"

class script_engine : public press_computer
{
private:
	tag_global_context m_context;
private:
	virtual BOOL run_user_function(tag_runtime_context* pcontext,tag_user_function* pfunc,tag_func_param_value_chain* param
		,tag_computer_result& ret,string& error);
public:
	BOOL run_program(const tag_program* p_prog,tag_computer_result &ret,string& error);
	//得到预处理后的程序
	tag_program* get_program(const string& script,string& error);
	BOOL run_script(const string& script,tag_computer_result& ret,string& error);
	script_engine();
	script_engine(IParse_Function_Macro* ptrOuter):press_computer(ptrOuter){
		m_context.m_ptr_outer=ptrOuter;
	}
	virtual ~script_engine();
private:
	INLINE void init_context(const tag_program* p_prog);
	INLINE BOOL run_block(tag_runtime_context& ctx,const tag_block* p_block
		,tag_computer_result & ret,string& error,tag_exit_type& rt_type);
	
};

#endif // !defined(AFX_SCRIPT_ENGINE_H__2C6E480E_810A_40E9_AC9A_6F2BB2A1F34B__INCLUDED_)
