#if !defined(AFX_BNN_TEST_H__0EB3EB63_4265_11D5_8BEB_C0AB56C10000__INCLUDED_)
#define AFX_BNN_TEST_H__0EB3EB63_4265_11D5_8BEB_C0AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// bnn_test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// bnn_test dialog

class bnn_test : public CDialog
{
// Construction
public:
	void DisplayTestPatterns();
	BOOL LoadTestSet();
	bnn_test(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(bnn_test)
	enum { IDD = IDD_BNN_TEST_DIALOG };
	CListBox	m_lb_test_pat_num;
	CListBox	m_lb_test_pat_in;
	CListBox	m_lb_net_out;
	int		m_no_test_pat;
	CString	m_test_pat_filename;
	int		m_test_pat_no_inval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(bnn_test)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(bnn_test)
	afx_msg void OnButtonTestPatLoad();
	afx_msg void OnSelchangeListTestPatNum();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNN_TEST_H__0EB3EB63_4265_11D5_8BEB_C0AB56C10000__INCLUDED_)
