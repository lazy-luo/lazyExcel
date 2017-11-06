// ClientA.h: interface for the CClientA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTA_H__9C771582_5B71_43EE_92DB_617393846D36__INCLUDED_)
#define AFX_CLIENTA_H__9C771582_5B71_43EE_92DB_617393846D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../Src/LTable.h"
class CClientA : public ILCallBack  
{
public:
	CClientA();
	virtual ~CClientA();
	virtual LONG CallBackProc(LONG msg,LPVOID param,BOOL& bCancel);
};

#endif // !defined(AFX_CLIENTA_H__9C771582_5B71_43EE_92DB_617393846D36__INCLUDED_)
