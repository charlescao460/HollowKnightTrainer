
// HollowKnightTrainerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HollowKnightTrainer.h"
#include "HollowKnightTrainerDlg.h"
#include "afxdialogex.h"
#include "Trainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHollowKnightTrainerDlg dialog



CHollowKnightTrainerDlg::CHollowKnightTrainerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOLLOWKNIGHTTRAINER_DIALOG, pParent)
	, strAddressString(_T(""))
	, strProcessAddressString(_T(""))
	, dwHpValue(0)
	, mpValue(0)
	, moneyValue(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHollowKnightTrainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Address, strAddressString);
	DDX_Text(pDX, IDC_PROCESS_ADDRESS, strProcessAddressString);
	DDX_Text(pDX, IDC_HP_VALUE, dwHpValue);
	DDX_Control(pDX, IDC_LOCK_HP, lockHpCheck);
	DDX_Text(pDX, IDC_MP_VALUE, mpValue);
	DDX_Text(pDX, IDC_MONEY_VALUE, moneyValue);
	DDX_Control(pDX, IDC_LOCK_MP, lockMpCheck);
	DDX_Control(pDX, IDC_LOCK_MONEY, lockMoneyCheck);
	DDX_Control(pDX, IDC_INVULNERABLE, lockInvulnerable);
	DDX_Control(pDX, IDC_UNLIMITED_DOUBLEJUMP, lockDoubleJump);
	DDX_Control(pDX, IDC_LIST3, mainList);
	DDX_Control(pDX, IDC_LIST_EDIT, listEdit);
	DDX_Control(pDX, IDC_LISTEDIT_CHECK, listEditCheck);
	DDX_Control(pDX, IDC_SEARCH_EDIT, listSearchEdit);
	DDX_Control(pDX, IDC_UNLIMITED_CHARMS, lockCharms);
	DDX_Control(pDX, IDC_TAB1, tabCtrl);
	DDX_Control(pDX, IDC_UNLIMITEDJUMP, unlimitedJumpCheck);
}

BEGIN_MESSAGE_MAP(CHollowKnightTrainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDM_ABOUT_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedAboutButton)
	ON_BN_CLICKED(IDC_INITIALIZE_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedInitializeButton)
	ON_BN_CLICKED(IDC_RESET_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedResetButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LOCK_HP, &CHollowKnightTrainerDlg::OnBnClickedLockHp)
	ON_BN_CLICKED(IDC_WRITE_MONEY_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedWriteMoneyButton)
	ON_BN_CLICKED(IDC_LOCK_MP, &CHollowKnightTrainerDlg::OnBnClickedLockMp)
	ON_BN_CLICKED(IDC_LOCK_MONEY, &CHollowKnightTrainerDlg::OnBnClickedLockMoney)
	ON_BN_CLICKED(IDC_INVULNERABLE, &CHollowKnightTrainerDlg::OnBnClickedInvulnerable)
	ON_BN_CLICKED(IDC_UNLIMITED_DOUBLEJUMP, &CHollowKnightTrainerDlg::OnBnClickedUnlimitedDoublejump)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CHollowKnightTrainerDlg::OnNMDblclkList3)
	ON_EN_KILLFOCUS(IDC_LIST_EDIT, &CHollowKnightTrainerDlg::OnEnKillfocusListEdit)
	ON_BN_CLICKED(IDC_LISTEDIT_CHECK, &CHollowKnightTrainerDlg::OnBnClickedlistEditCheck)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedRefreshButton)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, &CHollowKnightTrainerDlg::OnBnClickedSearchButton)
	ON_BN_CLICKED(IDC_UNLIMITED_CHARMS, &CHollowKnightTrainerDlg::OnBnClickedUnlimitedCharms)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CHollowKnightTrainerDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_UNLIMITEDJUMP, &CHollowKnightTrainerDlg::OnBnClickedUnlimitedJump)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
END_MESSAGE_MAP()


// CHollowKnightTrainerDlg message handlers

