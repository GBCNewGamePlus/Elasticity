//#include "SFML/Graphics/Transform.hpp"
#include "../Components/TransformComponent/TransformComponent.h"
#include "Actor.h"
#include <windows.h>
#include "../Components/CircleComponent/CircleComponent.h"

Actor::Actor()
{
	CoCreateGuid(&id);
	parent = NULL;
	tc = new TransformComponent();
	worldTransform = new sf::Transform();
	localTransform = &(tc->transform);
	tag = "";
}

Actor::Actor(string _tag)
{
	CoCreateGuid(&id);
	parent = NULL;
	tc = new TransformComponent();
	worldTransform = new sf::Transform();
	localTransform = &(tc->transform);
	tag = _tag;
}

Actor::~Actor(void)
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
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

void Actor::SetTransform(sf::Transform matrix)
{
	*localTransform = matrix;
}

void Actor::AddChild(Actor* s) 
{
	children.push_back(s);
	s->SetParent(this);
}

float greenSpeed = 0.3;
float blueSpeed = -0.3;
void Actor::Update(float msec) 
{
	if (parent) 
	{ //This node has a parent...
		*worldTransform = *(parent->worldTransform) * *(localTransform);
	}
	else 
	{ //Root node, world transform is local transform!
		worldTransform = localTransform;
	}

	if (tag == "greenCircle")
	{
		tc->TranslateBy(greenSpeed*msec, 0);
		if (tc->GetLocation().x + 100 > 1080 || tc->GetLocation().x < 0)
		{
			greenSpeed = -greenSpeed;
		}
	}
	else if (tag == "blueCircle")
	{
		tc->TranslateBy(blueSpeed*msec, 0);
		if (tc->GetLocation().x + 100 > 1080 || tc->GetLocation().x < 0)
		{
			blueSpeed = -blueSpeed;
		}
	}
}

bool Actor::Overlaps(Actor * otherActor)
{
	CircleComponent* cc1 = (CircleComponent*)GetComponent("circleComponent");
	CircleComponent* cc2 = (CircleComponent*)GetComponent("circleComponent");

	if (cc1 && cc2)
	{
		float r1 = cc1->GetRadius();
		float r2 = cc2->GetRadius();
		sf::Vector2f pos1 = tc->GetLocation();
		sf::Vector2f pos2 = otherActor->tc->GetLocation();
		sf::Vector2f center1 = sf::Vector2f(pos1.x + r1, pos1.y + r1);
		sf::Vector2f center2 = sf::Vector2f(pos2.x + r2, pos2.y + r2);
		float distanceX = abs(center2.x - center1.x);
		float distanceY = abs(center2.y - center1.y);
		float distance = sqrt(distanceX*distanceX + distanceY * distanceY);
		if (distance < r1 + r2)
		{
			return true;
		}
	}
	return false;
}
