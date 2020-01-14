#include <SFML/Graphics.hpp>
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
#include "Base/Actor.h"
#include "Components/ScriptComponent/ScriptComponent.h"
#include "Components/CircleComponent/CircleComponent.h"
#include "Components/TransformComponent/TransformComponent.h"

# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)

using namespace std;
using namespace LuaPlus;

void MyMouseFunction(const Event& e) {
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
		GameEngine::GetInstance()->Print(printing);
	}
}

void MyKeyboardFunction(const Event& e)
{
	if (e.descriptor == EventType::KeyboardEvent)
	{
		char buffer[100];
		const EKeyboardEvent& myKeyboardEvent = static_cast<const EKeyboardEvent&>(e);
		string message = "Key Pressed: ";
		if (myKeyboardEvent.isChar)
			message += myKeyboardEvent.keyChar;
		else
			message += myKeyboardEvent.keyInt;
		GameEngine::GetInstance()->Print(message);
	}
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	GameEngine* elasticity = GameEngine::GetInstance();
	if (elasticity->InitInstance("Game Title"))
	{
		/*
		 * Start of GAME CODE
		 */
		Dispatcher::GetInstance()->Subscribe(EventType::MouseEvent, &MyMouseFunction);
		Dispatcher::GetInstance()->Subscribe(EventType::KeyboardEvent, &MyKeyboardFunction);

		Actor* sun = new Actor();
		sun->AddComponent(new CircleComponent(10, sf::Color::Yellow));
		sun->AddComponent(new ScriptComponent("Assets/Scripts/ExampleScript.lua"));

		// Initial position of the Sun
		sun->tc->Translate(200, 200);
		sun->tc->Scale(10, 10);

		Actor* earth = new Actor();
		earth->AddComponent(new CircleComponent(10, sf::Color::Blue));
		earth->AddComponent(new ScriptComponent("Assets/Scripts/ExampleScript.lua"));

		// Initial position of earth
		earth->tc->Translate(0, 0);
		earth->tc->Scale(0.3, 0.3);
		sun->AddChild(earth);

		// moving the sun a little bit - nah, not really
		//sun->tc->Translate(300, 200);

		elasticity->AddActor(sun);
		elasticity->AddActor(earth);
		/*
		 * End of GAME CODE
		 */


		elasticity->Run();
		delete(sun);
	}
	return 0;
}
