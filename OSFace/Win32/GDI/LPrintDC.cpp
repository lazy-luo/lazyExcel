// LPrintDC.cpp: implementation of the CLPrintDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../LGUILib/Src/LDrawerSheet.h"
#include <Commdlg.h>
#include <cderr.h>
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX      2147483647L   /* maximum (signed) long value */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT CALLBACK SetupHookProc(
  HWND hdlg,      // handle to the dialog box window
  UINT uiMsg,     // message identifier
  WPARAM wParam,  // message parameter
  LPARAM lParam   // message parameter
){
	return 0;
}
UINT CALLBACK PrintHookProc(
  HWND hdlg,      // handle to the dialog box window
  UINT uiMsg,     // message identifier
  WPARAM wParam,  // message parameter
  LPARAM lParam   // message parameter
){
	switch(uiMsg){
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDABORT:
				MessageBox(hdlg,"dsfdsf",NULL,MB_OK);
				break;
			}
			break;
		case WM_PSD_PAGESETUPDLG:
			//MessageBox(hdlg,"dsfdsf",NULL,MB_OK);
			break;
	}
	return 0;
}

static long MultMultDivDiv(int factor, int num1, int num2,int den1, int den2);
CLPrintDC::CLPrintDC():m_pSheet(NULL)
{
	
}

CLPrintDC::~CLPrintDC()
{

}

BOOL CLPrintDC::PrintSetup(HWND hWnd,LONG nPages)
{
	ASSERT(m_pSheet);
	RECT rctW;
	BOOL bZero=FALSE;
	if(nPages<=0){
		bZero=TRUE;
		//if(m_pRptSet->m_hWnd!=NULL){
			//nPages=m_pRptSet->Pages();
		//}else{
			nPages=1;
		//}
	}
	
	PRINTDLG pd;
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC | PD_ENABLEPRINTHOOK;
	pd.hDC = NULL;
	pd.hwndOwner = hWnd;
	pd.hInstance = NULL;
	pd.nMaxPage=(nPages>1?nPages:2);
	if(!bZero)
		pd.nMaxPage = nPages;
	pd.nMinPage = 1;
	pd.nFromPage = 1;
	pd.nToPage  = nPages;
	pd.nCopies = 1;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
	pd.lpfnSetupHook =SetupHookProc;
	pd.lpfnPrintHook =PrintHookProc;
	
	//显示打印对话框，由用户来设定纸张大小等。
	if(!PrintDlg(&pd)) {
#ifdef _DEBUG
		switch(CommDlgExtendedError()){
		case PDERR_INITFAILURE:
			MessageBox(NULL,"PDERR_INITFAILURE","OK",MB_OK);
			break;
		case PDERR_LOADDRVFAILURE:
			MessageBox(NULL,"PDERR_LOADDRVFAILURE","OK",MB_OK);
			break;
		default:
			break;
		}
#endif
		return FALSE; 
	}
	
	ASSERT(pd.hDC!=NULL);
	nPages=pd.nToPage;
	SetMapMode(pd.hDC,MM_ANISOTROPIC);
	//转换坐标映射方式
	
    SIZE size;
    //得到实际设备每逻辑英寸的像素数量
    int xLogPixPerInch = GetDeviceCaps(pd.hDC,LOGPIXELSX); 
    int yLogPixPerInch = GetDeviceCaps(pd.hDC,LOGPIXELSY);
	HDC hScreenDC=GetDC(GetDesktopWindow());
	int xLogPixPerInchS = GetDeviceCaps(hScreenDC,LOGPIXELSX); 
    int yLogPixPerInchS = GetDeviceCaps(hScreenDC,LOGPIXELSY);

	
    //得到设备坐标和逻辑坐标的比例
	int nHorRes = GetDeviceCaps(pd.hDC, HORZRES);	
	int nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	size.cx=GetDeviceCaps(hScreenDC,HORZSIZE);
	size.cy=GetDeviceCaps(hScreenDC,VERTSIZE);

	ReleaseDC(GetDesktopWindow(),hScreenDC);
	SetWindowExtEx(pd.hDC,size.cx,size.cy,NULL);
	float fScX=(float)xLogPixPerInch/(float)xLogPixPerInchS;
	float fScY=(float)yLogPixPerInch/(float)yLogPixPerInchS;
    long xExt = (long)(size.cx*fScX);
    long yExt = (long)(size.cy*fScY);
	m_pSheet->SetScale(fScX,fScY);
	SetViewportExtEx(pd.hDC,(int)xExt, (int)yExt,NULL);	
	rctW.left=0;
	rctW.top=0;
	rctW.right=nHorRes;///fScX;
	rctW.bottom=nVerRes;///fScY;
	
	int nXMargin = 2;
	int nYMargin = 2;
	TEXTMETRIC tm;
	GetTextMetrics(pd.hDC, &tm);
	int nCharHeight = tm.tmHeight;
	int nCharWidth = tm.tmAveCharWidth;
	int nColX =nXMargin*nCharWidth;
	
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName ="kjhkj";// m_pRptSet->GetCaption(); 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	
	RECT rct;
	rct.left=-1;
	StartDoc(pd.hDC, &di);
	
	CopyRect(&rct,&rctW);

	LONG nBegin=1;
	
	if(m_pSheet){
		//nPages=m_pSheet->GetPageCount(&rctW);
	}

	if(pd.Flags & PD_PAGENUMS){
		nBegin=pd.nFromPage;
		nPages=pd.nToPage;
	}
	HDCH hdc;
	hdc.bIsPrint=TRUE;
	hdc.bPrintFixed=FALSE;
	hdc.hDC=pd.hDC;
	for(int iPage=nBegin;iPage<=nPages;iPage++){
		StartPage(pd.hDC);
		if(rct.left>=0){
			CopyRect(&rctW,&rct);
			if(m_pSheet){
				m_pSheet->OnPrint(&hdc,rctW);
			}
		}
		EndPage(pd.hDC);
	}
	EndDoc(pd.hDC);
	//打印结束
	DeleteDC(pd.hDC);
	m_pSheet->SetScale(1,1);
	return TRUE;

}


