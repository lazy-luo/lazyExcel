// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _ICLBookLibEvents wrapper class

class _ICLBookLibEvents : public COleDispatchDriver
{
public:
	_ICLBookLibEvents() {}		// Calls COleDispatchDriver default constructor
	_ICLBookLibEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ICLBookLibEvents(const _ICLBookLibEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// ICLBookLib wrapper class

class ICLBookLib : public COleDispatchDriver
{
public:
	ICLBookLib() {}		// Calls COleDispatchDriver default constructor
	ICLBookLib(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICLBookLib(const ICLBookLib& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long AttachWidow(long hWnd);
	void DeattachWindow();
	long AddSheet(LPCTSTR ptrName, long index);
	long GetCurrentSheet();
	long GetRows(long sheet);
	void SetRows(long sheet, long nNewValue);
	long GetCols(long sheet);
	void SetCols(long sheet, long nNewValue);
	long GetFixedRows(long sheet);
	void SetFixedRows(long sheet, long nNewValue);
	long GetFreezeRows(long sheet);
	void SetFreezeRows(long sheet, long nNewValue);
	long GetFixedCols(long sheet);
	void SetFixedCols(long sheet, long nNewValue);
	long GetFreezeCols(long sheet);
	void SetFreezeCols(long sheet, long nNewValue);
	void PrintMe(long bPrintAll);
	CString GetTextMatrix(long sheet, long row, long col);
	void SetTextMatrix(long sheet, long row, long col, LPCTSTR lpszNewValue);
	long GetRowHeight(long sheet, long row);
	void SetRowHeight(long sheet, long row, long nNewValue);
	long GetColWidth(long sheet, long col);
	void SetColWidth(long sheet, long col, long nNewValue);
	long GetBorderLineStyle(long sheet, long irow, long icol);
	void SetBorderLineStyle(long sheet, long irow, long icol, long nNewValue);
	void AppendACol(long sheet);
	void AppendARow(long sheet);
	void ClearCellData(long sheet, long nRow, long nCol);
	void ClearCurrentRangeData(long sheet);
	void CopyData(long sheet);
	void PasteData(long sheet);
	void DeleteCurrentCol(long sheet);
	void SetCurrentRangeBkColor(long sheet, long clr);
	void SetCurrentRangeForeColor(long sheet, long clr);
	void SetCurrentRangeBorderLineStyle(long sheet, long nStyle);
	long GetIsCellReadOnly(long sheet, long nRow, long nCol);
	void SetIsCellReadOnly(long sheet, long nRow, long nCol, long nNewValue);
	void SetCurrentRangeReadOnly(long sheet, long bVal);
	long SaveData(LPCTSTR strFile);
	long LoadData(LPCTSTR strFile);
	void SetCurrentRangeFontBold(long sheet);
	void SetCurrentRangeFontItalic(long sheet);
	void SetCurrentRangeFontUnderline(long sheet);
	void SetCurrentRangeFontHorzAlign(long sheet, long nAlign);
	long GetIsFontUnderline(long sheet, long nRow, long nCol);
	long GetIsAlignLeft(long sheet, long nRow, long nCol);
	long GetIsAlignRight(long sheet, long nRow, long nCol);
	long GetIsFontBold(long sheet, long nRow, long nCol);
	long GetIsFontItalic(long sheet, long nRow, long nCol);
	long GetFocusRow(long sheet);
	long GetFocusCol(long sheet);
	long GetIsAlignTop(long sheet, long nRow, long nCol);
	long GetIsAlignMiddle(long sheet, long nRow, long nCol);
	long GetIsAlignBottom(long sheet, long nRow, long nCol);
	void SetCurrentRangeFontVertAlign(long sheet, long nAlign);
	void SetCurrentRangeBorderColor(long sheet, long clr);
	void SetCurrentRangeFontName(long sheet, LPCTSTR ptrName, long bytChatSet);
	void SetCurrentRangeFontSize(long sheet, long nSize);
	CString GetGetFontName(long sheet, long nRow, long nCol);
	long GetGetFontSize(long sheet, long nRow, long nCol);
	long GetIsAlignCenter(long sheet, long nRow, long nCol);
	void MergeCells(long sheet, long nBeginRow, long nBeginCol, long nEndRow, long nEndCol, long* retVal);
	long MergeCurrentRange(long sheet);
	long UnMergeCurrentRange(long sheet);
	long GetGridLineStyle(long sheet);
	void SetGridLineStyle(long sheet, long nNewValue);
	long AddBitmapPan(long sheet, LPCTSTR ptrName);
	void DeleteCurrentRow(long sheet);
	void CutCurrentData(long sheet);
	void InsertARow(long sheet);
	void InsertACol(long sheet);
	long GetCurrentCellBkColor(long sheet);
	long GetCurrentCellBorderColor(long sheet);
	long GetCurrentCellForeColor(long sheet);
	CString GetMemoText(long sheet, long nRow, long nCol);
	void SetMemoText(long sheet, long nRow, long nCol, LPCTSTR lpszNewValue);
	long GetCurrentSheetIndex();
	void SetCurrentSheetIndex(long nNewValue);
	long GetSheetCount();
	CString GetSheetCaption(long index);
	void SetSheetCaption(long index, LPCTSTR lpszNewValue);
	void SetBorderLineDot(long sheet, long style);
	long GetBorderLineDot(long sheet, long row, long col);
	void SetCashStyle(long sheet, long style);
	long GetCashStyle(long sheet, long row, long col);
	void DeleteSheet(long index);
};
