// postfixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "postfix.h"
#include "postfixDlg.h"
#include ".\postfixdlg.h"

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


// CpostfixDlg dialog



CpostfixDlg::CpostfixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CpostfixDlg::IDD, pParent)
  , infexpr(_T(""))
  , postexpr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpostfixDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, infexpr);
  DDX_Text(pDX, IDC_EDIT2, postexpr);
}

BEGIN_MESSAGE_MAP(CpostfixDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedCONVERT)
END_MESSAGE_MAP()


// CpostfixDlg message handlers

BOOL CpostfixDlg::OnInitDialog()
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

void CpostfixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CpostfixDlg::OnPaint() 
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
HCURSOR CpostfixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CpostfixDlg::CheckInt( const char test )
{
  bool success = false;

  if( test == '0' || test == '1' || test == '2' || test == '3' || test=='4' ||
      test == '5' || test == '6' || test == '7' || test == '8' || test == '9' )
  {
    success = true;
  }

  return success;
}

bool CpostfixDlg::CheckForOper( const char test )
{
  bool success = false;

  if( test == '+' || test == '-' || test == '*' || test =='/' )
    success = true;

  return success;
}

bool CpostfixDlg::CheckForEndOper()
{
  bool checkForEndOper = true;

  // Checks the last element
  for( int i = infexpr.GetLength() - 1; i >= 0; i-- )
  {
    if( CheckInt( infexpr[i] ) )
    {
      checkForEndOper = true; // If it ends in an int, the expression is okay.      
      break;
    }
    
    else if( CheckForOper( infexpr[i] ) )
    {
      checkForEndOper = false; // If it ends in oper, its a bad expression.
      break;
    }
  }

  return checkForEndOper;
}

