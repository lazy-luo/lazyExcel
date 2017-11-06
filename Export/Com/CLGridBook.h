/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 10 11:19:57 2017
 */
/* Compiler settings for C:\work_folder\c++\LGridBook\Export\Com\CLGridBook.idl:
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

#ifndef __CLGridBook_h__
#define __CLGridBook_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICLBookLib_FWD_DEFINED__
#define __ICLBookLib_FWD_DEFINED__
typedef interface ICLBookLib ICLBookLib;
#endif 	/* __ICLBookLib_FWD_DEFINED__ */


#ifndef ___ICLBookLibEvents_FWD_DEFINED__
#define ___ICLBookLibEvents_FWD_DEFINED__
typedef interface _ICLBookLibEvents _ICLBookLibEvents;
#endif 	/* ___ICLBookLibEvents_FWD_DEFINED__ */


#ifndef __CLBookLib_FWD_DEFINED__
#define __CLBookLib_FWD_DEFINED__

#ifdef __cplusplus
typedef class CLBookLib CLBookLib;
#else
typedef struct CLBookLib CLBookLib;
#endif /* __cplusplus */

#endif 	/* __CLBookLib_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_CLGridBook_0000 */
/* [local] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_CLGridBook_0000_0001
    {	NO_LINE	= 0,
	LEFT_LINE	= 0x1,
	RIGHT_LINE	= 0x2,
	TOP_LINE	= 0x4,
	BOTTOM_LINE	= 0x8,
	FULL_LINE	= 0xf
    }	_tag_BorderLine;



extern RPC_IF_HANDLE __MIDL_itf_CLGridBook_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CLGridBook_0000_v0_0_s_ifspec;

#ifndef __ICLBookLib_INTERFACE_DEFINED__
#define __ICLBookLib_INTERFACE_DEFINED__

/* interface ICLBookLib */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICLBookLib;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16C06F17-CBA6-4C46-B8E9-9075D4CEF0EC")
    ICLBookLib : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachWidow( 
            /* [in] */ LONG hWnd,
            /* [retval][out] */ LONG __RPC_FAR *pret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeattachWindow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSheet( 
            BSTR ptrName,
            LONG index,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentSheet( 
            /* [retval][out] */ LONG __RPC_FAR *sheet) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Cols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedRows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedRows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FreezeRows( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FreezeRows( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedCols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedCols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FreezeCols( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FreezeCols( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrintMe( 
            BOOL bPrintAll) = 0;
        
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
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowHeight( 
            LONG sheet,
            LONG row,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowHeight( 
            LONG sheet,
            LONG row,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColWidth( 
            LONG sheet,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColWidth( 
            LONG sheet,
            LONG col,
            /* [in] */ LONG newVal) = 0;
        
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PasteData( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteCurrentCol( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeBkColor( 
            LONG sheet,
            LONG clr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeForeColor( 
            LONG sheet,
            LONG clr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeBorderLineStyle( 
            LONG sheet,
            LONG nStyle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsCellReadOnly( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsCellReadOnly( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeReadOnly( 
            LONG sheet,
            BOOL bVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveData( 
            BSTR strFile,
            /* [retval][out] */ BOOL __RPC_FAR *pret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadData( 
            BSTR strFile,
            /* [retval][out] */ BOOL __RPC_FAR *pret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontBold( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontItalic( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontUnderline( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontHorzAlign( 
            LONG sheet,
            LONG nAlign) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsFontUnderline( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignLeft( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignRight( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsFontBold( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsFontItalic( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FocusRow( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FocusCol( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignTop( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignMiddle( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignBottom( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontVertAlign( 
            LONG sheet,
            LONG nAlign) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeBorderColor( 
            LONG sheet,
            LONG clr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontName( 
            LONG sheet,
            BSTR ptrName,
            LONG bytChatSet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentRangeFontSize( 
            LONG sheet,
            LONG nSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetFontName( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetFontSize( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAlignCenter( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MergeCells( 
            LONG sheet,
            LONG nBeginRow,
            LONG nBeginCol,
            LONG nEndRow,
            LONG nEndCol,
            BOOL __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MergeCurrentRange( 
            LONG sheet,
            /* [retval][out] */ BOOL __RPC_FAR *bret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnMergeCurrentRange( 
            LONG sheet,
            /* [retval][out] */ BOOL __RPC_FAR *bret) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GridLineStyle( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GridLineStyle( 
            LONG sheet,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBitmapPan( 
            LONG sheet,
            BSTR ptrName,
            /* [retval][out] */ BOOL __RPC_FAR *bret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteCurrentRow( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CutCurrentData( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertARow( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertACol( 
            LONG sheet) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellBkColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellBorderColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCellForeColor( 
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemoText( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MemoText( 
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentSheetIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentSheetIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SheetCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SheetCaption( 
            LONG index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SheetCaption( 
            LONG index,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBorderLineDot( 
            LONG sheet,
            LONG style) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBorderLineDot( 
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCashStyle( 
            LONG sheet,
            LONG style) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCashStyle( 
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteSheet( 
            LONG index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICLBookLibVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICLBookLib __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICLBookLib __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICLBookLib __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AttachWidow )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ LONG hWnd,
            /* [retval][out] */ LONG __RPC_FAR *pret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeattachWindow )( 
            ICLBookLib __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSheet )( 
            ICLBookLib __RPC_FAR * This,
            BSTR ptrName,
            LONG index,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentSheet )( 
            ICLBookLib __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *sheet);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Cols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedRows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedRows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FreezeRows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FreezeRows )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedCols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedCols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FreezeCols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FreezeCols )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrintMe )( 
            ICLBookLib __RPC_FAR * This,
            BOOL bPrintAll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TextMatrix )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TextMatrix )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowHeight )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowHeight )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColWidth )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColWidth )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG col,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BorderLineStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [retval][out] */ _tag_BorderLine __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BorderLineStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG irow,
            LONG icol,
            /* [in] */ _tag_BorderLine newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendACol )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendARow )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearCellData )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearCurrentRangeData )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyData )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PasteData )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCurrentCol )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeBkColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG clr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeForeColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG clr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeBorderLineStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nStyle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCellReadOnly )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsCellReadOnly )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeReadOnly )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            BOOL bVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveData )( 
            ICLBookLib __RPC_FAR * This,
            BSTR strFile,
            /* [retval][out] */ BOOL __RPC_FAR *pret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadData )( 
            ICLBookLib __RPC_FAR * This,
            BSTR strFile,
            /* [retval][out] */ BOOL __RPC_FAR *pret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontBold )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontItalic )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontUnderline )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontHorzAlign )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nAlign);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFontUnderline )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignLeft )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignRight )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFontBold )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFontItalic )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FocusRow )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FocusCol )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignTop )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignMiddle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignBottom )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontVertAlign )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nAlign);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeBorderColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG clr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontName )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            BSTR ptrName,
            LONG bytChatSet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentRangeFontSize )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetFontName )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetFontSize )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAlignCenter )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MergeCells )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nBeginRow,
            LONG nBeginCol,
            LONG nEndRow,
            LONG nEndCol,
            BOOL __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MergeCurrentRange )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ BOOL __RPC_FAR *bret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnMergeCurrentRange )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ BOOL __RPC_FAR *bret);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GridLineStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GridLineStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBitmapPan )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            BSTR ptrName,
            /* [retval][out] */ BOOL __RPC_FAR *bret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCurrentRow )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CutCurrentData )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertARow )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertACol )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellBkColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellBorderColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCellForeColor )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemoText )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MemoText )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG nRow,
            LONG nCol,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentSheetIndex )( 
            ICLBookLib __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentSheetIndex )( 
            ICLBookLib __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SheetCount )( 
            ICLBookLib __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SheetCaption )( 
            ICLBookLib __RPC_FAR * This,
            LONG index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SheetCaption )( 
            ICLBookLib __RPC_FAR * This,
            LONG index,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBorderLineDot )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG style);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBorderLineDot )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCashStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG style);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCashStyle )( 
            ICLBookLib __RPC_FAR * This,
            LONG sheet,
            LONG row,
            LONG col,
            /* [retval][out] */ LONG __RPC_FAR *pret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteSheet )( 
            ICLBookLib __RPC_FAR * This,
            LONG index);
        
        END_INTERFACE
    } ICLBookLibVtbl;

    interface ICLBookLib
    {
        CONST_VTBL struct ICLBookLibVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICLBookLib_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICLBookLib_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICLBookLib_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICLBookLib_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICLBookLib_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICLBookLib_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICLBookLib_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICLBookLib_AttachWidow(This,hWnd,pret)	\
    (This)->lpVtbl -> AttachWidow(This,hWnd,pret)

#define ICLBookLib_DeattachWindow(This)	\
    (This)->lpVtbl -> DeattachWindow(This)

#define ICLBookLib_AddSheet(This,ptrName,index,pVal)	\
    (This)->lpVtbl -> AddSheet(This,ptrName,index,pVal)

#define ICLBookLib_GetCurrentSheet(This,sheet)	\
    (This)->lpVtbl -> GetCurrentSheet(This,sheet)

#define ICLBookLib_get_Rows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_Rows(This,sheet,pVal)

#define ICLBookLib_put_Rows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_Rows(This,sheet,newVal)

#define ICLBookLib_get_Cols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_Cols(This,sheet,pVal)

#define ICLBookLib_put_Cols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_Cols(This,sheet,newVal)

#define ICLBookLib_get_FixedRows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FixedRows(This,sheet,pVal)

#define ICLBookLib_put_FixedRows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FixedRows(This,sheet,newVal)

#define ICLBookLib_get_FreezeRows(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FreezeRows(This,sheet,pVal)

#define ICLBookLib_put_FreezeRows(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FreezeRows(This,sheet,newVal)

#define ICLBookLib_get_FixedCols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FixedCols(This,sheet,pVal)

#define ICLBookLib_put_FixedCols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FixedCols(This,sheet,newVal)

#define ICLBookLib_get_FreezeCols(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FreezeCols(This,sheet,pVal)

#define ICLBookLib_put_FreezeCols(This,sheet,newVal)	\
    (This)->lpVtbl -> put_FreezeCols(This,sheet,newVal)

#define ICLBookLib_PrintMe(This,bPrintAll)	\
    (This)->lpVtbl -> PrintMe(This,bPrintAll)

#define ICLBookLib_get_TextMatrix(This,sheet,row,col,pVal)	\
    (This)->lpVtbl -> get_TextMatrix(This,sheet,row,col,pVal)

#define ICLBookLib_put_TextMatrix(This,sheet,row,col,newVal)	\
    (This)->lpVtbl -> put_TextMatrix(This,sheet,row,col,newVal)

#define ICLBookLib_get_RowHeight(This,sheet,row,pVal)	\
    (This)->lpVtbl -> get_RowHeight(This,sheet,row,pVal)

#define ICLBookLib_put_RowHeight(This,sheet,row,newVal)	\
    (This)->lpVtbl -> put_RowHeight(This,sheet,row,newVal)

#define ICLBookLib_get_ColWidth(This,sheet,col,pVal)	\
    (This)->lpVtbl -> get_ColWidth(This,sheet,col,pVal)

#define ICLBookLib_put_ColWidth(This,sheet,col,newVal)	\
    (This)->lpVtbl -> put_ColWidth(This,sheet,col,newVal)

#define ICLBookLib_get_BorderLineStyle(This,sheet,irow,icol,pVal)	\
    (This)->lpVtbl -> get_BorderLineStyle(This,sheet,irow,icol,pVal)

#define ICLBookLib_put_BorderLineStyle(This,sheet,irow,icol,newVal)	\
    (This)->lpVtbl -> put_BorderLineStyle(This,sheet,irow,icol,newVal)

#define ICLBookLib_AppendACol(This,sheet)	\
    (This)->lpVtbl -> AppendACol(This,sheet)

#define ICLBookLib_AppendARow(This,sheet)	\
    (This)->lpVtbl -> AppendARow(This,sheet)

#define ICLBookLib_ClearCellData(This,sheet,nRow,nCol)	\
    (This)->lpVtbl -> ClearCellData(This,sheet,nRow,nCol)

#define ICLBookLib_ClearCurrentRangeData(This,sheet)	\
    (This)->lpVtbl -> ClearCurrentRangeData(This,sheet)

#define ICLBookLib_CopyData(This,sheet)	\
    (This)->lpVtbl -> CopyData(This,sheet)

#define ICLBookLib_PasteData(This,sheet)	\
    (This)->lpVtbl -> PasteData(This,sheet)

#define ICLBookLib_DeleteCurrentCol(This,sheet)	\
    (This)->lpVtbl -> DeleteCurrentCol(This,sheet)

#define ICLBookLib_SetCurrentRangeBkColor(This,sheet,clr)	\
    (This)->lpVtbl -> SetCurrentRangeBkColor(This,sheet,clr)

#define ICLBookLib_SetCurrentRangeForeColor(This,sheet,clr)	\
    (This)->lpVtbl -> SetCurrentRangeForeColor(This,sheet,clr)

#define ICLBookLib_SetCurrentRangeBorderLineStyle(This,sheet,nStyle)	\
    (This)->lpVtbl -> SetCurrentRangeBorderLineStyle(This,sheet,nStyle)

#define ICLBookLib_get_IsCellReadOnly(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsCellReadOnly(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_put_IsCellReadOnly(This,sheet,nRow,nCol,newVal)	\
    (This)->lpVtbl -> put_IsCellReadOnly(This,sheet,nRow,nCol,newVal)

#define ICLBookLib_SetCurrentRangeReadOnly(This,sheet,bVal)	\
    (This)->lpVtbl -> SetCurrentRangeReadOnly(This,sheet,bVal)

#define ICLBookLib_SaveData(This,strFile,pret)	\
    (This)->lpVtbl -> SaveData(This,strFile,pret)

#define ICLBookLib_LoadData(This,strFile,pret)	\
    (This)->lpVtbl -> LoadData(This,strFile,pret)

#define ICLBookLib_SetCurrentRangeFontBold(This,sheet)	\
    (This)->lpVtbl -> SetCurrentRangeFontBold(This,sheet)

#define ICLBookLib_SetCurrentRangeFontItalic(This,sheet)	\
    (This)->lpVtbl -> SetCurrentRangeFontItalic(This,sheet)

#define ICLBookLib_SetCurrentRangeFontUnderline(This,sheet)	\
    (This)->lpVtbl -> SetCurrentRangeFontUnderline(This,sheet)

#define ICLBookLib_SetCurrentRangeFontHorzAlign(This,sheet,nAlign)	\
    (This)->lpVtbl -> SetCurrentRangeFontHorzAlign(This,sheet,nAlign)

#define ICLBookLib_get_IsFontUnderline(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsFontUnderline(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsAlignLeft(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignLeft(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsAlignRight(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignRight(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsFontBold(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsFontBold(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsFontItalic(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsFontItalic(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_FocusRow(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FocusRow(This,sheet,pVal)

#define ICLBookLib_get_FocusCol(This,sheet,pVal)	\
    (This)->lpVtbl -> get_FocusCol(This,sheet,pVal)

#define ICLBookLib_get_IsAlignTop(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignTop(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsAlignMiddle(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignMiddle(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsAlignBottom(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignBottom(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_SetCurrentRangeFontVertAlign(This,sheet,nAlign)	\
    (This)->lpVtbl -> SetCurrentRangeFontVertAlign(This,sheet,nAlign)

#define ICLBookLib_SetCurrentRangeBorderColor(This,sheet,clr)	\
    (This)->lpVtbl -> SetCurrentRangeBorderColor(This,sheet,clr)

#define ICLBookLib_SetCurrentRangeFontName(This,sheet,ptrName,bytChatSet)	\
    (This)->lpVtbl -> SetCurrentRangeFontName(This,sheet,ptrName,bytChatSet)

#define ICLBookLib_SetCurrentRangeFontSize(This,sheet,nSize)	\
    (This)->lpVtbl -> SetCurrentRangeFontSize(This,sheet,nSize)

#define ICLBookLib_get_GetFontName(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_GetFontName(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_GetFontSize(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_GetFontSize(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_get_IsAlignCenter(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_IsAlignCenter(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_MergeCells(This,sheet,nBeginRow,nBeginCol,nEndRow,nEndCol,retVal)	\
    (This)->lpVtbl -> MergeCells(This,sheet,nBeginRow,nBeginCol,nEndRow,nEndCol,retVal)

#define ICLBookLib_MergeCurrentRange(This,sheet,bret)	\
    (This)->lpVtbl -> MergeCurrentRange(This,sheet,bret)

#define ICLBookLib_UnMergeCurrentRange(This,sheet,bret)	\
    (This)->lpVtbl -> UnMergeCurrentRange(This,sheet,bret)

#define ICLBookLib_get_GridLineStyle(This,sheet,pVal)	\
    (This)->lpVtbl -> get_GridLineStyle(This,sheet,pVal)

#define ICLBookLib_put_GridLineStyle(This,sheet,newVal)	\
    (This)->lpVtbl -> put_GridLineStyle(This,sheet,newVal)

#define ICLBookLib_AddBitmapPan(This,sheet,ptrName,bret)	\
    (This)->lpVtbl -> AddBitmapPan(This,sheet,ptrName,bret)

#define ICLBookLib_DeleteCurrentRow(This,sheet)	\
    (This)->lpVtbl -> DeleteCurrentRow(This,sheet)

#define ICLBookLib_CutCurrentData(This,sheet)	\
    (This)->lpVtbl -> CutCurrentData(This,sheet)

#define ICLBookLib_InsertARow(This,sheet)	\
    (This)->lpVtbl -> InsertARow(This,sheet)

#define ICLBookLib_InsertACol(This,sheet)	\
    (This)->lpVtbl -> InsertACol(This,sheet)

#define ICLBookLib_get_CurrentCellBkColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellBkColor(This,sheet,pVal)

#define ICLBookLib_get_CurrentCellBorderColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellBorderColor(This,sheet,pVal)

#define ICLBookLib_get_CurrentCellForeColor(This,sheet,pVal)	\
    (This)->lpVtbl -> get_CurrentCellForeColor(This,sheet,pVal)

#define ICLBookLib_get_MemoText(This,sheet,nRow,nCol,pVal)	\
    (This)->lpVtbl -> get_MemoText(This,sheet,nRow,nCol,pVal)

#define ICLBookLib_put_MemoText(This,sheet,nRow,nCol,newVal)	\
    (This)->lpVtbl -> put_MemoText(This,sheet,nRow,nCol,newVal)

#define ICLBookLib_get_CurrentSheetIndex(This,pVal)	\
    (This)->lpVtbl -> get_CurrentSheetIndex(This,pVal)

#define ICLBookLib_put_CurrentSheetIndex(This,newVal)	\
    (This)->lpVtbl -> put_CurrentSheetIndex(This,newVal)

#define ICLBookLib_get_SheetCount(This,pVal)	\
    (This)->lpVtbl -> get_SheetCount(This,pVal)

#define ICLBookLib_get_SheetCaption(This,index,pVal)	\
    (This)->lpVtbl -> get_SheetCaption(This,index,pVal)

#define ICLBookLib_put_SheetCaption(This,index,newVal)	\
    (This)->lpVtbl -> put_SheetCaption(This,index,newVal)

#define ICLBookLib_SetBorderLineDot(This,sheet,style)	\
    (This)->lpVtbl -> SetBorderLineDot(This,sheet,style)

#define ICLBookLib_GetBorderLineDot(This,sheet,row,col,pret)	\
    (This)->lpVtbl -> GetBorderLineDot(This,sheet,row,col,pret)

#define ICLBookLib_SetCashStyle(This,sheet,style)	\
    (This)->lpVtbl -> SetCashStyle(This,sheet,style)

#define ICLBookLib_GetCashStyle(This,sheet,row,col,pret)	\
    (This)->lpVtbl -> GetCashStyle(This,sheet,row,col,pret)

#define ICLBookLib_DeleteSheet(This,index)	\
    (This)->lpVtbl -> DeleteSheet(This,index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_AttachWidow_Proxy( 
    ICLBookLib __RPC_FAR * This,
    /* [in] */ LONG hWnd,
    /* [retval][out] */ LONG __RPC_FAR *pret);


void __RPC_STUB ICLBookLib_AttachWidow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_DeattachWindow_Proxy( 
    ICLBookLib __RPC_FAR * This);


void __RPC_STUB ICLBookLib_DeattachWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_AddSheet_Proxy( 
    ICLBookLib __RPC_FAR * This,
    BSTR ptrName,
    LONG index,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_AddSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_GetCurrentSheet_Proxy( 
    ICLBookLib __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *sheet);


void __RPC_STUB ICLBookLib_GetCurrentSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_Rows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_Rows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_Cols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_Cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_Cols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_Cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FixedRows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_FixedRows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FreezeRows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FreezeRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_FreezeRows_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_FreezeRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FixedCols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_FixedCols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FreezeCols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FreezeCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_FreezeCols_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_FreezeCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_PrintMe_Proxy( 
    ICLBookLib __RPC_FAR * This,
    BOOL bPrintAll);


void __RPC_STUB ICLBookLib_PrintMe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_TextMatrix_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_TextMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_TextMatrix_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICLBookLib_put_TextMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_RowHeight_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_RowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_RowHeight_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_RowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_ColWidth_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG col,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_ColWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_ColWidth_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG col,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_ColWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_BorderLineStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG irow,
    LONG icol,
    /* [retval][out] */ _tag_BorderLine __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_BorderLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_BorderLineStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG irow,
    LONG icol,
    /* [in] */ _tag_BorderLine newVal);


void __RPC_STUB ICLBookLib_put_BorderLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_AppendACol_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_AppendACol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_AppendARow_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_AppendARow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_ClearCellData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol);


void __RPC_STUB ICLBookLib_ClearCellData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_ClearCurrentRangeData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_ClearCurrentRangeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_CopyData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_CopyData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_PasteData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_PasteData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_DeleteCurrentCol_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_DeleteCurrentCol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeBkColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG clr);


