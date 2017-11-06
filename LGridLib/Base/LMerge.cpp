//////////////////////////////////////////////////////////////////////
//@模块		 ：合并对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-10
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LMerge.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLMerge::CLMerge():m_nBeginRow(-1),m_nBeginCol(-1),m_nEndRow(-1),
	m_nEndCol(-1){}

CLMerge::~CLMerge()
{
	
}

void CLMerge::getRange(LPRECT lprct)
{
	lprct->left=m_nBeginCol;
	lprct->top=m_nBeginRow;
	lprct->right=m_nEndCol;
	lprct->bottom=m_nEndRow;
}
BOOL CLMerge::OnSerial(CLSerial& ar)
{
	if(ar.isLoading()){
		ar>>m_nBeginCol;
		ar>>m_nBeginRow;
		ar>>m_nEndCol;
		ar>>m_nEndRow;
	}else{
		ar<<m_nBeginCol;
		ar<<m_nBeginRow;
		ar<<m_nEndCol;
		ar<<m_nEndRow;
	}
	return TRUE;
}
void CLMerge::setRange(LPRECT lprct)
{
	m_nBeginCol=lprct->left;
	m_nBeginRow=lprct->top;
	m_nEndCol=lprct->right;
	m_nEndRow=lprct->bottom;
}


//单元格合并对象集合

CLMergesArr::CLMergesArr(IGrid*	ptrGrid):MAP_MERGE(40,1000),m_nCount(1)
{
	m_ptrGrid=ptrGrid;
}

