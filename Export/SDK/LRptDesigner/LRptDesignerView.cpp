// LRptDesignerView.cpp : implementation of the CLRptDesignerView class
//

#include "stdafx.h"
#include "LRptDesigner.h"

#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#include "DesignerTollBar.h"
#include "LDlgSheetName.h"
#include "LDlgMemo.h"

#include "MainFrm.h"
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
static char g_szFilter[] = "位图文件 (*.bmp)|*.bmp";
/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView

IMPLEMENT_DYNCREATE(CLRptDesignerView, CView)

BEGIN_MESSAGE_MAP(CLRptDesignerView, CView)
	//{{AFX_MSG_MAP(CLRptDesignerView)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BOTTOM, OnUpdateAlignBottom)
	ON_COMMAND(ID_ALIGN_BOTTOM, OnAlignBottom)
	ON_COMMAND(ID_ALIGN_CENTER, OnAlignCenter)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTER, OnUpdateAlignCenter)
	ON_COMMAND(ID_ALIGN_LEFT, OnAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, OnUpdateAlignLeft)
	ON_COMMAND(ID_ALIGN_MIDDLE, OnAlignMiddle)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_MIDDLE, OnUpdateAlignMiddle)
	ON_COMMAND(ID_ALIGN_RIGHT, OnAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, OnUpdateAlignRight)
	ON_COMMAND(ID_ALIGN_TOP, OnAlignTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_TOP, OnUpdateAlignTop)
	ON_COMMAND(ID_APPEND_COL, OnAppendCol)
	ON_UPDATE_COMMAND_UI(ID_APPEND_COL, OnUpdateAppendCol)
	ON_COMMAND(ID_APPEND_ROW, OnAppendRow)
	ON_UPDATE_COMMAND_UI(ID_APPEND_ROW, OnUpdateAppendRow)
	ON_COMMAND(ID_CALC_ALL, OnCalcAll)
	ON_UPDATE_COMMAND_UI(ID_CALC_ALL, OnUpdateCalcAll)
	ON_COMMAND(ID_DATA_SORTAZ, OnDataSortaz)
	ON_UPDATE_COMMAND_UI(ID_DATA_SORTAZ, OnUpdateDataSortaz)
	ON_COMMAND(ID_DATA_SORTZA, OnDataSortza)
	ON_UPDATE_COMMAND_UI(ID_DATA_SORTZA, OnUpdateDataSortza)
	ON_COMMAND(ID_DELETE_COL, OnDeleteCol)
	ON_UPDATE_COMMAND_UI(ID_DELETE_COL, OnUpdateDeleteCol)
	ON_COMMAND(ID_DELETE_ROW, OnDeleteRow)
	ON_UPDATE_COMMAND_UI(ID_DELETE_ROW, OnUpdateDeleteRow)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_BACKCOLOR, OnUpdateFormatBackcolor)
	ON_COMMAND(ID_FORMAT_BOLD, OnFormatBold)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_BOLD, OnUpdateFormatBold)
	ON_COMMAND(ID_FORMAT_BORDER, OnFormatBorder)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_BORDER, OnUpdateFormatBorder)
	ON_COMMAND(ID_FORMAT_BRUSH, OnFormatBrush)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_BRUSH, OnUpdateFormatBrush)
	ON_COMMAND(ID_FORMAT_FONTNAME, OnFormatFontname)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_FONTNAME, OnUpdateFormatFontname)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_FORECOLOR, OnUpdateFormatForecolor)
	ON_COMMAND(ID_FORMAT_ITALIC, OnFormatItalic)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_ITALIC, OnUpdateFormatItalic)
	ON_COMMAND(ID_FORMAT_UNDERLINE, OnFormatUnderline)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_UNDERLINE, OnUpdateFormatUnderline)
	ON_COMMAND(ID_HYLINK, OnHylink)
	ON_UPDATE_COMMAND_UI(ID_HYLINK, OnUpdateHylink)
	ON_COMMAND(ID_INSERT_COL, OnInsertCol)
	ON_UPDATE_COMMAND_UI(ID_INSERT_COL, OnUpdateInsertCol)
	ON_COMMAND(ID_INSERT_FUNCTION, OnInsertFunction)
	ON_UPDATE_COMMAND_UI(ID_INSERT_FUNCTION, OnUpdateInsertFunction)
	ON_COMMAND(ID_INSERT_ROW, OnInsertRow)
	ON_UPDATE_COMMAND_UI(ID_INSERT_ROW, OnUpdateInsertRow)
	ON_COMMAND(ID_MERGE_CELL, OnMergeCell)
	ON_UPDATE_COMMAND_UI(ID_MERGE_CELL, OnUpdateMergeCell)
	ON_COMMAND(ID_MERGE_COLS, OnMergeCols)
	ON_UPDATE_COMMAND_UI(ID_MERGE_COLS, OnUpdateMergeCols)
	ON_COMMAND(ID_MERGE_ROWS, OnMergeRows)
	ON_UPDATE_COMMAND_UI(ID_MERGE_ROWS, OnUpdateMergeRows)
	ON_COMMAND(ID_NORMAL_SUM, OnNormalSum)
	ON_UPDATE_COMMAND_UI(ID_NORMAL_SUM, OnUpdateNormalSum)
	ON_COMMAND(ID_READONLY, OnReadonly)
	ON_UPDATE_COMMAND_UI(ID_READONLY, OnUpdateReadonly)
	ON_COMMAND(ID_SUM_HV, OnSumHv)
	ON_UPDATE_COMMAND_UI(ID_SUM_HV, OnUpdateSumHv)
	ON_COMMAND(ID_SUM_VERT, OnSumVert)
	ON_UPDATE_COMMAND_UI(ID_SUM_VERT, OnUpdateSumVert)
	ON_COMMAND(ID_SUMHORZ, OnSumhorz)
	ON_UPDATE_COMMAND_UI(ID_SUMHORZ, OnUpdateSumhorz)
	ON_COMMAND(ID_UNMERGE_CELL, OnUnmergeCell)
	ON_UPDATE_COMMAND_UI(ID_UNMERGE_CELL, OnUpdateUnmergeCell)
	ON_COMMAND(ID_VALUE_CURENCY, OnValueCurency)
	ON_UPDATE_COMMAND_UI(ID_VALUE_CURENCY, OnUpdateValueCurency)
	ON_COMMAND(ID_VALUE_PERCENT, OnValuePercent)
	ON_UPDATE_COMMAND_UI(ID_VALUE_PERCENT, OnUpdateValuePercent)
	ON_COMMAND(ID_VALUE_THOUSANDS, OnValueThousands)
	ON_UPDATE_COMMAND_UI(ID_VALUE_THOUSANDS, OnUpdateValueThousands)
	ON_COMMAND(ID_EDIT_OK, OnEditOk)
	ON_UPDATE_COMMAND_UI(ID_EDIT_OK, OnUpdateEditOk)
	ON_COMMAND(ID_EDIT_CANCEL, OnEditCancel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CANCEL, OnUpdateEditCancel)
	ON_COMMAND(ID_POINT_CREASE, OnPointCrease)
	ON_UPDATE_COMMAND_UI(ID_POINT_CREASE, OnUpdatePointCrease)
	ON_COMMAND(ID_POINT_DECREASE, OnPointDecrease)
	ON_UPDATE_COMMAND_UI(ID_POINT_DECREASE, OnUpdatePointDecrease)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_BORDER_LINE_STYLE, OnUpdateBorderLineStyle)
	ON_UPDATE_COMMAND_UI(ID_GRID_LINE_STYLE, OnUpdateGridLineStyle)
	ON_COMMAND(ID_EDIT_EQU, OnEditEqu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EQU, OnUpdateEditEqu)
	ON_COMMAND(IDM_INSERT_PICTURE, OnInsertPicture)
	ON_COMMAND(IDM_FREEZE_CELL, OnFreezeCell)
	ON_UPDATE_COMMAND_UI(IDM_FREEZE_CELL, OnUpdateFreezeCell)
	ON_COMMAND(IDM_INSERT_GRID, OnInsertGrid)
	ON_UPDATE_COMMAND_UI(IDM_INSERT_GRID, OnUpdateInsertGrid)
	ON_COMMAND(IDM_EDIT_DELETE_SHEET, OnEditDeleteSheet)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETE_SHEET, OnUpdateEditDeleteSheet)
	ON_COMMAND(IDM_FORMAT_SHEET_RENAME, OnFormatSheetRename)
	ON_UPDATE_COMMAND_UI(IDM_FORMAT_SHEET_RENAME, OnUpdateFormatSheetRename)
	ON_COMMAND(IDM_INSERT_REMARK, OnInsertRemark)
	ON_UPDATE_COMMAND_UI(IDM_INSERT_REMARK, OnUpdateInsertRemark)
	ON_COMMAND(ID_BORDER_LINE_STYLE, OnBorderLineStyle)
	ON_COMMAND(ID_BORDER_LINE_DOT, OnBorderLineDot)
	ON_UPDATE_COMMAND_UI(ID_BORDER_LINE_DOT, OnUpdateBorderLineDot)
	ON_COMMAND(IDM_INSERT_ROW, OnInsertRow)
	ON_UPDATE_COMMAND_UI(IDM_INSERT_ROW, OnUpdateInsertRow)
	ON_COMMAND(IDM_INSERT_COL, OnInsertCol)
	ON_UPDATE_COMMAND_UI(IDM_INSERT_COL, OnUpdateInsertCol)
	ON_COMMAND(ID_CASH_BORDER, OnCashBorder)
	ON_UPDATE_COMMAND_UI(ID_CASH_BORDER, OnUpdateCashBorder)
	ON_COMMAND(ID_CASH_HEADER, OnCashHeader)
	ON_UPDATE_COMMAND_UI(ID_CASH_HEADER, OnUpdateCashHeader)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_NOTIFY(msg_ncSETFONT, ID_TB_FORMATBAR, OnNotifySetFont)
