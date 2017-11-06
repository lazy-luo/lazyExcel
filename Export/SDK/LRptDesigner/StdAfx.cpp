// stdafx.cpp : source file that includes just the standard includes
//	LRptDesigner.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
extern CFont* m_pDefaultFont=NULL; 
C_LZY_API(LONG,GetFocusRow)(LONG sheet){
	CELL cell;
	GetCurrentCell(sheet,cell);
	return cell.Row;
}
C_LZY_API(LONG,GetFocusCol)(LONG sheet){
	CELL cell;
	GetCurrentCell(sheet,cell);
	return cell.Col;
}
C_LZY_API(LONG,GetBorderLineStyle)(LONG sheet,LONG irow,LONG icol){
	return GetBorderStyle(sheet,irow,icol);
}
C_LZY_API(LONG,GetCurrentCellBkColor)(LONG sheet){
	CELL cell;
	GetCurrentCell(sheet,cell);
	return GetCellBkColor(sheet,cell);
}
C_LZY_API(LONG,GetCurrentCellForeColor)(LONG sheet){
	CELL cell;
	GetCurrentCell(sheet,cell);
	return GetCellForeColor(sheet,cell);
}
C_LZY_API(LONG,GetCurrentCellBorderColor)(LONG sheet){
	CELL cell;
	GetCurrentCell(sheet,cell);
	return GetCellBorderColor(sheet,cell);
}
C_LZY_API(LONG,GetIsAlignBottom)(LONG sheet,LONG iRow,LONG iCol){
	return isVertAlignPos(sheet,iRow,iCol,vert_align_bottom);
}
C_LZY_API(LONG,GetIsAlignTop)(LONG sheet,LONG iRow,LONG iCol){
	return isVertAlignPos(sheet,iRow,iCol,vert_align_top);
}
C_LZY_API(LONG,GetIsAlignMiddle)(LONG sheet,LONG iRow,LONG iCol){
	return isVertAlignPos(sheet,iRow,iCol,vert_align_middle);
}
C_LZY_API(LONG,GetIsAlignLeft)(LONG sheet,LONG iRow,LONG iCol){
	return isHorzAlignPos(sheet,iRow,iCol,horz_align_left);
}
C_LZY_API(LONG,GetIsAlignCenter)(LONG sheet,LONG iRow,LONG iCol){
	return isHorzAlignPos(sheet,iRow,iCol,horz_align_center);
}
C_LZY_API(LONG,GetIsAlignRight)(LONG sheet,LONG iRow,LONG iCol){
	return isHorzAlignPos(sheet,iRow,iCol,horz_align_right);
}
C_LZY_API(void,SetCurrentRangeFontVertAlign)(LONG sheet,_tag_Vert_Align value){
	RANGE range;
	GetCurrentRange(sheet,range);
	setRangeVertAlignPos(sheet,range,value);
}
C_LZY_API(void,SetCurrentRangeFontHorzAlign)(LONG sheet,_tag_Horz_Align value){
	RANGE range;
	GetCurrentRange(sheet,range);
	
	setRangeHorzAlignPos(sheet,range,value);
}
C_LZY_API(BOOL,GetIsFontBold)(LONG sheet,LONG iRow,LONG iCol){
	return IsFontBold(sheet,iRow,iCol);
}
C_LZY_API(BOOL,GetIsFontItalic)(LONG sheet,LONG iRow,LONG iCol){
	return IsFontItalic(sheet,iRow,iCol);
}
C_LZY_API(void,SetCurrentRangeFontUnderline)(LONG sheet){
	SetCurrentRangeFontUnderLine(sheet);
}
C_LZY_API(BOOL,GetIsFontUnderline)(LONG sheet,LONG iRow,LONG iCol){
	return IsFontUnderline(sheet,iRow,iCol);
}
#ifdef STATIC_LINK
	HINSTANCE g_hInstance=NULL;
	#include "../../../LComm/LGlobalParam.h"
	#include "../../../LGUILib/Base/LDrawItem.cpp"
	#include "../../../LGUILib/Src/LScrollBar.cpp"
	
	#include "../../../OSFace/Win32/InterLink/LRptGrid.cpp"
	#include "../../../OSFace/Win32/InterLink/InplaceCtrl/LEditCtrl.cpp"
	#include "../../../Src/LBook.cpp"
	#include "../../../Base/LTabArea.cpp"
	
	#include "../../SDK/LExport.cpp"
	#include "../../../Public/LBookLink.h"
#endif