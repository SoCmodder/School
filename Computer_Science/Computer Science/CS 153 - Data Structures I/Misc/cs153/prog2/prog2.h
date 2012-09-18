// prog2.h : main header file for the PROG2 application
//

#if !defined(AFX_PROG2_H__0F2176BA_7AD4_11D4_A257_006097D2E7B9__INCLUDED_)
#define AFX_PROG2_H__0F2176BA_7AD4_11D4_A257_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg2App:
// See prog2.cpp for the implementation of this class
//

class CProg2App : public CWinApp
{
public:
	CProg2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG2_H__0F2176BA_7AD4_11D4_A257_006097D2E7B9__INCLUDED_)
