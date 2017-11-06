//////////////////////////////////////////////////////////////////////
//@模块		 ：艺术字对象定义
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFONT_H__32C146CB_1675_4C97_A764_4F51444A575D__INCLUDED_)
#define AFX_LFONT_H__32C146CB_1675_4C97_A764_4F51444A575D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define FILLTYPE_SOLID	0
#define FILLTYPE_1COLOR	1
#define FILLTYPE_2COLOR	2
#include "LSerial.h"
#define ahNORMAL	0
#define ahLEFT		1
#define ahCENTER	2
#define ahRIGHT		3
#define ahFILL		4

#define avTOP		0
#define avCENTER	1
#define avBOTTOM	2
#define avFILL		3

#define adHORIZONTAL	0
#define adVERTICAL	1
#define adLEFT		2
#define adRIGHT		3

/** 对齐结构 */
typedef struct _tagALIGNMENT
{

	BYTE bAlignHorz	:3;
	BYTE bAlignVert	:3;
	BYTE bDirection	:2;
	_tagALIGNMENT(){
		bAlignHorz=ahLEFT;
		bAlignVert=avBOTTOM;
		bDirection=adHORIZONTAL;
	}
	void operator = (const _tagALIGNMENT& alignment){
		bAlignHorz=alignment.bAlignHorz;
		bAlignVert=alignment.bAlignVert;
		bDirection=alignment.bDirection;
	}
	BOOL operator ==(const _tagALIGNMENT& alignment) const
	{ return bAlignHorz == alignment.bAlignHorz && bAlignVert == alignment.bAlignVert &&
		bDirection == alignment.bDirection; }
	
	BYTE getValue(){
		return (BYTE)(((BYTE)bAlignHorz<<5) 
			| (((BYTE)bAlignVert<<2) & 0x1C) 
			| (BYTE)bDirection);
	}
	void setValue(BYTE byt){
		bAlignHorz=((byt&0xE0)>>5);
		bAlignVert=((byt&0x1C)>>2);
		bDirection=(byt&0x03);
	}
} ALIGNMENT;

/**
 * 填充颜色结构
 */
typedef struct tagFILLCOLOR
{
  tagFILLCOLOR() : bFillType(0), crParam1(0x00000000), bParam1(0), bParam2(0), bParam3(0)
  { }
  BYTE bFillType;
  /** 填充色 */
  COLORREF crParam1;
  BYTE bParam1;
  BYTE bParam2;
  BYTE bParam3;
  BOOL OnSerial(CLSerial& ar){
	  if(ar.isLoading()){
			ar>>bFillType;
			ar>>crParam1;
			ar>>bParam1;
			ar>>bParam2;
			ar>>bParam3;
	  }else{
			ar<<bFillType;
			ar<<crParam1;
			ar<<bParam1;
			ar<<bParam2;
			ar<<bParam3;
	  }
	  return TRUE;
  }
} FILLCOLOR;

#define ARTSHAPE_NOART	0

class EXPORT_G_CLASS CLFont
{
public:
	LOGFONT m_lf;	//逻辑字体对象
	COLORREF m_clr;	//
	BYTE m_bytArtStyle;	//艺术字形	
	FILLCOLOR m_clrFill;	
	/** 边线颜色 */
	COLORREF m_clrLine;
	/** 字形参数1 */
	BYTE m_bytArtParam1;
	/** 字形参数2 */	
	BYTE m_bytArtParam2;
	/** 阴影 */	
	BYTE m_bytShadow;	
	ALIGNMENT	m_Alignment;
	CLFont();
	CLFont(const CLFont& rArtFont)
	{ *this = rArtFont; }
	virtual ~CLFont();
	
	void DrawText(HDC hDC, RECT rect, LPTSTR pStr,
		UINT nFormat = 0) const;
	const CLFont& operator=(const CLFont& rFont);
	BOOL operator==(const CLFont& rFont) const;
	BOOL OnSerial(CLSerial& ar);
	void ClearToDefault();
private:
	BOOL isMuiltLine(LPTSTR strSrc,LONG charWid,
		LONG charHei,RECT& rct,LONG& totHei) const;
	void DrawTextNomal(HDC hDC, RECT rect, LPTSTR pStr,
		UINT nFormat = 0) const;
	/** 着色 */
	BOOL RenderText(HDC hDC, LPPOINT lpPoints, LPBYTE lpTypes, int iNumPts) const;
	/** 根据提供的位置和画线方法画出轮廓(空心字) */
	BOOL PolyDraw95(HDC hDC, CONST LPPOINT lppt, CONST LPBYTE lpbTypes, int cCount) const;
	/** 艺术变形 */
	void PointsArt(LPPOINT lppt, int nCount) const;
	RECT GetPointsRect(CONST LPPOINT lppt, int nCount) const;
	//变形
	void RotateArt1(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt2(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt3(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt4(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt5(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt6(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt7(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt8(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt9(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt10(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt11(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt12(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt13(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt14(LPPOINT lppt, int nCount, RECT& rect) const;
	void RotateArt15(LPPOINT lppt, int nCount, RECT& rect) const;
	//阴影
	void PointsShadow(LPPOINT lppt, int nCount) const;
	void PointsShadow1(LPPOINT lppt, int nCount) const;
	void PointsShadow2(LPPOINT lppt, int nCount) const;
	void PointsShadow3(LPPOINT lppt, int nCount) const;
	void PointsShadow4(LPPOINT lppt, int nCount) const;
	
	
};
#endif // !defined(AFX_LFONT_H__32C146CB_1675_4C97_A764_4F51444A575D__INCLUDED_)
