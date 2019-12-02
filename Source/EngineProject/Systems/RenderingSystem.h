#pragma once
#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <string>
#include "InputSystem.h"

using namespace std;

// This system creates the window
class RenderingSystem 
{
private: 
	HINSTANCE hInstance; 
	HINSTANCE previousInstance; 
	PSTR cmdLine; 
	INT nCmdShow;
	string szTitle;

public:
	RenderingSystem(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow, string _szTitle);
	~RenderingSystem();
	void WindowCreate();
};
#endif // __INPUT_SYSTEM_H__
