#include "RigidBody.h"

RigidBody::RigidBody()
{
	mass = 1.0f;
	bounciness = 1.0f;
	obeysGravity = true;
	gravity = sf::Vector2<float>(0, -9.8f);
	maxVelocity = sf::Vector2<float>(10.0f, 10.0f);
	SetAABB();
	//engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();
	//engine.AddRigidBody(this);
}

void RigidBody::AddVelocity(sf::Vector2<float> v)
{
	currentVelocity += v;
	//currentVelocity = v;
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
	//grounded = engine.IsGrounded(this);
	grounded = false; // CHANGE THIS!
	return grounded;
}

void RigidBody::SetAABB()
{
	Bounds bound(sf::Vector2<float>(0, 0), sf::Vector2<float>(1, 1));

	// THIS NEEDS AN UPDATE!
	/*Renderer renderer = GetComponent<Renderer>();
	if (renderer)
	{
		bound = renderer.bounds;
	}*/

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
	//sf::Vector2<float> temp = transform.position;
	//temp += currentVelocity * dT;
	//transform.position = temp;

	SetAABB();
	totalForces = sf::Vector2<float>(0, 0);
}