// bnnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "bnnDlg.h"
#include "BnnNew.h"
#include "TRAIN.h"
#include "bnn_test.h"
#include "errorplot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBnnApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnDlg dialog

CBnnDlg::CBnnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBnnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBnnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBnnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBnnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBnnDlg, CDialog)
	//{{AFX_MSG_MAP(CBnnDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NN_NEW, OnNnNew)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(ID_NN_TRAIN, OnNnTrain)
	ON_BN_CLICKED(IDC_NN_TEST, OnNnTest)
	ON_BN_CLICKED(IDC_NN_LOAD, OnNnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBnnDlg message handlers

BOOL CBnnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBnnDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBnnDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBnnDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
	int number_of_neur_per_layer[3];
	FP inval[3], outval;
	int no_patterns = 8;
	Pattern lp[8];
//	CString str;

	UpdateData(TRUE);
//	str.Format("%d", m_no_neur_layer_1);
//	MessageBox(str);
	srand( (unsigned)time( NULL ) );

//	learn_rate = (float) 0.1;
//	momentum_val = (float) 0.9;
//	des_error = (float) 0.001;
//	no_layers = 3;
	
	number_of_neur_per_layer[0]=3;
	number_of_neur_per_layer[1]=m_no_neur_layer_1;
	number_of_neur_per_layer[2]=1;
*/
/*	inval[0] = (float) 0.1;
	inval[1] = (float) 0.1;
	inval[2] = (float) 0.1;
	outval = (float) 0.1;
	lp[0].set_pattern(3, 1, &inval[0], &outval);

	inval[0] = (float) 0.1;
	inval[1] = (float) 0.1;
	inval[2] = (float) 0.9;
	outval = (float) 0.9;
	lp[1].set_pattern(3, 1, &inval[0], &outval);
	
	inval[0] = (float) 0.1;
	inval[1] = (float)0.9;
	inval[2] = (float) 0.1;
	outval = (float) 0.9;
	lp[2].set_pattern(3, 1, &inval[0], &outval);
	
	inval[0] = (float) 0.1;
	inval[1] = (float) 0.9;
	inval[2] = (float) 0.9;
	outval = (float) 0.1;
	lp[3].set_pattern(3, 1, &inval[0], &outval);

	inval[0] = (float) 0.9;
	inval[1] = (float) 0.1;
	inval[2] = (float) 0.1;
	outval = (float) 0.9;
	lp[4].set_pattern(3, 1, &inval[0], &outval);

	inval[0] = (float) 0.9;
	inval[1] = (float) 0.1;
	inval[2] = (float) 0.9;
	outval = (float) 0.1;
	lp[5].set_pattern(3, 1, &inval[0], &outval);
	
	inval[0] = (float) 0.9;
	inval[1] = (float)0.9;
	inval[2] = (float) 0.1;
	outval = (float) 0.1;
	lp[6].set_pattern(3, 1, &inval[0], &outval);
	
	inval[0] = (float) 0.9;
	inval[1] = (float) 0.9;
	inval[2] = (float) 0.9;
	outval = (float) 0.9;
	lp[7].set_pattern(3, 1, &inval[0], &outval);
*/
/*	CFile theFile;
//	CFileDialog FD(FALSE,NULL,NULL,NULL,NULL); // save
	CFileDialog FD(TRUE,NULL,NULL,NULL,NULL); // load

	FD.DoModal();
	CString filename = FD.GetPathName();

//	theFile.Open(filename, CFile::modeCreate + CFile::modeWrite);
//	CArchive archive(&theFile, CArchive::store);
	theFile.Open(filename, CFile::modeRead);
	CArchive archive(&theFile, CArchive::load);

	for (int i=0; i<no_patterns; i++)
		lp[i].serialize(number_of_neur_per_layer[0],number_of_neur_per_layer[2],
			archive);

	for (i=0; i<no_patterns; i++)
		lp[i].show(number_of_neur_per_layer[0],number_of_neur_per_layer[2],this);
	archive.Close();
	theFile.Close();
*/


//	NN nn(m_no_layers, number_of_neur_per_layer);

//	nn.train(no_patterns, &lp[0], m_des_error, 1000, this);
//	nn.test(no_patterns, &lp[0]);// TODO: Add extra validation here

void CBnnDlg::OnNnNew() 
{
	// TODO: 
	CBnnNew NewDialog;

	NewDialog.DoModal();	
}

void CBnnDlg::OnExit() 
{
	// TODO
	CDialog::OnCancel();
}

void CBnnDlg::OnNnTrain() 
{
	// TODO: 
	if (theApp.m_pnn == NULL)
		MessageBox("No Neural Network available");
	else
	{
		TRAIN TrainDialog;
		TrainDialog.DoModal();
	}
}

void CBnnDlg::OnNnTest() 
{
	// TODO
	bnn_test TestPatDialog;

	TestPatDialog.DoModal();
}

void CBnnDlg::OnNnLoad() 
{
	// TODO: 
	ErrorPlot ErrorPlotDialog;

//ErrorPlotDialog.DoModal();
	ErrorPlotDialog.Create(IDD_ERROR_PLOT_DIALOG, NULL);
	ErrorPlotDialog.ShowWindow(SW_SHOW);	
}
