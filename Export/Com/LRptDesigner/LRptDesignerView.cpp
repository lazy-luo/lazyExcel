// LRptDesignerView.cpp : implementation of the CLRptDesignerView class
//

#include "stdafx.h"
#include "LRptDesigner.h"

#include "LRptDesignerDoc.h"
#include "LRptDesignerView.h"
#include "DesignerTollBar.h"

#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	ON_COMMAND(ID_CASH_BORDER, OnCashBorder)
	ON_UPDATE_COMMAND_UI(ID_CASH_BORDER, OnUpdateCashBorder)
	ON_COMMAND(ID_CASH_HEADER, OnCashHeader)
	ON_UPDATE_COMMAND_UI(ID_CASH_HEADER, OnUpdateCashHeader)
	ON_COMMAND(ID_BORDER_LINE_DOT, OnBorderLineDot)
	ON_UPDATE_COMMAND_UI(ID_BORDER_LINE_DOT, OnUpdateBorderLineDot)
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
CLRptDesignerView::CLRptDesignerView()
{
	// TODO: add construction code here
	
}

CLRptDesignerView::~CLRptDesignerView()
{
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
			charSet = 134;
		else
			charSet = ANSI_CHARSET;
		break;
	case NMFONTHDR::FONTSIZE:
		nHeight = pfh->lf.lfHeight;
		break;
	default:
		return;
	}
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		if(pfh->mask==NMFONTHDR::FONTNAME)
			pGrid->SetCurrentRangeFontName(sheet,pName,charSet);
		else
			pGrid->SetCurrentRangeFontSize(sheet,nHeight);
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
	ICLBookLib* pGrid=pDoc->GetReport();
	
	LONG nMargin=0;
	pGrid->AttachWidow((LONG)m_hWnd);
	LONG sheet=pGrid->AddSheet("工作表1",1);
	InitSheet(pGrid,sheet);
	sheet=pGrid->AddSheet("工作表2",2);
	InitSheet(pGrid,sheet);
	sheet=pGrid->AddSheet("工作表3",3);
	InitSheet(pGrid,sheet);
	return TRUE;
}

void CLRptDesignerView::OnUpdateAlignBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignBottom(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignBottom() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontVertAlign(pGrid->GetCurrentSheet(),2);
	}
}

void CLRptDesignerView::OnAlignCenter() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontHorzAlign(pGrid->GetCurrentSheet(),1);
	}
}

void CLRptDesignerView::OnUpdateAlignCenter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignCenter(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignLeft() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontHorzAlign(pGrid->GetCurrentSheet(),0);
	}
}

void CLRptDesignerView::OnUpdateAlignLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignLeft(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
	
}

void CLRptDesignerView::OnAlignMiddle() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontVertAlign(pGrid->GetCurrentSheet(),1);
	}
}

void CLRptDesignerView::OnUpdateAlignMiddle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignMiddle(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignRight() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontHorzAlign(pGrid->GetCurrentSheet(),2);
	}
}

void CLRptDesignerView::OnUpdateAlignRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignRight(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAlignTop() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontVertAlign(pGrid->GetCurrentSheet(),0);
	}
}

