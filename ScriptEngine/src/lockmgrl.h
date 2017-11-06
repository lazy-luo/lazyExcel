#ifndef _LOCKMGR_H_
#define _LOCKMGR_H_
#ifdef WIN32
	#include <windows.h>
	#include <string.h>
	#include <stdio.h>
	#include <math.h>
	#include <time.h>

	#define INITCRITICAL(a)	::InitializeCriticalSection(a)
	#define DELETECRITICAL(a)	::DeleteCriticalSection(a)
	
	#define COLSEHANDLE(a) CloseHandle(a)
	#define YIELD   Sleep(0)
	#define LOCK    EnterCriticalSection
	#define UNLOCK  LeaveCriticalSection
	#define SLEEP(x)    Sleep(1000*x)
	#define SEM_HANDLE	HANDLE
	#define DELETESINGLE(a)	CloseHandle(a)
	#define INIT_SEM(a,msg) \
		a = CreateSemaphore(NULL, 0, 1, NULL);\
		if(a == NULL) {\
			printf("CreateSemaphore \"semaABC\" failed ERROR=%d\n", GetLastError());\
			assert(FALSE);\
		}
	#define SET_SINGLE(a) \
		if(!ReleaseSemaphore(a,1,0)) {\
			printf("ReleaseSema failed: error=%d\n",GetLastError());\
			assert(FALSE);\
		}
	#define GET_SINGLE(a) \
		if(WaitForSingleObject(a, INFINITE) == WAIT_FAILED) {\
			printf("Wait in ALREADY_EXISTS child failed err=%d\n",GetLastError());\
			assert(FALSE);\
		}
	//#define WAIT_ERROR	WAIT_FAILED

	#define STD_CALL	__stdcall
	typedef LPTHREAD_START_ROUTINE ThreadEntry;
	#define CREATE_THREAD(a,b,c) \
		CreateThread(NULL,0,(ThreadEntry)a,(void*)b,0,(LPDWORD)c)
#else//Unix/Linux
	#include <unistd.h>
	#include <pthread.h>
	#include <time.h>
	#include <string.h>
	#include <sys/sem.h>
	#include <stdlib.h>
	#include <semaphore.h>
	#define CRITICAL_SECTION pthread_mutex_t
	#define INITCRITICAL(a)	pthread_mutex_init(a,NULL)
	#define DELETECRITICAL(a)
	
	#define COLSEHANDLE(a)
	#define YIELD   sched_yield()
	#define LOCK    pthread_mutex_lock
	#define UNLOCK  pthread_mutex_unlock
	#define SLEEP(x)    sleep(x)
	#define SEM_HANDLE	sem_t
	#define DELETESINGLE(a)	sem_destroy(&a)
	#define INIT_SEM(a,msg) \
		if(sem_init(&a,0,1) == -1) {\
			printf("sem_init FAILED: err=%d\n", errno);\
			assert(FALSE);\
		}
	#define SET_SINGLE(a) \
		if(sem_post(&a) == -1) {\
            printf("sem_post FAILED: err=%d\n", errno);\
            assert(FALSE);\
        }
	#define GET_SINGLE(a) sem_wait(a)//得到信号量
	#define WAIT_ERROR	-1
	#define STD_CALL

	typedef void* (*ThreadEntry)(void*);
	#define CREATE_THREAD(a,b,c) pthread_create (c, NULL, (ThreadEntry)a, (void*)b)
#endif

class CLCSWrapper
{
public:
	CLCSWrapper():m_nSpinCount(0){
		INITCRITICAL(&m_cs);
	};
	virtual ~CLCSWrapper(){DELETECRITICAL(&m_cs );};
	inline void Enter(){
		LOCK(&m_cs);
		m_nSpinCount++;
	};
	inline void Leave(){
		m_nSpinCount--;
		UNLOCK(&m_cs);
	};
private:
	CRITICAL_SECTION m_cs;
	long m_nSpinCount;
};

template <class T>
class CLLockMgr  
{
public:
	
	CLLockMgr(T& lockObject):
		m_rLockObject( lockObject )
	{
		m_rLockObject.Enter();
	}
	virtual ~CLLockMgr()
	{
		m_rLockObject.Leave();
	}
private:
	T&   m_rLockObject;
};

#endif //_LOCKMGR_H_