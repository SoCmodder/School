// lab_2_payroll.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "lab_2_payroll.h"
#include "lab_2_payrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab_2_payrollApp

BEGIN_MESSAGE_MAP(Clab_2_payrollApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Clab_2_payrollApp construction

Clab_2_payrollApp::Clab_2_payrollApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Clab_2_payrollApp object

Clab_2_payrollApp theApp;


// Clab_2_payrollApp initialization

BOOL Clab_2_payrollApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	Clab_2_payrollDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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