CLMergesArr::~CLMergesArr()
{
	m_ptrGrid=NULL;
	ClearAll();
}
//判断单元格是否被合并
BOOL CLMergesArr::isCellMerge(LONG row, LONG col)
{
	return (NULL==getMergeObject(row,col)?FALSE:TRUE);
}
//得到指定单元格的合并对象
CLMerge* CLMergesArr::getMergeObject(LONG row, LONG col,LONG& index,BOOL bForceNew)
{
	CLCellItem* ptrCell=NULL;
	CLMerge* pRet=getMergeObject(row,col,ptrCell,bForceNew);
	if(pRet)
		index=ptrCell->GetMergeIndex();
	else
		index=MERGE_NONE;
	return pRet;
}
CLMerge* CLMergesArr::getMergeObject(LONG row, LONG col,BOOL bForceNew)
{
	LONG index;
	return getMergeObject(row,col,index,bForceNew);
}
//判断指定范围是否可以被合并
BOOL CLMergesArr::ValidRange(LPRECT lpSrc,LPMERGELINK pRet,RECT& rctRet)
{
	ASSERT(lpSrc!=NULL);
	ASSERT(pRet!=NULL);
	if(lpSrc->top<0 || lpSrc->left<0 || lpSrc->bottom<0 
		|| lpSrc->right<0 || lpSrc->top>lpSrc->bottom 
		|| lpSrc->left>lpSrc->right)return FALSE;
	//范围内的单元格是否已经被合并过了
	CLMerge* ptrMerge=NULL;
	RECT rct,rctBk;
	rctBk=(*lpSrc);
	LPMERGELINK ptrT=pRet,ptrNew=NULL;
	LONG index=MERGE_NONE,indexBk=MERGE_NONE;
	for(int iRow=lpSrc->top;iRow<=lpSrc->bottom;iRow++){
		for(int iCol=lpSrc->left;iCol<=lpSrc->right;iCol++){
			ptrMerge=getMergeObject(iRow,iCol,index);
			//防止重复判断
			if(index!=indexBk){
				indexBk=index;
				if(ptrMerge){
					//范围内包含有合并对象
					//得到合并对象范围
					ptrMerge->getRange(&rct);
					//确保范围边界对齐
					switch(compRect(&rctBk,&rct)){
					case R_DIFF_RECT:
						//当前范围(lpSrc)可以当作一个新的范围添加到集合
						rctRet=(*lpSrc);
						break;
					case R_COMBINABLE_RECT:
						//当前范围(lpSrc)和比较范围(rct)可以合并
						rctRet.left=MIN(lpSrc->left,rct.left);
						rctRet.top=MIN(lpSrc->top,rct.top);
						rctRet.right=MAX(lpSrc->right,rct.right);
						rctRet.bottom=MAX(lpSrc->bottom,rct.bottom);
						if(NULL==ptrNew){
							ptrT->m_nIndex=indexBk;
							ptrT->m_ptrMerge=ptrMerge;
						}else{
							ptrNew=new MERGE_LINK();
							ptrNew->m_nIndex=indexBk;
							ptrNew->m_ptrMerge=ptrMerge;
							ptrT->m_ptrNext=ptrNew;
							ptrT=ptrNew;
						}
						break;
					case R_ERR_RECT:
						//当前范围和比较范围的交集是个非法范围
						//这种情况应不能审核通过
						goto to_error;
						break;
					default:
						//有其他情况吗？？
						//应该没有，如果走到这里应该抱错了
						goto to_error;
						break;
					}
					rctBk=rctRet;
				}
			}
		}
	}
	return TRUE;
to_error:
	if(pRet->m_ptrNext){
		delete pRet->m_ptrNext;
		pRet->m_ptrNext=NULL;
	}
	return FALSE;
}
BOOL CLMergesArr::ValidRange(LONG beginRow, LONG beginCol, 
							 LONG endRow, LONG endCol,LPMERGELINK pRet,RECT& rctRet)
{
	//规则：范围较大的合并对象会将其中范围较小的对象“吃掉”
	//确保范围有效
	RECT rct;
	rct.left=beginCol;
	rct.top=beginRow;
	rct.right=endCol;
	rct.bottom=endRow;
	return ValidRange(&rct,pRet,rctRet);
}
//范围比较
_tag_Rect_Relative CLMergesArr::compRect(LPRECT lpSrc,LPRECT lpdst)
{
	_tag_Rect_Relative nret=R_ERR_RECT;
	if(isCanCombin(lpSrc,lpdst)){
		nret=R_COMBINABLE_RECT;
	}else{
		//否则两个矩阵必须不相交
		if(lpSrc->left >lpdst->right || lpSrc->right<lpdst->left 
			|| lpdst->left>lpSrc->right || lpdst->right<lpSrc->left 
			|| lpSrc->top>lpdst->bottom || lpSrc->bottom<lpdst->top 
			|| lpdst->top>lpSrc->bottom || lpdst->bottom<lpSrc->top){
			nret=R_DIFF_RECT;
		}
		
	}
	return nret;
}

_tag_Rect_Relative CLMergesArr::compRect(LONG bgrow, LONG bgcol, LONG edrow, LONG edcol,LPRECT lpDst)
{
	RECT rct;
	rct.left=bgcol;
	rct.top=bgrow;
	rct.right=edcol;
	rct.bottom=edrow;
	return compRect(&rct,lpDst);
}

//单元格合并
BOOL CLMergesArr::mergeCells(LONG nBeginRow, LONG nBeginCol, 
						 LONG nEndRow, LONG nEndCol)
{
	BOOL bRet=FALSE;
	MERGE_LINK mergRet;
	LPMERGELINK	ptrLink;
	CLMerge* pRet;
	RECT rct;
	rct.left=nBeginCol;
	rct.top=nBeginRow;
	rct.right=nEndCol;
	rct.bottom=nEndRow;
	LONG	nIndex;
	if(ValidRange(nBeginRow,nBeginCol,nEndRow,nEndCol,&mergRet,rct)){
		if(!mergRet.IsEmpty()){
			//如果需要合并多个对象
			ptrLink=mergRet.m_ptrNext;
			while(ptrLink){
				RemoveMergeObject(ptrLink->m_nIndex);
				ptrLink=ptrLink->m_ptrNext;
			}
			pRet=mergRet.m_ptrMerge;
			nIndex=mergRet.m_nIndex;
		}else{
			nIndex=m_nCount++;
			pRet=NewMerge(nIndex);
		}
		ASSERT(pRet!=NULL);
		pRet->setRange(&rct);
		SetRangeCellIndex(nIndex,nIndex);
		bRet=TRUE;
	}
	return bRet;
}

