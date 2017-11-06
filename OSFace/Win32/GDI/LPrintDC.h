// LPrintDC.h: interface for the CLPrintDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_)
#define AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CLDrawerSheet;
class ISheet;
class CLPrintDC  
{
public:
	BOOL PrintSetup(HWND hWnd=NULL,LONG nPages=-1);
	void AttachObject(CLDrawerSheet* ptrV,ISheet* ptrSheet);
	CLPrintDC();
	virtual ~CLPrintDC();
	CLDrawerSheet* m_pSheet;
private:
	void MirrorMappingMode(HDC hDCScreen,int nScaleDen,int nScaleNum);
	HANDLE GetPrinterHandle(LPTSTR szPrinterName);
	HDC hPrintDC;
	
};

#endif // !defined(AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_)
