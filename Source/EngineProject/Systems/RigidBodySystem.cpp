#include "RigidBodySystem.h"
#include "../Base/Actor.h"

RigidBodySystem::RigidBodySystem()
{
	groundedTol = 0.1f;
	nextId = 0;
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
				CollisionPair pair;
				CollisionInfo colInfo;
				*pair.rigidBodyA = (*bodyA);
				*pair.rigidBodyB = (*bodyB);

				// TO DO: Get positions from the transform components as parameters.
				//sf::Vector2<float> distance = bodyB.transform.position - bodyA.transform.position;

				// TO DO: Remove this line once you have access to the actual distance.
				sf::Vector2<float> distance = sf::Vector2<float>(0,0);

				sf::Vector2<float> halfSizeA = ((*bodyA).aabb.tRight - (*bodyA).aabb.bLeft);
				halfSizeA.x /= 2;
				halfSizeA.y /= 2;

				sf::Vector2<float> halfSizeB = ((*bodyB).aabb.tRight - (*bodyB).aabb.bLeft);
				halfSizeB.x /= 2;
				halfSizeB.y /= 2;

				sf::Vector2<float> gap = sf::Vector2<float>(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				if (gap.x < 0 && gap.y < 0) 
				{
					map<CollisionPair, CollisionInfo>::iterator thisPair = collisions.find(pair);
					if (thisPair != collisions.end())
					{
						collisions.erase(thisPair);
					}

					if (gap.x > gap.y) 
					{
						if (distance.x > 0) 
						{
							colInfo.collisionNormal = sf::Vector2<float>(1, 0);
						}
						else 
						{
							colInfo.collisionNormal = sf::Vector2<float>(-1, 0);
						}
						colInfo.penetration = gap.x;
					}
					else {
						if (distance.y > 0) 
						{
							colInfo.collisionNormal = sf::Vector2<float>(0, 1);
						}
						else
						{
							colInfo.collisionNormal = sf::Vector2<float>(0, -1);
						}
						colInfo.penetration = gap.y;
					}
					collisions.insert({ pair, colInfo });
				}
				else
				{
					map<CollisionPair, CollisionInfo>::iterator thisPair = collisions.find(pair);
					if (thisPair != collisions.end())
					{
						collisions.erase(thisPair);
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
	vector<CollisionPair> pairs;
	for (map<CollisionPair, CollisionInfo>::iterator it = collisions.begin(); it != collisions.end(); ++it)
	{
		pairs.push_back(it->first);
	}
	
	for (auto pair = pairs.begin(); pair != pairs.end(); ++pair)
	{
		float minBounce = GetMin(pair->rigidBodyA->bounciness, pair->rigidBodyB->bounciness);
		float velAlongNormal = Dot(pair->rigidBodyB->currentVelocity - pair->rigidBodyA->currentVelocity, collisions[(*pair)].collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;

		if (pair->rigidBodyA->mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / pair->rigidBodyA->mass;

		if (pair->rigidBodyB->mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / pair->rigidBodyB->mass;

		j /= invMassA + invMassB;

		sf::Vector2<float> impulse = j * collisions[(*pair)].collisionNormal;

		sf::Vector2<float> velocityA = invMassA * impulse;
		sf::Vector2<float> velocityB = invMassB * impulse;
		pair->rigidBodyA->AddVelocity(-velocityA);
		pair->rigidBodyB->AddVelocity(velocityB);

		if (abs(collisions[(*pair)].penetration) > 0.01f)
		{
			PositionalCorrection((*pair));
		}
	}
}

void RigidBodySystem::PositionalCorrection(CollisionPair c) 
{
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c.rigidBodyA->mass == 0)
		invMassA = 0;
	else
		invMassA = 1 / c.rigidBodyA->mass;

	if (c.rigidBodyB->mass == 0)
		invMassB = 0;
	else
		invMassB = 1 / c.rigidBodyB->mass;

	sf::Vector2<float> correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

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
		if ((*it)->GetComponent("rigidBodyComponent"))
		{
			IntegrateBodies(dt);
			CheckCollisions();
			ResolveCollisions();
		}
	}
}