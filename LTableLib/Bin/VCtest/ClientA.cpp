// ClientA.cpp: implementation of the CClientA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientA.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientA::CClientA()
{

}

CClientA::~CClientA()
{

}
LONG CClientA::CallBackProc(LONG msg,LPVOID param,BOOL& bCancel)
{
	char* ptrText=(char*)param;
	MessageBox(NULL,ptrText,"CClientA",MB_OK);
	return 0;
}