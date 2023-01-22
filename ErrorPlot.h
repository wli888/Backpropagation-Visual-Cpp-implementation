#if !defined(AFX_ERRORPLOT_H__EBCE7480_B03C_11D5_8BEB_40AB56C10000__INCLUDED_)
#define AFX_ERRORPLOT_H__EBCE7480_B03C_11D5_8BEB_40AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorPlot.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// ErrorPlot dialog

class ErrorPlot : public CDialog
{
// Construction
public:
	ErrorPlot(CWnd* pParent = NULL);   // standard constructor
	void AddToList(FP error);
	void SetMaxError(FP max_error);
	FP GetMaxError();
	void SetMaxErrorChanged(bool bool_val);
	bool GetMaxErrorChanged();
	void Drawit();
	void SetPaintDC(ErrorPlot *ep);
	void Reset();
	void draw();
	bool finished;

//	void SetNonSummaryArea(int nonSummaryArea);
//	void SetBottomMargin(int bottomMargin);

// Dialog Data
	//{{AFX_DATA(ErrorPlot)
	enum { IDD = IDD_ERROR_PLOT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ErrorPlot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	CPaintDC* paintDC;
	CList<FP,FP> ErrorList;
	FP maxError;
	bool maxErrorChanged;
	bool xStepChanged;
	int currentXStep;
	int nonSummaryArea;
	int bottomMargin;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(ErrorPlot)
	afx_msg void OnPaint();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnDrawit();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORPLOT_H__EBCE7480_B03C_11D5_8BEB_40AB56C10000__INCLUDED_)
