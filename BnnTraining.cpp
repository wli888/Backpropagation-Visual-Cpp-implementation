// BnnTraining.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "BnnTraining.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBnnApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CBnnTraining dialog


CBnnTraining::CBnnTraining(CWnd* pParent /*=NULL*/)
	: CDialog(CBnnTraining::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBnnTraining)
	m_actLearningRate = _T("");
	m_actMomentum = _T("");
	m_epocheNumber = _T("");
	m_currentError = _T("");
	m_lowestError = _T("");
	m_mCUPS = _T("0.0");
	//}}AFX_DATA_INIT
}


void CBnnTraining::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBnnTraining)
	DDX_Text(pDX, IDC_STATIC_GIVEN_EPOCHE, m_noEpoches);
	DDX_Text(pDX, IDC_STATIC_GIVEN_ERROR, m_desError);
	DDX_Text(pDX, IDC_STATIC_GIVEN_REFRESH, m_refresh);
	DDX_Text(pDX, IDC_STATIC_LR, m_given_lr);
	DDX_Text(pDX, IDC_STATIC_MOMENTUM, m_given_momentum);
	DDX_Text(pDX, IDC_STATIC_TNN_ACT_LR, m_actLearningRate);
	DDX_Text(pDX, IDC_STATIC_TNN_ACT_MOMENTUM, m_actMomentum);
	DDX_Text(pDX, IDC_STATIC_TNN_EPOCHE_N, m_epocheNumber);
	DDX_Text(pDX, IDC_STATIC_TNN_ERROR, m_currentError);
	DDX_Text(pDX, IDC_STATIC_TNN_LOWEST_ERROR, m_lowestError);
	DDX_Text(pDX, IDC_STATIC_TNN_MCUPS, m_mCUPS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBnnTraining, CDialog)
	//{{AFX_MSG_MAP(CBnnTraining)
	ON_BN_CLICKED(ID_TRAINING_EXIT, OnTrainingExit)
	ON_BN_CLICKED(ID_TRAINING_ABORT, OnTrainingAbort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnTraining message handlers


BOOL CBnnTraining::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_noEpoches.Format("%ld", theApp.m_ptrainingpar->no_epoches);
	m_desError.Format("%g", theApp.m_ptrainingpar->des_error);
	m_refresh.Format("%ld", theApp.m_ptrainingpar->update_count);
	m_given_lr.Format("%g", theApp.m_ptrainingpar->learning_rate->GetLearningRate());
	m_given_momentum.Format("%g", theApp.m_ptrainingpar->momentum->GetMomentum());

	return TRUE;
}


void CBnnTraining::display(FP arg1, long arg2, double arg3, FP arg4, FP arg5)
{

	m_currentError.Format("%g", arg1);
	m_epocheNumber.Format("%ld", arg2);
	m_mCUPS.Format("%g", arg3);
	m_actLearningRate.Format("%g", arg4);
	m_actMomentum.Format("%g", arg5);
	UpdateData(FALSE);

	;
/*	FP temp;
	char buf[20];

	temp = theApp.m_pnn->GetTotalError() - theApp.m_pnn->GetPrevTotalError();
	sprintf(buf, "%g", temp);
MessageBox(buf, m_act_momentum);*/
/*	NN *m_pnn=theApp.m_pnn;
	if ((m_pnn->GetTotalError() <= m_pnn->GetPrevTotalError()) ||
		(m_pnn->GetPrevTotalError() == 0.0f))
	{
		MessageBox("Plus");
	}
	else
	{
		MessageBox("Min");
	}*/
}


void CBnnTraining::OnTrainingExit() 
{
	// TODO:
	CDialog::OnOK();
}

void CBnnTraining::OnTrainingAbort() 
{
	// TODO: 	
	theApp.m_pnn->train(theApp.m_ppatternset, theApp.m_ptrainingpar, this);
//		AfxBeginThread(MyThreadProc,NULL);

}
