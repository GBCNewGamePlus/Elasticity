#ifndef __BASE_ACTOR_H__
#define __BASE_ACTOR_H__
#include <string>
#include <windows.h>
#include "ActorComponent.h"
#include <vector>
#include "SFML/System/Vector2.hpp"
//#include "../Components/CircleComponent/CircleComponent.h"
using namespace std;
namespace sf
{
	class Transform;
}
class TransformComponent;

class Actor
{
private:
	GUID id;
	vector<ActorComponent*> components;

public:
	Actor();
	Actor(string _tag);
	~Actor(void);
	void AddComponent(ActorComponent* _component);
	ActorComponent* GetComponent(string componentName);
	void SetTransform(sf::Transform matrix);
	sf::Transform* GetLocalTransform() { return localTransform; }
	sf::Transform* GetWorldTransform() { return worldTransform; }
	void SetParent(Actor* p) { parent = p; }
	void AddChild(Actor* s);
	virtual void Update(float msec);
	TransformComponent* tc;
	string tag;
	bool Overlaps(Actor* otherActor);

protected:
	Actor* parent;
	sf::Transform* worldTransform;
	sf::Transform* localTransform;
	vector<Actor*> children;
};

#endif
