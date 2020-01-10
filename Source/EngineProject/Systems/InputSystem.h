#pragma once
#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <Windowsx.h>
#include "../GameEngine.h"
#include <string>

using namespace std;

class InputSystem
{
private:
	InputSystem();
	static InputSystem *s_instance;
public:
	static InputSystem GetInputSystem();
};

#endif 
