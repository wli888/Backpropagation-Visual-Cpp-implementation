// bnnDlg.h : header file
//

#if !defined(AFX_BNNDLG_H__F28984A6_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
#define AFX_BNNDLG_H__F28984A6_423B_11D5_8BEB_C0AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/////////////////////////////////////////////////////////////////////////////
// CBnnDlg dialog

class CBnnDlg : public CDialog
{
// Construction
public:
	CBnnDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBnnDlg)
	enum { IDD = IDD_BNN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBnnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNnNew();
	afx_msg void OnExit();
	afx_msg void OnNnTrain();
	afx_msg void OnNnTest();
	afx_msg void OnNnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNNDLG_H__F28984A6_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
