// bnn.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <math.h>
#include "bnn.h"
#include "bnnDlg.h"
#include "TRAIN.h"
#include "errorplot.h"
#include "MDICoinDoc.h"
#include "MDICoinView.h"
#include "typeinfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBnnApp

BEGIN_MESSAGE_MAP(CBnnApp, CWinApp)
	//{{AFX_MSG_MAP(CBnnApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CBnnApp construction

CBnnApp::CBnnApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pnn = NULL;
	m_ppatternset = NULL;
	m_ptestpatternset = NULL;
	m_ptrainingpar = NULL;
	m_train_patterns_filename = _T("C:\\My Documents\\WL\\bnndata\\pattrainnn.txt");
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBnnApp object

CBnnApp theApp;
ErrorPlot ErrorPlotDialog;
//ofstream oFile;


/////////////////////////////////////////////////////////////////////////////
// CBnnApp initialization

BOOL CBnnApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CBnnDlg dlg;
	m_pMainWnd = &dlg;

	ErrorPlotDialog.Create(IDD_ERROR_PLOT_DIALOG, NULL);
/*	ErrorPlotDialog.ShowWindow(SW_SHOW);
	CPaintDC pDC(&ErrorPlotDialog);
	ErrorPlotDialog.SetPaintDC(&pDC);*/

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


//--------------------------------------------------------------------

TrainingPar::TrainingPar()
{
	learning_rate = NULL;
	momentum = NULL;
	des_error = 0.0;
	no_epoches = 0;
	update_count = 0;
}


TrainingPar::~TrainingPar()
{
	;
}


TrainingPar::load(CString filename)
{
	ifstream iFile;
	FP learningRate, momentum_help;

	iFile.open(filename);
	iFile >> learningRate >> momentum_help >> des_error >> no_epoches >> update_count;
	iFile.close();
	learning_rate->SetLearningRate(learningRate);
	momentum->SetMomentum(momentum_help);
}


TrainingPar::save(CString filename)
{
	ofstream oFile;

	oFile.open(filename);
	oFile << learning_rate->GetLearningRate() << ' ' << momentum->GetMomentum()
		<< ' ' << des_error << ' '; 
	oFile.close();
}

//--------------------------------------------------------------------

Pattern::Pattern()
{
	pinput = NULL;
	poutput = NULL;
}


void Pattern::set_pattern(int no_inval, int no_outval, FP *pinval, FP *poutval)
{
	int i;
	FP *pinput_help, *poutput_help;

	pinput = new FP[no_inval];
	poutput = new FP[no_outval];
	pinput_help = pinput;
	poutput_help = poutput;
	for (i=0; i<no_inval; i++)
	{
		*pinput_help = *pinval;
		pinput_help++;
		pinval++;
	}
	for (i=0; i<no_outval; i++)
	{
		*poutput_help = *poutval;
		poutput_help++;
		poutval++;
	}
}


void Pattern::load(int no_inval, int no_outval, ifstream& iFile)
{
	int i;
	FP *pinput_help, *poutput_help;
	
	pinput = new FP[no_inval];
	poutput = new FP[no_outval];
	pinput_help = pinput;
	poutput_help = poutput;

    for (i=0; i<no_inval; i++)
	{
		iFile >> *pinput_help;		
		pinput_help++;
	}
	for (i=0; i<no_outval; i++)
	{
		iFile >> *poutput_help;
		poutput_help++;
	}
}


void Pattern::save(int no_inval, int no_outval, ofstream& oFile)
{
	int i;
	FP *pinput_help, *poutput_help;

    pinput_help = pinput;
    poutput_help = poutput;
    for (i=0; i<no_inval; i++)
    {
        oFile << *pinput_help;
        pinput_help++;
    }
    for (i=0; i<no_outval; i++)
    {
        oFile << *poutput_help;
        poutput_help++;
    }
}

void Pattern::show(int no_inval, int no_outval, TRAIN *dlg)
{
	int i;
	FP *pinput_help, *poutput_help;
	char buf[40];

	pinput_help = pinput;
	poutput_help = poutput;
	for (i=0; i<no_inval; i++)
	{
		sprintf(buf,"input %d = %f",i,*pinput_help);
		dlg->MessageBox(buf);
		pinput_help++;
	}
	for (i=0; i<no_outval; i++)
	{
		sprintf(buf,"output %d = %f",i,*poutput_help);
		dlg->MessageBox(buf);
		poutput_help++;
	}
}


Pattern::~Pattern()
{
	delete [] pinput;
	delete [] poutput;
}

//--------------------------------------------------------------------

PatternSet::PatternSet()
{
	no_patterns = 0;
	no_inval = 0;
	no_outval = 0;
	ppatterns = NULL;
}


PatternSet::~PatternSet()
{
	delete [] ppatterns;
}


void PatternSet::set_patternset(int number_of_patterns, int no_in_val, int no_out_val, 
							Pattern *p2patterns)
{
	Pattern *ppatterns_help;

	no_patterns = number_of_patterns;
	no_inval = no_in_val;
	no_outval = no_out_val;
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns; i++)
	{
		ppatterns_help = p2patterns;
		ppatterns_help++;
		p2patterns++;
	}
}


void PatternSet::load(CString filename)
{
	Pattern *ppatterns_help;
	ifstream iFile;	

	iFile.open(filename);
	iFile >> no_patterns >> no_inval >> no_outval;
	ppatterns = new Pattern[no_patterns];
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns;i++)
	{
		ppatterns_help->load(no_inval, no_outval, iFile);
		ppatterns_help++;
	}
	iFile.close();
}


void PatternSet::save(CString filename)
{
	Pattern *ppatterns_help;
	ofstream oFile;	

	oFile.open(filename);
	oFile << no_patterns << ' ' << no_inval << ' ' << no_outval;
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns;i++)
	{
		ppatterns_help->save(no_inval, no_outval, oFile);
		ppatterns_help++;
	}
	oFile.close();
}


