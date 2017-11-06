//////////////////////////////////////////////////////////////////////
//@模块		 ：图形画板对象
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LCHARTPAN_H__47BAF930_0926_4A67_9E1D_CB05B2554B39__INCLUDED_)
#define AFX_LCHARTPAN_H__47BAF930_0926_4A67_9E1D_CB05B2554B39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Base/LDrawItem.h"
#include "../Public/LGUIPublic.h"
#include "../Interface/LGUIInterface.h"
class GUI_EXPORT_CLASS CLChartPan : public CLDrawItemBase  
{
public:
	CLChartPan();
	virtual ~CLChartPan();

};

#endif // !defined(AFX_LCHARTPAN_H__47BAF930_0926_4A67_9E1D_CB05B2554B39__INCLUDED_)
