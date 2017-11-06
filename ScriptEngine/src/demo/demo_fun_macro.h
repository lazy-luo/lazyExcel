// demo_fun_macro.h: interface for the demo_fun_macro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_FUN_MACRO_H__6E60F981_CDAA_4B7B_AD52_64DEBC0CFED5__INCLUDED_)
#define AFX_DEMO_FUN_MACRO_H__6E60F981_CDAA_4B7B_AD52_64DEBC0CFED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../interface.h"
class demo_fun_macro : public IParse_Function_Macro  
{
private:
	pcall_function m_pcall;
	pget_macro_define m_pmacro;
public:
	demo_fun_macro();
	demo_fun_macro(pcall_function pcall,pget_macro_define pmacro)
		:m_pcall(pcall),m_pmacro(pmacro){};
	virtual ~demo_fun_macro();
	virtual BOOL call_function(const string& name,const tag_func_param_value_chain* param
		,tag_result_type type,tag_computer_result& ret,string& error,LPVOID pparam);
	virtual BOOL get_macro_define(const string& name,tag_computer_result& ret
		,string& error,LPVOID pparam);
};

#endif // !defined(AFX_DEMO_FUN_MACRO_H__6E60F981_CDAA_4B7B_AD52_64DEBC0CFED5__INCLUDED_)
