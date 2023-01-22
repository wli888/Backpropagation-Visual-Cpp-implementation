// MDICoinView.h : interface of the CMDICoinView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDICOINVIEW_H__784465AE_3BB7_11D5_8BEB_70B456C10000__INCLUDED_)
#define AFX_MDICOINVIEW_H__784465AE_3BB7_11D5_8BEB_70B456C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMDICoinView : public CView
{
protected: // create from serialization only
	CMDICoinView();
	DECLARE_DYNCREATE(CMDICoinView)

// Attributes
public:
	CMDICoinDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDICoinView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDICoinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDICoinView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MDICoinView.cpp
inline CMDICoinDoc* CMDICoinView::GetDocument()
   { return (CMDICoinDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICOINVIEW_H__784465AE_3BB7_11D5_8BEB_70B456C10000__INCLUDED_)
