// pegsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pegs.h"
#include "pegsDlg.h"
#include <math.h>

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
// CPegsDlg dialog

CPegsDlg::CPegsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPegsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPegsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPegsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPegsDlg)
	DDX_Control(pDX, IDC_LIST_MOVES, m_moveList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPegsDlg, CDialog)
	//{{AFX_MSG_MAP(CPegsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_MENU_NEW, OnMenuNew)
	ON_COMMAND(IDC_MENU_EXIT, OnMenuExit)
	ON_COMMAND(IDC_MENU_ABOUT, OnMenuAbout)
	ON_BN_CLICKED(IDC_BUTTON_SOLVE, OnButtonSolve)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_HINT, OnButtonHint)
	ON_BN_CLICKED(IDC_RADIO_SIZE5, OnRadioSize5)
	ON_BN_CLICKED(IDC_RADIO_SIZE6, OnRadioSize6)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnButtonUndo)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PIECE+0,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+1,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+2,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+3,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+4,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+5,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+6,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+7,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+8,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+9,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+10,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+11,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+12,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+13,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+14,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+15,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+16,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+17,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+18,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+19,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+20,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+21,OnClickPiece)
	ON_BN_CLICKED(IDC_PIECE+22,OnClickPiece)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPegsDlg message handlers

BOOL CPegsDlg::OnInitDialog()
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
	
	this->CheckDlgButton(IDC_RADIO_SIZE5,1);
	boardSize=16;
	m_empty=0;
	DrawBoard();
	OnMenuNew();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPegsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPegsDlg::OnPaint() 
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
HCURSOR CPegsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPegsDlg::OnMenuNew() {
	int x,y;
	char temp[3],str[12];

	if(m_empty>boardSize-2) {
		m_empty=0;
	}

	for(y=0;y<MAX_MATRIX_SIZE;y++) {
		for(x=0;x<MAX_MATRIX_SIZE;x++) {
			board[x][y]=2;
		}
	}

	for(x=0;x<boardSize-1;x++) {
		m_spaces[x].SetIcon(ExtractIcon(NULL,ICON_FILE,ICON_PEG));
		board[GetX(x)][GetY(x)]=1;
	}

	for(x=boardSize-1;x<MAX_BOARD_SIZE-1;x++) {
		m_spaces[x].SetIcon(ExtractIcon(NULL,ICON_FILE,ICON_UNUSED));
	}

	board[GetX(m_empty)][GetY(m_empty)]=0;

	m_spaces[m_empty].SetIcon(ExtractIcon(NULL,ICON_FILE,ICON_EMPTY));

	m_moveStatus=0;
	m_numberPegs=boardSize-2;

	m_moveList.ResetContent();

	itoa(m_empty+1,temp,10);
	strcpy(str,"Empty: ");
	strcat(str,temp);
	m_moveList.AddString(str);

	UpdateData();
}

void CPegsDlg::OnMenuExit() {
	OnOK();
}

void CPegsDlg::OnMenuAbout() {
	CAboutDlg dlg;
	dlg.DoModal();
}

void CPegsDlg::OnButtonSolve() {
	int from,to;

	if(m_numberPegs==1) {
		return;
	}

	UpdateData(TRUE);

	if(!Solve(m_numberPegs)) {
		MessageBox("This configuration is not solvable.");
		UpdateData(FALSE);
	} else {

		m_moveList.AddString(SOLVE_STRING);

		for(int x=boardSize-m_numberPegs-2;x<boardSize-3;x++) {

			from=GetNumber(moves[x].fromX,moves[x].fromY);
			to=GetNumber(moves[x].toX,moves[x].toY);

			DisplayMove(from-1,to-1);

			UpdateData();
		}

		m_numberPegs=1;
	}

}

void CPegsDlg::OnButtonSelect() {
	if(m_numberPegs!=boardSize-2 || m_moveStatus) {
		OnMenuNew();
	}
	m_moveStatus=2;
	board[GetX(m_empty)][GetY(m_empty)]=1;
	m_spaces[m_empty].SetIcon( \
		ExtractIcon(NULL,ICON_FILE,ICON_PEG));
}

void CPegsDlg::OnClickPiece() {
	const MSG *m=GetCurrentMessage();
	int number=m->wParam-IDC_PIECE;
	int toX,fromX,toY,fromY;

	if(number>boardSize-2) {
		return;
	}

	switch(m_moveStatus) {
	case 0:
		if(board[GetX(number)][GetY(number)]==1) {
			m_spaces[number].SetIcon( \
				ExtractIcon(NULL,ICON_FILE,ICON_MOVING));
			m_moveFrom=number;
			m_moveStatus=1;
		}
		break;
	case 1:
		m_moveTo=number;
		toX=GetX(number);
		toY=GetY(number);
		fromX=GetX(m_moveFrom);
		fromY=GetY(m_moveFrom);
		if(CheckMove(m_moveFrom,m_moveTo)) {
			DisplayMove(m_moveFrom,m_moveTo);

			moves[boardSize-m_numberPegs-2].fromX=fromX;
			moves[boardSize-m_numberPegs-2].toX=toX;
			moves[boardSize-m_numberPegs-2].fromY=fromY;
			moves[boardSize-m_numberPegs-2].toY=toY;

			--m_numberPegs;
		} else {
			m_spaces[m_moveFrom].SetIcon( \
				ExtractIcon(NULL,ICON_FILE,ICON_PEG));
		}
		m_moveStatus=0;

		CheckGameOver();

		break;
	case 2:
		m_empty=number;
		board[GetX(number)][GetY(number)]=0;
		m_spaces[m_empty].SetIcon( \
			ExtractIcon(NULL,ICON_FILE,ICON_EMPTY));
		m_moveStatus=0;
		OnMenuNew();
	}
}

