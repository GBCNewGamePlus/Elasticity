#include "InputSystem.h"
#include <strsafe.h>

TCHAR greeting[2000000] = _T("Hello, World!");
LRESULT CALLBACK InputSystem::WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam)
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


