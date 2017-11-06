// LRptDesignerDoc.h : interface of the CLRptDesignerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LRPTDESIGNERDOC_H__E6E0C5E6_8406_4434_9E4D_16EF2CE10C11__INCLUDED_)
#define AFX_LRPTDESIGNERDOC_H__E6E0C5E6_8406_4434_9E4D_16EF2CE10C11__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLRptDesignerDoc : public CDocument
{
protected: // create from serialization only
	CLRptDesignerDoc();
	DECLARE_DYNCREATE(CLRptDesignerDoc)

// Attributes
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLRptDesignerDoc)
	public:
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	BOOL bInitOK;
	virtual ~CLRptDesignerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLRptDesignerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//ICLBookLib m_RptGrid;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LRPTDESIGNERDOC_H__E6E0C5E6_8406_4434_9E4D_16EF2CE10C11__INCLUDED_)
