#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <iostream>
#include <windows.h>
#include <direct.h> // This is for drive information
#include <intrin.h> // This is for CPU information
#include <strsafe.h>
#include <tchar.h>
#include <string>
#include "Systems/ScriptSystem.h"
#include "Systems/RenderingSystem.h"
#include "Systems/InputSystem.h"
#include <time.h>

using namespace std;

GameEngine* GameEngine::instance = 0;

GameEngine* GameEngine::GetInstance()
{
	if (!instance)
	{
		instance = new GameEngine();
	}
	return instance;
}

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

// Log Functions
void GameEngine::PrintToWindow(string message) 
{
}

void GameEngine::Print(string message)
{
	message += "\n";
	char buf[1000];
	sprintf_s(buf, message.c_str());
	OutputDebugStringA(buf);
}

// Initialize Functions
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
	Print("Multiple Instances NOT Detected!");
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
	Print("Checking your hardware...");
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

	string cpuType = "Your CPU Type is: ";
	cpuType += CPUBrandString;
	cpuType += "\nNumber of Cores: ";

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	char convertBuffer[32];
	wsprintf(convertBuffer, "%d", sysInfo.dwNumberOfProcessors);
	cpuType += convertBuffer;

	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL,&type, (LPBYTE)&dwMHz, &BufSize);
		cpuType += "\nIts speed is: ";
		wsprintf(convertBuffer, "%d", dwMHz);
		cpuType += convertBuffer;
		cpuType += " MHz\n";
	}
	else
	{
		Print("Unable to find this information - registry probably corrupted...");
	}
	Print(cpuType);
}

// Real Game Engine
bool GameEngine::InitInstance(string _szTitle)
{
	szTitle = _szTitle;
	// Creates window as soon as the game engine is initialized
	window = new sf::RenderWindow(sf::VideoMode(1080, 960), szTitle, sf::Style::None );
	RenderSplashScreen();

	if (IsOnlyInstance(szTitle.c_str()))
	{
		Print("Starting system check...");
		bool result = CheckStorage(DISK_SPACE_NEEDED) && CheckMemory(PHYSICAL_MEMORY_NEEDED, VIRTUAL_MEMORY_NEEDED);
		if (result) { ReadCPUSpeed(); }
		Print("Finished system check...");
		currentState = GameState::GameLoop;
		return result;
	}
	else
	{
		currentState = GameState::Exiting;
		return false;
	}
}

void GameEngine::RenderSplashScreen()
{
	window->clear();
	sf::Texture texture;
	if (texture.loadFromFile("Assets\\Images\\SplashScreen.png") != true) {
		return;
	}
	sf::Sprite sprite(texture);
	window->draw(sprite);
	window->display();
	sf::Event loadingEvent;
	/*
	 Displays our beautiful logo
	 */
	while (currentState == GameState::Initializing) {
		while (window->pollEvent(loadingEvent)) {
			if (loadingEvent.type == sf::Event::EventType::KeyPressed
				|| loadingEvent.type == sf::Event::EventType::MouseButtonPressed
				|| loadingEvent.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}

void GameEngine::Run()
{
	RenderingSystem rs(window);
	InputSystem is(window);
	ScriptSystem ss(&actors);
	MSG msg;
	ss.Run();
	float oldTime = clock();
	float deltaTime;
	while (rs.IsWindowOpen())
	{
		/*
		 * calculates DT
		 */
		deltaTime = clock() - oldTime;
		oldTime = clock();
		/*
		 * Verify events
		 */
		if (!is.Update()) {
			rs.WindowClose();
		}
		/*
		 * Update Actors
		 */
		for (std::vector<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}

		rigidBodySystem.UpdatePhysics(&actors, deltaTime);
		/*
		 * Renders updated actors
		 */
		rs.RenderActors(&actors);
	}
	// just before leaving 
	delete window;
}

void GameEngine::AddActor(Actor* _actor)
{
	actors.push_back(_actor);
}
