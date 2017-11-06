//////////////////////////////////////////////////////////////////////
//@模块		 ：导出对象实现
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////
#ifndef _LAPIIINTERFACE_H
#define _LAPIIINTERFACE_H
//单元格格式定义
#define C_LZY_API(ret,name)	 ret name
#ifndef STATIC_LINK
#	pragma comment(lib,"LGridBook.lib")
	
static LOGFONT DEFAULT_LOGFONT={-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, _T("宋体")};

typedef enum _tag_Horz_Align{
	horz_align_left=0,
	horz_align_center,
	horz_align_right
}enum_horz_align;
typedef enum _tag_Vert_Align{
	vert_align_top=0,
	vert_align_middle,
	vert_align_bottom
}enum_vert_align;
typedef enum _tag_Number_Format{
	number_format_default=0,//默认格式
	number_format_money,//金额格式
	number_format_percent,//百分比格式
	number_format_dotSP,//点分格式
	number_format_dec_zero,//减少精度
	number_format_inc_zero//增加精度
}enum_number_format;
typedef struct _tagCELL
{
	LONG Col;
	LONG Row;
	BOOL operator==(const _tagCELL& cell) const
		{ return Col == cell.Col && Row == cell.Row ; }
	void operator =(const _tagCELL& cell){
		Col=cell.Col;
		Row=cell.Row;
	}
}CELL,*LPCELL;
typedef struct _tagPOS
{
	LONG m_begin;
	LONG m_end;
	_tagPOS():m_begin(-1),m_end(-1){};
	BOOL operator ==(const _tagPOS& pos) const{
		return (m_begin==pos.m_begin && m_end==pos.m_end);
	}
	void operator =(const _tagPOS& pos){
		m_begin=pos.m_begin;
		m_end=pos.m_end;
	}
}POS,*LPPOS;
typedef struct _tagRANGE
{
public:
	POS m_posRow;
	POS m_posCol;
	BOOL operator ==(const _tagRANGE& range) const{
		return (m_posRow==range.m_posRow && m_posCol==range.m_posCol);
	}
	void operator =(const _tagRANGE& range){
		m_posRow=range.m_posRow;
		m_posCol=range.m_posCol;
	}
}RANGE,*LPRANGE;
#else
#	define __DEF_POSITION
#   define _NORMAL_CALL
#	define RES_DEFINE
#	include "../../../OSFace/Win32/InterLink/LRptGrid.h"
#endif
#ifndef STATIC_LINK
extern "C"{
#endif

C_LZY_API(LONG,CreateReport)();
C_LZY_API(LONG,GetBook)(LONG rptHandle);
C_LZY_API(void,GetCurrentRange)(LONG sheet,RANGE& range);
C_LZY_API(BOOL,AddBitmapPan)(LONG book, LONG sheet,LPTSTR ptrName);
C_LZY_API(BOOL,GetCurrentCell)(LONG sheet,CELL& cell);
C_LZY_API(LONG,GetFontSize)(LONG sheet, LONG nRow, LONG nCol);
C_LZY_API(LPTSTR,GetFontName)(LONG sheet, LONG nRow, LONG nCol);
C_LZY_API(void,SetCurrentRangeFontSize)(LONG sheet, LONG nSize);
C_LZY_API(void,SetCurrentRangeFontName)(LONG sheet, LPTSTR ptrName, LONG bytChatSet);
C_LZY_API(LONG,GetGridLineStyle)(LONG sheet);
C_LZY_API(void,SetGridLineStyle)(LONG sheet,LONG style);
C_LZY_API(void,SetCurrentRangeBorderColor)(LONG sheet, LONG clr);
C_LZY_API(void,SetCurrentRangeFontItalic)(LONG sheet);
C_LZY_API(void,SetCurrentRangeFontBold)(LONG sheet);
C_LZY_API(void,SetCurrentRangeBorderLineStyle)(LONG sheet, LONG nStyle);
C_LZY_API(void,SetCurrentRangeForeColor)(LONG sheet, LONG clr);
C_LZY_API(void,SetCurrentRangeBkColor)(LONG sheet, LONG clr);
C_LZY_API(void,DeleteCurrentCol)(LONG sheet);
C_LZY_API(void,CutCurrentData)(LONG sheet);
C_LZY_API(void,InsertACol)(LONG sheet);
C_LZY_API(void,InsertARow)(LONG sheet);
C_LZY_API(void,DeleteCurrentRow)(LONG sheet);
C_LZY_API(void,PasteData)(LONG sheet);
C_LZY_API(void,CopyData)(LONG sheet);
C_LZY_API(BOOL,IsReadOnly)(LONG sheet);
C_LZY_API(void,SetReadOnly)(LONG sheet,BOOL val);
C_LZY_API(void,ClearCurrentRangeData)(LONG sheet);
C_LZY_API(void,ClearCellData)(LONG sheet, LONG nRow, LONG nCol);
C_LZY_API(LONG,GetCurrentSheet)(LONG book);
C_LZY_API(LONG,GetSheet)(LONG book, LONG nIndex);
C_LZY_API(BOOL,AttachWidow)(LONG rptHandle,HWND hWnd);
C_LZY_API(void,DeattachWindow)(LONG rptHandle);
C_LZY_API(BOOL,SaveBook)(LONG book, LPTSTR ptrName);
C_LZY_API(void,AppendACol)(LONG sheet);
C_LZY_API(void,AppendARow)(LONG sheet);
C_LZY_API(BOOL,LoadBook)(LONG book, LPTSTR ptrName);
C_LZY_API(BOOL,AddDrawItem)(LONG sheet,LPVOID ptrItem);
C_LZY_API(LONG,AddLinstener)(LONG sheet,LPVOID ptrObj,LONG msgID,BOOL bAddHeader);
C_LZY_API(BOOL,SetMessageFilter)(LONG sheet,LPVOID ptrFun);
C_LZY_API(BOOL,RemoveMessageFilter)(LONG sheet,LPVOID ptrFun);
C_LZY_API(void,SetFocusItem)(LONG sheet,LPVOID ptrItem);
C_LZY_API(LONG,NotifyMessage)(LONG sheet,LONG msgID,LPVOID param);
C_LZY_API(LONG,AddSheet)(LONG book, LPTSTR ptrName,LONG nIndex);
C_LZY_API(void,SetCurrentSheet)(LONG book, LONG nIndex);
C_LZY_API(void,SetRows)(LONG sheet,LONG irows);
C_LZY_API(LONG,GetRows)(LONG sheet);
C_LZY_API(void,SetCols)(LONG sheet,LONG icols);
C_LZY_API(LONG,GetCols)(LONG sheet);
C_LZY_API(void,SetFixedRows)(LONG sheet,LONG irows);
C_LZY_API(LONG,GetFixedRows)(LONG sheet);
C_LZY_API(void,SetFixedCols)(LONG sheet,LONG icols);
C_LZY_API(LONG,GetFixedCols)(LONG sheet);
C_LZY_API(void,SetFreezeRows)(LONG sheet,LONG irows);
C_LZY_API(LONG,GetFreezeRows)(LONG sheet);
C_LZY_API(void,SetFreezeCols)(LONG sheet,LONG icols);
C_LZY_API(LONG,GetFreezeCols)(LONG sheet);
C_LZY_API(void,BringDrawItemToFront)(LONG sheet,LPVOID ptrItem);
C_LZY_API(void,BringDrawItemToBack)(LONG sheet,LPVOID ptrItem);
C_LZY_API(void,BringDrawItemToTop)(LONG sheet,LPVOID ptrItem);
C_LZY_API(void,BringDrawItemToBottom)(LONG sheet,LPVOID ptrItem);
C_LZY_API(LPTSTR,GetTextMatrix)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetTextMatrix)(LONG sheet,LONG irow,LONG icol,LPTSTR ptrTxt);
C_LZY_API(LONG,GetRowHeight)(LONG sheet,LONG irow);
C_LZY_API(void,SetRowHeight)(LONG sheet,LONG irow,LONG vheight);
C_LZY_API(LONG,GetColWidth)(LONG sheet,LONG icol);
C_LZY_API(void,SetColWidth)(LONG sheet,LONG icol,LONG vwidth);
C_LZY_API(BOOL,PrintBook)(LONG book, BOOL bPrintAll);
C_LZY_API(BOOL,MergeRange)(LONG sheet,LONG rowBegin,
						 LONG colBegin,LONG rowEnd,LONG colEnd);
