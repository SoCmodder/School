//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.
// Program 4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Program 4.h"
#include "Program 4Dlg.h"
#include ".\program 4dlg.h"

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


// CProgram4Dlg dialog



CProgram4Dlg::CProgram4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgram4Dlg::IDD, pParent)
   , make(_T(""))
   , model(_T(""))
   , year(0)
   , NumAutos(0)
   , status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgram4Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT1, make);
   DDX_Control(pDX, IDC_LIST1, AutoList);
   DDX_Text(pDX, IDC_EDIT3, model);
   DDX_Text(pDX, IDC_EDIT2, year);
   DDX_Text(pDX, IDC_EDIT5, NumAutos);
   DDX_Text(pDX, IDC_EDIT4, status);
}

BEGIN_MESSAGE_MAP(CProgram4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_BUTTON1, AddToHead)
   ON_BN_CLICKED(IDC_BUTTON2, AddToTail)
   ON_BN_CLICKED(IDC_BUTTON4, FindAutomobile)
   ON_BN_CLICKED(IDC_BUTTON3, Remove)
   ON_BN_CLICKED(IDC_BUTTON6, ClearList)
   ON_BN_CLICKED(IDC_BUTTON5, ShowAllCars)
END_MESSAGE_MAP()


// CProgram4Dlg message handlers

BOOL CProgram4Dlg::OnInitDialog()
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

void CProgram4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProgram4Dlg::OnPaint() 
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
HCURSOR CProgram4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Preconditions: None
//PostConditions: Will appropriately Update the Listbox 
void CProgram4Dlg::UpdateListBox()
{
   AutoList.ResetContent();  // clears the contents of the list box
   Yard.IterReset(); //Resets Iter
   for(int i=0; i<Yard.GetNumOfNodes(); i++)
   {
      Automobile tmp(Yard.GetNextData());
      AutoList.AddString(tmp.GetAuto());
   }
   NumAutos = Yard.GetNumOfNodes();
}

//Preconditions: None
//PostConditions: Will check to make sure all the data is legal 
bool CProgram4Dlg::ErrorCheck()
{
   bool tmp = false;
   if(model=="")
   {
      status="Please enter a model";
   }
   else if(make=="")
   {
      status="Please enter a make";
   }
   else if(year<1900)
   {
	   status = "Sorry we don't support vehicles before 1900";
   }
   else if(year>=2008)
   {
      status="Sorry you can't make automboiles that don't exist yet!";
   }
   else
   {
      tmp = true;
   }
   return tmp;
}

//Preconditions: None
//PostConditions: Will add a node to head
void CProgram4Dlg::AddToHead()
{
  if(UpdateData(TRUE))
   {
      if(ErrorCheck())
      {
         Automobile tmp(make,model,year);
         Yard.AddToHead(tmp);
         status="Your automobile has been added";
         UpdateListBox();
      }
      UpdateData(FALSE);
   }
}

//Preconditions: None
//PostConditions: Will add a node to tail
void CProgram4Dlg::AddToTail()
{
   if(UpdateData(TRUE))
   {
      if(ErrorCheck())
      {
         Automobile tmp(make,model,year);
         Yard.AddToTail(tmp);
         status="Your automobile has been added";
         UpdateListBox();
      }
      UpdateData(FALSE);
   }
}

//Preconditions: None
//PostConditions: Will search the array for a specific automobile
void CProgram4Dlg::FindAutomobile()
{
   UpdateData(TRUE);
   AutoList.ResetContent();
   Automobile tmp(make, model, year);
   if(Yard.Search(tmp)!= 0)
   {
      for(int i = 0; i < Yard.Search(tmp); i++)
      {
         AutoList.AddString(tmp.GetAuto());
      }
      status="Here are the results of your search";
   }
   else
   {
      status="Sorry nothing fits that description";
   }
   UpdateData(FALSE);
}

//Preconditions: None
//PostConditions: Will remove a specific automobile
void CProgram4Dlg::Remove()
{
if(UpdateData(TRUE))
   {
      if(ErrorCheck())
      {
         Automobile tmp(make, model, year);
         if(Yard.Remove(tmp))
         {
            status="Your automobile has been removed";
         }
         else
         {
            status="Sorry that Automobile doesn't exist";
         }
      }
   }
   UpdateListBox();
   UpdateData(FALSE);
}

//Preconditions: None
//PostConditions: Will empty the linked list
void CProgram4Dlg::ClearList()
{
   Yard.Clear();
   NumAutos = 0;
   UpdateListBox();
   status= "The list has been cleared";
   UpdateData(FALSE);
}

//Preconditions: None
//PostConditions: Will show all the cars in the entire linked
// list
void CProgram4Dlg::ShowAllCars()
{
   UpdateListBox();
   UpdateData(TRUE);
   status = "Here is the list of all of the cars";
   UpdateData(FALSE);

}
