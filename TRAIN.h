#if !defined(AFX_TRAIN_H__0EB3EB62_4265_11D5_8BEB_C0AB56C10000__INCLUDED_)
#define AFX_TRAIN_H__0EB3EB62_4265_11D5_8BEB_C0AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TRAIN.h : header file
//

#include "fp.h"


/////////////////////////////////////////////////////////////////////////////
// TRAIN dialog

class TRAIN : public CDialog
{
// Construction
public:
	BOOL LoadTrainSet();
	TRAIN(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(TRAIN)
	enum { IDD = IDD_TRAIN_DIALOG };
	CString	m_par_filename;
	CString	m_pat_filename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TRAIN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TRAIN)
	afx_msg void OnTrain();
	afx_msg void OnButtonTnnTrainPat();
	afx_msg void OnButtonTnnParScreen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAIN_H__0EB3EB62_4265_11D5_8BEB_C0AB56C10000__INCLUDED_)
