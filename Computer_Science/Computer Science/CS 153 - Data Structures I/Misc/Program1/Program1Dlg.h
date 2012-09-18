// Program1Dlg.h : header file
//

#if !defined(AFX_PROGRAM1DLG_H__CD445F0C_3F00_4280_A712_2A41B061CF4D__INCLUDED_)
#define AFX_PROGRAM1DLG_H__CD445F0C_3F00_4280_A712_2A41B061CF4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProgram1Dlg dialog

class CProgram1Dlg : public CDialog
{
// Construction
public:
	CProgram1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProgram1Dlg)
	enum { IDD = IDD_PROGRAM1_DIALOG };
	CString	m_input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgram1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProgram1Dlg)
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

#endif // !defined(AFX_PROGRAM1DLG_H__CD445F0C_3F00_4280_A712_2A41B061CF4D__INCLUDED_)
