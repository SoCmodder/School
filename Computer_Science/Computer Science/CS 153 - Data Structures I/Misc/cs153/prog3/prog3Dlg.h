// prog3Dlg.h : header file
//

#if !defined(AFX_PROG3DLG_H__23568DDC_835F_11D4_A469_006097D2E7B9__INCLUDED_)
#define AFX_PROG3DLG_H__23568DDC_835F_11D4_A469_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vect.h"

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg dialog

class CProg3Dlg : public CDialog
{
// Construction
public:
	CProg3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg3Dlg)
	enum { IDD = IDD_PROG3_DIALOG };
	CString	m_input1;
	CString	m_input2;
	CString	m_answer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	int Vertify(const CVect& a, const CVect& b, CWnd* w) const;

	// Generated message map functions
	//{{AFX_MSG(CProg3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPlus();
	afx_msg void OnButtonMinus();
	afx_msg void OnButtonProduct();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG3DLG_H__23568DDC_835F_11D4_A469_006097D2E7B9__INCLUDED_)