CLMerge* CLMergesArr::NewMerge(LONG Index)
{
	INDEX key;
	key.Index = Index;
	CLMerge* pItem;
	if (Lookup(key,pItem))
		return pItem;
	pItem = new CLMerge;
	SetAt(key, pItem);
	return pItem;
}
BOOL CLMergesArr::OnSerial(CLSerial& ar)
{
	if(ar.isLoading())
		ar>>m_nCount;
	else
		ar<<m_nCount;
	return TRUE;
}
BOOL CLMergesArr::isCanCombin(LPRECT lpsrc, LPRECT dst)
{
	if(lpsrc->left==dst->left && lpsrc->right==dst->right){
		if((lpsrc->top>=dst->top && lpsrc->top<=dst->bottom) || 
			(lpsrc->bottom>=dst->top && lpsrc->bottom<=dst->bottom) ||
			(dst->top>=lpsrc->top && dst->top<=lpsrc->bottom) || 
			(dst->bottom>=lpsrc->top && dst->bottom<=lpsrc->bottom)){
			return TRUE;
		}
	}else if(lpsrc->top==dst->top && lpsrc->bottom==dst->bottom){
		if((lpsrc->left>=dst->left && lpsrc->left<=dst->right) || 
			(lpsrc->right>=dst->left && lpsrc->right<=dst->right) ||
			(dst->left>=lpsrc->left && dst->left<=lpsrc->right) || 
			(dst->right>=lpsrc->left && dst->right<=lpsrc->right)){
			return TRUE;
		}
	}else if((dst->top>=lpsrc->top && dst->top<=lpsrc->bottom && dst->bottom>=lpsrc->top 
		&& dst->bottom<=lpsrc->bottom && dst->left>=lpsrc->left && dst->left<=lpsrc->right 
		&& dst->right>=lpsrc->left && dst->right<=lpsrc->right ) ||(lpsrc->top>=dst->top 
		&& lpsrc->top<=dst->bottom && lpsrc->bottom>=dst->top && lpsrc->bottom<=dst->bottom 
		&& lpsrc->left>=dst->left && lpsrc->left<=dst->right && lpsrc->right>=dst->left 
		&& lpsrc->right<=dst->right)){
		return TRUE;
	}
	return FALSE;
}

BOOL CLMergesArr::RemoveMergeCell(LONG row,LONG col)
{
	ASSERT(m_ptrGrid!=NULL);
	CLCellItem* ptr=m_ptrGrid->GetTable()->GetACell(row,col);
	if(ptr){
		LONG nIndex=ptr->GetMergeIndex();
		if((nIndex)!=MERGE_NONE){
			if(isCanRemoveMergeCell(nIndex,row,col)){
				//能够取消单元格合并
				ptr->SetMergeIndex(MERGE_NONE);

				return TRUE;
			}else{
				return FALSE;
			}
		}
	}
	return TRUE;
}
void CLMergesArr::RemoveMergeObject(LONG nIndex)
{
	
	INDEX key;
	key.Index=nIndex;
	CLMerge* pItem;
	if (Lookup(key,pItem)){
		SetRangeCellIndex(nIndex,MERGE_NONE);
		delete pItem;
		RemoveKey(key);
	}

}
void CLMergesArr::ClearAll()
{
	INDEX key;
	CLMerge* ptrItem;
	POSITION pos = GetStartPosition();
	while (pos != NULL)
	{
		GetNextAssoc(pos, key, ptrItem);
		//SetRangeCellIndex(key.Index,MERGE_NONE);
		delete ptrItem;
	}
	
	RemoveAll(); 
}

