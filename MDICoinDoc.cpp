// MDICoinDoc.cpp : implementation of the CMDICoinDoc class
//

#include "stdafx.h"
#include "MDICoin.h"

#include "MDICoinDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDICoinDoc

IMPLEMENT_DYNCREATE(CMDICoinDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDICoinDoc, CDocument)
	//{{AFX_MSG_MAP(CMDICoinDoc)
	ON_COMMAND(ID_EDIT_ADD_COIN, OnEditAddCoin)
	ON_COMMAND(ID_EDIT_REMOVE_COIN, OnEditRemoveCoin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDICoinDoc construction/destruction

CMDICoinDoc::CMDICoinDoc()
{
	// TODO: 
	m_nCoins=1;

}

CMDICoinDoc::~CMDICoinDoc()
{
}

BOOL CMDICoinDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDICoinDoc serialization

void CMDICoinDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMDICoinDoc diagnostics

#ifdef _DEBUG
void CMDICoinDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDICoinDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDICoinDoc commands

int CMDICoinDoc::GetCoinCount()
{
	return m_nCoins;
}

void CMDICoinDoc::OnEditAddCoin() 
{
	// TODO: 
	m_nCoins++;
	//update view to redraw coin stack
	UpdateAllViews(NULL);
}

void CMDICoinDoc::OnEditRemoveCoin() 
{
	// TODO: 
	if (m_nCoins>0)
		m_nCoins--;
	UpdateAllViews(NULL);
}
