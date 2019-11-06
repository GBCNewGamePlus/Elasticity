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

int currentY = 5;
bool hello = false;

TCHAR greeting[2000000] = _T("Hello, World!"); 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc,
			5, currentY,
			greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		_tcscat_s(greeting, _tcslen(greeting) + 200, TEXT(" left button clicked\n"));
		InvalidateRect(hWnd, NULL, TRUE);
		// End application-specific layout section.  
		currentY += 10;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, param, lparam);
		break;
	}
}

// Use this main to test multiple instance detection.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	static TCHAR szWindowClass[] = _T("win32app");
	static TCHAR szTitle[] = _T("Elasticity");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			szTitle,
			NULL);

		return 1;
	}

	GameCodeApp *gameCodeApp = new GameCodeApp();
	if (gameCodeApp->IsOnlyInstance(szTitle))
	{
		if (!gameCodeApp->InitInstance()) 
		{
			delete gameCodeApp;
			return-1;
		}
		delete gameCodeApp;


		HWND hWnd = CreateWindow(
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			800, 800,
			NULL,
			NULL,
			hInstance,
			NULL
		);
		if (!hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				szTitle,
				NULL);

			return 1;
		}
		ShowWindow(hWnd,
			nCmdShow);
		UpdateWindow(hWnd);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return (int)msg.wParam;
	}
	return 0;
}

// Use this main to see the output on the console.
