//////////////////////////////////////////////////////////////////////
//@模块		 ：全局公用定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////
#ifndef _LGLOBALPARAM_H
#define _LGLOBALPARAM_H
#include "LGlobalDefine.h"
#include <math.h>
#include <new.h>
#ifdef _DEBUG
#ifndef ASSERT
#include <assert.h>
#define ASSERT(x) assert(x)
#endif
#else
#ifndef ASSERT
#define ASSERT(X)
#endif
#endif
//操作平台定义
//#define _LINUX_
#ifndef _WIN32
#define _WIN32
#endif

#ifdef _WIN32
#pragma warning(disable: 4390)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)
#pragma warning(disable: 4530)
#pragma warning(disable: 4244)
#endif

#ifndef interface
#define interface struct
#endif

#include "../LTableLib/Res/resource.h"
/*
#ifdef _LCOM_EXPORT_
#	include "../Export/Com/resource.h"
#else
#	ifndef RES_DEFINE
#		include "../resource.h"
#	else
		#define IDC_CUR_CROSS                   9001
		#define IDC_CUR_DROPPAN                 9002
		#define IDC_CURCROSS                    9003
		#define IDC_CURDOWN                     9004
		#define IDC_CURRIGHT                    9005
		#define IDC_CURSIZE_EW                  9006
		#define IDC_CURSIZE_NS                  9007
#	endif
#endif
*/

RES_MODULE_EXPORT extern HINSTANCE g_hInstance;

#if defined _LINK_DYN_TYPE_ && defined _WIN32 && !defined _LCOM_EXPORT_
#pragma comment(lib,"MSVCRT.LIB")
#endif

//是否跟踪绘图
//#define DEBUG_DRAW
//是否采用双缓冲
#define _LZY_USE_DOUBLE_BUFF_
//导出接口方式0-->SDK导出类  1-->SDK API  2-->COM对象
#if defined _LCOM_EXPORT_
#define _EXPORT_TYPE_		0
#else
#define _EXPORT_TYPE_		1
#endif

#define RET_MAP_NEW		2
#define RET_MAP_TRUE	1

#ifdef _LINK_DYN_TYPE_
#	if defined _GLOBAL_EXPORT_
#		define	EXPORT_G_CLASS	__declspec(dllexport)
#	else
#		define	EXPORT_G_CLASS	__declspec(dllimport)
#	endif
#else
#	define	EXPORT_G_CLASS 
#endif

//如果连编则注销此定义
#if defined _EXPORT_ADDIN_
	#if defined LGRIDBOOK_EXPORTS
		#define	_EXPORT_G_CLASS_	__declspec(dllexport)
	#else
		#define	_EXPORT_G_CLASS_	__declspec(dllimport)
	#endif
#else
	#define	_EXPORT_G_CLASS_
#endif

#include "LSerial.h"
#include <string>

#ifndef _START_
#ifdef _DEBUG
#define _DEBUG_MEM
#include "../MemDebug/LDebug.h"
#else
#define _START_(x)
#define _END_
#endif
#endif

#ifndef DOUBLE
#define DOUBLE	double
#endif

#define ABSTRACT	=0
#ifndef LZY_INLINE
#define LZY_INLINE inline
#endif
#define  MIN(a,b)		a>b?b:a
#define  MAX(a,b)		a>b?a:b

#define DLONG	__int64
#define MAKEALONG(a, b)      ((LONG)(((DWORD)(a)) | ((DWORD)((DWORD)(b))) << BITLEN(a)))

#define MAKEADLONG(nCol, nRow)      \
	((DLONG)(((DLONG)(nCol)) | ((DLONG)((DLONG)(nRow))) << (8*sizeof(LONG))))

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL                   0x020A
#endif
//
#define SELECT_NONE			0
#define SELECT_BY_ROW		1
#define	SELECT_BY_CELL		2
///

//单元格合并规则
#define MERGE_ALL			0
#define MERGE_ROW_ONLY		1
#define MERGE_COL_ONLY		2

