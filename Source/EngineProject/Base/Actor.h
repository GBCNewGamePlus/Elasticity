#ifndef __BASE_ACTOR_H__
#define __BASE_ACTOR_H__
#include <string>
#include <windows.h>
#include "ActorComponent.h"
#include <vector>
using namespace std;

class Actor
{
private:
	GUID id;
	vector<ActorComponent*> components;

public:
	Actor();
	~Actor(void);
	void AddComponent(ActorComponent* _component);
	ActorComponent* GetComponent(string componentName);
	void SetTransform(const int &matrix) { localTransform = matrix; }
	int GetTransform() { return localTransform; }
	int GetWorldTransform() { return worldTransform; }
	void SetParent(Actor* p) { parent = p; }
	void AddChild(Actor* s);
	virtual void Update(float msec);

protected:
	Actor* parent;
	int worldTransform;
	int localTransform;
	vector<Actor*> children;
};

#endif
