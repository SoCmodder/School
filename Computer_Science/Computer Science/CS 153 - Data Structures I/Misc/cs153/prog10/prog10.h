// prog10.h : main header file for the PROG10 application
//

#if !defined(AFX_PROG10_H__66643A44_AEDD_11D4_ADFC_005056000000__INCLUDED_)
#define AFX_PROG10_H__66643A44_AEDD_11D4_ADFC_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg10App:
// See prog10.cpp for the implementation of this class
//

class CProg10App : public CWinApp
{
public:
	CProg10App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg10App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg10App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG10_H__66643A44_AEDD_11D4_ADFC_005056000000__INCLUDED_)
