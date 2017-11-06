//////////////////////////////////////////////////////////////////////
//@模块		 ：图片画板
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-11
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBITMAPPAN_H__48DE5517_CB44_4450_9366_A87F82E4CCF3__INCLUDED_)
#define AFX_LBITMAPPAN_H__48DE5517_CB44_4450_9366_A87F82E4CCF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Base/LDrawItem.h"
#include "../Public/LGUIPublic.h"
#include "../Interface/LGUIInterface.h"
class GUI_EXPORT_CLASS CLBitmapPan : public CLDrawItemBase  
{
private:
	void ClearBitmap();
	HBITMAP m_hBitmap;
	LPIDAREA m_pArea;
public:
	BOOL SetBitmap(LPTSTR ptrName);
	CLBitmapPan();
	virtual ~CLBitmapPan();
	virtual void OnLButtonDown(LONG idArea,const MOUSESTATUS& nstatus);
	virtual void OnMouseMove(LONG idArea,MOUSESTATUS& nstatus);
	virtual BOOL GetRect(LONG idArea,RECT& rct);
	virtual BOOL GetRgn(LONG idArea,HRGN& hrgn);
	virtual LPIDAREA GetAreaIDs();
	virtual BOOL IsActive(){return TRUE;};
	
	virtual void OnDraw(LPHDC pDC,const RECT& rct);
	
};

#endif // !defined(AFX_LBITMAPPAN_H__48DE5517_CB44_4450_9366_A87F82E4CCF3__INCLUDED_)