void PatternSet::show(TRAIN *dlg)
{
	char buf[40];
	Pattern *ppatterns_help;

	sprintf(buf,"no_patterns = %d",no_patterns);
	dlg->MessageBox(buf);
	sprintf(buf,"no_inval = %d",no_inval);
	dlg->MessageBox(buf);
	sprintf(buf,"no_outval = %d",no_outval);
	dlg->MessageBox(buf);

	ppatterns_help = ppatterns;
	for(int i=0; i<no_patterns; i++)
	{
		ppatterns_help->show(no_inval, no_outval, dlg);
		ppatterns_help++;
	}
}

//--------------------------------------------------------------------

void TestPattern::set_pattern(int no_inval, FP *pinval)
{
	int i;
	FP *pinput_help;

	pinput = new FP[no_inval];
	pinput_help = pinput;
	for (i=0; i<no_inval; i++)
	{
		*pinput_help = *pinval;
		pinput_help++;
		pinval++;
	}
}


void TestPattern::load(int no_inval, ifstream& iFile)
{
	int i;
	FP *pinput_help;
	
	pinput = new FP[no_inval];
	pinput_help = pinput;

    for (i=0; i<no_inval; i++)
	{
		iFile >> *pinput_help;		
		pinput_help++;
	}
}


void TestPattern::save(int no_inval, ofstream& oFile)
{
	int i;
	FP *pinput_help;
	
	pinput_help = pinput;
    for (i=0; i<no_inval; i++)
	{
		oFile << *pinput_help;
		pinput_help++;
	}
}


//--------------------------------------------------------------------

void TestPatternSet::set_patternset(int number_of_patterns, int no_in_val, 
									TestPattern *p2patterns)
{
	TestPattern *ppatterns_help;

	no_patterns = number_of_patterns;
	no_inval = no_in_val;
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns; i++)
	{
		ppatterns_help = p2patterns;
		ppatterns_help++;
		p2patterns++;
	}
}


void TestPatternSet::load(CString filename)
{
	TestPattern *ppatterns_help;
	ifstream iFile;

	iFile.open(filename);
	iFile >> no_patterns >> no_inval;
	ppatterns = new TestPattern[no_patterns];
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns;i++)
	{
		ppatterns_help->load(no_inval, iFile);
		ppatterns_help++;
	}
	iFile.close();
}


void TestPatternSet::save(CString filename)
{
	TestPattern *ppatterns_help;
	ofstream oFile;

	oFile.open(filename);
	oFile << no_patterns << ' ' << no_inval; 
	ppatterns_help = ppatterns;
	for (int i=0; i<no_patterns;i++)
	{
		ppatterns_help->save(no_inval, oFile);
		ppatterns_help++;
	}
	oFile.close();
}
//--------------------------------------------------------------------

Weight::Weight()
{
	weight = (FP) abs(rand())/32768;
//cout << "\nWeight = " << weight;
	deltaWeight = 0.0;
	prevDeltaWeight = 0.0;
	learningRate = 0.1;
	momentum = 0.9;
}


Weight::~Weight()
{
	;
}


FP Weight::GetWeight()
{
	return weight;
}


FP Weight::GetDeltaWeight()
{
	return deltaWeight;
}


FP Weight::GetPrevDeltaWeight()
{
	return prevDeltaWeight;
}


void Weight::SetWeight(FP weight)
{
	this->weight = weight;
}


void Weight::SetDeltaWeight(FP deltaWeight)
{
	this->deltaWeight = deltaWeight;
}


void Weight::SetPrevDeltaWeight(FP prevDeltaWeight)
{
	this->prevDeltaWeight = prevDeltaWeight;
}


void Weight::CalcDeltaWeight(FP delta, FP output)
{
	prevDeltaWeight = deltaWeight;
//	deltaweight = (learning_rate * delta * output) + (momentum * prev_deltaweight);
	deltaWeight = (theApp.m_ptrainingpar->learning_rate->GetLearningRate() * 
					delta * output) + 
					(theApp.m_ptrainingpar->momentum->GetMomentum() * prevDeltaWeight);
}


void Weight::AdjustWeight()
{
	weight += deltaWeight;
}


//--------------------------------------------------------------------


Neuron::Neuron()
{
	output = 0.0;
	delta = 0.0;
	pInWeights = NULL;
	pPrevInWeights = NULL;
	pBias = NULL;
	pPrevBias = NULL;
}

Neuron::~Neuron()
{
	if (pInWeights != NULL)
		delete [] pInWeights;
	if (pPrevInWeights != NULL)
		delete [] pPrevInWeights;
	if (theApp.m_pnn->HasBias() == TRUE)
	{
		if (pBias != NULL)
			delete pBias;
		if (pPrevBias != NULL)
			delete pPrevBias;
	}
}


void Neuron::SetNeuron(int no_neur_prev_layer, Boolean hasBias)
{
//cout << "\nThis neuron has " << no_neur_prev_layer << " incoming weights";
	if (no_neur_prev_layer > 0)
	{
		pInWeights = new Weight[no_neur_prev_layer];
		pPrevInWeights = new Weight[no_neur_prev_layer];
	}
	if (hasBias == TRUE)
	{
		pBias = new Weight;
		pPrevBias = new Weight;
	}
}


Weight* Neuron::GetPPrevInWeights()
{
	return pPrevInWeights;
}


Weight* Neuron::GetPInWeights()
{
	return pInWeights;
}


FP Neuron::GetOutput()
{
	return output;
}


FP Neuron::GetDelta()
{
	return delta;
}


void Neuron::SetPPrevInWeights(Weight *pPrevInWeights)
{
	this->pPrevInWeights = pPrevInWeights;
}


void Neuron::SetPInWeights(Weight *pInWeights)
{
	this->pInWeights = pInWeights;
}


void Neuron::SetOutput(FP output)
{
	this->output = output;
}


