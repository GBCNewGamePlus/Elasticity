#ifndef __A_STARCOMPONENT_H__
#define __A_STARCOMPONENT_H__

#include "Base/ActorComponent.h" 
#include "GridSystem.h"

namespace Component {

	class A_StarComponent : public ActorComponent {
	public:
		int location[2];
		GridSystem* gridControl;
		list <gridSq> movePath;
		A_StarComponent(GridSystem* papa, int loc[2]);
		void FindPath(int destination[2]);
		void MovePath();
	};
}

#endif // __A_STARCOMPONENT_H__
