// Lab_3Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CLab_3Dlg dialog
class CLab_3Dlg : public CDialog
{
// Construction
public:
	CLab_3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB_3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString input_name;
	int input_hours;
	int input_wage;
	afx_msg void OnBnClickedButton1();
	CListBox thelistbox;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit3();
};