void CpostfixDlg::OnBnClickedCONVERT()
{
  UpdateData(TRUE);

  /********* VARIABLES *********/

  stack opers; // Used to store all operators or parenthesis.
  
  int index = 0; // What is used to move through the array

  bool addOperand = false; // Will be used to check for expression validity.
  bool success = true; // Used to check if the whole expression was a sucess
                       // and clear out any left over operators.
  bool endOper = CheckForEndOper(); // Checks to make sure the end is not an 
                                    // operator.

  postexpr = ""; // Resets post expression everytime.
  char mult = '*', div = '/';

  /********* VARIABLES *********/

  if( !endOper ) // If the end is an operator, it is an invalid expression.
  {
    success = false;
    MessageBox("You can't do this expression!", "Error!", MB_OK);
  }

  // If it is a valid expression so far, the loop will run.
  while( index < infexpr.GetLength() && endOper )
  {
    if( infexpr[ index ] == '(' )
    {
      opers.push( infexpr[ index ] ); // Pushes a left paren on the stack.
    }
    
    // Checks for an integer, if it is an integer, it runs the loop.
    else if( CheckInt( infexpr[ index ] ) )
    {
      // This make sure an integer was not previously added before it.
      if( !addOperand )
      {
        postexpr.AppendChar( infexpr[ index ] );
        addOperand = true;
      }
      
      // Otherwise, you have two integers next to each other, and thats bad.
      else
      {
        MessageBox("The expression is invalid.", "Error!",MB_OK);
        success = false;
        break;
      }
    }
    
    // Checks to see if the passed character is an operator.
    else if( CheckForOper( infexpr[ index ] ) )
    {
      if( addOperand ) // If an integer was added before it, the expression is 
                       // okay.
      {
        if( !opers.isEmpty() ) // If oper stack isnt empty, checks precedence.
        {
          if( opers.top() == mult || opers.top() == div )
          {
            postexpr.AppendChar( opers.top() );
            opers.pop();
            // Adds the opers.top() immediately if its a + or - or if the stack
            // still has operations and if it is equal to a left paren.
            if( (!opers.isEmpty() && opers.top() != '(') && 
                (infexpr[ index ] == '+' || infexpr[ index ] == '-') )
            {
              postexpr.AppendChar( opers.top() );
              opers.pop();
              opers.push( infexpr[ index ] );
            }
            else
            {
              // Otherwise, the oper is pushed.
              opers.push( infexpr[ index ] );
            }
          }
        
          // If there is something in the opers STACK, it is cleared if the
          // char trying to be put in is a + or - because of precedence.
          else if( (infexpr[ index ] == '+' || infexpr[ index ] == '-') )
          {
            if( CheckForOper( opers.top() ) )
            {
              postexpr.AppendChar( opers.top() );
              opers.pop();
              opers.push( infexpr[ index ] );
            }
            
            else
              opers.push( infexpr[ index ] );
          }
          
          // If its multiplication or division, it is just pushed in.
          else
          {
            opers.push( infexpr[ index ] );
          }
        }
      
        // Otherwise, if the stack is empty, it just pushes it in.
        else
        {
          opers.push( infexpr[ index ] );
        }

        // Means that the last thing added was NOT an integer.
        addOperand = false;
      }


      // If there was not an integer added before the operator it is trying
      // to add, then it is invalid.
      else
      {
        MessageBox("The expression is invalid.", "Error!",MB_OK);
        success = false;
        break;
      }
    }

    else if( infexpr[ index ] == ' ' )
    {
      // laugh out loud. you cant do anything with spaces!
    }

    // Testing the last case of a right parenthesis.
    else if( infexpr[ index ] == ')' )
		{
      infexpr.Trim();
      // If there is a operator next to a parenth, it is wrong.
      if( index != 0 && CheckForOper( infexpr[index-1] ) )
      {
        success = false;
        MessageBox("Invalid expression.", "Error!", MB_OK);
        break;
      }

      // If there is no left parenthesis or operator, something is wrong.
			else if( opers.isEmpty() )
			{
				MessageBox("Something is missing from the expression.", "Error!", 
                   MB_OK);
				success = false;
				break;
			}
      
      // If the top isn't the left parenthesis, there is still at least one
      // operation left.
      else if( opers.top() != '(' )
      {
        // Pops all opers left until it reaches a (
        do 
        { 
            postexpr.AppendChar( opers.top() );
            opers.pop();
        }while( !opers.isEmpty() && opers.top() != '(' );
      }

			// If the opers stack isnt empty, then it should be a left parenthesis.
			if( !opers.isEmpty() )
			{
				if( opers.top() == '(' )
					opers.pop();
			}
      
      // If not, they are missing a left parenthesis.
      else
			{
					MessageBox("You are missing a left parenthesis.", "Error!", MB_OK);
					success = false;
			}
		}

    // If it isn't, then something is definitely wrong or not entered.
    else
		{
			success = false;
			MessageBox("Something is wrong with your expression or it is not entered.", 
                 "Error!", MB_OK);
			break;
		}

    // Moves to next character.
    index++;
  };

  // If nothing failed, it runs this loop.
  if( success )
	{
    // If the opers stack is still not empty, it runs this.
		while( !opers.isEmpty() )
		{
      // If it comes up with a left parenthesis, they either forgot a right
      // parenthesis, or added an extra left.
			if( opers.top() == '(' )
			{
				MessageBox("You forgot a right paren, or added an extra left paren.", 
                   "Error!", MB_OK );
				postexpr = ""; // Sets expression = to blank so the program doesn't
                       // show what it has done.
				break;
			}
      
      // If there are more operators, it pops them until they are gone.
      else if( CheckForOper ( opers.top() ) )
      {	
        postexpr.AppendChar( opers.top() );
        opers.pop();
      }
		}
	}
  
  // If the expression did not complete successfully, this empties the post
  // expression.
  else if( !success )
  {
		postexpr = ""; // Sets expression to blank if it was unsuccessful so it
                   // does not show what it has done up until the error.
  }

  UpdateData(FALSE);
}