END_MESSAGE_MAP()
void CLRptDesignerView::OnActivateFrame(UINT nState, CFrameWnd* pFrameWnd)
{
	CMainFrame* pMainFrame=(CMainFrame*)(CMainFrame*)GetApp()->m_pMainWnd;
	if(pMainFrame){
		pMainFrame->OnEnableOwnerDrawCtrl(TRUE);
		//pMainFrame->AdjustHelpMenu(pMainFrame->m_hWnd);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView construction/destruction

BOOL CLRptDesignerView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	PICKERBTNHDR* pParam=(PICKERBTNHDR*)lParam;
	switch(wParam){
	case ID_FORMAT_BACKCOLOR:
		OnBackcolor(pParam->iValue);
		break;
	case ID_FORMAT_FORECOLOR:
		OnForecolor(pParam->iValue);
		break;
	case ID_FORMAT_BORDER:
		OnBorderColor(pParam->iValue);
		break;
	case ID_BORDER_LINE_STYLE:
		OnBorderLineStyle(pParam->iValue);
		break;
	case ID_GRID_LINE_STYLE:
		OnGridLineStyle(pParam->iValue);
		break;
	}
	return CView::OnNotify(wParam, lParam, pResult);
}
CLRptDesignerView::CLRptDesignerView():m_ptrReport(0)
{
	// TODO: add construction code here
	
}

CLRptDesignerView::~CLRptDesignerView()
{
	if(m_ptrReport){
		DeattachWindow(m_ptrReport);
		m_ptrReport=0;
	}
}
void CLRptDesignerView::OnNotifySetFont(NMHDR* pNotifyStruct, LRESULT* result)
{
	NMFONTHDR* pfh = (NMFONTHDR*)pNotifyStruct;
	char pName[LF_FACESIZE+1];
	BYTE charSet;
	LONG nHeight;
	switch(pfh->mask)
	{
	case NMFONTHDR::FONTNAME:
		lstrcpyn(pName, pfh->lf.lfFaceName, LF_FACESIZE);
		if (_istlead(pName[0]) || pName[0]=='@'
			&& _istlead(pName[1]))
			charSet = (char)134;
		else
			charSet = ANSI_CHARSET;
		break;
	case NMFONTHDR::FONTSIZE:
		nHeight = pfh->lf.lfHeight;
		break;
	default:
		return;
	}
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		if(pfh->mask==NMFONTHDR::FONTNAME)
			SetCurrentRangeFontName(sheet,pName,charSet);
		else
			SetCurrentRangeFontSize(sheet,nHeight);
	}
	*result = 1;
}
BOOL CLRptDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView drawing

