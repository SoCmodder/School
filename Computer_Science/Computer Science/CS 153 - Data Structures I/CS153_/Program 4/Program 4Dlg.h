//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.
// Program 4Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "LinkedList.h"
#include "Automobile.h"


// CProgram4Dlg dialog
class CProgram4Dlg : public CDialog
{
// Construction
public:
	CProgram4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROGRAM4_DIALOG };

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
   LinkedList<Automobile> Yard; //instance of a LinkedList
   void UpdateListBox();
   bool ErrorCheck();
   CString make;
   CListBox AutoList;
   CString model;
   int year;
   int NumAutos;
   CString status;
   afx_msg void AddToHead();
   afx_msg void AddToTail();
   afx_msg void FindAutomobile();
   afx_msg void Remove();
   afx_msg void ClearList();
   afx_msg void ShowAllCars();
};
