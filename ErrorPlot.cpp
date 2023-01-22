// ErrorPlot.cpp : implementation file
//

#include "stdafx.h"
#include "bnn.h"
#include "ErrorPlot.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ErrorPlot dialog


ErrorPlot::ErrorPlot(CWnd* pParent /*=NULL*/)
	: CDialog(ErrorPlot::IDD, pParent)
{
	//{{AFX_DATA_INIT(ErrorPlot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	maxError = 0.0;
	maxErrorChanged = FALSE;
	xStepChanged = FALSE;
	currentXStep = 1;
	nonSummaryArea = 500;
	bottomMargin = 10;
	finished = FALSE;
}


void ErrorPlot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ErrorPlot)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ErrorPlot, CDialog)
	//{{AFX_MSG_MAP(ErrorPlot)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ErrorPlot message handlers


BOOL ErrorPlot::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ErrorPlot::OnPaint() 
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
		OnDrawit();
		CDialog::OnPaint();
	}
}


void ErrorPlot::OnDrawit() 
{
	RECT* pRect = &paintDC->m_ps.rcPaint;
	FP error;
	FP errorPerc;
	int  x, y, xstep, xstephelp, noXSteps;
	int right, bottom;

//	sprintf(buf, "%d", pRect->right);
//	paintDC->DrawText(buf,pRect,0);

	bottom = pRect->bottom;
	pRect->bottom = pRect->bottom - 100;
	right = pRect->right;
	pRect->right = pRect->right - 100;

	if (ErrorList.GetCount() > pRect->right)
	{
		xstep = (int) (ceil((ErrorList.GetCount() - nonSummaryArea)/
			(pRect->right - nonSummaryArea)));
        noXSteps = (int) (ceil((ErrorList.GetCount() - nonSummaryArea) / xstep));
	    if (xstep != currentXStep)
		{
			currentXStep = xstep;
			xStepChanged = TRUE;
		}
		else
		{
			xStepChanged = FALSE;
		}
	}
	else
	{
		xstep = 1;
	}
	xstephelp = xstep;
	x = 1;
	if ((maxErrorChanged == true) || (xStepChanged == TRUE) || (finished))
	{
		POSITION pos = ErrorList.GetHeadPosition();
		if (finished)
		{
			ShowWindow(SW_SHOW);
		}
//			RedrawWindow(NULL,NULL,0);
		else
		{
			RedrawWindow(NULL,NULL, RDW_ERASE+RDW_INVALIDATE+RDW_ERASENOW);
/*			tagRECT rect;
			rect.bottom = pRect->bottom - 100;
			rect.left = 0;
			rect.right = pRect->right - 100;
			rect.top = 0;
			RedrawWindow(&rect,NULL, RDW_ERASE+RDW_INVALIDATE+RDW_ERASENOW);*/
		}
		paintDC->MoveTo((pRect->right - nonSummaryArea),pRect->top);
		paintDC->LineTo((pRect->right - nonSummaryArea),pRect->bottom);
		paintDC->MoveTo(0, pRect->top);
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			error = ErrorList.GetNext(pos);
			xstephelp--;
			if (xstephelp == 0)
			{
				errorPerc = error / maxError;
				y = (int) ((pRect->bottom - bottomMargin) * errorPerc);
				y = (pRect->bottom - bottomMargin) - y;
				paintDC->LineTo(x,y);
				paintDC->MoveTo(x,y);
//				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
//					((pRect->right - 200)-x)))
//				if ((xstep > 1) && (x >= (pRect->right - 200)))
				if ((xstep > 1) && (x >= noXSteps))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;
			}
		}
	}
	else
	{
		error = ErrorList.GetTail();
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			xstephelp--;
			if (xstephelp == 0)
			{
//				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
//					((pRect->right - 200)-x)))
				if ((xstep > 1) && (x >= noXSteps))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;
			}
		}
		errorPerc = error / maxError;
		y = (int) ((pRect->bottom - bottomMargin) * errorPerc);
		y = (pRect->bottom - bottomMargin) - y;
		paintDC->LineTo(x,y);
		paintDC->MoveTo(x,y);
	}
	pRect->bottom = bottom;
	pRect->right = right;
}


