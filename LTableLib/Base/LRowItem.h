// LRowItem.h: interface for the CLRowItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LROWITEM_H__CC5B916A_4643_48EE_969C_8E8619BC555E__INCLUDED_)
#define AFX_LROWITEM_H__CC5B916A_4643_48EE_969C_8E8619BC555E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Public/LPublicDef.h"
#define GETINDEX	INDEX Index;\
	Index.Index=index

class TABLE_EXPORT_CLASS CLRowItem  
{
public:
	CLRowItem();
	virtual ~CLRowItem();
	BOOL OnSerial(CLSerial& ar);
	__inline LONG GetHeight(){return m_nHeight;}
	__inline void SetHeight(LONG val){
		if(val<0)val=0;
		m_nHeight=val;
	}
private:
	LONG m_nHeight;
};
class CLRowsArr:public CLMapBase<INDEX,CLRowItem>
{
public:
	__inline CLRowItem* NewRow(LONG index){
		return (CLRowItem*)GetRow(index,TRUE);
	}
	__inline CLRowItem* GetRow(LONG index,BOOL bForceNew=FALSE){
		GETINDEX;
		return (CLRowItem*)GetValue(Index,bForceNew);
	}
	__inline void DeleteRow(LONG index){
		GETINDEX;
		DeleteValue(Index);
	}
};

#endif // !defined(AFX_LROWITEM_H__CC5B916A_4643_48EE_969C_8E8619BC555E__INCLUDED_)
