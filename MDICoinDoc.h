// MDICoinDoc.h : interface of the CMDICoinDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDICOINDOC_H__784465AC_3BB7_11D5_8BEB_70B456C10000__INCLUDED_)
#define AFX_MDICOINDOC_H__784465AC_3BB7_11D5_8BEB_70B456C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMDICoinDoc : public CDocument
{
protected: // create from serialization only
	CMDICoinDoc();
	DECLARE_DYNCREATE(CMDICoinDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDICoinDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetCoinCount();
	virtual ~CMDICoinDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_nCoins;
	//{{AFX_MSG(CMDICoinDoc)
	afx_msg void OnEditAddCoin();
	afx_msg void OnEditRemoveCoin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICOINDOC_H__784465AC_3BB7_11D5_8BEB_70B456C10000__INCLUDED_)
