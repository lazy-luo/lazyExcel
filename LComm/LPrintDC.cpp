// LPrintDC.cpp: implementation of the CLPrintDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LPrintDC.h"
#include "../../GridSetSrc/LGridSet.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLPrintDC::CLPrintDC():m_pRptSet(NULL)
{
	
}

CLPrintDC::~CLPrintDC()
{

}

BOOL CLPrintDC::PrintSetup(HWND hWnd,LONG nPages)
{
	ASSERT(m_pRptSet);
	RECT rctW;
	BOOL bZero=FALSE;
	if(nPages<=0){
		bZero=TRUE;
		nPages=m_pRptSet->GetPageCount();
	}
	
	PRINTDLG pd;
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC;
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
    SIZE size,sizeV;

    GetWindowExtEx(pd.hDC,&size);      //确定窗口大小
    //得到实际设备每逻辑英寸的像素数量
    int xLogPixPerInch = GetDeviceCaps(pd.hDC,LOGPIXELSX); 
    int yLogPixPerInch = GetDeviceCaps(pd.hDC,LOGPIXELSY);

	int xLogPixPerInchS = GetDeviceCaps(GetDC(GetDesktopWindow()),LOGPIXELSX); 
    int yLogPixPerInchS = GetDeviceCaps(GetDC(GetDesktopWindow()),LOGPIXELSY);
    //得到设备坐标和逻辑坐标的比例
	//GetWindowExtEx(pd.hDC,&size);
	size.cx*=64;
	size.cy*=64;
	SetWindowExtEx(pd.hDC,size.cx,size.cy,NULL);    

	GetViewportExtEx(pd.hDC,&sizeV);
	float fDltX=(float)xLogPixPerInch/xLogPixPerInchS;
	float fDltY=(float)yLogPixPerInch/yLogPixPerInchS;

    long xExt = (long)size.cx*fDltX ;
    long yExt = (long)size.cy*fDltY ;
	SetViewportExtEx(pd.hDC,(int)xExt, (int)yExt,NULL);

	int nHorRes = GetDeviceCaps(pd.hDC, HORZRES);	
	int nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	rctW.left=0;
	rctW.top=0;
	rctW.right=nHorRes/fDltX;
	rctW.bottom=nVerRes/fDltY;

	int nXMargin = 2;
	int nYMargin = 2;
	TEXTMETRIC tm;
	GetTextMetrics(pd.hDC, &tm);
	int nCharHeight = tm.tmHeight;
	int nCharWidth = tm.tmAveCharWidth;
	int nColX =nXMargin*nCharWidth;

	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = m_pRptSet->GetGridName(); 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	
	RECT rct;
	rct.left=-1;
	StartDoc(pd.hDC, &di);
	
	
	CopyRect(&rct,&rctW);
	/*
	if(pd.hDevMode){
		LPDEVMODE pdm=(LPDEVMODE)GlobalLock(pd.hDevMode);    
		LPTSTR strPrinterName=NULL;
		
		strPrinterName=(LPTSTR)pdm->dmDeviceName;
		
		HANDLE hPrinter = GetPrinterHandle(strPrinterName);
		FORM_INFO_1  finfo;
		finfo.Flags=FORM_PRINTER;
		DWORD dwNum=0,dwLen=0;
		if (hPrinter)
		{
			LONG dmDrect=pdm->dmOrientation;
			if(!GetForm(hPrinter,(char*)pdm->dmFormName,1,(LPBYTE)&finfo,dwLen,&dwNum)){
				if(GetForm(hPrinter,(char*)pdm->dmFormName,1,(LPBYTE)&finfo,dwNum,&dwNum)){
					rctW.left=0;
					rctW.top=0;
					//纸张方向
					if(dmDrect==DMORIENT_PORTRAIT){
						rctW.right=(finfo.Size.cx/10000)*32 ;
						rctW.bottom=(finfo.Size.cy/10000)*32 ;
					}else{
						rctW.bottom =(finfo.Size.cx/10000)*40 ;
						rctW.right =(finfo.Size.cy/10000)*40 ;
					}
					CopyRect(&rct,&rctW);
				}
			}
			ClosePrinter(hPrinter);
		}
	}
	GlobalFree(pd.hDevMode);
	*/
	LONG nBegin=1;
	
	if(m_pRptSet){
		nPages=m_pRptSet->GetPageCount(rctW);
	}

	
	if(pd.Flags & PD_PAGENUMS){
		nBegin=pd.nFromPage;
		nPages=pd.nToPage;
	}
	DRAWER drawer;
	drawer.m_bIsPrinting=TRUE;
	drawer.m_hDC=pd.hDC;
	drawer.m_Rect=rct;
	for(int iPage=nBegin;iPage<=nPages;iPage++){
		StartPage(pd.hDC);
		if(rct.left>=0){
			//CopyRect(&rctW,&rct);
			drawer.m_nCurrPageNO=iPage;
			if(m_pRptSet){
				m_pRptSet->OnDraw(drawer);
			}
		}
		EndPage(pd.hDC);
	}
	EndDoc(pd.hDC);
	//打印结束
	DeleteDC(pd.hDC);
	return TRUE;

}

void CLPrintDC::AttachReportSet(LPVOID ptrV)
{
	if(NULL==m_pRptSet && ptrV){
		m_pRptSet=(CLGridSet*)ptrV;
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