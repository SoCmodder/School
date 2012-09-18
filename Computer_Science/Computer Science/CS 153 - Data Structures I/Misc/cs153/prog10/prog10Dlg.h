// prog10Dlg.h : header file
//

#if !defined(AFX_PROG10DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_)
#define AFX_PROG10DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_

#include "ctree.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg10Dlg dialog

class CProg10Dlg : public CDialog
{
// Construction
public:
	CProg10Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg10Dlg)
	enum { IDD = IDD_PROG10_DIALOG };
	CListBox	m_list;
	int		m_input;
	int		m_listSelect;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg10Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg10Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonBalance();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonPurge();
	afx_msg void OnRadioInorder();
	afx_msg void OnRadioPostorder();
	afx_msg void OnRadioPreorder();
	afx_msg void OnSelchangeListDisplay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_displayOrder;
	void DisplayTree(void);
	CTree m_tree;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG10DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_)