BOOL CHollowKnightTrainerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	CHollowKnightTrainerDlg::InitList();
	CHollowKnightTrainerDlg::ShowList(0);
	CHollowKnightTrainerDlg::InitTAB();
	CHollowKnightTrainerDlg::InitHotKeys();
	CHollowKnightTrainerDlg::OnBnClickedAboutButton();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHollowKnightTrainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHollowKnightTrainerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHollowKnightTrainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void  CHollowKnightTrainerDlg::InitHotKeys()
{
	RegisterHotKey(m_hWnd, INIT_HOTKEY, NULL, VK_F11);
	RegisterHotKey(m_hWnd, HP_HOTKEY, NULL, VK_F1);
	RegisterHotKey(m_hWnd, MP_HOTKEY, NULL, VK_F2);
	RegisterHotKey(m_hWnd, MONEY_HOTKEY, NULL, VK_F3);
	RegisterHotKey(m_hWnd, INVULNERABLE_HOTKEY, NULL, VK_F4);
	RegisterHotKey(m_hWnd, CHARMS_HOTKEY, NULL, VK_F5);
	RegisterHotKey(m_hWnd, DOUBLEJUMP_HOTKEY, NULL, VK_F6);
	RegisterHotKey(m_hWnd, JUMP_HOTKEY, NULL, VK_F7);
}

void CHollowKnightTrainerDlg::InitTAB()
{
	tabCtrl.InsertItem(PLAYERDATA_TAB, _T("玩家数据类PlayerData"));
	tabCtrl.InsertItem(HEROCONTROLLER_TAB, _T("角色控制类HeroController"));
	tabCtrl.InsertItem(HEROCONTROLLERSTATES_TAB, _T("控制状态类HeroControllerStates"));
}

void CHollowKnightTrainerDlg::InitList()
{
	listEdit.ShowWindow(SW_HIDE);
	mainList.DeleteAllItems();
	mainList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_GRIDLINES| LVS_EX_DOUBLEBUFFER| LVS_EX_FLATSB);
	mainList.InsertColumn(0, _T("偏移Offset"), LVCFMT_LEFT, 120);
	mainList.InsertColumn(1, _T("名称Name"), LVCFMT_LEFT, 250);
	mainList.InsertColumn(2, _T("类型Type"), LVCFMT_LEFT, 200);
	mainList.InsertColumn(3, _T("值Value"), LVCFMT_LEFT, 200);
}

void CHollowKnightTrainerDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	m_selectedTabNumber = tabCtrl.GetCurSel();
	CHollowKnightTrainerDlg::ShowList(m_selectedTabNumber);
	CHollowKnightTrainerDlg::ReadListData();

	*pResult = 0;
}

//This function load PlayerDataOffsets.txt from Resource into mainList ListCtrl
void CHollowKnightTrainerDlg::ShowList(int selectedTabNumber)
{
	mainList.DeleteAllItems();
	//Find .txt files from Resource and assign to CString strResourceData;
	HRSRC hResource=NULL;
	switch (selectedTabNumber)
	{
	case PLAYERDATA_TAB:
	{
		hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_TXT1), _T("txt"));
		break;
	}
	case HEROCONTROLLER_TAB:
	{
		hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_TXT2), _T("txt"));
		break;
	}
	case HEROCONTROLLERSTATES_TAB:
	{
		hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_TXT3), _T("txt"));
		break;
	}
	default:
		break;
	}
	
	if (hResource == NULL)
	{
		CTrainer::ReportError(_T("find resource"));
		return;
	}
	//DWORD dwResourceSize = SizeofResource(NULL, hResource);
	HGLOBAL hGlobal = LoadResource(NULL, hResource);
	if (hGlobal == NULL)
	{
		CTrainer::ReportError(_T("find resource"));
		return;
	}
	LPVOID pResource = LockResource(hGlobal);
	if(pResource==NULL)
	{
		CTrainer::ReportError(_T("lock resource"));
		return;
	}
	CString strResourceData;
	strResourceData.Format(_T("%s"), pResource);
	

	int columnIndex = 0;
	int newLineIndex = 0;
	int colonIndex = 0;
	int typeIndex = 0;
	int leftBracketIndex = 0;
	int rightBracketIndex = 0;
	CString offset;
	CString name;
	CString type;
	do 
	{
		//find the indexes of key char
		colonIndex = strResourceData.Find(L':');
		leftBracketIndex = strResourceData.Find(L'(');
		typeIndex = strResourceData.Find(_T("type:"));
		rightBracketIndex = strResourceData.Find(L')');
		newLineIndex = strResourceData.Find(L'\n');
		if(newLineIndex==-1)
		{
			newLineIndex = strResourceData.Find(L'\0');
		}

		//find the substring of key information
		offset = strResourceData.Mid(0,colonIndex);
		name = strResourceData.Mid(colonIndex + 1, leftBracketIndex - colonIndex - 1);
		type = strResourceData.Mid(typeIndex + 5, rightBracketIndex - typeIndex - 5);

		//delete the column that already been read.  
		strResourceData = strResourceData.Mid(newLineIndex + 1, strResourceData.GetLength() - newLineIndex);

		mainList.InsertItem(columnIndex, offset);
		mainList.SetItemText(columnIndex, 1, name);
		mainList.SetItemText(columnIndex, 2, type);
		columnIndex++;

	} while (!strResourceData.IsEmpty());
	
	//GetDlgItem(IDC_LIST3)->EnableWindow(FALSE);
}

