#if !defined(AFX_BNNTRAINPAT_H__446E16A0_5367_11D5_8BEB_10B356C10000__INCLUDED_)
#define AFX_BNNTRAINPAT_H__446E16A0_5367_11D5_8BEB_10B356C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BnnTrainPat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPat dialog

class CBnnTrainPat : public CDialog
{
// Construction
public:
	void DisplayTrainPatterns();
	CBnnTrainPat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBnnTrainPat)
	enum { IDD = IDD_DIALOG_TRAIN_PAT };
	CListBox	m_lb_train_pat_out;
	CListBox	m_lb_train_pat_num;
	CListBox	m_lb_train_pat_in;
	CString	m_train_pat_filename;
	int		m_train_pat_no_inval;
	int		m_train_pat_no_outval;
	int		m_no_train_pat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnTrainPat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBnnTrainPat)
	afx_msg void OnButtonTrainPatLoad();
	afx_msg void OnSelchangeListTrainPatNum();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNNTRAINPAT_H__446E16A0_5367_11D5_8BEB_10B356C10000__INCLUDED_)
