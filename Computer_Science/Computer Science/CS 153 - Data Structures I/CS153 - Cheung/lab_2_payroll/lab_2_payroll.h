// lab_2_payroll.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Clab_2_payrollApp:
// See lab_2_payroll.cpp for the implementation of this class
//

class Clab_2_payrollApp : public CWinApp
{
public:
	Clab_2_payrollApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Clab_2_payrollApp theApp;