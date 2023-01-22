// TRAIN.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "TRAIN.h"
#include "BnnTrainPar.h"
#include "BnnTrainPat.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBnnApp theApp;


/////////////////////////////////////////////////////////////////////////////
// TRAIN dialog


TRAIN::TRAIN(CWnd* pParent /*=NULL*/)
	: CDialog(TRAIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(TRAIN)
	m_par_filename = _T("");
	m_pat_filename = theApp.m_train_patterns_filename;
	//}}AFX_DATA_INIT
}


void TRAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TRAIN)
	DDX_Text(pDX, IDC_EDIT_TNN_PAR_FILENAME, m_par_filename);
	DDX_Text(pDX, IDC_EDIT_TNN_PAT_FILENAME, m_pat_filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TRAIN, CDialog)
	//{{AFX_MSG_MAP(TRAIN)
	ON_BN_CLICKED(ID_TRAIN, OnTrain)
	ON_BN_CLICKED(IDC_BUTTON_TNN_TRAIN_PAT, OnButtonTnnTrainPat)
	ON_BN_CLICKED(IDC_BUTTON_TNN_PAR_SCREEN, OnButtonTnnParScreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TRAIN message handlers


void TRAIN::OnTrain() 
{
	// TODO: 

	if (LoadTrainSet())
	{
		CBnnTraining trainingDialog;

		trainingDialog.DoModal();
	}
}


void TRAIN::OnButtonTnnTrainPat() 
{
	// TODO:
	CBnnTrainPat TrainPatDialog;

	TrainPatDialog.DoModal();
	m_pat_filename = theApp.m_train_patterns_filename;
	UpdateData(FALSE);
}

BOOL TRAIN::LoadTrainSet()
{
	UpdateData(TRUE);  // TRUE: screen -> membervar
	if (m_pat_filename.IsEmpty())
	{
		MessageBox("Please specify filename for training pattern set");
		return FALSE;
	}
	else
	{
		if (theApp.m_ppatternset == NULL)
		{
			theApp.m_ppatternset = new PatternSet; 
			theApp.m_ppatternset->load(m_pat_filename);
		}
		return TRUE;
	}
}

void TRAIN::OnButtonTnnParScreen() 
{
	CBnnTrainPar TrainParDialog;

	TrainParDialog.DoModal();
//	m_par_filename = theApp.m_train_parameters_filename;
	UpdateData(FALSE);	
}
