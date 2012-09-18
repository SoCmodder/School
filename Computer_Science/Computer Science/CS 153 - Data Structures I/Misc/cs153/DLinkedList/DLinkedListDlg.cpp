// DLinkedListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DLinkedList.h"
#include "DLinkedListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLinkedListDlg dialog

CDLinkedListDlg::CDLinkedListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDLinkedListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLinkedListDlg)
	m_input = _T("");
	m_fileName = _T("");
	m_selection = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_modified=0;
}

void CDLinkedListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLinkedListDlg)
	DDX_Control(pDX, IDC_LIST_DISP, m_list);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_fileName);
	DDX_LBIndex(pDX, IDC_LIST_DISP, m_selection);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDLinkedListDlg, CDialog)
	//{{AFX_MSG_MAP(CDLinkedListDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	ON_BN_CLICKED(IDC_BUTTON_FULL, OnButtonFull)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_LBN_SELCHANGE(IDC_LIST_DISP, OnSelchangeListDisp)
	ON_BN_CLICKED(IDC_BUTTON_APPEND, OnButtonAppend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLinkedListDlg message handlers

BOOL CDLinkedListDlg::OnInitDialog()
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

void CDLinkedListDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else if(nID == SC_CLOSE) {
		if(m_modified) {
			if(MessageBox("Exit and discard changes?",NULL,MB_YESNO)==IDNO)
				return;
		}
		CDialog::OnSysCommand(nID,lParam);
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDLinkedListDlg::OnPaint() 
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
HCURSOR CDLinkedListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Assignment 6 (Doubly Linked List Bag)
// Erin Pringle and Joe Wingbermuehle
// This is a program to keep track of strings using a doubly linked list.

// Insert an item (m_input) to m_bag
// PRE: m_input is the string to insert.
// POST: m_input is inserted into m_bag if possible, otherwise an
//		 error message is displayed.
void CDLinkedListDlg::OnButtonInsert() {
	UpdateData(TRUE);

	// Insert if possible, else give error
	if(!m_bag.insert(m_input)) {
		MessageBox("Could not insert value.",NULL,MB_OK);
	} else {
		m_modified=1;
	}

	DisplayList();
	UpdateData(FALSE);
}

// Append an item to the list
// PRE: m_input is the string to append
// POST: m_input is appeneded to m_bag
void CDLinkedListDlg::OnButtonAppend() {
	UpdateData(TRUE);

	// Append if possible, else give error
	if(!m_bag.append(m_input)) {
		MessageBox("Could not append value.",NULL,MB_OK);
	} else {
		m_modified=1;
	}

	DisplayList();
	UpdateData(FALSE);
}

// Remove an item (m_input) from m_bag.
// PRE: m_input is the item to remove.
// POST: Removes the item from m_bag if possible, otherwise gives
//		 an error message.
void CDLinkedListDlg::OnButtonRemove() {
	UpdateData(TRUE);

	// Remove if possible, else give error
	if(!m_bag.remove(m_input)) {
		OnButtonFind();		// use OnButtonFind's error message
	} else {
		m_modified=1;
	}

	DisplayList();
	UpdateData(FALSE);
}

// Check if a string (m_input) is in m_bag
// PRE: m_input is the string to find.
// POST: Displays a message showing whether or not m_input is in m_bag.
void CDLinkedListDlg::OnButtonFind() {
	UpdateData(TRUE);
	char *beginning="The string \"";				// Beginning of the message
	char *negativeEnd="\" is not in the list.";		// "not in list" ending
	char *positiveEnd="\" is in the list.";			// "in list" ending

	// Make length the length of the largest possible output
	int length=strlen(beginning)+strlen(negativeEnd)+strlen(m_input);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_input is found
	strcpy(output,beginning);
	strcat(output,m_input);
	if(m_bag.find(m_input)) {
		strcat(output,positiveEnd);
	} else {
		strcat(output,negativeEnd);
	}

	MessageBox(output,NULL,MB_OK);
	UpdateData(FALSE);
	delete [] output;
}

// Check if m_bag is empty
// PRE: none
// POST: Display a message showing whether or not m_bag is empty.
void CDLinkedListDlg::OnButtonEmpty() {
	char *beginning="The list is ";		// Beginning of the message
	char *negative="not ";				// "not" for if the bag is not empty
	char *ending="empty.";				// End of the message

	// Make length the length of the largest possible output
	int length=strlen(beginning)+strlen(negative)+strlen(ending);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_bag is empty
	strcpy(output,beginning);
	if(!m_bag.empty()) {
		strcat(output,negative);
	}
	strcat(output,ending);

	MessageBox(output,NULL,MB_OK);
	delete [] output;
}

// Check if m_bag is full
// PRE: none
// POST: Display a message showing whether or not m_bag is full.
void CDLinkedListDlg::OnButtonFull() {
	char *beginning="The list is ";		// Beginning of the message
	char *negative="not ";				// "not" in case m_bag is full
	char *ending="full.";				// End of the message

	// Make length the length of the largest possible ouput
	int length=strlen(beginning)+strlen(negative)+strlen(ending);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_bag is full
	strcpy(output,beginning);
	if(!m_bag.full()) {
		strcat(output,negative);
	}
	strcat(output,ending);

	MessageBox(output,NULL,MB_OK);
	delete [] output;
}

// Load a file and display the contents in the listbox
// PRE: m_modified is 0 if the bag hasn't been modifed.
//		m_fileName is the file from which to load m_bag.
// POST: If m_modified is 1, the user is asked whether or not to
//		 discard changes, not changes are made if not.
//		 m_fileName is opened if possible (error message if not)
//		 and m_bag is loaded.
void CDLinkedListDlg::OnMenuOpen() {
	FILE *fd;		// File descriptor for the input file
	CString temp;	// CString for creating a char* from char's
	int ch;			// Input from the file

	// Make sure the user is okay with lossing changes if modified
	if(m_modified) {
		if(MessageBox("Open and discard changes?",NULL,MB_YESNO)==IDNO)
			return;
	}

	UpdateData(TRUE);

	// Attempt to open the file, give message on error
	if(m_fileName!="" && (fd=fopen(m_fileName,"rb"))) {
		m_bag.reset();

		// Loop through the complete values and insert to m_bag
		for(;;) {

			// Create a CString by reading chars from fd
			temp="";
			for(;;) {
				ch=fgetc(fd);
				if(ch=='\n' || ch==EOF) break;
				temp+=char(ch);
			}
			if(ch==EOF) break;
			m_bag.insert(temp);
		}

		fclose(fd);
		m_modified=0;
	} else {	// File could not be opened
		char *beginning="Could not open \"";	// Beginning of the error message
		char *ending="\" for read.";			// End of the error message

		// Make length the length of the error message
		int length=strlen(beginning)+strlen(ending)+strlen(m_fileName);

		// Allocate memory for the message string and create the string
		char *output=new char[length+1];
		strcpy(output,beginning);
		strcat(output,m_fileName);
		strcat(output,ending);

		MessageBox(output,NULL,MB_OK);
		delete [] output;
	}

	DisplayList();
	UpdateData(FALSE);
}

// Save m_bag to a file
// PRE: m_fileName is the name of the file to save and m_bag is
//		the list to save
// POST: Saves to m_fileName if possible, otherwise gives an error
//		 On success, m_modified is set to 0
void CDLinkedListDlg::OnMenuSave() {
	FILE *fd;		// File descriptor for the file to write
	UpdateData(TRUE);

	// Open the file if possible, else give error message
	if(m_fileName!="" && (fd=fopen(m_fileName,"wb"))) {

		// Loop through writing the elements of m_bag to the file
		for(int x=0;x<m_bag.numberElements();x++) {
			fprintf(fd,"%s\n",m_bag[x]);
		}

		fclose(fd);
		m_modified=0;

		MessageBox("File saved!",NULL,MB_OK);
	} else {
		char *beginning="Could not open \"";		// Beginning of the error message
		char *ending="\" for write.";				// End of the error message

		// Make length the length of the error message
		int length=strlen(beginning)+strlen(ending)+strlen(m_fileName);

		// Allocate memory for the error message and create the message
		char *output=new char[length+1];
		strcpy(output,beginning);
		strcat(output,m_fileName);
		strcat(output,ending);

		MessageBox(output,NULL,MB_OK);
		delete [] output;
	}

	UpdateData(FALSE);
}

// Display the list (m_bag) in the listbox
// PRE: m_bag is a valid CDList
// POST: Display the contents of m_bag in the listbox
void CDLinkedListDlg::DisplayList() {
	int x;		// Index variable

	m_list.ResetContent();

	// Add the elements of m_bag to the listbox
	for(x=0;x<m_bag.numberElements();x++) {
		m_list.AddString(m_bag[x]);
	}
}


// Display the about dialog
// PRE: none
// POST: The about dialog is displayed
void CDLinkedListDlg::OnMenuAbout() {
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

// Exit if m_bag hasn't been modified or the user wants to discard it
// PRE: m_modified is 1 if modified, 0 if not
// POST: Exits if the bag hasn't been modified. If the bag has been
//		 modified, it asks the user if s/he wants to discard changes
//		 and exits only if the user selects "Yes"
void CDLinkedListDlg::OnMenuExit() {

	// If m_bag has been modified, make sure the user really wants to exit
	if(m_modified) {
		if(MessageBox("Exit and discard changes?",NULL,MB_YESNO)==IDNO)
			return;
	}

	// Exit
	CDialog::OnOK();
}

// Clear the list if it hasn't been modified or the user wants to discard it
// PRE: m_modified is 1 if modified, 0 if not
// POST: Clears the m_bag if it hasn't been modified. If m_bag has been
//		 modified, it asks the user if s/he wants to discard changes and
//		 clears only if so.
void CDLinkedListDlg::OnMenuNew() {

	// If m_bag has been modified, make sure the user wants to discard changes
	if(m_modified) {
		if(MessageBox("Create new and discard changes?",NULL,MB_YESNO)==IDNO)
			return;
	}

	// Clear m_bag and update the listbox
	UpdateData(TRUE);
	m_bag.reset();
	DisplayList();
	UpdateData(FALSE);
}

// Put the value the user clicks in the list box in m_input
// PRE: none
// POST: m_input is the listbox selection
void CDLinkedListDlg::OnSelchangeListDisp() {
	UpdateData(TRUE);
	m_input=m_bag[m_selection];
	UpdateData(FALSE);
}