void CPegsDlg::DisplayMove(int from, int to) {
	int middle;
	char temp[3],str[12];

	m_spaces[to].SetIcon( \
		ExtractIcon(NULL,ICON_FILE,ICON_PEG));
	m_spaces[from].SetIcon( \
		ExtractIcon(NULL,ICON_FILE,ICON_EMPTY));
	if(to>from) {
		middle=from+(to-from)/2;
	} else {
		middle=to+(from-to)/2;
	}
	m_spaces[middle].SetIcon( \
		ExtractIcon(NULL,ICON_FILE,ICON_EMPTY));

	board[GetX(from)][GetY(from)]=0;
	board[GetX(to)][GetY(to)]=1;
	if(to>from) {
		middle=from+(to-from)/2;
	} else {
		middle=to+(from-to)/2;
	}
	board[GetX(middle)][GetY(middle)]=0;


	itoa(from+1,temp,10);
	strcpy(str,temp);
	strcat(str," to ");
	itoa(to+1,temp,10);
	strcat(str,temp);
	m_moveList.AddString(str);
}

void CPegsDlg::DrawBoard() {
	const int vertOffset=10;
	const int horzOffset=10;
	int startLocation=88;
	int pieceCount=0;
	int x,y;

	UpdateData(TRUE);

	for(y=0;y<GetY(MAX_BOARD_SIZE-2);y++) {
		for(x=startLocation;x<=startLocation+y*iconSize;x+=iconSize) {
			RECT temp;
			temp.top=vertOffset+y*iconSize;
			temp.bottom=vertOffset+iconSize+y*iconSize;
			temp.left=horzOffset+x;
			temp.right=horzOffset+x+iconSize;
			m_spaces[pieceCount].Create(NULL,SS_NOTIFY|SS_ICON|WS_VISIBLE,temp, \
				m_hWnd,IDC_PIECE+pieceCount);
			++pieceCount;
		}
		startLocation-=iconSize/2;
	}

	UpdateData(FALSE);
}

void CPegsDlg::OnButtonNew() {
	OnMenuNew();
}

void CPegsDlg::OnButtonHint() {
	int x;
	int tempBoard[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

	if(m_numberPegs>1) {

		memcpy(tempBoard,board,sizeof(int)*MAX_MATRIX_SIZE*MAX_MATRIX_SIZE);
		x=Solve(m_numberPegs);
		memcpy(board,tempBoard,sizeof(int)*MAX_MATRIX_SIZE*MAX_MATRIX_SIZE);
		if(!x) {
			MessageBox("This configuration is not solvable.");
			UpdateData(FALSE);
		} else {
			x=boardSize-m_numberPegs-2;
			int from=GetNumber(moves[x].fromX,moves[x].fromY);
			int to=GetNumber(moves[x].toX,moves[x].toY);
			DisplayMove(from-1,to-1);
			--m_numberPegs;
		}
	}
}

void CPegsDlg::OnRadioSize5() {
	boardSize=16;
	OnMenuNew();
}

void CPegsDlg::OnRadioSize6() {
	boardSize=22;
	OnMenuNew();
}

void CPegsDlg::OnButtonUndo() {
	CString str;
	int middle;
	int last=boardSize-m_numberPegs-3;
	int from=GetNumber(moves[last].fromX,moves[last].fromY)-1;
	int to=GetNumber(moves[last].toX,moves[last].toY)-1;

	if(m_numberPegs<boardSize-2) {

		m_spaces[to].SetIcon( \
			ExtractIcon(NULL,ICON_FILE,ICON_EMPTY));
		m_spaces[from].SetIcon( \
			ExtractIcon(NULL,ICON_FILE,ICON_PEG));
		if(to>from) {
			middle=from+(to-from)/2;
		} else {
			middle=to+(from-to)/2;
		}
		m_spaces[middle].SetIcon( \
			ExtractIcon(NULL,ICON_FILE,ICON_PEG));

		board[GetX(from)][GetY(from)]=1;
		board[GetX(to)][GetY(to)]=0;
		if(to>from) {
			middle=from+(to-from)/2;
		} else {
			middle=to+(from-to)/2;
		}
		board[GetX(middle)][GetY(middle)]=1;

		m_moveList.DeleteString(m_moveList.GetCount()-1);

		m_moveList.GetText(m_moveList.GetCount()-1,str);

		if(str==SOLVE_STRING) {
			m_moveList.DeleteString(m_moveList.GetCount()-1);
		}

		++m_numberPegs;
	}
}

void CPegsDlg::CheckGameOver() {
	int possible=0;
	CString message;
	int matrixSize=GetY(boardSize)+1;

	for(int y=1;y<matrixSize;y++) {
		for(int x=1;x<matrixSize;x++) {
			if(board[x][y]==1) {
				if((board[x+1][y]==1 && !board[x+2][y])
					|| (board[x-1][y]==1 && !board[x-2][y])
					|| (board[x][y+1]==1 && !board[x][y+2])
					|| (board[x][y-1]==1 && !board[x][y-2])
					|| (board[x+1][y+1]==1 && !board[x+2][y+2])
					|| (board[x-1][y-1]==1 && !board[x-2][y-2])) {
					++possible;
				}
			}
		}
	}

	if(!possible) {
		if(m_numberPegs==1) {
			message="You Win!\n";
		} else {
			message="Game Over!\n";
		}
		switch(m_numberPegs) {
		case 1:
			message+="IQ: Genius";
			break;
		case 2:
			message+="IQ: Smart";
			break;
		case 3:
			message+="IQ: Average";
			break;
		case 4:
			message+="IQ: Moron";
			break;
		default:
			message+="IQ: Ignoramus";
			break;
		}
		MessageBox(message);
	}
}
