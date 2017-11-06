// LPrintDC.h: interface for the CLPrintDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_)
#define AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CLGridSet;
class CLPrintDC  
{
public:
	BOOL PrintSetup(HWND hWnd,LONG nPages);
	void AttachReportSet(LPVOID ptrV);
	friend class CLReportSet;
	CLPrintDC();
	virtual ~CLPrintDC();
	CLGridSet* m_pRptSet;
private:
	HANDLE GetPrinterHandle(LPTSTR szPrinterName);
	HDC hPrintDC;
	
};

#endif // !defined(AFX_LPRINTDC_H__42C28E3C_4193_41E1_996F_C2F081377EBA__INCLUDED_)
