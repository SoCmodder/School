// treeDlg.cpp : implementation file
/* Program Description: This program inserts the names of any employees entered and orders
 * them alphabetically in order to achieve an efficient search time.
 */

#include "stdafx.h"
#include "tree.h"
#include "treeDlg.h"
#include ".\treedlg.h"

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


// CtreeDlg dialog



CtreeDlg::CtreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtreeDlg::IDD, pParent)
  , name(_T(""))
  , resultBox(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtreeDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, name);
  DDX_Control(pDX, IDC_TREE2, treeControl);
  DDX_Control(pDX, IDC_EDIT2, orderControl);
  DDX_Text(pDX, IDC_EDIT2, resultBox);
}

BEGIN_MESSAGE_MAP(CtreeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedINSERT)
  ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedDELETE)
  ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedFIND)
  ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedCLEAR)
  ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedPREORDER)
  ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedINORDER)
  ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedPOSTORDER)
END_MESSAGE_MAP()


// CtreeDlg message handlers

BOOL CtreeDlg::OnInitDialog()
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

void CtreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtreeDlg::OnPaint() 
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
HCURSOR CtreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Updates the tree.
// Pre: None.
// Post: All NODES are added to tree.
void CtreeDlg::redisplayTreeControl( NODE* root1, HTREEITEM parent ) 
{
	if (root1 != NULL) 
  {
    parent = treeControl.InsertItem( root1->toString(), parent );

	  if ( !root1->isLeaf() ) 
    {
	    redisplayTreeControl(root1->getRight(), parent); // go display right subtree
	    redisplayTreeControl(root1->getLeft(), parent);   // go display left subtree
	  }
	
    treeControl.Expand(parent, TVE_EXPAND);
	}

	else 
    treeControl.InsertItem("NULL", parent);
}

// Inserts a new value.
// Pre: Something has been entered.
// Post: Inserts the new value into a node at the root of the tree
// and redisplays the tree.
void CtreeDlg::OnBnClickedINSERT()
{
  if(UpdateData(TRUE))
   {
	  if( name.Trim().GetLength( ) == 0 )
    {
	    MessageBox("Enter someone to add.", "Insert Error");
	    return;
	  }
		
    // Inserts a NODE with the given name.
    tree.insert( tree.getRootForUpdate(), name ); 

    // Deletes the tree and re-updates it.
	  treeControl.DeleteAllItems(); 
	  redisplayTreeControl( tree.getRootForUpdate(), TVI_ROOT );
	}

	UpdateData(FALSE);
}

// Deletes a node from the tree.
// Pre: Something to delete has been entered.
// Post: Removes the node with the matching value, otherwise it displays
// a message box saying it couldn't find the person.
void CtreeDlg::OnBnClickedDELETE()
{
  if( UpdateData(TRUE) )
  {
    if( name.Trim().GetLength( ) == 0 )
    {
	    MessageBox("Enter someone to remove.", "Deletion Error");
	    return;
	  }
    
    else
    {
      // Removes a NODE with the given name.
      bool removed = tree.remove( tree.getRootForUpdate(), name );

      if( !removed )
        MessageBox("Person not found!", "Error!",MB_OK);

      // Deletes the tree and re-updates it.
      treeControl.DeleteAllItems();
      redisplayTreeControl( tree.getRoot(), TVI_ROOT );
    }
  }

  UpdateData(FALSE);
}

// Finds the person in the tree with the given value.
// Pre: A name has been entered.
// Post: The node with the matching name is found and displayed in
// the result box.
void CtreeDlg::OnBnClickedFIND()
{
  if( UpdateData(TRUE) )
  {
    if( name.Trim().GetLength( ) == 0 )
    {
	    MessageBox("Enter someone to find.", "Find Error");
	    return;
	  }

    else
    {
      // Finds the NODE and adds it into temp.
      NODE* temp = tree.find( tree.getRoot(), name );

      if( temp == NULL )
        MessageBox("Person not found!", "Error!", MB_OK);

      else
      {
        // Extracts the data from the found NODE.
        CString foundData = temp->toString();
        // Puts the data in the edit control.
        resultBox = foundData;
      }
    }
  }

  UpdateData(FALSE);
}

// Clears the tree.
// Pre: None.
// Deletes ALL nodes from the tree.
void CtreeDlg::OnBnClickedCLEAR()
{
  if( UpdateData(TRUE) );
  {
    // Empties the tree.
    tree.clearTree( tree.getRootForUpdate() );
    treeControl.DeleteAllItems();
    redisplayTreeControl( tree.getRoot(), TVI_ROOT );
  }

  UpdateData(FALSE);
}

// PreOrders the tree.
// Pre: None.
// Post: Orders the tree by root, left, then right and displays the final
// result in the result box.
void CtreeDlg::OnBnClickedPREORDER()
{
  UpdateData(TRUE);
  // Empties the result box.
  resultBox.Empty();

  if( tree.getRoot() != NULL )
  {
    // preOrders the tree.
    CString preString = tree.preOrderTraversal( tree.getRoot() );

    // Updates it in the result box.
    resultBox = preString;
  }

  else
    MessageBox("Tree is empty!", "PreOrder Error", MB_OK);

  UpdateData(FALSE);
}

// InOrders the tree.
// Pre: None.
// Post: Orders the tree by left, root, then right and displays the final
// result in the result box.
void CtreeDlg::OnBnClickedINORDER()
{
  UpdateData(TRUE);
  resultBox.Empty();

  if( tree.getRoot() != NULL )
  {
    // Prints data from tree inOrder.
    CString inOrdString = tree.inOrderTraversal( tree.getRoot() );

    // Updates it in the result box.
    resultBox = inOrdString;
  }

  else
    MessageBox("Tree is empty!", "InOrder Error", MB_OK);

  UpdateData(FALSE);
}

// PostOrders the tree.
// Pre: None.
// Post: Orders the tree by eft, then right, then root and displays the final
// result in the result box.
void CtreeDlg::OnBnClickedPOSTORDER()
{
  UpdateData(TRUE);
  resultBox.Empty();

  if( tree.getRoot() != NULL )
  {
    // Prints data from tree in postOrder
    CString postString = tree.postOrderTraversal( tree.getRoot() );

    // Updates it in the result box.
    resultBox = postString;
  }

  else
    MessageBox("Tree is empty!", "PostOrder Error", MB_OK);

  UpdateData(FALSE);
}
