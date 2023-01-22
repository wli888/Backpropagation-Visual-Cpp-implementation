#if !defined(AFX_BNNTRAINPAR_H__76E28D20_0846_11D6_8BEB_F0A756C10000__INCLUDED_)
#define AFX_BNNTRAINPAR_H__76E28D20_0846_11D6_8BEB_F0A756C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BnnTrainPar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPar dialog

#define DISPLAY_TEXTUAL 0
#define DISPLAY_GRAPHICAL 1
#define LEARNINGRATE_STATIC 0
#define LEARNINGRATE_BOLDDRIVER 1
#define LEARNINGRATE_FUZZYLOGIC 2
#define MOMENTUM_STATIC 0
#define MOMENTUM_FUZZYLOGIC 1
#define MOMENTUM_NONE 2


class CBnnTrainPar : public CDialog
{
// Construction
public:
	CBnnTrainPar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBnnTrainPar)
	enum { IDD = IDD_DIALOG_TRAIN_PAR };
	CComboBox	m_cbMomentum;
	CComboBox	m_cbLearningRate;
	CComboBox	m_cbDisplay;
	CString	m_trainingParFilename;
	long	m_noEpoches;
	long	m_refresh;
	FP	m_learningRate;
	FP	m_momentum;
	FP	m_desError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnTrainPar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBnnTrainPar)
	afx_msg void OnTrainPar1Ok();
	afx_msg void OnTrainPar1Cancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNNTRAINPAR_H__76E28D20_0846_11D6_8BEB_F0A756C10000__INCLUDED_)
