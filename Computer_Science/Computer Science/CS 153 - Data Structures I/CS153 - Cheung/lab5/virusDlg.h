// virusDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CvirusDlg dialog
class CvirusDlg : public CDialog
{
// Construction
public:
	CvirusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VIRUS_DIALOG };

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
	int input_age;
	BOOL input_vacinated;
	afx_msg void OnBnClickedButton1();
	CListBox live_box;
	CListBox dead_box;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString obox;
	afx_msg void OnBnClickedButton4();
	void display(CListBox& lbox);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
