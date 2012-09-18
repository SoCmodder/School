// program1Dlg.h : header file
//

#pragma once


// Cprogram1Dlg dialog
class Cprogram1Dlg : public CDialog
{
// Construction
public:
	Cprogram1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROGRAM1_DIALOG };

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
	int operand1;
	int operand2;
	int sum;
	afx_msg void Go_AddButton();
};
