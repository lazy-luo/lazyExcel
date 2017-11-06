/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 10 11:19:53 2017
 */
/* Compiler settings for C:\work_folder\c++\LGridBook\Export\Control\GridBook.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __GridBook_h__
#define __GridBook_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IReportGrid_FWD_DEFINED__
#define __IReportGrid_FWD_DEFINED__
typedef interface IReportGrid IReportGrid;
#endif 	/* __IReportGrid_FWD_DEFINED__ */


#ifndef ___IReportGridEvents_FWD_DEFINED__
#define ___IReportGridEvents_FWD_DEFINED__
typedef interface _IReportGridEvents _IReportGridEvents;
#endif 	/* ___IReportGridEvents_FWD_DEFINED__ */


#ifndef __ReportGrid_FWD_DEFINED__
#define __ReportGrid_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReportGrid ReportGrid;
#else
typedef struct ReportGrid ReportGrid;
#endif /* __cplusplus */

#endif 	/* __ReportGrid_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_GridBook_0000 */
/* [local] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_GridBook_0000_0001
    {	NO_LINE	= 0,
	LEFT_LINE	= 0x1,
	RIGHT_LINE	= 0x2,
	TOP_LINE	= 0x4,
	BOTTOM_LINE	= 0x8,
	FULL_LINE	= 0xf
    }	_tag_BorderLine;



extern RPC_IF_HANDLE __MIDL_itf_GridBook_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GridBook_0000_v0_0_s_ifspec;

#ifndef __IReportGrid_INTERFACE_DEFINED__
#define __IReportGrid_INTERFACE_DEFINED__

/* interface IReportGrid */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IReportGrid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71BF6F4E-0502-47E0-80B2-3F9F8CC6B9B2")
    IReportGrid : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBitmapPan( 
            LONG sheet,
            BSTR ptrName,
            /* [retval][out] */ BOOL __RPC_FAR *bret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSheet( 
            BSTR ptrName,
            LONG index,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppendACol( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppendARow( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearCellData( 
            LONG sheet,
            LONG nRow,
            LONG nCol) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearCurrentRangeData( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyData( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CutCurrentData( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteCurrentCol( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteCurrentRow( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteSheet( 
            LONG index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Cols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColWidth( 
            LONG sheet,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColWidth( 
            LONG sheet,
            LONG col,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentSheetIndex( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentSheetIndex( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedCols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedCols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedRows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedRows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FreezeCols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FreezeCols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FreezeRows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FreezeRows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextMatrix( 
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextMatrix( 
            LONG sheet,
            LONG row,
            LONG col,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderLineStyle( 
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [retval][out] */ _tag_BorderLine __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderLineStyle( 
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [in] */ _tag_BorderLine newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellBkColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellBorderColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellForeColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetFontName( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReportGridVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IReportGrid __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IReportGrid __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IReportGrid __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IReportGrid __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IReportGrid __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IReportGrid __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IReportGrid __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            IReportGrid __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBitmapPan )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            BSTR ptrName,
            /* [retval][out] */ BOOL __RPC_FAR *bret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSheet )( 
            IReportGrid __RPC_FAR * This,
            BSTR ptrName,
            LONG index,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendACol )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendARow )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearCellData )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearCurrentRangeData )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyData )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CutCurrentData )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCurrentCol )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCurrentRow )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteSheet )( 
            IReportGrid __RPC_FAR * This,
            LONG index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Cols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColWidth )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColWidth )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG col,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentSheetIndex )( 
            IReportGrid __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentSheetIndex )( 
            IReportGrid __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedCols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedCols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedRows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedRows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FreezeCols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FreezeCols )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FreezeRows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FreezeRows )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TextMatrix )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TextMatrix )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BorderLineStyle )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [retval][out] */ _tag_BorderLine __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BorderLineStyle )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [in] */ _tag_BorderLine newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellBkColor )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellBorderColor )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellForeColor )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetFontName )( 
            IReportGrid __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IReportGridVtbl;

    interface IReportGrid
    {
        CONST_VTBL struct IReportGridVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReportGrid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReportGrid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReportGrid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReportGrid_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IReportGrid_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IReportGrid_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IReportGrid_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IReportGrid_get_hWnd(This,pVal)	\
    (This)->lpVtbl -> get_hWnd(This,pVal)

#define IReportGrid_AddBitmapPan(This,sheet,ptrName,bret)	\
    (This)->lpVtbl -> AddBitmapPan(This,sheet,ptrName,bret)

#define IReportGrid_AddSheet(This,ptrName,index,pVal)	\
    (This)->lpVtbl -> AddSheet(This,ptrName,index,pVal)

#define IReportGrid_AppendACol(This,sheet)	\
    (This)->lpVtbl -> AppendACol(This,sheet)

#define IReportGrid_AppendARow(This,sheet)	\
    (This)->lpVtbl -> AppendARow(This,sheet)

#define IReportGrid_ClearCellData(This,sheet,nRow,nCol)	\
    (This)->lpVtbl -> ClearCellData(This,sheet,nRow,nCol)

#define IReportGrid_ClearCurrentRangeData(This,sheet)	\
    (This)->lpVtbl -> ClearCurrentRangeData(This,sheet)

#define IReportGrid_CopyData(This,sheet)	\
    (This)->lpVtbl -> CopyData(This,sheet)

#define IReportGrid_CutCurrentData(This,sheet)	\
    (This)->lpVtbl -> CutCurrentData(This,sheet)

#define IReportGrid_DeleteCurrentCol(This,sheet)	\
    (This)->lpVtbl -> DeleteCurrentCol(This,sheet)

#define IReportGrid_DeleteCurrentRow(This,sheet)	\
    (This)->lpVtbl -> DeleteCurrentRow(This,sheet)

#define IReportGrid_DeleteSheet(This,index)	\
    (This)->lpVtbl -> DeleteSheet(This,index)

#define IReportGrid_get_Cols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_Cols(This,sheet,pVal)

#define IReportGrid_put_Cols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_Cols(This,sheet,newVal)

#define IReportGrid_get_Rows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_Rows(This,sheet,pVal)

#define IReportGrid_put_Rows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_Rows(This,sheet,newVal)

#define IReportGrid_get_ColWidth(This,sheet,col,pVal)	\
    (This)->lpVtbl -> get_ColWidth(This,sheet,col,pVal)

#define IReportGrid_put_ColWidth(This,sheet,col,newVal)	\
    (This)->lpVtbl -> put_ColWidth(This,sheet,col,newVal)

#define IReportGrid_get_CurrentSheetIndex(This,pVal)	\
    (This)->lpVtbl -> get_CurrentSheetIndex(This,pVal)

#define IReportGrid_put_CurrentSheetIndex(This,newVal)	\
    (This)->lpVtbl -> put_CurrentSheetIndex(This,newVal)

#define IReportGrid_get_FixedCols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FixedCols(This,sheet,pVal)

#define IReportGrid_put_FixedCols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FixedCols(This,sheet,newVal)

#define IReportGrid_get_FixedRows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FixedRows(This,sheet,pVal)

#define IReportGrid_put_FixedRows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FixedRows(This,sheet,newVal)

#define IReportGrid_get_FreezeCols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FreezeCols(This,sheet,pVal)

#define IReportGrid_put_FreezeCols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FreezeCols(This,sheet,newVal)

#define IReportGrid_get_FreezeRows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FreezeRows(This,sheet,pVal)

#define IReportGrid_put_FreezeRows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FreezeRows(This,sheet,newVal)

#define IReportGrid_get_TextMatrix(This,sheet,row,col,pVal)	\
    (This)->lpVtbl -> get_TextMatrix(This,sheet,row,col,pVal)

#define IReportGrid_put_TextMatrix(This,sheet,row,col,newVal)	\
    (This)->lpVtbl -> put_TextMatrix(This,sheet,row,col,newVal)

#define IReportGrid_get_BorderLineStyle(This,sheet,irow,icol,pVal)	\
    (This)->lpVtbl -> get_BorderLineStyle(This,sheet,irow,icol,pVal)

#define IReportGrid_put_BorderLineStyle(This,sheet,irow,icol,newVal)	\
    (This)->lpVtbl -> put_BorderLineStyle(This,sheet,irow,icol,newVal)

#define IReportGrid_get_CurrentCellBkColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellBkColor(This,sheet,pVal)

#define IReportGrid_get_CurrentCellBorderColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellBorderColor(This,sheet,pVal)

#define IReportGrid_get_CurrentCellForeColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellForeColor(This,sheet,pVal)

#define IReportGrid_get_GetFontName(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_GetFontName(This,sheet,nRow,nCol,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_hWnd_Proxy( 
    IReportGrid __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_AddBitmapPan_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    BSTR ptrName,
    /* [retval][out] */ BOOL __RPC_FAR *bret);


void __RPC_STUB IReportGrid_AddBitmapPan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_AddSheet_Proxy( 
    IReportGrid __RPC_FAR * This,
    BSTR ptrName,
    LONG index,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_AddSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_AppendACol_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_AppendACol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_AppendARow_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_AppendARow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_ClearCellData_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol);


void __RPC_STUB IReportGrid_ClearCellData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_ClearCurrentRangeData_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_ClearCurrentRangeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_CopyData_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_CopyData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_CutCurrentData_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_CutCurrentData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_DeleteCurrentCol_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_DeleteCurrentCol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_DeleteCurrentRow_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB IReportGrid_DeleteCurrentRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReportGrid_DeleteSheet_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG index);


