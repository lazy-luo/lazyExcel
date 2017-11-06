// script_rule.h: interface for the script_rule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPT_RULE_H__B144C994_A749_4AC3_914D_C57DF3F94081__INCLUDED_)
#define AFX_SCRIPT_RULE_H__B144C994_A749_4AC3_914D_C57DF3F94081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../interface.h"

static char* g_ptr_split=";";
static char* g_shift_char="\\";
static tag_pair_string g_ptr_pair[]={//必须为单字符分隔
	tag_pair_string(string_block_type,"\"","\"")
	,tag_pair_string(program_block_type,"{","}")
};
//
static char* g_remark_row_string="//";

static tag_key_word g_keyword[]={
	tag_key_word(condition_if,"if")
	,tag_key_word(condition_else,"else")
	,tag_key_word(while_loop,"while")
	,tag_key_word(for_loop,"for")
	,tag_key_word(return_oper,"return")
	,tag_key_word(break_loop,"break")
	,tag_key_word(continue_loop,"continue")
	,tag_key_word(switch_case,"switch")
	,tag_key_word(case_case,"case")
	,tag_key_word(string_type_def,"string")
	,tag_key_word(number_type_def,"number")
	,tag_key_word(list_type_def,"list")
	,tag_key_word(for_each_loop,"for_each")
	,tag_key_word(null_type_def,"null")
};
enum tag_static_oper_index{
	idx_oper_shrl_pttv=0
	,idx_oper_shrr_pttv
	,idx_oper_ae
	,idx_oper_le
	,idx_oper_self_add_left
	,idx_oper_self_sub_left
	,idx_oper_self_add_right
	,idx_oper_self_sub_right
	,idx_oper_shrl
	,idx_oper_shrr
	,idx_oper_e
	,idx_oper_ne
	,idx_oper_bool_and
	,idx_oper_bool_or
	,idx_oper_add_pttv
	,idx_oper_sub_pttv
	,idx_oper_div_pttv
	,idx_oper_mod_pttv
	,idx_oper_mul_pttv
	,idx_oper_or_pttv
	,idx_oper_and_pttv
	,idx_oper_xor_pttv
	,idx_oper_add_left
	,idx_oper_sub_left
	,idx_oper_add
	,idx_oper_sub
	,idx_oper_mul
	,idx_oper_mod
	,idx_oper_div
	,idx_oper_pttv
	,idx_oper_shift_begin
	,idx_oper_shift_end
	,idx_list_index_begin
	,idx_list_index_end
	,idx_oper_a
	,idx_oper_l
	,idx_oper_and
	,idx_oper_or
	,idx_oper_not
	,idx_oper_bool_not
	,idx_oper_xor
	,idx_oper_dot_f
};
static g_idx_list_index_end;
static tag_operator g_operator[]={
	tag_operator(oper_shrl_pttv,LEVEL_SHRL_PTTV)//,"<<="
	,tag_operator(oper_shrr_pttv,LEVEL_SHRR_PTTV)//,">>="
	,tag_operator(oper_ae,LEVEL_AE)//,">="
	,tag_operator(oper_le,LEVEL_LE)//,"<="
	,tag_operator(oper_self_add_left,LEVEL_SELF_ADD_LEFT,OPER_SINGLE_LEFT)//,"++"
	,tag_operator(oper_self_sub_left,LEVEL_SELF_SUB_LEFT,OPER_SINGLE_LEFT)//,"--"
	,tag_operator(oper_self_add_right,LEVEL_SELF_ADD_RIGHT,OPER_SINGLE_RIGHT)//,"++"
	,tag_operator(oper_self_sub_right,LEVEL_SELF_SUB_RIGHT,OPER_SINGLE_RIGHT)//,"--"
	,tag_operator(oper_shrl,LEVEL_SHR_LEFT)//,"<<"
	,tag_operator(oper_shrr,LEVEL_SHR_RIGHT)//,">>"
	,tag_operator(oper_e,LEVEL_E)//,"=="
	,tag_operator(oper_ne,LEVEL_NE)//,"!="
	,tag_operator(oper_bool_and,LEVEL_BOOL_AND)//,"&&"
	,tag_operator(oper_bool_or,LEVEL_BOOL_OR)//,"||"
	,tag_operator(oper_add_pttv,LEVEL_ADD_PTTV)//,"+="
	,tag_operator(oper_sub_pttv,LEVEL_SUB_PTTV)//,"-="
	,tag_operator(oper_div_pttv,LEVEL_DIV_PTTV)//,"/="
	,tag_operator(oper_mod_pttv,LEVEL_MOD_PTTV)//,"%="
	,tag_operator(oper_mul_pttv,LEVEL_MUL_PTTV)//,"*="
	,tag_operator(oper_or_pttv,LEVEL_OR_PTTV)//,"|="
	,tag_operator(oper_and_pttv,LEVEL_AND_PTTV)//,"&="
	,tag_operator(oper_xor_pttv,LEVEL_XOR_PTTV)//,"^="
	,tag_operator(oper_add_left,LEVEL_ADD_LEFT,OPER_SINGLE_LEFT)//,"+"
	,tag_operator(oper_sub_left,LEVEL_SUB_LEFT,OPER_SINGLE_LEFT)//,"-"
	,tag_operator(oper_add,LEVEL_ADD)//,"+"
	,tag_operator(oper_sub,LEVEL_SUB)//,"-"
	,tag_operator(oper_mul,LEVEL_MUL)//,"*"
	,tag_operator(oper_mod,LEVEL_MOD)//,"%"
	,tag_operator(oper_div,LEVEL_DIV)//,"/"
	,tag_operator(oper_pttv,LEVEL_PTTV)//,"="
	,tag_operator(oper_shift_begin,LEVEL_SFT_BG,OPER_NORMAL,FALSE)//,"("
	,tag_operator(oper_shift_end,LEVEL_SFT_ED,OPER_NORMAL,FALSE)//,")"
	,tag_operator(oper_list_index_begin,LEVEL_SFT_IDX,OPER_NORMAL)//,"["
	,tag_operator(oper_list_index_end,LEVEL_SFT_ED_IDX,OPER_NORMAL,FALSE)//,"]"------------------------
	,tag_operator(oper_a,LEVEL_A)//,">"
	,tag_operator(oper_l,LEVEL_L)//,"<"
	,tag_operator(oper_and,LEVEL_AND)//,"&"
	,tag_operator(oper_or,LEVEL_OR)//,"|"
	,tag_operator(oper_not,LEVEL_NOT,OPER_SINGLE_LEFT)//,"~"
	,tag_operator(oper_bool_not,LEVEL_BOOL_NOT,OPER_SINGLE_LEFT)//,"!"
	,tag_operator(oper_xor,LEVEL_XOR)//,"^"
	,tag_operator(oper_dot_f,LEVEL_DOT_FLAG,OPER_NORMAL,FALSE)//,","
};
static INT i=0;
static map<string,tag_operator_define*> g_map_oper;
static tag_operator_define g_oper[]={
	tag_operator_define("<<=",g_map_oper,&g_operator[idx_oper_shrl_pttv],i++)
	,tag_operator_define(">>=",g_map_oper,&g_operator[idx_oper_shrr_pttv],i++)
	,tag_operator_define(">=",g_map_oper,&g_operator[idx_oper_ae],i++)
	,tag_operator_define("<=",g_map_oper,&g_operator[idx_oper_le],i++)
	,tag_operator_define("++",g_map_oper,NULL,i++,OPER_SINGLE_ALL,TRUE,&g_operator[idx_oper_self_add_left],&g_operator[idx_oper_self_add_right])
	,tag_operator_define("--",g_map_oper,NULL,i++,OPER_SINGLE_ALL,TRUE,&g_operator[idx_oper_self_sub_left],&g_operator[idx_oper_self_sub_right])
	,tag_operator_define("<<",g_map_oper,&g_operator[idx_oper_shrl],i++)
	,tag_operator_define(">>",g_map_oper,&g_operator[idx_oper_shrr],i++)
	,tag_operator_define("==",g_map_oper,&g_operator[idx_oper_e],i++)
	,tag_operator_define("!=",g_map_oper,&g_operator[idx_oper_ne],i++)
	,tag_operator_define("&&",g_map_oper,&g_operator[idx_oper_bool_and],i++)
	,tag_operator_define("||",g_map_oper,&g_operator[idx_oper_bool_or],i++)
	,tag_operator_define("+=",g_map_oper,&g_operator[idx_oper_add_pttv],i++)
	,tag_operator_define("-=",g_map_oper,&g_operator[idx_oper_sub_pttv],i++)
	,tag_operator_define("/=",g_map_oper,&g_operator[idx_oper_div_pttv],i++)
	,tag_operator_define("%=",g_map_oper,&g_operator[idx_oper_mod_pttv],i++)
	,tag_operator_define("*=",g_map_oper,&g_operator[idx_oper_mul_pttv],i++)
	,tag_operator_define("|=",g_map_oper,&g_operator[idx_oper_or_pttv],i++)
	,tag_operator_define("&=",g_map_oper,&g_operator[idx_oper_and_pttv],i++)
	,tag_operator_define("^=",g_map_oper,&g_operator[idx_oper_xor_pttv],i++)
	,tag_operator_define("+",g_map_oper,&g_operator[idx_oper_add],i++,OPER_NORMAL | OPER_SINGLE_LEFT,TRUE,&g_operator[idx_oper_add_left],NULL)
	,tag_operator_define("-",g_map_oper,&g_operator[idx_oper_sub],i++,OPER_NORMAL | OPER_SINGLE_LEFT,TRUE,&g_operator[idx_oper_sub_left],NULL)
	,tag_operator_define("*",g_map_oper,&g_operator[idx_oper_mul],i++)
	,tag_operator_define("%",g_map_oper,&g_operator[idx_oper_mod],i++)
	,tag_operator_define("/",g_map_oper,&g_operator[idx_oper_div],i++)
	,tag_operator_define("=",g_map_oper,&g_operator[idx_oper_pttv],i++)
	,tag_operator_define("(",g_map_oper,&g_operator[idx_oper_shift_begin],i++,OPER_NORMAL,FALSE)
	,tag_operator_define(")",g_map_oper,&g_operator[idx_oper_shift_end],i++,OPER_NORMAL,FALSE)
	,tag_operator_define("[",g_map_oper,&g_operator[idx_list_index_begin],i++,OPER_NORMAL)
	,tag_operator_define("]",g_map_oper,&g_operator[idx_list_index_end],g_idx_list_index_end=i++,OPER_NORMAL,FALSE)
	,tag_operator_define(">",g_map_oper,&g_operator[idx_oper_a],i++)
	,tag_operator_define("<",g_map_oper,&g_operator[idx_oper_l],i++)
	,tag_operator_define("&",g_map_oper,&g_operator[idx_oper_and],i++)
	,tag_operator_define("|",g_map_oper,&g_operator[idx_oper_or],i++)
	,tag_operator_define("~",g_map_oper,NULL,i++,OPER_SINGLE_LEFT,TRUE,&g_operator[idx_oper_not])
	,tag_operator_define("!",g_map_oper,NULL,i++,OPER_SINGLE_LEFT,TRUE,&g_operator[idx_oper_bool_not])
	,tag_operator_define("^",g_map_oper,&g_operator[idx_oper_xor],i++)
	,tag_operator_define(",",g_map_oper,&g_operator[idx_oper_dot_f],i++,OPER_NORMAL,FALSE)
};
#define SIZE_OPERATOR (sizeof(g_oper)/sizeof(tag_operator_define))
#define SIZE_PAIR (sizeof(g_ptr_pair)/sizeof(tag_pair_string))
#define SIZE_KEYWORD (sizeof(g_keyword)/sizeof(tag_key_word))

