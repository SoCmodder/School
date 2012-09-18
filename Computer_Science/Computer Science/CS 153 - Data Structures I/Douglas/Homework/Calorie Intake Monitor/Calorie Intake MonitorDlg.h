// Calorie Intake MonitorDlg.h : header file
//

#pragma once


// CCalorieIntakeMonitorDlg dialog
class CCalorieIntakeMonitorDlg : public CDialog
{
// Construction
public:
	CCalorieIntakeMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALORIEINTAKEMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
};
