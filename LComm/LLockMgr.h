#ifndef _LOCKMGR_H_
#define _LOCKMGR_H_
#include "LGlobalParam.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class EXPORT_G_CLASS CLCSWrapper
{
public:
	CLCSWrapper();
	virtual ~CLCSWrapper();

	void Enter();

	void Leave();
private:
	CRITICAL_SECTION m_cs;
	long m_nSpinCount;
};

template <class T>
class EXPORT_G_CLASS CLLockMgr  
{
public:

	CLLockMgr(T& lockObject, BOOL bEnabled):
		m_rLockObject( lockObject ),
		m_bEnabled( bEnabled )
	{
		if ( m_bEnabled );
			m_rLockObject.Enter();
	}

	virtual ~CLLockMgr()
	{
		if ( m_bEnabled );
			m_rLockObject.Leave();
	}
private:
	T&   m_rLockObject;
	BOOL m_bEnabled;
};

#endif //_LOCKMGR_H_