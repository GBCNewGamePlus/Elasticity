#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__
#include "SFML/System/Vector2.hpp"
#include "../../Base/ActorComponent.h" 

class RigidBodySystem;
class CircleComponent;
class SquareComponent;
class TransformComponent;

struct AABB
{
	sf::Vector2f bLeft;
	sf::Vector2f tRight;
};

struct Bounds
{
	sf::Vector2f center;
	sf::Vector2f extents;
	sf::Vector2f max;
	sf::Vector2f min;
	sf::Vector2f size;

	Bounds(sf::Vector2f _center, sf::Vector2f _size)
	{
		center = _center;
		size = _size;
		extents = sf::Vector2f(size.x / 2, size.y / 2);
		max = sf::Vector2f(center.x + extents.x, center.y + extents.y);
		min = sf::Vector2f(center.x - extents.x, center.y - extents.y);
	}
};

class RigidBody : public ActorComponent
{
public:
	RigidBody();
	int id;
	float mass;                              // Mass of the RigidBody
	float bounciness;                        // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity;                       // Whether or not this body obeys gravity
	sf::Vector2f gravity;              // The gravity vector applied to this body
	sf::Vector2f currentVelocity;      // The current velocity the body is moving at
	sf::Vector2f maxVelocity;          // The maximum allowed velocity for this object
	bool grounded;
	AABB aabb;
	RigidBodySystem* rigidBodySystem;
	TransformComponent* transform;
	CircleComponent* circleComponent;
	SquareComponent* squareComponent;

	void AddVelocity(sf::Vector2f v);
	void AddForce(sf::Vector2f force);
	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Integrate(float dt);

private:
	sf::Vector2f totalForces;
};

#endif 