#define		DEFAULT_COL_WIDTH	100
#define		DEFAULT_ROW_HEIGHT	20
typedef enum _tag_Drawer_Type{
	type_draw_client,
	type_draw_none_client,
	type_draw_all
}tag_Drawer_Type;
//单元格格式定义
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
///
#define DEFAULT_CELL_TYPE			0
#define CELL_NUMBER_FORMAT_DOT		1
#define CELL_NUMBER_FORMAT_PERCENT	2
#define CELL_NUMBER_FORMAT_MONEY	4

#define NO_CASH_STYLE				0
#define CELL_CASH_STYLE_HEAD		8/*金额单元*/
#define CELL_CASH_STYLE_BODY		16/*金额单元*/
#define  READ_ONLY					32

//集合默认值序号
#define DEFAULT_MAP_INDEX	-1
//单元格边框类型定义
#define DEFAULT_BORDER_STYLE	0
#define BORDER_STYLE_LEFT		1
#define BORDER_STYLE_RIGHT		4
#define BORDER_STYLE_TOP		2
#define BORDER_STYLE_BOTTOM		8
#define BORDER_STYLE_ALL		BORDER_STYLE_LEFT|BORDER_STYLE_RIGHT|BORDER_STYLE_TOP \
								|BORDER_STYLE_BOTTOM

#define BORDER_NO_LINE_DOT		0
#define BORDER_LEFT_LINE_DOT	1
#define BORDER_TOP_LINE_DOT		2
#define BORDER_RIGHT_LINE_DOT	4
#define BORDER_BOTTOM_LINE_DOT	8
#define BORDER_ALL_LINE_DOT		BORDER_LEFT_LINE_DOT | BORDER_TOP_LINE_DOT \
									|BORDER_RIGHT_LINE_DOT|BORDER_BOTTOM_LINE_DOT
//哈希表参数
#ifndef HASH_BIG_BLOCK_SIZE
#define		HASH_BIG_BLOCK_SIZE		80
#define		HASH_SMALL_BLOCK_SIZE	40
#define		HASH_BIG_ARR_SIZE		10949
#define		HASH_SMALL_ARR_SIZE		100
#endif
#define DEFAULT_CURSOR			0

#define TAB_SPLICT_WIDTH		6
//外观
#define STYLE_FLAT_LOOK	0
#define STYLE_3D_LOOK	1

#define		HITEST_OUT							0
#define		HITEST_TABAREA_SPLIT				22//Tab控件分隔条上
#define		HITEST_TABAREA_BUTTON				23//按钮区
#define		HITEST_TABAREA_CLIENT				24//客户区
#define		HITEST_TABAREA_FREE					25//自由区域


#define		AREA_ERROR		199
#define		AREA_OUTER		200
#define		AREA_TABLE		201
#define		AREA_CLIENT		202
#define		AREA_FIXED_RGN_HORZ	203
#define		AREA_FIXED_RGN_VERT	204
#define		AREA_FIXED_RGN_CROSS 205
#define		AREA_FREEZE_RGN	206
#define		AREA_TOTAL		207
#define		AREA_GRAPHICS	208
#define		AREA_IN_VERT_SPLICT_LINE	209
#define		AREA_IN_HORZ_SPLICT_LINE	210
#define		AREA_RANGE_BORDER		211
#define		AREA_RANGE_CORNER		212

////////////////////////
#define		GRID_LINE_DEFAULT					1
#define		GRID_NO_VERT_LINE					2
#define		GRID_NO_HORZ_LINE					4
#define		GRID_NO_LINE						GRID_NO_VERT_LINE | GRID_NO_HORZ_LINE


//绘图对象类型
#define		PAN_USER	0
#define		PAN_BITMAP	1
#define		PAN_CHART	2

//区域填充方式
#define STYLE_FILL_COPY		1 //数据块复制
#define STYLE_FILL_EQ_DEC	2 //等差填充
#define STYLE_FILL_EQ_MIUL  3 //等比填充
#define STYLE_FILL_SEQUENCE 4 //序列填充
/////
#define	FREE_AREA_TOP		1
#define FREE_AREA_LEFT		2
#define FREE_AREA_RIGHT		3
#define FREE_AREA_BOTTOM	4

