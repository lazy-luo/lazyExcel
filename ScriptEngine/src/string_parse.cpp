///////////////////////////////////////////////////////////////////////////////////////
//@module		:	词法解析类(实现)
//@author		:	zhiyong.luo
//@create date	:	2006-11-29
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////
#include "string_parse.h"
INT string_parse::get_pair_string(const CHAR* ptr,CHAR end_ch){
	INT ret=0,ic=0;
	for(CHAR ch=*ptr++;ret++,(ch!=0);ch=*ptr++){
		if(ch=='\\')ic++;
		else{
			if(end_ch==ch && !(ic%2))break;
			ic=0;
		}
	}
	return ret;
}
//解析源字符流
BOOL string_parse::parse_tokens(tag_token_chain *&token_c)
{
	BOOL ret=TRUE,bskip=FALSE,boper=FALSE,bisend=FALSE
		,bpair=FALSE,bother=FALSE,bshift=FALSE,bsplit=FALSE,bfirst=TRUE;
	tag_operator_define* poper=NULL;//,*prev_oper=NULL;
	tag_pair_string* ppair=NULL;
	string other_string="",str_tmp="";
	CHAR ch;
	INT nlen=0,index=0;
	const CHAR *ptrcurr,*ptrnext;
	ASSERT(m_palpha!=NULL);
	ASSERT(token_c==NULL);
	token_c=NEW_CHAIN;
	tag_token_chain* ptoken_c=token_c;
	while(ch=next()){
		if(!m_palpha->is_valid_alpha(ch)){
			//出现了非法字符
			ret=FALSE;
#ifndef LZY_USE_HASH
			token_c->clear();
#endif
			break;
		}
		ptrcurr=PREV_POS_STRING;
		if((bskip=m_palpha->is_skip_alpha(ptrcurr,m_move))
			||(bshift=m_palpha->is_shift_alpha(ptrcurr,m_move))
			||(bsplit=m_palpha->is_split_alpha(ptrcurr,m_move))
			||(bpair=m_palpha->is_pair_alpha(ptrcurr,m_move,ppair,bisend,index))
			||(boper=m_palpha->is_operator_alpha(ptrcurr,m_move,poper))
			||(bother=m_palpha->is_other_alpha(ptrcurr,m_move,other_string))){
			/*是否为接受边界*/
			bfirst=TRUE;
			ptrnext=CURRENT_POS_STRING;
			if(bpair){
				bpair=FALSE;
				ASSERT(ppair!=NULL);
				if(ppair->type==string_block_type/*是否为非解析的连续串。如字符串*/){
					ASSERT(ptoken_c->is_empty());
					nlen=get_pair_string(ptrnext,ppair->end.at(BEGIN_STRING_ITERATOR));
					//解析转义附\r\n\t
					ptoken_c->node.append(ptrnext,nlen-1,TRUE);
					ptoken_c->node.type=type_token_string;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
					m_move=nlen;
					//
				}else{
					/*一般配对符号*/
					if(ptoken_c->is_empty()){
						/*当前符号为空*/
						ptoken_c->node.append(bisend?ppair->end:ppair->begin);
						ptoken_c->node.type=type_token_pair;
						ptoken_c->node.index=index;
						ptoken_c=GET_NEXT_CHAIN(ptoken_c);
					}else{
						//保存前一个
						ptoken_c->node.type=type_token_id;
						ptoken_c=GET_NEXT_CHAIN(ptoken_c);
						ptoken_c->node.append(bisend?ppair->end:ppair->begin);
						ptoken_c->node.type=type_token_pair;
						ptoken_c->node.index=index;
						ptoken_c=GET_NEXT_CHAIN(ptoken_c);
					}
				}
			}else if(boper){
				boper=FALSE;
				ASSERT(poper!=NULL);
				if(ptoken_c->is_empty()){
					/*当前符号为空*/
					ptoken_c->node.type=type_token_operator;
					ptoken_c->node.poper=poper;
					//if(poper->get_type()==oper_dot_f)
					ptoken_c->node.value=poper->oper;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
				}else{
					ptoken_c->node.type=type_token_id;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
					ptoken_c->node.poper=poper;
					ptoken_c->node.type=type_token_operator;
					//if(poper->get_type()==oper_dot_f)
					ptoken_c->node.value=poper->oper;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
				}
			}else if(bskip){
				if(!ptoken_c->is_empty()){
					ptoken_c->node.type=type_token_id;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
				}
			}else if(bshift){
				bshift=FALSE;
				//必须是续行符
				if(*(ptrcurr+1)!='\n' && *(ptrcurr+1)!='\r'){
					ASSERT(FALSE);
					ret=FALSE;
					break;
				}else{
					iterator++;
					ptrcurr=CURRENT_POS_STRING;
					m_palpha->is_skip_alpha(ptrcurr,m_move);
				}
			}else if(bsplit){
				bsplit=FALSE;
				if(!ptoken_c->is_empty()){
					ptoken_c->node.type=type_token_id;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
					ptoken_c->node.value+=ch;
					ptoken_c->node.type=type_token_split;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
				}else{
					ptoken_c->node.type=type_token_split;
					ptoken_c->node.value+=ch;
					ptoken_c=GET_NEXT_CHAIN(ptoken_c);
				}
			}else if(bother){
				bother=FALSE;
			}else{
				ASSERT(FALSE);
				ret=FALSE;
				break;
			}
		}else{
			ptoken_c->node.append(ch);
			bfirst=FALSE;
		}
	}
	if(!ptoken_c->is_empty() && ptoken_c->node.type==type_token_undefine){
		ptoken_c->node.type=type_token_id;
	}else{
		ptoken_c->prev->next=NULL;
#ifndef LZY_USE_HASH
		delete ptoken_c;
#endif
	}
	return ret;
}
