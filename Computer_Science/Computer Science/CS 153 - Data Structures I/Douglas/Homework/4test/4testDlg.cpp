// 4testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "4test.h"
#include "4testDlg.h"
#include "food.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
Pocket Pk1;
int total=0;
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


// CMy4testDlg dialog



CMy4testDlg::CMy4testDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy4testDlg::IDD, pParent)
	, m_foodname(_T(""))
	, m_message(_T(""))
	, m_calories(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy4testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_foodname);
	DDX_Control(pDX, IDC_LIST1, m_listing);
	DDX_Text(pDX, IDC_EDIT3, m_message);
	DDX_Text(pDX, IDC_EDIT2, m_calories);
	DDV_MinMaxInt(pDX, m_calories, 0, INT_MAX);
}

BEGIN_MESSAGE_MAP(CMy4testDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
END_MESSAGE_MAP()


// CMy4testDlg message handlers

BOOL CMy4testDlg::OnInitDialog()
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

void CMy4testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy4testDlg::OnPaint() 
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
HCURSOR CMy4testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//This Button Gets food, adds it to the list and the dynamic array
//PRE: None
//POST: The fields of Calories and Foodname are used to add a food_item to pocket
void CMy4testDlg::OnBnClickedButton2()
{

  CString cals ="0";
  UpdateData(TRUE);
  if(m_calories+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert(m_foodname, m_calories); 
	Pk1.Display(m_listing);
   	m_message="Food Added";
  }
UpdateData(FALSE);
}

//Give Back Food
//PRE: None
//POST: If food exists, it is removed from pocket, if not, an error message is 
//displayed in the message box
void CMy4testDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);

	if (!Pk1.Remove(m_foodname))
		m_message="ERROR: No such food";
	else
	{
		Pk1.Display(m_listing);

	}


	UpdateData(FALSE);
}
//Check Calories
//PRE: None
//POST: Total calories in pocket is displayed
void CMy4testDlg::OnBnClickedButton3()
{
	char temp[20];
	itoa(Pk1.Total_Cal(), temp, 10);
	m_message=temp;
	UpdateData(FALSE);

}
//Most Calories
//PRE: none
//POST: The food with the most calories in poclet is displayed
void CMy4testDlg::OnBnClickedButton4()
{
	m_message = Pk1.Max_Cal();
	UpdateData(FALSE);


}
//Least Calories
//PRE: none
//POST: The food with the least calories in poclet is displayed
void CMy4testDlg::OnBnClickedButton1()
{
	m_message = Pk1.Least_Cal();
	UpdateData(FALSE);

}
//Add Whopper
//PRE: None
//POST: Inserts a Whopper into the pocket 
void CMy4testDlg::OnBnClickedButton6()
{
	  if(1150+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert("Whopper", 1150);
	Pk1.Display(m_listing);
	m_message="Food Added";  
  }
UpdateData(FALSE);	
}
//Add Big Mac
//PRE: None
//POST: Inserts a Big Mac into the pocket
void CMy4testDlg::OnBnClickedButton9()
{
  if(650+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert("Big Mac", 650);
	Pk1.Display(m_listing);
    m_message="Food Added";
  }
UpdateData(FALSE);
}
//Add Pizza
//PRE: None
//POST: Inserts a Pizza into the pocket
void CMy4testDlg::OnBnClickedButton10()
{
  if(425+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert("Pizza", 425);
	Pk1.Display(m_listing);
	m_message="Food Added";
  }
UpdateData(FALSE);}
//Add Burrito
//PRE: None
//POST: Inserts a Burrito into the pocket
void CMy4testDlg::OnBnClickedButton7()
{
  if(370+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert("Burrito", 370);
	Pk1.Display(m_listing);
	m_message="Food Added";  
  }
UpdateData(FALSE);
}
//add tic tac
//PRE: None
//POST: Inserts a tic tac into the pocket
void CMy4testDlg::OnBnClickedButton8()
{
  if(1+Pk1.Total_Cal()>2000)
  {
	  m_message="ERROR: You'll go over 2000 Calories";
  }
  else
  {
	Pk1.Insert("Tic Tac", 1);
	Pk1.Display(m_listing);
	m_message="Food Added";
  }
UpdateData(FALSE);}
