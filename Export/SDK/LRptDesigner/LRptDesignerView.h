// LRptDesignerView.h : interface of the CLRptDesignerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LRPTDESIGNERVIEW_H__6B1C6A3C_7CE5_402A_AACF_31A263C267A6__INCLUDED_)
#define AFX_LRPTDESIGNERVIEW_H__6B1C6A3C_7CE5_402A_AACF_31A263C267A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLRptDesignerView : public CView
{
	friend class CMainFrame;
protected: // create from serialization only
	CLRptDesignerView();
	DECLARE_DYNCREATE(CLRptDesignerView)

// Attributes
public:
	void RefreshFixedCell(LONG sheet);
	CLRptDesignerDoc* GetDocument();
	void OnForecolor(LONG clrIndex);
	void OnBackcolor(LONG clrIndex);
	void OnBorderColor(LONG clrIndex);
	void OnBorderLineStyle(LONG nStyle);
	void OnGridLineStyle(LONG nStyle);
	
	
	virtual void OnActivateFrame(UINT nState, CFrameWnd* pFrameWnd);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLRptDesignerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void PreSubclassWindow();
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	LONG GetReport();
	void SetReport(LONG val);
	virtual ~CLRptDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString COLUMNtoName(LONG col);
// Generated message map functions
protected:
	//{{AFX_MSG(CLRptDesignerView)
	afx_msg void OnUpdateAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnAlignBottom();
	afx_msg void OnAlignCenter();
	afx_msg void OnUpdateAlignCenter(CCmdUI* pCmdUI);
	afx_msg void OnAlignLeft();
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnAlignMiddle();
	afx_msg void OnUpdateAlignMiddle(CCmdUI* pCmdUI);
	afx_msg void OnAlignRight();
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnAlignTop();
	afx_msg void OnUpdateAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnAppendCol();
	afx_msg void OnUpdateAppendCol(CCmdUI* pCmdUI);
	afx_msg void OnAppendRow();
	afx_msg void OnUpdateAppendRow(CCmdUI* pCmdUI);
	afx_msg void OnCalcAll();
	afx_msg void OnUpdateCalcAll(CCmdUI* pCmdUI);
	afx_msg void OnDataSortaz();
	afx_msg void OnUpdateDataSortaz(CCmdUI* pCmdUI);
	afx_msg void OnDataSortza();
	afx_msg void OnUpdateDataSortza(CCmdUI* pCmdUI);
	afx_msg void OnDeleteCol();
	afx_msg void OnUpdateDeleteCol(CCmdUI* pCmdUI);
	afx_msg void OnDeleteRow();
	afx_msg void OnUpdateDeleteRow(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatBackcolor(CCmdUI* pCmdUI);
	afx_msg void OnFormatBold();
	afx_msg void OnUpdateFormatBold(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorder();
	afx_msg void OnUpdateFormatBorder(CCmdUI* pCmdUI);
	afx_msg void OnFormatBrush();
	afx_msg void OnUpdateFormatBrush(CCmdUI* pCmdUI);
	afx_msg void OnFormatFontname();
	afx_msg void OnUpdateFormatFontname(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatForecolor(CCmdUI* pCmdUI);
	afx_msg void OnFormatItalic();
	afx_msg void OnUpdateFormatItalic(CCmdUI* pCmdUI);
	afx_msg void OnFormatUnderline();
	afx_msg void OnUpdateFormatUnderline(CCmdUI* pCmdUI);
	afx_msg void OnHylink();
	afx_msg void OnUpdateHylink(CCmdUI* pCmdUI);
	afx_msg void OnInsertCol();
	afx_msg void OnUpdateInsertCol(CCmdUI* pCmdUI);
	afx_msg void OnInsertFunction();
	afx_msg void OnUpdateInsertFunction(CCmdUI* pCmdUI);
	afx_msg void OnInsertRow();
	afx_msg void OnUpdateInsertRow(CCmdUI* pCmdUI);
	afx_msg void OnMergeCell();
	afx_msg void OnUpdateMergeCell(CCmdUI* pCmdUI);
	afx_msg void OnMergeCols();
	afx_msg void OnUpdateMergeCols(CCmdUI* pCmdUI);
	afx_msg void OnMergeRows();
	afx_msg void OnUpdateMergeRows(CCmdUI* pCmdUI);
	afx_msg void OnNormalSum();
	afx_msg void OnUpdateNormalSum(CCmdUI* pCmdUI);
	afx_msg void OnReadonly();
	afx_msg void OnUpdateReadonly(CCmdUI* pCmdUI);
	afx_msg void OnSumHv();
	afx_msg void OnUpdateSumHv(CCmdUI* pCmdUI);
	afx_msg void OnSumVert();
	afx_msg void OnUpdateSumVert(CCmdUI* pCmdUI);
	afx_msg void OnSumhorz();
	afx_msg void OnUpdateSumhorz(CCmdUI* pCmdUI);
	afx_msg void OnUnmergeCell();
	afx_msg void OnUpdateUnmergeCell(CCmdUI* pCmdUI);
	afx_msg void OnValueCurency();
	afx_msg void OnUpdateValueCurency(CCmdUI* pCmdUI);
	afx_msg void OnValuePercent();
	afx_msg void OnUpdateValuePercent(CCmdUI* pCmdUI);
	afx_msg void OnValueThousands();
	afx_msg void OnUpdateValueThousands(CCmdUI* pCmdUI);
	afx_msg void OnEditOk();
	afx_msg void OnUpdateEditOk(CCmdUI* pCmdUI);
	afx_msg void OnEditCancel();
	afx_msg void OnUpdateEditCancel(CCmdUI* pCmdUI);
	afx_msg void OnPointCrease();
	afx_msg void OnUpdatePointCrease(CCmdUI* pCmdUI);
	afx_msg void OnPointDecrease();
	afx_msg void OnUpdatePointDecrease(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateBorderLineStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGridLineStyle(CCmdUI* pCmdUI);
	afx_msg void OnEditEqu();
	afx_msg void OnUpdateEditEqu(CCmdUI* pCmdUI);
	afx_msg void OnInsertPicture();
	afx_msg void OnFreezeCell();
	afx_msg void OnUpdateFreezeCell(CCmdUI* pCmdUI);
	afx_msg void OnInsertGrid();
	afx_msg void OnUpdateInsertGrid(CCmdUI* pCmdUI);
	afx_msg void OnEditDeleteSheet();
	afx_msg void OnUpdateEditDeleteSheet(CCmdUI* pCmdUI);
	afx_msg void OnFormatSheetRename();
	afx_msg void OnUpdateFormatSheetRename(CCmdUI* pCmdUI);
	afx_msg void OnInsertRemark();
	afx_msg void OnUpdateInsertRemark(CCmdUI* pCmdUI);
	afx_msg void OnBorderLineStyle();
	afx_msg void OnBorderLineDot();
	afx_msg void OnUpdateBorderLineDot(CCmdUI* pCmdUI);
	afx_msg void OnCashBorder();
	afx_msg void OnUpdateCashBorder(CCmdUI* pCmdUI);
	afx_msg void OnCashHeader();
	afx_msg void OnUpdateCashHeader(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnNotifySetFont(NMHDR* pNotifyStruct, LRESULT* result);
	DECLARE_MESSAGE_MAP()
private:
	
	LONG m_ptrReport;
	void InitSheet(LONG pRpt,LONG sheet);
	BOOL InitGrid();
};

#ifndef _DEBUG  // debug version in LRptDesignerView.cpp
inline CLRptDesignerDoc* CLRptDesignerView::GetDocument()
   { return (CLRptDesignerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LRPTDESIGNERVIEW_H__6B1C6A3C_7CE5_402A_AACF_31A263C267A6__INCLUDED_)