void __RPC_STUB ICLBookLib_SetCurrentRangeBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeForeColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG clr);


void __RPC_STUB ICLBookLib_SetCurrentRangeForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeBorderLineStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nStyle);


void __RPC_STUB ICLBookLib_SetCurrentRangeBorderLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsCellReadOnly_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsCellReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_IsCellReadOnly_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [in] */ BOOL newVal);


void __RPC_STUB ICLBookLib_put_IsCellReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeReadOnly_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    BOOL bVal);


void __RPC_STUB ICLBookLib_SetCurrentRangeReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SaveData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    BSTR strFile,
    /* [retval][out] */ BOOL __RPC_FAR *pret);


void __RPC_STUB ICLBookLib_SaveData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_LoadData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    BSTR strFile,
    /* [retval][out] */ BOOL __RPC_FAR *pret);


void __RPC_STUB ICLBookLib_LoadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontBold_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontItalic_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontUnderline_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontHorzAlign_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nAlign);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontHorzAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsFontUnderline_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsFontUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignLeft_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignRight_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsFontBold_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsFontBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsFontItalic_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsFontItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FocusRow_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FocusRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_FocusCol_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_FocusCol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignTop_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignMiddle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignMiddle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignBottom_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontVertAlign_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nAlign);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontVertAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeBorderColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG clr);


