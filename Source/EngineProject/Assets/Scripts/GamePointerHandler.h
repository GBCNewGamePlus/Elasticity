#ifndef __GAME_GAMEPOINTERHANDLER_GAME_H__
#define __GAME_GAMEPOINTERHANDLER_GAME_H__

#include "../../Components/ScriptComponent/IPointerHandler.h"

namespace Game {
	class GamePointerHandler : public Component::IPointerHandler {
		bool VOnPointerMove(const CPoint &mousePos);
		bool VOnPointerButtonDown(const CPoint &mousePos, const TCHAR &buttonName);
		bool VOnPointerButtonUp(const CPoint &mousePos, const TCHAR &buttonName);
		int VGetPointerRadius();
	};
}

#endif // __GAME_GAMEPOINTERHANDLER_GAME_H__
