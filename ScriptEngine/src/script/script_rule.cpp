// script_rule.cpp: implementation of the script_rule class.
//
//////////////////////////////////////////////////////////////////////

#include "script_rule.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

script_rule::script_rule()
{
	
}
//////////////
BOOL script_rule::is_valid_alpha(CHAR ch)
{
	return TRUE;
}
/*根据当前指针判断是否为配对符*/
BOOL script_rule::is_pair_alpha(const CHAR* pch,INT& nmove
								,tag_pair_string*& ppair,BOOL& bisend,INT& id)
{
	BOOL ret=FALSE;
	nmove=0;
	tag_pair_string *ptr=GET_PAIR_STR;
	for(int i=0;i<SIZE_PAIR;i++){
		if((bisend=(*pch==ptr[i].end.at(BEGIN_STRING_ITERATOR))) 
			|| (*pch==ptr[i].begin.at(BEGIN_STRING_ITERATOR))){
			ppair=&ptr[i];
			ret=TRUE;
			id=i;
			break;
		}
	}
	return ret;
}
/*判断是否为无用的空白分隔字符*/
BOOL script_rule::is_skip_alpha(const CHAR* pch,INT& nmove)
{
	CHAR ch;
	INT nlen=0;
	BOOL ret;
	for(ch=*pch,ret=IS_SKIP_CHAR(ch);ch && IS_SKIP_CHAR(ch);ch=*++pch,nmove++);
	if(is_remark_flag(pch,nlen)){
		nmove+=nlen;
		ret=TRUE;
	}
	if(nmove>0)
		nmove--;
	return ret;
}
BOOL script_rule::is_remark_flag(const CHAR* pch,INT& nmove)
{
	BOOL ret=FALSE;
	if(pch){
		ret=(strstr(pch,g_remark_row_string)==pch);
		if(ret){
			nmove=strlen(g_remark_row_string);
			for(pch+=nmove;*pch && *pch!='\n';pch++,nmove++);
		}
	}
	return ret;
}
BOOL script_rule::is_operator_alpha(const CHAR* it
									,INT& nmove,tag_operator_define*& poper){
	BOOL ret=FALSE;
	string strt="";
	INT ipos=0,act_len;
	map<string,tag_operator_define*>::iterator itr;
	strt=string(it,0,MAX_OPERATOR_LENGTH);
	act_len=(strt.length()<MAX_OPERATOR_LENGTH?strt.length():MAX_OPERATOR_LENGTH);
	for(ipos=act_len;ipos>0;ipos--){
		string key(strt,0,ipos);
		if(g_map_oper.end()!=(itr=g_map_oper.find(key))){
			strt=key;
			poper=((tag_operator_define*)(itr->second));//->get_operator(prev_oper,bfirst);
			nmove=strt.length()-1;
			ret=TRUE;
			break;
		}
	}
	return ret;
}

/*是否为操作符*/
/*
BOOL script_rule::is_operator_alpha(const CHAR* pch
									,INT& nmove,tag_operator*& poper,INT& id)
{
	BOOL ret=FALSE;
	tag_operator* oper=GET_OPERATOR;
	int max_len=0,len,index=0;
	nmove=0;
	string strC="";
	char ch=*pch,char_v[32];
	const char *ptr;
	for(int i=0;i<SIZE_OPERATOR;i++){
		len=oper[i].get_oper()->size();
		if(max_len<len){
			index=max_len;
			for(ptr=pch;(ch=*(char*)ptr++) && max_len<len;char_v[max_len++]=ch);
			char_v[max_len]='\0';
		}
		if((char*)char_v==strstr((char*)char_v,oper[i].get_oper()->c_str())){
			//找到了
			poper=&oper[i];
			nmove=len-1;
			id=i;
			ret=TRUE;
			break;
		}
	}
	return ret;
}*/
/*是否为转义符*/
BOOL script_rule::is_shift_alpha(const CHAR* pch,INT& nmove)
{
	nmove=0;
	return *pch=='\\';
}
/*是否为预定义分隔符*/
BOOL script_rule::is_split_alpha(const CHAR* pch,INT& nmove)
{
	nmove=0;
	return *pch==';';
}
/*是否为其他分隔符号*/
BOOL script_rule::is_other_alpha(const CHAR* pch,INT& nmove,string& pstring)
{
	nmove=0;
	return FALSE;
}
/////////////

script_rule::~script_rule()
{

}

_tag_key_word_type script_rule::get_keyword_type(const string &key)
{
	_tag_key_word_type ret=comm_id_type;
	tag_key_word* keyword=GET_KEYWORD_STR;
	for(INT i=0;i<SIZE_KEYWORD;i++){
		if(!comp_string(key.c_str(),keyword[i].key.c_str())){
			ret=keyword[i].type;
			break;
		}
	}
	return ret;
}
