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
#include "Components/RigidBodyComponent/RigidBody.h"
#include "GridSystem.h"
#include "A_StarComponent.h"

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

		Actor* greenCircle = new Actor("greenCircle");
		greenCircle->AddComponent(new CircleComponent(50, sf::Color::Green));
		greenCircle->tc->TranslateBy(0, elasticity->WindowHeight() / 2 - 50);

		Actor* blueCircle = new Actor("blueCircle");
		blueCircle->AddComponent(new CircleComponent(50, sf::Color::Blue));
		blueCircle->tc->TranslateBy(elasticity->WindowWidth() - 100, elasticity->WindowHeight() / 2 - 50);

		Actor* gridCon = new Actor("gridCon");
		gridCon->AddComponent(new Component::GridSystem(10, 10.0f));

		Actor* aiTest = new Actor("aiTest");
		aiTest->AddComponent(new Component::A_StarComponent(aiTest->tc, static_cast<Component::GridSystem*>(gridCon->GetComponent("GridSystem")),sf::Vector2<int>{ 1,1 }));
		aiTest->AddComponent(new CircleComponent(10, sf::Color::Magenta));

		//static_cast<Component::A_StarComponent*>(aiTest->GetComponent("A_StarComponent"))->FindPath(sf::Vector2<int>{9, 9});
		//static_cast<Component::A_StarComponent*>(aiTest->GetComponent("A_StarComponent"))->MovePath(*aiTest->tc,5);

		elasticity->AddActor(greenCircle);
		elasticity->AddActor(blueCircle);
		elasticity->AddActor(aiTest);
		/*
		 * End of GAME CODE
		 */

		elasticity->Run();
	}
	return 0;
}
