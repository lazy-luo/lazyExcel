//////////////////////////////////////////////////////////////////////
//@模块		 ：表格对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-10
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTABLE_H__05027B11_7281_41A7_8848_95DEE70C6975__INCLUDED_)
#define AFX_LTABLE_H__05027B11_7281_41A7_8848_95DEE70C6975__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Public/LPublicDef.h"
#include "../Base/LCellItem.h"
#include "../Base/LColItem.h"
#include "../Base/LRowItem.h"
#include "../Base/LStyle.h"
#ifdef _DEBUG
	#define ASSERT_CELL(cell) \
		ASSERT(cell.Row>=0 && cell.Row<m_Rows && cell.Col>=0 && cell.Col<m_Cols);
#else
	#define ASSERT_CELL(cell)
#endif
class TABLE_EXPORT_CLASS CLTable:public ITable,public IParse_Function_Macro,public CLCallServ,public LScript_Engine
{
	friend class CLGrid;
	friend class CLSheet;
public:
	BOOL IsFormulaCell(LONG nRow,LONG nCol);
	void SetFormulaValue(LONG nRow,LONG nCol,char* pValue);
	LPTSTR GetFormulaValue(LONG nRow,LONG nCol);
	__inline void GetBeginPos(CELL& cell,POINT& ptOffset);
	__inline void GetEndPos(CELL& cell,POINT& ptOffset,
		const SIZE& size,CELL& cellRet,POINT& ptRet);
	BOOL OnSerial(CLSerial& ar);
	void SetBkColor(RANGE& range,COLORREF clr);
	void SetForeColor(RANGE& range,COLORREF clr);
	__inline BOOL CellReadOnly(LONG nRow, LONG nCol);
	void CellReadOnly(LONG nRow, LONG nCol, BOOL bVal);
	void ClearCellData(LONG nRow,LONG nCol,BOOL bRedraw=TRUE);
	void SetRangeReadOnly(RANGE &range, BOOL bVal);
	BOOL IsRangeReadOnly(RANGE &range);
	__inline void SetBorderStyle(LONG nRow, LONG nCol, LONG nStyle)
	{
		CELL cell(nRow,nCol);
		SetBorderStyle(cell,nStyle);
	}
	__inline LONG GetBorderStyle(LONG nRow, LONG nCol){
		CELL cell(nRow,nCol);
		return GetBorderStyle(cell);
	}
	__inline void GetOldRange(RANGE& range);
	__inline void ClearOldRange();
	__inline void GetCurrentRange(RANGE& range);
	
	__inline void SetCellMemo(LONG irow, LONG icol, LPTSTR ptrTxt);
	__inline LPTSTR GetCellMemo(LONG irow, LONG icol);
	__inline COLORREF GetBorderColor(const CELL& cell)
	{
		CLStyle* ptrStyle=GetCellStyle(cell);
		return (ptrStyle?ptrStyle->GetBorderColor():COLOR_CELL_BORDER_LINE);
	}
	__inline LONG GetBorderStyle(const CELL& cell)
	{
		CLStyle* ptrStyle=GetCellStyle(cell);
		return (ptrStyle?ptrStyle->GetBorderStyle():DEFAULT_BORDER_STYLE);
	}
	__inline void SetBorderStyle(const CELL& cell,LONG style)
	{
		CLStyle* ptrStyle=GetCellStyle(cell,TRUE);
		if(ptrStyle){
			ptrStyle->SetBorderStyle(style);
			ReDraw();
		}
	}
	__inline LONG GetCashStyle(const CELL& cell){
		CLStyle* ptrStyle=GetCellStyle(cell);
		return (ptrStyle?ptrStyle->GetType():NO_CASH_STYLE);
	}
	__inline void SetCashStyle(const CELL& cell,LONG style)
	{
		CLStyle* ptrStyle=GetCellStyle(cell,TRUE);
		if(ptrStyle){
			ptrStyle->SetType(style);
			ReDraw();
		}
	}
	__inline LONG GetBorderLineStyle(const CELL& cell)
	{
		CLStyle* ptrStyle=GetCellStyle(cell);
		return (ptrStyle?ptrStyle->GetBorderLineStyle():BORDER_NO_LINE_DOT);
	}
	__inline void SetBorderLineStyle(const CELL& cell,LONG style)
	{
		CLStyle* ptrStyle=GetCellStyle(cell,TRUE);
		if(ptrStyle){
			ptrStyle->SetBorderLineStyle(style);
			ReDraw();
		}
	}
	__inline void SetCashStyle(const RANGE& range,LONG style);
	__inline void SetBorderLineStyle(const RANGE& range,LONG style);
	__inline void SetBorderStyle(const RANGE& range,LONG style);