void __RPC_STUB ICLBookLib_SetCurrentRangeBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontName_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    BSTR ptrName,
    LONG bytChatSet);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCurrentRangeFontSize_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nSize);


void __RPC_STUB ICLBookLib_SetCurrentRangeFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_GetFontName_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_GetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_GetFontSize_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_GetFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_IsAlignCenter_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_IsAlignCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_MergeCells_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nBeginRow,
    LONG nBeginCol,
    LONG nEndRow,
    LONG nEndCol,
    BOOL __RPC_FAR *retVal);


void __RPC_STUB ICLBookLib_MergeCells_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_MergeCurrentRange_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ BOOL __RPC_FAR *bret);


void __RPC_STUB ICLBookLib_MergeCurrentRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_UnMergeCurrentRange_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ BOOL __RPC_FAR *bret);


void __RPC_STUB ICLBookLib_UnMergeCurrentRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_GridLineStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_GridLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_GridLineStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [in] */ LONG newVal);


void __RPC_STUB ICLBookLib_put_GridLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_AddBitmapPan_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    BSTR ptrName,
    /* [retval][out] */ BOOL __RPC_FAR *bret);


void __RPC_STUB ICLBookLib_AddBitmapPan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_DeleteCurrentRow_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_DeleteCurrentRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_CutCurrentData_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_CutCurrentData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_InsertARow_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_InsertARow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_InsertACol_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet);


