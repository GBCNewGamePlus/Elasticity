#include "../Components/TransformComponent/TransformComponent.h"
#include "RigidBodySystem.h"
#include "../Base/Actor.h"
#include "../Components/RigidBodyComponent/RigidBody.h"

RigidBodySystem::RigidBodySystem()
{
	groundedTol = 0.1f;
	nextId = 0;
}

RigidBody* RigidBodySystem::GetRigidBody(int id)
{
	list<RigidBody>::iterator rb;
	for (rb = rigidBodies.begin(); rb != rigidBodies.end(); ++rb)
	{
		if (rb->id == id)
		{
			return &(*rb);
		}
	}
	return NULL;
}

void RigidBodySystem::AddRigidBody(RigidBody rigidBody) 
{
	rigidBody.id = nextId;
	nextId++;
	rigidBodies.push_back(rigidBody);
}

void RigidBodySystem::IntegrateBodies(float dt) 
{
	list <RigidBody> ::iterator rb;
	for (rb = rigidBodies.begin(); rb != rigidBodies.end(); ++rb)
	{
		(*rb).Integrate(dt);
	}
}

bool RigidBodySystem::IsGrounded(RigidBody rigidBody) 
{
	list <RigidBody> ::iterator rb;
	for (rb = rigidBodies.begin(); rb != rigidBodies.end(); ++rb) 
	{
		if ((*rb).id != rigidBody.id) 
		{
			if (rigidBody.aabb.bLeft.x < (*rb).aabb.tRight.x && 
				rigidBody.aabb.tRight.x > (*rb).aabb.bLeft.x && 
				abs(rigidBody.aabb.bLeft.y - (*rb).aabb.tRight.y) <= groundedTol) 
			{
				if (abs(rigidBody.currentVelocity.y) < groundedTol)
					return true;
			}
		}
	}
	return false;
}

void RigidBodySystem::CheckCollisions()
{
	list <RigidBody> ::iterator bodyA, bodyB;
	
	for (bodyA = rigidBodies.begin(); bodyA != rigidBodies.end(); ++bodyA)
	{
		for (bodyB = rigidBodies.begin(); bodyB != rigidBodies.end(); ++bodyB) 
		{
			if ((*bodyA).id != (*bodyB).id) 
			{
				Collision collision;
				collision.rigidBodyA = bodyA->id;
				collision.rigidBodyB = bodyB->id;

				// TO DO: Get positions from the transform components as parameters.
				sf::Vector2<float> distance = bodyB->transform->GetLocation() - bodyA->transform->GetLocation();

				sf::Vector2<float> halfSizeA = ((*bodyA).aabb.tRight - (*bodyA).aabb.bLeft);
				halfSizeA.x /= 2;
				halfSizeA.y /= 2;

				sf::Vector2<float> halfSizeB = ((*bodyB).aabb.tRight - (*bodyB).aabb.bLeft);
				halfSizeB.x /= 2;
				halfSizeB.y /= 2;

				sf::Vector2<float> gap = sf::Vector2<float>(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				if (gap.x < 0 && gap.y < 0) 
				{
					list<Collision>::iterator c;
					for (c = collisions.begin(); c != collisions.end(); ++c)
					{
						if (c->rigidBodyA == collision.rigidBodyA && c->rigidBodyB == collision.rigidBodyB)
						{
							collisions.erase(c);
						}
					}

					if (gap.x > gap.y) 
					{
						if (distance.x > 0) 
						{
							collision.collisionNormal = sf::Vector2<float>(1, 0);
						}
						else 
						{
							collision.collisionNormal = sf::Vector2<float>(-1, 0);
						}
						collision.penetration = gap.x;
					}
					else {
						if (distance.y > 0) 
						{
							collision.collisionNormal = sf::Vector2<float>(0, 1);
						}
						else
						{
							collision.collisionNormal = sf::Vector2<float>(0, -1);
						}
						collision.penetration = gap.y;
					}
					collisions.push_back(collision);
				}
				else
				{
					list<Collision>::iterator c;
					for (c = collisions.begin(); c != collisions.end(); ++c)
					{
						if (c->rigidBodyA == collision.rigidBodyA && c->rigidBodyB == collision.rigidBodyB)
						{
							collisions.erase(c);
						}
					}
				}
			}
		}
	}
}

float RigidBodySystem::GetMin(float a, float b)
{
	if (a <= b)
	{
		return a;
	}
	return b;
}

float RigidBodySystem::Dot(sf::Vector2<float> vectorA, sf::Vector2<float> vectorB)
{
	return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
}

void RigidBodySystem::ResolveCollisions()
{
	list<Collision>::iterator c;
	for (c = collisions.begin(); c != collisions.end(); ++c)
	{
		float minBounce = GetMin(GetRigidBody(c->rigidBodyA)->bounciness, GetRigidBody(c->rigidBodyB)->bounciness);
		float velAlongNormal = Dot(GetRigidBody(c->rigidBodyB)->currentVelocity - GetRigidBody(c->rigidBodyA)->currentVelocity, c->collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;

		if (GetRigidBody(c->rigidBodyA)->mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / GetRigidBody(c->rigidBodyA)->mass;

		if (GetRigidBody(c->rigidBodyB)->mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / GetRigidBody(c->rigidBodyB)->mass;

		j /= invMassA + invMassB;

		sf::Vector2<float> impulse = j * c->collisionNormal;

		sf::Vector2<float> velocityA = invMassA * impulse;
		sf::Vector2<float> velocityB = invMassB * impulse;
		GetRigidBody(c->rigidBodyA)->AddVelocity(-velocityA);
		GetRigidBody(c->rigidBodyB)->AddVelocity(velocityB);

		if (abs(c->penetration) > 0.01f)
		{
			PositionalCorrection((*c));
		}
	}
}

void RigidBodySystem::PositionalCorrection(Collision c) 
{
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (GetRigidBody(c.rigidBodyA)->mass == 0)
		invMassA = 0;
	else
		invMassA = 1 / GetRigidBody(c.rigidBodyA)->mass;

	if (GetRigidBody(c.rigidBodyB)->mass == 0)
		invMassB = 0;
	else
		invMassB = 1 / GetRigidBody(c.rigidBodyB)->mass;

	sf::Vector2<float> correction = ((c.penetration / (invMassA + invMassB)) * percent) * -c.collisionNormal;

	// TO DO: Get the position from the transform component as a function parameter.
	//sf::Vector2<float> temp = c.rigidBodyA.transform.position;

	// TO DO: Get rid of this line once you have a reference to the position.
	sf::Vector2<float> temp = sf::Vector2<float>(0,0);

	// TO DO: Uncomment th following three lines onve you have access to the position.
	temp -= invMassA * correction;
	//c.rigidBodyA.transform.position = temp;
	//temp = c.rigidBodyB.transform.position;
	temp += invMassB * correction;
	//c.rigidBodyB.transform.position = temp;
}

void RigidBodySystem::UpdatePhysics(vector<Actor*>* actors, float dt)
{
	for (std::vector<Actor*>::iterator it = actors->begin(); it != actors->end(); ++it)
	{
		RigidBody* rigidBody = (RigidBody*)(*it)->GetComponent("rigidBodyComponent");
		if (rigidBody)
		{
			rigidBody->rigidBodySystem = this;
			IntegrateBodies(dt);
			CheckCollisions();
			ResolveCollisions();
		}
	}
}