	BOOL isFocusCell(const CELL& cell);
	__inline void GetRightBottomCell(const SIZE& sizeClient/*ClientSize*/,CELL& cell,POINT& ptOffsetClip);
	__inline BOOL isRangeVisible(const RANGE& range,BOOL* bisClip=NULL,LPRECT prctOff=NULL);
	void AdjustSizeChange(LONG cx, LONG cy,BOOL bSpecColRowSize=FALSE);
	__inline LPSCROLLINFOEXT GetScrollInfo(BOOL bHorz=TRUE);
	__inline void SetCellText(LONG irow,LONG icol,LPTSTR ptrTxt);
	__inline LPTSTR GetCellText(LONG irow,LONG icol);
	__inline void SetRowHeight(LONG irow,LONG val);
	__inline LONG GetRowHeight(LONG irow);
	__inline void SetColWidth(LONG icol,LONG val);
	__inline LONG GetColWidth(LONG icol);
	
	CLTable();
	virtual ~CLTable();
	__inline BOOL CanScroll(BOOL bHorz,BOOL bAddValue);
	__inline LONG GetCols(){return m_Cols;};
	__inline LONG GetRows(){return m_Rows;};
	__inline LONG GetFixedRows(){return m_FixedRows;};
	__inline LONG GetFixedCols(){return m_FixedCols;};
	__inline LONG GetFreezeRows(){return m_FreezeRows;};
	__inline LONG GetFreezeCols(){return m_FreezeCols;};
	
	__inline void SetCols(LONG val);
	__inline void SetRows(LONG val);
	__inline void SetFixedRows(LONG val);
	__inline void SetFixedCols(LONG val);
	__inline void SetFreezeRows(LONG val);
	__inline void SetFreezeCols(LONG val);
	__inline BOOL HasScroll(BOOL bHorz);
	
	__inline void ReDraw(BOOL bFull=FALSE){if(m_ptrOuter)m_ptrOuter->ReDraw(bFull);};
	__inline void ReleaseDC(HDCH& hDC){if(m_ptrOuter)m_ptrOuter->ReleaseDC(hDC);};
	__inline BOOL GetDC(HDCH& hDC){return (m_ptrOuter?m_ptrOuter->GetDC(hDC):FALSE);};
	__inline CLCellItem* GetACell(const CELL cell,BOOL bForceNew=FALSE){return GetACell(cell.Row,cell.Col,bForceNew);};
	__inline CLCellItem* GetACell(LONG irow,LONG icol,BOOL bForceNew=FALSE);
	__inline CLColItem*	GetACol(LONG icol,BOOL bForceNew=FALSE);
	__inline CLRowItem*	GetARow(LONG irow,BOOL bForceNew=FALSE);
	
	virtual __inline CLStyle* GetCellStyle(const CELL& cell,BOOL bForceNew=FALSE);
	__inline CLFont* GetCellFont(const CELL& cell,BOOL bForceNew=FALSE);
	__inline void SetExtendSize(const SIZE& size){m_sizeExtend=size;};
	__inline void GetExtendSize(SIZE& size){size=m_sizeExtend;};
	__inline COLORREF GetBorderLineColor(LONG irow,LONG icol){
		CLStyle* ptr=GetCellStyle(irow,icol);
		return ptr->GetBorderColor();
	}
	__inline void SetBorderColor(LONG irow,LONG icol,COLORREF clr){
		CLStyle* ptr=GetCellStyle(irow,icol,TRUE);
		ptr->SetBorderColor(clr);
	}
	__inline BOOL isFixedCell(const CELL& cell){
		ASSERT_CELL(cell);
		return cell.Row<m_FixedRows || cell.Col<m_FixedCols;
	};
	__inline BOOL isFreezeCell(const CELL& cell){
		ASSERT_CELL(cell);
		return (cell.Row>=m_FixedRows && cell.Row<m_FixedRows+m_FreezeRows) ||
			(cell.Col>=m_FixedCols && cell.Col<m_FixedCols+m_FreezeCols);
	}
	
