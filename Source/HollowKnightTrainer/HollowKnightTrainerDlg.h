
// HollowKnightTrainerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <mmsystem.h>

#pragma comment( lib, "Winmm.lib" )

#define PLAYERDATA_TAB 0
#define HEROCONTROLLER_TAB 1
#define HEROCONTROLLERSTATES_TAB 2

// CHollowKnightTrainerDlg dialog
class CHollowKnightTrainerDlg : public CDialogEx
{
// Construction
public:
	CHollowKnightTrainerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOLLOWKNIGHTTRAINER_DIALOG };
#endif

	//Here are the timer IDs that represent different timers
	static const UINT_PTR REFRESH_TIMER = 0x1111;
	static const UINT_PTR HP_LOCK_TIMER = 0x2222;
	static const UINT_PTR MP_LOCK_TIMER = 0x3333;
	static const UINT_PTR MONEY_LOCK_TIMER = 0x4444;
	static const UINT_PTR INVULNERABLE_TIMER = 0x5555;
	static const UINT_PTR DOUBLEJUMP_LOCK_TIMER = 0x6666;
	static const UINT_PTR UNLIMITED_CHARMS_TIMER = 0x7777;
	static const UINT_PTR UNLIMITEDJUMP_TIMER = 0x8888;


	static const UINT_PTR INIT_HOTKEY = 0;
	static const UINT_PTR HP_HOTKEY = 1;
	static const UINT_PTR MP_HOTKEY = 2;
	static const UINT_PTR MONEY_HOTKEY = 3;
	static const UINT_PTR INVULNERABLE_HOTKEY= 4;
	static const UINT_PTR CHARMS_HOTKEY = 5;
	static const UINT_PTR DOUBLEJUMP_HOTKEY = 6;
	static const UINT_PTR JUMP_HOTKEY = 7;


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int m_Col=-1;
	int m_Row = -1;
	int m_selectedTabNumber = 0;
	int searchBase = 0;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void InitHotKeys();
	afx_msg void InitTAB();
	afx_msg void InitList();
	afx_msg void ShowList(int selectedTabNumber);
	afx_msg void ReadListData();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAboutButton();
	afx_msg void OnBnClickedInitializeButton();
	CString strSearchKeyWord;
	CString strAddressString;
	CString strProcessAddressString;
	afx_msg void OnBnClickedResetButton();
	DWORD dwHpValue;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton lockHpCheck;
	afx_msg void OnBnClickedLockHp();
	DWORD mpValue;
	DWORD moneyValue;
	afx_msg void OnBnClickedWriteMoneyButton();
	afx_msg void OnBnClickedLockMp();
	CButton lockMpCheck;
	CButton lockMoneyCheck;
	afx_msg void OnBnClickedLockMoney();
	CButton lockInvulnerable;
	afx_msg void OnBnClickedInvulnerable();
	CButton lockDoubleJump;
	afx_msg void OnBnClickedUnlimitedDoublejump();
	CListCtrl mainList;
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit listEdit;
	afx_msg void OnEnKillfocusListEdit();
	virtual void OnOK();
	CButton listEditCheck;
	afx_msg void OnBnClickedlistEditCheck();
	CEdit listSearchEdit;
	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedUnlimitedCharms();
	CButton lockCharms;
	CTabCtrl tabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton unlimitedJumpCheck;
	afx_msg void OnBnClickedUnlimitedJump();
	afx_msg long OnHotKey(WPARAM wParam, LPARAM lParam);
};
