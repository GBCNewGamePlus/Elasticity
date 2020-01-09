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
	string szTitle;

public:
	RenderingSystem(string _szTitle);
	~RenderingSystem();
	void WindowCreate();
};
#endif // __INPUT_SYSTEM_H__
