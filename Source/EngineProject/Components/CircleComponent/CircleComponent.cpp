#include <SFML/Graphics.hpp>
#include "CircleComponent.h"

CircleComponent::CircleComponent()
{
	radius = 10;
	color = sf::Color::Green;
	componentName = "circleComponent";
}

CircleComponent::CircleComponent(float r)
{
	radius = r;
	color = sf::Color::Green;
	componentName = "circleComponent";
}

CircleComponent::CircleComponent(sf::Color c)
{
	radius = 10;
	color = c;
	componentName = "circleComponent";
}

CircleComponent::CircleComponent(float r, sf::Color c)
{
	radius = r;
	color = c;
	componentName = "circleComponent";
}

void CircleComponent::SetRadius(float r)
{
	radius = r;
}

float CircleComponent::GetRadius()
{
	return radius;
}

void CircleComponent::SetColor(sf::Color c)
{
	color = c;
}

sf::Color CircleComponent::GetColor()
{
	return color;
}
