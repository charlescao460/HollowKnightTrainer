#pragma once
#ifndef TRAINER_H
#define TRAINER_H
#endif

extern DWORD dwHeroControllerClassBaseAddress;
extern DWORD dwHeroControllerStatesClassBaseAddress;
extern DWORD dwObjectClassBaseAddress;
extern DWORD dwPlayerDataBaseAddress;
extern DWORD dwProcessBaseAddress;

extern DWORD dwPID;
extern HANDLE hProcess;
extern BOOL bActivated;

extern DWORD dwOriginalMoney;

class CTrainer
{
public:

	CTrainer();
	static bool Initialize(void);
	static DWORD GetObjectClassBaseAddress(HANDLE handle, DWORD processBaseAddress);
	static DWORD GetPlayerDataBaseAddress(HANDLE hProcess, DWORD dwObjectClassBaseAddress);
	static DWORD GetHeroControllerClassBaseAddress(HANDLE hProcess, DWORD dwObjectClassBaseAddress);
	static DWORD GetdwHeroControllerStatesClassBaseAddress(HANDLE hProcess, DWORD dwObjectClassBaseAddress);
	static DWORD GetProcessBaseAddress(DWORD pid);
	static DWORD GetHpValue(void);
	static DWORD GetMpValue(void);
	static DWORD GetMoneyValue(void);
	static bool SetHpValue(DWORD dwHP);
	static bool SetBlueHpValue(DWORD dwBHP);
	static bool SetMpValue(DWORD dwMP);
	static bool SetMoneyValue(DWORD dwMoney);
	static bool SetInvulnerable(BOOL checked);
	static bool SetUnlimitedDoubleJump(BOOL checked);
	static bool SetCharmSlotsFilled(DWORD dwSlots);
	static bool SetUnlimitedJump(BOOL checked);
	static void WriteListData(CString offset, CString type, CString newValue,  int curSelTab);
	static CString ReadListData(CString offset, CString type, int curSelTab);
	static DWORD CStringToHex(CString str);
	static VOID ReportError(CString operation);
	static int CStringFindNoCase(CString str, CString keyWords);
	~CTrainer();
};

