// Calorie Intake Monitor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CCalorieIntakeMonitorApp:
// See Calorie Intake Monitor.cpp for the implementation of this class
//

class CCalorieIntakeMonitorApp : public CWinApp
{
public:
	CCalorieIntakeMonitorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCalorieIntakeMonitorApp theApp;