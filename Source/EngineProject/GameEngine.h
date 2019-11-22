#pragma once
#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__
#include <windows.h>
#include <tchar.h>
class GameEngine
{
private:
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	void ReadCPUSpeed();
	void ErrorExit(const char* lpszFunction);
	//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam);
	/*
	 * For some unusual reason we always need 300 MB everywhere.
	 * Curious, isn't it?
	 */
	const DWORDLONG MB = 1024 * 1024;
	const DWORDLONG DISK_SPACE_NEEDED = 300 * MB;
	const DWORDLONG PHYSICAL_MEMORY_NEEDED = 300 * MB;
	const DWORDLONG VIRTUAL_MEMORY_NEEDED = 300 * MB;
	HINSTANCE hInstance;
	HINSTANCE previousInstance;
	PSTR cmdLine;
	INT nCmdShow;

public:
	GameEngine(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow);
	~GameEngine();
	bool InitInstance();
	bool IsOnlyInstance(LPCTSTR windowName);
};
#endif // __GAME_ENGINE_H__


