// HW9Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "HW9.h"
#include "HW9Dlg.h"
#include "Stack.h"
#include "CharNode.h"
#include "IntNode.h"

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
// CHW9Dlg dialog

CHW9Dlg::CHW9Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHW9Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHW9Dlg)
	m_InFix = _T("");
	m_PostFix = _T("");
	m_Result = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHW9Dlg)
	DDX_Text(pDX, IDC_InFix, m_InFix);
	DDX_Text(pDX, IDC_PostFix, m_PostFix);
	DDX_Text(pDX, IDC_Result, m_Result);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHW9Dlg, CDialog)
	//{{AFX_MSG_MAP(CHW9Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ConvertInFix, OnConvertInFix)
	ON_BN_CLICKED(IDC_Clear, OnClear)
	ON_BN_CLICKED(IDC_EvaluatePostFix, OnEvaluatePostFix)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHW9Dlg message handlers

BOOL CHW9Dlg::OnInitDialog()
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

void CHW9Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHW9Dlg::OnPaint() 
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
HCURSOR CHW9Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





/* This function takes a pre fix notation equation and makes it a post fix 
notation equation
PRE: the prefix notation has a space between characters and is syntactically 
correct
POST: m_PostFix contains the updated equation
 *************************************************************************/
void CHW9Dlg::OnConvertInFix() 
{
	UpdateData (TRUE);
	Stack charStack;
	CString temp;
	char delim [] = " ",* token, PostFix[50],InFix [50];
	
	Node * info;
	CharNode *  top;
	char * topOp;
	CharNode * newOper;


	strcpy (InFix, m_InFix);
	token = strtok (InFix, delim);
	while (token != NULL)
	{
		
		if (!strcmp (token, "*")||!strcmp (token, "/")||!strcmp (token, "+")
			||!strcmp (token, "-") ||!strcmp (token, "(")||!strcmp (token, ")"))
		{
			if ((charStack.top () == NULL) )   //  Empty Set Branch
			{
				newOper = new CharNode (token);
				charStack.push (newOper);
			}
			else    // Branches for non-empty set
			{
				info = charStack.top();
				top = (CharNode*) info;
				topOp = top -> oper; 
				
				if ( !strcmp (topOp, "(")) // Stack any Operator after "("
				{
					newOper = new CharNode (token);
					charStack.push (newOper);
				}			
				
				
				
				if ( (!strcmp (token, "+") || !strcmp (token, "-")) && // Branches for maintaining Higharchy
					 (!strcmp (topOp, "*") || !strcmp (topOp, "/")) )
				{
					while ((!(strcmp (topOp, "*")) || !(strcmp (topOp, "/"))))
					{
						
						strcpy (PostFix, topOp);
						m_PostFix = m_PostFix + PostFix + " ";
						charStack.pop();

						
						if (charStack.top () != NULL) 
						{
							info = charStack.top();
							top = (CharNode*) info;
							topOp = top -> oper;

			
						}
						else
						{
							topOp = "EmptySet";
						}
					}
					newOper = new CharNode (token);
					charStack.push (newOper);

				}

				if ( (!strcmp (token, "+") || !strcmp (token, "-")) &&
					 (!strcmp (topOp, "+") || !strcmp (topOp, "-")))
				{
					while (charStack.top () != NULL)
					{
						info = charStack.top();
						top = (CharNode*) info;
						topOp = top -> oper;	
						
						strcpy (PostFix, topOp);
						m_PostFix = m_PostFix + PostFix + " ";
						charStack.pop();
					} 
					newOper = new CharNode (token);
					charStack.push (newOper);

					
				}
				if ( (!strcmp (token, "*") || !strcmp (token, "/")) &&
					 (!strcmp (topOp, "*") || !strcmp (topOp, "/")))
				{
					while ((charStack.top () != NULL)|| !strcmp (token, "+")||
						    !strcmp (token, "-"))
					{
						info = charStack.top();
						top = (CharNode*) info;
						topOp = top -> oper;	
						
						strcpy (PostFix, topOp);
						m_PostFix = m_PostFix + PostFix + " ";
						charStack.pop();
					} 
					
					
					
					newOper = new CharNode (token);
					charStack.push (newOper);

					
				}
				if ( (!strcmp (token, "*") || !strcmp (token, "/")) &&
					 (!strcmp (topOp, "+") || !strcmp (topOp, "-")))
				{
					newOper = new CharNode (token);
					charStack.push (newOper);

				}
				if (!strcmp (token, "(") )
				{
					newOper = new CharNode (token);
					charStack.push (newOper);
				}
				
				if (!strcmp (token, ")" ))
				{
					info = charStack.top();
					top = (CharNode*) info;
					topOp = top -> oper; 					
					
					while (strcmp (topOp, "("))
					{
						strcpy (PostFix, topOp);
						m_PostFix = m_PostFix + PostFix + " ";
						charStack.pop();

						info = charStack.top();
						top = (CharNode*) info;
						topOp = top -> oper;

					}
					charStack.pop ();
				}

			}
			
		}
		else
		{
			strcpy (PostFix, token);
			m_PostFix = m_PostFix + PostFix + " ";
		}
		token = strtok (NULL, delim);
	}
	
	while (charStack.top () != NULL)
	{
		info = charStack.top();
		top = (CharNode*) info;
		topOp = top -> oper;
		
		strcpy (PostFix, topOp);
		m_PostFix = m_PostFix + PostFix + " ";
		charStack.pop ();
		
	}

	UpdateData (FALSE);

}







/* This function clears the fields so that repeated equations can be tested
PRE: NONE
POST: m_Result and m_PostFix are cleared of values
 *************************************************************************/
void CHW9Dlg::OnClear() 
{
	UpdateData (TRUE);
	m_PostFix = " ";
	m_Result = 0;
	UpdateData (FALSE);
}





/* This function takes a post fix notation equation and returns the answer
PRE: the original prefix notation equation was syntactically 
correct and had spaces between characters
POST: m_Result contains the numerical value of the original equation
 *************************************************************************/
void CHW9Dlg::OnEvaluatePostFix() 
{
	UpdateData (TRUE);
	Stack intStack;
	
	Node * info;
	IntNode *  top;
	int num1, num2;
	IntNode * newOper;
	char delim [] = " ",* token, PostFix [50];


	strcpy (PostFix, m_PostFix);
	token = strtok (PostFix, delim);

	while (token != NULL)
	{
		if (!strcmp (token, "*")||!strcmp (token, "/")||!strcmp (token, "+")
			||!strcmp (token, "-"))
		{
			info = intStack.top();
			top = (IntNode*) info;
			num1 = top -> num;
			intStack.pop ();

			info = intStack.top();
			top = (IntNode*) info;
			num2 = top -> num;
			intStack.pop ();

			if (!strcmp (token, "*"))
			{
				num1 = num1 * num2;
			}

			if (!strcmp (token, "+"))
			{
				num1 = num1 + num2;
			}

			if (!strcmp (token, "-"))
			{
				num1 = num2 - num1;
			}

			if (!strcmp (token, "/"))
			{
				num1 = num2 / num1;
			}
			
			newOper = new IntNode (num1);
			intStack.push (newOper);

		}
		else
		{
			num1 = atoi (token);
			newOper = new IntNode (num1);
			intStack.push (newOper);
		}
	token = strtok (NULL, delim);
	}

	info = intStack.top();
	top = (IntNode*) info;
	m_Result = top -> num;
	UpdateData (FALSE);

}