void Neuron::SetDelta(FP delta)
{
	this->delta = delta;
}


void Neuron::CalcOutput(Layer *PPrevLayer)
{
	CalcActivation(CalcInput(PPrevLayer));
}


FP Neuron::CalcInput(Layer *pprev_layer)
{
	FP temp;
	int i, no_neur_prev_layer;
	Neuron *pneurons;
	Weight *pInWeightsHelp;

	temp = 0.0;
//	pInWeightsHelp = Neuron::GetPInWeights();
	no_neur_prev_layer = pprev_layer->no_neurons;
	pneurons = pprev_layer->pneurons;
	pInWeightsHelp = GetPInWeights();
	for (i=0; i<no_neur_prev_layer; i++)
	{
		temp += pneurons->GetOutput() * pInWeightsHelp->GetWeight();
		pneurons++;
		pInWeightsHelp++;
	}
	if (theApp.m_pnn->HasBias() == TRUE)
	{
		temp += pBias->GetWeight();
	}
	return temp;
//	input = temp;
//	calc_activation(input);
//	calc_activation(temp);
}


void Neuron::CalcActivation(FP inval)
{
	SetOutput((FP) (1.0/(1.0+exp((double) -inval))));
}

void Neuron::CalcDelta(Layer *pnext_layer, int weight_number)
{
	FP temp;
	int i, weight_help;
	Neuron *pneuron_help;
	Weight *pin_weights_help;

	temp = 0.0;
	pneuron_help = pnext_layer->pneurons;
	for (i=0; i<pnext_layer->no_neurons; i++)
	{
		pin_weights_help = pneuron_help->GetPInWeights();
		for (weight_help=0; weight_help<weight_number; weight_help++)
		{
			pin_weights_help++;
		}
		temp += pin_weights_help->GetWeight() * pneuron_help->GetDelta();
		pneuron_help++;
	}
	/*Neuron::*/SetDelta(temp * CalcActivationFirstDerivative());
}


void Neuron::CalcDeltaOutputLayer(FP *ppattern_output)
{
	FP diffval;

	diffval = *ppattern_output - GetOutput();
	SetDelta(diffval * CalcActivationFirstDerivative());
}


FP Neuron::CalcActivationFirstDerivative()
{
	FP output = GetOutput();
	return (output * (1.0 - output));
}


void Neuron::CalcDeltaWeights(Layer *pPrevLayer)
{
	int k;
	Neuron *pneuron_prev_layer;
	Weight *pweight_help;
	FP delta;

	pweight_help = GetPInWeights();
	pneuron_prev_layer = pPrevLayer->pneurons;
	delta = GetDelta();
	for (k=0; k<pPrevLayer->no_neurons; k++)
	{
		pweight_help->CalcDeltaWeight(delta, pneuron_prev_layer->GetOutput());
		pweight_help->AdjustWeight();
		pweight_help++;
		pneuron_prev_layer++;
	}
	if (theApp.m_pnn->HasBias() == TRUE)
	{
		pBias->CalcDeltaWeight(GetDelta(), 1.0);

	}
}


void Neuron::BackupWeights(int no_neur_prev_layer)
{
	int k;
	Weight *pweight_help, *pPrevWeightHelp;

	pweight_help = GetPInWeights();
	pPrevWeightHelp = GetPPrevInWeights();
	for (k=0; k<no_neur_prev_layer; k++)
	{
		pPrevWeightHelp->SetWeight(pweight_help->GetWeight());
		pweight_help++;
		pPrevWeightHelp++;
	}
	if (theApp.m_pnn->HasBias() == TRUE)
	{
		pPrevBias->SetWeight(pBias->GetWeight());
	}
}


void Neuron::RestoreWeights(int no_neur_prev_layer)
{
	int k;
	Weight *pweight_help, *pPrevWeightHelp;

	pweight_help = GetPInWeights();
	pPrevWeightHelp = GetPPrevInWeights();
	for (k=0; k<no_neur_prev_layer; k++)
	{
		pweight_help->SetWeight(pPrevWeightHelp->GetWeight());
		pweight_help++;
		pPrevWeightHelp++;
	}
	if (theApp.m_pnn->HasBias() == TRUE)
	{
		pBias->SetWeight(pPrevBias->GetWeight());
	}
}


//--------------------------------------------------------------------

Layer::Layer()
{
	no_neurons = 0;
	pneurons = NULL;
}


Layer::~Layer()
{
	if (pneurons != NULL)
		delete [] pneurons;
}


void Layer::setlayer(int num_of_neurons, int no_neur_prev_layer, Boolean hasBias)
{
	int i;
	Neuron *pNeuronHelp;

	no_neurons = num_of_neurons;
//cout << "\n\nnumber of neurons in layer: " << no_neurons;

	pneurons= new Neuron[num_of_neurons];
	pNeuronHelp = pneurons;
	for (i=0; i<num_of_neurons ; i++)
	{
		pNeuronHelp->SetNeuron(no_neur_prev_layer, hasBias);
		pNeuronHelp++;
	}
}

//--------------------------------------------------------------------

NN::NN(int num_of_layers, int *pnum_of_neur_per_layer, Boolean hasBias)
{
	int i, no_neur_prev_layer;
	int *pno_neur_per_layer_help;
	Layer *players_help;

	totalError = 0.0;
	prevTotalError = totalError;
	this->hasBias = hasBias; 
	no_layers = num_of_layers;
	pno_neur_per_layer = new int[no_layers];
//cout << "\nnumber of layers: " << no_layers;
	players = new Layer[no_layers];
	pno_neur_per_layer_help = pno_neur_per_layer;
	players_help = players;
	no_neur_prev_layer = 0;
	for (i=0; i< no_layers; i++)
	{
		*pno_neur_per_layer_help = *pnum_of_neur_per_layer;
//cout << "number of neurons in layer " << i+1 << ": " << *pno_neur_per_layer_help;
		players_help->setlayer(*pnum_of_neur_per_layer, no_neur_prev_layer, hasBias);
		pno_neur_per_layer_help++;
		players_help++;
		no_neur_prev_layer = *pnum_of_neur_per_layer;
		pnum_of_neur_per_layer++;
	}
	poutput_layer = --players_help;
}


