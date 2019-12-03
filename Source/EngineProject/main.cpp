#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <basetsd.h> 
#include <winnt.h>
#include <tchar.h>

#include "GameEngine.h"
#include "Base/Dispatcher.h"
#include "Base/Event.h"
#include "Events/EMouseEvent.h"
#include "Events/EKeyboardEvent.h"
#include "LuaPlus.h"

//#pragma comment(lib, "luaplus51-1201.lib")


# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)

using namespace std;
using namespace std::placeholders;
using namespace LuaPlus;

class ClassObserver
{
public:
	void handle(const Event& e)
	{
		if (e.descriptor == EventType::MouseEvent)
		{
			char number[10];
			const EMouseEvent& myMouseEvent = static_cast<const EMouseEvent&>(e);
			string printing = "Mouse Clicked on (";
			snprintf(number, sizeof(number), "%d", myMouseEvent.x);
			printing += number;
			printing += ",";
			snprintf(number, sizeof(number), "%d", myMouseEvent.y);
			printing += number;
			printing += ")";
			printing = myMouseEvent.leftClick ? "Left " + printing : "Right " + printing;
			GameEngine::GetInstance()->PrintToWindow(printing);
		}
		else if (e.descriptor == EventType::KeyboardEvent)
		{
			char buffer[100];
			const EKeyboardEvent& myKeyboardEvent = static_cast<const EKeyboardEvent&>(e);
			string message = "Key Pressed: ";
			if (myKeyboardEvent.isChar)
				message += myKeyboardEvent.keyChar;
			else
				message += myKeyboardEvent.keyInt;
			GameEngine::GetInstance()->PrintToWindow(message);
		}
	}
};

// Use this main to test multiple instance detection.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	/*
	*/
	LuaState* pLuaState = LuaState::Create();

	GameEngine* engine = GameEngine::GetInstance();
	if (engine->InitInstance(hInstance, previousInstance, cmdLine, nCmdShow, "Game Title"))
	{
		ClassObserver co;
		Dispatcher::GetInstance()->Subscribe(EventType::MouseEvent, std::bind(&ClassObserver::handle, co, _1));
		Dispatcher::GetInstance()->Subscribe(EventType::KeyboardEvent, std::bind(&ClassObserver::handle, co, _1));
		pLuaState->DoString("birthdayList={John='Superman',Mary='Batman'}");
		LuaObject table = pLuaState->GetGlobals().GetByName("birthdayList");
		// loop through the table, printing out the pair
		for (LuaTableIterator it(table); it; it.Next()) 
		{
			LuaObject key = it.GetKey();
			LuaObject value = it.GetValue();
			// do whatever you want with the objects...
			engine->PrintToWindow(value.GetString());
		}
		engine->Run();
	}
	LuaState::Destroy(pLuaState);
	pLuaState = NULL;
	/*
	bool runs = engine.initialize(); -> systems that you have in the engine
	engine.loadActor(paddleOneXml);
	auto levels = engine.loadLevels();
	auto world = engine.loadWorld(levelXML);
	engine.loadActors(world, actorListXML);
	engine.loadSprites();
	engine.loadSounds();
	
	auto result = engine.run(); -> whenever there is an exit condition
\	*/

	return 0;
}

// Use this main to see the output on the console.
