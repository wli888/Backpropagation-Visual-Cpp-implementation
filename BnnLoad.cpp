// BnnLoad.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "BnnLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBnnLoad dialog


CBnnLoad::CBnnLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CBnnLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBnnLoad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBnnLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBnnLoad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBnnLoad, CDialog)
	//{{AFX_MSG_MAP(CBnnLoad)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnLoad message handlers
