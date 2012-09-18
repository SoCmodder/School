// groceriesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "groceries.h"
#include "groceriesDlg.h"
#include ".\groceriesdlg.h"

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


// CgroceriesDlg dialog



CgroceriesDlg::CgroceriesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CgroceriesDlg::IDD, pParent)
	, price(0)
	, description(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgroceriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListBox);
	DDX_Text(pDX, IDC_EDIT2, price);
	DDX_Text(pDX, IDC_EDIT1, description);
}

BEGIN_MESSAGE_MAP(CgroceriesDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
END_MESSAGE_MAP()


// CgroceriesDlg message handlers

BOOL CgroceriesDlg::OnInitDialog()
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

void CgroceriesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgroceriesDlg::OnPaint() 
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
HCURSOR CgroceriesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Adds an item when the "Add Item" button is clicked.
// Pre: None.
// Post: Checks to see if the bag is full and the price is non-negative, then adds the item to the
//       array and updates the listbox.
void CgroceriesDlg::OnBnClickedButton1()
{
	if (UpdateData(TRUE)) // updates the data
  {
	  GroceryItem item1; // a grocery item.
	
	  item1.description = description;  // assigns desc. from GUI to the grocery item defined.
	  item1.price = price; // assigns the price from GUI to the grocery item defined.

	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/
	  if ( item1.price < 0 || item1.price > 9999 )
		  MessageBox("Please enter a price between $0 and $9999.", "Error!", MB_OK);
	  else if ( groceryBag.isFull() )
		  MessageBox("The bag is full.", "Error!", MB_OK);
    else if ( description == "" )
      MessageBox("Please enter an item name.", "Error!", MB_OK);
	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/
	
	  else
	  {
	  	// adds the grocery item and then updates the listbox.
	  	groceryBag.add(item1);
	  	groceryBag.Display(ListBox);
	  	UpdateData(FALSE);
	  }
  }
	return;
}

// This function removes one occurence of the item specified.
// Pre: None.
// Post: Checks that the price is not non-negative and then runs the removeOne function.
//       After the item has been removed, it updates the listbox.
void CgroceriesDlg::OnBnClickedButton2()
{
	if (UpdateData(TRUE))
  {
	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/
	  if ( price < 0 || price > 9999 )
		  MessageBox("Please enter a price between $0 and $9999.", "Error!", MB_OK);
	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/
	  else
	  {
		  // grocery item declaration
		  GroceryItem item1;
		  item1.setPrice(price);
		  item1.setDescription(description);

      // removes the item
		  groceryBag.removeOne(item1);
		  groceryBag.Display(ListBox);
		  UpdateData(FALSE);
	  }
  }
	return;
}

// This function removes all occurences of the item specified.
// Pre: None.
// Post: Checks that the price is non-negative then runs the removeAll function
//       until all matching items have been removed from the array.
void CgroceriesDlg::OnBnClickedButton3()
{
	if (UpdateData(TRUE))
  {
	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/
	  if ( price < 0 || price > 9999 )
		  MessageBox("Please enter a price between $0 and $9999.", "Error!", MB_OK);
	  /********* CHECKS THAT ALL REQUIREMENTS ARE MET *********/

	  else
	  {
		  // declares a grocery item
		  GroceryItem item1;
		  item1.setPrice(price);
		  item1.setDescription(description);
		
      // removes all matching items
		  groceryBag.removeAll(item1);
		  groceryBag.Display(ListBox);
		  UpdateData(FALSE);
	  }
  }
	return;
}

// This function clears all of the items in said bag.
// Pre: None.
// Post: Runs the clearContents function and updates the listbox.
void CgroceriesDlg::OnBnClickedButton4()
{
	groceryBag.clearContents();
	groceryBag.Display(ListBox);

	return;
}
