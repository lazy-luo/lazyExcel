// LCellItem.h: interface for the CLCellItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCELLITEM_H__E721BE6C_D051_411F_99B3_45AA5098A966__INCLUDED_)
#define AFX_LCELLITEM_H__E721BE6C_D051_411F_99B3_45AA5098A966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Public/LPublicDef.h"
#define GETCELL	CELL cell;\
	cell.Row=irow;\
	cell.Col=icol

class TABLE_EXPORT_CLASS CLCellItem  
{
private:
	LPTSTR	m_ptrTxt;
	LPTSTR	m_ptrMemo;
	LONG	m_nMergeIndex;
public:
	BOOL OnSerial(CLSerial& ar);
	void ClearToDefault(BOOL bClrMerge=TRUE);
	void SetCell(CLCellItem* ptrCell);
	void SetCell(CLCellItem& cell);
	CLCellItem();
	virtual ~CLCellItem();
	LPTSTR	GetText();
	void	SetText(LPTSTR ptr);
	LPTSTR	GetMemo();
	void	SetMemo(LPTSTR ptr);
	__inline LONG	GetMergeIndex(){return m_nMergeIndex;};
	__inline void SetMergeIndex(LONG nIndex){m_nMergeIndex=nIndex;};
};

class CLCellsArr:public CLMapBase<CELL,CLCellItem>
{
public:
	__inline CLCellItem* NewCell(LONG irow,LONG icol){
		return (CLCellItem*)GetCell(irow,icol,TRUE);
	}
	__inline CLCellItem* GetCell(LONG irow,LONG icol,BOOL bForceNew=FALSE){
		GETCELL;
		return (CLCellItem*)GetValue(cell,bForceNew);
	}
	__inline void DeleteCell(LONG irow,LONG icol){
		GETCELL;
		DeleteValue(cell);
	}
};
#endif // !defined(AFX_LCELLITEM_H__E721BE6C_D051_411F_99B3_45AA5098A966__INCLUDED_)
