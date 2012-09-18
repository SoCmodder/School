// HW9Dlg.h : header file
//

#if !defined(AFX_HW9DLG_H__53A20945_3AB8_11D6_BD88_00010227F33C__INCLUDED_)
#define AFX_HW9DLG_H__53A20945_3AB8_11D6_BD88_00010227F33C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHW9Dlg dialog

class CHW9Dlg : public CDialog
{
// Construction
public:
	CHW9Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHW9Dlg)
	enum { IDD = IDD_HW9_DIALOG };
	CString	m_InFix;
	CString	m_PostFix;
	int		m_Result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW9Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHW9Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvertInFix();
	afx_msg void OnClear();
	afx_msg void OnEvaluatePostFix();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW9DLG_H__53A20945_3AB8_11D6_BD88_00010227F33C__INCLUDED_)
