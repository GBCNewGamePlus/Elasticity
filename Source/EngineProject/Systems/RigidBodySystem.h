#pragma once
#ifndef __RIGIDBODY_SYSTEM_H__
#define __RIGIDBODY_SYSTEM_H__
#include <vector>
#include <list> 
#include <map> 
#include "SFML/System/Vector2.hpp"

using namespace std;
namespace sf {class RenderWindow;}
class Actor;
class RigidBody;

struct Collision 
{
	int rigidBodyA;
	int rigidBodyB;
	sf::Vector2f collisionNormal;
	float penetration;
};

class RigidBodySystem
{
private:
	int nextId;	
	list<Collision> collisions;
	list<RigidBody*> rigidBodies;
	void IntegrateBodies(float dt);
	void CheckCollisions();
	void ResolveCollisions();
	void PositionalCorrection(Collision c);
	float GetMin(float a, float b);
	float Dot(sf::Vector2f vectorA, sf::Vector2f vectorB);
	RigidBody* GetRigidBody(int id);

public:
	RigidBodySystem();
	float groundedTol = 0.1f;
	bool IsGrounded(RigidBody rigidBody);
	void AddRigidBody(RigidBody* rigidBody);
	void UpdatePhysics(vector<Actor*>* actors, float dt);
};
#endif
