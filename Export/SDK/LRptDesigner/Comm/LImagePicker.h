// LImagePicker.h: interface for the CLImagePicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LImagePICKER_H__80E3D4A0_1772_4324_9A7C_AF98C4AC4222__INCLUDED_)
#define AFX_LImagePICKER_H__80E3D4A0_1772_4324_9A7C_AF98C4AC4222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LPickerBtn.h"
#include "LImagePan.h"
class CLImagePicker : public CLPickerBtn  
{
public:
	BOOL Create(CRect rect, CWnd * pParentWnd, UINT nID,LONG nRow,
		LONG nCol,ImageTableEntry*	pBorders,LONG nBmpID=0);
	LONG GetCurrentValue();
	void SetCurrentValue(LONG nStyle);
	virtual void OnPopup();
	virtual void OnDrawButton(CDC * pDC, CRect& rect);
	
	CLImagePicker(LONG nDefaultLine=0);
	virtual ~CLImagePicker();
private:
	LONG GetArrIndexByValue(LONG nVal);
	LONG GetCurrentImageID();
	LONG GetIndex(LONG nImagID);
	ImageTableEntry *m_nBorders;
	LONG m_nRows;
	LONG m_nCols;
};

#endif // !defined(AFX_LImagePICKER_H__80E3D4A0_1772_4324_9A7C_AF98C4AC4222__INCLUDED_)