//滚动条尺寸
#define INIT_LINK_VALUE	-1
#define MERGE_NONE		-1
#define SCROLLBAR_SIZE	16
//常量定义
#define ARROW_LEFT		1
#define ARROW_RIGHT		2
#define ARROW_UP		3
#define ARROW_DOWN		4

#define  CASHNAME "亿千百十万千百十亿千百十万千百十"\
					"亿千百十万千百十亿千百十万千百十亿千百十万千百十" \
					"亿千百十万千百十亿千百十万千百十亿千百十万千百十" \
					"亿千百十万千百十亿千百十万千百十亿千百十万千百十" \
					"亿千百十万千百十亿千百十万千百十元角分"

#define  COLOR_BKGRD		RGB(255,255,255)//报表背景色//GetSysColor(COLOR_INFOBK)
#define  COLOR_FOCUSBKGRD	GetSysColor(COLOR_HIGHLIGHT)//当前焦点单元(行)填充颜色
#define	 COLOR_FIXCOLUMNBK	GetSysColor(COLOR_BTNFACE)//RGB(192, 192, 192)//RGB(117,117,0)//固定单元填充背景色
#define  COLOR_FOREGRDFIXED	RGB(0,0,0)//固定单元前景色
#define  COLOR_FOREDATA		RGB(0,0,0)//数据前景色
#define  COLOR_BORDER		RGB(255,100,100)//边框颜色
#define  COLOR_GRIDLINE		RGB(190,190,190)//表体分隔线颜色
#define  COLOR_SCROLL_BAR	GetSysColor(COLOR_BTNFACE)//
#define  COLOR_FOCUSE_BORDER	RGB(0,0,0)
#define  COLOR_FOCUSE_FIXED_FORE	RGB(0,0,255)
#define  COLOR_CELL_BORDER_LINE	RGB(0,0,0)
#define  COLOR_RANGE_SEL	RGB(192,192,225)
#define  COLOR_GRID_BORDER	RGB(128,128,128)
#define  COLOR_FREEZE_LINE  RGB(64,64,64)
#define  COLOR_TOOL_TIP		GetSysColor(COLOR_INFOBK)

static LOGFONT DEFAULT_LOGFONT={-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 134, 3, 2, 1, 2, "宋体"};
//static LOGFONT VERSION_LOGFONT={-12, 0, 0, 0, FW_BOLD, 0, 0, 0, 134, 3, 2, 1, 2, "宋体"};

typedef enum _tag_Rect_Relative{
	R_SUB_RECT,R_PARENT_RECT,R_DIFF_RECT,
		R_COMBINABLE_RECT/*两个矩形可以合并*/,R_ERR_RECT
};

typedef struct tag_MouseStatus
{
	tag_MouseStatus():nButton(0),bIsLock(FALSE),posx(0),
		posy(0),nStatusParam(0),nParam(0){};
	INT  posx;
	INT  posy;
	LONG nStatusParam;
	LONG nParam;
	BYTE nButton;
	BOOL bMouseIN;
	BOOL bIsLock;	//当任何键按下没有释放时,锁定消息(任何时候只有一个对象获得锁)
	void operator =(const tag_MouseStatus& status){
		posx=status.posx;
		posy=status.posy;
		nStatusParam=status.nStatusParam;
		nParam=status.nParam;
		nButton=status.nButton;
		bMouseIN=status.bMouseIN;
		bIsLock=status.bIsLock;
	}
}MOUSESTATUS,*LPMOUSESTATUS;
typedef struct _tagCHAIN{
  LPVOID ptrData;
  _tagCHAIN* ptrNext;
  _tagCHAIN():ptrData(NULL),ptrNext(NULL){}
  ~_tagCHAIN(){
	if(ptrNext)
		delete ptrNext;
	ptrNext=NULL;
  }
  BOOL isEmpty(){
	return ptrData==NULL && ptrNext==NULL;
  }
}CHAIN,*LPCHAIN;
typedef struct _tagNODE{
	LPCHAIN m_pchain;
	_tagNODE():m_pchain(NULL){}
	~_tagNODE(){
		if(m_pchain)
			delete m_pchain;
		m_pchain=NULL;
	}
}NODE,*LPNODE;
typedef struct tag_IDArea{
  LONG lngID;
  BOOL bRect;
  tag_IDArea* ptrNext;
  tag_IDArea():lngID(0),ptrNext(NULL),bRect(TRUE){}
  ~tag_IDArea(){
	if(ptrNext)
		delete ptrNext;
  }
}IDAREA,*LPIDAREA;