//This function get the offset from mainList and read data and show in the mainList
void CHollowKnightTrainerDlg::ReadListData()
{
	if (!bActivated)
		return;
	int columnIndex = 0;
	CString offset;
	CString type;
	CString value;

	do
	{
		offset = mainList.GetItemText(columnIndex, 0);
		type = mainList.GetItemText(columnIndex, 2);
		value = CTrainer::ReadListData(offset, type,m_selectedTabNumber);
		mainList.SetItemText(columnIndex, 3, value);
		columnIndex++;
	} while (!mainList.GetItemText(columnIndex,0).IsEmpty());
}

void CHollowKnightTrainerDlg::OnBnClickedRefreshButton()
{
		CHollowKnightTrainerDlg::ReadListData();
}

void CHollowKnightTrainerDlg::OnBnClickedSearchButton()
{
	mainList.SetItemState(mainList.GetSelectedColumn(), 0, LVIS_SELECTED | LVIS_FOCUSED);
	listSearchEdit.SetFocus();
	CString newKeyWord;
	int columnIndex=searchBase;
	int searchResultIndex = 0;
	listSearchEdit.GetWindowText(newKeyWord);
	if (newKeyWord != strSearchKeyWord) // if key word changes
	{
		strSearchKeyWord = newKeyWord;
		searchBase = 0;
	}
	do {
		if(CTrainer::CStringFindNoCase(mainList.GetItemText(columnIndex,1),newKeyWord)!=-1)//if keyword is included
		{
			searchResultIndex = columnIndex;
			break;
		}
		columnIndex++;
	} while (!mainList.GetItemText(columnIndex, 0).IsEmpty());
	searchBase = searchResultIndex+1;//next time start at next column
	mainList.SetItemState(searchResultIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	mainList.EnsureVisible(searchResultIndex, FALSE);
	mainList.SetFocus();
}

void CHollowKnightTrainerDlg::OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (listEditCheck.GetCheck()) 
	{
		CRect rc;
		m_Row = pNMItemActivate->iItem;//get selected row 
		m_Col = pNMItemActivate->iSubItem;//get selected coloum


		if (pNMItemActivate->iSubItem == 3) //if selected Value row
		{
			mainList.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//get subItem's Rect
			listEdit.SetParent(&mainList);//set parent of listEdit
			listEdit.MoveWindow(rc);//move listEdit to Rect position 
			listEdit.SetWindowText(mainList.GetItemText(m_Row, m_Col));//put the subItem's value into listEdit
			listEdit.ShowWindow(SW_SHOW);//show listEdit
			listEdit.SetFocus();
			listEdit.ShowCaret();
			listEdit.SetSel(-1);//set caret to the end
		}
	}
	*pResult = 0;
}


void CHollowKnightTrainerDlg::OnEnKillfocusListEdit()
{
	CString type;
	CString offset;
	CString newValue;
	
	offset = mainList.GetItemText(m_Row, 0);
	type = mainList.GetItemText(m_Row, 2);
	listEdit.GetWindowText(newValue);//get newValue from listEdit
	CTrainer::WriteListData(offset, type, newValue,m_selectedTabNumber);//write new value;
	CHollowKnightTrainerDlg::ReadListData();//refresh list
	listEdit.ShowWindow(SW_HIDE);//hide listEidt
}


