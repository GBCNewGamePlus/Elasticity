#ifndef __A_STARCOMPONENT_H__
#define __A_STARCOMPONENT_H__

#include "Components/TransformComponent/TransformComponent.h"
#include "SFML/System/Vector2.hpp"
#include "Base/ActorComponent.h" 
#include "GridSystem.h"


namespace Component {

	class A_StarComponent : public ActorComponent {
	public:
		sf::Vector2<int> location;
		GridSystem* gridControl;
		list <gridSq> movePath;
		bool moving = false;
		sf::Vector2f totalMove;
		A_StarComponent(GridSystem* papa, sf::Vector2<int> loc);
		void FindPath(sf::Vector2<int> destination);
		void MovePath(TransformComponent ai, float increment);
	};
}

#endif // __A_STARCOMPONENT_H__
