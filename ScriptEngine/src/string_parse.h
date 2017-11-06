///////////////////////////////////////////////////////////////////////////////////////
//@module		:	词法解析类
//@author		:	zhiyong.luo
//@create date	:	2006-11-29
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRING_PARSE_H__BFCFC1EC_BFFA_4ADB_80FC_9DA7D1E32A71__INCLUDED_)
#define AFX_STRING_PARSE_H__BFCFC1EC_BFFA_4ADB_80FC_9DA7D1E32A71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "interface.h"

#define SKIP_SPACE \
	{\
		for(CHAR ch=next();ch \
			&& IS_SKIP_CHAR(ch);ch=next());\
		iterator--;\
	}

#define MOVE(n) \
	iterator+=n;\
	if(iterator<BEGIN_STRING_ITERATOR)\
		iterator=BEGIN_STRING_ITERATOR;

#define CURRENT_POS iterator
#define CURRENT_POS_STRING \
	(const char*)(m_string.c_str()+iterator)
#ifdef _DEBUG
#define PREV_POS_STRING \
	(/*ASSERT(iterator>0),*/(const char*)(m_string.c_str()+iterator-1))
#else
#define PREV_POS_STRING \
	((const char*)(m_string.c_str()+iterator-1))
#endif
#define IS_ADJUST_POSITION \
	(m_move!=0)

#ifdef LZY_USE_HASH
#define NEW_CHAIN \
	var_token_chain.GetValue(++key_index,TRUE)
#define GET_NEXT_CHAIN(p) \
	((p->next=var_token_chain.GetValue(++key_index,TRUE),p->next->prev=p),p->next);\
	
#else
#define NEW_CHAIN \
	new tag_token_chain()
#define GET_NEXT_CHAIN(p) \
	p->get_next()
#endif
class string_parse
{
private:
	IParse_Alpha* m_palpha;
	tag_token_chain* m_ptoken_chain;
#ifdef LZY_USE_HASH
	INT key_index;
	CLMapBase<INT,tag_token_chain>	 var_token_chain;
#endif
	string m_string;
	string m_strname;
	INT	iterator;
	INT m_strlen;
	INT m_line;//文件行<用于错误定位>
	INT m_col;//列
	INT m_move;
public:
	string_parse(IParse_Alpha* p,const string& name,const string& src):m_string(src)
		,iterator(BEGIN_STRING_ITERATOR),m_palpha(p),m_line(0),m_col(0)
#ifdef LZY_USE_HASH
		,key_index(0)
#endif
		,m_strname(name),m_strlen(src.size()),m_move(0),m_ptoken_chain(NULL){
#ifdef _DEBUG
		ASSERT(parse_tokens(m_ptoken_chain));
#else
		parse_tokens(m_ptoken_chain);
#endif
	};
	INLINE tag_token_chain* get_token_chain(){return m_ptoken_chain;}
	virtual ~string_parse(){
#ifndef LZY_USE_HASH
		if(m_ptoken_chain)
			delete m_ptoken_chain;
#endif
	};
private:
	BOOL parse_tokens(tag_token_chain*& token_c);
	INLINE void adjust_pointer(){
		if(m_move!=0){
			MOVE(m_move);
			m_move=0;
		}
	}
	INLINE INT get_pair_string(const CHAR* ptr,CHAR end_ch);
	INLINE BOOL has_next(){adjust_pointer(); return iterator<m_strlen;}
	INLINE CHAR next(){adjust_pointer(); return (has_next()?(m_col++,m_string.at(iterator++)):NULL);}
	INLINE CHAR current_value(){adjust_pointer(); return (has_next()?m_string.at(iterator):NULL);}
};

#endif // !defined(AFX_STRING_PARSE_H__BFCFC1EC_BFFA_4ADB_80FC_9DA7D1E32A71__INCLUDED_)
