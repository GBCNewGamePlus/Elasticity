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
#include "Components/SquareComponent/SquareComponent.h"
#include "Components/TransformComponent/TransformComponent.h"

# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)

using namespace std;
using namespace LuaPlus;

void MyMouseFunction(const Event& e) 
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
		sun->tc->TranslateBy(200, 200);
		sun->tc->ScaleBy(10, 10);

		Actor* earth = new Actor();
		earth->AddComponent(new CircleComponent(10, sf::Color::Blue));
		earth->AddComponent(new ScriptComponent("Assets/Scripts/ExampleScript.lua"));

		// Initial position of earth
		earth->tc->TranslateBy(0, 0);
		earth->tc->ScaleBy(0.3, 0.3);
		sun->AddChild(earth);
		sun->tc->TranslateBy(50, 50);
		sun->tc->RotateBy(90);

		Actor* box1 = new Actor();
		box1->AddComponent(new SquareComponent(50, sf::Color::Red));
		box1->tc->TranslateBy(500, 500);
		box1->tc->RotateBy(45);

		Actor* box2 = new Actor();
		box2->AddComponent(new SquareComponent(50, sf::Color::Blue));
		box2->tc->TranslateBy(600, 500);
		box2->tc->RotateBy(45);

		elasticity->AddActor(sun);
		elasticity->AddActor(earth);
		elasticity->AddActor(box1);
		elasticity->AddActor(box2);
		/*
		 * End of GAME CODE
		 */


		elasticity->Run();
		delete(sun);
	}
	return 0;
}
