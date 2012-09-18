// EMRDlg.cpp : implementation file
// Program Description: This program maintains patients ordered by
// priority.  It uses a heap to keep the patients ordered, going from
// top to bottom in descending order.  It also has an option to list
// the patients in a dropdown display using a heap sort ordering them
// from top to bottom.

#include "stdafx.h"
#include "EMR.h"
#include "EMRDlg.h"
#include ".\emrdlg.h"

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


// CEMRDlg dialog



CEMRDlg::CEMRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEMRDlg::IDD, pParent)
  , medProblem(_T(""))
  , priNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEMRDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, medProblem);
  DDX_Text(pDX, IDC_EDIT2, priNum);
  DDX_Control(pDX, IDC_COMBO1, comboBox);
  DDX_Control(pDX, IDC_TREE1, treeControl);
}

BEGIN_MESSAGE_MAP(CEMRDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedADD)
  ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedTREAT)
  ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedCLEAR)
  ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedLIST)
END_MESSAGE_MAP()


// CEMRDlg message handlers

BOOL CEMRDlg::OnInitDialog()
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

void CEMRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEMRDlg::OnPaint() 
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
HCURSOR CEMRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/* Add's a patient's problem.
 * Pre: Something must be entered in description box and priority must be > -1
 * Post: A patient is added to the heap.
 */
void CEMRDlg::OnBnClickedADD()
{
  if( UpdateData(TRUE) )
  {
    // Checks to see if something is entered.
    if( medProblem.Trim().GetLength() == 0 )
      MessageBox("Please enter the patient's problem.", "Error!", MB_OK);

    // Checks the priority to make sure it is in the bounds.
    else if( priNum < 0 || priNum > 100 )
      MessageBox("Please enter a number between 0 and 100.", "Error!", MB_OK);

    else
    {
      // Creates a PATIENT with the given problem and priority.
      PATIENT newPatient( medProblem, priNum );

      // Inserts into the heap.
      eRoom.insert( newPatient );
      // Updates and displays the tree.
      treeControl.DeleteAllItems();
      redisplayTreeControl( 0, TVI_ROOT );
    }
  }

  UpdateData(FALSE);
}

/* Removes the highest priority patient.
 * Pre: There are patients in the heap.
 * Post: The highest patient is removed and the next highest is sent to the 
 * top.
 */
void CEMRDlg::OnBnClickedTREAT()
{
  if( UpdateData(FALSE) )
  {
    // If the patient was removed, a messagebox is displayed saying (s)he was.
    if( eRoom.removeRoot() )
      MessageBox("Patient treated!", "Success!", MB_OK);

    else
      MessageBox("Patient not treated!", "Error!", MB_OK);

    // Updates and displays the tree.
    treeControl.DeleteAllItems();
    redisplayTreeControl( 0, TVI_ROOT );
  }

  UpdateData(FALSE);
}

/* Clears the waiting room.
 * Pre: None.
 * Post: The heap(waiting room) is cleared.
 */
void CEMRDlg::OnBnClickedCLEAR()
{
  if( UpdateData(TRUE) )
  {
    eRoom.clear();
    // Updates and displays the tree.
    treeControl.DeleteAllItems();
    redisplayTreeControl( 0, TVI_ROOT );
  }

  UpdateData(FALSE);
}

/* Sends patients in order to a combo box.
 * Pre: None.
 * Post: All patients in the heap are added to the combo box.
 */
void CEMRDlg::OnBnClickedLIST()
{
  UpdateData(TRUE);

  // Creates a copy of the heap.
  HEAP copiedHeap( eRoom );
  bool success = true; // Variable used so that my remove function wouldn't
                       // produce a warning since it is a bool.
  
  comboBox.ResetContent(); // Resets combo box to nothing.
  int i = 0; // Variable used to show the PATIENT is the root patient.

  // While there are patients in the room, it adds them to the CBox.
  while( copiedHeap.getNumPatients() > 0 )
  {
    // Adds patients to the combo box.
    comboBox.AddString( copiedHeap.getPatient( i ).toString() );
    
    if( copiedHeap.removeRoot() )
      success = true;

    else
      success = false;
  }
  comboBox.SetCurSel( 0 );

  UpdateData(FALSE);
}

/* Updates tree display.
 * Pre: None.
 * Post: All patients in the heap are added to the tree display
 */
void CEMRDlg::redisplayTreeControl( int index, HTREEITEM parent ) 
{
  // If the index passed is greater than the number of patients, then it 
  // returns.
  if( index > eRoom.getNumPatients() - 1 )
    return;

	else if ( index < eRoom.getNumPatients() ) 
  {
    // If there is a patient, it puts them in the tree.
    if( eRoom.getPatient( index ).getDesc() != "" )
    {
      parent = treeControl.InsertItem( eRoom.getPatient( index ).toString(), 
                                       parent );

      // go display right subtree
	    redisplayTreeControl( (2*(index) +2), parent);
      // go display left subtree
	    redisplayTreeControl( (2*(index) +1), parent);   
	
      treeControl.Expand(parent, TVE_EXPAND);
	  }

	  else 
      treeControl.InsertItem("NULL", parent);
  }
}