void CLMergesArr::SetRangeCellIndex(LONG nIndex,LONG nIndexTo)
{
	ASSERT(m_ptrGrid!=NULL);
	INDEX key;
	key.Index=nIndex;
	CLMerge* ptr;
	CLCellItem* ptrItem=NULL;
	if(Lookup(key,ptr)){
		RECT rct;
		ptr->getRange(&rct);
		for(int irow=rct.top;irow<=rct.bottom;irow++){
			for(int icol=rct.left;icol<=rct.right;icol++){
				ptrItem=m_ptrGrid->GetTable()->GetACell(irow,icol);
				if(ptrItem){
					ptrItem->SetMergeIndex(nIndexTo);
				}
			}
		}
	}
}
void CLMergesArr::GetMasterCell(CELL& cell)
{
	ASSERT(m_ptrGrid!=NULL);
	LONG index;
	CLMerge* ptrMerge=getMergeObject(cell.Row,cell.Col,index,FALSE);
	if(ptrMerge){
		RECT rct;
		ptrMerge->getRange(&rct);
		cell.Row=rct.top;
		cell.Col=rct.left;
	}
}
CLCellItem* CLMergesArr::GetMasterCell(LONG nRow, LONG nCol,LONG& index,BOOL bForceNew)
{
	ASSERT(m_ptrGrid!=NULL);
	CLMerge* ptrMerge=getMergeObject(nRow,nCol,index,bForceNew);
	if(ptrMerge){
		RECT rct;
		ptrMerge->getRange(&rct);
		nRow=rct.top;
		nCol=rct.left;
	}
	return m_ptrGrid->GetTable()->GetACell(nRow,nCol,bForceNew);
}

BOOL CLMergesArr::GetMergeInfo(LONG nIndex,RECT& rct)
{
	CLMerge* ptrMerge=GetMergeObject(nIndex);
	BOOL bRet=FALSE;
	if(ptrMerge!=NULL){
		ptrMerge->getRange(&rct);
		bRet=TRUE;
	}
	return bRet;
}

CLMerge* CLMergesArr::GetMergeObject(LONG nIndex)
{
	CLMerge* ptrRet=NULL;
	INDEX key;
	key.Index=nIndex;
	Lookup(key,ptrRet);
	return ptrRet;
}

BOOL CLMergesArr::isCanRemoveMergeCell(LONG nIndex, LONG nRow, LONG nCol)
{
	CLMerge* ptrMerge=GetMergeObject(nIndex);
	if(ptrMerge){
		RECT rctRange;
		ptrMerge->getRange(&rctRange);
		return (rctRange.top==rctRange.bottom?nCol==rctRange.left || 
			nCol==rctRange.right:(rctRange.left==rctRange.right?nRow==rctRange.top ||
			nRow==rctRange.bottom:FALSE));
	}
	return FALSE;
}

BOOL CLMergesArr::RemoveMergeRange(RANGE &range)
{
	BOOL bret=FALSE;
	//检查范围
	VALUE_LINK vLink;
	LPVALUELINK ptrLink;
	if(isCanRemoveRange(range,vLink)){
		ptrLink=&vLink;
		while(ptrLink){
			if(ptrLink->nValue!=INIT_LINK_VALUE){
				RemoveMergeObject(ptrLink->nValue);
			}
			ptrLink=ptrLink->ptrNext;
		}
		bret=TRUE;
	}
	return bret;
}

