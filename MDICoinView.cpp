// MDICoinView.cpp : implementation of the CMDICoinView class
//

#include "stdafx.h"
#include "MDICoin.h"

#include "MDICoinDoc.h"
#include "MDICoinView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView


IMPLEMENT_DYNCREATE(CMDICoinView, CView)

BEGIN_MESSAGE_MAP(CMDICoinView, CView)
	//{{AFX_MSG_MAP(CMDICoinView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView construction/destruction

CMDICoinView::CMDICoinView()
{
	// TODO: add construction code here

}

CMDICoinView::~CMDICoinView()
{
}

BOOL CMDICoinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView drawing

void CMDICoinView::OnDraw(CDC* pDC)
{
	CMDICoinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 
	//save the current brush
	CBrush*	pOldBrush=pDC->GetCurrentBrush();
	//create a solid yellow brush
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,0));

	//select the yellow brush in to the device context
	pDC->SelectObject(&br);
	for(int nCount =0;nCount<pDoc->GetCoinCount(); nCount++)
	{
		int y=100 - 10*nCount;
		pDC->Ellipse(40,y,100,y-30);
		pDC->Ellipse(40,y-10,100,y-35);
	}
	pDC->SelectObject(pOldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView printing

BOOL CMDICoinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDICoinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDICoinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView diagnostics

#ifdef _DEBUG
void CMDICoinView::AssertValid() const
{
	CView::AssertValid();
}

void CMDICoinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDICoinDoc* CMDICoinView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDICoinDoc)));
	return (CMDICoinDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDICoinView message handlers
