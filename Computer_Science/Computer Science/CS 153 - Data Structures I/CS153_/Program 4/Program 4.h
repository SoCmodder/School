// Program 4.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CProgram4App:
// See Program 4.cpp for the implementation of this class
//

class CProgram4App : public CWinApp
{
public:
	CProgram4App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProgram4App theApp;