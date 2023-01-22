// bnn.h : main header file for the BNN application
//

#if !defined(AFX_BNN_H__F28984A4_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
#define AFX_BNN_H__F28984A4_423B_11D5_8BEB_C0AB56C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <fstream.h>
#include "resource.h"		// main symbols
#include "TRAIN.h"
#include "BnnTraining.h"
#include "bnnDlg.h"
#include "fp.h"


#define FALSE 0
#define TRUE 1

typedef unsigned char Boolean;

UINT MyThreadProc( LPVOID pParam );



class ALearningRate
{
public:
	virtual void CalcLearningRate() = 0;
	FP GetLearningRate();
	void SetLearningRate(FP lr);
private:
	FP learningRate;
};


class StaticLearningRate : public ALearningRate
{
public:
	StaticLearningRate();
	StaticLearningRate(FP lr);
	virtual void CalcLearningRate();
};


class BoldDriverLearningRate : public ALearningRate
{
public:
	BoldDriverLearningRate();
	BoldDriverLearningRate(FP lr, FP lr_increase, FP lr_decrease);
	virtual void CalcLearningRate();
private:
	FP learningRateIncrease;
	FP learningRateDecrease;
};


class FuzzyLogicLearningRate : public ALearningRate
{
public:
	FuzzyLogicLearningRate();
	FuzzyLogicLearningRate(FP lr);
	virtual void CalcLearningRate();
	FP CalcVL(FP error);
	FP CalcLO(FP error);
	FP CalcME(FP error);
	FP CalcHI(FP error);
	FP CalcVH(FP error);
	FP CalcNL(FP deltaError);
	FP CalcNS(FP deltaError);
	FP CalcZE(FP deltaError);
	FP CalcPS(FP deltaError);
	FP CalcPL(FP deltaError);
	FP CalcNB(FP error, FP deltaError);
	FP CalcNT(FP error, FP deltaError);
	FP CalcZR(FP error, FP deltaError);
	FP CalcPT(FP error, FP deltaError);
	FP CalcPB(FP error, FP deltaError);
	void CalcGamma(FP error);
	void Init(FP error);
private:
	FP gamma;
	FP errorBegin;
	FP NB, NT, ZRmin, ZRplus, PT, PB;
};


class LearningRate
{
public:
	LearningRate();
	LearningRate(ALearningRate *aLearningRate);
//	void setcomp(ALearningRate *aLearningRate);
	~LearningRate();
	FP GetLearningRate();
	void SetLearningRate(FP learningRate);
	void CalcLearningRate();
private:
	ALearningRate *_aLearningRate;
};


class AMomentum
{
public:
	virtual void CalcMomentum() = 0;
	FP GetMomentum();
	void SetMomentum(FP m);
private:
	FP momentum;
};


class StaticMomentum : public AMomentum
{
public:
	StaticMomentum();
	StaticMomentum(FP m);
	virtual void CalcMomentum();
};


class FuzzyLogicMomentum : public AMomentum
{
public:
	FuzzyLogicMomentum();
	FuzzyLogicMomentum(FP m);
	virtual void CalcMomentum();
	FP CalcNL(FP deltaError);
	FP CalcNS(FP deltaError);
	FP CalcZE(FP deltaError);
	FP CalcPS(FP deltaError);
	FP CalcPL(FP deltaError);
	FP CalcNB(FP deltaError);
	FP CalcNT(FP deltaError);
	FP CalcZR(FP deltaError);
	FP CalcPT(FP deltaError);
	FP CalcPB(FP deltaError);
	void CalcGamma(FP error);
	void Init(FP error);
private:
	FP gamma;
	FP errorBegin;
	FP NB, NT, ZRmin, ZRplus, PT, PB;
	FP prevDeltaError;
};


class Momentum
{
public:
	Momentum();
	Momentum(AMomentum *aMomentum);
//	void setcomp(ALearningRate *aLearningRate);
	~Momentum();
	FP GetMomentum();
	void SetMomentum(FP m);
	void CalcMomentum();
private:
	AMomentum *_aMomentum;
};


class TrainingPar
{
public:
	LearningRate*	learning_rate;
	Momentum*	momentum;
	FP	des_error;
	long	no_epoches;
	long	update_count;
	TrainingPar();
	~TrainingPar();
	load(CString filename);
	save(CString filename);
};


class Pattern
{
public:
	FP *pinput;
	FP *poutput;
	Pattern();
	virtual void set_pattern(int no_inval, int no_outval, FP *pinval, FP *poutval);
	virtual void load(int no_inval, int no_outval, ifstream& iFile);
	virtual void save(int no_inval, int no_outval, ofstream& oFile);
	virtual void show(int no_inval, int no_outval, TRAIN *dlg);
	~Pattern();
};


