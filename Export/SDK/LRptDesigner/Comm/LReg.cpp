#include "stdafx.h"
#include "lreg.h"

/*================================================================ 
* 函数名：    CLReg
* 参数：      (HKEY hRootKey) 
* 说明：      如果构造函数不带参数，则使用默认的参数，m_hRootKey被初始化
			  为HKEY_LOCAL_MACHINE, 如果带有参数则 m_hRootKey为指定的值
================================================================*/ 
CLReg::CLReg(HKEY hRootKey) 
{
	m_hRootKey = hRootKey; 
}

CLReg::~CLReg() //在析构函数中关闭打开注册表句柄
{
	Close();
}



/*================================================================ 
* 函数名：    VerifyKey
* 参数：      (HKEY hRootKey, LPCTSTR pszPath) 
* 功能描述:   判断给定的路径是否存在 (兼有打开的功能)
			  如果第一个参数为NULL，则使用默认的根键。
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::VerifyKey (LPCTSTR pszPath)
{
 	LONG ReturnValue = ::RegOpenKeyEx (m_hRootKey, pszPath, 0L,
										KEY_ALL_ACCESS, &m_hSubKey);

	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}


/*================================================================ 
* 函数名：    VerifyValue
* 参数：      (LPCTSTR pszValue)
* 功能描述:   判断给定的值是否存在 （请先调用VerifyKey，然后在使用该函数）
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::VerifyValue (LPCTSTR pszValue)
{
	LONG lReturn = ::RegQueryValueEx(m_hSubKey, pszValue, NULL,
		NULL, NULL, NULL);

	if(lReturn == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}

/*================================================================ 
* 函数名：    VerifyValue
* 参数：      (LPCTSTR pszValue)
* 功能描述:   判断指定的键名是否等于某个值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::IsEqual(LPCTSTR pszValue,int nn)
{
	int nTemp;
	this->GetValue(pszValue,nTemp);
	if(nTemp==nn)
		return TRUE;
	return FALSE;
}
BOOL CLReg::IsEqual(LPCTSTR pszValue,DWORD dw)
{
	DWORD dwTemp;
	this->GetValue(pszValue,dwTemp);
	if(dwTemp==dw)
		return TRUE;
	return FALSE;
}
BOOL CLReg::IsEqual(LPCTSTR pszValue,LPCTSTR lpsz)
{
	CString str;
	this->GetValue(pszValue,str);
	if(str.CompareNoCase(lpsz)==0)
		return TRUE;
	return FALSE;
}


/*================================================================ 
* 函数名：    CreateKey
* 参数：      (HKEY hRootKey, LPCTSTR pszPath)
* 功能描述:   创建路径
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::CreateKey (LPCTSTR pszPath)
{
	DWORD dw;

	LONG ReturnValue = ::RegCreateKeyEx (m_hRootKey, pszPath, 0L, NULL,
							REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, 
							&m_hSubKey, &dw);

	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}



/*================================================================ 
* 函数名：    SetValue
* 参数：      (LPCTSTR lpszKeyName, int iVal)
* 功能描述:   写入整型值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::SetValue (LPCTSTR lpszKeyName, int iVal)
{
	DWORD dwValue;

	dwValue = (DWORD)iVal;
	LONG ReturnValue = ::RegSetValueEx(m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST unsigned char*) &dwValue, sizeof(DWORD));


	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}

/*================================================================ 
* 函数名：    SetValue
* 参数：      (LPCTSTR lpszKeyName, DWORD dwVal)
* 功能描述:   写入DWORD值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::SetValue (LPCTSTR lpszKeyName, DWORD dwVal)
{
	return ::RegSetValueEx (m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST unsigned char*) &dwVal, sizeof(DWORD));
}


/*================================================================ 
* 函数名：    SetValue
* 参数：      (LPCTSTR lpszKeyName, LPCTSTR pszData)
* 功能描述:   写入字符串值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::SetValue (LPCTSTR lpszKeyName, LPCTSTR pszData)
{

	LONG ReturnValue = ::RegSetValueEx (m_hSubKey, lpszKeyName, 0L, REG_SZ,
		(CONST unsigned char*) pszData, strlen(pszData) + 1);


	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}


/*================================================================ 
* 函数名：    GetValue
* 参数：      (LPCTSTR lpszKeyName, int& iVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取整数
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::GetValue(LPCTSTR lpszKeyName, int& iVal)
{

	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = ::RegQueryValueEx (m_hSubKey, (LPSTR) lpszKeyName, NULL,
		&dwType, (unsigned char *) &dwDest, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		iVal = (int)dwDest;
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* 函数名：    GetValue
* 参数：      (LPCTSTR lpszKeyName, DWORD& dwVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取DWORD值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::GetValue (LPCTSTR lpszKeyName, DWORD& dwVal)
{

	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = ::RegQueryValueEx (m_hSubKey, (LPSTR) lpszKeyName, NULL, 
		&dwType, (unsigned char *) &dwDest, &dwSize);


	if(lReturn == ERROR_SUCCESS)
	{
		dwVal = dwDest;
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* 函数名：    GetValue
* 参数：      (LPCTSTR lpszKeyName, CString& sVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取字符串值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::GetValue (LPCTSTR lpszKeyName, CString& sVal)
{

	DWORD dwType;
	DWORD dwSize = 200;
	char  szString[255];

	LONG lReturn = ::RegQueryValueEx (m_hSubKey, (LPSTR) lpszKeyName, NULL,
		&dwType, (unsigned char *) szString, &dwSize);


	if(lReturn == ERROR_SUCCESS)
	{
		sVal = szString;
		return TRUE;
	}

	return FALSE;
}



/*================================================================ 
* 函数名：    DeleteValue
* 参数：      (LPCTSTR pszValue) 
* 功能描述:   删除值
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::DeleteValue (LPCTSTR pszValue)
{
	if(::RegDeleteValue(m_hSubKey, pszValue)== ERROR_SUCCESS)		
		return TRUE;
	else
		return FALSE;
}

/*================================================================ 
* 函数名：    DeleteKey
* 参数：      (HKEY hRootKey, LPCTSTR pszPath) 
* 功能描述:   删除路径
* 返回值：    BOOL
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
BOOL CLReg::DeleteKey (LPCTSTR pszPath)
{

	if(::RegDeleteKey(m_hRootKey, pszPath) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}


/*================================================================ 
* 函数名：    Close
* 参数：      
* 功能描述:   关闭注册表
* 返回值：    void
* 作 者：     罗智勇 2005-09-12
================================================================*/ 
 void CLReg::Close()
{
	if (m_hSubKey)
	{
		::RegCloseKey (m_hSubKey);
		m_hSubKey = NULL;
	}
}


void CLReg::SetRootKey(HKEY root)
{
	m_hRootKey=root;
}
