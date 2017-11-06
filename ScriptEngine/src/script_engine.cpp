///////////////////////////////////////////////////////////////////////////////////////
//@module		:	脚本引擎类(实现)
//@author		:	zhiyong.luo
//@create date	:	2006-12-06
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////
#include "alanysis_tokens.h"
#include "script_engine.h"
#include "script/script_rule.h"
script_engine::script_engine(){}
script_engine::~script_engine(){}
tag_program* script_engine::get_program(const string& script,string& error)
{
	tag_program* p_prog=NULL;
#ifdef LZY_COUNT
	computer_count=0;//计算次数
	get_var_count=0;//取变量次数
	run_block_count=0;//运行程序块次数
	run_func_count=0;//函数运行次数
#endif
#ifdef LZY_INVOID_ERROR
	try{
#endif
		script_rule rule;
		alanysis_tokens alan_token(&rule);
		p_prog=alan_token.get_program(script,error);
#ifdef LZY_INVOID_ERROR
	}catch(...){
		if(error==""){
			error="脚本处理过程中出现了无法预料的错误！";
		}
	}
#endif
	return p_prog;
}
BOOL script_engine::run_script(const string &script, tag_computer_result &ret,string& error)
{
	BOOL ret_v=FALSE;
	tag_program* p_prog=get_program(script,error);
	if(p_prog){
		ret_v=run_program(p_prog,ret,error);
	}
	if(p_prog)
		delete p_prog;
	return ret_v;
}
BOOL script_engine::run_program(const tag_program *p_prog, tag_computer_result &ret,string& error)
{
	BOOL ret_v=FALSE;
	tag_exit_type breturn=type_not_exit;
	init_context(p_prog);
	tag_runtime_context ctx;
	ctx.ptr_prog=(tag_program*)p_prog;
	ctx.m_ptr_global=&m_context;
	if(p_prog){
		ret_v=run_block(ctx,&(p_prog->m_block),ret,error,breturn);
	}
	return ret_v;
}
//运行一个程序段
BOOL script_engine::run_block(tag_runtime_context& ctx
							  ,const tag_block *p_block, tag_computer_result &ret
							  ,string& error,tag_exit_type& rt_type)
{
#ifdef LZY_COUNT
	run_block_count++;//计算次数
#endif
	INT nlen=0,i_idx;
	BOOL ret_v=FALSE;
	ASSERT(p_block);
	tag_block* pblock=(tag_block*)p_block;
	tag_block_node* ptr_node=&(pblock->node);
	tag_sentence_if* p_if=NULL;
	tag_sentence_for* p_for=NULL;
	tag_sentence_for_each* p_for_each=NULL;
	tag_sentence_while* p_while=NULL;
	tag_exit_type tp_t=type_not_exit;
	tag_press_seq* pseq;
	ctx.m_ptr_current=pblock;
	tag_result_value *v_tmp_v;
	tag_computer_result c_result;
	while(ptr_node){
		switch(ptr_node->type){
		case type_sentence_press_seq:
			if(ptr_node->type==type_sentence_press_seq){
				if(pseq=ptr_node->p_press){
					while(pseq){
						if(!(computer(&ctx,*(pseq->press),ret,error,NULL))){
							goto to_exit;
							break;
						}
						pseq=pseq->next;
					}
				}
			}
			break;
		case type_sentence_while:
			p_while=ptr_node->p_while;
			ASSERT(p_while);
			if(!(p_while->p_cond)){
				error="运行时错误 [while语句必须存在条件表达式]";
				goto to_exit;
			}
			while(TRUE){
				if(!computer(&ctx,*(p_while->p_cond),ret,error,NULL)){
					goto to_exit;
				}
				ASSERT(ret.is_number_type());
				if(!((INT)ret.get_number())){
					//条件不成立时退出循环
#ifdef PRINT_PRESS
					printf("press[%s]--%f\n",p_while->p_cond->to_string().c_str(),ret.get_number());
#endif
					break;
				}
				//条件成立
				if(p_while->p_block){
					tp_t=type_not_exit;
					ctx.m_ptr_current=p_while->p_block;
					if(!run_block(ctx,p_while->p_block,ret,error,tp_t)){
						goto to_exit;
					}
					if(tp_t!=type_not_exit){
						if(tp_t==type_continue_exit){
							continue;
						}else{
							if(tp_t==type_return_exit)rt_type=tp_t;
							break;
						}
					}
				}
			}
			break;
		case type_sentence_for_each:
			//是for_each语句
			p_for_each=ptr_node->p_for_each;
			ASSERT(p_for_each);
			if(ctx.get_recognise_flag(p_for_each->list_index,c_result) && c_result.get_rel_type()==type_result_list){
				vector<tag_result_value> *s_vector=(vector<tag_result_value>*)c_result.get_refer_list();
				if(s_vector && ctx.get_recognise_flag(p_for_each->var_index,c_result)){
					if(p_for_each->p_index_press){
						if(!computer(&ctx,*(p_for_each->p_index_press),ret,error,NULL) || !ret.is_number_type()){
							goto to_exit;
						}
						i_idx=(INT)ret.get_number();
						if(i_idx<0 || i_idx>s_vector->size()){
							error="数组下标越界!";
							goto to_exit;
						}
						v_tmp_v=&s_vector->at(i_idx);
						if(!v_tmp_v->is_list_type()){
							error="for_each语句只能作用于数组类型!";
							goto to_exit;
						}
						s_vector=(vector<tag_result_value> *)v_tmp_v->get_list();
					}
					for(vector<tag_result_value>::iterator it=s_vector->begin();it!=s_vector->end();it++){
						//执行程序块
						//替换变量
						if(it->is_list_type()){
							c_result.set_refer_list((vector<tag_result_value>*)it->get_list());
						}else c_result.set_refer_string(it->get_string());
						if(p_for_each->p_block){
							tp_t=type_not_exit;
							ctx.m_ptr_current=p_for_each->p_block;
							if(!run_block(ctx,p_for_each->p_block,ret,error,tp_t)){
								goto to_exit;
								break;
							}
							if(tp_t!=type_not_exit){
								if(tp_t==type_continue_exit){
									continue;
								}else{
									if(tp_t==type_return_exit)rt_type=tp_t;
									break;
								}
							}
						}
					}
				}
			}
			break;
		case type_sentence_for:
			//是for语句
			p_for=ptr_node->p_for;
			ASSERT(p_for);
			if(p_for->p_init){
				if(!computer(&ctx,*(p_for->p_init),ret,error,NULL)){
					goto to_exit;
				}
			}
			for(;;){
				if(p_for->p_cond){
					if(!computer(&ctx,*(p_for->p_cond),ret,error,NULL)){
						goto to_exit;
					}
					ASSERT(ret.is_number_type());
					if(!((INT)ret.get_number())){
						//条件不成立时退出循环
						break;
					}
				}
				//执行程序块
				if(p_for->p_block){
					tp_t=type_not_exit;
					ctx.m_ptr_current=p_for->p_block;
					if(!run_block(ctx,p_for->p_block,ret,error,tp_t)){
						goto to_exit;
						break;
					}
					if(tp_t!=type_not_exit){
						if(tp_t==type_continue_exit){
							continue;
						}else{
							if(tp_t==type_return_exit)rt_type=tp_t;
							break;
						}
					}
				}
				if(p_for->p_dosth){
					if(!computer(&ctx,*(p_for->p_dosth),ret,error,NULL)){
						goto to_exit;
						break;
					}
				}
			}
			break;
		case type_sentence_if:
			//是if语句
			p_if=ptr_node->p_if;
			ASSERT(p_if);
			if(p_if->p_cond){
				if(!computer(&ctx,*(p_if->p_cond),ret,error,NULL)){
					goto to_exit;
					break;
				}
				ASSERT(ret.is_number_type());
				if((INT)ret.get_number()){
					//条件成立,运行正常块
					ASSERT(p_if->p_block);
					ctx.m_ptr_current=p_if->p_block;
					if(!run_block(ctx,p_if->p_block,ret,error,rt_type)){
						goto to_exit;
						break;
					}
				}else if(p_if->p_else_block){
					//运行else
					ASSERT(p_if->p_else_block);
					ctx.m_ptr_current=p_if->p_else_block;
					if(!run_block(ctx,p_if->p_else_block,ret,error,rt_type)){
						goto to_exit;
						break;
					}
				}
			}
			break;
		case type_noname_block:
			if(!run_block(ctx,ptr_node->p_block,ret,error,rt_type)){
				goto to_exit;
				break;
			}
			break;
		case type_sentence_break:
			rt_type=type_break_exit;
			break;
		case type_sentence_continue:
			rt_type=type_continue_exit;
			break;
		case type_sentence_return:
			rt_type=type_return_exit;
			if(!(computer(&ctx,*(ptr_node->p_return->ret_press),ret,error,NULL))){
				goto to_exit;
				break;
			}
			break;
		}
		if(rt_type!=type_not_exit)
			break;
		ptr_node=ptr_node->next;
	}
	ret_v=TRUE;
to_exit:
	return ret_v;
}
typedef map<INT,tag_computer_result*>::value_type param_value_type;
BOOL script_engine::run_user_function(tag_runtime_context* pcontext,tag_user_function* pfunc
							   ,tag_func_param_value_chain* param
							   ,tag_computer_result& ret,string& error)
{
#ifdef LZY_COUNT
	run_func_count++;//计算次数
#endif
	BOOL bret=TRUE,bsave_param=FALSE;
	tag_exit_type rt_type=type_not_exit;
	ASSERT(pfunc!=NULL && pcontext!=NULL);
	if(!pfunc->p_node)return TRUE;
	INT index=0;
	CLMapBase<INT,tag_computer_result>	 var_pool;//(提供结果对象)
	map<INT,tag_computer_result*>	 param_pool;
	tag_computer_result* presult=NULL,*temp_v=NULL;
	//备份原始参数
	tag_func_param_value_chain* ptr_pp=param;
	tag_block* pold=pcontext->m_ptr_current;
	pcontext->m_ptr_current=pfunc->p_node;
	if(pfunc->p_node && !pfunc->m_param.is_empty()){
		//确保有参数
		bsave_param=TRUE;
		tag_func_param_define_chain* pchain=&pfunc->m_param;
		while(pchain){
			if(pchain->p_type==type_by_value){
				presult=pcontext->ptr_prog->get_local_var(pchain->index/*param_name*/);
				ASSERT(presult);
				temp_v=var_pool.GetValue(++index,TRUE);
				*temp_v=*presult;
				param_pool.insert(param_value_type(pchain->index,temp_v));
				pchain=pchain->next;
			}
		}
	}
	//拷贝实际参数
	if(bsave_param){
		ptr_pp=param;
		tag_func_param_define_chain* pchain=&pfunc->m_param;
		while(pchain && ptr_pp){
			if(!pcontext->ptr_prog->set_value_param(pchain->index
				,&ptr_pp->param)){
				ASSERT(FALSE);
				bret=FALSE;
				goto to_exit;
			}
			pchain=pchain->next;
			ptr_pp=ptr_pp->next;
		}
	}
	if(!run_block(*pcontext,pfunc->p_node,ret,error,rt_type)){
		ASSERT(FALSE);
		bret=FALSE;
		goto to_exit;
	}
to_exit:
	//恢复原始参数
	pcontext->m_ptr_current=pold;
	if(bsave_param){
		for(map<INT,tag_computer_result*>::iterator it=param_pool.begin();
			it!=param_pool.end();it++){
			if(!pcontext->ptr_prog->set_value_param((INT)it->first
				,(tag_computer_result*)it->second)){
				ASSERT(FALSE);
				bret=FALSE;
				break;
			}
		}
	}
	return bret;
}

void script_engine::init_context(const tag_program *p_prog)
{
	m_context.m_ptr_outer=m_ptrOuter;
}
