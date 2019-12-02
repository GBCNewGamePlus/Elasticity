#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class Dispatcher
{
public:
	using SlotType = std::function< void(const Event&) >;
	void Subscribe(const EventType descriptor, SlotType&& slot);
	void Post(const Event& event);
	static Dispatcher* GetInstance();
private:
	std::map<EventType, std::vector<SlotType>> observers;
	static Dispatcher* instance;
	Dispatcher();
};

#endif
