// prog2Dlg.h : header file
//

#if !defined(AFX_PROG2DLG_H__0F2176BC_7AD4_11D4_A257_006097D2E7B9__INCLUDED_)
#define AFX_PROG2DLG_H__0F2176BC_7AD4_11D4_A257_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg2Dlg dialog

class CProg2Dlg : public CDialog
{
// Construction
public:
	CProg2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg2Dlg)
	enum { IDD = IDD_PROG2_DIALOG };
	int		m_streetInt;
	CString	m_streetStr;
	int		m_zip;
	CString	m_state;
	CString	m_city;
	CString	m_address;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCat();
	afx_msg void OnButtonParse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG2DLG_H__0F2176BC_7AD4_11D4_A257_006097D2E7B9__INCLUDED_)
