#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow, string _szTitle)
{
	hInstance = _hInstance;
	previousInstance = _previousInstance;
	cmdLine = _cmdLine;
	nCmdShow = _nCmdShow;
	szTitle = _szTitle;
	WindowCreate();
}

RenderingSystem::~RenderingSystem() {}

void RenderingSystem::WindowCreate()
{
	static TCHAR szWindowClass[] = _T("win32app");
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = InputSystem::WndProc;
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
		/*MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			szTitle,
			NULL);*/

		return;
	}
	HWND hWnd = CreateWindow(szWindowClass, szTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		/*MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			szTitle,
			NULL);*/

		return;
	}
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
}