void __RPC_STUB ICLBookLib_InsertACol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_CurrentCellBkColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_CurrentCellBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_CurrentCellBorderColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_CurrentCellBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_CurrentCellForeColor_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_CurrentCellForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_MemoText_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_MemoText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_MemoText_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG nRow,
    LONG nCol,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICLBookLib_put_MemoText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_CurrentSheetIndex_Proxy( 
    ICLBookLib __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_CurrentSheetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_CurrentSheetIndex_Proxy( 
    ICLBookLib __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ICLBookLib_put_CurrentSheetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_SheetCount_Proxy( 
    ICLBookLib __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_SheetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICLBookLib_get_SheetCaption_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICLBookLib_get_SheetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICLBookLib_put_SheetCaption_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG index,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICLBookLib_put_SheetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetBorderLineDot_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG style);


void __RPC_STUB ICLBookLib_SetBorderLineDot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_GetBorderLineDot_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [retval][out] */ LONG __RPC_FAR *pret);


void __RPC_STUB ICLBookLib_GetBorderLineDot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_SetCashStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG style);


void __RPC_STUB ICLBookLib_SetCashStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_GetCashStyle_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG sheet,
    LONG row,
    LONG col,
    /* [retval][out] */ LONG __RPC_FAR *pret);


