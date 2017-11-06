#if !defined(AFX_LCOLORPICKER_H__E60ADD9A_5C00_4DC5_8AC9_24C01DC429DD__INCLUDED_)
#define AFX_LCOLORPICKER_H__E60ADD9A_5C00_4DC5_8AC9_24C01DC429DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LColorPicker.h : header file
//
#include "LColorPan.h"
#include "LPickerBtn.h"
/////////////////////////////////////////////////////////////////////////////

class CLColorPicker : public CLPickerBtn
{
// Construction
public:
	COLORREF GetColor();
	void SetColor(COLORREF clr);
	CLColorPicker(LONG nDefault=0);
	virtual void OnPopup();
	virtual void OnDrawButton(CDC * pDC, CRect& rect);
	virtual ~CLColorPicker();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LCOLORPICKER_H__E60ADD9A_5C00_4DC5_8AC9_24C01DC429DD__INCLUDED_)
