#include "stdafx.h"
#include "Trainer.h"
#include <tlhelp32.h>
#include <tchar.h>
#include"HollowKnightTrainerDlg.h"

//Extern variables for base addresses
DWORD dwObjectClassBaseAddress = NULL;
DWORD dwPlayerDataBaseAddress=NULL;
DWORD dwHeroControllerClassBaseAddress = NULL;
DWORD dwHeroControllerStatesClassBaseAddress = NULL;
DWORD dwProcessBaseAddress = NULL;
//Variables dealing with process
DWORD dwPID = 0;
HANDLE hProcess = NULL;
BOOL bActivated = FALSE;
//Variables for game data
DWORD dwOriginalMoney = 0;
//Here is the offsets:
static const DWORD FIRST_OFFSET = 0x00FAE7B0;
static const DWORD SECOND_OFFSET = 0xD0;
static const DWORD THIRD_OFFSET = 0x3C;
static const DWORD FOURTH_OFFSET = 0x14;

static const DWORD PLAYERDATA_OFFSET = 0x28;
static const DWORD HP_OFFSET = 0x74;
static const DWORD MP_OFFSET = 0xB0;
static const DWORD MONEY_OFFSET = 0xA8;
static const DWORD BLUEHP_OFFSET = 0x80;
static const DWORD CHARMS_SLOTS_FILLED_OFFSET = 0x3A8;
static const DWORD AIR_JUMP_OFFSET = 0xA78;

static const DWORD HEREOCONTROLLER_OFFSET = 0x20;
static const DWORD DOUBLEJUMPED_OFFSET = 0x4BF;
static const DWORD SHADOWDASHCOOLDOWN_OFFSET = 0x258;//float


static const DWORD HEREOCONTROLLERSTATES_OFFSET = 0x24;
static const DWORD INVULNERABLE_OFFSET = 0x2A;





CTrainer::CTrainer()
{
}

bool CTrainer::Initialize(void)
{
	HWND hwGame = FindWindowA(NULL, "Hollow Knight");//Get game window's handle
	if (hwGame == NULL)
	{
		CTrainer::ReportError(_T("find game's window"));
		return 0;
	}
	GetWindowThreadProcessId(hwGame, &dwPID); //get game's process id
	if (dwPID == 0)
	{
		CTrainer::ReportError(_T("get PID"));
		return 0;
	}
	dwProcessBaseAddress = CTrainer::GetProcessBaseAddress(dwPID);
	if (dwProcessBaseAddress == NULL)
	{
		CTrainer::ReportError(_T("find process base address"));
		return 0;
	}
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);// Using Windows API OpenProcess function to access game's memory and get process's handle
	if (hProcess == NULL)
	{
		CTrainer::ReportError(_T("open process"));
		return 0;
	}
	dwObjectClassBaseAddress = CTrainer::GetObjectClassBaseAddress(hProcess, dwProcessBaseAddress); // storing character object's base address for later use
	if (dwObjectClassBaseAddress == NULL)
	{
		CTrainer::ReportError(_T("reading memory"));
		return 0;
	}
	dwPlayerDataBaseAddress = CTrainer::GetPlayerDataBaseAddress(hProcess, dwObjectClassBaseAddress);
	dwHeroControllerClassBaseAddress = CTrainer::GetHeroControllerClassBaseAddress(hProcess, dwObjectClassBaseAddress);
	dwHeroControllerStatesClassBaseAddress = CTrainer::GetdwHeroControllerStatesClassBaseAddress(hProcess, dwObjectClassBaseAddress);
	
	return 1;
}



//This function uses Snapshot to find out the processs's base address.
DWORD CTrainer::GetProcessBaseAddress(DWORD pid)
{
	DWORD dwResult = NULL;
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	TCHAR szGameModule[MAX_MODULE_NAME32 + 1] = _T("hollow_knight.exe");

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);// Take a snapshot of game's processes.
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		CTrainer::ReportError(_T("creat process's snapshot"));
		return NULL;
	}
	me32.dwSize = sizeof(MODULEENTRY32);// Set the size of the structure before using it.
	if (!Module32First(hModuleSnap, &me32))//Strat to retrieves information about the first module
	{
		CTrainer::ReportError(_T("retrieve first module"));
		CloseHandle(hModuleSnap);
		return NULL;
	}
	// Traverse each module to find out base addresss of processs hollow_knight.exe 
	do {
		if (_tccmp(szGameModule, me32.szModule) == 0) //if module name is "hollow_knight.exe"
		{
			dwResult = (DWORD)me32.modBaseAddr;//assign the address of "hollow_knight.exe" to dwResult
			break;
		}
	} while (Module32Next(hModuleSnap, &me32));
	if (dwResult == NULL)
	{
		CTrainer::ReportError(_T("find hollow_knight.exe"));
		CloseHandle(hModuleSnap);
		return NULL;
	}
	CloseHandle(hModuleSnap);
	return dwResult;
}

