#if !defined(AFX_BNNTRAINING_H__5E715566_08EF_11D6_8BEB_10A256C10000__INCLUDED_)
#define AFX_BNNTRAINING_H__5E715566_08EF_11D6_8BEB_10A256C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BnnTraining.h : header file
//

#include "fp.h"


/////////////////////////////////////////////////////////////////////////////
// CBnnTraining dialog

class CBnnTraining : public CDialog
{
// Construction
public:
	CBnnTraining(CWnd* pParent = NULL);   // standard constructor
	void display(FP arg1, long arg2, double arg3, FP arg4, FP arg5);

// Dialog Data
	//{{AFX_DATA(CBnnTraining)
	enum { IDD = IDD_TRAINING_DIALOG };
	CString	m_noEpoches;
	CString	m_desError;
	CString	m_refresh;
	CString	m_given_lr;
	CString	m_given_momentum;
	CString	m_actLearningRate;
	CString	m_actMomentum;
	CString	m_epocheNumber;
	CString	m_currentError;
	CString	m_lowestError;
	CString	m_mCUPS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnTraining)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL CBnnTraining::OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBnnTraining)
	afx_msg void OnTrainingExit();
	afx_msg void OnTrainingAbort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNNTRAINING_H__5E715566_08EF_11D6_8BEB_10A256C10000__INCLUDED_)
