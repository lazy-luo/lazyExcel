//////////////////////////////////////////////////////////////////////
//@模块	:		TableArea类
//@作者	:		罗智勇
//@创建时间:	2005-11-08
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTABAREA_H__66C075AE_6AB1_4CE7_B6FA_EB937DA3D382__INCLUDED_)
#define AFX_LTABAREA_H__66C075AE_6AB1_4CE7_B6FA_EB937DA3D382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../LComm/LCommBase.h"
#include "../LComm/LMap.h"
#include "../LComm/LFont.h"
class CLPageItem
{
private:
	LPTSTR	m_ptrCaption;
	LPVOID	m_ptrData;
public:
	CLPageItem():m_ptrCaption(NULL),m_ptrData(NULL){}
	~CLPageItem(){
		if(m_ptrCaption)
			delete[] m_ptrCaption;
	}
	LPVOID	GetData(){return m_ptrData;}
	void	SetData(LPVOID pVal){m_ptrData=pVal;}
	LPTSTR  GetCaption(){return m_ptrCaption;}
	void	SetCaption(LPTSTR  ptr){
		if(m_ptrCaption)
			delete[] m_ptrCaption;
		m_ptrCaption=NULL;
		if(ptr){
			LONG nLen=strlen(ptr);
			m_ptrCaption=new char[nLen+1];
			strcpy(m_ptrCaption,ptr);
		}
	}
	void ClearToDefault(){
		SetData(NULL);
		SetCaption(NULL);
	}
	__inline void operator =(CLPageItem* ptrItem)
	{
		ASSERT(ptrItem!=NULL);
		SetData(ptrItem->GetData());
		SetCaption(ptrItem->GetCaption());
	}
	__inline void operator =(CLPageItem& ptrItem)
	{
		operator =(&ptrItem);
	}
};
#define MAP_PAGEITEM	LMap<INDEX,INDEX&,CLPageItem,CLPageItem&>
class CLTabArea : public MAP_PAGEITEM ,public IMouseEvent
{
public:
	void SetBeginPos(const POINT & pt);
	void isVisible(BOOL bVal);
	
	BOOL OnSerial(CLSerial& ar);
	LONG GetPageCount();
	LPVOID GetValue(LPVOID nVal);
	void SetFocusForeColor(COLORREF clr);
	COLORREF GetFocusForeColor();
	void SetFocusBkColor(COLORREF clr);
	COLORREF GetFocusBkColor();
	void SetBorderColor(COLORREF clr);
	COLORREF GetBorderColor();
	void SetForeColor(COLORREF clr);
	COLORREF GetForeColor();
	void SetBkColor(COLORREF clr);
	COLORREF GetBkColor();
	void ScrollHorz(LONG nValue,BOOL bPixel=FALSE);
	LONG GetMaxPageNO();
	virtual void DrawPages(LPDRAWER lpDrawer);
	BOOL SetCurrentPageNO(LONG nVal);
	LONG GetCurrentPageNO();
	LPVOID GetPageData(LONG nIndex);
	void SetPageData(LONG nIndex,LPVOID ptrV);
	LPTSTR GetPageCaption(LONG nIndex);
	void SetPageCaption(LONG nIndex,LPTSTR ptrV);
	CLPageItem* GetPage(LONG nIndex);
	BOOL RemovePage(LONG nIndex);
	CLPageItem* AddPage(LPVOID ptrData,LONG nIndex);
	BOOL isVisible();