	__inline BOOL GetRangeRect(const RANGE& range,RECT& rctClip,
		RECT& rctVisible,RECT& rct,LONG nOffset);
	__inline LONG GetFontSize(LONG nRow,LONG nCol);
	__inline LPTSTR GetFontName(LONG nRow,LONG nCol);
	__inline void SetFontSize(RANGE &range,LONG iSize);
	__inline void SetFontName(RANGE& range,LPTSTR ptrName,BYTE bytChatSet);
	__inline void SetBorderColor(RANGE& range,COLORREF clr);
	__inline BOOL IsAlignBottom(LONG nRow,LONG nCol);
	__inline BOOL IsAlignMiddle(LONG nRow,LONG nCol);
	__inline BOOL IsAlignTop(LONG nRow,LONG nCol);
	__inline void SetAlignBottom(RANGE& range);
	__inline void SetAlignMiddle(RANGE& range);
	__inline void SetAlignTop(RANGE& range);
	__inline BOOL IsAlignRight(LONG nRow,LONG nCol);
	__inline BOOL IsAlignCenter(LONG nRow,LONG nCol);
	__inline BOOL IsAlignLeft(LONG nRow,LONG nCol);
	__inline BOOL IsFontBold(LONG nRow,LONG nCol);
	__inline BOOL IsFontItalic(LONG nRow,LONG nCol);
	__inline BOOL IsFontUnderline(LONG nRow,LONG nCol);
	__inline void SetFontUnderline(RANGE& range,BOOL bVal);
	__inline void SetFontItalic(RANGE& range,BOOL bVal);
	__inline void SetFontBold(RANGE& range,BOOL bVal);
	__inline void SetAlignCenter(RANGE& range);
	__inline void SetAlignRight(RANGE& range);
	__inline void SetAlignLeft(RANGE& range);
	virtual __inline void SetRedrawHelp(IRedrawHelp* ptr);
	