//This function can get the System.Object instance's base address
DWORD CTrainer::GetObjectClassBaseAddress(HANDLE hProcess,DWORD processBaseAddress)
{
	DWORD dwAddress = FIRST_OFFSET +processBaseAddress;//initial value is the sum of base address and first offset we have found in Cheat Engine
	DWORD dwReadingResult=NULL;//temporary variable to store reading result

	if (!ReadProcessMemory(hProcess,(LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL)|| dwReadingResult==NULL)
	{
		CTrainer::ReportError(_T("read memory"));
		return NULL;
	}
	dwAddress = dwReadingResult + SECOND_OFFSET;//using memory reading result and offset 0xD0 to calculate next pointer
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
	dwAddress = dwReadingResult + THIRD_OFFSET;//using offset 0x3C to caculate next pointer
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
	dwAddress = dwReadingResult + FOURTH_OFFSET;//using offset 0x14 to caculate next pointer
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);

	return dwReadingResult;
}

//Calculate and read PlayerData class instance's base address 
DWORD CTrainer::GetPlayerDataBaseAddress(HANDLE hProcess, DWORD dwObjectClassBaseAddress)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwObjectClassBaseAddress+ PLAYERDATA_OFFSET;
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
	
	return dwReadingResult;
}

//Calculate and read HeroController class instance's base address
DWORD CTrainer::GetHeroControllerClassBaseAddress(HANDLE hProcess, DWORD dwObjectClassBaseAddress)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwObjectClassBaseAddress + HEREOCONTROLLER_OFFSET;
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);

	return dwReadingResult;
}

//Calculate and read HeroControllerStates class instance's base address
DWORD CTrainer::GetdwHeroControllerStatesClassBaseAddress(HANDLE hProcess,DWORD dwObjectClassBaseAddress)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwObjectClassBaseAddress + HEREOCONTROLLERSTATES_OFFSET;
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);

	return dwReadingResult;
}

//This function read memory and return HP's value
DWORD CTrainer::GetHpValue(void)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwPlayerDataBaseAddress + HP_OFFSET;//using HP's offset to calculate it's address
	ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
		return dwReadingResult;
}

//This function read moemory and return MP's value
DWORD CTrainer::GetMpValue(void)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwPlayerDataBaseAddress + MP_OFFSET;//using MP's offset to calculate it's address
	ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
	return dwReadingResult;
}

//This function read memory and return money's value
DWORD CTrainer::GetMoneyValue(void)
{
	DWORD dwReadingResult = 0;
	DWORD dwAddress = dwPlayerDataBaseAddress + MONEY_OFFSET;//using money's offset to calculate it's address
	ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
	return dwReadingResult;
}

//This function write memory to change HP's value
//This function is abandoned
bool CTrainer::SetHpValue(DWORD dwHP)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + HP_OFFSET;//using HP's offset to calculate it's address
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwHP, sizeof(DWORD), NULL))
		return 1;
	else
		return 0;
}

//This function write memory to change extra HP (blue HP) 's value. using to lock hp
bool CTrainer::SetBlueHpValue(DWORD dwBHP)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + BLUEHP_OFFSET;//using HP's offset to calculate it's address
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwBHP, sizeof(DWORD), NULL))
		return 1;
	else
		return 0;
}

//This function write memory to change MP's value
bool CTrainer::SetMpValue(DWORD dwMP)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + MP_OFFSET;//using MP's offset to calculate it's address
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwMP, sizeof(DWORD), NULL))
		return 1;
	else
		return 0;
}

//This function write memory to change money's value
bool CTrainer::SetMoneyValue(DWORD dwMoney)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + MONEY_OFFSET;//using money's offset to calculate it's address
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwMoney, sizeof(DWORD), NULL))
		return 1;
	else
		return 0;
}

//Write memory to set the status of invulnerable
bool CTrainer::SetInvulnerable(BOOL checked)
{
	DWORD dwAddress = dwHeroControllerStatesClassBaseAddress + INVULNERABLE_OFFSET;
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &checked, sizeof(BOOL), NULL))
		return 1;
	else
		return 0;
}

//Set Double Jump step count to 0 so we can do double jump again and again
bool CTrainer::SetUnlimitedDoubleJump(BOOL checked)
{
	BOOL write = !checked;
	DWORD dwAddress = dwHeroControllerClassBaseAddress + DOUBLEJUMPED_OFFSET;
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &write, sizeof(BOOL), NULL))
		return 1;
	else
		return 0;
}

