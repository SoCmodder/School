// Lab_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CLab_1App:
// See Lab_1.cpp for the implementation of this class
//

class CLab_1App : public CWinApp
{
public:
	CLab_1App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLab_1App theApp;