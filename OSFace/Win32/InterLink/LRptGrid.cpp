//////////////////////////////////////////////////////////////////////
//@模块		 ：报表对象平台相关接口实现(WIN32)
//@版本		 ：v1.0.0
//@作者		 ：罗智勇
//@时间		 ：2005-11-01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LRptGrid.h"
#ifdef DEBUG_DRAW
long m_cellCount=0;
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern EXPORT_G_CLASS CLMouseEventMgrl	g_nMouseEventMgrl;
#define RPT_PROPERTY_ID	"_sfdkslf:zy^*^(_*_lzy_"
CLRptGrid::CLRptGrid():m_hWnd(NULL),m_pOldProc(0),m_pTimerLsner(NULL)
	,m_ptrCurrCtrl(NULL),m_ptrEdit(NULL),m_nCurrCtrlRow(-1),m_nCurrCtrlCol(-1)
{
	
}

CLRptGrid::~CLRptGrid()
{
	DeattachWindow();
	ClearInplaceCtrl();
	CLEAR_MOUSE_EVENT(m_hWnd)
}
BOOL CLRptGrid::AttachWidow(HWND hWnd)
{
	if(NULL!=GET_LINK((LONG)hWnd)){
		ASSERT(FALSE);
		return FALSE;
	}
	if(m_hWnd){
		DeattachWindow();
	}
	m_pOldProc=SetWindowLong(hWnd,GWL_WNDPROC,(LONG)WndProc);
	if(m_pOldProc!=0){
		m_hWnd=hWnd;
		::SetProp(m_hWnd,RPT_PROPERTY_ID,(HANDLE)this);
		m_book.SetRedrawHelp(this);
		m_book.SetPanKey((LONG)m_hWnd);
		g_nMouseEventMgrl.SetTimerCreator(this);

		InitInplaceCtrl();
	}
	return m_pOldProc!=0;
}
void CLRptGrid::DeattachWindow()
{
	if(m_hWnd && m_pOldProc!=0){
		SetWindowLong(m_hWnd,GWL_WNDPROC,m_pOldProc);
		::RemoveProp(m_hWnd,RPT_PROPERTY_ID);
		m_book.SetRedrawHelp(NULL);
	}
	//m_hWnd=NULL;
}
BOOL CLRptGrid::GetDC(HDCH& hDC)
{
	BOOL bret=FALSE;
	if(m_hWnd){
		hDC.hDC=::GetDC(m_hWnd);
		bret=TRUE;
	}
	return bret;
}
LRESULT CALLBACK CLRptGrid::WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	BOOL bCancel=FALSE;
	HDC hdc;
	CLRptGrid* ptrGrid=(CLRptGrid*)GetProp(hWnd,RPT_PROPERTY_ID);
	if(!ptrGrid){
		ASSERT(FALSE);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	switch(uMsg){
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
		return (LONG)SendMessage((HWND)lParam,LZY_MSG_CTLCOLOR,wParam,lParam);
	case WM_TIMER:
		if(ptrGrid->m_pTimerLsner)
			ptrGrid->m_pTimerLsner->OnTimerOut(wParam);
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		if(::GetUpdateRect(hWnd,NULL,FALSE)){
				hdc = BeginPaint(hWnd, &ps);
#ifdef DEBUG_DRAW
				m_cellCount++;
#endif
				RECT rct;
				GetClientRect(hWnd,&rct);			
				LONG offset=0;
				rct.left+=offset;
				rct.right-=offset;
				rct.top+=offset;
				rct.bottom-=offset;
				
				DRAWER cellDrawer;
				cellDrawer.m_hDC=hdc;
				cellDrawer.m_lpRect=&rct;
				cellDrawer.m_clrBk=RGB(192,192,192);
				cellDrawer.m_clrFore=RGB(0,0,255);			
				ptrGrid->GetBook()->OnDraw(&cellDrawer);
				
				EndPaint(hWnd, &ps);
				::ReleaseDC(hWnd,hdc);
		}
		
		//::ValidateRect(hWnd,NULL);
		return 0;
	case WM_MOUSEMOVE:
		{
			
			RECT rct;
			POINT pt,ptLT;
			GetCursorPos(&pt);
			GetClientRect(hWnd,&rct);
			ptLT.x=rct.left;
			ptLT.y=rct.top;
			ClientToScreen(hWnd,&ptLT);
			pt.x-=ptLT.x;
			pt.y-=ptLT.y;
			
			short Button=0 ;
			if(wParam & MK_LBUTTON )
				Button = 1;
			else if(wParam & MK_RBUTTON )
				Button = 2;
			else if(wParam & MK_MBUTTON )
				Button = 4;
			
			g_nMouseEventMgrl.OnMouseMove((LONG)hWnd,pt.x,pt.y,Button,bCancel);
			if(bCancel)return TRUE;
		}
		return 1;
		//break;
	case WM_LBUTTONDOWN:
		{
			/*触发一次鼠标移动事件先  :) */
			RECT rct;
			POINT pt,ptLT;
			GetCursorPos(&pt);
			GetClientRect(hWnd,&rct);
			ptLT.x=rct.left;
			ptLT.y=rct.top;
			ClientToScreen(hWnd,&ptLT);
			pt.x-=ptLT.x;
			pt.y-=ptLT.y;
			
			short Button=0 ;
			if(wParam & MK_LBUTTON )
				Button = 1;
			else if(wParam & MK_RBUTTON )
				Button = 2;
			else if(wParam & MK_MBUTTON )
				Button = 4;
			g_nMouseEventMgrl.OnMouseMove((LONG)hWnd,pt.x,pt.y,Button,bCancel);
		}
		SetCapture(hWnd);
		g_nMouseEventMgrl.OnLButtonDown((LONG)hWnd,wParam,lParam,bCancel);
		ptrGrid->HideInPlaceCtrl();
		if(bCancel)return 0;
		//return 0;
		break;
	case WM_LBUTTONUP:
#ifdef DEBUG_DRAW
		m_cellCount=0;
#endif
		ReleaseCapture();
		g_nMouseEventMgrl.OnLButtonUp((LONG)hWnd,wParam,lParam,bCancel);
		if(bCancel)return 0;
		//return 0;
		break;
	case WM_MOUSEWHEEL:
		//鼠标滚动支持
		g_nMouseEventMgrl.OnMouseWheel((LONG)hWnd,wParam,lParam,bCancel);
		if(bCancel)return 0;
		//return 0;
		break;
	case WM_LBUTTONDBLCLK:
		{
			BOOL bCancel=FALSE;
			ptrGrid->OnLDBClick(wParam,lParam,bCancel);
			if(bCancel)
				return 0;
		}
		//return 0;
		break;
	case WM_CHAR:
		ptrGrid->OnChar(wParam,lParam);
		break;
	case WM_KEYDOWN:
		{
			BOOL bCancel=FALSE;
			ptrGrid->OnKeyDown(wParam,lParam,bCancel);
			if(bCancel)
				return 0;
		}
		break;
	case WM_KEYUP:
		{
			BOOL bCancel=FALSE;
			ptrGrid->OnKeyUp(wParam,lParam,bCancel);
			if(bCancel)
				return 0;
		}
		break;
	case WM_CLOSE:
		//g_nMouseEventMgrl.ClearTimer();
		//ptrGrid->DeleteTimer();
		break;
	default:
		break;
	}
	return CallWindowProc((WNDPROC)ptrGrid->m_pOldProc,hWnd, uMsg, wParam, lParam);
}
void CLRptGrid::ReDraw(BOOL bAll)
{
	if(m_hWnd){
		::InvalidateRect(m_hWnd,NULL,FALSE);
	}
}

