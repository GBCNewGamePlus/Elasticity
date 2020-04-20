#ifndef __GRID_SYSTEM_H__
#define __GRID_SYSTEM_H__

#include "Base/ActorComponent.h" 
#include <list>
#include "SFML/System/Vector2.hpp"

namespace Component {
	struct gridSq {
		int location[2]; //the grid coodrinate of the square
		sf::Vector2f locationF; //the world coordinate of the square
		float size; //giving the length of the grid square
		int value = 0; //the value used for tracking pathing
		gridSq *parent = nullptr;
		int g = 0; //the value to be modified for the individual tile's priority
		int h = 0; //the value to be modified for each tile's distance to the target
		
		

		
		gridSq(int loc[2], float locf[2], float si) {
			memcpy(location, loc, sizeof(location));
			locationF.x = locf[0];
			locationF.y = locf[1];
			size = si;
		}
		void hAssign(int des[2]) { //don't call this it's used in the a*
			h = abs(location[0] - des[0]) + abs(location[1] + des[1]);
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
		std::list <gridSq> grid;
		float size; //designates size of the grid total which will be divided for each square
		std::list<gridSq>* closedList;
		std::list<gridSq>* openList;
		std::list<gridSq>* path;
		std::list<int[2]> surroundingTiles;
		
		void ClearPath();
		void surroundUpdate(int loc[2]);
		gridSq* findTile(int ref[2]);
		//here's all the tiles to be checked
	public :
		GridSystem(int gS, float s);
		list <gridSq>* FindPath(int loc[2], int des[2]);
	    void AlterGrid(int size);
		void GridReset();
	};
}

#endif // __GRID_SYSTEM_H__