NN::~NN()
{
	;
}


Boolean NN::HasBias()
{
	return hasBias;
}


void NN::Delete()
{
	delete [] pno_neur_per_layer;
	delete [] players;
}


void NN::forwardpass(Pattern *ppattern)
{
	int i,j;
	Layer *players_help, *pprev_layer;
	Neuron *pneurons_help;
	FP *ppattern_input_help;

	players_help = players;
	pneurons_help = players_help->pneurons;
	ppattern_input_help = ppattern->pinput;
	for (j=1; j<=players_help->no_neurons; j++)
	{
		pneurons_help->SetOutput(*ppattern_input_help);
		pneurons_help++;
		ppattern_input_help++;
	}
	pprev_layer = players_help;
	for (i=2; i<=no_layers; i++)
	{
		players_help++;
		pneurons_help = players_help->pneurons;
		for (j=1; j<=players_help->no_neurons; j++)
		{
			pneurons_help->CalcOutput(pprev_layer);
//cout << "\noutput " << j << " = " << pneurons_help->output;
			pneurons_help++;
		}
		pprev_layer = players_help;
	}
}


void NN::backwardpass(Pattern *ppattern)
{
	int i, j;
	Neuron *pneurons_help;
	Layer *player_help, *pnext_layer_help;
	FP *ppattern_output_help;

	pneurons_help = poutput_layer->pneurons;
	ppattern_output_help = ppattern->poutput;
	for (j=0; j<poutput_layer->no_neurons; j++)
	{
		pneurons_help->CalcDeltaOutputLayer(ppattern_output_help);
		ppattern_output_help++;
		pneurons_help++;
	}
	player_help = poutput_layer;
	pnext_layer_help = poutput_layer;
	for (i=2; i<=no_layers; i++)
	{
		player_help--;
		pneurons_help = player_help->pneurons;
		for (j=0; j<player_help->no_neurons; j++)
		{
			pneurons_help->CalcDelta(pnext_layer_help, j);
			pneurons_help++;
		}
		pnext_layer_help--;
	}
}


void NN::calc_total_error(Pattern *ppattern)
{
	int i;
	Neuron *pneurons_help;
	FP *poutput_help, temp;

	pneurons_help = poutput_layer->pneurons;
	poutput_help = ppattern->poutput;
	for (i=0; i<poutput_layer->no_neurons; i++)
	{
		temp = *poutput_help - pneurons_help->GetOutput();
		temp = temp * temp;
		totalError += temp;
		pneurons_help++;
		poutput_help++;
	}
}


void NN::calc_deltaweights()
{
	int i, j;
	Layer *player_help, *pprev_layer;
	Neuron *pneuron_help;

	player_help = players;
	pprev_layer = players;
	for (i=2; i<=no_layers; i++)
	{
		player_help++;
		pneuron_help = player_help->pneurons;
		for (j=0; j<player_help->no_neurons; j++)
		{
			pneuron_help->CalcDeltaWeights(pprev_layer);
			pneuron_help++;
		}
		pprev_layer++;
	}
}


void NN::BackupWeights()
{
	int i, j;
	Layer *player_help, *pprev_layer;
	Neuron *pneuron_help;

	player_help = players;
	pprev_layer = players;
	for (i=2; i<=no_layers; i++)
	{
		player_help++;
		pneuron_help = player_help->pneurons;
		for (j=0; j<player_help->no_neurons; j++)
		{
			pneuron_help->BackupWeights(pprev_layer->no_neurons);
			pneuron_help++;
		}
		pprev_layer++;
	}
}


void NN::RestoreWeights()
{
	int i, j;
	Layer *player_help, *pprev_layer;
	Neuron *pneuron_help;

	player_help = players;
	pprev_layer = players;
	for (i=2; i<=no_layers; i++)
	{
		player_help++;
		pneuron_help = player_help->pneurons;
		for (j=0; j<player_help->no_neurons; j++)
		{
			pneuron_help->RestoreWeights(pprev_layer->no_neurons);
			pneuron_help++;
		}
		pprev_layer++;
	}
}


/*void NN::show_outputs()
{
	int i;
	Neuron *pneuron_help;

	pneuron_help = poutput_layer->pneurons;
	for (i=0; i<poutput_layer->no_neurons; i++)
	{
//		cout << "\nOutput neuron " << i << " = " << pneuron_help->output;
		pneuron_help++;
	}
}*/


long NN::GetNoWeights()
{
	long no_weights;
	int *pno_neur_per_layer_help, i;

	no_weights = 0;
	pno_neur_per_layer_help = pno_neur_per_layer;
	for (i=1; i<no_layers; i++)
	{
		no_weights += (long) *pno_neur_per_layer_help * *(pno_neur_per_layer_help+1);
		pno_neur_per_layer_help++;
	}
	return no_weights;
}


