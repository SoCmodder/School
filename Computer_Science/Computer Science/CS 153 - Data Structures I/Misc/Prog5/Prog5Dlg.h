// Prog5Dlg.h : header file
//

#if !defined(AFX_PROG5DLG_H__34FD3470_169F_465C_AA17_CE4479F932F2__INCLUDED_)
#define AFX_PROG5DLG_H__34FD3470_169F_465C_AA17_CE4479F932F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg5Dlg dialog

class CProg5Dlg : public CDialog
{
// Construction
public:
	CProg5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg5Dlg)
	enum { IDD = IDD_PROG5_DIALOG };
	CListBox	m_Listbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg5Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONgo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG5DLG_H__34FD3470_169F_465C_AA17_CE4479F932F2__INCLUDED_)