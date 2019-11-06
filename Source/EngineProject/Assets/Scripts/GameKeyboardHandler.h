#ifndef __GAME_GAMEKEYBOARDHANDLER_GAME_H__
#define __GAME_GAMEKEYBOARDHANDLER_GAME_H__

#include "../../Components/ScriptComponent/IKeyboardHandler.h"

namespace Game {
	class GameKeyboardHandler : public Component::IKeyboardHandler {
		bool VOnKeyDown(unsigned int const kcode);
		bool VOnKeyUp(unsigned int const kcode);
	};
}

#endif // __GAME_GAMEKEYBOARDHANDLER_GAME_H__
