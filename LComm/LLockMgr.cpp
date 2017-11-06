#include "StdAfx.h"
#include "LLockMgr.h"

CLCSWrapper::CLCSWrapper()
{
	m_nSpinCount = 0;
	::InitializeCriticalSection( &m_cs );
}

CLCSWrapper::~CLCSWrapper()
{
	::DeleteCriticalSection( &m_cs );
}

void CLCSWrapper::Enter()
{
	::EnterCriticalSection( &m_cs );
	m_nSpinCount++;
}

void CLCSWrapper::Leave()
{
	m_nSpinCount--;
	::LeaveCriticalSection( &m_cs );
}