void NN::train(PatternSet *ppatternset, TrainingPar *tp, CBnnTraining *displayDialog)
{
	Boolean stop = FALSE;
	int i, j;
	long epoche = 0; 
	Pattern *ppattern_help;
	time_t   start, finish;
	double   elapsed_time, time_per_epoche;
	double	 mcups;
	FP	 max_error;

//ep	ErrorPlotDialog.Reset();
//ep	ErrorPlotDialog.ShowWindow(SW_HIDE);
//ep	ErrorPlotDialog.ShowWindow(SW_SHOW);
//ep	ErrorPlotDialog.SetPaintDC(&ErrorPlotDialog);
////ep	ErrorPlotDialog.SetTimer(1,5*1000, &TimerProc);

//	oFile.open("C:\\My Documents\\WL\\bnndata\\fm.txt");

	j = 0;
	max_error = 0.0;
	time( &start );
	do
	{
		BackupWeights();
		prevTotalError = totalError;
		totalError = 0.0;
		epoche++;
		ppattern_help = ppatternset->ppatterns;
		for (i=0; i< ppatternset->no_patterns; i++)
		{
			forwardpass(ppattern_help);
			calc_total_error(ppattern_help);
			backwardpass(ppattern_help);
			calc_deltaweights();
			ppattern_help++;
		}
		if (((tp->no_epoches != 0) && (tp->no_epoches <= epoche)) || 
			(totalError <= tp->des_error))
		{
			stop = TRUE;
			time( &finish );
			elapsed_time = difftime( finish, start );
			time_per_epoche = elapsed_time / (double) epoche;
			mcups = (theApp.m_pnn->GetNoWeights() * ppatternset->no_patterns)/
					time_per_epoche;
			mcups = mcups/1000000.0;
		}
		else
		{
			theApp.m_ptrainingpar->learning_rate->CalcLearningRate();
			theApp.m_ptrainingpar->momentum->CalcMomentum();
		}
		j++;
		if ((j==tp->update_count) || (stop == TRUE))
		{
			displayDialog->display(totalError, epoche, mcups, 
				theApp.m_ptrainingpar->learning_rate->GetLearningRate(),
				theApp.m_ptrainingpar->momentum->GetMomentum());
			j = 0;
		}
//ep		if (total_error > ErrorPlotDialog.GetMaxError())
//ep		{
//ep			ErrorPlotDialog.SetMaxError(total_error);
//ep			ErrorPlotDialog.SetMaxErrorChanged(true);
//ep		}
//ep		else
//ep		{
//ep			ErrorPlotDialog.SetMaxErrorChanged(false);
//ep		}
//ep		ErrorPlotDialog.AddToList( total_error);
//	//ep	dialog->EnableWindow(FALSE);
////ep		ErrorPlotDialog.EnableWindow(TRUE);

//ep		ErrorPlotDialog.Drawit();

////ep		ErrorPlotDialog.EnableWindow(FALSE);
//	//ep	dialog->EnableWindow(TRUE);
//	//ep	dialog->SetActiveWindow();
	}
	while (!stop);
//ep	ErrorPlotDialog.finished = TRUE;

//	oFile.close();
}


void NN::SetOutputs(TestPattern *ppattern)
{
	int i;
	Neuron *pneuron_help;
	FP *poutval;

	if (ppattern->poutput == NULL)
	{
		ppattern->poutput = new FP[poutput_layer->no_neurons];
	}
	poutval = ppattern->poutput;
	pneuron_help = poutput_layer->pneurons;
	for (i=0; i<poutput_layer->no_neurons; i++)
	{
		*poutval = pneuron_help->GetOutput();
		pneuron_help++;
		poutval++;
	}
}


void NN::test(TestPatternSet *ppatternset)
{
	int i;
	TestPattern *ppattern_help;
	int *pno_neur_per_layer_help;

	ppattern_help = ppatternset->ppatterns;
	for (i=0; i< ppatternset->no_patterns; i++)
	{
		forwardpass(ppattern_help);
		SetOutputs(ppattern_help);
		ppattern_help++;
	}
	pno_neur_per_layer_help = pno_neur_per_layer;
	for (i=1; i<no_layers;i++)
	{
		pno_neur_per_layer_help++;
	}
	ppatternset->no_outval = *pno_neur_per_layer_help;
}


FP NN::GetPrevTotalError()
{
	return prevTotalError;
}


void NN::SetPrevTotalError(FP totalError)
{
	prevTotalError = totalError;
}


FP NN::GetTotalError()
{
	return totalError;
}


LearningRate::LearningRate()
{
	;
}

LearningRate::LearningRate(ALearningRate *aLearningRate)
{
	_aLearningRate = aLearningRate;
}


LearningRate::~LearningRate()
{
	;
}


FP LearningRate::GetLearningRate()
{
	return _aLearningRate->GetLearningRate();
}


void LearningRate::SetLearningRate(FP learningRate)
{
	_aLearningRate->SetLearningRate(learningRate);
}

void LearningRate::CalcLearningRate()
{
	_aLearningRate->CalcLearningRate();
}


FP ALearningRate::GetLearningRate()
{
	return learningRate;
}


void ALearningRate::SetLearningRate(FP lr)
{
	learningRate = lr;
}


StaticLearningRate::StaticLearningRate()
{
	;
}

StaticLearningRate::StaticLearningRate(FP lr)
{
	SetLearningRate(lr);
}

void StaticLearningRate::CalcLearningRate()
{
	;
}


BoldDriverLearningRate::BoldDriverLearningRate()
{
	;
}


BoldDriverLearningRate::BoldDriverLearningRate(FP lr, FP lr_increase, 
											   FP lr_decrease)
{
	SetLearningRate(lr);
	learningRateIncrease = lr_increase;
	learningRateDecrease = lr_decrease;
}


void BoldDriverLearningRate::CalcLearningRate()
{
	NN *m_pnn=theApp.m_pnn;

	if ((m_pnn->GetTotalError() == m_pnn->GetPrevTotalError()) ||
		(m_pnn->GetPrevTotalError() == 0.0)) 
	{
/*		if (GetLearningRate() >= 10.0)
		{
			SetLearningRate(GetLearningRate() * learningRateDecrease);
//			m_pnn->RestoreWeights();
		}
		else if (GetLearningRate() <= 0.01)
			SetLearningRate(GetLearningRate() * learningRateIncrease);*/
		;	// same learning rate, do nothing.
	}
	else if (m_pnn->GetTotalError() < m_pnn->GetPrevTotalError())
	{
		if (GetLearningRate() <= 10.0)
			SetLearningRate(GetLearningRate() * learningRateIncrease);
	}
	else
	{
		if (GetLearningRate() >= 0.01)
		{
			SetLearningRate(GetLearningRate() * learningRateDecrease);
			m_pnn->RestoreWeights();
		}
	}
}


