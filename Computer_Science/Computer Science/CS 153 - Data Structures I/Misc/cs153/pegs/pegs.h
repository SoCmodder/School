// pegs.h : main header file for the PEGS application
//

#if !defined(AFX_PEGS_H__3D5FCD54_A52E_11D4_ADF3_005056000000__INCLUDED_)
#define AFX_PEGS_H__3D5FCD54_A52E_11D4_ADF3_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPegsApp:
// See pegs.cpp for the implementation of this class
//

class CPegsApp : public CWinApp
{
public:
	CPegsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPegsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPegsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEGS_H__3D5FCD54_A52E_11D4_ADF3_005056000000__INCLUDED_)
