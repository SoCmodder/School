// program2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Cprogram2App:
// See program2.cpp for the implementation of this class
//

class Cprogram2App : public CWinApp
{
public:
	Cprogram2App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cprogram2App theApp;