typedef struct _tag_Drawer
{
	_tag_Drawer():m_nUserProperty(0){}
	HDC m_hDC;
	LPRECT m_lpRect;
	COLORREF	m_clrLine;
	LONG		m_nUserProperty;	//用外传属性
	COLORREF	m_clrBk;		//背景
	COLORREF	m_clrFore;		//前景
	LONG		m_nStyle;
	LONG		m_nRowStyle;
	LONG		m_nColStyle;
}DRAWER,*LPDRAWER;


//定义绘图句柄对象
typedef struct _tagHDCH
{
	_tagHDCH():hDC(NULL),bIsPrint(FALSE),pParam(NULL),bPrintFixed(TRUE){}
	HDC hDC;
	BOOL bIsPrint;
	BOOL bPrintFixed;
	LPVOID	pParam;
}HDCH,*LPHDC;
//鼠标测试结构
typedef struct _tag_Hitest
{
	_tag_Hitest():nHitest(HITEST_OUT),
		nRow(-1),nCol(-1),nValue(0),nButton(0),nUserData(0){}
	LONG	nHitest;
	LONG	nRow;
	LONG	nCol;
	LONG	nValue;
	LONG	nButton;
	LONG	nUserData;//用户自定义
	RECT	m_Rect;
	void reset(){
		nHitest=HITEST_OUT;
		nRow=-1;
		nCol=-1;
		nValue=0;
		nButton=0;
		m_Rect.left=0;
		m_Rect.top=0;
		m_Rect.right=0;
		m_Rect.bottom=0;
		nUserData=0;
	}
	_tag_Hitest& operator =(const _tag_Hitest& dst){
		if(this!=&dst){
			nHitest=dst.nHitest;
			nRow=dst.nRow;
			nCol=dst.nCol;
			nValue=dst.nValue;
			nButton=dst.nButton;
			m_Rect=dst.m_Rect;
			nUserData=dst.nUserData;
		}
		return *this;
	}
}HITEST,*LPHITEST;
//滚动条信息结构
typedef struct  _tagSCROLLINFOEXT
{
	DLONG	m_nMaxValue;//滚动最大范围
	DLONG	m_nExistValue;//适口范围粒度
	DLONG	m_nCurrValue;//当前滚动条值
	BOOL	m_bVisible;	//是否显示滚动条
	LONG	m_nVirtualValue;//
	_tagSCROLLINFOEXT():m_nMaxValue(0),m_nExistValue(0),m_nVirtualValue(0)
		,m_nCurrValue(0),m_bVisible(FALSE){}
	BOOL OnSerial(CLSerial& ar){
		if(ar.isLoading()){
			ar>>m_nMaxValue;
			ar>>m_nExistValue;
			ar>>m_nCurrValue;
			ar>>m_bVisible;
			ar>>m_nVirtualValue;
		}else{
			ar<<m_nMaxValue;
			ar<<m_nExistValue;
			ar<<m_nCurrValue;
			ar<<m_bVisible;
			ar<<m_nVirtualValue;
		}
		return TRUE;
	}
}SCROLLINFOEXT,*LPSCROLLINFOEXT;
//序号结构对象
typedef struct  _tagINDEX
{
	//序号
	LONG Index;
	BOOL operator==(const _tagINDEX& filed) const
		{ return Index == filed.Index ; }
	operator DLONG() { return (DLONG)Index; }

}INDEX,*LPINDEX;
//单元格结构对象
typedef struct _tagCELL
{
	LONG Col;
	LONG Row;
	BOOL operator==(const _tagCELL& cell) const
		{ return Col == cell.Col && Row == cell.Row ; }
	operator DLONG() { return MAKEADLONG(Col,Row); }
	void operator =(const _tagCELL& cell){
		Col=cell.Col;
		Row=cell.Row;
	}
	BOOL OnSerial(CLSerial& ar){
		if(ar.isLoading()){
			ar>>Row;
			ar>>Col;
		}else{
			ar<<Row;
			ar<<Col;
		}
		return TRUE;
	}
	_tagCELL(LONG row,LONG col):Row(row),Col(col){}
	_tagCELL():Row(0),Col(0){}
}CELL,*LPCELL;

