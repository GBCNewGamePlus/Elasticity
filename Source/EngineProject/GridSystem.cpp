#include "GridSystem.h"

void Component::GridSystem::ClearPath()
{
	openList->clear();
	closedList->clear();
	path->clear();
}

void Component::GridSystem::surroundUpdate(sf::Vector2<int> loc)
{
	surroundingTiles.clear();
	surroundingTiles.push_back({ loc.x,   loc.y -1 });
	surroundingTiles.push_back({ loc.x -1, loc.y -1 });
	surroundingTiles.push_back({ loc.x -1, loc.y });
	surroundingTiles.push_back({ loc.x-1, loc.y +1 });
	surroundingTiles.push_back({ loc.x,   loc.y +1 });
	surroundingTiles.push_back({ loc.x+1, loc.y +1 });
	surroundingTiles.push_back({ loc.x+1, loc.y });
	surroundingTiles.push_back({ loc.x+1, loc.y -1 });
}

Component::gridSq* Component::GridSystem::findTile(sf::Vector2<int> ref)
{
	for (Component::gridSq x : grid) {
		if (x.location == ref) {
			return &x;
		}
	}
	return nullptr;
}

Component::GridSystem::GridSystem(int gS, float s)
{
	gridSize = gS; //establish number of squares
	size = s; //establish size of grid
	componentName = "GridSystem";
	GridReset();

}

list<Component::gridSq>* Component::GridSystem::FindPath(sf::Vector2<int> loc, sf::Vector2<int> des)
{
	Component::gridSq* currentTile;
	Component::gridSq* destinationTile;
	currentTile = findTile(loc);
	destinationTile = findTile(des);
	for (Component::gridSq x : grid) { //setting the h value for the whole grid, absolutely no idea if this is the most efficient way to do this
		x.hAssign(des);
	}
	ClearPath();
	openList->push_back(*currentTile);
	while (!openList->empty()) { //while there are tiles still to check
		Component::gridSq* temp;
		temp = &openList->front();
		for (Component::gridSq q : *openList) { //here we're grabbing the lowest priority value from the list of open tiles, aka, the current closest option
			if (&temp == nullptr) {
				temp = &q;
			}
			else {
				if (temp->value < q.value) {
					temp = &q;
				}
			}
		}
		if (temp->h == 0) { //if h = 0 then we've hit the target, so we add it to the path and return
			path->push_front(*temp);
			Component::gridSq* writer = temp;
			while (writer->parent != nullptr) { //now we're going back through the path we took and adding them all to the list to send
				path->push_front(*writer->parent);
				writer = writer->parent;
			}
			return path; //WE'RE DONE BOYS
		}
		openList->remove(*temp);
		surroundUpdate(temp->location);
		for (sf::Vector2<int> x : surroundingTiles) { //now we check every surrounding tile for a value lower
			Component::gridSq* check = findTile(x);
			if (check->value < temp->value) {
				bool closedCheck = false;
				for (Component::gridSq q : *closedList) { //once we find one with a lower value we make sure it's not in the closed list
					if (q.location == check->location) {
						closedCheck = true;
					}
				}
				if (!closedCheck) { //once we've confirmed that it's not on the closed list we check if it's parent is shorter and add it to the open list
					if (check->parent != nullptr) {
						if (check->parent->value > temp->value) {
							check->parent = temp;
						}
					}
					else {
						check->parent = temp;
					}
					openList->push_front(*check);
				}
			}
		}
		closedList->push_front(*temp); //now we throw the just checked square into the closed pile, so we won't check it again.

	}
	return nullptr;
}

void Component::GridSystem::AlterGrid(int size)
{
	gridSize = size;
	GridReset();
}

void Component::GridSystem::GridReset()
{
	float squareSize = size / gridSize;
	int current[2];
	float currentf[2];
	for (int i = 0; i < gridSize; i++) //x axis
	{
		for (int j = 0; j < gridSize; j++) //y axis
		{
			current[0] = i;
			current[1] = j;
			currentf[0] = squareSize * i;
			currentf[1] = squareSize * j;
			Component::gridSq temp(current, currentf, squareSize); //here we make each grid square
			grid.push_back(temp); //and then shove it on the list
		}
	}
}