FuzzyLogicLearningRate::FuzzyLogicLearningRate()
{
	NB = -0.08;
	NT = -0.04;
	ZRmin = -0.001;
	ZRplus = 0.001;
	PT = 0.04; 
	PB = 0.08;
}


FuzzyLogicLearningRate::FuzzyLogicLearningRate(FP lr)
{
	NB = -0.08;
	NT = -0.04;
	ZRmin = -0.001;
	ZRplus = 0.001;
	PT = 0.04; 
	PB = 0.08;
	SetLearningRate(lr);
}


void FuzzyLogicLearningRate::CalcLearningRate()
{
	NN *m_pnn=theApp.m_pnn;
	FP error, deltaError, temp;
	FP memberPB, memberPT, memberZR, memberNT, memberNB;
	FP learningRate;

	temp = 0.0;
	error = m_pnn->GetTotalError();
	if (m_pnn->GetPrevTotalError() == 0.0)
	{
		deltaError = 0.0;
		Init(error);
	}
	else
		deltaError = error - m_pnn->GetPrevTotalError();
	CalcGamma(error);
	
	memberPB = CalcPB(error, deltaError);
	memberPT = CalcPT(error, deltaError);
	memberZR = CalcZR(error, deltaError);
	memberNT = CalcNT(error, deltaError);
	memberNB = CalcNB(error, deltaError);
	
	temp = memberPB * PB * gamma;
	temp += memberPT * PT * gamma;
	if (deltaError > 0.0)
		temp += memberZR * ZRplus * gamma;
	else
		temp += memberZR * ZRmin * gamma;
	temp += memberNT * NT * gamma;
	temp += memberNB * NB * gamma;
	learningRate = GetLearningRate();
	learningRate +=	temp / (memberPB + memberPT + memberZR + memberNT + memberNB);
	if (learningRate <= 0.0)
		learningRate = 0.1;
	SetLearningRate(learningRate);
}


FP FuzzyLogicLearningRate::CalcVL(FP error)
{
	if (error <= (0.1 * gamma))
		return 1.0;
	else if (error >= (0.3 * gamma))
		return 0.0;
	else
		return (((-5.0 / gamma) * error) + 1.5);
}


FP FuzzyLogicLearningRate::CalcLO(FP error)
{
	if ((error > (0.1 * gamma)) && (error <= (0.3 * gamma)))
		return (((5.0 / gamma) * error) - 0.5);
	else if ((error > (0.3 * gamma)) && (error < (0.5 * gamma)))
		return (((-5.0 / gamma) * error) + 2.5);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcME(FP error)
{
	if ((error > (0.3 * gamma)) && (error <= (0.5 * gamma)))
		return (((5.0 / gamma) * error) - 1.5);
	else if ((error > (0.5 * gamma)) && (error < (0.7 * gamma)))
		return (((-5.0 / gamma) * error) + 3.5);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcHI(FP error)
{
	if ((error > (0.5 * gamma)) && (error <= (0.7 * gamma)))
		return (((5.0 / gamma) * error) - 2.5);
	else if ((error > (0.7 * gamma)) && (error < (0.9 * gamma)))
		return (((-5.0 / gamma) * error) + 4.5);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcVH(FP error)
{
	if (error <= (0.7 * gamma))
		return 0.0;
	else if (error >= (0.9 * gamma))
		return 1.0;
	else
		return (((5.0 / gamma) * error) - 3.5);
}


FP FuzzyLogicLearningRate::CalcNL(FP deltaError)
{
	if (deltaError <= (-0.03 * gamma))
		return 1.0;
	else if (deltaError >= (-0.01 * gamma))
		return 0.0;
	else
		return (((-50.0 / gamma) * deltaError) - 0.5);
}


FP FuzzyLogicLearningRate::CalcNS(FP deltaError)
{
	if ((deltaError > (-0.03 * gamma)) && (deltaError <= (-0.01 * gamma)))
		return (((50.0 / gamma) * deltaError) + 1.5);
	else if ((deltaError > (-0.01 * gamma)) && (deltaError < 0.0))
		return ((-100.0 / gamma) * deltaError);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcZE(FP deltaError)
{
	if ((deltaError > (-0.01 * gamma)) && (deltaError <= 0.0))
		return (((100.0 / gamma) * deltaError) + 1.0);
	else if ((deltaError > 0.0) && (deltaError < (0.01 * gamma)))
		return (((-100.0 / gamma) * deltaError) + 1.0);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcPS(FP deltaError)
{
	if ((deltaError > 0.0) && (deltaError <= (0.01 * gamma)))
		return ((100.0 / gamma) * deltaError);
	else if ((deltaError > (0.01 * gamma)) && (deltaError < (0.03 * gamma)))
		return (((-50.0 / gamma) * deltaError) + 1.5);
	else
		return 0.0;
}


FP FuzzyLogicLearningRate::CalcPL(FP deltaError)
{
	if (deltaError <= (0.01 * gamma))
		return 0.0;
	else if (deltaError >= (0.03 * gamma))
		return 1.0;
	else
		return (((50.0 / gamma) * deltaError) - 0.5);
}


FP FuzzyLogicLearningRate::CalcNB(FP error, FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcVH(error), CalcPL(deltaError));
	tempMax = max (tempMax, min(CalcHI(error), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcME(error), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcLO(error), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcVL(error), CalcPL(deltaError)));
	return tempMax;
}


FP FuzzyLogicLearningRate::CalcNT(FP error, FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcVH(error), CalcPS(deltaError));
	tempMax = max (tempMax, min(CalcHI(error), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcME(error), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcLO(error), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcVL(error), CalcPS(deltaError)));
	return tempMax;
}


FP FuzzyLogicLearningRate::CalcZR(FP error, FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcVH(error), CalcZE(deltaError));
	tempMax = max (tempMax, min(CalcHI(error), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcME(error), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcLO(error), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcVL(error), CalcZE(deltaError)));
	return tempMax;
}


FP FuzzyLogicLearningRate::CalcPT(FP error, FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcVH(error), CalcNS(deltaError));
	tempMax = max (tempMax, min(CalcHI(error), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcME(error), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcLO(error), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcVL(error), CalcNS(deltaError)));
	return tempMax;
}


FP FuzzyLogicLearningRate::CalcPB(FP error, FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcVH(error), CalcNL(deltaError));
	tempMax = max (tempMax, min(CalcHI(error), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcME(error), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcLO(error), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcVL(error), CalcNL(deltaError)));
	return tempMax;
}