	/////////////////////////////////////////////////////////////////////
	///////////////表格尺寸相关函数//////////////////////
	__inline void GetCellBeginXY(POINT& pt)
	{
		pt=m_beginLeftTop;
	}
	__inline void SetCellBeginXY(const POINT& pt)
	{
		m_beginLeftTop=pt;
	}
	__inline void GetDrawPanRect(RECT& rct)
	{
		rct.left=m_beginDrawPos.x;
		rct.top=m_beginDrawPos.y;
		rct.right=rct.left+m_sizeAll.cx;
		rct.bottom=rct.top+m_sizeAll.cy;
	};
	__inline void GetClientRect(RECT& rct,BOOL bRel=FALSE){
		POINT pt;
		GetBeginClientPos(pt);
		SIZE size;
		GetClientSize(size);
		if(bRel){
			//如果为真意味着想要得到实际的客户区大小（即Table域实际尺寸）
			size.cx=(size.cx>m_hScrollInfo.m_nMaxValue-pt.x?
				m_hScrollInfo.m_nMaxValue-pt.x+1:size.cx);
			size.cy=(size.cy>m_vScrollInfo.m_nMaxValue-pt.y?
				m_vScrollInfo.m_nMaxValue-pt.y+1:size.cy);
		}
		rct.left=pt.x;
		rct.top=pt.y;
		rct.right=rct.left+size.cx;
		rct.bottom=rct.top+size.cy;
	};
	__inline void GetTableRect(RECT& rct){
		POINT pt;
		GetBeginTablePos(pt);
		rct.left=pt.x;
		rct.top=pt.y;
		rct.right=rct.left+m_sizeTable.cx;
		rct.bottom=rct.top+m_sizeTable.cy;
	};
	__inline void GetCurrentCell(CELL& cell){
		if(m_currentCell.Row<m_FixedRows)
			m_currentCell.Row=m_FixedRows;
		if(m_currentCell.Col<m_FixedCols)
			m_currentCell.Col=m_FixedCols;
		
		cell=m_currentCell;
	};
	__inline void GetPrevFocusCell(CELL& cell){
		cell=m_prevFocusCell;
	}
	__inline void SetPrevFocusCell(const CELL& cell){
		m_prevFocusCell=cell;
	}
	__inline void SetOldRange(const RANGE& range){m_OldRange=range;};
	__inline void SetCurrentRange(const RANGE& range){m_CurrRange=range;};
	__inline void SetCurrentCell(CELL& cell){
		m_CurrRange.SetSingleCellRange(cell);
		m_currentCell=cell;
	};
	//扩展尺寸函数(主要用于打印)
	__inline void GetClientRect(const RECT& rctAll,RECT& rct)
	{
		POINT pt;
		pt.x=rctAll.left+m_sizeFreeLeft.cx;
		pt.y=rctAll.top+m_sizeFreeTop.cy+FLAG_BAR_HEIGHT;
		LONG nFixedColsLen=GetFixedColsWidth();
		LONG nFixedRowsLen=GetFixedRowsHeight();
		LONG nFreezeRowLen=GetFreezeRowsHeight();
		LONG nFreezeColLen=GetFreezeColsWidth();
		pt.x+=nFixedColsLen;
		pt.y+=nFixedRowsLen;
		pt.x+=nFreezeColLen;
		pt.y+=nFreezeRowLen;
		SIZE size,sizeTable,sizeAll;

		sizeAll.cx=rctAll.right-rctAll.left;
		sizeAll.cy=rctAll.bottom-rctAll.top;
		sizeTable.cx=sizeAll.cx-m_sizeFreeLeft.cx-m_sizeFreeRight.cx;
		sizeTable.cy=sizeAll.cy-m_sizeFreeTop.cy-FLAG_BAR_HEIGHT-m_sizeFreeBottom.cy;
		size.cx=sizeTable.cx-(nFixedColsLen+nFreezeColLen);
		size.cy=sizeTable.cy-(nFixedRowsLen+nFreezeRowLen);

		rct.left=pt.x;
		rct.top=pt.y;
		rct.right=rct.left+size.cx;
		rct.bottom=rct.top+size.cy;
	};	//ext
	__inline void GetTableRect(const RECT& rctAll,RECT& rct)
	{
		POINT pt;
		GetBeginTablePos(pt);
		rct.left=pt.x;
		rct.top=pt.y;
		rct.right=rct.left+m_sizeTable.cx;
		rct.bottom=rct.top+m_sizeTable.cy;
	};
	__inline void GetBeginDrawPos(const RECT& rctAll,POINT &pt)
	{
		pt.x=rctAll.left;
		pt.y=rctAll.top;
	};
	__inline void GetBeginTablePos(const RECT& rctAll,POINT &pt)
	{
		pt.x=rctAll.left+m_sizeFreeLeft.cx;
		pt.y=rctAll.top+m_sizeFreeTop.cy+FLAG_BAR_HEIGHT;
	};
	__inline void GetBeginClientPos(const RECT& rctAll,POINT &pt)
	{
		GetBeginFreezePos(rctAll,pt);
		pt.x+=GetFreezeColsWidth();
		pt.y+=GetFreezeRowsHeight();
	};
	__inline void GetBeginFreezePos(const RECT& rctAll,POINT &pt)
	{
		GetBeginTablePos(rctAll,pt);
		pt.x+=GetFixedColsWidth();
		pt.y+=GetFixedRowsHeight();
	};

	__inline void GetDrawPanSize(const RECT& rctAll,SIZE& size)
	{
		size.cx=rctAll.right-rctAll.left;
		size.cy=rctAll.bottom-rctAll.top;
	};
	__inline void GetClientSize(const RECT& rctAll,SIZE& size)
	{
		SIZE sizeTable,sizeAll;
		LONG nFixedColsLen=GetFixedColsWidth();
		LONG nFixedRowsLen=GetFixedRowsHeight();
		LONG nFreezeRowLen=GetFreezeRowsHeight();
		LONG nFreezeColLen=GetFreezeColsWidth();

		sizeAll.cx=rctAll.right-rctAll.left;
		sizeAll.cy=rctAll.bottom-rctAll.top;
		sizeTable.cx=sizeAll.cx-m_sizeFreeLeft.cx-m_sizeFreeRight.cx;
		sizeTable.cy=sizeAll.cy-m_sizeFreeTop.cy-FLAG_BAR_HEIGHT-m_sizeFreeBottom.cy;
		size.cx=sizeTable.cx-(nFixedColsLen+nFreezeColLen);
		size.cy=sizeTable.cy-(nFixedRowsLen+nFreezeRowLen);
	};