C_LZY_API(BOOL,RemoveMergeRange)(LONG sheet,LONG rowBegin,
							   LONG colBegin,LONG rowEnd,LONG colEnd);
C_LZY_API(LONG,GetBorderStyle)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetBorderStyle)(LONG sheet,LONG irow,LONG icol,LONG style);
C_LZY_API(BOOL,MergeCurrentRange)(LONG sheet,LONG nType);
C_LZY_API(BOOL,UnMergeCurrentRange)(LONG sheet);
C_LZY_API(BOOL,isHorzAlignPos)(LONG sheet,LONG irow,LONG icol,enum_horz_align pos);
C_LZY_API(BOOL,isVertAlignPos)(LONG sheet,LONG irow,LONG icol,enum_vert_align pos);
C_LZY_API(void,setRangeHorzAlignPos)(LONG sheet,RANGE& range,enum_horz_align pos);
C_LZY_API(void,setRangeVertAlignPos)(LONG sheet,RANGE& range,enum_vert_align pos);
C_LZY_API(void,setHorzAlignPos)(LONG sheet,LONG irow,LONG icol,enum_horz_align pos);
C_LZY_API(void,setVertAlignPos)(LONG sheet,LONG irow,LONG icol,enum_vert_align pos);
C_LZY_API(BOOL,IsFontUnderline)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetCurrentRangeFontUnderLine)(LONG sheet);
C_LZY_API(BOOL,IsFontBold)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(BOOL,IsFontItalic)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(LONG,GetCellForeColor)(LONG sheet,CELL cell);
C_LZY_API(LONG,GetCellBkColor)(LONG sheet,CELL cell);
C_LZY_API(LONG,GetCellBorderColor)(LONG sheet,CELL cell);
C_LZY_API(LONG,GetCurrentSheetIndex)(LONG book);
C_LZY_API(LONG,GetSheetCount)(LONG book);
C_LZY_API(void,DeleteSheet)(LONG book,LONG nIndex);
C_LZY_API(LPTSTR,GetSheetCaption)(LONG book,LONG index);
C_LZY_API(void,SetSheetCaption)(LONG book,LONG index,LPTSTR ptrTxt);
C_LZY_API(LPTSTR,GetCellMemo)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetCellMemo)(LONG sheet,LONG irow,LONG icol,LPTSTR ptrMemo);
C_LZY_API(LONG,GetBorderLineDot)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetBorderLineDot)(LONG sheet,LONG style);
C_LZY_API(LONG,GetCashStyle)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(void,SetCashStyle)(LONG sheet,LONG style);
C_LZY_API(void,SetFreeAreaSize)(LONG sheet,const SIZE& size,LONG nFreeID);
#ifndef STATIC_LINK
}
#endif
C_LZY_API(LONG,GetFocusRow)(LONG sheet);
C_LZY_API(LONG,GetFocusCol)(LONG sheet);
C_LZY_API(LONG,GetBorderLineStyle)(LONG sheet,LONG irow,LONG icol);
C_LZY_API(LONG,GetCurrentCellBkColor)(LONG sheet);
C_LZY_API(LONG,GetCurrentCellForeColor)(LONG sheet);
C_LZY_API(LONG,GetCurrentCellBorderColor)(LONG sheet);
C_LZY_API(LONG,GetIsAlignBottom)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(LONG,GetIsAlignTop)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(LONG,GetIsAlignMiddle)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(LONG,GetIsAlignLeft)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(LONG,GetIsAlignCenter)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(LONG,GetIsAlignRight)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(void,SetCurrentRangeFontVertAlign)(LONG sheet,_tag_Vert_Align value);
C_LZY_API(void,SetCurrentRangeFontHorzAlign)(LONG sheet,_tag_Horz_Align value);
C_LZY_API(BOOL,GetIsFontBold)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(BOOL,GetIsFontItalic)(LONG sheet,LONG iRow,LONG iCol);
C_LZY_API(void,SetCurrentRangeFontUnderline)(LONG sheet);
C_LZY_API(BOOL,GetIsFontUnderline)(LONG sheet,LONG iRow,LONG iCol);

#endif