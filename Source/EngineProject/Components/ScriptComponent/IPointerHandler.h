#ifndef __COMPONENT_IPOINTERHANDLER_COMPONENT_H__
#define __COMPONENT_IPOINTERHANDLER_COMPONENT_H__
#include "../../Base/ActorComponent.h" 
#include "atltypes.h"
namespace Component {
	class IPointerHandler {
	public:
		virtual bool VOnPointerMove(const CPoint &mousePos) = 0;
		virtual bool VOnPointerButtonDown(const CPoint &mousePos, const TCHAR &buttonName) = 0;
		virtual bool VOnPointerButtonUp(const CPoint &mousePos, const TCHAR &buttonName) = 0;
		virtual int VGetPointerRadius() = 0;
	};
}

#endif // __COMPONENT_IPOINTERHANDLER_COMPONENT_H__
