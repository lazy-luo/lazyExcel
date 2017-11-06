//////////////////////////////////////////////////////////////////////
//@模块		 ：表格列对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCOLITEM_H__0D2C1E49_16C4_4164_8D77_6DB6D8EACBD1__INCLUDED_)
#define AFX_LCOLITEM_H__0D2C1E49_16C4_4164_8D77_6DB6D8EACBD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Public/LPublicDef.h"
#define GETINDEX	INDEX Index;\
	Index.Index=index


class TABLE_EXPORT_CLASS CLColItem  
{
public:
	CLColItem();
	virtual ~CLColItem();
	BOOL OnSerial(CLSerial& ar);
	__inline LONG GetWidth(){return m_nWidth;}
	__inline void SetWidth(LONG val){
		if(val<0)val=0;
		m_nWidth=val;
	}
private:
	LONG m_nWidth;
};
class CLColsArr:public CLMapBase<INDEX,CLColItem>
{
public:
	__inline CLColItem* NewCol(LONG index){
		return (CLColItem*)GetCol(index,TRUE);
	}
	__inline CLColItem* GetCol(LONG index,BOOL bForceNew=FALSE){
		GETINDEX;
		return (CLColItem*)GetValue(Index,bForceNew);
	}
	__inline void DeleteCol(LONG index){
		GETINDEX;
		DeleteValue(Index);
	}
};
#endif // !defined(AFX_LCOLITEM_H__0D2C1E49_16C4_4164_8D77_6DB6D8EACBD1__INCLUDED_)
