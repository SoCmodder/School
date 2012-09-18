// lab6.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "lab6.h"
#include "lab6Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab6App

BEGIN_MESSAGE_MAP(Clab6App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Clab6App construction

Clab6App::Clab6App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Clab6App object

Clab6App theApp;


// Clab6App initialization

BOOL Clab6App::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	Clab6Dlg dlg;
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
