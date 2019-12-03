#include "InputSystem.h"
#include <strsafe.h>
#include "../Events/EMouseEvent.h"
#include "../Events/EKeyboardEvent.h"
#include "../Base/Dispatcher.h"

using namespace std;
TCHAR InputSystem::WindowText[2000];

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
		TextOut(hdc, 5, 10, WindowText, _tcslen(WindowText));
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lparam);
		yPos = GET_Y_LPARAM(lparam);
		Dispatcher::GetInstance()->Post(EMouseEvent(xPos, yPos, true));
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		xPos = GET_X_LPARAM(lparam);
		yPos = GET_Y_LPARAM(lparam);
		Dispatcher::GetInstance()->Post(EMouseEvent(xPos, yPos, false));
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if ((param >= 'A' && param < 'Z') || (param >= 'a' && param < 'z') || (param >= '0' && param < '9'))
		{
			Dispatcher::GetInstance()->Post(EKeyboardEvent((char)param));
		}
		else
		{
			Dispatcher::GetInstance()->Post(EKeyboardEvent((int)param));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, msg, param, lparam);
		break;
	}
}

void InputSystem::ChangeMessage(string message) 
{
	sprintf_s(WindowText, 2000, message.c_str());
}


