#ifndef __COMPONENT_IKEYBOARDHANDLER_COMPONENT_H__
#define __COMPONENT_IKEYBOARDHANDLER_COMPONENT_H__
#include "../../Base/ActorComponent.h" 
namespace Component {
	class IKeyboardHandler {
		virtual bool VOnKeyDown(unsigned int const kcode) = 0;
		virtual bool VOnKeyUp(unsigned int const kcode) = 0;
	};
}

#endif //__COMPONENT_IKEYBOARDHANDLER_COMPONENT_H__