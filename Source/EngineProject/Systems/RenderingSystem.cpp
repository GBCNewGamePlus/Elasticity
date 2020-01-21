#include <SFML/Graphics.hpp>
#include "../Base/Actor.h"
#include "../Base/ActorComponent.h"
#include "RenderingSystem.h"
#include "../Components/CircleComponent/CircleComponent.h"

RenderingSystem::RenderingSystem(sf::RenderWindow* _window)
{
	window = _window;
}

RenderingSystem::~RenderingSystem() {
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

void RenderingSystem::RenderActors(vector<Actor*>* actors) {
	window->clear();

	for (std::vector<Actor*>::iterator it = actors->begin(); it != actors->end(); ++it) 
	{
		if ((*it)->GetComponent("circleComponent"))
		{
			CircleComponent* cc = (CircleComponent*)(*it)->GetComponent("circleComponent");
			sf::CircleShape shape(cc->GetRadius());
			shape.setFillColor(cc->GetColor());
			window->draw(shape, *(*it)->GetWorldTransform());
		}
	}

	window->display();
}
