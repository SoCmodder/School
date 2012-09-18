// zombieVirusDlg.cpp : implementation file
// Program descript: This program allows the user to create people and decide whether
//                   they become vaccinated or zombified.  They can also choose if they
//                   want to kill only zombies or unleash armageddon and kill everyone.

#include "stdafx.h"
#include "zombieVirus.h"
#include "zombieVirusDlg.h"
#include ".\zombievirusdlg.h"

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


// CzombieVirusDlg dialog



CzombieVirusDlg::CzombieVirusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CzombieVirusDlg::IDD, pParent)
  , name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CzombieVirusDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, name);
  DDX_Control(pDX, IDC_LIST1, aliveListBox);
  DDX_Control(pDX, IDC_LIST2, cemetaryListBox);
}

BEGIN_MESSAGE_MAP(CzombieVirusDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedADD)
  ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedVaccinate)
  ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedZombify)
  ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedarmageddon)
  ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedZombieAttack)
  ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedkillZombies)
END_MESSAGE_MAP()


// CzombieVirusDlg message handlers

BOOL CzombieVirusDlg::OnInitDialog()
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

void CzombieVirusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CzombieVirusDlg::OnPaint() 
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
HCURSOR CzombieVirusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CzombieVirusDlg::OnBnClickedADD()
{
  NODE* temp = NULL;
  bool nameError = false;

  if( UpdateData(TRUE) ) // Checks for entered data
  {
    for( temp = alive.getHeadPtr(); temp != NULL; temp = temp->getNext() )
    {
      // Checks if a person with the same name exists.
      if( temp->getPerson().getName() == name )  
      {      
        nameError = true;
      } 
    }
    
    if( nameError )
      MessageBox("A person with that name already exists!", "Error!", MB_OK);

    // Checks to make sure something has been entered.
    else if( name.Trim().GetLength() == 0 )
      MessageBox("Please enter a name!", "Error!", MB_OK);

    else
    {
    PERSON human1( name ); // Creates person.
    alive.insertAtHead( human1 ); // Inserts them at the top of the list.
    alive.updateBagContentsDisplay(aliveListBox); // Updates list box.
    UpdateData(FALSE);
    }
  }
}

void CzombieVirusDlg::OnBnClickedVaccinate()
{
  UpdateData(TRUE);

  int selectedPerson =  aliveListBox.GetCurSel(); // Determines the position of selected person.
  
  if( aliveListBox.GetCurSel() > -1 )
  {
    NODE* personToVac = alive.findNodeByIndex(selectedPerson); // NODE selected person is stored in.

    PERSON savePerson = personToVac->getPerson(); // Extracts the person from the node.

    // Tests to see if the person has already been vaccinated or zombified.
    if( savePerson.getStatus() == "Zombie" || savePerson.getStatus() == "Vaccinated" )
      MessageBox("You can't vaccinate this person!", "Error!", MB_OK);
    
    else
      savePerson.setVaccinated(); // Vaccinates the person.

    personToVac->setPerson(savePerson); // Updates the NODE with the newly vaccinated person.
    alive.updateBagContentsDisplay(aliveListBox); // Updates list box.
  }

  else
    MessageBox("Select a person to vaccinate!", "Error!", MB_OK);

  UpdateData(FALSE);
}

void CzombieVirusDlg::OnBnClickedZombify()
{
  UpdateData(TRUE);

  int selectedPerson =  aliveListBox.GetCurSel(); // Determines the position of selected person.
  
  if( aliveListBox.GetCurSel() > -1 )
  {
    NODE* personToZom = alive.findNodeByIndex(selectedPerson); // NODE selected person is stored in.

    PERSON zomPerson = personToZom->getPerson();

    // Tests to see if the person has already been vaccinated or zombified.
    if( zomPerson.getStatus() == "Zombie" || zomPerson.getStatus() == "Vaccinated" )
      MessageBox("You can't zombify this person!", "Error!", MB_OK);
    
    else
      zomPerson.setZombie(); // Zombifies the person.

    personToZom->setPerson(zomPerson); // Updates the NODE with the newly zombified person.
    alive.updateBagContentsDisplay(aliveListBox); // Updates list box.
  }

  else
    MessageBox("Select a person to zombify!", "Error!", MB_OK);

  UpdateData(FALSE);
}

void CzombieVirusDlg::OnBnClickedZombieAttack()
{
  UpdateData(TRUE);

  NODE* temp = NULL;
  NODE* attackPerson = NULL;

  for( temp = alive.getTailPtr(); temp != NULL; temp = temp->getPrev() )
  {
    // Checks for a zombie.
    if( temp->getPerson().getStatus() == "Zombie" )
    {
      // Runs up the list zombifying people until it finds a vaccinated person.
      for( attackPerson = temp->getPrev(); attackPerson != NULL; attackPerson = attackPerson->getPrev() )
      {
        if( attackPerson->getPerson().getStatus() == "Unvaccinated" )
        {
          PERSON zombiePerson = attackPerson->getPerson(); // Extracts the person from the NODE.

          zombiePerson.setZombie(); // Zombifies extracted person.
          attackPerson->setPerson( zombiePerson ); // Updates the NODE with zombified person.
          alive.updateBagContentsDisplay(aliveListBox); // Updates the listbox.
        }

        else
        {
          break;
        }
      }  
      
      // Runs down the list zombifying people until it finds a vaccinated person.
      for( attackPerson = temp->getNext(); attackPerson != NULL; attackPerson = attackPerson->getNext() )
      {
        if( attackPerson->getPerson().getStatus() == "Unvaccinated" )
        {
          PERSON zombiePerson = attackPerson->getPerson(); // Extracts the person from the NODE.

          zombiePerson.setZombie(); // Zombifies the person.
          attackPerson->setPerson( zombiePerson ); // Updates the NODE with zombified person.
          alive.updateBagContentsDisplay(aliveListBox); // Updates the listbox.
        }

        else
        {
          break;
        }
      }
    }  
  }

  UpdateData(FALSE);
}

void CzombieVirusDlg::OnBnClickedarmageddon()
{
  UpdateData(TRUE);

  PERSON personToMove;

  while( alive.getHeadPtr() != NULL ) {
    // Extracts person to be moved from alive to cemetary.
    personToMove = alive.getHeadPtr()->getPerson();

    alive.removeHeadNode();

    // Moves the person to the tail of the cemetary list.
    cemetary.insertAtTail( personToMove );
  }

  cemetary.updateBagContentsDisplay(cemetaryListBox); // Updates list box.
  alive.updateBagContentsDisplay(aliveListBox);

  UpdateData(FALSE);
}

void CzombieVirusDlg::OnBnClickedkillZombies()
{
  UpdateData(TRUE);

  NODE* temp = NULL; // Will be the temp NODE to check for a Zombie.
  bool kill = true; // Variable that tells the loop whether to run or not.
  PERSON zombieToKill;

  while( kill )
  {
    kill = false;

    // Runs through the list in the alive list box.
    for( temp = alive.getTailPtr(); temp != NULL; temp = temp->getPrev() )
    {  
      if( temp->getPerson().getStatus() == "Zombie" )
      {      
        zombieToKill = temp->getPerson(); // Extracts the zombie.
        alive.removeNode( temp ); // Removes the NODE with the Zombie in it.
        cemetary.insertAtTail( zombieToKill ); // Puts the Zombie in the cemetary.
        kill = true;
        break; // Breaks out of the loop.
      }
    }
  }

  alive.updateBagContentsDisplay(aliveListBox);
  cemetary.updateBagContentsDisplay(cemetaryListBox);

  UpdateData(FALSE);
}