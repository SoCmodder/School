// Lab_3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CLab_3App:
// See Lab_3.cpp for the implementation of this class
//

class CLab_3App : public CWinApp
{
public:
	CLab_3App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLab_3App theApp;