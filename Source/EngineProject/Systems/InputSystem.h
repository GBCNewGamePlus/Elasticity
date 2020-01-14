#pragma once
#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <Windowsx.h>
#include "../GameEngine.h"
#include <string>

using namespace std;
/*
namespace sf {

}*/

class InputSystem
{
private: 
	sf::RenderWindow* window;
public:
	InputSystem(sf::RenderWindow* _window);
	bool Update();
};

#endif 
