// BnnTrainPat.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "BnnTrainPat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBnnApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPat dialog


CBnnTrainPat::CBnnTrainPat(CWnd* pParent /*=NULL*/)
	: CDialog(CBnnTrainPat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBnnTrainPat)
	m_train_pat_filename = theApp.m_train_patterns_filename;
	m_train_pat_no_inval = 0;
	m_train_pat_no_outval = 0;
	m_no_train_pat = 0;
	//}}AFX_DATA_INIT
}


void CBnnTrainPat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBnnTrainPat)
	DDX_Control(pDX, IDC_LIST_TRAIN_PAT_OUT, m_lb_train_pat_out);
	DDX_Control(pDX, IDC_LIST_TRAIN_PAT_NUM, m_lb_train_pat_num);
	DDX_Control(pDX, IDC_LIST_TRAIN_PAT_IN, m_lb_train_pat_in);
	DDX_Text(pDX, IDC_EDIT_TRAIN_PAT_FILENAME, m_train_pat_filename);
	DDX_Text(pDX, IDC_EDIT_TRAIN_PAT_NO_INVAL, m_train_pat_no_inval);
	DDX_Text(pDX, IDC_EDIT_TRAIN_PAT_NO_OUTVAL, m_train_pat_no_outval);
	DDX_Text(pDX, IDC_EDIT_NO_TRAIN_PAT, m_no_train_pat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBnnTrainPat, CDialog)
	//{{AFX_MSG_MAP(CBnnTrainPat)
	ON_BN_CLICKED(IDC_BUTTON_TRAIN_PAT_LOAD, OnButtonTrainPatLoad)
	ON_LBN_SELCHANGE(IDC_LIST_TRAIN_PAT_NUM, OnSelchangeListTrainPatNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPat message handlers


void CBnnTrainPat::OnButtonTrainPatLoad() 
{
	// TODO:
	CFileDialog FD(TRUE,NULL,NULL,NULL,NULL);
//	CString strMessage;

	UpdateData(TRUE);  // TRUE: screen -> membervar
	if (m_train_pat_filename.IsEmpty())
	{
		FD.DoModal();
		m_train_pat_filename = FD.GetPathName();
		UpdateData(FALSE); // FALSE: membervar -> screen
	}

	theApp.m_ppatternset = new PatternSet; 
	theApp.m_ppatternset->load(m_train_pat_filename);
	DisplayTrainPatterns();
//	theApp.m_ppatternset->show(this);

//	strMessage = "Training Patterns loaded from file " + m_pat_filename;
//	MessageBox(strMessage);	
}

void CBnnTrainPat::DisplayTrainPatterns()
{
	PatternSet *train_patternset;
	int i;
	char buf[10];

	train_patternset = theApp.m_ppatternset;
	m_no_train_pat = train_patternset->no_patterns;
	m_train_pat_no_inval = train_patternset->no_inval;
	m_train_pat_no_outval = train_patternset->no_outval;
	m_lb_train_pat_num.ResetContent();
	for (i=0; i<m_no_train_pat; i++)
	{
		sprintf(buf, "%d", i+1);
		m_lb_train_pat_num.AddString(buf);
	}
	UpdateData(FALSE);
}

void CBnnTrainPat::OnSelchangeListTrainPatNum() 
{
	// TODO:
	int lbindex, i;
	char buf[10];
	Pattern *train_pattern;
	PatternSet *train_patternset;
	FP *input_val, *output_val;

	lbindex = m_lb_train_pat_num.GetCurSel();
	train_patternset = theApp.m_ppatternset;
	train_pattern = train_patternset->ppatterns;
	for (i=0; i<lbindex; i++)
	{
		train_pattern++;
	}
	m_lb_train_pat_in.ResetContent();
	input_val = train_pattern->pinput;
	for (i=0; i<train_patternset->no_inval; i++)
	{
		sprintf(buf, "%f", *input_val);
		m_lb_train_pat_in.AddString(buf);
		input_val++;
	}
	m_lb_train_pat_out.ResetContent();
	output_val = train_pattern->poutput;
	for (i=0; i<train_patternset->no_outval; i++)
	{
		sprintf(buf, "%f", *output_val);
		m_lb_train_pat_out.AddString(buf);
		output_val++;
	}
}

void CBnnTrainPat::OnOK() 
{
	// TODO
	UpdateData(TRUE);  // TRUE: screen -> membervar
	theApp.m_train_patterns_filename = m_train_pat_filename;
	CDialog::OnOK();
}
