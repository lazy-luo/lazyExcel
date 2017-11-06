// LScript_Engine.h: interface for the LScript_Engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSCRIPT_ENGINE_H__B5A98387_5298_4631_B709_CB2C6DB43CA4__INCLUDED_)
#define AFX_LSCRIPT_ENGINE_H__B5A98387_5298_4631_B709_CB2C6DB43CA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../LComm/LGlobalDefine.h"
#if defined _LINK_DYN_TYPE_
//¶¯Ì¬Á´½Ó
#include "script_include_c++.h"
#else
//¾²Ì¬Á´½Ó
#include "../ScriptEngine/src/interface.h"
#endif
class LScript_Engine  
{
	friend class CLTable;
	friend class lzy_sniffer;
protected:
	LONG m_handle_script;
	prun_script_direction	m_ptrFunc;
	pget_script_handle		m_ptrFunc_get_handle;
	prun_script_handle		m_pfun_run_handle;
	pfree_script_handle		m_pfun_free_handle;
private:
#if defined _LINK_DYN_TYPE_
	BOOL get_plusin_module(string str_file){
		prun_script_direction script_fun=NULL;
#ifdef WIN32
		HMODULE hmod=LoadLibrary(str_file.c_str());
		if(hmod){
			script_fun=(prun_script_direction)GetProcAddress(hmod,"run_script_direction");
		}
#else
		//unix/linux
		void* hmod =NULL;
		try{
			hmod = dlopen(str_file.c_str(), RTLD_LAZY);
			printf("%s\n",str_file.c_str());
			if(hmod){
				m_ptrFunc=(prun_script_direction)dlsym(hmod,"run_script_direction");
				m_ptrFunc_get_handle=(pget_script_handle)dlsym(hmod,"get_script_handle");
				m_pfun_run_handle=(prun_script_handle)dlsym(hmod,"run_script_handle");
				m_pfun_free_handle=(pfree_script_handle)dlsym(hmod,"free_script_handle");
			}
		}catch(...){
			if(hmod){
				dlclose(hmod);
			}
			printf("error oper dll file [%s]!\n",str_file.c_str());
		}

#endif
		return m_ptrFunc && m_ptrFunc_get_handle && m_pfun_run_handle && m_pfun_free_handle;
	}
#endif
	BOOL calc_script(const string& script
		,tag_computer_result& ret,IParse_Function_Macro* pcall,string& error,BOOL bparse=FALSE);
public:
	LScript_Engine();
	virtual ~LScript_Engine();
	
};

#endif // !defined(AFX_LSCRIPT_ENGINE_H__B5A98387_5298_4631_B709_CB2C6DB43CA4__INCLUDED_)
