#if !defined _LREG_H
#define _LREG_H

class CLReg : public CObject
{
public:
	CLReg(HKEY hRootKey = HKEY_LOCAL_MACHINE); //构造函数带有默认参数
	virtual ~CLReg();

public:
	void SetRootKey(HKEY root);
	BOOL VerifyKey (LPCTSTR pszPath); 
	BOOL VerifyValue (LPCTSTR pszValue);

	BOOL CreateKey (LPCTSTR pszPath);
	void Close();

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteKey (LPCTSTR pszPath);

	BOOL SetValue (LPCTSTR pszKey, int iVal);
	BOOL SetValue (LPCTSTR pszKey, DWORD dwVal);
	BOOL SetValue (LPCTSTR pszKey, LPCTSTR pszVal);

	BOOL GetValue (LPCTSTR pszKey, int& iVal);
	BOOL GetValue (LPCTSTR pszKey, DWORD& dwVal);
	BOOL GetValue (LPCTSTR pszKey, CString& sVal);

	BOOL IsEqual(LPCTSTR pszValue,int nn);
	BOOL IsEqual(LPCTSTR pszValue,DWORD dw);
	BOOL IsEqual(LPCTSTR pszValue,LPCTSTR lpsz);

protected:	
	HKEY 	m_hSubKey;    //保存打开的子键句柄
	HKEY    m_hRootKey;   //保存根键句柄
};

#endif
