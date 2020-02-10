#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__
#include "../../Base/ActorComponent.h" 
#include "SFML/System/Vector2.hpp"

class RigidBodySystem;
class CircleComponent;
class SquareComponent;
class TransformComponent;

struct AABB
{
	sf::Vector2<float> bLeft;
	sf::Vector2<float> tRight;
};

struct Bounds
{
	sf::Vector2<float> center;
	sf::Vector2<float> extents;
	sf::Vector2<float> max;
	sf::Vector2<float> min;
	sf::Vector2<float> size;

	Bounds(sf::Vector2<float> _center, sf::Vector2<float> _size)
	{
		center = _center;
		size = _size;
		extents = sf::Vector2<float>(size.x / 2, size.y / 2);
		max = sf::Vector2<float>(center.x + extents.x, center.y + extents.y);
		min = sf::Vector2<float>(center.x - extents.x, center.y - extents.y);
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
	sf::Vector2<float> gravity;              // The gravity vector applied to this body
	sf::Vector2<float> currentVelocity;      // The current velocity the body is moving at
	sf::Vector2<float> maxVelocity;          // The maximum allowed velocity for this object
	bool grounded;
	AABB aabb;
	RigidBodySystem* rigidBodySystem;
	TransformComponent* transform;
	CircleComponent* circleComponent;
	SquareComponent* squareComponent;

	void AddVelocity(sf::Vector2<float> v);
	void AddForce(sf::Vector2<float> force);
	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Integrate(float dt);

private:
	sf::Vector2<float> totalForces;
};

#endif 