class PatternSet
{
public:
	int no_patterns;
	int	no_inval;
	int	no_outval;
	Pattern *ppatterns;
	PatternSet();
	virtual void set_patternset(int number_of_patterns, int no_in_val, int no_out_val, 
							Pattern *p2patterns);
	virtual void load(CString filename);
	virtual void save(CString filename);
	~PatternSet();
	void show(TRAIN *dlg);
};


class TestPattern : public Pattern
{
public:
	void set_pattern(int no_inval, FP *pinval);
	void load(int no_inval, ifstream& iFile);
	void save(int no_inval, ofstream& oFile);
//	void show(int no_inval, TRAIN *dlg);
};


class TestPatternSet : public PatternSet
{
public:
	TestPattern *ppatterns;
	void set_patternset(int number_of_patterns, int no_in_val, TestPattern *p2patterns);
	void load(CString filename);
	void save(CString filename);
};


class Weight
{
public:
	Weight();
	~Weight();
	FP GetWeight();
	FP GetDeltaWeight();
	FP GetPrevDeltaWeight();
	void SetWeight(FP weight);
	void SetDeltaWeight(FP deltaWeight);
	void SetPrevDeltaWeight(FP prevDeltaWeight);
	void CalcDeltaWeight(FP delta, FP output);
	void AdjustWeight();
private:
	FP weight;
	FP deltaWeight;
	FP prevDeltaWeight;
	FP learningRate, momentum;
};


class Layer;

class Neuron
{
public:
//	FP input;
	Neuron();
	~Neuron();
	virtual void SetNeuron(int no_neur_prev_layer, Boolean hasBias);
	virtual void CalcOutput(Layer *PPrevLayer);
	virtual FP CalcInput(Layer *PPrevLayer);
	virtual void CalcActivation(FP inval);
	virtual FP CalcActivationFirstDerivative();
	virtual void CalcDelta(Layer *pnext_layer, int weight_number);
	virtual void CalcDeltaOutputLayer(FP *ppattern_output);
	virtual void CalcDeltaWeights(Layer *pPrevLayer);
	virtual void BackupWeights(int no_neur_prev_layer);
	virtual void RestoreWeights(int no_neur_prev_layer);
	virtual Weight *GetPPrevInWeights();
	virtual Weight *GetPInWeights();
	virtual FP GetOutput();
	virtual FP GetDelta();
	virtual void SetPPrevInWeights(Weight *pInWeights);
	virtual void SetPInWeights(Weight *pInWeights);
	virtual void SetOutput(FP output);
	virtual void SetDelta(FP delta);

private:
	FP output;
	FP delta;
	Weight *pInWeights;
	Weight *pPrevInWeights;
	Weight *pBias;
	Weight *pPrevBias;
};


class Layer
{
public:
	int no_neurons;
	Neuron *pneurons;
	Layer();
	~Layer();
	void setlayer(int num_of_neurons, int no_neur_prev_layer, Boolean hasBias);
};


class NN
{
public:
	int no_layers;
	int *pno_neur_per_layer;
	Layer *players, *poutput_layer;
	NN(int num_of_layers, int num_of_neur_per_layer[], Boolean hasBias);
	~NN();
	void Delete();
	void forwardpass(Pattern *ppattern);
	void backwardpass(Pattern *ppattern);
	void calc_total_error(Pattern *ppattern);
	void calc_deltaweights();
//	void show_outputs();
	void train(PatternSet *ppatternset, TrainingPar *tp, CBnnTraining *displayDialog);
	void train2();
	void SetOutputs(TestPattern *ppattern);
	void test(TestPatternSet *ppatternset);
	long GetNoWeights();
	void BackupWeights();
	void RestoreWeights();
	FP GetPrevTotalError();
	void SetPrevTotalError(FP totalError);
	FP GetTotalError();
	Boolean HasBias();
private:
	FP prevTotalError;
	FP totalError;
	Boolean hasBias;
};



/////////////////////////////////////////////////////////////////////////////
// CBnnApp:
// See bnn.cpp for the implementation of this class
//

class CBnnApp : public CWinApp
{
public:
	NN* m_pnn;
	PatternSet *m_ppatternset;
	TestPatternSet *m_ptestpatternset;
	TrainingPar *m_ptrainingpar;
	CString m_train_patterns_filename;
	CBnnApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBnnApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBnnApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNN_H__F28984A4_423B_11D5_8BEB_C0AB56C10000__INCLUDED_)
