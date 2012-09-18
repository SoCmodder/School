// Lab_3Dlg.cpp : implementation file
//
/*
file: Lab_3Dlg.cpp
author: Brent Powers
Date: 2-3-05
Program Description: This program will allow the user to input a employee name, wage, and overtime hours
				, then these variables will be entered into a dynamc array. Once in this array the user
				can delete the entry from the array, search the array to find a particular name, calculate
				the total cost of all overtime hours in the array, and completely clear the array. This
				program must allow for an unlimited amount of entries to be entered. This has to be done with 
				a dynamic array.


*/

#include "stdafx.h"
#include "Lab_3.h"
#include "Lab_3Dlg.h"
#include "payroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

payroll my_payroll;
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


// CLab_3Dlg dialog



CLab_3Dlg::CLab_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLab_3Dlg::IDD, pParent)
	, input_name(_T(""))
	, input_hours(0)
	, input_wage(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLab_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_name);
	DDV_MaxChars(pDX, input_name, 40);
	DDX_Text(pDX, IDC_EDIT2, input_hours);
	DDX_Text(pDX, IDC_EDIT3, input_wage);
	DDX_Control(pDX, IDC_LIST1, thelistbox);
}

BEGIN_MESSAGE_MAP(CLab_3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT3, OnEnChangeEdit3)
END_MESSAGE_MAP()


// CLab_3Dlg message handlers

BOOL CLab_3Dlg::OnInitDialog()
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

void CLab_3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLab_3Dlg::OnPaint() 
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
HCURSOR CLab_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLab_3Dlg::OnBnClickedButton1()//the add button
{
	if(UpdateData(TRUE))//new data
	{
		if(input_wage>=0)//so there is no negative numbers
		{
			my_payroll.add(input_name,input_hours,input_wage);//adds the stuff
			my_payroll.Display(thelistbox);//displays it
			input_name="";//resets the edit box
			input_wage=0;
			input_hours=0;
		}else 
		{
			MessageBox("Please enter a non-negative wage.","Error",MB_OK); //if negative wage is entered
		}
			UpdateData(FALSE);
	}
}

void CLab_3Dlg::OnBnClickedButton2()//delete button
{
	if(UpdateData(TRUE))
	{
		my_payroll.delete_(input_name);//runs the delete function
		my_payroll.Display(thelistbox);//redisplays the array
		input_name="";//resets the input boxes
		input_wage=0;
		input_hours=0;
		UpdateData(FALSE);
	}
}

void CLab_3Dlg::OnBnClickedButton3()//find button
{
	int i;
	employee pass;//temporary variable to recieve a struct employee
	UpdateData(TRUE);
	i=my_payroll.find_(input_name);//looks for name
	if (i>=0)
	{
		pass=my_payroll.passback(i);//gets that struct if found
		input_name=pass.name;
		input_wage=pass.wage;
		input_hours=pass.overtime;
        }
	if (i==-1)
	{
		MessageBox("Name does not exist in Database","Does Not Exist",MB_OK);//not found
	}
		UpdateData(FALSE);

}

void CLab_3Dlg::OnBnClickedButton4()// clear button
{
	my_payroll.clear();//resets all
	my_payroll.Display(thelistbox);//updates the listbox
}

void CLab_3Dlg::OnBnClickedButton5()// total button
{
	my_payroll.total(); //calc total
}

void CLab_3Dlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
