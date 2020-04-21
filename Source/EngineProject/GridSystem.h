#ifndef __GRID_SYSTEM_H__
#define __GRID_SYSTEM_H__


#include <list>
#include "SFML/System/Vector2.hpp"
#include "Base/ActorComponent.h" 

namespace Component {
	struct gridSq {
		bool operator == (const gridSq& s) const { return location == s.location && locationF == s.locationF; }
		bool operator != (const gridSq& s) const { return !operator==(s); }
		sf::Vector2<int> location; //the grid coodrinate of the square
		sf::Vector2f locationF; //the world coordinate of the square
		float size; //giving the length of the grid square
		int value = 0; //the value used for tracking pathing
		gridSq *parent = nullptr;
		int g = 0; //the value to be modified for the individual tile's priority
		int h = 0; //the value to be modified for each tile's distance to the target
		
		

		
		gridSq(int loc[2], float locf[2], float si) {
			location.x = loc[0];
			location.y = loc[1];
			locationF.x = locf[0];
			locationF.y = locf[1];
			size = si;
		}
		void hAssign(sf::Vector2<int> des) { //don't call this it's used in the a*
			h = abs(location.x - des.x) + abs(location.y + des.y);
			value = g + h;
		}
		void gAssign(int ga) { // call this to set the tile priority for an individual tile
			g = ga;
			value = g + h;
		}
	};
	class GridSystem {
	protected:
		int gridSize = 15; //designates the grid as x by x
		std::list <Component::gridSq> grid;
		float size; //designates size of the grid total which will be divided for each square
		std::list<Component::gridSq>* closedList;
		std::list<gridSq>* openList;
		std::list<Component::gridSq>* path;
		std::list<sf::Vector2<int>> surroundingTiles;
		
		void ClearPath();
		void surroundUpdate(sf::Vector2<int> loc);
		Component::gridSq* findTile(sf::Vector2<int> ref);
		//here's all the tiles to be checked
	public :
		GridSystem(int gS, float s);
		std::list <Component::gridSq>* FindPath(sf::Vector2<int> loc, sf::Vector2<int> des);
	    void AlterGrid(int size);
		void GridReset();
	};
}

#endif // __GRID_SYSTEM_H__