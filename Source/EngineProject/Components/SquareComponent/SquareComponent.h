#ifndef __SQUARE_COMPONENT_H__
#define __SQUARE_COMPONENT_H__
#include "../../Base/ActorComponent.h" 

namespace sf {class Color;}

class SquareComponent : public ActorComponent
{
public:
	SquareComponent();
	SquareComponent(float length);
	SquareComponent(sf::Color c);
	SquareComponent(float length, sf::Color c);
	void SetRadius(float length);
	float GetLength();
	void SetColor(sf::Color c);
	sf::Color GetColor();

private:
	float length;
	sf::Color color;
};

#endif 
