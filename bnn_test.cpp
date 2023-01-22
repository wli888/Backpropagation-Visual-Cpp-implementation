// bnn_test.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "bnn_test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBnnApp theApp;

/////////////////////////////////////////////////////////////////////////////
// bnn_test dialog


bnn_test::bnn_test(CWnd* pParent /*=NULL*/)
	: CDialog(bnn_test::IDD, pParent)
{
	//{{AFX_DATA_INIT(bnn_test)
	m_no_test_pat = 0;
	m_test_pat_filename = _T("C:\\My Documents\\WL\\bnndata\\pattestnn.txt");
	m_test_pat_no_inval = 0;
	//}}AFX_DATA_INIT
}


void bnn_test::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(bnn_test)
	DDX_Control(pDX, IDC_LIST_TEST_PAT_NUM, m_lb_test_pat_num);
	DDX_Control(pDX, IDC_LIST_TEST_PAT_IN, m_lb_test_pat_in);
	DDX_Control(pDX, IDC_LIST_NET_OUT, m_lb_net_out);
	DDX_Text(pDX, IDC_EDIT_NO_TEST_PAT, m_no_test_pat);
	DDX_Text(pDX, IDC_EDIT_TEST_PAT_FILENAME, m_test_pat_filename);
	DDX_Text(pDX, IDC_EDIT_TEST_PAT_NO_INVAL, m_test_pat_no_inval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(bnn_test, CDialog)
	//{{AFX_MSG_MAP(bnn_test)
	ON_BN_CLICKED(IDC_BUTTON_TEST_PAT_LOAD, OnButtonTestPatLoad)
	ON_LBN_SELCHANGE(IDC_LIST_TEST_PAT_NUM, OnSelchangeListTestPatNum)
	ON_BN_CLICKED(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// bnn_test message handlers

void bnn_test::OnButtonTestPatLoad() 
{
	// TODO
	CFileDialog FD(TRUE,NULL,NULL,NULL,NULL);

	UpdateData(TRUE);  // TRUE: screen -> membervar
	if (m_test_pat_filename.IsEmpty())
	{
		FD.DoModal();
		m_test_pat_filename = FD.GetPathName();
		UpdateData(FALSE); // FALSE: membervar -> screen
	}

	theApp.m_ptestpatternset = new TestPatternSet; 
	theApp.m_ptestpatternset->load(m_test_pat_filename);
	DisplayTestPatterns();
}


void bnn_test::DisplayTestPatterns()
{
	TestPatternSet *test_patternset;
	int i;
	char buf[10];

	test_patternset = theApp.m_ptestpatternset;
	m_no_test_pat = test_patternset->no_patterns;
	m_test_pat_no_inval = test_patternset->no_inval;
	m_lb_test_pat_num.ResetContent();
	for (i=0; i<m_no_test_pat; i++)
	{
		sprintf(buf, "%d", i+1);
		m_lb_test_pat_num.AddString(buf);
	}
	UpdateData(FALSE);
}

void bnn_test::OnSelchangeListTestPatNum() 
{
	// TODO
	int lbindex, i;
	char buf[10];
	TestPattern *test_pattern;
	TestPatternSet *test_patternset;
	FP *input_val, *output_val;

	lbindex = m_lb_test_pat_num.GetCurSel();
	test_patternset = theApp.m_ptestpatternset;
	test_pattern = test_patternset->ppatterns;
	for (i=0; i<lbindex; i++)
	{
		test_pattern++;
	}
	m_lb_test_pat_in.ResetContent();
	input_val = test_pattern->pinput;
	for (i=0; i<test_patternset->no_inval; i++)
	{
		sprintf(buf, "%f", *input_val);
		m_lb_test_pat_in.AddString(buf);
		input_val++;
	}
	m_lb_net_out.ResetContent();
	output_val = test_pattern->poutput;
	if (output_val == NULL)
	{		
		m_lb_net_out.AddString("N/A");
	}
	else
	{
		for (i=0; i<test_patternset->no_outval; i++)
		{
			sprintf(buf, "%f", *output_val);
			m_lb_net_out.AddString(buf);
			output_val++;
		}
	}
}


BOOL bnn_test::LoadTestSet()
{
	UpdateData(TRUE);  // TRUE: screen -> membervar
	if (m_test_pat_filename.IsEmpty())
	{
		MessageBox("Please specify filename for test pattern set");
		return FALSE;
	}
	else
	{
		if (theApp.m_ptestpatternset == NULL)
		{
			theApp.m_ptestpatternset = new TestPatternSet; 
			theApp.m_ptestpatternset->load(m_test_pat_filename);
			DisplayTestPatterns();
		}
		return TRUE;
	}
}


void bnn_test::OnTest() 
{
	// TODO: 
	if (LoadTestSet())
	{
		theApp.m_pnn->test(theApp.m_ptestpatternset);
	}
}
