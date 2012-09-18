// HW3.h : main header file for the HW3 application
//

#if !defined(AFX_HW3_H__98E2C4B6_1430_11D6_BDCF_00010227F343__INCLUDED_)
#define AFX_HW3_H__98E2C4B6_1430_11D6_BDCF_00010227F343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHW3App:
// See HW3.cpp for the implementation of this class
//

class CHW3App : public CWinApp
{
public:
	CHW3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHW3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW3_H__98E2C4B6_1430_11D6_BDCF_00010227F343__INCLUDED_)
