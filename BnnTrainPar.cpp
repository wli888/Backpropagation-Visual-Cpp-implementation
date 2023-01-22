// BnnTrainPar.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "BnnTrainPar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBnnApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPar dialog


CBnnTrainPar::CBnnTrainPar(CWnd* pParent /*=NULL*/)
	: CDialog(CBnnTrainPar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBnnTrainPar)
	m_trainingParFilename = _T("");
	m_noEpoches = 0;
	m_desError = 0.0001;
	m_refresh = 1000;
	m_learningRate = 0.1;
	m_momentum = 0.9;
	//}}AFX_DATA_INIT
}


void CBnnTrainPar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBnnTrainPar)
	DDX_Control(pDX, IDC_COMBO_MOMENTUM, m_cbMomentum);
	DDX_Control(pDX, IDC_COMBO_LR, m_cbLearningRate);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_cbDisplay);
	DDX_Text(pDX, IDC_EDIT_TRAIN_PAR_FILENAME, m_trainingParFilename);
	DDX_Text(pDX, IDC_EDIT_TNN_NO_EPOCHES, m_noEpoches);
	DDX_Text(pDX, IDC_EDIT_DISPLAY, m_refresh);
	DDX_Text(pDX, IDC_EDIT_LR, m_learningRate);
	DDX_Text(pDX, IDC_EDIT_MOMENTUM, m_momentum);
	DDX_Text(pDX, IDC_EDIT_TNN_DES_ERROR, m_desError);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBnnTrainPar, CDialog)
	//{{AFX_MSG_MAP(CBnnTrainPar)
	ON_BN_CLICKED(ID_TRAIN_PAR1_OK, OnTrainPar1Ok)
	ON_BN_CLICKED(ID_TRAIN_PAR1_CANCEL, OnTrainPar1Cancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnTrainPar message handlers


BOOL CBnnTrainPar::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbDisplay.AddString("Textual");
	m_cbDisplay.AddString("Graphical");
	m_cbDisplay.SetCurSel(DISPLAY_TEXTUAL);

	m_cbLearningRate.AddString("Static");
	m_cbLearningRate.AddString("Bold driver");
	m_cbLearningRate.AddString("Fuzzy logic");
	m_cbLearningRate.SetCurSel(LEARNINGRATE_STATIC);

	m_cbMomentum.AddString("Static");
	m_cbMomentum.AddString("Fuzzy logic");
	m_cbMomentum.AddString("None");
	m_cbMomentum.SetCurSel(MOMENTUM_STATIC);
	return TRUE;
}


void CBnnTrainPar::OnTrainPar1Ok() 
{
	// TODO: 
	UpdateData(TRUE);  // TRUE: screen -> membervar
	if (m_trainingParFilename.IsEmpty())
	{
		theApp.m_ptrainingpar = new TrainingPar;
		theApp.m_ptrainingpar->des_error = m_desError;
		theApp.m_ptrainingpar->no_epoches = m_noEpoches;
		
		theApp.m_ptrainingpar->update_count = m_refresh;
		switch(m_cbDisplay.GetCurSel())
		{
		case DISPLAY_TEXTUAL:
			break;

		case DISPLAY_GRAPHICAL:
			break;

		default:
			break;
		}

		switch(m_cbLearningRate.GetCurSel())
		{
		case LEARNINGRATE_STATIC:
			theApp.m_ptrainingpar->learning_rate  = new LearningRate(
				new StaticLearningRate(m_learningRate));
			break;
		case LEARNINGRATE_BOLDDRIVER:
			theApp.m_ptrainingpar->learning_rate  = new LearningRate(
				new BoldDriverLearningRate(m_learningRate, 1.1, 0.5));
			break;
		case LEARNINGRATE_FUZZYLOGIC:
			theApp.m_ptrainingpar->learning_rate  = new LearningRate(
				new FuzzyLogicLearningRate(m_learningRate));
			break;
		default:
			break;
		}


		switch(m_cbMomentum.GetCurSel())
		{
		case MOMENTUM_STATIC:
			theApp.m_ptrainingpar->momentum  = new Momentum(
				new StaticMomentum(m_momentum));
			break;
		case MOMENTUM_FUZZYLOGIC:
			theApp.m_ptrainingpar->momentum  = new Momentum(
				new FuzzyLogicMomentum(m_momentum));
			break;
		case MOMENTUM_NONE:
			theApp.m_ptrainingpar->momentum  = new Momentum(new StaticMomentum(0));
			break;
		default:
			break;
		}
	}
	CDialog::OnOK();
}


void CBnnTrainPar::OnTrainPar1Cancel() 
{
	// TODO: 
	CDialog::OnCancel();
}
