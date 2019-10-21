#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <basetsd.h> 
#include <winnt.h>
#include <tchar.h>
#include "Base/GameCodeApp.h"

# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)
using namespace std;

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}

// Use this main to test multiple instance detection.
int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{

	const char* CLASS_NAME = "Elasticity";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);
	cout << "ASDF" << endl;
	GameCodeApp *gameCodeApp = new GameCodeApp();
	if (gameCodeApp->IsOnlyInstance("Elasticity"))
	{
		CreateWindow(CLASS_NAME, "Elasticity", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, NULL, NULL, NULL);
		if (gameCodeApp->InitInstance()) {}
	}
	delete gameCodeApp;

	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// Use this main to see the output on the console.
