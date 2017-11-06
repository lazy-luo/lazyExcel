// LRowItem.cpp: implementation of the CLRowItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LRowItem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLRowItem::CLRowItem():m_nHeight(DEFAULT_ROW_HEIGHT)
{

}

CLRowItem::~CLRowItem()
{

}
BOOL CLRowItem::OnSerial(CLSerial& ar)
{
	if(ar.isLoading()){
		ar>>m_nHeight;
	}else{
		ar<<m_nHeight;
	}
	return TRUE;
}