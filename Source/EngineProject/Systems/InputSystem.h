#pragma once
#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <Windowsx.h>

static class InputSystem
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM param, LPARAM lparam);
};
#endif // __INPUT_SYSTEM_H__
