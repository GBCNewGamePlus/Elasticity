#ifndef __SCRIPT_COMPONENT_H__
#define __SCRIPT_COMPONENT_H__
#include <string>
#include "../../Base/ActorComponent.h"

using namespace std;

class ScriptComponent : public ActorComponent
{
private:
	string path;

public:
	ScriptComponent(string _path);
	string GetPath();
};

#endif
