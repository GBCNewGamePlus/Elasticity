
#include "A_StarComponent.h"

Component::A_StarComponent::A_StarComponent(GridSystem* papa, sf::Vector2<int> loc)
{
	gridControl = papa;
	location = loc;
}

void Component::A_StarComponent::FindPath(sf::Vector2<int> destination) //call when you want the ai pathing updated
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
