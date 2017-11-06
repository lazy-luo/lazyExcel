///////////////////////////////////////////////////////////////////////////////////////
//@module		:	虚拟机实现类
//@author		:	zhiyong.luo
//@create date	:	2006-12-07
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LZYVM_H__D164DB0B_FE6C_4085_846F_F70ECD3E1E23__INCLUDED_)
#define AFX_LZYVM_H__D164DB0B_FE6C_4085_846F_F70ECD3E1E23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef unsigned char R_TP_8;
typedef unsigned short R_TP_16;
typedef unsigned  int R_TP_32;
typedef unsigned __int64 R_TP_64;

#define REGISTER_TYPE R_TP_64/*定义虚拟机支持的位数*/

#define ADD(x,y) x+=y
#define SUB(x,y) x-=y
#define MUL(x,y) x*=y
#define DIV(x,y) x/=y
#define CMP(x,y) x==y?0:x>y

class CLZYVM  
{
public:
	CLZYVM();
	virtual ~CLZYVM();

};

#endif // !defined(AFX_LZYVM_H__D164DB0B_FE6C_4085_846F_F70ECD3E1E23__INCLUDED_)
