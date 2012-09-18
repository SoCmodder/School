// postfixDlg.h : header file
// This program converts an infix expression that the user enters into a
// postfix expression calculated by the program.

#pragma once

#include "stack.h"

// CpostfixDlg dialog
class CpostfixDlg : public CDialog
{
// Construction
public:
	CpostfixDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POSTFIX_DIALOG };

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
  CString infexpr;
  CString postexpr;

  // This converts the expression given from infix to postfix.
  // Pre: An expression must be entered to convert, and in the correct format.
  // Post: The expression given is converted to postfix using a stack to store
  //       operators.
  afx_msg void OnBnClickedCONVERT();

  // Checks to see if the passed character is a single digit integer.
  // Pre: None.
  // Post: Returns true if the passed character is a single digit integer,
  //       otherwise, it returns false.
  bool CheckInt( const char test );

  
  // Checks to see if the passed character is an operator.
  // Pre: None.
  // Post: Returns true if the passed character is an operator,
  //       otherwise, it returns false.
  bool CheckForOper( const char test );

  // Checks to see if the end element is an operator.
  // Pre: None.
  // Post: Returns true if it ends in an integer and false if it ends in an
  //       operator.
  bool CheckForEndOper();
};
