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

# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)

using namespace std;
using namespace std::placeholders;

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
	}
};

// Use this main to test multiple instance detection.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	GameEngine* engine = GameEngine::GetInstance();
	if (engine->InitInstance(hInstance, previousInstance, cmdLine, nCmdShow, "Game Title"))
	{
		ClassObserver co;
		Dispatcher::GetInstance()->Subscribe(EventType::MouseEvent, std::bind(&ClassObserver::handle, co, _1));
		engine->Run();
	}
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
