//////////////////////////////////////////////////////////////////////
//@模块		 ：单元格对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LCellItem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLCellItem::CLCellItem():m_ptrTxt(NULL)
	,m_ptrMemo(NULL),m_nMergeIndex(MERGE_NONE)
{

}

void CLCellItem::SetCell(CLCellItem &cell)
{
	SetText(cell.GetText());
	SetMemo(cell.GetMemo());	
	m_nMergeIndex=cell.m_nMergeIndex;
}

void CLCellItem::SetCell(CLCellItem *ptrCell)
{
	ASSERT(ptrCell!=NULL);
	SetCell(*ptrCell);
}
CLCellItem::~CLCellItem()
{
	if(m_ptrTxt)
		delete[] m_ptrTxt;
	if(m_ptrMemo)
		delete[] m_ptrMemo;
}
LPTSTR CLCellItem::GetText()
{
	return m_ptrTxt;
}

void CLCellItem::SetText(LPTSTR ptr)
{
	if(m_ptrTxt){
		delete[] m_ptrTxt;
		m_ptrTxt=NULL;
	}
	if(ptr && *ptr!='\0'){
		m_ptrTxt=new char[strlen(ptr)+1];
		strcpy(m_ptrTxt,ptr);
	}
}
void CLCellItem::ClearToDefault(BOOL bClrMerge)
{
	if(m_ptrTxt){
		delete[] m_ptrTxt;
		m_ptrTxt=NULL;
	}
	if(m_ptrMemo){
		delete[] m_ptrMemo;
		m_ptrMemo=NULL;
	}
	if(bClrMerge)
		m_nMergeIndex=MERGE_NONE;
	
}
LPTSTR CLCellItem::GetMemo()
{
	return m_ptrMemo;
}
void CLCellItem::SetMemo(LPTSTR ptr)
{
	if(m_ptrMemo){
		delete[] m_ptrMemo;
		m_ptrMemo=NULL;
	}
	if(ptr && *ptr!='\0'){
		m_ptrMemo=new char[strlen(ptr)+1];
		strcpy(m_ptrMemo,ptr);
	}
}
BOOL CLCellItem::OnSerial(CLSerial& ar)
{
	LONG val;
	if(ar.isLoading()){
		ar>>m_nMergeIndex;
		val=ar.GetValue();
		if(val>0){
			if(m_ptrTxt){
				delete[] m_ptrTxt;	
			}
			m_ptrTxt=new char[val+1];
			ar>>m_ptrTxt;
		}else{
			ar>>val;
		}
		val=ar.GetValue();
		if(val){
			if(m_ptrMemo){
				delete[] m_ptrMemo;	
			}
			m_ptrMemo=new char[val+1];
			ar>>m_ptrMemo;
		}else{
			ar>>val;
		}
	}else{
		ar<<m_nMergeIndex<<m_ptrTxt<<m_ptrMemo;
	}
	return TRUE;
}