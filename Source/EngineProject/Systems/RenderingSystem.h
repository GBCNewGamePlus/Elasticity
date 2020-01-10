#pragma once
#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>

using namespace std;

namespace sf {
	class RenderWindow;
}

class Actor;


// This system creates the window
class RenderingSystem 
{
private: 
	string szTitle;

public:
	RenderingSystem(string _szTitle);
	~RenderingSystem();
	void WindowCreate();
	void WindowClose();
	bool IsWindowOpen();
	void RenderSplashScreen();
	void RenderActors(vector<Actor*>* actors);
	sf::RenderWindow* window;
};
#endif // __INPUT_SYSTEM_H__
