#include "A_StarComponent.h"

Component::A_StarComponent::A_StarComponent(GridSystem* papa, int loc[2])
{
	gridControl = papa;
	memcpy(location, loc, sizeof(location));
}

void Component::A_StarComponent::FindPath(int destination[2])
{
	movePath = gridControl->FindPath(location, destination);
}

void Component::A_StarComponent::MovePath()
{
	//movement code here, gotta reference transforms or some shite
}
