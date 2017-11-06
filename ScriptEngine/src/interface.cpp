#include "interface.h"
struct _tag_oper_pair{
	_tag_oper_pair(_tag_operator_type id,const string& str):idx(id),oper(str){}
	_tag_operator_type idx;
	string oper;
};
static _tag_oper_pair static_oper[]={
	_tag_oper_pair(oper_type_undefine,"error"),
	_tag_oper_pair(oper_shift_begin, "("),
	_tag_oper_pair(oper_shift_end,   ")"),
	_tag_oper_pair(oper_add_left,  "+"),
	_tag_oper_pair(oper_sub_left,  "-"),
	_tag_oper_pair(oper_add,  "+"),
	_tag_oper_pair(oper_sub,  "-"),
	_tag_oper_pair(oper_shrl, "<<"),
	_tag_oper_pair(oper_shrr, ">>"),
	_tag_oper_pair(oper_mul,  "*"),
	_tag_oper_pair(oper_mod,  "%"),
	_tag_oper_pair(oper_div,  "/"),
	_tag_oper_pair(oper_ae,   ">="),
	_tag_oper_pair(oper_a,		">"),
	_tag_oper_pair(oper_e,		"=="),
	_tag_oper_pair(oper_ne,	"!="),
	_tag_oper_pair(oper_le,	"<="),
	_tag_oper_pair(oper_l,		"<"),
	_tag_oper_pair(oper_pttv,	"="),
	_tag_oper_pair(oper_dot_f, ","),
	_tag_oper_pair(oper_and,	"&"),
	_tag_oper_pair(oper_bool_and,"&&"),
	_tag_oper_pair(oper_or,"|"),
	_tag_oper_pair(oper_bool_or,	"||"),
	_tag_oper_pair(oper_bool_not, "!"),
	_tag_oper_pair(oper_not, "~"),
	_tag_oper_pair(oper_xor,"^"),
	_tag_oper_pair(oper_self_add_left,"++"),
	_tag_oper_pair(oper_self_sub_left,"--"),
	_tag_oper_pair(oper_self_add_right,"++"),
	_tag_oper_pair(oper_self_sub_right,"--"),
	_tag_oper_pair(oper_add_pttv,"+="),
	_tag_oper_pair(oper_sub_pttv,"-="),
	_tag_oper_pair(oper_mul_pttv,"*="),
	_tag_oper_pair(oper_div_pttv,"/="),
	_tag_oper_pair(oper_or_pttv,"|="),
	_tag_oper_pair(oper_and_pttv,"&="),
	_tag_oper_pair(oper_xor_pttv,"^="),
	_tag_oper_pair(oper_shrl_pttv,"<<="),
	_tag_oper_pair(oper_shrr_pttv,">>="),
	_tag_oper_pair(oper_mod_pttv,"%=")
};
tag_sentence_if::~tag_sentence_if(){
	if(p_cond)
		delete p_cond;
	if(p_block)
		delete p_block;
	if(p_else_block)
		delete p_else_block;
}
tag_user_function::~tag_user_function(){
	if(p_node)
		delete p_node;
}
tag_sentence_for_each::~tag_sentence_for_each(){
	if(p_index_press)delete p_index_press;
	if(p_block)
		delete p_block;
}
tag_block_node::~tag_block_node(){
	switch(type){
	case type_sentence_if:
		if(p_if)
			delete p_if;
		break;
	case type_sentence_for:
		if(p_for)
			delete p_for;
		break;
	case type_sentence_return:
		if(p_return)
			delete p_return;
		break;
	case type_sentence_while:
		if(p_while)
			delete p_while;
		break;
	case type_sentence_press_seq:
		if(p_press)
			delete p_press;
		break;
	case type_noname_block:
		if(p_block)
			delete p_block;
		break;
	case type_sentence_break:
		break;
	case type_sentence_continue:
		break;
	case type_sentence_for_each:
		if(p_for_each)
			delete p_for_each;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	if(next)
		delete next;
}
tag_sentence_for::~tag_sentence_for(){
	if(p_init)
		delete p_init;
	if(p_cond)
		delete p_cond;
	if(p_dosth)
		delete p_dosth;
	if(p_block)
		delete p_block;
}
tag_sentence_while::~tag_sentence_while(){
	if(p_cond)
		delete p_cond;
	if(p_block)
		delete p_block;
}
#if (defined PRINT_PRESS)
string tag_press::to_string() const{
	string ret="";
	switch(node.type){
	case type_function://º¯Êý
		ret+=node.ptr_func->name+"(";
		{
			tag_param* ptr=node.ptr_func->param;
			while(ptr){
				ret+=ptr->press->to_string();
				ptr=ptr->next;
			}
		}
		ret+=")";
		break;
	case type_string://×Ö·û´®
		ret+="\"";
		if(node.str_value)
			ret+=(*node.str_value);
		ret+="\"";
		break;
	case type_normal://Ò»°ã·ûºÅ
		{
			char ptmp[64];
			sprintf(ptmp,"var<%d>\0",node.var_index);
			ret+=ptmp;
		}
		break;
	case type_number://Êý×ÖÊý×Ö
		{
			char ptmp[64];
			sprintf(ptmp,"%f\0",node.dbl_value);
			ret+=ptmp;
		}
		break;
	case type_operator:
		{
			ret+=static_oper[(INT)node.p_oper->get_type()].oper;
		}
		break;
	}
	return ret;
}
#endif