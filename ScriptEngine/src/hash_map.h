///////////////////////////////////////////////////////////////////////////////////////
//@module		:	Hash对象集合类
//@author		:	zhiyong.luo
//@create date	:	2006-10-08
//@last_modify	:	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASH_MAP_H__36851820_2895_4B94_9110_285063B671CE__INCLUDED_)
#define AFX_HASH_MAP_H__36851820_2895_4B94_9110_285063B671CE__INCLUDED_
#include <string>
using namespace std;
#ifndef __DEF_POSITION
	struct _POSITION {};
	typedef _POSITION* POSITION;
#endif
#define BEFORE_START_POSITION ((POSITION)-1L)
#ifdef _DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif
struct LPlex   
{
	LPlex* pNext;
	LPlex():pNext(NULL){}
	void* data() { return this+1; }
	//分配内存块
	static LPlex* Create(LPlex*& head, UINT nMax, UINT cbElement){
		ASSERT(nMax > 0 && cbElement > 0);
		LPlex* p = (LPlex*) new BYTE[sizeof(LPlex) + nMax * cbElement];
		p->pNext = head;
		head = p;  
		return p;
	}
	//释放内存
	void FreeDataChain(){
		LPlex* p = this;
		while (p != NULL){
			BYTE* bytes = (BYTE*) p;
			LPlex* pNext = p->pNext;
			delete[] bytes;
			p = pNext;
		}
	}
};

template<class TYPE, class ARG_TYPE>
BOOL WINAPI CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
{
	return *pElement1 == *pElement2;
}
template<class ARG_KEY>
INLINE DLONG WINAPI HashKey(ARG_KEY key)
{
	return ((DLONG)(void*)(DWORD)key);
}
template<>
INLINE DLONG WINAPI HashKey<INT&>(INT& key){
	return (DLONG)key;
}
template<>
INLINE DLONG WINAPI HashKey<const char*>(const char* str ){
	int i,l; 
	unsigned long ret=0; 
	unsigned short *s; 
	if (str == NULL) return(0); 
	l=(strlen(str)+1)/2; 
	s=(unsigned short *)str; 
	for (i=0; i < l;i++)
		ret^=(s[i]<<(i&0x0F)); 
	return(DLONG)(ret); 
}
template<>
INLINE DLONG WINAPI HashKey<string&>(string& key)
{
	return HashKey<const char*>(key.c_str());
}
template<class TYPE>
INLINE void WINAPI ConstructElements(TYPE* pElements, int nCount)
{
	ASSERT(nCount != 0);
	memset((void*)pElements, 0, nCount * sizeof(TYPE));
	for (; nCount--; pElements++){
#ifndef _DEBUG_MEM
		new ((void*)pElements) TYPE;
#else
		TYPE tmp;
		memcpy((void*)pElements, (void*)(&tmp),sizeof(TYPE));
#endif
	}
}

