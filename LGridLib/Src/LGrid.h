//////////////////////////////////////////////////////////////////////
//@模块		 ：Grid对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-12
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LGRID_H__54098575_F5FE_472C_AC1D_2FE6E2F07244__INCLUDED_)
#define AFX_LGRID_H__54098575_F5FE_472C_AC1D_2FE6E2F07244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Public/LGridPublic.h"
#include "../Interface/LGridInterface.h"
#include "../Base/LMerge.h"

class GRID_EXPORT_CLASS CLGrid : public CLTable ,public IGrid
{
	friend class CLSheet;
private:
	void HideInPlaceCtrl();
	void ReplaceACol(LONG nDstCol, LONG nSrcCol);
	void ReplaceARow(LONG nDstRow, LONG nSrcRow);
	void ClearACol(LONG nCol,BOOL bclrMerge=TRUE);
	void ClearARow(LONG nRow,BOOL bclrMerge=TRUE);
	void MoveRows(LONG nReplaceRow,LONG nRows=1,BOOL bAdd=TRUE);
	void MoveCols(LONG nReplaceCol,LONG nCols=1,BOOL bAdd=TRUE);
	BOOL AdjustMergeObjectRange(LONG nPos,LONG nOffset,BOOL bIsRow=TRUE,
		BOOL bIsAdd=TRUE,BOOL bDisMergeCurrentCell=FALSE);
	__inline LONG getARowData(LPTSTR ptrData, COLCHAIN &colRange);
	BOOL validPasteData(LPTSTR ptrText,SIZE& size,ROWCHAIN& rowRange);
	
	void MoveRect(RECT &rct, LONG cx, LONG cy);
	BOOL GetCellRect(const CELL& cell,RECT& rct,RECT& rctVisible,BOOL bClip=TRUE);
	CLMergesArr*	m_pMergeArr;
	COLORREF m_clrGridLine;
	BOOL	m_bScrollByCell;//是否按照单元格滚动标志
	LONG	m_nPerLogicPixel;//每个滚动值代表的滚动像素
	
	LONG	m_bFillFocus;//是否填充当前焦点单元
	LONG	m_nSelectMode;//选择模式
	BOOL	m_bExcelMode;//是否为Excel模式
	BOOL	m_bRangeMode;//是否支持范围选择

	RANGE	m_TrackOld;
	RANGE	m_TrackCurr;
public:
	CLGrid();
	virtual ~CLGrid();
	BOOL OnSerial(CLSerial& ar);
	void ClearRangeData(RANGE& range);
	__inline LONG GetNextRow(const CELL& cell);
	__inline LONG GetPrevRow(const CELL& cell);
	__inline LONG GetNextCol(const CELL& cell);
	__inline LONG GetPrevCol(const CELL& cell);
	__inline void SetRangeBorderLineStyle(RANGE &range, LONG nStyle);
	__inline void SetRangeForeColor(RANGE &range, COLORREF clr);
	__inline void SetRangeBkColor(RANGE &range, COLORREF clr);
	__inline void DeleteCurrentCol();
	BOOL AppendCol();
	BOOL InsertCol(BOOL bBefore=TRUE);
	void DeleteCurrentRow();
	BOOL InsertRow(BOOL bBefore=TRUE);
	BOOL AppendRow();
	void CutDataToClipBox();
	void GetDataFromClipBox();
	void CopyDataToClipBox();
	BOOL PasteData(LPTSTR ptrText);
	void CopyDataToClipBox(RANGE &range);

	BOOL MergeCurrentRange(LONG nType=MERGE_ALL);
	BOOL UnMergeCurrentRange();
	__inline void GetMasterCell(CELL& cell);
	__inline void SetMasterCellText(LONG irow,LONG icol,LPTSTR ptrTxt);
	__inline LPTSTR GetMasterCellText(LONG irow,LONG icol);
	__inline BOOL isFocusCell(const RANGE& range);
	__inline HRGN GetRowRgn(LONG nRow,RECT& rctClip);
	__inline void GetCellRange(LONG nRow, LONG nCol, RANGE &range);
	__inline void GetCombinRange(RANGE &range, const RANGE &rangeD);
	__inline BOOL GetCellRect(LONG irow,LONG icol,RECT& rct,RECT& rctVisible,BOOL bClip=TRUE);
	__inline LONG getSelectMode(){return m_nSelectMode;};
	__inline void setSelectMode(LONG mod){m_nSelectMode=mod;};
	__inline BOOL isFillFocusMode(){return m_bFillFocus;};
	__inline void isFillFocusMode(BOOL val){m_bFillFocus=val;};
	
	__inline BOOL isRangeMode(){return m_bRangeMode;};
	__inline void isRangeMode(BOOL val){m_bRangeMode=val;};
	__inline ITable* GetTable(){return (ITable*)this;};
	__inline BOOL isExcelMode(){return m_bExcelMode;};
	__inline void isExcelMode(BOOL val){m_bExcelMode=val;};
	void RedrawScrollBar(CLScrollBar* ptrObj);
	BOOL RemoveMergeRange(RANGE& range);
	BOOL MergeRange(RANGE& range,INT nType=MERGE_ALL);
	__inline COLORREF GetGridLineColor(){return m_clrGridLine;};
	__inline void SetGridLineColor(COLORREF clr){m_clrGridLine=clr;};
	__inline BOOL GetMergeRange(const CELL cell,RANGE& range);
	__inline BOOL isMergeCell(const CELL& cell);
	LONG ScrollHorz(CLScrollBar* ptrObj,DLONG val,BOOL bPixel=FALSE);
	LONG ScrollVert(CLScrollBar* ptrObj,DLONG val,BOOL bPixel=FALSE);
	void StopExtendTrack(BOOL bHorz=TRUE);
	void AutoAdjustPos(const CELL& cell);
};

#endif // !defined(AFX_LGRID_H__54098575_F5FE_472C_AC1D_2FE6E2F07244__INCLUDED_)
