//////////////////////////////////////////////////////////////////////
//@模块		:	公共定义类
//@作者		:	罗智勇
//@创建时间	:	2005-11-05
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPUBLICDEF_H__36851820_2895_4B94_9110_285063B671CE__INCLUDED_)
#define AFX_LPUBLICDEF_H__36851820_2895_4B94_9110_285063B671CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../LComm/LScript_Engine.h"
#include "../../LComm/LMap.h"
#include "LTableApi.h"
#include "../Interface/LInterface.h"
#include "../../LComm/LSerial.h"

#include "../../LComm/LCommBase.h"
//#define USE_MAP_A
#ifdef USE_MAP_A
#define BASE_CLASS LMap<LONG,LONG&,NODE*,NODE*&>
#else
#define BASE_CLASS CLMapBase<LONG,NODE>
#endif
class CLCallServ:private BASE_CLASS,public ICallServ
{
private:
#ifdef USE_MAP_A
	void ClearAll()
	{
		LONG key;
		NODE* ptrItem=NULL;
		POSITION pos = GetStartPosition();
		while (pos != NULL)
		{
			GetNextAssoc(pos, key, ptrItem);
			delete ptrItem;
		}
		RemoveAll(); 
	}
#endif
public:
	CLCallServ():BASE_CLASS(40,100){};
	~CLCallServ()
	{
#ifdef USE_MAP_A
		ClearAll();
#endif
	}
	virtual LONG NotifyMessage(LONG msgID,LPVOID param){
		NODE* ptrN=NULL;
#ifdef USE_MAP_A
			if(!Lookup(msgID,ptrN))return -1;
#else
			ptrN=GetValue(msgID);
#endif
		BOOL bCancel=FALSE;
		if(ptrN){
			CHAIN* ptrV=ptrN->m_pchain;
			if(ptrV && !ptrV->isEmpty()){
				ICallBack* ptrCall;
				while(ptrV && ptrV->ptrData){
					ptrCall=(ICallBack*)ptrV->ptrData;
					ptrCall->CallBackProc(msgID,param,bCancel);
					if(bCancel)
						break;
					ptrV=ptrV->ptrNext;
				}
			}
		}else
			return -1;
		return 0;
	};//服务器端消息转发
	virtual LONG AddLinstener(ICallBack* ptrObj,LONG msgID,BOOL bAddHeader=TRUE){
		if(!ptrObj)return 0;
		NODE* ptrN=NULL;
#ifdef USE_MAP_A
		if(!Lookup(msgID,ptrN)){
			ptrN=new NODE();
			SetAt(msgID,ptrN);
		}
#else
		ptrN=GetValue(msgID,TRUE);
#endif
		CHAIN* ptrV=ptrN->m_pchain;
		if(!ptrV){
			ptrV=new CHAIN();
			ptrN->m_pchain=ptrV;
			ptrV->ptrData=(LPVOID)ptrObj;
		}else{
			CHAIN* ptrT,*ptrPre;
			for(ptrT=ptrV;ptrT && ptrT->ptrData!=(LPVOID)ptrObj;ptrPre=ptrT,ptrT=ptrT->ptrNext);
			if(!ptrT){
				//没有找到对象映射
				ptrT=new CHAIN();
				if(bAddHeader){
					ptrN->m_pchain=ptrT;
					ptrN->m_pchain->ptrNext=ptrV;
				}else{
					ptrPre->ptrNext=ptrT;
				}
				ptrT->ptrData=(LPVOID)ptrObj;
			}
		}
		return 0;
	};//增加消息订阅者
	virtual LONG RemoveListener(ICallBack* ptrObj,LONG msgID){
		if(!ptrObj)return 0;
		NODE* ptrN=NULL;
#ifdef USE_MAP_A
		if(!Lookup(msgID,ptrN))return 0;
#else
		ptrN=GetValue(msgID);
#endif
		CHAIN* ptrV=ptrN->m_pchain;
		if(!ptrV){
#ifdef USE_MAP_A
			RemoveKey(msgID);
#else
			DeleteValue(msgID);
#endif
			return 0;
		}
		BOOL bFind=FALSE,bTail=FALSE;
		CHAIN* ptrT;
		ptrT=ptrV;
		while(ptrV){
			if(ptrV->ptrData==(LPVOID)ptrObj){
				bFind=TRUE;
				bTail=(!ptrV->ptrNext);
				break;
			}
			ptrT=ptrV;
			ptrV=ptrV->ptrNext;
		}
		if(bFind){
			if(ptrV==ptrN->m_pchain){
				if(bTail){
#ifdef USE_MAP_A
					RemoveKey(msgID);
#else
					DeleteValue(msgID);
#endif
					return 0;
				}else{
					ptrN->m_pchain=ptrV->ptrNext;
					ptrV->ptrNext=NULL;
				}
			}else{
				if(bTail){
					ptrT->ptrNext=NULL;
				}else{
					//在中间
					ptrT->ptrNext=ptrV->ptrNext;
					ptrV->ptrNext=NULL;
				}
			}
			delete ptrV;
		}
		return 0;
	};
	virtual LONG ClearListener(LONG msgID){
#ifdef USE_MAP_A
		NODE* ptrN=NULL;
		if(Lookup(msgID,ptrN)){
			delete ptrN;
		}
		RemoveKey(msgID);
#else
		DeleteValue(msgID);
#endif
		return 0;
	};
};

#endif