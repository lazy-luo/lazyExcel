// LStyle.cpp: implementation of the CLStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LStyle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLStyle::CLStyle():m_clrBK(COLOR_BKGRD),m_iFont(DEFAULT_MAP_INDEX),m_lpData(NULL),m_pValue(NULL),
	m_iBorder(DEFAULT_BORDER_STYLE),m_clrLine(COLOR_CELL_BORDER_LINE),m_nStyle(DEFAULT_CELL_TYPE)
{
	
}

CLStyle::~CLStyle()
{
	if(m_pValue)
		delete[] m_pValue;
}
void CLStyle::CopyStyle(const CLStyle *ptr)
{
	ASSERT(ptr!=NULL);
	m_clrBK=ptr->m_clrBK;
	m_clrLine=ptr->m_clrLine;
	m_lpData=ptr->m_lpData;
	m_iFont=ptr->m_iFont;
	m_iBorder=ptr->m_iBorder;
	m_nStyle=ptr->m_nStyle;
}
BOOL CLStyle::OnSerial(CLSerial& ar)
{
	LONG val;
	if(ar.isLoading()){
		ar>>m_clrBK>>m_clrLine>>m_iBorder>>m_iFont>>m_nStyle>>val;
		m_lpData=(LPVOID)val;
		val=ar.GetValue();
		if(m_pValue){
			delete[] m_pValue;	
		}
		m_pValue=new char[val+1];
		ar>>m_pValue;
		if(val==0){
			delete[] m_pValue;
			m_pValue=NULL;
		}
	}else{
		ar<<m_clrBK<<m_clrLine<<m_iBorder<<m_iFont<<m_nStyle;
		val=(LONG)m_lpData;
		ar<<val<<m_pValue;
	}
	return TRUE;
}
void CLStyle::ClearToDefault()
{
	m_clrBK=COLOR_BKGRD;
	m_iFont=DEFAULT_MAP_INDEX;
	m_lpData=NULL;
	m_iBorder=DEFAULT_BORDER_STYLE;
	m_clrLine=COLOR_CELL_BORDER_LINE;
	m_nStyle=DEFAULT_CELL_TYPE;
}