LONG CLRptGrid::CreateTimer(ITimerListener* ptrLsner,LONG uElapse,LONG nID)
{
	if(m_hWnd){
		m_pTimerLsner=ptrLsner;
		return ::SetTimer(m_hWnd,nID,uElapse,NULL);
	}else
		return 0;
}
BOOL CLRptGrid::DeleteTimer(LONG iTimer)
{
	if(m_hWnd){
		return ::KillTimer(m_hWnd,iTimer);
	}else
		return FALSE;
}
void CLRptGrid::OnLDBClick(LONG wParam,LONG lParam,BOOL& bCancel)
{
	//if(!m_bShowOver)return;
	short xPos = LOWORD(lParam);
	short yPos = HIWORD(lParam);
	POINT pt;
	pt.x=xPos;
	pt.y=yPos;	
	ISheet* pSheet=m_book.GetCurrentSheet();
	if(!pSheet)return;
	LONG pos=pSheet->GetMousePosition(pt);
	if(pos==AREA_CLIENT || pos==AREA_FREEZE_RGN){
		CLPlatform::SetCursor(IDC_CURCROSS);
		SetCurrentCtrl();
	}
}
void CLRptGrid::OnChar(LONG wParam,LONG lParam)
{
	//if(!m_bShowOver)return;
	switch(wParam){
	case VK_RETURN:
	case VK_TAB:
	case VK_ESCAPE:
		return;
	}
	SetCurrentCtrl();
	if(m_ptrCurrCtrl){
		m_ptrCurrCtrl->SendMessage(WM_CHAR,wParam,lParam);
	}
}
BOOL CLRptGrid::InitInplaceCtrl()
{
	if(m_ptrEdit==NULL)
		m_ptrEdit=new CLEditCtrl(m_hWnd);
	return TRUE;
}

