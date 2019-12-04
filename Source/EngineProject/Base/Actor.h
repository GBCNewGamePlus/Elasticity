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
	void AddComponent(ActorComponent* _component);
	ActorComponent* GetComponent(string componentName);
};

#endif
