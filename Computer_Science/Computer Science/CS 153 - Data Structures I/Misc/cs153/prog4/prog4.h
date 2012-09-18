// prog4.h : main header file for the PROG4 application
//

#if !defined(AFX_PROG4_H__1EC94D4A_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
#define AFX_PROG4_H__1EC94D4A_85BF_11D4_A46D_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg4App:
// See prog4.cpp for the implementation of this class
//

class CProg4App : public CWinApp
{
public:
	CProg4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG4_H__1EC94D4A_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