//set Charm Slots Filled to 0 so we can equip as much charms as we want
bool CTrainer::SetCharmSlotsFilled(DWORD dwSlots)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + CHARMS_SLOTS_FILLED_OFFSET;
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwSlots, sizeof(DWORD), NULL))
		return 1;
	else
		return 0;
}

bool CTrainer::SetUnlimitedJump(BOOL checked)
{
	DWORD dwAddress = dwPlayerDataBaseAddress + AIR_JUMP_OFFSET;
	if (WriteProcessMemory(hProcess, (LPVOID)dwAddress, &checked, sizeof(BOOL), NULL))
		return 1;
	else
		return 0;
}

//Write PlayerData
void CTrainer::WriteListData(CString offset, CString type, CString newValue,int curSelTab)
{
	DWORD dwBaseAddress = NULL;
	switch (curSelTab)
	{
	case PLAYERDATA_TAB:
	{
		dwBaseAddress = dwPlayerDataBaseAddress;
		break;
	}
	case HEROCONTROLLER_TAB:
	{
		dwBaseAddress = dwHeroControllerClassBaseAddress;
		break;
	}
	case HEROCONTROLLERSTATES_TAB:
	{
		dwBaseAddress = dwHeroControllerStatesClassBaseAddress;
		break;
	}
	default:
		break;
	}
	if (type == _T("System.Int32"))
	{
		DWORD dwNewValue = _tcstol(newValue, NULL, 10);
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &dwNewValue, sizeof(DWORD), NULL);
	}
	else if (type == _T("System.Boolean"))
	{
		BYTE byNewValue = (byte)_tcstol(newValue, NULL, 10);
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &byNewValue, sizeof(BYTE), NULL);
	}
	else if (type == _T("System.Single"))
	{
		FLOAT flNewValue = _tcstof(newValue, NULL);
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &flNewValue, sizeof(FLOAT), NULL);
	}
	else
	{
		MessageBox(NULL, _T("Can't modify unsupported type"), _T("Error"), MB_ICONERROR);
	}
}

//Get the information from mianList and read data from game
CString CTrainer::ReadListData(CString offset, CString type,int curSelTab)
{
	DWORD dwBaseAddress = NULL;
	switch (curSelTab)
	{
	case PLAYERDATA_TAB :
	{
		dwBaseAddress = dwPlayerDataBaseAddress;
		break;
	}
	case HEROCONTROLLER_TAB: 
	{
		dwBaseAddress = dwHeroControllerClassBaseAddress;
		break;
	}
	case HEROCONTROLLERSTATES_TAB:
	{
		dwBaseAddress = dwHeroControllerStatesClassBaseAddress;
		break;
	}
	default:
		break;
	}
	CString strReadingResult;
	if(type==_T("System.Int32"))
	{
		DWORD dwReadingResult = 0;
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &dwReadingResult, sizeof(DWORD), NULL);
		strReadingResult.Format(_T("%d"), dwReadingResult);
		return strReadingResult;
	}
	else if (type == _T("System.Boolean"))
	{
		BYTE byReadingResult = 0;
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &byReadingResult, sizeof(BYTE), NULL);
		strReadingResult.Format(_T("%d"), byReadingResult);
		return strReadingResult;
	}
	else if (type == _T("System.Single"))
	{
		FLOAT flReadingResult = 0.0;
		DWORD dwAddress = dwBaseAddress + CTrainer::CStringToHex(offset);
		ReadProcessMemory(hProcess, (LPCVOID)dwAddress, &flReadingResult, sizeof(FLOAT), NULL);
		strReadingResult.Format(_T("%f"), flReadingResult);
		return strReadingResult;
	}
	else
	{
		strReadingResult = _T("类型不受支持Unsupported type");
		return strReadingResult;
	}
}

//This function transfer CString to hex integer
DWORD CTrainer::CStringToHex(CString str)
{
	return _tcstol(str, NULL, 16);
}

//This function are used to show error information if it occur.
VOID CTrainer::ReportError(CString operation) 
{
	CString error;
	error.Format(_T("0x%08x"), GetLastError());//get last error code 
	MessageBox(NULL, _T("Fail to ")+operation+_T(" please check your antivirus programme and make sure you are running this program as an administrator.\nError code:") + error, _T("Error"), MB_ICONERROR);
}

int CTrainer::CStringFindNoCase(CString str, CString keyWords)
{
	str.MakeUpper();
	keyWords.MakeUpper();
	return str.Find(keyWords);

}

CTrainer::~CTrainer()
{
}
