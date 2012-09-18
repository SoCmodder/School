// prog11Dlg.h : header file
//

#if !defined(AFX_PROG11DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_)
#define AFX_PROG11DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_

#include "CBST.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg11Dlg dialog

class CProg11Dlg : public CDialog
{
// Construction
public:
	CProg11Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg11Dlg)
	enum { IDD = IDD_PROG11_DIALOG };
	CListBox	m_list;
	int		m_listSelect;
	CString	m_input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg11Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg11Dlg)
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
	enum {INORDER,PREORDER,POSTORDER} m_displayOrder;
	void DisplayTree(void);
	CBST m_tree;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG11DLG_H__66643A46_AEDD_11D4_ADFC_005056000000__INCLUDED_)
