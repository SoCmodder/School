// Lab_3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Lab_3.h"
#include "Lab_3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab_3App

BEGIN_MESSAGE_MAP(CLab_3App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLab_3App construction

CLab_3App::CLab_3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLab_3App object

CLab_3App theApp;


// CLab_3App initialization

BOOL CLab_3App::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CLab_3Dlg dlg;
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
