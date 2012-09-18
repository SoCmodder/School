// lab8.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "lab8.h"
#include "lab8Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab8App

BEGIN_MESSAGE_MAP(Clab8App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Clab8App construction

Clab8App::Clab8App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Clab8App object

Clab8App theApp;


// Clab8App initialization

BOOL Clab8App::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	Clab8Dlg dlg;
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
