// LToolTip.h: interface for the CLToolTip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTOOLTIP_H__4D782C57_3F1A_4B52_9B14_763D7952C66F__INCLUDED_)
#define AFX_LTOOLTIP_H__4D782C57_3F1A_4B52_9B14_763D7952C66F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BASE/LDrawItem.h"
#include "../Public/LGUIPublic.h"
#include "../Interface/LGUIInterface.h"
class GUI_EXPORT_CLASS CLToolTip : public CLDrawItemBase  
{
private:
	LPTSTR m_ptrMsg;
public:
	void SetMessage(LPTSTR ptrTxt);
	CLToolTip();
	virtual ~CLToolTip();
	virtual void OnDraw(LPHDC pDC,const RECT& rct);
};

#endif // !defined(AFX_LTOOLTIP_H__4D782C57_3F1A_4B52_9B14_763D7952C66F__INCLUDED_)
