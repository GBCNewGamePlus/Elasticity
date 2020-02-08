#include <SFML/Graphics.hpp>
#include "SquareComponent.h"

SquareComponent::SquareComponent()
{
	length = 10;
	color = sf::Color::Green;
	componentName = "squareComponent";
}

SquareComponent::SquareComponent(float l)
{
	length = l;
	color = sf::Color::Green;
	componentName = "squareComponent";
}

SquareComponent::SquareComponent(sf::Color c)
{
	length = 10;
	color = c;
	componentName = "squareComponent";
}

SquareComponent::SquareComponent(float l, sf::Color c)
{
	length = l;
	color = c;
	componentName = "squareComponent";
}

void SquareComponent::SetRadius(float l)
{
	length = l;
}

float SquareComponent::GetLength()
{
	return length;
}

void SquareComponent::SetColor(sf::Color c)
{
	color = c;
}

sf::Color SquareComponent::GetColor()
{
	return color;
}