typedef struct _tagPOS
{
	LONG m_begin;
	LONG m_end;
	_tagPOS():m_begin(-1),m_end(-1){};
	BOOL isEmpty() const{
		return (m_begin==-1 || m_end==-1);
	}
	void SetPos(LONG val1,LONG val2){
		m_begin=(val1>val2?val2:val1);
		m_end=(val1<val2?val2:val1);
	}
	BOOL operator ==(const _tagPOS& pos) const{
		return (m_begin==pos.m_begin && m_end==pos.m_end);
	}
	void operator =(const _tagPOS& pos){
		m_begin=pos.m_begin;
		m_end=pos.m_end;
	}
	BOOL OnSerial(CLSerial& ar){
		if(ar.isLoading()){
			ar>>m_begin;
			ar>>m_end;
		}else{
			ar<<m_begin;
			ar<<m_end;
		}
		return TRUE;
	}
}POS,*LPPOS;
//范围对象结构
typedef struct _tagRANGE
{
public:
	POS m_posRow;
	POS m_posCol;
	BOOL isEmpty() const{
		return (m_posRow.isEmpty() || m_posCol.isEmpty());
	}
	BOOL isCellInRange(LONG irow,LONG icol){
		if(isEmpty())return FALSE;
		return (irow>=m_posRow.m_begin && irow<=m_posRow.m_end 
			&& icol>=m_posCol.m_begin && icol<=m_posCol.m_end);
	}
	void CombinRange(_tagRANGE& range){
		if(range.isEmpty())return;
		if(m_posCol.m_begin>range.m_posCol.m_begin)
			m_posCol.m_begin=range.m_posCol.m_begin;
		if(m_posCol.m_end<range.m_posCol.m_end)
			m_posCol.m_end=range.m_posCol.m_end;
		if(m_posRow.m_begin>range.m_posRow.m_begin)
			m_posRow.m_begin=range.m_posRow.m_begin;
		if(m_posRow.m_end<range.m_posRow.m_end)
			m_posRow.m_end=range.m_posRow.m_end;
	}
	void AdjustRange(){
		LONG lngT;
		if(m_posRow.m_begin>m_posRow.m_end){
			lngT=m_posRow.m_begin;
			m_posRow.m_begin=m_posRow.m_end;
			m_posRow.m_end=lngT;
		}
		if(m_posCol.m_begin>m_posCol.m_end){
			lngT=m_posCol.m_begin;
			m_posCol.m_begin=m_posCol.m_end;
			m_posCol.m_end=lngT;
		}
	}
	BOOL GetRangeRect(RECT& rct){
		if(isEmpty())return FALSE;
		rct.left=m_posCol.m_begin;
		rct.top=m_posRow.m_begin;
		rct.right=m_posCol.m_end;
		rct.bottom=m_posRow.m_end;
		return TRUE;
	}
	void SetRangeRect(const RECT& rct){
		m_posRow.SetPos(rct.top,rct.bottom);
		m_posCol.SetPos(rct.left,rct.right);
	}
	//是否是单元范围
	BOOL isSingleCellRange(){
		return (!isEmpty() && 
			m_posRow.m_begin==m_posRow.m_end && m_posCol.m_begin==m_posCol.m_end);
	}
	BOOL operator ==(const _tagRANGE& range) const{
		return (m_posRow==range.m_posRow && m_posCol==range.m_posCol);
	}
	void operator =(const _tagRANGE& range){
		m_posRow=range.m_posRow;
		m_posCol=range.m_posCol;
	}
	BOOL OnSerial(CLSerial& ar){
		m_posRow.OnSerial(ar);
		m_posCol.OnSerial(ar);
		return TRUE;
	}
	void ClearRange(){
		m_posRow.m_begin=m_posRow.m_end=-1;
		m_posCol.m_begin=m_posCol.m_end=-1;
	}
	void SetSingleCellRange(const CELL& cell){
		m_posRow.m_begin=m_posRow.m_end=cell.Row;
		m_posCol.m_begin=m_posCol.m_end=cell.Col;
	}
}RANGE,*LPRANGE;



