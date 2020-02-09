#pragma once
#ifndef __RIGIDBODY_SYSTEM_H__
#define __RIGIDBODY_SYSTEM_H__
#include <vector>
#include <list> 
#include <map> 
#include "SFML/System/Vector2.hpp"
#include "../Components/RigidBodyComponent/RigidBody.h"

using namespace std;
namespace sf {class RenderWindow;}
class RigidBody;
class Actor;


struct CollisionPair 
{
	RigidBody* rigidBodyA;
	RigidBody* rigidBodyB;
};

struct CollisionInfo 
{
	sf::Vector2<float> collisionNormal;
	float penetration;
};

class RigidBodySystem
{
private:
	int nextId;	
	map<CollisionPair, CollisionInfo> collisions;
	list<RigidBody> rigidBodies;
	void IntegrateBodies(float dt);
	void CheckCollisions();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair c);
	float GetMin(float a, float b);
	float Dot(sf::Vector2<float> vectorA, sf::Vector2<float> vectorB);

public:
	RigidBodySystem();
	float groundedTol = 0.1f;
	bool IsGrounded(RigidBody rigidBody);
	void AddRigidBody(RigidBody rigidBody);
	void UpdatePhysics(vector<Actor*>* actors, float dt);
};
#endif