void CLRptGrid::SetCurrentCtrl()
{
#define OFFSET	5
	if(m_ptrEdit){
		IGrid* ptrGrid=m_book.GetCurrentSheet()->GetGrid();
		if(!ptrGrid)return;
		ITable* ptrTable=ptrGrid->GetTable();
		if(!ptrTable)return;
		CELL cell;
		ptrTable->GetCurrentCell(cell);
		ptrGrid->GetMasterCell(cell);
		//自动适应
		ptrGrid->AutoAdjustPos(cell);

		CLCellItem* ptrItem=ptrTable->GetACell(cell);
		//if(!ptrItem)return;
		CLFont* ptrFont=ptrTable->GetCellFont(cell);
		if(!ptrFont)return;
		CLStyle* ptrStyle=ptrTable->GetCellStyle(cell);
		if(!ptrStyle || (ptrStyle && ptrStyle->ReadOnly()))
			return;//只读单元不能修改
		RECT rct,rctC;
		ptrGrid->GetCellRect(cell.Row,cell.Col,rctC,rct);
		
		rct.left+=(OFFSET-1);
		rct.top+=(OFFSET-1);
		rct.right-=OFFSET;
		rct.bottom-=OFFSET;

		m_nCurrCtrlRow=cell.Row;
		m_nCurrCtrlCol=cell.Col;
		
		m_ptrEdit->setBkColor(ptrStyle->GetBkColor());
		m_ptrEdit->SetForeColor(ptrFont->m_clr);
		m_ptrEdit->setPosition(rct.left,rct.top,rct.right,rct.bottom);
		//m_ptrEdit->setFont(m_hFontBody);
		
		m_ptrEdit->setStringValue(ptrItem?ptrItem->GetText():"");
		m_ptrCurrCtrl=m_ptrEdit;
	}
}
void CLRptGrid::OnKeyDown(LONG wParam,LONG lParam,BOOL& bCancel)
{
	//if(!m_bShowOver)return;
	ISheet* psheet=m_book.GetCurrentSheet();
	if(!psheet)return;
	IGrid* ptrGrid=psheet->GetGrid();
	if(!ptrGrid)return;
	ITable* ptrTable=ptrGrid->GetTable();
	if(!ptrTable)return;
	
	CELL cell,cellBegin,cellSize;
	ptrTable->GetCurrentCell(cell);
	ptrGrid->GetMasterCell(cell);
	bCancel=FALSE;
	cellSize.Col=ptrTable->GetCols();
	cellSize.Row=ptrTable->GetRows();
	cellBegin.Col=ptrTable->GetFixedCols()+ptrTable->GetFreezeCols();
	cellBegin.Row=ptrTable->GetFixedRows()+ptrTable->GetFreezeRows();
	switch( wParam ){
	case VK_DELETE:
		{
			bCancel=TRUE;
			CLDrawItemBase *ptrItem=psheet->GetFocusItem();
			if(ptrItem){
				psheet->DeleteDrawItem(ptrItem);
			}else{
				RANGE range;
				ptrTable->GetCurrentRange(range);
				ptrGrid->ClearRangeData(range);
			}
			ReDraw();
		}
		break;
	case VK_HOME:
		bCancel=TRUE;
		
		if(cell.Col>cellBegin.Col){
			HideInPlaceCtrl();
			cell.Col=cellBegin.Col;
			ReDraw();
		}
		break;
	case VK_END:
		bCancel=TRUE;
		if(cell.Col<cellSize.Col-1){
			HideInPlaceCtrl();
			cell.Col=cellSize.Col-1;
			ReDraw();
		}
		break;
	case VK_TAB:
	case VK_RIGHT:
		bCancel=TRUE;
		if(cell.Col<cellSize.Col-1){
			HideInPlaceCtrl();
			cell.Col=ptrGrid->GetNextCol(cell);
			ReDraw();
		}else{
			
		}
		break;
	case VK_LEFT:
		bCancel=TRUE;
		if(cell.Col>cellBegin.Col){
			HideInPlaceCtrl();
			cell.Col=ptrGrid->GetPrevCol(cell);
			ReDraw();
		}else{
			
		}
		break;
	case VK_UP:
		bCancel=TRUE;
		if(cell.Row>cellBegin.Row){
			HideInPlaceCtrl();
			cell.Row=ptrGrid->GetPrevRow(cell);

			ReDraw();
		}else{
			
		}
		break;
	case VK_RETURN:
	case VK_DOWN:
		bCancel=TRUE;
		if(cell.Row<cellSize.Row-1){
			HideInPlaceCtrl();
			cell.Row=ptrGrid->GetNextRow(cell);
			
			ReDraw();
		}else{
			
		}
		break;
	default:
		break;
	}
	if(bCancel){
		ptrTable->SetCurrentCell(cell);
		ptrTable->SetPrevFocusCell(cell);
		ptrGrid->AutoAdjustPos(cell);
	}
}
void CLRptGrid::OnKeyUp(LONG wParam,LONG lParam,BOOL& bCancel)
{
	
}
void CLRptGrid::HideInPlaceCtrl()
{
	ISheet* psheet=m_book.GetCurrentSheet();
	if(!psheet)return;
	IGrid* ptrGrid=psheet->GetGrid();
	if(!ptrGrid)return;
	ITable* ptrTable=ptrGrid->GetTable();
	if(!ptrTable)return;
	RANGE range;
	ptrTable->GetCurrentRange(range);
	CELL cell;
	if(m_nCurrCtrlRow>=0 && m_nCurrCtrlCol>=0){
		cell.Row=m_nCurrCtrlRow;
		cell.Col=m_nCurrCtrlCol;
	}else{
		ptrTable->GetCurrentCell(cell);
		ptrGrid->GetMasterCell(cell);
	}
	if(m_ptrCurrCtrl
		&& cell.Row>0 && cell.Col>0){
		m_ptrCurrCtrl->setVisible(FALSE);
		char* ptr=m_ptrCurrCtrl->getStringValue();

		ptrTable->SetCellText(cell.Row,cell.Col,ptr);
/*
		CLCellItem* ptrItem=NULL;
		if(ptr!=NULL && ptr[0]!='\0'){
			ptrItem=ptrTable->GetACell(cell,TRUE);
			if(ptrItem)
				ptrItem->SetText(ptr);
		}else{
			ptrItem=ptrTable->GetACell(cell);
			if(ptrItem)
				ptrItem->SetText(ptr);
		}
*/
		m_ptrCurrCtrl->setStringValue("");
		if(ptr)
			delete[] ptr;
		m_ptrCurrCtrl=NULL;
		ReDraw();
	}
}

void CLRptGrid::ClearInplaceCtrl()
{
	if(m_ptrEdit)
		delete m_ptrEdit;
	m_ptrEdit=NULL;
}