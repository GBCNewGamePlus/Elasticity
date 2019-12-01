#pragma once
#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <Windowsx.h>

class InputSystem
{
public:
	InputSystem();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam);
};

#endif 
