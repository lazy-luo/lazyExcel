///////////////////////////////////////////////////////////////////////////////////////
//@module		:	Óï·¨½âÎöÀà
//@author		:	zhiyong.luo
//@create date	:	2006-12-07
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALANYSIS_TOKENS_H__0EB19A32_FC75_4460_9105_62B8CD5F246D__INCLUDED_)
#define AFX_ALANYSIS_TOKENS_H__0EB19A32_FC75_4460_9105_62B8CD5F246D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "interface.h"
class alanysis_tokens  
{
public:
	tag_program* get_program(const string& script,string& error);
	alanysis_tokens(IParse_Alpha* pout):m_ptrOuter(pout){};
	virtual ~alanysis_tokens();
private:
	IParse_Alpha* m_ptrOuter;
private:
	INLINE vector<tag_result_value>* parse_listvar_init(vector<tag_result_value>* parr,tag_token_chain *&pchain,string& error);
	INLINE BOOL get_sentence_for_each(tag_program& prog,tag_block &curr_b, tag_token_chain *&pchain,string& error);
	INLINE BOOL get_sentence_for(tag_program& prog,tag_block &curr_b, tag_token_chain *&pchain,string& error);
	INLINE BOOL get_sentence_while(tag_program& prog,tag_block &curr_b, tag_token_chain *&pchain,string& error);
	INLINE BOOL get_sentence_if(tag_program& prog,tag_block& curr_b,tag_token_chain*& pchain,string& error);
	INLINE BOOL get_press_seq(tag_program& prog,tag_block &curr_b,tag_token_chain*& pchain,string& error,BOOL bseq=TRUE);
	INLINE BOOL is_dot_flag(tag_token *ptoken);
	INLINE BOOL is_split_flag(tag_token *ptoken);
	INLINE BOOL is_declare_key(_tag_key_word_type type){return (type==string_type_def || type==number_type_def);}
	INLINE tag_press* get_press(tag_program& prog,tag_block& curr_b,tag_token_chain *&pchain,const tag_token* token
		,string& error,BOOL& berror,BOOL b_return_when_lease_level=FALSE);
	INLINE tag_user_function* get_user_function(tag_program& prog,tag_block &curr_b,tag_user_function*& pfunc,tag_result_type r_type,tag_token_chain*& pchain,string& error);
	INLINE BOOL is_user_define_function(tag_token_chain* pchain,_tag_key_word_type& type);
	INLINE tag_param* get_param(tag_program& prog,tag_block& curr_b,tag_token_chain *&pchain,string& error);
	INLINE BOOL is_block_split(tag_token *ptoken);
	INLINE BOOL is_begin_block(tag_token* pchain);
	INLINE BOOL is_end_block(tag_token* pchain);
	INLINE BOOL is_begin_shift(tag_token* pchain);
	INLINE BOOL is_end_shift(tag_token* pchain);
	INLINE BOOL is_begin_index(tag_token *ptoken);
	INLINE BOOL is_end_index(tag_token *ptoken);
	INLINE BOOL get_block(tag_program& prog,tag_block &curr_b,tag_token_chain*&pchain,INT& level,string& error);
	INLINE _tag_key_word_type get_keyword_type(const string &key){return m_ptrOuter->get_keyword_type(key);};
	INLINE BOOL parse_var_define(tag_program& prog,tag_block& curr_b,tag_token_chain *& pchain
		,_tag_key_word_type type,string& error);

};
#define IF_ERROR_CLEAR() \
	if(p_if)delete p_if;\
		ptr_pn->p_if=NULL;\
		bret=FALSE
#define IF_ERROR_MSG_EXIT(msg) \
	if(p_if)delete p_if;\
		ptr_pn->p_if=NULL;\
		berror=TRUE;\
		error=msg;\
		return FALSE
		
#endif // !defined(AFX_ALANYSIS_TOKENS_H__0EB19A32_FC75_4460_9105_62B8CD5F246D__INCLUDED_)
