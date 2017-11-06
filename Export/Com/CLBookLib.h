	
// CLBookLib.h : Declaration of the CCLBookLib

#ifndef __CLBOOKLIB_H_
#define __CLBOOKLIB_H_

#include "resource.h"       // main symbols
#include "../SDK/LExport.h"
#ifdef _DEBUG_MEM
#define m_export	(*m_pexport)
#endif
/////////////////////////////////////////////////////////////////////////////
// CCLBookLib
class ATL_NO_VTABLE CCLBookLib : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCLBookLib, &CLSID_CLBookLib>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCLBookLib>,
	public IDispatchImpl<ICLBookLib, &IID_ICLBookLib, &LIBID_CLGRIDBOOKLib>
{
private:
#ifdef _DEBUG_MEM
	CLExport* m_pexport;
#else
	CLExport	m_export;
#endif
public:
	CCLBookLib()
	{
#ifdef _DEBUG_MEM
		_START_
		m_pexport=new CLExport();
#endif
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CLBOOKLIB)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCLBookLib)
	COM_INTERFACE_ENTRY(ICLBookLib)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CCLBookLib)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{

		m_pUnkMarshaler.Release();
#ifdef _DEBUG_MEM
		delete m_pexport;
		_END_
#endif
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICLBookLib
public:
	STDMETHOD(DeleteSheet)(LONG index);
	STDMETHOD(GetCashStyle)(LONG sheet,LONG row,LONG col,/*[out,retval]*/LONG* pret);
	STDMETHOD(SetCashStyle)(LONG sheet,LONG style);
	STDMETHOD(GetBorderLineDot)(LONG sheet,LONG row,LONG col,/*[out,retval]*/LONG* pret);
	STDMETHOD(SetBorderLineDot)(LONG sheet,LONG style);
	STDMETHOD(get_SheetCaption)(LONG index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_SheetCaption)(LONG index, /*[in]*/ BSTR newVal);
	STDMETHOD(get_SheetCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_CurrentSheetIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CurrentSheetIndex)(/*[in]*/ long newVal);
	STDMETHOD(get_MemoText)(LONG sheet,LONG nRow,LONG nCol, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MemoText)(LONG sheet,LONG nRow,LONG nCol, /*[in]*/ BSTR newVal);
	STDMETHOD(get_CurrentCellForeColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_CurrentCellBorderColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_CurrentCellBkColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(InsertACol)(LONG sheet);
	STDMETHOD(InsertARow)(LONG sheet);
	STDMETHOD(CutCurrentData)(LONG sheet);
	STDMETHOD(DeleteCurrentRow)(LONG sheet);
	STDMETHOD(AddBitmapPan)(LONG sheet,BSTR ptrName,/*[out,retval]*/ BOOL* bret);
	STDMETHOD(get_GridLineStyle)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_GridLineStyle)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(UnMergeCurrentRange)(LONG sheet,/*[out,retval]*/BOOL *bret);
	STDMETHOD(MergeCurrentRange)(LONG sheet,/*[out,retval]*/BOOL *bret);
	STDMETHOD(MergeCells)(LONG sheet,LONG nBeginRow, LONG nBeginCol, LONG nEndRow, LONG nEndCol, BOOL *retVal);
	STDMETHOD(get_GetFontSize)(LONG sheet,LONG nRow,LONG nCol, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_GetFontName)(LONG sheet,LONG nRow,LONG nCol, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SetCurrentRangeFontSize)(LONG sheet, LONG nSize);
	STDMETHOD(SetCurrentRangeFontName)(LONG sheet, BSTR ptrName, LONG bytChatSet);
	STDMETHOD(SetCurrentRangeBorderColor)(LONG sheet, LONG clr);
	STDMETHOD(SetCurrentRangeFontVertAlign)(LONG sheet, LONG nAlign);
	STDMETHOD(get_IsAlignBottom)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsAlignMiddle)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsAlignTop)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_FocusCol)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_FocusRow)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_IsFontItalic)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsFontBold)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsAlignRight)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsAlignLeft)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsAlignCenter)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_IsFontUnderline)(LONG sheet, LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(SetCurrentRangeFontHorzAlign)(LONG sheet, LONG nAlign);
	STDMETHOD(SetCurrentRangeFontUnderline)(LONG sheet);
	STDMETHOD(SetCurrentRangeFontItalic)(LONG sheet);
	STDMETHOD(SetCurrentRangeFontBold)(LONG sheet);
	STDMETHOD(LoadData)(BSTR strFile,/*[out,retval]*/ BOOL* pret);
	STDMETHOD(SaveData)(BSTR strFile,/*[out,retval]*/BOOL* pret);
	STDMETHOD(SetCurrentRangeReadOnly)(LONG sheet,BOOL bVal);
	STDMETHOD(get_IsCellReadOnly)(LONG sheet,LONG nRow, LONG nCol, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_IsCellReadOnly)(LONG sheet,LONG nRow, LONG nCol, /*[in]*/ BOOL newVal);
	STDMETHOD(SetCurrentRangeBorderLineStyle)(LONG sheet,LONG nStyle);
	STDMETHOD(SetCurrentRangeForeColor)(LONG sheet,LONG clr);
	STDMETHOD(SetCurrentRangeBkColor)(LONG sheet,LONG clr);
	STDMETHOD(DeleteCurrentCol)(LONG sheet);
	STDMETHOD(PasteData)(LONG sheet);
	STDMETHOD(CopyData)(LONG sheet);
	STDMETHOD(ClearCurrentRangeData)(LONG sheet);
	STDMETHOD(ClearCellData)(LONG sheet,LONG nRow, LONG nCol);
	STDMETHOD(AppendARow)(LONG sheet);
	STDMETHOD(AppendACol)(LONG sheet);
	STDMETHOD(get_BorderLineStyle)(LONG sheet,LONG irow,LONG icol, /*[out, retval]*/ _tag_BorderLine *pVal);
	STDMETHOD(put_BorderLineStyle)(LONG sheet,LONG irow,LONG icol, /*[in]*/ _tag_BorderLine newVal);
	STDMETHOD(get_ColWidth)(LONG sheet,LONG col, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_ColWidth)(LONG sheet,LONG col, /*[in]*/ LONG newVal);
	STDMETHOD(get_RowHeight)(LONG sheet,LONG row, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_RowHeight)(LONG sheet,LONG row, /*[in]*/ LONG newVal);
	STDMETHOD(get_TextMatrix)(LONG sheet,LONG row,LONG col, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TextMatrix)(LONG sheet,LONG row,LONG col, /*[in]*/ BSTR newVal);
	STDMETHOD(PrintMe)(BOOL bPrintAll);
	STDMETHOD(get_FreezeCols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FreezeCols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FixedCols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FixedCols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FreezeRows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FreezeRows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FixedRows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FixedRows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_Cols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_Cols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_Rows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_Rows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(GetCurrentSheet)(/*[out,retval]*/ LONG* sheet);
	STDMETHOD(AddSheet)(BSTR ptrName,LONG index,/* [out, retval]*/ LONG *pVal);
	STDMETHOD(DeattachWindow)();
	STDMETHOD(AttachWidow)(/*[in]*/ LONG hWnd,/*[out,retval]*/LONG* pret);
};

#endif //__CLBOOKLIB_H_
