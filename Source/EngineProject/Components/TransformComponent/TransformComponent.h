#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"
#ifndef __COMPONENT_TRANSFORM_COMPONENT_H__
#define __COMPONENT_TRANSFORM_COMPONENT_H__

#include "../../Base/ActorComponent.h" 
class TransformComponent : public ActorComponent {
public:
	TransformComponent();
	TransformComponent(sf::Vector2<float> trans);
	TransformComponent(sf::Vector2<float> trans, float angle, sf::Vector2<float> scal);
	void SetPosition(float x, float y);
	void SetRotation(float angle);
	void SetScale(float x, float y);
	void TranslateBy(float x, float y);
	void RotateBy(float angle);
	void ScaleBy(float x, float y);
	sf::Vector2<float> GetLocation();
	float GetRotation();
	sf::Vector2<float> GetScale();
	sf::Transform transform;
private:
	void UpdateTransform();		
	float rotationv;
	sf::Vector2<float> translationv;
	sf::Vector2<float> scalev;
	sf::Transform translate;
	sf::Transform rotation;
	sf::Transform scale;
};

#endif // __COMPONENT_TRANSFORM_COMPONENT_H__