template<class TYPE>
INLINE void WINAPI DestructElements(TYPE* pElements, int nCount)
{
	ASSERT(nCount != 0);
	for (; nCount--; pElements++)
		pElements->~TYPE();
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class LMap
{
protected:
	//定义哈希表结构
	struct CAssoc{
		CAssoc* pNext;
		KEY key;
		VALUE value;
	};
public:
	LMap(int nBlockSize = HASH_BIG_BLOCK_SIZE,int nHashTbSize=HASH_BIG_ARR_SIZE);
	int GetCount() const;
	BOOL IsEmpty() const;
	BOOL Lookup(ARG_KEY key, VALUE*& rValue,BOOL bForceNew=FALSE);
	BOOL Lookup(ARG_KEY key, VALUE& rValue) const;
	VALUE& operator[](ARG_KEY key);
	void SetAt(ARG_KEY key, ARG_VALUE newValue);
	BOOL RemoveKey(ARG_KEY key);
	void RemoveAll();
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct LPlex* m_pBlocks;
	int m_nBlockSize;
	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(ARG_KEY, UINT&) const;
public:
	~LMap();
};

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
INLINE int LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetCount() const
	{ return m_nCount; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
INLINE BOOL LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::IsEmpty() const
	{ return m_nCount == 0; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
INLINE void LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::SetAt(ARG_KEY key, ARG_VALUE newValue)
	{ (*this)[key] = newValue; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
INLINE POSITION LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
INLINE UINT LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetHashTableSize() const
	{ return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::LMap(int nBlockSize,int nHashTbSize)
{
	ASSERT(nBlockSize > 0);
	m_pHashTable = NULL;
	m_nHashTableSize = nHashTbSize;  
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::InitHashTable(
	UINT nHashSize, BOOL bAllocNow)
{
	ASSERT(this);
	if (m_pHashTable != NULL){
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}

	if (bAllocNow){
		m_pHashTable = new CAssoc* [nHashSize];
		memset(m_pHashTable, 0, sizeof(CAssoc*) * nHashSize);
	}
	m_nHashTableSize = nHashSize;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveAll()
{
	ASSERT(this);

	if (m_pHashTable != NULL){
		for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++){
			CAssoc* pAssoc;
			for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
			  pAssoc = pAssoc->pNext){
				DestructElements<VALUE>(&pAssoc->value, 1);
				DestructElements<KEY>(&pAssoc->key, 1);
			}
		}
	}
	if(m_pHashTable)
		delete[] m_pHashTable;
	m_pHashTable = NULL;
	
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	
	m_pBlocks = NULL;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::~LMap()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::CAssoc*
LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::NewAssoc()
{
	if (m_pFreeList == NULL){
		LPlex* newBlock = LPlex::Create(m_pBlocks, m_nBlockSize, sizeof(LMap::CAssoc));
		LMap::CAssoc* pAssoc = (LMap::CAssoc*) newBlock->data();
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--){
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	ASSERT(m_pFreeList != NULL); 
	LMap::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);
	ConstructElements<KEY>(&pAssoc->key, 1);
	ConstructElements<VALUE>(&pAssoc->value, 1); 
	return pAssoc;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::FreeAssoc(typename LMap::CAssoc* pAssoc){
	DestructElements<VALUE>(&pAssoc->value, 1);
	DestructElements<KEY>(&pAssoc->key, 1);
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	ASSERT(m_nCount >= 0); 
	if (m_nCount == 0)
		RemoveAll();
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::CAssoc*
LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetAssocAt(ARG_KEY key, UINT& nHash) const{
	nHash = (UINT)(HashKey<ARG_KEY>(key) % m_nHashTableSize);
	if (m_pHashTable == NULL)
		return NULL;
	CAssoc* pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext){
		if (CompareElements(&pAssoc->key, &key))
			return pAssoc;
	}
	return NULL;
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(ARG_KEY key, VALUE*& rValue,BOOL bForceNew){
	ASSERT(this);
	UINT nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL){
		if(bForceNew){
			rValue=&((*this)[key]);
			bForceNew=FALSE;
			return 2;
		}else{
			rValue=NULL;
			return FALSE; 
		}
	}
	rValue = &(pAssoc->value);
	
	return 1;
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(ARG_KEY key, VALUE& rValue) const{
	ASSERT(this);

	UINT nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
		return FALSE; 

	rValue = pAssoc->value;
	return 1;
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key){
	ASSERT(this);

	UINT nHash;
	CAssoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL){
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);
		pAssoc = NewAssoc();
		pAssoc->key = key;
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;  
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveKey(ARG_KEY key){
	ASSERT(this);
	if (m_pHashTable == NULL)
		return FALSE; 
	CAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[HashKey<ARG_KEY>(key) % m_nHashTableSize];
	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext){
		if (CompareElements(&pAssoc->key, &key)){
			*ppAssocPrev = pAssoc->pNext; 
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE; 
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void LMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc(POSITION& rNextPosition,
	KEY& rKey, VALUE& rValue) const{
	ASSERT(this);
	ASSERT(m_pHashTable != NULL); 

	CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	ASSERT(pAssocRet != NULL);
	if (pAssocRet == (CAssoc*) BEFORE_START_POSITION){
		for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		ASSERT(pAssocRet != NULL); 
	}

	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL){
		for (UINT nBucket = ((UINT)(HashKey<ARG_KEY>(pAssocRet->key) % m_nHashTableSize)) + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}
	rNextPosition = (POSITION) pAssocNext;
	//回填返回值
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}
template<class T,class V>
class CLMapBase:public LMap<T,T&,V,V&>{
public:
	CLMapBase(int nBlockSize = HASH_BIG_BLOCK_SIZE,int nHashTbSize=HASH_BIG_ARR_SIZE):LMap<T,T&,V,V&>(nBlockSize,nHashTbSize){}
	virtual ~CLMapBase(){
		ClearAll();
	}
	virtual inline V*	GetValue(T index,BOOL bForceNew=FALSE){
		V* pret;
		if(Lookup(index,pret,bForceNew)){
			return pret;
		}else{
			ASSERT(!bForceNew);
			return NULL;
		}
	}
	virtual inline V* NewValue(T index){
		return GetValue(index,TRUE);
	}
	inline void DeleteValue(T index){
		RemoveKey(index);
	}
	inline void SetValue(T index,V* pVal){
		SetAt(index,*pVal);
	}
	inline void ClearAll(){
		RemoveAll();
	}
};
template<class T,class V>
class CLMapBaseExt:public CLMapBase<T,V>{
public:
	CLMapBaseExt(int nBlockSize = HASH_BIG_BLOCK_SIZE,int nHashTbSize=HASH_BIG_ARR_SIZE):CLMapBase<T,V>(nBlockSize,nHashTbSize){}
	inline V* GetDefaultValue(){
		return &m_defaultV;
	}
	virtual inline V*	GetValue(T index,BOOL bForceNew=FALSE){
		V* pret;
		if(Lookup(index,pret,bForceNew)){
			return pret;
		}else{
			//如果不在集合中,返回默认值
			ASSERT(!bForceNew);
			return &m_defaultV;
		}
	}
protected:
	V m_defaultV;
};
#endif // !defined(AFX_LMAP_H__36851820_2895_4B94_9110_285063B671CE__INCLUDED_)
