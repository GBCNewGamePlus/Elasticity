#ifndef __A_STARCOMPONENT_H__
#define __A_STARCOMPONENT_H__

#include "Base/ActorComponent.h" 
#include "GridSystem.h"
#include "Components/TransformComponent/TransformComponent.h"

namespace Component {

	class A_StarComponent : public ActorComponent {
	public:
		int location[2];
		GridSystem* gridControl;
		list <gridSq> movePath;
		bool moving = false;
		sf::Vector2f totalMove;
		A_StarComponent(GridSystem* papa, int loc[2]);
		void FindPath(int destination[2]);
		void MovePath(TransformComponent ai, float increment);
	};
}

#endif // __A_STARCOMPONENT_H__