void CLRptDesignerView::OnDraw(CDC* pDC)
{
	
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView printing

BOOL CLRptDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLRptDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLRptDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView diagnostics

#ifdef _DEBUG
void CLRptDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CLRptDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLRptDesignerDoc* CLRptDesignerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLRptDesignerDoc)));
	return (CLRptDesignerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLRptDesignerView message handlers

void CLRptDesignerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

BOOL CLRptDesignerView::InitGrid()
{
	CLRptDesignerDoc* pDoc = GetDocument();
	m_ptrReport=CreateReport();
	LONG pGrid=GetReport();
	LONG nMargin=0;
	AttachWidow(pGrid,m_hWnd);
	LONG sheet=AddSheet(GetBook(pGrid),"工作表1",1);
	
	InitSheet(pGrid,sheet);
	sheet=AddSheet(GetBook(pGrid),"工作表2",2);
	InitSheet(pGrid,sheet);
	sheet=AddSheet(GetBook(pGrid),"工作表3",3);
	InitSheet(pGrid,sheet);
	SetCurrentSheet(GetBook(pGrid),1);
	return TRUE;
}

void CLRptDesignerView::OnUpdateAlignBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignBottom(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignBottom() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontVertAlign(GetCurrentSheet(GetBook(pGrid)),vert_align_bottom);
	}
}

