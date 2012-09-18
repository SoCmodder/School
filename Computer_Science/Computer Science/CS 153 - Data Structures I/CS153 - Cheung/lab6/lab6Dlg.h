// lab6Dlg.h : header file
//

#pragma once


// Clab6Dlg dialog

class Clab6Dlg : public CDialog
{
// Construction
public:
	
	Clab6Dlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_LAB6_DIALOG };

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
	CString ifix;
	CString pfix;
	afx_msg void OnBnClickedButton1();
	void convert(CString readin, CString& readout);
};
