/*
File: lab8Dlg.cpp
Author: Brent Powers
Date: 4-14-05
Description implemetation file for dlg
*/


// lab8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab8.h"
#include "lab8Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Clab8Dlg dialog



Clab8Dlg::Clab8Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab8Dlg::IDD, pParent)
	, input_number(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_number);
	DDX_Control(pDX, IDC_LIST1, output_box);
}

BEGIN_MESSAGE_MAP(Clab8Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// Clab8Dlg message handlers

BOOL Clab8Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Clab8Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
Function: insert
Description: inserts a node in tree and displays the tree
Precondition: valid input in dlg
Postcondition: node is placed in tree
*/
void Clab8Dlg::OnBnClickedButton2()//insert button
{
	if(UpdateData(TRUE))
	{
		thetree.insert(input_number);//insert
		thetree.Display(output_box);//display
		input_number=0;
		UpdateData(FALSE);//reset the box
	}

}
/*
Function: isempty
Description: says weither the BST is empty or not
Precondition: none
Postcondition: Messagebox saying if tree is empty or not
*/
void Clab8Dlg::OnBnClickedButton3()//isempty
{
	bool temp=thetree.isEmpty();//set variable to is empty
	if(temp==TRUE)//if tree is empty
	{
		MessageBox("The Search Tree is currently empty","Empty");
	}
	if(temp==FALSE)//if tree isn't empty
	{
		MessageBox("The Search Tree currently is not empty","Not Empty");
	}
	return;
}
/*
Function: find
Description: find's either or not value is in tree
Precondtion: valid input
Postconditon: Message Box confirming in tree or noe
*/

void Clab8Dlg::OnBnClickedButton1()//find
{
	if(UpdateData(TRUE))
	{
		bool temp=thetree.Find(input_number);//temp for in tree or not
		if(temp==TRUE)//if in tree
		{
			MessageBox("That value is found in the tree","Found");
		}
		if(temp==FALSE)//if not in tree
		{
			MessageBox("That value is not found in the tree","Not Found");
		}
		input_number=0;//reset the box
		UpdateData(FALSE);
	}
	return;
}