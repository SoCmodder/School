// Prog3Dlg.h : header file
//

#if !defined(AFX_PROG3DLG_H__88B4D66D_1217_4B5C_9E0F_D078F12F6AEC__INCLUDED_)
#define AFX_PROG3DLG_H__88B4D66D_1217_4B5C_9E0F_D078F12F6AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	CListBox	m_listbox;
	CString	m_msg;
	int		m_input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONinsert();
	afx_msg void OnBUTTONfind();
	afx_msg void OnBUTTONremove();
	afx_msg void OnBUTTONempty();
	afx_msg void OnBUTTONfull();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG3DLG_H__88B4D66D_1217_4B5C_9E0F_D078F12F6AEC__INCLUDED_)
