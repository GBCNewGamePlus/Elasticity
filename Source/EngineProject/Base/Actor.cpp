#include "Actor.h"
#include <windows.h>

Actor::Actor()
{
	CoCreateGuid(&id);
}

void Actor::AddComponent(ActorComponent* _component)
{
	components.push_back(_component);
}

ActorComponent* Actor::GetComponent(string componentName)
{
	vector<ActorComponent*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
	{
		if ((*it)->componentName == componentName)
		{
			return *it;
		}
	}
	return NULL;
}