void __RPC_STUB ICLBookLib_GetCashStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICLBookLib_DeleteSheet_Proxy( 
    ICLBookLib __RPC_FAR * This,
    LONG index);


void __RPC_STUB ICLBookLib_DeleteSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICLBookLib_INTERFACE_DEFINED__ */



#ifndef __CLGRIDBOOKLib_LIBRARY_DEFINED__
#define __CLGRIDBOOKLib_LIBRARY_DEFINED__

/* library CLGRIDBOOKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CLGRIDBOOKLib;

#ifndef ___ICLBookLibEvents_DISPINTERFACE_DEFINED__
#define ___ICLBookLibEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICLBookLibEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICLBookLibEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6066F594-F213-4363-91CC-18F3B4465CE6")
    _ICLBookLibEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICLBookLibEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ICLBookLibEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ICLBookLibEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ICLBookLibEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ICLBookLibEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ICLBookLibEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ICLBookLibEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ICLBookLibEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ICLBookLibEventsVtbl;

    interface _ICLBookLibEvents
    {
        CONST_VTBL struct _ICLBookLibEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICLBookLibEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICLBookLibEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICLBookLibEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICLBookLibEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICLBookLibEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICLBookLibEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICLBookLibEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICLBookLibEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CLBookLib;

#ifdef __cplusplus

class DECLSPEC_UUID("D3D6527B-CD33-4482-9B7A-21C8FF6929A7")
CLBookLib;
#endif
#endif /* __CLGRIDBOOKLib_LIBRARY_DEFINED__ */

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