void CLRptDesignerView::OnAlignCenter() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontHorzAlign(GetCurrentSheet(GetBook(pGrid)),horz_align_center);
	}
}

void CLRptDesignerView::OnUpdateAlignCenter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignCenter(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignLeft() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontHorzAlign(GetCurrentSheet(GetBook(pGrid)),horz_align_left);
	}
}

void CLRptDesignerView::OnUpdateAlignLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignLeft(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
	
}

void CLRptDesignerView::OnAlignMiddle() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontVertAlign(GetCurrentSheet(GetBook(pGrid)),vert_align_middle);
	}
}

void CLRptDesignerView::OnUpdateAlignMiddle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignMiddle(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignRight() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontHorzAlign(GetCurrentSheet(GetBook(pGrid)),horz_align_right);
	}
}

void CLRptDesignerView::OnUpdateAlignRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignRight(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignTop() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontVertAlign(GetCurrentSheet(GetBook(pGrid)),vert_align_top);
	}
}

void CLRptDesignerView::OnUpdateAlignTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsAlignTop(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAppendCol() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		AppendACol(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateAppendCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnAppendRow() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		AppendARow(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateAppendRow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnCalcAll() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateCalcAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnDataSortaz() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateDataSortaz(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnDataSortza() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateDataSortza(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnDeleteCol() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		DeleteCurrentCol(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateDeleteCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnDeleteRow() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		DeleteCurrentRow(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateDeleteRow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		CopyData(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditCut() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		CutCurrentData(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		PasteData(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

void CLRptDesignerView::OnEditRedo() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		PrintBook(GetBook(pGrid),TRUE);
	}
}

void CLRptDesignerView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CLRptDesignerView::OnBorderColor(LONG clr)
{
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeBorderColor(GetCurrentSheet(GetBook(pGrid)),(LONG)clr);
	}
}
void CLRptDesignerView::OnBackcolor(LONG clr) 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeBkColor(GetCurrentSheet(GetBook(pGrid)),(LONG)clr);
	}
}

void CLRptDesignerView::OnUpdateFormatBackcolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*
	if(!GetDocument()->hasView())
		pCmdUI->Enable(FALSE);
	if(pCmdUI->m_pOther)
		pCmdUI->m_pOther->Invalidate();
	*/
}

void CLRptDesignerView::OnFormatBold() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontBold(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateFormatBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsFontBold(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnFormatBorder() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateFormatBorder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFormatBrush() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateFormatBrush(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFormatFontname() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateFormatFontname(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnForecolor(LONG clr) 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeForeColor(GetCurrentSheet(GetBook(pGrid)),(LONG)clr);
	}
}

void CLRptDesignerView::OnUpdateFormatForecolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFormatItalic() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontItalic(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateFormatItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsFontItalic(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnFormatUnderline() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeFontUnderline(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateFormatUnderline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(GetIsFontUnderline(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnHylink() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateHylink(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnInsertCol() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		InsertACol(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateInsertCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnInsertFunction() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateInsertFunction(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnInsertRow() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		InsertARow(GetCurrentSheet(GetBook(pGrid)));
		RefreshFixedCell(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateInsertRow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeCell() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		MergeCurrentRange(GetCurrentSheet(GetBook(pGrid)),0);
	}
}

void CLRptDesignerView::OnUpdateMergeCell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeCols() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		MergeCurrentRange(GetCurrentSheet(GetBook(pGrid)),1);
	}
}

void CLRptDesignerView::OnUpdateMergeCols(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeRows() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		MergeCurrentRange(GetCurrentSheet(GetBook(pGrid)),2);
	}
}

void CLRptDesignerView::OnUpdateMergeRows(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnNormalSum() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateNormalSum(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnReadonly() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		SetReadOnly(sheet,!IsReadOnly(sheet));
	}
}

void CLRptDesignerView::OnUpdateReadonly(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(IsReadOnly(sheet));
	}
}

void CLRptDesignerView::OnSumHv() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateSumHv(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnSumVert() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateSumVert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnSumhorz() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateSumhorz(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnUnmergeCell() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		UnMergeCurrentRange(GetCurrentSheet(GetBook(pGrid)));
	}
}

void CLRptDesignerView::OnUpdateUnmergeCell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnValueCurency() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateValueCurency(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnValuePercent() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateValuePercent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnValueThousands() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateValueThousands(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

LONG CLRptDesignerView::GetReport()
{
	return m_ptrReport;
}
void CLRptDesignerView::SetReport(LONG val)
{
	m_ptrReport=val;
}

void CLRptDesignerView::OnEditOk() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateEditOk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditCancel() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateEditCancel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnPointCrease() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdatePointCrease(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnPointDecrease() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdatePointDecrease(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::PreSubclassWindow();
}

BOOL CLRptDesignerView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}
void CLRptDesignerView::RefreshFixedCell(LONG sheet)
{
	if(sheet==0)return;
	int irow;
	char ptr[200];
	SetColWidth(sheet,0,40);
	CString strT;
	for(irow=0;irow<GetRows(sheet);irow++){
		for(int icol=0;icol<GetCols(sheet);icol++){
			if(irow==0 || icol==0){
				if(irow==0 && icol>0){
					strT=COLUMNtoName(icol-1);
					sprintf((char*)ptr,"%s\0",(LPCTSTR)strT);
				}
				else
					sprintf((char*)ptr,"%d\0",irow);
				SetTextMatrix(sheet,irow,icol,ptr);
			}
		}
	}
	SetTextMatrix(sheet,0,0,"");
}
void CLRptDesignerView::InitSheet(LONG pGrid,LONG sheet)
{
	if(sheet==0)return;
	SetRows(sheet,64);
	SetCols(sheet,16);
	SIZE size;
	size.cx=20;
	//SetFreeAreaSize(sheet,size,2);

//	SetIsExcelMode(sheet,TRUE);
//	SetPageMode(sheet,1);
	SetFixedCols(sheet,1);
	SetFixedRows(sheet,1);
//	SetResizeStyle(sheet,3);
//	SetBorderLineStyle(sheet,0);
//	SetGridAppearance(sheet,0);
//	SetScrollStyle(sheet,1);
	//SetFreezeRows(sheet,2);
	//SetColStyle(sheet,4,4);
	RefreshFixedCell(sheet);
}

BOOL CLRptDesignerView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bVal= CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	if(bVal){
		CLRptDesignerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if(!pDoc->bInitOK){
			pDoc->bInitOK=TRUE;
			InitGrid();
		}
	}
	
	return bVal;
}

void CLRptDesignerView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::CalcWindowRect(lpClientRect, nAdjustType);
}


void CLRptDesignerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	ModifyStyle (WS_BORDER, 0);
    ModifyStyleEx (WS_EX_CLIENTEDGE, 0);
    GetParentFrame()->RecalcLayout();
	SetWindowPos(NULL,0,0,0,0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED|SWP_DRAWFRAME);
	
}

void CLRptDesignerView::OnBorderLineStyle(LONG nStyle) 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetCurrentRangeBorderLineStyle(GetCurrentSheet(GetBook(pGrid)),nStyle);
	}
}

void CLRptDesignerView::OnUpdateBorderLineStyle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnGridLineStyle(LONG nStyle) 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		SetGridLineStyle(GetCurrentSheet(GetBook(pGrid)),nStyle);
	}
}

void CLRptDesignerView::OnUpdateGridLineStyle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditEqu() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateEditEqu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

CString CLRptDesignerView::COLUMNtoName(LONG col)
{
	TCHAR s[4];
	if (col < 26)
	{
		s[0] = (TCHAR)('A' + col);
		s[1] = '\x0';
	}
	else if (col < 26 * 27)
	{
		s[0] = (TCHAR)('A' + col / 26 - 1);
		s[1] = (TCHAR)('A' + col % 26);
		s[2] = '\x0';
	}
	else
	{
		s[0] = (TCHAR)('A' + (col / 26 - 1) / 26 - 1);
		s[1] = (TCHAR)('A' + (col / 26 - 1) % 26);
		s[2] = (TCHAR)('A' + col % 26);
		s[3] = '\x0';
	}
	return s;
}

void CLRptDesignerView::OnInsertPicture() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,g_szFilter);
	dlg.DoModal();
	CString strFile=dlg.GetPathName();
	LONG pGrid=GetReport();
	if(pGrid){
		AddBitmapPan(GetBook(pGrid),GetCurrentSheet(GetBook(pGrid)),(char*)(LPCTSTR)strFile);
	}
}

void CLRptDesignerView::OnFreezeCell() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		//看看是否能够冻结窗口
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		LONG nfrez_rows=GetFreezeRows(sheet),nfrez_cols=GetFreezeCols(sheet);
		BOOL bFreeze=(nfrez_rows>0 || nfrez_cols>0);
		if(bFreeze){
			//取消冻结窗格
			SetFreezeRows(sheet,0);
			SetFreezeCols(sheet,0);
		}else{
			//冻结窗格
			RANGE range;
			GetCurrentRange(sheet,range);
			if(range.m_posRow.m_begin==range.m_posRow.m_end 
				&& range.m_posCol.m_begin==range.m_posCol.m_end){
				nfrez_rows=range.m_posRow.m_begin-GetFixedRows(sheet);
				nfrez_cols=range.m_posCol.m_begin-GetFixedCols(sheet);
			}else{
				//是合并单元格
				nfrez_rows=range.m_posRow.m_end-GetFixedRows(sheet);
				nfrez_cols=range.m_posCol.m_end-GetFixedCols(sheet);
			}
			SetFreezeRows(sheet,nfrez_rows<0?0:nfrez_rows);
			SetFreezeCols(sheet,nfrez_cols<0?0:nfrez_cols);
		}
		Invalidate();
	}
}

