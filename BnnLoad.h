#if !defined(AFX_BNNLOAD_H__F28984B2_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
#define AFX_BNNLOAD_H__F28984B2_423B_11D5_8BEB_C0AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BnnLoad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBnnLoad dialog

class CBnnLoad : public CDialog
{
// Construction
public:
	CBnnLoad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBnnLoad)
	enum { IDD = IDD_LOAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBnnLoad)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNNLOAD_H__F28984B2_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