void FuzzyLogicLearningRate::CalcGamma(FP error)
{
	if (error >= errorBegin)
		gamma = 1.0;
	else if (error == 0.0)
		gamma = 0.0001;
	else
		gamma = (error / errorBegin);
}


void FuzzyLogicLearningRate::Init(FP error)
{
	errorBegin = error;
}


Momentum::Momentum()
{
	;
}

Momentum::Momentum(AMomentum *aMomentum)
{
	_aMomentum = aMomentum;
}


Momentum::~Momentum()
{
	;
}


FP Momentum::GetMomentum()
{
	return _aMomentum->GetMomentum();
}


void Momentum::SetMomentum(FP m)
{
	_aMomentum->SetMomentum(m);
}

void Momentum::CalcMomentum()
{
	_aMomentum->CalcMomentum();
}


FP AMomentum::GetMomentum()
{
	return momentum;
}


void AMomentum::SetMomentum(FP m)
{
	momentum = m;
}


StaticMomentum::StaticMomentum()
{
	;
}

StaticMomentum::StaticMomentum(FP m)
{
	SetMomentum(m);
}

void StaticMomentum::CalcMomentum()
{
	;
}


FuzzyLogicMomentum::FuzzyLogicMomentum()
{
	NB = -0.8;
	NT = -0.4;
	ZRmin = -0.1;
	ZRplus = 0.1;
	PT = 0.4; 
	PB = 0.8;
	prevDeltaError = 0.0;
}


FuzzyLogicMomentum::FuzzyLogicMomentum(FP m)
{
	NB = -0.8;
	NT = -0.4;
	ZRmin = -0.1;
	ZRplus = 0.1;
	PT = 0.4; 
	PB = 0.8;
	prevDeltaError = 0.0;
	SetMomentum(m);
}


void FuzzyLogicMomentum::CalcMomentum()
{
	NN *m_pnn=theApp.m_pnn;
	FP error, deltaError, temp;
	FP memberPB, memberPT, memberZR, memberNT, memberNB;
	FP momentum, momentumhelp;

	temp = 0.0;
	error = m_pnn->GetTotalError();
	if (m_pnn->GetPrevTotalError() == 0.0)
	{
		deltaError = 0.0;
		Init(error);
	}
	else
		deltaError = error - m_pnn->GetPrevTotalError();
	CalcGamma(error);
	
	memberPB = CalcPB(deltaError);
	memberPT = CalcPT(deltaError);
	memberZR = CalcZR(deltaError);
	memberNT = CalcNT(deltaError);
	memberNB = CalcNB(deltaError);
	
	temp = memberPB * PB * gamma;
	temp += memberPT * PT * gamma;
	if (deltaError >= 0.0)
		temp += memberZR * ZRplus * gamma;
	else
		temp += memberZR * ZRmin * gamma;
	temp += memberNT * NT * gamma;
	temp += memberNB * NB * gamma;
	momentum = GetMomentum();
	momentumhelp =	temp / (memberPB + memberPT + memberZR + memberNT + memberNB);
	momentum += momentumhelp;
	if (momentum <= 0.0)
		momentum = 0.9;
	else if (momentum > 1.0)
		momentum = 0.9;
	SetMomentum(momentum);
	prevDeltaError = deltaError;

//	oFile << error << ' ' << deltaError << ' '
//		<< theApp.m_ptrainingpar->learning_rate->GetLearningRate() << ' ' 
//		<< momentum << ' ' << momentumhelp << "\n"; 
}


FP FuzzyLogicMomentum::CalcNL(FP deltaError)
{
	if (deltaError <= (-0.03 * gamma))
		return 1.0;
	else if (deltaError >= (-0.01 * gamma))
		return 0.0;
	else
		return (((-50.0 / gamma) * deltaError) - 0.5);
}


FP FuzzyLogicMomentum::CalcNS(FP deltaError)
{
	if ((deltaError > (-0.03 * gamma)) && (deltaError <= (-0.01 * gamma)))
		return (((50.0 / gamma) * deltaError) + 1.5);
	else if ((deltaError > (-0.01 * gamma)) && (deltaError < 0.0))
		return ((-100.0 / gamma) * deltaError);
	else
		return 0.0;
}


FP FuzzyLogicMomentum::CalcZE(FP deltaError)
{
	if ((deltaError > (-0.01 * gamma)) && (deltaError <= 0.0))
		return (((100.0 / gamma) * deltaError) + 1.0);
	else if ((deltaError > 0.0) && (deltaError < (0.01 * gamma)))
		return (((-100.0 / gamma) * deltaError) + 1.0);
	else
		return 0.0;
}


FP FuzzyLogicMomentum::CalcPS(FP deltaError)
{
	if ((deltaError > 0.0) && (deltaError <= (0.01 * gamma)))
		return ((100.0 / gamma) * deltaError);
	else if ((deltaError > (0.01 * gamma)) && (deltaError < (0.03 * gamma)))
		return (((-50.0 / gamma) * deltaError) + 1.5);
	else
		return 0.0;
}


