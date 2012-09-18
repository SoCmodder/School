// prog5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog5.h"
#include "prog5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProg5Dlg dialog

CProg5Dlg::CProg5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg5Dlg)
	m_newnum = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg5Dlg)
	DDX_Control(pDX, IDC_LIST_BAG, m_mylist);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_newnum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg5Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg5Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_FULL, OnButtonFull)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg5Dlg message handlers

BOOL CProg5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProg5Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProg5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//Assignment 5
//Erin Pringle and Joe Wingbermuehle
//09-21-2000
//This is a program to keep track of a "bag" of numbers using a linked list

const int MAX_LENGTH=20;	// Max length for int to string conversion

//Insert an item to the bag
//Precondition: A valid integer is typed into the edit box and the Insert
//               button is clicked.
//Postcondition: The integer is added to the bag and the new bag is displayed.
void CProg5Dlg::OnButtonInsert() 
{
	if(UpdateData(TRUE)) {

		// Insert the value, if possible, otherwise display error
		if(!m_bag.insert(m_newnum)) {
			MessageBox("The bag is full.",NULL,MB_OK);
		}

		DisplayBag();
	}
	UpdateData(FALSE);
}

//Remove an item from the bag
//Precondition:  A valid integer is typed into the edit box and the Remove
//               button is clicked.
//Postcondition:  If the integer is in the bag, the first occurance of the integer
//                is removed from the bag and the new list is displayed.  Otherwise
//                a message box pops up stating the integer was not found.
void CProg5Dlg::OnButtonRemove() 
{
	if(UpdateData(TRUE)) {

		// Use OnButtonFind's message if we could not remove the item
		if(!m_bag.remove(m_newnum)) {
			OnButtonFind();
		}
		DisplayBag();
	}
	UpdateData(FALSE);
}

//Check if a value is in the bag
//Precondition:  A valid integer is typed into the edit box and the Find
//               button is clicked.
//Postcondition:  A message box pops up stating whether or not that integer
//                was found in the bag.
void CProg5Dlg::OnButtonFind() 
{
	if(UpdateData(TRUE)) {
		char output[MAX_LENGTH+31];		// the string to display
		char str[MAX_LENGTH+1];			// temporary array for int to string conversion

		// Create the first part of the string to be displayed
		strcpy(output,"The number ");
		itoa(m_newnum,str,10);
		strcat(output,str);

		// Select a message based on whether or not the int was found
		if(m_bag.find(m_newnum)) {
			strcat(output," is in the bag.");
		} else {
			strcat(output," is not in the bag.");
		}

		// Display the message
		MessageBox(output,NULL,MB_OK);
	}
	UpdateData(FALSE);
}

//Check if the bag is full
//Precondition:  The Full button is clicked.
//Postcondition:  A message box pops up telling whether or not the bag is full.
void CProg5Dlg::OnButtonFull() 
{
	// Display a message on whether or not the bag is full
	if(m_bag.isFull()) {
		MessageBox("The bag is full.",NULL,MB_OK);
	} else {
		MessageBox("The bag is not full.",NULL,MB_OK);
	}
}

//Check if the bag is empty
//Precondition:  The Empty button is clicked.
//Postcondition:  A message box pops up telling whether or not the bag 
//                is empty.
void CProg5Dlg::OnButtonEmpty() 
{
	// Display message on whether or not the bag is full
	if(m_bag.isEmpty()) {
		MessageBox("The bag is empty.",NULL,MB_OK);
	} else {
		MessageBox("The bag is not empty.",NULL,MB_OK);
	}
}

//Display the contents of the bag in the list box
//Precondition:  bag is a valid CBag
//Postcondition:  The list box is cleared and the updated bag is displayed 
//                in the list box.
void CProg5Dlg::DisplayBag()
{
	char temp[MAX_LENGTH+1]; //temporary character array of the integers in m_Bag 
	int size; //size of m_Bag

	//getting the number of elements in m_Bag
	size = m_bag.numberElements();

	//Clearing list box
	m_mylist.ResetContent();
     
	//Creating temporary character array and displaying the new bag in the list box
	for (int index = 0; index < size; ++index ) 
    { 
		 itoa(m_bag[index],temp,10);
		 m_mylist.AddString(temp);
	}
}