void CLPrintDC::AttachObject(CLDrawerSheet* ptrV,ISheet* ptrSheet)
{
	if(NULL==m_pSheet && ptrV && ptrSheet){
		m_pSheet=ptrV;
		m_pSheet->AttachSheet(ptrSheet);
	}
}

HANDLE CLPrintDC::GetPrinterHandle(LPTSTR szPrinterName)
{
	HANDLE hPrinter = NULL;
	/*
    PRINTER_DEFAULTS pds;
    ZeroMemory(&pds, sizeof(PRINTER_DEFAULTS));
    pds.DesiredAccess = PRINTER_ALL_ACCESS;
    OpenPrinter(szPrinterName, &hPrinter, &pds);
	*/
	return hPrinter;
}
void CLPrintDC::MirrorMappingMode(HDC hDCScreen,int nScaleDen,int nScaleNum)
{
	ASSERT(hPrintDC);
	SIZE sizeVpExt,sizeWinExt;
	if (hDCScreen != NULL)
	{

		::GetViewportExtEx(hDCScreen, &sizeVpExt);
		::GetWindowExtEx(hDCScreen, &sizeWinExt);

		int nFactor = 0x900;
		if (nScaleNum > nScaleDen)
			nFactor = MulDiv(nFactor, nScaleDen, nScaleNum);
		else
			nFactor = MulDiv(nFactor, nScaleNum, nScaleDen);
		int nLogPixelsX = ::GetDeviceCaps(hPrintDC, LOGPIXELSX);
		int nAttribLogPixelsX = ::GetDeviceCaps(hDCScreen, LOGPIXELSX);
		if (nLogPixelsX > nAttribLogPixelsX)
			nFactor = MulDiv(nFactor, nAttribLogPixelsX, nLogPixelsX);
		else
			nFactor = MulDiv(nFactor, nLogPixelsX, nAttribLogPixelsX);

		while (sizeWinExt.cx > -nFactor && sizeWinExt.cx < nFactor &&
			   sizeVpExt.cx  > -nFactor && sizeVpExt.cx  < nFactor)
		{
			sizeWinExt.cx <<= 1;
			sizeVpExt.cx  <<= 1;
		}

		while (sizeWinExt.cy > -nFactor && sizeWinExt.cy < nFactor &&
			   sizeVpExt.cy  > -nFactor && sizeVpExt.cy  < nFactor)
		{
			sizeWinExt.cy <<= 1;
			sizeVpExt.cy  <<= 1;
		}

		long lTempExt = MultMultDivDiv(sizeVpExt.cx,
			nScaleNum, ::GetDeviceCaps(hPrintDC, LOGPIXELSX),
			nScaleDen, ::GetDeviceCaps(hDCScreen, LOGPIXELSX));

		ASSERT(sizeWinExt.cx != 0);
		sizeVpExt.cx = (int)lTempExt;

		lTempExt = MultMultDivDiv(sizeVpExt.cy,
			nScaleNum, ::GetDeviceCaps(hPrintDC, LOGPIXELSY),
			nScaleDen, ::GetDeviceCaps(hDCScreen, LOGPIXELSY));

		ASSERT(sizeWinExt.cy != 0);
		sizeVpExt.cy = (int)lTempExt;
	}

	if (hPrintDC != NULL)
	{
		::SetMapMode(hPrintDC, MM_ANISOTROPIC);
		::SetWindowExtEx(hPrintDC, sizeWinExt.cx, sizeWinExt.cy, NULL);
		::SetViewportExtEx(hPrintDC, sizeVpExt.cx, sizeVpExt.cy, NULL);
		//MirrorViewportOrg();
	}
}
static long MultMultDivDiv(int factor, int num1, int num2,
	int den1, int den2)
{
#if defined(_AFX_PORTABLE) || defined(_MAC)
	// make sure that (num1 * num2) does not overflow 31-bits.
	long temp = num1 < 0 ? -num1 : num1;
	for (int nBitsResult = 0; temp != 0; nBitsResult++)
		temp >>= 1;
	temp = num2 < 0 ? -num2 : num2;
	for (; temp != 0; nBitsResult++)
		temp >>= 1;
	if (nBitsResult > 31)
	{
		num1 >>= nBitsResult - 31;
		num2 >>= nBitsResult - 31;
	}

	// make sure that (den1 * den2) does not overflow 31-bits
	temp = den1 < 0 ? -den1 : den1;
	for (nBitsResult = 0; temp != 0; nBitsResult++)
		temp >>= 1;
	temp = den2 < 0 ? -den2 : den2;
	for (; temp != 0; nBitsResult++)
		temp >>= 1;
	if (nBitsResult > 31)
	{
		den1 >>= nBitsResult - 31;
		den2 >>= nBitsResult - 31;
	}

	long numerator = (long)num1 * (long)num2;   // no overflow
	long denominator = (long)den1 * (long)den2; // no overflow
#else
	__int64 numerator = (__int64)num1 * (__int64)num2;   // no overflow
	__int64 denominator = (__int64)den1 * (__int64)den2; // no overflow
	__int64 temp;
#endif

	temp = numerator < 0 ? -numerator : numerator;
	for (int nBitsInNum = 0; temp != 0; nBitsInNum++)
		temp >>= 1;

	temp = factor < 0 ? -factor : factor;
	for (int nBitsInFactor = 0; temp != 0; nBitsInFactor++)
		temp >>= 1;

	nBitsInNum += nBitsInFactor;

	if (denominator < 0)
	{
		denominator = -denominator;
		numerator = -numerator;
	}
	while (nBitsInNum-- > 31)
	{
		numerator >>= 1;
		denominator >>= 1;
		if (nBitsInNum-- <= 31)
			break;
		numerator >>= 1;
		denominator >>= 1;
		if (nBitsInNum-- <= 31)
			break;
		factor >>= 1;
		denominator >>= 1;
	}
	numerator *= factor;

	if (denominator == 0)
		return numerator < 0 ? LONG_MIN : LONG_MAX;

	return (long) ((numerator + denominator/2) / denominator);
}
