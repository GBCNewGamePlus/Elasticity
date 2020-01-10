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
		GameEngine::GetInstance()->PrintToWindow(printing);
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
		GameEngine::GetInstance()->PrintToWindow(message);
	}
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	GameEngine* elasticity = GameEngine::GetInstance();
	if (elasticity->InitInstance(hInstance, previousInstance, cmdLine, nCmdShow, "Game Title"))
	{
		/*
		 * Start of GAME CODE
		 */
		Dispatcher::GetInstance()->Subscribe(EventType::MouseEvent, &MyMouseFunction);
		Dispatcher::GetInstance()->Subscribe(EventType::KeyboardEvent, &MyKeyboardFunction);
		Actor* exampleActor = new Actor();
		//ScriptComponent* sc = new ScriptComponent("Assets/Scripts/ExampleScript.lua");
		//exampleActor->AddComponent(sc);
		CircleComponent* cc = new CircleComponent(10, sf::Color::Yellow);
		exampleActor->AddComponent(cc);
		elasticity->AddActor(exampleActor);
		/*
		 * End of GAME CODE
		 */
		elasticity->Run();
		delete(cc);
		delete(exampleActor);
	}
	return 0;

	/*
	CODE TO TEST INTEGRATION
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
		*/
}