/*
void ErrorPlot::OnDrawit() 
{
	// construct a paint DC from the dialog window
//	CPaintDC paintDC(this);
	// make a shortcut pointer to the rectangle
	// note that this time only the paint rectangle is used to draw in
	RECT* pRect = &paintDC->m_ps.rcPaint;
	FP error;
	FP errorPerc;
	int  x, y, xstep, xstephelp;
	char message[10];

//ofstream oFile;
//oFile.open("C:\\My Documents\\WL\\bnndata\\error.txt");

//sprintf(message, "%d %d %d %d", pRect->right, pRect->left, pRect->top, pRect->bottom);
//this->MessageBox(message);

	if (ErrorList.GetCount() > pRect->right)
	{
		xstep = (int) ((ErrorList.GetCount() - 200)/(pRect->right - 200));
		xstep++;
		if (xstep != currentXStep)
		{
			currentXStep = xstep;
			xStepChanged = TRUE;
		}
		else
		{
			xStepChanged = FALSE;
		}
//		paintDC->MoveTo((pRect->right - 200),pRect->top);
//		paintDC->LineTo((pRect->right - 200),pRect->bottom);
	}
	else
	{
		xstep = 1;
	}
	xstephelp = xstep;
	x = 1;
	if ((maxErrorChanged == true) || (xStepChanged == TRUE))
	{
		POSITION pos = ErrorList.GetHeadPosition();
		this->RedrawWindow(NULL,NULL,
			RDW_ERASE+RDW_INVALIDATE+RDW_ERASENOW);
		paintDC->MoveTo(0, pRect->top);
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			error = ErrorList.GetNext(pos);
			xstephelp--;
			if (xstephelp == 0)
			{
				errorPerc = error / maxError;
				y = (int) (pRect->bottom * errorPerc);
				y = pRect->bottom - y;
//oFile << error << ' ';
				paintDC->LineTo(x,y);
				paintDC->MoveTo(x,y);
//				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
//					((pRect->right - 200)-x)))
				if ((xstep > 1) && (x >= (pRect->right - 200)))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;*/
/*		if (xstep > 1)
		{
sprintf(message, "%d %d %d %d", xdraw, y, xstep, ErrorList.GetCount());
this->MessageBox(message);
		}*/
/*			}
		}
	}
	else
	{	
		error = ErrorList.GetTail();
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			xstephelp--;
			if (xstephelp == 0)
			{
				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
					((pRect->right - 200)-x)))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;
			}
		}
		errorPerc = error / maxError;
		y = (int) (pRect->bottom * errorPerc);
		y = pRect->bottom - y;
//oFile << error << ' ';
		paintDC->LineTo(x,y);
		paintDC->MoveTo(x,y);
//sprintf(message, "%d %d %d %d", x, y, pRect->bottom, ErrorList.GetCount());
//this->MessageBox(message);

	}
//oFile.close();
*/
/*

	// loop through the horizontal paint rectangle
	for(int x =pRect->left; x<pRect->right ;x++)
		// loop through the vertical paint rectangle
//		for(int y =pRect->top; y<pRect->bottom;y++)
			// set each pixel to a different color
	{
//			paintDC.SetPixel(x,x*x,0);
		int temp = x - 100;
		if (temp*temp < pRect->bottom){
			paintDC.LineTo(x, temp*temp);
			paintDC.MoveTo(x, temp* temp);}}*/
//			_itoa(x, buffer,10);
//	paintDC.TextOut(0,x*x,buffer);


/*	ofstream oFile;

	oFile.open("C:\\My Documents\\WL\\bnndata\\error.txt");
	POSITION pos = ErrorList.GetHeadPosition();
	for (int i=1;i<= ErrorList.GetCount();i++)
	{
		oFile << ErrorList.GetNext(pos) << ' ';
	}
	oFile.close();*/
//}



void ErrorPlot::AddToList(FP error)
{
	ErrorList.AddTail(error);	
}


FP ErrorPlot::GetMaxError()
{
	return maxError;
}


void ErrorPlot::SetMaxError(FP max_error)
{
	maxError = max_error;
}


