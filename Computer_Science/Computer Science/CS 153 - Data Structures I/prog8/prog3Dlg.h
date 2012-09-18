//Filename: prog3Dlg.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 


#include"Stack.h"
#include"bag.h"
#if !defined(AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_)
#define AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg dialog


class CProg3Dlg : public CDialog
{
// Construction
public:
	void Display();
	CProg3Dlg(CWnd* pParent = NULL);	// standard constructor
	bool Error_ValidExpression();

	bool Error_Balanced();
// Dialog Data
	//{{AFX_DATA(CProg3Dlg)
	enum { IDD = IDD_PROG3_DIALOG };
	CString	m_conv_input;
	CString	m_eval_input;
	CString	m_result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONConvert();
	afx_msg void OnBUTTONEvaluate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CBag my_bag;
    Stack my_stack;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_)
