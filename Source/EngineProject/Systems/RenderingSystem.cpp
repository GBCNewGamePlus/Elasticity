#include <SFML/Graphics.hpp>
#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(string _szTitle)
{
	szTitle = _szTitle;
	WindowCreate();
}

RenderingSystem::~RenderingSystem() {}

void RenderingSystem::WindowCreate()
{
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

}