	BOOL GetRangeRect(const RECT& rctAll,const RANGE& range,RECT& rctClip,
		RECT& rctVisible,RECT& rct,LONG nOffset);//ext

	////
	void SetDrawPanRect(const RECT& rct);
	__inline void GetBeginDrawPos(POINT &pt){pt=m_beginDrawPos;};
	__inline void SetBeginDrawPos(const POINT& pt){m_beginDrawPos=pt;};
	__inline void GetBeginTablePos(POINT &pt);
	__inline void GetBeginClientPos(POINT &pt);
	__inline void GetBeginFreezePos(POINT &pt);
	__inline void GetBeginCell(CELL& cell){
		if(m_beginCell.Row<m_FixedRows+m_FreezeRows)
			m_beginCell.Row=m_FixedRows+m_FreezeRows;
		if(m_beginCell.Col<m_FixedCols+m_FreezeCols)
			m_beginCell.Col=m_FixedCols+m_FreezeCols;
		cell=m_beginCell;
	};
	__inline void SetBeginCell(const CELL& cell){m_beginCell=cell;};
	__inline void GetClientSize(SIZE& size);
	__inline void GetDrawPanSize(SIZE& size){size=m_sizeAll;};
	__inline void SetDrawPanSize(const SIZE& size);
	
	
	__inline void GetFreeAreaSize(SIZE& size,LONG nFreeID);
	__inline void SetFreeAreaSize(const SIZE& size,LONG nFreeID);
	/////////////////////////////////////////////////////////////////////
	//内部消息捕获函数
	LONG NotifyProc(LONG wMsg,LONG nCmd,WPARAM wParam,
		LPARAM lParam,BOOL& bCancel){
		bCancel=FALSE;
		return 0;
	};

private:

	BOOL GetRangeRect_Atom(const RECT& rctClp,const POINT& ptCellBeginXY/*ptCellBeginXY*/,const POINT& ptFreezeBegin/*BeginFreezePos*/,
						   const RANGE& rgn,RECT& rctClip,
						   RECT& rctVisible,RECT& rct,LONG nOffset);
	void InitSize();
	LONG GetFreezeColsWidth();
	LONG GetFreezeRowsHeight();
	LONG GetFixedColsWidth();
	LONG GetFixedRowsHeight();
	IRedrawHelp*	m_ptrOuter;
	CLCSWrapper     sm_CritSec;	//同步对象
protected:
	void RemoveCellStyle(LONG nRow, LONG nCol);
	virtual __inline CLStyle* GetCellStyle(LONG irow,LONG icol,BOOL bForceNew=FALSE);
	virtual __inline BOOL IsDefaultCellStyle(CLStyle* ptrStyle);
	virtual __inline BOOL IsDefaultCellFont(CLFont* ptrFont);
	LONG	m_Rows;
	LONG	m_Cols;
	LONG	m_FixedRows;
	LONG	m_FixedCols;
	LONG	m_FreezeRows;
	LONG	m_FreezeCols;
	
	SIZE	m_sizeExtend;
	SIZE	m_sizeAll;		//对象尺寸(包括上下左右四个方向可能的预留区域)
	SIZE	m_sizeTable;	//表格对象尺寸
	SIZE	m_sizeClient;
	SIZE	m_sizeFreeTop;
	SIZE	m_sizeFreeLeft;
	SIZE	m_sizeFreeRight;
	SIZE	m_sizeFreeBottom;
	
	CELL	m_prevFocusCell;
	CELL	m_beginCell;	//表格客户端开始单元格
	POINT	m_beginLeftTop;	//客户区右上角偏移
	
	CELL	m_currentCell;	//当前焦点单元
	POINT	m_beginDrawPos;			//对象起始位置
	RANGE	m_CurrRange;
	RANGE	m_OldRange;
	
	SCROLLINFOEXT	m_vScrollInfo;//垂直滚动信息
	SCROLLINFOEXT	m_hScrollInfo;//水平滚动信息
	
	CLCellsArr	m_CellsArr;	//单元格集合
	CLColsArr	m_ColsArr;	//列集合
	CLRowsArr	m_RowsArr;	//行集合
	CLStylesArr	m_StyleArr;	//单元格样式集合
	CLFontArr	m_FontArr;	//字体集合
};

#endif // !defined(AFX_LTABLE_H__05027B11_7281_41A7_8848_95DEE70C6975__INCLUDED_)
