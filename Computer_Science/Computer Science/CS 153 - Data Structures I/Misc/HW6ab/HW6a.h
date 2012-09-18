// HW6a.h : main header file for the HW6A application
//

#if !defined(AFX_HW6A_H__0E4AB3FA_264E_11D6_BD85_00010227F346__INCLUDED_)
#define AFX_HW6A_H__0E4AB3FA_264E_11D6_BD85_00010227F346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHW6aApp:
// See HW6a.cpp for the implementation of this class
//

class CHW6aApp : public CWinApp
{
public:
	CHW6aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW6aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHW6aApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW6A_H__0E4AB3FA_264E_11D6_BD85_00010227F346__INCLUDED_)
