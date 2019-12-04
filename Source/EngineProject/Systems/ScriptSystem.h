#ifndef __SCRIPT_SYSTEM_H__
#define __SCRIPT_SYSTEM_H__
#include <vector>
#include "../Base/Actor.h"
#include "../Components/ScriptComponent/ScriptComponent.h"
#include "LuaPlus.h"
#include "../GameEngine.h"
using namespace LuaPlus;

class ScriptSystem
{
public:
	ScriptSystem(vector<Actor*>* _actors);
	~ScriptSystem();
	void Run();

private:
	vector<Actor*>* actors;
	LuaState* pLuaState;
};

#endif