void CLRptDesignerView::OnUpdateFreezeCell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		pCmdUI->Enable(TRUE);
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		BOOL bFreeze=(GetFreezeRows(sheet)>0 || GetFreezeCols(sheet)>0);
		if(bFreeze){
			pCmdUI->SetText("取消冻结窗格(&F)");
		}else{
			pCmdUI->SetText("冻结窗格(&F)");
			LONG nfrez_rows,nfrez_cols;
			RANGE range;
			GetCurrentRange(sheet,range);
			if(range.m_posRow.m_begin==range.m_posRow.m_end 
				&& range.m_posCol.m_begin==range.m_posCol.m_end){
				nfrez_rows=range.m_posRow.m_begin-GetFixedRows(sheet);
				nfrez_cols=range.m_posCol.m_begin-GetFixedCols(sheet);
				if(nfrez_rows<=0 && nfrez_cols<=0)
					pCmdUI->Enable(FALSE);
			}
		}
	}
}

void CLRptDesignerView::OnInsertGrid() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG index;
		CLDlgSheetName dlg;
		dlg.DoModal();
		if(dlg.m_pCaption.IsEmpty())return;
		index=GetCurrentSheetIndex(GetBook(pGrid));
		if(index<1)index=1;
		LONG sheet=AddSheet(GetBook(pGrid),(LPTSTR)((LPCTSTR)dlg.m_pCaption),index);
		InitSheet(pGrid,sheet);
		SetCurrentSheet(GetBook(pGrid),index);
		Invalidate();
	}
	
}