BOOL CLMergesArr::isCanRemoveRange(RANGE &range,VALUE_LINK& retIndex)
{
	BOOL bret=TRUE;
	LONG nIndex;
	if(!range.isEmpty() && !range.isSingleCellRange()){
		bret=TRUE;
		LONG nTmp;
		RECT rct;
		range.GetRangeRect(rct);
		if(rct.left>rct.right){
			nTmp=rct.left;
			rct.left=rct.right;
			rct.right=nTmp;
		}
		if(rct.top>rct.bottom){
			nTmp=rct.top;
			rct.top=rct.bottom;
			rct.bottom=nTmp;
		}
		CLMerge* ptr=NULL;
		LPVALUELINK ptrLink=NULL;
		RECT rctT;
		for(LONG irow=rct.top;irow<=rct.bottom;irow++){
			for(LONG icol=rct.left;icol<=rct.right;icol++){
				ptr=getMergeObject(irow,icol,nIndex);
				if(ptr && !retIndex.isExist(nIndex)){
					ptr->getRange(&rctT);
					if(rct.left<=rctT.left && rct.top<=rctT.top 
						&& rct.right>=rctT.right && rct.bottom>=rctT.bottom){
						if(ptrLink==NULL)
							ptrLink=&retIndex;
						else{
							ptrLink->ptrNext=new VALUE_LINK();
							ptrLink=ptrLink->ptrNext;
						}
						ptrLink->nValue=nIndex;
					}else{
						return FALSE;
					}
				}
			}
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CLMergesArr::GetRangeInfo(LONG nRow,LONG nCol,RANGE &range)
{
	CLMerge* ptr=getMergeObject(nRow,nCol,FALSE);
	RECT rct;
	BOOL bret=FALSE;
	if(ptr){
		ptr->getRange(&rct);
		bret=TRUE;
	}else{
		rct.left=nCol;
		rct.right=nCol;
		rct.top=nRow;
		rct.bottom=nRow;
	}
	range.m_posCol.m_begin=rct.left;
	range.m_posCol.m_end=rct.right;
	range.m_posRow.m_begin=rct.top;
	range.m_posRow.m_end=rct.bottom;
	return bret;
}

CLMerge* CLMergesArr::getMergeObject(CLCellItem *ptrCell)
{
	if(NULL==ptrCell)return NULL;
	LONG nIndex=ptrCell->GetMergeIndex();
	if(nIndex!=MERGE_NONE){
		return GetMergeObject(nIndex);
	}
	return NULL;
}

void CLMergesArr::RemoveMergeObject(CLCellItem *ptrCell)
{
	if(NULL==ptrCell)return;
	LONG nIndex=ptrCell->GetMergeIndex();
	if(nIndex!=MERGE_NONE){
		RemoveMergeObject(nIndex);
	}
}

void CLMergesArr::RefreshMergeRange(LONG nIndex)
{
	CLMerge* ptrMerge=GetMergeObject(nIndex);
	if(ptrMerge){
		RECT rctRange;
		CLCellItem* ptrItem=NULL;
		ptrMerge->getRange(&rctRange);
		for(LONG irow=rctRange.top;irow<=rctRange.bottom;irow++){
			for(LONG icol=rctRange.left;icol<=rctRange.right;icol++){
				ptrItem=m_ptrGrid->GetTable()->GetACell(irow,icol);
				if(ptrItem){
					ptrItem->SetMergeIndex(nIndex);
				}
			}
		}
	}
}
CLMerge* CLMergesArr::getMergeObject(LONG row,LONG col,
									 CLCellItem*& ptrItem,BOOL bForceNew)
{
	ASSERT(m_ptrGrid!=NULL);
	CLMerge* ptrRet=NULL;
	ptrItem=m_ptrGrid->GetTable()->GetACell(row,col,bForceNew);
	if(ptrItem){
		INDEX key;
		if((key.Index=ptrItem->GetMergeIndex())!=MERGE_NONE){
			Lookup(key,ptrRet);
		}
	}
	return ptrRet;
}
BOOL CLMergesArr::mergeRange(RANGE& range)
{
	if(range.isSingleCellRange())return FALSE;
	return mergeCells(range.m_posRow.m_begin,range.m_posCol.m_begin,
		range.m_posRow.m_end,range.m_posCol.m_end);
}