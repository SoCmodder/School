//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 2 Description: This program will implement
// a bag class and will offer some basic forms of data 
// manipulation of the bag.
// program2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "program2.h"
#include "program2Dlg.h"
#include ".\program2dlg.h"

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
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV support

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


// Cprogram2Dlg dialog



Cprogram2Dlg::Cprogram2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cprogram2Dlg::IDD, pParent)
   , weight(0)
   , description(_T(""))
   , TotalWeight(0)
   , TotalSize(0)
   , status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cprogram2Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT1, weight);
   DDX_Text(pDX, IDC_EDIT2, description);
   DDX_Control(pDX, IDC_LIST1, trashBagListBox);
   DDX_Text(pDX, IDC_EDIT3, TotalWeight);
   DDX_Text(pDX, IDC_EDIT4, TotalSize);
   DDX_Text(pDX, IDC_EDIT6, status);
}

BEGIN_MESSAGE_MAP(Cprogram2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_BUTTON1, Add_Button)
   ON_BN_CLICKED(IDC_BUTTON2, Delete_Button)
   ON_BN_CLICKED(IDC_BUTTON3, Empty_Button)

   ON_BN_CLICKED(IDC_BUTTON4, Delete_All)
END_MESSAGE_MAP()


// Cprogram2Dlg message handlers

BOOL Cprogram2Dlg::OnInitDialog()
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

	// Set the icon for this dialog. The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cprogram2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cprogram2Dlg::OnPaint() 
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

// The system calls this function to obtain the cursor to 
// display while the user drags the minimized window.
HCURSOR Cprogram2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//This function implements the updating of the list box in the GUI. 
// It will change what shows up in the list box and changes acurately. 
void Cprogram2Dlg::UpdateListBox(void)
{
   trashBagListBox.ResetContent();  // clears the contents of the list box
   for(int i=0; i<TrashBag.GetSize(); i++)
   trashBagListBox.AddString(TrashBag.GetItem(i));
   TotalWeight = TrashBag.GetWeight();
   TotalSize = TrashBag.GetSize();
}

//This function is the event handler for Add button on the GUI. It takes
// in the data entered in the GUI control boxes, and then adds it to the
// bag.
void Cprogram2Dlg::Add_Button()
{
   UpdateData(TRUE);
   if((TrashBag.GetWeight()+weight)>TrashBag.GetMaxWeight())
      MessageBox("Sorry this is too heavy");
   else if(TrashBag.GetSize()==TrashBag.GetMaxSize())
   {
      TrashBag.ArrayLarger();
      TrashBag.add(weight, description);
      UpdateListBox();
      status = "The bag can now hold 5 more items";
   }
   else if(weight<=0)
      status = "Weight Must Be Greater Than Zero";
   else
   {
      TrashBag.add(weight, description);
      UpdateListBox();
      status = "The item has been added to the bag";
   }
   UpdateData(FALSE);      

}

//This function is the event handler for the 
//Delete button on the GUI. It takes in the description from 
// the GUI and then calls the erase_one function 
// to delete the desired item.
void Cprogram2Dlg::Delete_Button()
{
   UpdateData(TRUE);
   if(!TrashBag.erase_one(description, weight))
   status = "The item does not exist";
   else
   {
     UpdateListBox();
     status = "The item has been removed";
   }
   UpdateData(FALSE);

}


//This function is the even handler for the Empty Button on the GUI. 
//It requires no data and does nothing more then empty the bag.
void Cprogram2Dlg::Empty_Button()
{
   UpdateData(TRUE);
   TrashBag.erase_all();
   trashBagListBox.ResetContent();
   TotalWeight=TrashBag.GetWeight();
   TotalSize=TrashBag.GetSize();
   status = "The bag is now empty";
   UpdateData(FALSE);

}


void Cprogram2Dlg::Delete_All()
{
   UpdateData(TRUE);
   int total = 0;
   for (int i=0; i<TrashBag.GetSize(); i++)
   {
      if(TrashBag.erase_one(description,weight))
      {
         total ++;
         i --;
      }
   }
   char buffer[10];
	itoa(total, buffer, 10);
	status = " ";
   status += buffer;
   status += " items removed";
   UpdateListBox();
   UpdateData(FALSE);
}
