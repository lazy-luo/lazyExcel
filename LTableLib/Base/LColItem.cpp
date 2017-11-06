// LColItem.cpp: implementation of the CLColItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LColItem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLColItem::CLColItem():m_nWidth(DEFAULT_COL_WIDTH)
{

}

CLColItem::~CLColItem()
{

}
BOOL CLColItem::OnSerial(CLSerial& ar)
{
	if(ar.isLoading()){
		ar>>m_nWidth;
	}else{
		ar<<m_nWidth;
	}
	return TRUE;
}