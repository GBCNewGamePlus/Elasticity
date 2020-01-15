#include <SFML/Graphics.hpp>
#include "InputSystem.h"
#include <strsafe.h>
#include "../Events/EMouseEvent.h"
#include "../Events/EKeyboardEvent.h"
#include "../Base/Dispatcher.h"

using namespace std;

InputSystem::InputSystem(sf::RenderWindow* _window) {
	window = _window;
}

bool InputSystem::Update() {
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type) {
			case sf::Event::Closed:
				return false; // messages the main game loop to simply close the window
				break;
			case sf::Event::KeyPressed:
				if ((event.key.code >= 'A' && event.key.code < 'Z') || (event.key.code >= 'a' && event.key.code < 'z') || (event.key.code >= '0' && event.key.code < '9'))
				{
					Dispatcher::GetInstance()->Post(EKeyboardEvent((char)event.key.code));
				}
				else
				{
					Dispatcher::GetInstance()->Post(EKeyboardEvent((int)event.key.code));
				}
				break;
			case sf::Event::MouseButtonPressed:
				Dispatcher::GetInstance()->Post(
					EMouseEvent(event.mouseButton.x, 
						        event.mouseButton.y, 
						        event.mouseButton.button == sf::Mouse::Left));
				break;
		}
		if (event.type == sf::Event::Closed) {
			// Game ends - user closed the window
			return false;
		}





	}
	// Game continues
	return true;
}


/*
TCHAR InputSystem::WindowText[2000];
HWND InputSystem::hwnd;

LRESULT CALLBACK InputSystem::WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam)
{
	hwnd = hWnd;
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
	InvalidateRect(hwnd, NULL, TRUE);
}
*/


