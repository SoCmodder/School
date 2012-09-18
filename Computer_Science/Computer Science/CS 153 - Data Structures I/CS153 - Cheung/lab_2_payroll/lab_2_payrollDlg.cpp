// lab_2_payrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab_2_payroll.h"
#include "lab_2_payrollDlg.h"
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


// Clab_2_payrollDlg dialog



Clab_2_payrollDlg::Clab_2_payrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab_2_payrollDlg::IDD, pParent)
	, input_name(_T(""))
	, input_overtime(0)
	, input_wage(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab_2_payrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_name);
	DDX_Text(pDX, IDC_EDIT2, input_overtime);
	DDX_Text(pDX, IDC_EDIT3, input_wage);
	DDX_Control(pDX, IDC_LIST1, thelistbox);
}

BEGIN_MESSAGE_MAP(Clab_2_payrollDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
END_MESSAGE_MAP()


// Clab_2_payrollDlg message handlers

BOOL Clab_2_payrollDlg::OnInitDialog()
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

void Clab_2_payrollDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab_2_payrollDlg::OnPaint() 
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
HCURSOR Clab_2_payrollDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Clab_2_payrollDlg::OnBnClickedButton1()//add button
{
	if(UpdateData(TRUE))//new data
	{
		if(input_wage>=0)//so there is no negative numbers
		{
			my_payroll.add(input_name,input_overtime,input_wage);//adds the stuff
			my_payroll.Display(thelistbox);//displays it
			input_name="";//resets the edit box
			input_wage=0;
			input_overtime=0;
		}else 
		{
			MessageBox("Please enter a non-negative wage.","Error",MB_OK);
		}
			UpdateData(FALSE);
	}}




void Clab_2_payrollDlg::OnBnClickedButton3()//find button
{
	int i;
	employee pass;
	UpdateData(TRUE);
	i=my_payroll.find_(input_name);
	if ((i>=0)&&(i<=14))
	{
		pass=my_payroll.passback(i);
		input_name=pass.name;
		input_wage=pass.wage;
		input_overtime=pass.overtime;
        }
	if (i==-1)
	{
		MessageBox("Name does not exist in Database","Does Not Exist",MB_OK);
	}
		UpdateData(FALSE);
}


void Clab_2_payrollDlg::OnBnClickedButton2()//delete button
{
	if(UpdateData(TRUE))
	{
		my_payroll.delete_(input_name);
		my_payroll.Display(thelistbox);
		input_name="";
		input_wage=0;
		input_overtime=0;
		UpdateData(FALSE);
	}
}

void Clab_2_payrollDlg::OnBnClickedButton5()//is full button
{
	if (my_payroll.isfull()==TRUE)
	{
		MessageBox("The database is currently full.","Full",MB_OK);
	}
	else 
	{
		MessageBox("The database is not currently full.","Empty",MB_OK);
	}
}



void Clab_2_payrollDlg::OnBnClickedButton4()//clear button
{
	my_payroll.clear();
	my_payroll.Display(thelistbox);
}

void Clab_2_payrollDlg::OnBnClickedButton6()//total button
{
	my_payroll.total();
	
}