FP FuzzyLogicMomentum::CalcPL(FP deltaError)
{
	if (deltaError <= (0.01 * gamma))
		return 0.0;
	else if (deltaError >= (0.03 * gamma))
		return 1.0;
	else
		return (((50.0 / gamma) * deltaError) - 0.5);
}


FP FuzzyLogicMomentum::CalcNB(FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcPL(prevDeltaError), CalcPL(deltaError));
	tempMax = max (tempMax, min(CalcPS(prevDeltaError), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcZE(prevDeltaError), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcNS(prevDeltaError), CalcPL(deltaError)));
	tempMax = max (tempMax, min(CalcNL(prevDeltaError), CalcPL(deltaError)));
	return tempMax;
}


FP FuzzyLogicMomentum::CalcNT(FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcPL(prevDeltaError), CalcPS(deltaError));
	tempMax = max (tempMax, min(CalcPS(prevDeltaError), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcZE(prevDeltaError), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcNS(prevDeltaError), CalcPS(deltaError)));
	tempMax = max (tempMax, min(CalcNL(prevDeltaError), CalcPS(deltaError)));
	return tempMax;
}


FP FuzzyLogicMomentum::CalcZR(FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcPL(prevDeltaError), CalcZE(deltaError));
	tempMax = max (tempMax, min(CalcPS(prevDeltaError), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcZE(prevDeltaError), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcNS(prevDeltaError), CalcZE(deltaError)));
	tempMax = max (tempMax, min(CalcNL(prevDeltaError), CalcZE(deltaError)));
	return tempMax;
}


FP FuzzyLogicMomentum::CalcPT(FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcPL(prevDeltaError), CalcNS(deltaError));
	tempMax = max (tempMax, min(CalcPS(prevDeltaError), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcZE(prevDeltaError), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcNS(prevDeltaError), CalcNS(deltaError)));
	tempMax = max (tempMax, min(CalcNL(prevDeltaError), CalcNS(deltaError)));
	return tempMax;
}


FP FuzzyLogicMomentum::CalcPB(FP deltaError)
{
	FP tempMax;

	tempMax = min(CalcPL(prevDeltaError), CalcNL(deltaError));
	tempMax = max (tempMax, min(CalcPS(prevDeltaError), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcZE(prevDeltaError), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcNS(prevDeltaError), CalcNL(deltaError)));
	tempMax = max (tempMax, min(CalcNL(prevDeltaError), CalcNL(deltaError)));
	return tempMax;
}


void FuzzyLogicMomentum::CalcGamma(FP error)
{
	if (error >= errorBegin)
		gamma = 1.0;
	else if (error == 0.0)
		gamma = 0.0001;
	else
		gamma = (error / errorBegin);
}


void FuzzyLogicMomentum::Init(FP error)
{
	errorBegin = error;
}



/* -------------------------------------------------------------------------------*/
UINT MyThreadProc( LPVOID pParam )
{
//	ErrorPlotDialog.MessageBox("Hallo");
	
    //TRAIN* ptrain = (TRAIN*)pParam;

theApp.m_pnn->train2();
	return 0;
}


/* TRAIN 2   TRAIN 2   TRAIN 2 */
void NN::train2(/*TRAIN *dialog*/)
{
	Boolean stop = FALSE;
	int i, j;
	long epoche = 0; 
	Pattern *ppattern_help;
	time_t   start, finish;
	double   elapsed_time, time_per_epoche;
	double	 mcups;
	FP	 max_error;
PatternSet *ppatternset; 
TrainingPar *tp;

	ppatternset = theApp.m_ppatternset;
	tp = theApp.m_ptrainingpar;
/*	ErrorPlotDialog.Reset();
	ErrorPlotDialog.ShowWindow(SW_HIDE);
	ErrorPlotDialog.ShowWindow(SW_SHOW);
	ErrorPlotDialog.SetPaintDC(&ErrorPlotDialog);*/
//	ErrorPlotDialog.SetTimer(1,5*1000, &TimerProc);

	j = 0;
	max_error = 0.0;
	time( &start );
	do
	{
		totalError = 0.0;
		epoche++;
		ppattern_help = ppatternset->ppatterns;
		for (i=0; i< ppatternset->no_patterns; i++)
		{
			forwardpass(ppattern_help);
			calc_total_error(ppattern_help);
			backwardpass(ppattern_help);
			calc_deltaweights();
			ppattern_help++;
		}
		if (((tp->no_epoches != 0) && (tp->no_epoches <= epoche)) || 
			(totalError <= tp->des_error))
		{
			stop = TRUE;
			time( &finish );
			elapsed_time = difftime( finish, start );
//			sprintf(buf,"%f",elapsed_time);
//			dialog->MessageBox(buf);
			time_per_epoche = elapsed_time / (double) epoche;
			mcups = (theApp.m_pnn->GetNoWeights() * ppatternset->no_patterns)/
					time_per_epoche;
			mcups = mcups/1000000.0;
		}
		j++;
		if ((j==tp->update_count) || (stop == TRUE))
		{
	//		dialog->display(total_error, epoche, mcups);
//			dialog->m_error.Format("%f", total_error);
//			dialog->m_epoche_number.Format("%ld", epoche);
//			dialog->UpdateData(FALSE);
			j = 0;
		}
/*		if (total_error > ErrorPlotDialog.GetMaxError())
		{
			ErrorPlotDialog.SetMaxError(total_error);
			ErrorPlotDialog.SetMaxErrorChanged(true);
		}
		else
		{
			ErrorPlotDialog.SetMaxErrorChanged(false);
		}
		ErrorPlotDialog.AddToList(total_error);*/
//		dialog->EnableWindow(FALSE);
//		ErrorPlotDialog.EnableWindow(TRUE);

//		ErrorPlotDialog.Drawit();

//		ErrorPlotDialog.EnableWindow(FALSE);
//		dialog->EnableWindow(TRUE);
//		dialog->SetActiveWindow();
	}
	while (!stop);
//	ErrorPlotDialog.finished = TRUE;
}