//出于性能的考虑，可以更换以下宏定义
#define GET_SPLIT_STR g_ptr_split
#define GET_PAIR_STR g_ptr_pair
#define GET_KEYWORD_STR g_keyword
#define GET_OPERATOR g_oper

#define MAX_OPERATOR_LENGTH 3 //操作符最长长度(改变操作符的时候注意修改)
#define MAX_KEYWORD_LENGTH 8 //关键字最大长度
#define MAX_STRING_PAIR_LENGTH 1
#define MAX_PAIR_LENGTH	1

class script_rule :public IParse_Alpha
{
public:
	virtual _tag_key_word_type get_keyword_type(const string& key);
	script_rule();
	virtual ~script_rule();
	virtual BOOL is_valid_alpha(CHAR ch);/*字符是否是个合法字符*/
	/*根据当前指针判断是否为配对符*/
	virtual BOOL is_pair_alpha(const CHAR* pch,INT& nmove,tag_pair_string*& ppair,BOOL& bisend,INT& id);
	/*判断是否为无用的空白分隔字符*/
	virtual BOOL is_skip_alpha(const CHAR* pch,INT& nmove);
	/*是否为操作符*/
	virtual BOOL is_operator_alpha(const CHAR* it,INT& nmove,tag_operator_define*& poper);
	/*是否为转义符*/
	virtual BOOL is_shift_alpha(const CHAR* pch,INT& nmove);
	/*是否为预定义分隔符*/
	virtual BOOL is_split_alpha(const CHAR* pch,INT& nmove);
	/*是否为其他分隔符号*/
	virtual BOOL is_remark_flag(const CHAR* pch,INT& nmove);
	virtual BOOL is_other_alpha(const CHAR* pch,INT& nmove,string& pstring);
	//virtual tag_operator* get_operator(INT index){return &g_operator[index];}
	virtual tag_pair_string* get_pair(INT index){return &g_ptr_pair[index];};
};

#endif // !defined(AFX_SCRIPT_RULE_H__B144C994_A749_4AC3_914D_C57DF3F94081__INCLUDED_)
