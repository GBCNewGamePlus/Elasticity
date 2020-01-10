#include <SFML/Graphics.hpp>
#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(string _szTitle)
{
	szTitle = _szTitle;
	WindowCreate();
}

RenderingSystem::~RenderingSystem() {
	delete window;
}

void RenderingSystem::WindowCreate()
{
	window = new sf::RenderWindow(sf::VideoMode(1080, 960), szTitle);
}

void RenderingSystem::WindowClose()
{
	if (window) window->close();
}

bool RenderingSystem::IsWindowOpen()
{
	if (window) return window->isOpen();
	return false;
}

void RenderingSystem::RenderSplashScreen() 
{
}

void RenderingSystem::RenderActors(vector<Actor*>* actors) {
	window->clear();
	/*
	 Draws stuff
	 */
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	window->draw(shape);

	window->display();

}
