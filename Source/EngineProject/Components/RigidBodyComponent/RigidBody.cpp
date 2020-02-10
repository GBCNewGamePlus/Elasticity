#include "RigidBody.h"
#include "../../Systems/RigidBodySystem.h"
#include "../CircleComponent/CircleComponent.h"
#include "../SquareComponent/SquareComponent.h"
#include "../TransformComponent/TransformComponent.h"

RigidBody::RigidBody()
{
	componentName = "rigidBodyComponent";
	id = -1; // -1 = ID not set. ID is set by the RigidBodySystem.
	mass = 1.0f;
	bounciness = 1.0f;
	obeysGravity = true;
	gravity = sf::Vector2<float>(0, -9.8f);
	maxVelocity = sf::Vector2<float>(10.0f, 10.0f);
	SetAABB();
	rigidBodySystem->AddRigidBody(*this);
}

void RigidBody::AddVelocity(sf::Vector2<float> v)
{
	currentVelocity += v;
}

void RigidBody::AddForce(sf::Vector2<float> force)
{
	totalForces += force;
}

void RigidBody::Stop()
{
	currentVelocity = sf::Vector2<float>(0,0);
	totalForces = sf::Vector2<float>(0, 0);
}

bool RigidBody::IsGrounded()
{
	grounded = rigidBodySystem->IsGrounded(*this);
	return grounded;
}

void RigidBody::SetAABB()
{
	sf::Vector2<float> center = transform->GetLocation();
	sf::Vector2<float> size = transform->GetScale();
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

	aabb.bLeft = sf::Vector2<float>(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
	aabb.tRight = sf::Vector2<float>(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void RigidBody::Integrate(float dt) 
{
	sf::Vector2<float> acceleration;

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
		acceleration = sf::Vector2<float>(0,0);

	currentVelocity += acceleration * dt;

	// TO DO: Access the transform component and update the position!
	sf::Vector2<float> temp = transform->GetLocation();
	temp += currentVelocity * dt;
	transform->SetPosition(temp.x, temp.y);

	SetAABB();
	totalForces = sf::Vector2<float>(0, 0);
}