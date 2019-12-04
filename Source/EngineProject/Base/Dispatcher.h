#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class Dispatcher
{
public:
	void Subscribe(const EventType descriptor, void(*slot)(const Event& e) );
	void Post(const Event& event);
	static Dispatcher* GetInstance();
	
private:
	std::map<EventType, std::vector<void(*)(const Event&)>> observers;
	static Dispatcher* instance;
	Dispatcher();
};

#endif
