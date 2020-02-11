#ifndef __COMPONENT_TRANSFORM_COMPONENT_H__
#define __COMPONENT_TRANSFORM_COMPONENT_H__
#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"
#include "../../Base/ActorComponent.h" 
class TransformComponent : public ActorComponent {
public:
	TransformComponent();
	TransformComponent(sf::Vector2f trans);
	TransformComponent(sf::Vector2f trans, float angle, sf::Vector2f scal);
	void SetPosition(float x, float y);
	void SetRotation(float angle);
	void SetScale(float x, float y);
	void TranslateBy(float x, float y);
	void RotateBy(float angle);
	void ScaleBy(float x, float y);
	sf::Vector2f GetLocation();
	float GetRotation();
	sf::Vector2f GetScale();
	sf::Transform transform;
private:
	void UpdateTransform();		
	float rotationv;
	sf::Vector2f translationv;
	sf::Vector2f scalev;
	sf::Transform translate;
	sf::Transform rotation;
	sf::Transform scale;
};

#endif // __COMPONENT_TRANSFORM_COMPONENT_H__

