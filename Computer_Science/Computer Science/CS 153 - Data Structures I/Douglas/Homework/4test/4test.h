// 4test.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CMy4testApp:
// See 4test.cpp for the implementation of this class
//

class CMy4testApp : public CWinApp
{
public:
	CMy4testApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy4testApp theApp;