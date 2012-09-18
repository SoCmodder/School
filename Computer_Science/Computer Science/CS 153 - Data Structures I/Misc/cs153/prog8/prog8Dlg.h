// prog8Dlg.h : header file
//

#if !defined(AFX_PROG8DLG_H__0FC5C376_9CB5_11D4_ADE5_005056000000__INCLUDED_)
#define AFX_PROG8DLG_H__0FC5C376_9CB5_11D4_ADE5_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg8Dlg dialog

class CProg8Dlg : public CDialog
{
// Construction
public:
	CProg8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg8Dlg)
	enum { IDD = IDD_PROG8_DIALOG };
	CString	m_alg;
	double	m_answer;
	CString	m_rpn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg8Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg8Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSolveAlg();
	afx_msg void OnButtonSolveRPN();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG8DLG_H__0FC5C376_9CB5_11D4_ADE5_005056000000__INCLUDED_)