	//鼠标回调事件
	virtual void OnMouseMove(LONG idArea,MOUSESTATUS& nstatus);
	virtual void OnMouseOut(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnLButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnRButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnRButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMButtonUp(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMouseWheel(LONG idArea,const MOUSESTATUS& nstatus);
	virtual BOOL GetRect(LONG idArea,RECT& rct);
	virtual BOOL GetRgn(LONG idArea,HRGN& hrgn);
	virtual LPIDAREA GetAreaIDs();
	virtual BOOL IsActive(){return isVisible();};
	/////////////////////////////////////////////////////////////////////
	
	void ReDraw(BOOL bAll);
	void SetRedrawHelp(IRedrawHelp* ptrDrawHelp);
	void SetSplictOwner(ISplictFace* ptrSplict);
	CLTabArea();
	virtual ~CLTabArea();
	
private:
	void MoveOffset(LONG nValue);
	void SetCurrentPage(LONG nIndex);
	void SetFitLastPage(LONG index);
	void GetItemTopLine(LONG nIndex,RECT& rct);
	void ResetBeginOfLeft();
	BOOL m_bChangePage;
	LONG m_nBeginColWidth;
	LONG GetTableIndex(POINT& pt);
	void GetFocusTopLine(RECT& rct);
	void Test();
	void DrawAItem(const DRAWER& cellDrawer,const POINT* pt,LONG nPtCount,RECT& rctTxt,
		LPTSTR ptrTxt,BOOL bFocus=FALSE);
	LONG GetItemLength(LONG nIndex);
	LONG GetItemBeginLeft(LONG nIndex);
	BOOL GetRegionPoints(LONG nIndex,RECT& clipRct,
		LONG& itemLen,POINT* pt,LONG& nLen,BOOL& bFocus);

	static LONG GetTextWidth(LPTSTR ptrTxt);
	void DrawSplitArea(const DRAWER& cellDrawer);
	void DrawBtArea(const DRAWER& cellDrawer);
	void DrawClient(const DRAWER& cellDrawer);
	void GetSplitRect(const RECT& rctClip,RECT&rct);
	void GetBtAreaRect(const RECT& rctClip,RECT& rct);
	BOOL isEmptyRect(const RECT& rct);
	void GetClientRect(const RECT& rctClip,RECT& rct);
	void GetBeginPagePos(POINT& pt);
	void RefreshStatus(const RECT& rctAll);
	BOOL ReplaceValue(LONG indexSrc,LONG indexDst);
	void MovePageToB(LONG nbeginIndex,LONG endIndex);
	void MovePageToF(LONG beginIndex,LONG nendIndex);
	
	BOOL	m_bFitLeft;	
	LONG	m_nLeftBeginCol;
	LONG	m_nRightEndCol;
	LONG	m_nBeginLeft;	//起始列开始位置
	LONG	m_nBeginRight;	//最后一列开始位置
	CLFont	m_Font;
	BOOL	m_bHasSp;	//是否右边有分隔条
	BOOL m_nPageCount;
	BOOL m_bVisible;
	POINT	m_ptTrack;
	POINT	m_posStart;
	POINT	m_posStartDraw;
	
	BOOL m_bEnablePre;
	BOOL m_bEnableFirst;
	BOOL m_bEnableNext;
	BOOL m_bEnableLast;
	
	BOOL m_bDownSplict;
	BOOL m_bDownPre;
	BOOL m_bDownFirst;
	BOOL m_bDownNext;
	BOOL m_bDownLast;
	
	BOOL m_bRaisePre;
	BOOL m_bRaiseFirst;
	BOOL m_bRaiseNext;
	BOOL m_bRaiseLast;
	

	LONG	m_nSplitWidth;
	LONG m_nCurrentPageNO;
	RECT	m_rectArea;
	RECT	m_rctClient;
	RECT	m_rctBtArea;
	RECT	m_rctSplit;
	COLORREF	m_clrBk;
	COLORREF	m_clrBkFocus;
	COLORREF	m_clrForeFocus;
	COLORREF	m_clrBorder;
	COLORREF	m_clrFore;

	SIZE		m_offSet;
	LPIDAREA		m_ptrArea;
	IRedrawHelp* m_ptrDrawHelp;
	ISplictFace* m_ptrSplict;
	void ClearAll();
};

#endif // !defined(AFX_LTABAREA_H__66C075AE_6AB1_4CE7_B6FA_EB937DA3D382__INCLUDED_)