HRESULT CHollowKnightTrainerDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam != INIT_HOTKEY && !bActivated)
		return TRUE;
	switch (wParam)
	{
	case INIT_HOTKEY:
	{
		if (!bActivated) 
		{
			CHollowKnightTrainerDlg::OnBnClickedInitializeButton();
			PlaySound(MAKEINTRESOURCE(IDC_WAVE_ACTIVATE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		}
		else
		{
			CHollowKnightTrainerDlg::OnBnClickedResetButton();
			PlaySound(MAKEINTRESOURCE(IDC_WAVE_RESET), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		}
		break;
	}
	case HP_HOTKEY:
	{
		lockHpCheck.GetCheck() ? lockHpCheck.SetCheck(FALSE) : lockHpCheck.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedLockHp();
		DWORD idWAVE = lockHpCheck.GetCheck() ? IDC_WAVE_HPON : IDC_WAVE_HPOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case MP_HOTKEY:
	{
		lockMpCheck.GetCheck() ? lockMpCheck.SetCheck(FALSE) : lockMpCheck.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedLockMp();
		DWORD idWAVE = lockMpCheck.GetCheck() ? IDC_WAVE_MPON : IDC_WAVE_MPOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case MONEY_HOTKEY:
	{
		lockMoneyCheck.GetCheck() ? lockMoneyCheck.SetCheck(FALSE) : lockMoneyCheck.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedLockMoney();
		DWORD idWAVE = lockMoneyCheck.GetCheck() ? IDC_WAVE_MONEYON : IDC_WAVE_MONEYOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case INVULNERABLE_HOTKEY:
	{
		lockInvulnerable.GetCheck() ? lockInvulnerable.SetCheck(FALSE) : lockInvulnerable.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedInvulnerable();
		DWORD idWAVE = lockInvulnerable.GetCheck() ? IDC_WAVE_INVULNERABLEON : IDC_WAVE_INVULNERABLEOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case CHARMS_HOTKEY:
	{
		lockCharms.GetCheck() ? lockCharms.SetCheck(FALSE) : lockCharms.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedUnlimitedCharms();
		DWORD idWAVE = lockCharms.GetCheck() ? IDC_WAVE_CHARMSON : IDC_WAVE_CHARMSOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case DOUBLEJUMP_HOTKEY:
	{
		lockDoubleJump.GetCheck() ? lockDoubleJump.SetCheck(FALSE) : lockDoubleJump.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedUnlimitedDoublejump();
		DWORD idWAVE = lockDoubleJump.GetCheck() ? IDC_WAVE_DOUBLEJUMPON : IDC_WAVE_DOUBLEJUMPOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	case JUMP_HOTKEY:
	{	
		unlimitedJumpCheck.GetCheck() ? unlimitedJumpCheck.SetCheck(FALSE) : unlimitedJumpCheck.SetCheck(TRUE);
		CHollowKnightTrainerDlg::OnBnClickedUnlimitedJump();
		DWORD idWAVE = unlimitedJumpCheck.GetCheck() ? IDC_WAVE_JUMPON : IDC_WAVE_JUMPOFF;
		PlaySound(MAKEINTRESOURCE(idWAVE), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
		break;
	}
	default:
		break;
	}
	return TRUE;
}



void CHollowKnightTrainerDlg::OnBnClickedAboutButton()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CHollowKnightTrainerDlg::OnBnClickedInitializeButton()
{
	if (!CTrainer::Initialize())
		return;

	if(!SetTimer(REFRESH_TIMER,500,NULL))//set a timer to refresh data in every 500ms
	{
	CTrainer::ReportError(_T("set timer"));
	}
	bActivated = TRUE;

	//Enable and Disable controls
	GetDlgItem(IDC_INITIALIZE_BUTTON)->EnableWindow(FALSE); 
	GetDlgItem(IDC_RESET_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_WRITE_MONEY_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_LOCK_HP)->EnableWindow(TRUE);
	GetDlgItem(IDC_LOCK_MP)->EnableWindow(TRUE);
	GetDlgItem(IDC_LOCK_MONEY)->EnableWindow(TRUE);
	GetDlgItem(IDC_INVULNERABLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNLIMITED_DOUBLEJUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNLIMITED_CHARMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNLIMITEDJUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_LISTEDIT_CHECK)->EnableWindow(TRUE);
	GetDlgItem(IDC_REFRESH_BUTTON)->EnableWindow(TRUE);
	//SendDlgItemMessage(IDC_MONEY_VALUE, EM_SETREADONLY, FALSE);



	strAddressString.Format(_T("0x%08x"), dwObjectClassBaseAddress);	//assign address to edit control's CString variable
	strProcessAddressString.Format(_T("0x%08x"),dwProcessBaseAddress);
	CHollowKnightTrainerDlg::ReadListData();
	UpdateData(FALSE);//update base address to the edit control
	
}



void CHollowKnightTrainerDlg::OnBnClickedResetButton()
{
	//cancel all the check and their function
	lockHpCheck.SetCheck(FALSE);
	lockMpCheck.SetCheck(FALSE);
	lockMoneyCheck.SetCheck(FALSE);
	lockInvulnerable.SetCheck(FALSE);
	lockDoubleJump.SetCheck(FALSE);
	listEditCheck.SetCheck(FALSE);
	lockCharms.SetCheck(FALSE);
	unlimitedJumpCheck.SetCheck(FALSE);
	
	CHollowKnightTrainerDlg::OnBnClickedLockHp();
	CHollowKnightTrainerDlg::OnBnClickedLockMp();
	CHollowKnightTrainerDlg::OnBnClickedLockMoney();
	CHollowKnightTrainerDlg::OnBnClickedInvulnerable();
	CHollowKnightTrainerDlg::OnBnClickedUnlimitedDoublejump();
	CHollowKnightTrainerDlg::OnBnClickedUnlimitedCharms();
	CHollowKnightTrainerDlg::OnBnClickedUnlimitedJump();

	//reset imformation in edit control
	strAddressString.Format(_T("0x%08x"), 0);
	strProcessAddressString.Format(_T("0x%08x"), 0);
	dwHpValue = 0;
	mpValue = 0;
	moneyValue = 0;
	//close handle
	CloseHandle(hProcess);
	//Enable and Disable controls
	GetDlgItem(IDC_INITIALIZE_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_RESET_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_WRITE_MONEY_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOCK_HP)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOCK_MP)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOCK_MONEY)->EnableWindow(FALSE);
	GetDlgItem(IDC_INVULNERABLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNLIMITED_DOUBLEJUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNLIMITED_CHARMS)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNLIMITEDJUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEDIT_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH_BUTTON)->EnableWindow(FALSE);

	bActivated = FALSE;


	UpdateData(FALSE);
}

//Different Timer: 
void CHollowKnightTrainerDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case REFRESH_TIMER:
	{	
		//refresh data
		dwHpValue = CTrainer::GetHpValue();
		mpValue = CTrainer::GetMpValue();
		moneyValue = CTrainer::GetMoneyValue();
		UpdateData(FALSE);
		break;
	}

	case HP_LOCK_TIMER:
	{
		CTrainer::SetBlueHpValue(3);
		break;
	}

	case MP_LOCK_TIMER:
	{
		CTrainer::SetMpValue(100);
		break;
	}

	case MONEY_LOCK_TIMER:
	{
		CTrainer::SetMoneyValue(dwOriginalMoney);
		break;
	}

	case INVULNERABLE_TIMER:
	{
		CTrainer::SetInvulnerable(TRUE);
		break;
	}

	case DOUBLEJUMP_LOCK_TIMER:
	{
		CTrainer::SetUnlimitedDoubleJump(TRUE);
		break;
	}

	case UNLIMITED_CHARMS_TIMER:
	{
		CTrainer::SetCharmSlotsFilled(0);
		break;
	}
	case UNLIMITEDJUMP_TIMER:
	{
		CTrainer::SetUnlimitedJump(1);
		break;
	}

	default: break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


//LOCK HP Checkbox
void CHollowKnightTrainerDlg::OnBnClickedLockHp()
{
	if (lockHpCheck.GetCheck())
	{
		SetTimer(HP_LOCK_TIMER, 500, NULL);//set a timer to write HP's value every 500ms
	}
	else
	{
		KillTimer(HP_LOCK_TIMER);//delete the timer
		CTrainer::SetBlueHpValue(0);
	}
}


void CHollowKnightTrainerDlg::OnBnClickedWriteMoneyButton()
{
	//add 500 to money
	if (!CTrainer::SetMoneyValue(CTrainer::GetMoneyValue()+500))
	{
		CTrainer::ReportError(_T("write money's value"));
	}
}


void CHollowKnightTrainerDlg::OnBnClickedLockMp()
{
	if (lockMpCheck.GetCheck())
	{
		SetTimer(MP_LOCK_TIMER, 500, NULL);
	}
	else
	{
		KillTimer(MP_LOCK_TIMER);
	}
}


void CHollowKnightTrainerDlg::OnBnClickedLockMoney()
{
	if(lockMoneyCheck.GetCheck())
	{
		GetDlgItem(IDC_WRITE_MONEY_BUTTON)->EnableWindow(FALSE);
		dwOriginalMoney = CTrainer::GetMoneyValue();
		SetTimer(MONEY_LOCK_TIMER, 500, NULL);
	}
	else
	{
		GetDlgItem(IDC_WRITE_MONEY_BUTTON)->EnableWindow(TRUE);
		if(dwOriginalMoney!=0)
			CTrainer::SetMoneyValue(dwOriginalMoney);
		KillTimer(MONEY_LOCK_TIMER);
	}
}


void CHollowKnightTrainerDlg::OnBnClickedInvulnerable()
{
	if(lockInvulnerable.GetCheck())
	{
		SetTimer(INVULNERABLE_TIMER, 500, NULL);
	}
	else
	{
		KillTimer(INVULNERABLE_TIMER);
		CTrainer::SetInvulnerable(FALSE);
	}
}


void CHollowKnightTrainerDlg::OnBnClickedUnlimitedDoublejump()
{
	if(lockDoubleJump.GetCheck())
	{
		SetTimer(DOUBLEJUMP_LOCK_TIMER, 50, NULL);
	}
	else
	{
		KillTimer(DOUBLEJUMP_LOCK_TIMER);
	}

}

void CHollowKnightTrainerDlg::OnBnClickedUnlimitedCharms()
{
	if (lockCharms.GetCheck())
	{
		SetTimer(UNLIMITED_CHARMS_TIMER, 50, NULL);
	}
	else
	{
		KillTimer(UNLIMITED_CHARMS_TIMER);
	}
}


void CHollowKnightTrainerDlg::OnBnClickedUnlimitedJump()
{
	if (unlimitedJumpCheck.GetCheck())
	{
		SetTimer(UNLIMITEDJUMP_TIMER, 500, NULL);
	} 
	else
	{
		KillTimer(UNLIMITEDJUMP_TIMER);
		CTrainer::SetUnlimitedJump(0);
	}
}


//Override OnOK() so it will not close by Enter
void CHollowKnightTrainerDlg::OnOK()
{
	mainList.SetFocus();
	//CDialogEx::OnOK();
}


void CHollowKnightTrainerDlg::OnBnClickedlistEditCheck()
{
	int result;
	result = ::MessageBox(
		NULL,
		_T("修改以下列表数据有可能会导致游戏崩溃，修改部分数据将会使您的游戏体验大幅下降。请在修改前备份好存档！\n要继续吗？\nModifying ListData could cause unexpected error during gaming, and you may lose pleasure from the game. Please backup your save files before you modify ListData.\nDo you still want to activate?"),
		_T("警告Warning"),
		MB_OKCANCEL | MB_ICONWARNING
	);
	if (result == 2)//if user selects "cancel" button
	{
		listEditCheck.SetCheck(FALSE);
	}
	else
	{
	::MessageBox(NULL, _T("现在你可以双击列表中的单元格来修改数值了。\nNow you can modify ListData by double-clicking the cells in Value row"), _T("成功！Success!"), MB_ICONINFORMATION);
	}

	
}









