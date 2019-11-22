#include "GameEngine.h"
#include <iostream>
#include <windows.h>
#include <direct.h> // This is for drive information
#include <intrin.h> // This is for CPU information
#include <strsafe.h>
#include <tchar.h>
#include <Windowsx.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam);

GameEngine::GameEngine(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow, TCHAR* _szTitle)
{
	hInstance = _hInstance;
	previousInstance = _previousInstance;
	cmdLine = _cmdLine;
	nCmdShow = _nCmdShow;
	szTitle = _szTitle;
	/*
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		*/
		return;
}

GameEngine::~GameEngine()
{
}

TCHAR greeting[2000000] = _T("Hello, World!");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int xPos = 0;
	int yPos = 0;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc,
			5, 10,
			greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lparam);
		yPos = GET_Y_LPARAM(lparam);
		/*  */
		sprintf_s(greeting, 260, TEXT("Left mouse button clicked at x:%d, y:%d"), xPos, yPos);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		xPos = GET_X_LPARAM(lparam);
		yPos = GET_Y_LPARAM(lparam);
		sprintf_s(greeting, 260, TEXT("Right mouse button clicked at x:%d, y:%d"), xPos, yPos);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if ((param >= 'A' && param < 'Z')
			|| (param >= 'a' && param < 'z')
			|| (param >= '0' && param < '9'))
			sprintf_s(greeting, 260, TEXT("key pressed :%c"), param);
		else
			sprintf_s(greeting, 260, TEXT("key pressed: %d"), param);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, msg, param, lparam);
		break;
	}
}

bool GameEngine::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd); SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			MessageBox(NULL, _T("Multiple Instances Detected!"), _T("Error"), NULL);
			return false;
		}
	}
	MessageBox(NULL, _T("Multiple Instances NOT Detected!"), _T("Success"), NULL);
	return true;
}

bool GameEngine::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	cout << "Checking necessary storage..." << endl;
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	/*
	 * First we undestand how the partition has been divided and how many clusters
	 * we need free for our game
	 */
	unsigned __int64 const neededClusters =
		diskSpaceNeeded /
		(diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	/* Diagnostic messages will be sent to std output using cout */
	cout << "You have " <<
		(diskfree.avail_clusters * diskfree.sectors_per_cluster * diskfree.bytes_per_sector) / MB
		<< " MB available in your hard disk. " << endl;

	/* Now we compare.... */
	if (diskfree.avail_clusters < neededClusters)
	{
		/* Error messages will be sent in message boxes - those require action by the user */
		TCHAR pszDest[260] = _T("");
		sprintf_s(pszDest, 260, TEXT("You need at least %I64u MB free on your disk to run the game. Please buy a new computer."), diskSpaceNeeded / MB);
		MessageBox(NULL, pszDest, _T("Failure"), NULL);
	}
	return true;
}

void GameEngine::ErrorExit(const char* lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

bool GameEngine::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	cout << "Checking necessary memory..." << endl;
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	BOOL result = GlobalMemoryStatusEx(&status);
	if (!result)
	{
		ErrorExit("GlobalMemoryStatusEx");
	}
	cout << "Physical Memory: You have " << status.ullAvailPhys / MB << " MB free" << endl;
	cout << "Virtual Memory: You have " << status.ullAvailVirtual / MB << " MB free" << endl;
	if (status.ullTotalPhys < physicalRAMNeeded) {
		/* Error messages will be sent in message boxes - those require action by the user */
		TCHAR pszDest[260] = _T("");
		sprintf_s(pszDest, 260, TEXT("You need at least %I64u MB free on your physical memory to run the game. Please close Google Chrome and try again."), physicalRAMNeeded / MB);
		MessageBox(NULL, pszDest, _T("Failure"), NULL);
		return false;
	}
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		/* Error messages will be sent in message boxes - those require action by the user */
		TCHAR pszDest[260] = _T("");
		sprintf_s(pszDest, 260, TEXT("You need at least %I64u MB free on your virtual memory to run the game. Please close Google Chrome and try again."), virtualRAMNeeded / MB);
		MessageBox(NULL, pszDest, _T("Failure"), NULL);
		return false;
	}
	char *buff = new char[virtualRAMNeeded];
	if (buff) {
		delete[] buff;
	}
	else {
		/* Error messages will be sent in message boxes - those require action by the user */
		TCHAR pszDest[260] = _T("");
		sprintf_s(pszDest, 260, TEXT("You need at least %I64u MB contiguous free on your virtual memory to run the game. Please close Google Chrome and try again."), virtualRAMNeeded / MB);
		MessageBox(NULL, pszDest, _T("Failure"), NULL);
		return false;
	}
	return true;
}

void GameEngine::ReadCPUSpeed()
{
	cout << "Checking your hardware..." << endl;
	int CPUInfo[4] = { -1 };
	unsigned   nExIds, i = 0;
	char CPUBrandString[0x40];
	// Get the information associated with each extended ID.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	//string includes manufacturer, model and clockspeed
	cout << "" << CPUBrandString << endl;
	TCHAR cpuType[260] = _T("");
	sprintf_s(cpuType, 260, TEXT("Your CPU Type is : %s \n"), CPUBrandString);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	TCHAR cores[260] = _T("");
	sprintf_s(cores, 260, TEXT("Number of Cores: %lu \n"), sysInfo.dwNumberOfProcessors);

	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ,
		&hKey);

	TCHAR speed[260] = _T("");
	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz",
			NULL,
			&type,
			(LPBYTE)&dwMHz, &BufSize);

		sprintf_s(speed, 260, TEXT("Its speed is: %lu MHz \n"), dwMHz);
	}
	else
	{
		cout << "Unable to find this information - registry probably corrupted..." << endl;
	}
	TCHAR final[260] = _T("");
	snprintf(final, 260, "%s %s %s", cpuType, cores, speed);

	MessageBox(NULL, final, _T("Information"), NULL);


}

bool GameEngine::InitInstance()
{
	if (IsOnlyInstance(szTitle))
	{
		if (!InitInstance())
		{
			return;
		}
	}

	cout << "Starting system check..." << endl;
	bool result = CheckStorage(DISK_SPACE_NEEDED) && CheckMemory(PHYSICAL_MEMORY_NEEDED, VIRTUAL_MEMORY_NEEDED);
	if (result) { ReadCPUSpeed(); }
	cout << "Finished system check..." << endl;
	return result;
}
