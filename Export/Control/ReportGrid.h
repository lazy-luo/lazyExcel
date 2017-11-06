	
// ReportGrid.h : Declaration of the CReportGrid

#ifndef __REPORTGRID_H_
#define __REPORTGRID_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "../SDK/LExport.h"
#ifdef _DEBUG_MEM
#define m_export	(*m_pexport)
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportGrid
class ATL_NO_VTABLE CReportGrid : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CReportGrid, IReportGrid, &IID_IReportGrid, &LIBID_GRIDBOOKLib>,
	public CComControl<CReportGrid>,
	public IPersistStreamInitImpl<CReportGrid>,
	public IOleControlImpl<CReportGrid>,
	public IOleObjectImpl<CReportGrid>,
	public IOleInPlaceActiveObjectImpl<CReportGrid>,
	public IViewObjectExImpl<CReportGrid>,
	public IOleInPlaceObjectWindowlessImpl<CReportGrid>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CReportGrid>,
	public IPersistStorageImpl<CReportGrid>,
	public ISpecifyPropertyPagesImpl<CReportGrid>,
	public IQuickActivateImpl<CReportGrid>,
	public IDataObjectImpl<CReportGrid>,
	public IProvideClassInfo2Impl<&CLSID_ReportGrid, &DIID__IReportGridEvents, &LIBID_GRIDBOOKLib>,
	public IPropertyNotifySinkCP<CReportGrid>,
	public CComCoClass<CReportGrid, &CLSID_ReportGrid>
{
private:
#ifdef _DEBUG_MEM
	CLExport* m_pexport;
#else
	CLExport	m_export;
#endif
public:
	CReportGrid()
	{
#ifdef _DEBUG_MEM
		_START_
		m_pexport=new CLExport();
#endif
		m_pUnkMarshaler = NULL;
		m_bWindowOnly = TRUE;
	}

DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_REGISTRY_RESOURCEID(IDR_REPORTGRID)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CReportGrid)
	COM_INTERFACE_ENTRY(IReportGrid)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

BEGIN_PROP_MAP(CReportGrid)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	//PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CReportGrid)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CReportGrid)
	CHAIN_MSG_MAP(CComControl<CReportGrid>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



	HRESULT FinalConstruct()
	{
		HRESULT ret= CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
		
		return ret;
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IReportGrid,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IReportGrid
public:
	STDMETHOD(get_GetFontName)(LONG sheet,LONG nRow,LONG nCol, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CurrentCellForeColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_CurrentCellBorderColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_CurrentCellBkColor)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_BorderLineStyle)(LONG sheet,LONG irow,LONG icol, /*[out, retval]*/ _tag_BorderLine *pVal);
	STDMETHOD(put_BorderLineStyle)(LONG sheet,LONG irow,LONG icol, /*[in]*/ _tag_BorderLine newVal);
	STDMETHOD(get_TextMatrix)(LONG sheet,LONG row,LONG col, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TextMatrix)(LONG sheet,LONG row,LONG col, /*[in]*/ BSTR newVal);
	STDMETHOD(get_FreezeRows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FreezeRows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FreezeCols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FreezeCols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FixedRows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FixedRows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_FixedCols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_FixedCols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_CurrentSheetIndex)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_CurrentSheetIndex)(/*[in]*/ LONG newVal);
	STDMETHOD(get_ColWidth)(LONG sheet,LONG col, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_ColWidth)(LONG sheet,LONG col, /*[in]*/ LONG newVal);
	STDMETHOD(get_Rows)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_Rows)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(get_Cols)(LONG sheet, /*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_Cols)(LONG sheet, /*[in]*/ LONG newVal);
	STDMETHOD(DeleteSheet)(LONG index);
	STDMETHOD(DeleteCurrentRow)(LONG sheet);
	STDMETHOD(DeleteCurrentCol)(LONG sheet);
	STDMETHOD(CutCurrentData)(LONG sheet);
	STDMETHOD(CopyData)(LONG sheet);
	STDMETHOD(ClearCurrentRangeData)(LONG sheet);
	STDMETHOD(ClearCellData)(LONG sheet,LONG nRow,LONG nCol);
	STDMETHOD(AppendARow)(LONG sheet);
	STDMETHOD(AppendACol)(LONG sheet);
	STDMETHOD(AddSheet)(BSTR ptrName,LONG index,/*[out, retval]*/LONG* pVal);
	STDMETHOD(AddBitmapPan)(LONG sheet,BSTR ptrName,/*[out, retval]*/BOOL *bret);
	STDMETHOD(get_hWnd)(/*[out, retval]*/ LONG *pVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("¿Ø¼þ¼ÓÔØÊ§°Ü!");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		if(m_hWnd){
			m_export.AttachWidow(m_hWnd);
		}
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		m_export.DeattachWindow();
		return 0;
	}
};

#endif //__REPORTGRID_H_
