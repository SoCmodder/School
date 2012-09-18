// hw2Dlg.h : header file
//

#pragma once


// Chw2Dlg dialog
class Chw2Dlg : public CDialog
{
// Construction
public:
	Chw2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HW2_DIALOG };

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
	CString datestring;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