void ErrorPlot::Drawit()
{
	OnPaint();
}

bool ErrorPlot::GetMaxErrorChanged()
{
	return maxErrorChanged;
}

void ErrorPlot::SetMaxErrorChanged(bool bool_val)
{
	maxErrorChanged = bool_val;
}

void ErrorPlot::SetPaintDC(ErrorPlot *ep)
{
	paintDC = new CPaintDC(ep);
}

void ErrorPlot::Reset()
{
	maxError = 0.0;
	maxErrorChanged = FALSE;
	xStepChanged = FALSE;
	currentXStep = 1;
	finished = FALSE;
	ErrorList.RemoveAll();
}





/*
void ErrorPlot::SetNonSummaryArea(int nonSummaryArea)
{
	this->nonSummaryArea = nonSummaryArea;
}

void ErrorPlot::SetBottomMargin(int bottomMargin)
{
	this->bottomMargin = bottomMargin;
}*/
/*
void ErrorPlot::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MessageBox("clocked");
	draw();
	CDialog::OnLButtonDown(nFlags, point);
}


void ErrorPlot::draw()
{
	RECT* pRect = &paintDC->m_ps.rcPaint;
	FP error;
	FP errorPerc;
	int  x, y, xstep, xstephelp, noXSteps;

	if (ErrorList.GetCount() > pRect->right)
	{
		xstep = (int) (ceil((ErrorList.GetCount() - nonSummaryArea)/
			(pRect->right - nonSummaryArea)));
        noXSteps = (int) (ceil((ErrorList.GetCount() - nonSummaryArea) / xstep));//-
	//		(pRect->right - nonSummaryArea));
	    if (xstep != currentXStep)
		{
			currentXStep = xstep;
			xStepChanged = TRUE;
		}
		else
		{
			xStepChanged = FALSE;
		}
	}
	else
	{
		xstep = 1;
	}
	xstephelp = xstep;
	x = 1;
//	if ((maxErrorChanged == true) || (xStepChanged == TRUE))
//	{
		MessageBox("if");
		POSITION pos = ErrorList.GetHeadPosition();
		this->RedrawWindow(NULL,NULL,
			RDW_ERASE+RDW_INVALIDATE+RDW_ERASENOW);
		paintDC->MoveTo((pRect->right - nonSummaryArea),pRect->top);
		paintDC->LineTo((pRect->right - nonSummaryArea),pRect->bottom);
		paintDC->MoveTo(0, pRect->top);
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			error = ErrorList.GetNext(pos);
			xstephelp--;
			if (xstephelp == 0)
			{
				errorPerc = error / maxError;
				y = (int) ((pRect->bottom - bottomMargin) * errorPerc);
				y = (pRect->bottom - bottomMargin) - y;
				paintDC->LineTo(x,y);
				paintDC->MoveTo(x,y);
//				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
//					((pRect->right - 200)-x)))
//				if ((xstep > 1) && (x >= (pRect->right - 200)))
				if ((xstep > 1) && (x >= noXSteps))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;
			}
		}*/
/*	}
	else
	{	
		MessageBox("else");
		error = ErrorList.GetTail();
		for (int error_number=1;error_number<=ErrorList.GetCount();error_number++)
		{
			xstephelp--;
			if (xstephelp == 0)
			{
//				if ((xstep > 1) && (((ErrorList.GetCount() - 200)-error_number) <= 
//					((pRect->right - 200)-x)))
				if ((xstep > 1) && (x >= noXSteps))
				{
					xstep = 1;
				}
				xstephelp = xstep;
				x++;
			}
		}
		errorPerc = error / maxError;
		y = (int) ((pRect->bottom - bottomMargin) * errorPerc);
		y = (pRect->bottom - bottomMargin) - y;
		paintDC->LineTo(x,y);
		paintDC->MoveTo(x,y);
	}*/
//}

void ErrorPlot::OnButton1() 
{
	// TODO: Add your control notification handler code here
	MessageBox("clicked");
}

void ErrorPlot::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
		MessageBox("Timer 1");
	CDialog::OnTimer(nIDEvent);
}