void CLRptDesignerView::OnUpdateAlignTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsAlignTop(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnAppendCol() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->AppendACol(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateAppendCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnAppendRow() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->AppendARow(pGrid->GetCurrentSheet());
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->DeleteCurrentCol(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateDeleteCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnDeleteRow() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->DeleteCurrentRow(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateDeleteRow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->CopyData(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditCut() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->CutCurrentData(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->PasteData(pGrid->GetCurrentSheet());
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
	
}

void CLRptDesignerView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CLRptDesignerView::OnBorderColor(LONG clr)
{
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeBorderColor(pGrid->GetCurrentSheet(),(LONG)clr);
	}
}
void CLRptDesignerView::OnBackcolor(LONG clr) 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeBkColor(pGrid->GetCurrentSheet(),(LONG)clr);
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontBold(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateFormatBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsFontBold(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeForeColor(pGrid->GetCurrentSheet(),(LONG)clr);
	}
}

void CLRptDesignerView::OnUpdateFormatForecolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnFormatItalic() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontItalic(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateFormatItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsFontItalic(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnFormatUnderline() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeFontUnderline(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateFormatUnderline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(pGrid->GetIsFontUnderline(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->InsertACol(pGrid->GetCurrentSheet());
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->InsertARow(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateInsertRow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeCell() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->MergeCurrentRange(pGrid->GetCurrentSheet());
	}
}

void CLRptDesignerView::OnUpdateMergeCell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeCols() 
{
	// TODO: Add your command handler code here
	
}

void CLRptDesignerView::OnUpdateMergeCols(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnMergeRows() 
{
	// TODO: Add your command handler code here
	
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
	
}

void CLRptDesignerView::OnUpdateReadonly(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->UnMergeCurrentRange(pGrid->GetCurrentSheet());
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

ICLBookLib* CLRptDesignerView::GetReport()
{
	CLRptDesignerDoc* pDoc = GetDocument();
	if(pDoc)
		return pDoc->GetReport();
	return NULL;
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

void CLRptDesignerView::InitSheet(ICLBookLib* pGrid,LONG sheet)
{
	if(sheet==0)return;
	pGrid->SetRows(sheet,64);
	pGrid->SetCols(sheet,16);
	
//	pGrid->SetIsExcelMode(sheet,TRUE);
//	pGrid->SetPageMode(sheet,1);
	pGrid->SetFixedCols(sheet,1);
	pGrid->SetFixedRows(sheet,1);
//	pGrid->SetResizeStyle(sheet,3);
//	pGrid->SetBorderLineStyle(sheet,0);
//	pGrid->SetGridAppearance(sheet,0);
//	pGrid->SetScrollStyle(sheet,1);
	//pGrid->SetFreezeRows(sheet,2);
	//pGrid->SetColStyle(sheet,4,4);
	int irow;
	char ptr[200];
	pGrid->SetColWidth(sheet,0,40);
	CString strT;
	for(irow=0;irow<pGrid->GetRows(sheet);irow++){
		for(int icol=0;icol<pGrid->GetCols(sheet);icol++){
			if(irow==0 || icol==0){
				if(irow==0 && icol>0){
					strT=COLUMNtoName(icol-1);
					sprintf((char*)ptr,"%s\0",(LPCTSTR)strT);
				}
				else
					sprintf((char*)ptr,"%d\0",irow);
				pGrid->SetTextMatrix(sheet,irow,icol,ptr);
			}
		}
	}
	pGrid->SetTextMatrix(sheet,0,0,"");
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetCurrentRangeBorderLineStyle(pGrid->GetCurrentSheet(),nStyle);
	}
}

void CLRptDesignerView::OnUpdateBorderLineStyle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLRptDesignerView::OnGridLineStyle(LONG nStyle) 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->SetGridLineStyle(pGrid->GetCurrentSheet(),nStyle);
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
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		pGrid->AddBitmapPan(pGrid->GetCurrentSheet(),strFile);
	}
}

void CLRptDesignerView::OnBorderLineDot() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		if(15!=pGrid->GetBorderLineDot(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)))
			val=15;
		pGrid->SetBorderLineDot(sheet,val);
	}
}

void CLRptDesignerView::OnUpdateBorderLineDot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(15==pGrid->GetBorderLineDot(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnCashBorder() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		if(16!=pGrid->GetCashStyle(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)))
			val=16;
		pGrid->SetCashStyle(sheet,val);
	}
	
}

void CLRptDesignerView::OnUpdateCashBorder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(16==pGrid->GetCashStyle(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}

void CLRptDesignerView::OnCashHeader() 
{
	// TODO: Add your command handler code here
	ICLBookLib* pGrid=GetReport();
	LONG val=0;
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		if(8!=pGrid->GetCashStyle(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)))
			val=8;
		pGrid->SetCashStyle(sheet,val);
	}
}

void CLRptDesignerView::OnUpdateCashHeader(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ICLBookLib* pGrid=GetReport();
	if(pGrid){
		LONG sheet=pGrid->GetCurrentSheet();
		pCmdUI->SetCheck(8==pGrid->GetCashStyle(sheet,pGrid->GetFocusRow(sheet),
			pGrid->GetFocusCol(sheet)));
	}
}
