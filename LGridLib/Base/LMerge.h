//////////////////////////////////////////////////////////////////////
//@模块		 ：合并对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-10
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LMERGE_H__F38FE0C3_3CB5_4BD8_A4FE_47A5F41AA174__INCLUDED_)
#define AFX_LMERGE_H__F38FE0C3_3CB5_4BD8_A4FE_47A5F41AA174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Public/LGridPublic.h"
#include "../Interface/LGridInterface.h"
class CLMerge;
class CLMergesArr;
typedef struct tag_MergeLink
{
	tag_MergeLink():m_ptrMerge(NULL),m_ptrNext(NULL),m_nIndex(MERGE_NONE){}
	BOOL IsEmpty(){return m_ptrMerge==NULL && m_ptrNext==NULL;}
	CLMerge* m_ptrMerge;
	LONG m_nIndex;
	tag_MergeLink* m_ptrNext;
	~tag_MergeLink(){
		while(m_ptrNext)
			delete m_ptrNext;
		m_ptrNext=NULL;
	}
}MERGE_LINK,*LPMERGELINK;

class GRID_EXPORT_CLASS CLMerge  
{
	friend class CLMergesArr;
public:
	BOOL OnSerial(CLSerial& ar);
	void setRange(LPRECT lprct);
	void getRange(LPRECT lprct);
	CLMerge();
	virtual ~CLMerge();
private:
	int m_nBeginRow;
	int m_nBeginCol;
	int m_nEndRow;
	int m_nEndCol;
};
//合并对象集合
#define MAP_MERGE	LMap<INDEX,INDEX&,CLMerge*,CLMerge*&>

class GRID_EXPORT_CLASS CLMergesArr : public MAP_MERGE  
{
private:
	LONG	m_nCount;
	BOOL isCanRemoveRange(RANGE& range,VALUE_LINK& retIndex);
	BOOL isCanRemoveMergeCell(LONG nIndex,LONG nRow,LONG nCol);
	__inline CLMerge* GetMergeObject(LONG nIndex);
	
	void SetRangeCellIndex(LONG nIndex,LONG nIndexTo);
	IGrid* m_ptrGrid;
	__inline CLMerge* getMergeObject(LONG row, LONG col,LONG& index,BOOL bForceNew=TRUE);
	
	
	__inline BOOL  isCanCombin(LPRECT lpsrc,LPRECT dst);
	__inline _tag_Rect_Relative compRect(LONG bgrow,LONG bgcol,LONG edrow,LONG edcol,LPRECT lpDst);
	__inline _tag_Rect_Relative compRect(LPRECT lpSrc,LPRECT lpdst);
	BOOL ValidRange(LONG beginRow,LONG beginCol,LONG endRow,LONG endCol,
		LPMERGELINK pRet,RECT& rctRet);
	BOOL ValidRange(LPRECT lpSrc,LPMERGELINK pRet,RECT& rctRet);
public:
	CLMerge* NewMerge(LONG Index);
	BOOL OnSerial(CLSerial& ar);
	void RefreshMergeRange(LONG nIndex);
	void RemoveMergeObject(CLCellItem* ptrCell);
	__inline CLMerge* getMergeObject(LONG row,LONG col,CLCellItem*& ptrItem,BOOL bForceNew=FALSE);
	CLMerge* getMergeObject(CLCellItem* ptrCell);
	__inline CLMerge* getMergeObject(LONG row,LONG col,BOOL bForceNew=TRUE);
	__inline void GetMasterCell(CELL& cell);
	BOOL RemoveMergeRange(RANGE& range);
	void RemoveMergeObject(LONG nIndex);
	__inline BOOL GetMergeInfo(LONG nIndex,RECT& rct);
	__inline BOOL GetRangeInfo(LONG nRow,LONG nCol,RANGE &range);
	__inline CLCellItem* GetMasterCell(LONG nRow,LONG nCol,LONG& index,BOOL bForceNew=FALSE);
	BOOL RemoveMergeCell(LONG row,LONG col);
	__inline BOOL isCellMerge(LONG row,LONG col);
	BOOL mergeCells(LONG nBeginRow,LONG nBeginCol,LONG nEndRow,LONG nEndCol);
	BOOL mergeRange(RANGE& range);
	void ClearAll();
	CLMergesArr(IGrid*	ptrGrid);
	virtual ~CLMergesArr();
};

#endif // !defined(AFX_LMERGE_H__F38FE0C3_3CB5_4BD8_A4FE_47A5F41AA174__INCLUDED_)
