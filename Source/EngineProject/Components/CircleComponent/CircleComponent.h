
#ifndef __CIRCLE_COMPONENT_H__
#define __CIRCLE_COMPONENT_H__
#include <SFML/Graphics.hpp>
#include "../../Base/ActorComponent.h" 
//namespace sf{class Color;}

class CircleComponent : public ActorComponent
{
public:
	CircleComponent();
	CircleComponent(float r);
	CircleComponent(sf::Color c);
	CircleComponent(float r, sf::Color c);
	void SetRadius(float r);
	float GetRadius();
	void SetColor(sf::Color c);
	sf::Color GetColor();

private:
	float radius;
	sf::Color color;
};
#endif 


