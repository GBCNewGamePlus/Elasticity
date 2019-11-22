#include "RenderingSystem.h"

namespace System {
	RenderingSystem::RenderingSystem(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow, TCHAR* _szTitle)
	{
		hInstance = _hInstance;
		previousInstance = _previousInstance;
		cmdLine = _cmdLine;
		nCmdShow = _nCmdShow;
		szTitle = _szTitle;
	}
	RenderingSystem::~RenderingSystem() {}
	void RenderingSystem::CreateWindow() 
	{
		static TCHAR szWindowClass[] = _T("win32app");

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		//wcex.lpfnWndProc = WndProc;
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

			return;
		}
	}
}
