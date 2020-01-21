#pragma once
#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include "Base/Actor.h"

using namespace std;

/*
 * SFML RenderWindow forward declaration 
 * (apparently there is some problems with SFML headers in .h files)
 */
namespace sf {
	class RenderWindow;
}

enum GameState:byte {
	Initializing = 0,
	GameLoop = 1,
	Exiting = 2
};

class GameEngine
{
private:
	/*
	 * Implementing GameEngine as a static class
	 */
	GameEngine();
	~GameEngine();
	static GameEngine* instance;
	GameState currentState = GameState::Initializing;
	/*
	 * Check functions (initialization)
	 */
	void RenderSplashScreen();
	bool IsOnlyInstance(LPCTSTR windowName);
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	void ReadCPUSpeed();
	void ErrorExit(const char* lpszFunction);
	/*
	 * Constant values to check for run environment quality
	 */
	const DWORDLONG MB = 1024 * 1024;
	const DWORDLONG DISK_SPACE_NEEDED = 300 * MB;
	const DWORDLONG PHYSICAL_MEMORY_NEEDED = 300 * MB;
	const DWORDLONG VIRTUAL_MEMORY_NEEDED = 300 * MB;
	/*
	 * Game Title - to be defined in main.cpp by the user
	 */
	string szTitle;
	/*
	 * List of Actors in the game
	 */
	vector<Actor*> actors;
	/*
	 * Game Window
	 */
	sf::RenderWindow* window;


public:
	static GameEngine* GetInstance();
	bool InitInstance(string _szTitle);
	void Run();
	void Print(string message);
	void PrintToWindow(string message);
	void AddActor(Actor* _actor);
};
#endif // __GAME_ENGINE_H__


