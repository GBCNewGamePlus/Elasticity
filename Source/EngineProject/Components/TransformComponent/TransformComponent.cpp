#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	//transforms
	translate.translate(0, 0);
	rotation.rotate(0);
	scale.scale(1, 1);
	//user values (vector, angle in degrees, vector)
	translationv = sf::Vector2f(0, 0);
	rotationv = 0;
	scalev = sf::Vector2f(0, 0);
	//updating the main matrix
	transform = translate * rotation * scale;
	//transform = scale * rotation * translate;
	componentName = "transformComponent";
}
TransformComponent::TransformComponent(sf::Vector2f trans)
{
	translate.translate(trans.x, trans.y);
	rotation.rotate(0);
	scale.scale(0, 0);
	translationv = sf::Vector2f(trans.x, trans.y);
	rotationv = 0;
	scalev = sf::Vector2f(0, 0);
	transform = translate * rotation * scale;
	//transform = scale * rotation * translate;
	componentName = "transformComponent";
}
TransformComponent::TransformComponent(sf::Vector2f trans, float angle, sf::Vector2f scal)
{
	translate.translate(trans.x, trans.y);
	rotation.rotate(angle);
	scale.scale(scal.x, scal.y);
	translationv = sf::Vector2f(trans.x, trans.y);
	rotationv = angle;
	scalev = sf::Vector2f(scal.x,scal.y);
	transform = translate * rotation * scale;
	//transform = scale * rotation * translate;
	componentName = "transformComponent";
}

void TransformComponent::SetPosition(float x, float y)
{
	transform = transform.Identity;
	translationv += sf::Vector2f(x, y);
	transform.translate(x, y);
}

void TransformComponent::SetRotation(float angle)
{
	rotation = rotation.Identity;
	rotationv += angle;
	rotation.rotate(angle);
}

void TransformComponent::SetScale(float x, float y)
{
	scale = scale.Identity;
	scalev += sf::Vector2f(x, y);
	scale.scale(x, y);
}

void TransformComponent::TranslateBy(float x, float y)
{
	translate.translate(x, y);
	translationv += sf::Vector2f(x, y);
	UpdateTransform();
}
void TransformComponent::RotateBy(float angle)
{
	rotation.rotate(angle);
	rotationv += angle;
	UpdateTransform();
}
void TransformComponent::ScaleBy(float x, float y)
{
	scale.scale(x, y);
	scalev += sf::Vector2f(x, y);
	UpdateTransform();
}
sf::Vector2f TransformComponent::GetLocation()
{
	return translationv;
}
float TransformComponent::GetRotation()
{
	return rotationv;
}
sf::Vector2f TransformComponent::GetScale()
{
	return scalev;
}
void TransformComponent::UpdateTransform()
{
	transform = translate * rotation * scale;
	//transform = scale * rotation * translate;
}
