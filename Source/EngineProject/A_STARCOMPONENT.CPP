#include "A_StarComponent.h"
#include "SFML/System/Vector2.hpp"
Component::A_StarComponent::A_StarComponent(GridSystem* papa, int loc[2])
{
	gridControl = papa;
	memcpy(location, loc, sizeof(location));
}

void Component::A_StarComponent::FindPath(int destination[2]) //call when you want the ai pathing updated
{
	movePath = *gridControl->FindPath(location, destination);
}

void Component::A_StarComponent::MovePath(TransformComponent ai, float incremen) //call every frame you want the ai to move on
{
	if (!moving) { //sets the next target for moving to
		totalMove = ai.GetLocation() - movePath.front().locationF;
		moving = true;
	}
	float tempx = totalMove.x / incremen;
	float tempy = totalMove.y / incremen;
	ai.TranslateBy(tempx, tempy);
	if (ai.GetLocation() == movePath.front().locationF) {
		movePath.pop_front();
		moving = false;
	}
	
}