void CLRptDesignerView::OnUpdateInsertGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditDeleteSheet() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		if(GetSheetCount(GetBook(pGrid))>1){
			if(MessageBox("您真的想要删除当前工作表吗?","提示信息"
				,MB_YESNO | MB_ICONQUESTION)==IDYES){
				LONG index;
				index=GetCurrentSheetIndex(GetBook(pGrid));
				if(index<1)index=1;
				DeleteSheet(GetBook(pGrid),index);
				if(index>1)index--;
				SetCurrentSheet(GetBook(pGrid),index);
				Invalidate();
			}
		}else{
			MessageBox("您必须确保至少有一个工作表!删除操作被拒绝。","提示信息"
				,MB_OK | MB_ICONINFORMATION);
		}
	}
}

void CLRptDesignerView::OnUpdateEditDeleteSheet(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFormatSheetRename() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG index=GetCurrentSheetIndex(GetBook(pGrid));
		if(index>0){
			CLDlgSheetName dlg;
			LPTSTR ptr=GetSheetCaption(GetBook(pGrid),index);
			dlg.m_pCaption=(LPCSTR)ptr;
			dlg.DoModal();
			SetSheetCaption(GetBook(pGrid),index,(LPTSTR)((LPCTSTR)dlg.m_pCaption));
		}
		Invalidate();
	}
}

