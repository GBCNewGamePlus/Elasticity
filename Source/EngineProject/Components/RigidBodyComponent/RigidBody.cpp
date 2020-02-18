#include "../CircleComponent/CircleComponent.h"
#include "RigidBody.h"
#include "../../Systems/RigidBodySystem.h"
#include "../SquareComponent/SquareComponent.h"
#include "../TransformComponent/TransformComponent.h"

RigidBody::RigidBody()
{
	componentName = "rigidBodyComponent";
	id = -1; // -1 = ID not set. ID is set by the RigidBodySystem.
	mass = 1.0f;
	bounciness = 1.0f;
	obeysGravity = true;
	gravity = sf::Vector2f(0, -9.8f);
	maxVelocity = sf::Vector2f(10.0f, 10.0f);
	SetAABB();
	rigidBodySystem->AddRigidBody(this);
}

void RigidBody::AddVelocity(sf::Vector2f v)
{
	currentVelocity += v;
}

void RigidBody::AddForce(sf::Vector2f force)
{
	totalForces += force;
}

void RigidBody::Stop()
{
	currentVelocity = sf::Vector2f(0,0);
	totalForces = sf::Vector2f(0, 0);
}

bool RigidBody::IsGrounded()
{
	grounded = rigidBodySystem->IsGrounded(*this);
	return grounded;
}

void RigidBody::SetAABB()
{
	sf::Vector2f center;
	sf::Vector2f size;
	if (transform)
	{
		center = transform->GetLocation();
		size = transform->GetScale();
	}
	else
	{
		center = sf::Vector2f(0, 0);
		size = sf::Vector2f(0, 0);
	}

	if (circleComponent)
	{
		size.x = size.x * circleComponent->GetRadius();
		size.y = size.y * circleComponent->GetRadius();
	}
	else if (squareComponent)
	{
		size.x = size.x * squareComponent->GetLength();
		size.y = size.y * squareComponent->GetLength();
	}
	Bounds bound(center, size);

	aabb.bLeft = sf::Vector2f(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
	aabb.tRight = sf::Vector2f(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void RigidBody::Integrate(float dt) 
{
	sf::Vector2f acceleration;

	if (obeysGravity && !IsGrounded()) 
	{
		acceleration = gravity;
	}
	else 
	{
		if (abs(currentVelocity.y) < 0.05f) 
			currentVelocity.y = 0;
	}

	acceleration += totalForces / mass;
	if (mass == 0)
		acceleration = sf::Vector2f(0,0);

	currentVelocity += acceleration * dt;

	// TO DO: Access the transform component and update the position!
	sf::Vector2f temp = transform->GetLocation();
	temp += currentVelocity * dt;
	transform->SetPosition(temp.x, temp.y);

	SetAABB();
	totalForces = sf::Vector2f(0, 0);
}