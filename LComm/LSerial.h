// LSerial.h: interface for the CLSerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSERIAL_H__6931BB57_B643_4776_BE39_155C968C2C02__INCLUDED_)
#define AFX_LSERIAL_H__6931BB57_B643_4776_BE39_155C968C2C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <stdio.h>

class CLSerial  
{
public:
	_inline LONG GetValue()
	{
		if(m_fp && !feof(m_fp)){
			LONG ret=0;
			fpos_t pos;
			if(fgetpos(m_fp,&pos))
				ASSERT(FALSE);
			operator>>(ret);
			if(fsetpos(m_fp,&pos))
				ASSERT(FALSE);
			return ret;
		}else
			return 0;
	};
	_inline BOOL isLoading(){return m_bIsLoading;};
	CLSerial(LPTSTR strFile,BOOL bRead){
		
		m_bIsLoading=bRead;
		if(!bRead){
			m_fp=fopen(strFile,"wb+");
			if(!m_fp)
				ASSERT(FALSE);
		}else{
			m_fp=fopen(strFile,"rb");
			if(!m_fp)
				ASSERT(FALSE);
		}
		
	};
	virtual ~CLSerial(){
		if(m_fp)
			fclose(m_fp);
	};
	
	_inline CLSerial& operator >> (INT& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(INT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (WORD& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(WORD),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (DWORD& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(DWORD),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (char& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(char),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (LONG& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(LONG),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (FLOAT& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(FLOAT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (double& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(double),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (__int64& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(__int64),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (RECT& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(RECT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (POINT& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(POINT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (SIZE& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(SIZE),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (BYTE& iVal){
		if(m_fp && !feof(m_fp)){
			fread((char*)&iVal,sizeof(BYTE),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator >> (LPTSTR iVal){
		if(m_fp && !feof(m_fp)){
			LONG nLen=0;
			operator>>(nLen);
			if(nLen>0){
				fread((char*)iVal,sizeof(char),nLen,m_fp);
				if(ferror(m_fp))
					ASSERT(FALSE);
			}
			iVal[nLen]='\0';
		}
		return *this;
	}

	_inline CLSerial& operator << (INT& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(INT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (char& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(char),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (WORD& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(WORD),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (DWORD& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(DWORD),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (LONG& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(LONG),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (FLOAT& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(FLOAT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (double& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(double),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (__int64& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(__int64),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (BYTE& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(BYTE),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (RECT& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(RECT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (POINT& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(POINT),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (SIZE& iVal){
		if(m_fp){
			fwrite((char*)&iVal,sizeof(SIZE),1,m_fp);
			if(ferror(m_fp))
				ASSERT(FALSE);
		}
		return *this;
	}
	_inline CLSerial& operator << (LPTSTR iVal){
		if(m_fp){
			LONG nLen=0;
			if(iVal)
				nLen=strlen(iVal);
			operator<<(nLen);
			if(nLen>0){
				fwrite((char*)iVal,sizeof(char),nLen,m_fp);
				if(ferror(m_fp))
					ASSERT(FALSE);
			}
		}
		return *this;
	}

private:
	BOOL	m_bIsLoading;
	FILE*	m_fp;
};

#endif // !defined(AFX_LSERIAL_H__6931BB57_B643_4776_BE39_155C968C2C02__INCLUDED_)