void CLRptDesignerView::OnUpdateFormatSheetRename(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnInsertRemark() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		if(sheet!=0){
			CLDlgMemo dlg;
			LONG irow=GetFocusRow(sheet);
			LONG icol=GetFocusCol(sheet);
			LPTSTR ptr=GetCellMemo(sheet,irow,icol);
			dlg.m_strMemo=(LPCSTR)ptr;
			dlg.DoModal();
			SetCellMemo(sheet,irow,icol,(LPTSTR)((LPCTSTR)dlg.m_strMemo));
		}
		Invalidate();
	}
}

void CLRptDesignerView::OnUpdateInsertRemark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}



void CLRptDesignerView::OnBorderLineStyle() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnBorderLineDot() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		if(15!=GetBorderLineDot(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)))
			val=15;
		SetBorderLineDot(GetCurrentSheet(GetBook(pGrid)),val);
	}
}

void CLRptDesignerView::OnUpdateBorderLineDot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(15==GetBorderLineDot(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnCashBorder() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		if(16!=GetCashStyle(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)))
			val=16;
		SetCashStyle(GetCurrentSheet(GetBook(pGrid)),val);
	}
	
}

void CLRptDesignerView::OnUpdateCashBorder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(16==GetCashStyle(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnCashHeader() 
{
	// TODO: Add your command handler code here
	LONG pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		if(8!=GetCashStyle(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)))
			val=8;
		SetCashStyle(GetCurrentSheet(GetBook(pGrid)),val);
	}
}

void CLRptDesignerView::OnUpdateCashHeader(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	LONG pGrid=GetReport();
	if(pGrid){
		LONG sheet=GetCurrentSheet(GetBook(pGrid));
		pCmdUI->SetCheck(8==GetCashStyle(sheet,GetFocusRow(sheet),
			GetFocusCol(sheet)));
	}
}