void __RPC_STUB IReportGrid_DeleteSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_Cols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_Cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_Cols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_Cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_Rows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_Rows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_ColWidth_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG col,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_ColWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_ColWidth_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG col,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_ColWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_CurrentSheetIndex_Proxy( 
    IReportGrid __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_CurrentSheetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_CurrentSheetIndex_Proxy( 
    IReportGrid __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_CurrentSheetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_FixedCols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_FixedCols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_FixedRows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_FixedRows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_FreezeCols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_FreezeCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_FreezeCols_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_FreezeCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_FreezeRows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_FreezeRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_FreezeRows_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB IReportGrid_put_FreezeRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_TextMatrix_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_TextMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_TextMatrix_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [in] */ BSTR newVal);


void __RPC_STUB IReportGrid_put_TextMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_BorderLineStyle_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG irow,
    LONG icol,
    /* [retval][out] */ _tag_BorderLine __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_BorderLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IReportGrid_put_BorderLineStyle_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG irow,
    LONG icol,
    /* [in] */ _tag_BorderLine newVal);


void __RPC_STUB IReportGrid_put_BorderLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_CurrentCellBkColor_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_CurrentCellBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_CurrentCellBorderColor_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_CurrentCellBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_CurrentCellForeColor_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_CurrentCellForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IReportGrid_get_GetFontName_Proxy( 
    IReportGrid __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IReportGrid_get_GetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReportGrid_INTERFACE_DEFINED__ */



#ifndef __GRIDBOOKLib_LIBRARY_DEFINED__
#define __GRIDBOOKLib_LIBRARY_DEFINED__

/* library GRIDBOOKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_GRIDBOOKLib;

#ifndef ___IReportGridEvents_DISPINTERFACE_DEFINED__
#define ___IReportGridEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IReportGridEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IReportGridEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11BC8ADD-4696-4E09-A5F3-A42EC70D6C7E")
    _IReportGridEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IReportGridEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IReportGridEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IReportGridEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IReportGridEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IReportGridEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IReportGridEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IReportGridEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IReportGridEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IReportGridEventsVtbl;

    interface _IReportGridEvents
    {
        CONST_VTBL struct _IReportGridEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IReportGridEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IReportGridEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IReportGridEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IReportGridEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IReportGridEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IReportGridEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IReportGridEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IReportGridEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ReportGrid;

#ifdef __cplusplus

class DECLSPEC_UUID("A7E2631B-1E33-412D-B4DE-F515D709AE90")
ReportGrid;
#endif
#endif /* __GRIDBOOKLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
