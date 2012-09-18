// HW3Dlg.h : header file
//

#if !defined(AFX_HW3DLG_H__98E2C4B8_1430_11D6_BDCF_00010227F343__INCLUDED_)
#define AFX_HW3DLG_H__98E2C4B8_1430_11D6_BDCF_00010227F343__INCLUDED_

#include "ListBox.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHW3Dlg dialog

class CHW3Dlg : public CDialog
{
// Construction
public:
	CHW3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHW3Dlg)
	enum { IDD = IDD_HW3_DIALOG };
	CListBox	m_ListBox;
	CString	m_messages;
	CString	m_Input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHW3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONFind();
	afx_msg void OnBUTTONInsert();
	afx_msg void OnBUTTONRemove();
	afx_msg void OnBUTTONEmpty();
	afx_msg void OnBUTTONFull();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ListBox ListBox;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW3DLG_H__98E2C4B8_1430_11D6_BDCF_00010227F343__INCLUDED_)