typedef struct tag_ColChain
{
	tag_ColChain():ptrData(NULL),ptrNext(NULL){}
	LPTSTR		ptrData;
	tag_ColChain* ptrNext;
	void setText(LPTSTR ptr){
		if(ptrData){
			delete ptrData;
			ptrData=NULL;
		}
		if(ptr){
			LONG nLen=strlen(ptr)+1;
			ptrData=new char[nLen];
			memcpy(ptrData,ptr,nLen);
		}
	}
	~tag_ColChain(){
		if(ptrData)
			delete[] ptrData;
		if(ptrNext){
			delete ptrNext;
			ptrNext=NULL;
		}
	}

}COLCHAIN,*LPCOLCHAIN;
typedef struct tag_RowChain
{
	tag_RowChain():ptrCol(NULL),ptrNext(NULL){}
	LPCOLCHAIN	ptrCol;
	tag_RowChain* ptrNext;
	~tag_RowChain(){
		if(ptrCol)
			delete ptrCol;
		if(ptrNext){
			delete ptrNext;
			ptrNext=NULL;
		}
	}
}ROWCHAIN,*LPROWCHAIN;

typedef struct tag_ValueLink
{
	tag_ValueLink():nValue(INIT_LINK_VALUE),ptrNext(NULL){}
	LONG	nValue;
	tag_ValueLink* ptrNext;
	void SubLink(tag_ValueLink& link){
		
	}
	void SubLink(tag_ValueLink* plink){
		if(plink)
			SubLink(*plink);
	}
	BOOL isExist(LONG nVal){
		if(nVal==nValue){
			return TRUE;
		}else{
			if(ptrNext){
				return ptrNext->isExist(nVal);
			}else
				return FALSE;
		}
	}
	~tag_ValueLink(){
		if(ptrNext)
			delete ptrNext;
		ptrNext=NULL;
	}
}VALUE_LINK,*LPVALUELINK;

typedef struct _tag_CellDrawerParam
{
	_tag_CellDrawerParam():bMergeCell(FALSE){};
	BOOL	bMergeCell;
	RANGE	rangeMerge;
	LONG	nparam;
	void operator =(const _tag_CellDrawerParam& param){
		bMergeCell=param.nparam;
		rangeMerge=param.rangeMerge;
		nparam=param.nparam;
	}
}CELLPARAM,*LPCELLPARAM;
typedef struct _tag_CellItemDrawer
{
	CELLPARAM	cellParam;
	CELL		m_cell;
	HDC m_hDC;
	BOOL		bIsPrint;
	LPRECT m_lpRect;
	_tag_CellItemDrawer():bIsPrint(NULL),m_lpRect(NULL){
		
	}
	void operator =(const _tag_CellItemDrawer& draw){
		cellParam=draw.cellParam;
		m_cell=draw.m_cell;
		m_hDC=draw.m_hDC;
		m_lpRect=draw.m_lpRect;
		bIsPrint=draw.bIsPrint;
	}
}CELLITEMDRAWER,*LPCELLITEMDRAWER;

#endif